"""Compile the real path resolver and check each config/layout in a fresh process."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest


class FilePathTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix="nextsim-path-tests-")
        cls.addClassCleanup(cls.temp.cleanup)
        cls.probe = Path(cls.temp.name) / "paths"
        source = Path(cls.temp.name) / "paths.cpp"
        source.write_text('#include <NextSim_io/FilePath.hpp>\n#include <iostream>\n'
                          'int main() { std::cout << NextSimIO::NetworkXmlFilePath.generic_string() '
                          '<< "\\n" << NextSimIO::ParameterXmlFilePath.generic_string(); }')
        subprocess.run([os.environ.get("CXX", "c++"), "-std=c++17", "-I",
                        str(Path(__file__).resolve().parents[1] / "includes"),
                        str(source), "-o", str(cls.probe)], check=True)

    def check_paths(self, config, directories, network, parameter, override=True):
        with tempfile.TemporaryDirectory(prefix="nextsim-config-") as tmp:
            root = Path(tmp)
            inputs = root / "SimulationInput"
            inputs.mkdir()
            (inputs / "config.txt").write_bytes(config.encode())
            for directory in directories:
                (inputs / directory).mkdir(parents=True)
            cwd = root / "nested" / "working"
            cwd.mkdir(parents=True)
            env = dict(os.environ)
            env.pop("NEXTSIM_PROJECT_ROOT", None)
            if override:
                env["NEXTSIM_PROJECT_ROOT"] = str(root)
                cwd = Path(self.temp.name)
            actual = subprocess.check_output([str(self.probe)], cwd=cwd, env=env, text=True).splitlines()
            self.assertEqual(actual, [str(inputs / network), str(inputs / parameter)])

    def test_modern_network_with_whitespace_and_crlf(self):
        self.check_paths(" network = tram \r\n", ["networks/tram/parameter_xml"],
                         "networks/tram", "networks/tram/parameter_xml")

    def test_modern_key_overrides_legacy_keys(self):
        self.check_paths("branch=old\nnetwork_name=other\nnetwork=tram\n", [],
                         "networks/tram", "networks/tram/parameter_xml")

    def test_migrated_folder_with_legacy_keys(self):
        self.check_paths("branch=old\nnetwork_name=tram\n", ["networks/tram"],
                         "networks/tram", "networks/tram/parameter_xml")

    def test_legacy_layout_and_parameters(self):
        self.check_paths("branch=old\nnetwork_name=tram\n",
                         ["datasets/old/network_xml_tram", "datasets/old/parameter_xml"],
                         "datasets/old/network_xml_tram", "datasets/old/parameter_xml")

    def test_shared_parameters(self):
        self.check_paths("network=tram\n", ["networks/tram", "parameter_xml"],
                         "networks/tram", "parameter_xml")

    def test_per_network_parameters_override_shared(self):
        self.check_paths("network=tram\n", ["networks/tram/parameter_xml", "parameter_xml"],
                         "networks/tram", "networks/tram/parameter_xml")

    def test_legacy_key_without_branch(self):
        self.check_paths("network_name=tram\n", [], "networks/tram", "networks/tram/parameter_xml")

    def test_find_project_from_nested_working_directory(self):
        self.check_paths("network=tram\n", [], "networks/tram", "networks/tram/parameter_xml", override=False)


if __name__ == "__main__":
    unittest.main()
