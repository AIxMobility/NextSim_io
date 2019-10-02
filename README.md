The I/O parsing of XML for the simulation


Build (from root directory):
> $cmake -H. -Bbuild

> $cmake --build build -- -j3

> $g++ -arch x86_64 -Wl,-rpath,'$ORIGIN' -o Main main.cpp ./build/lib/libapp.dylib

>./Main

Additional Comments:

The XML file directory is loaded at runtime. Main.cpp has to be in the same directory as the network_xml for the tiny_xml to execute parsing correctly. 

The end-tags of the XML files need to be checked beforehand. 

