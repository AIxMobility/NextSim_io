/**
 * NextSim Captain
 * @file : DedicatedLaneArr.hpp
 * @brief dedicatedLane.xml, the dedicated lanes of a network. When the file
 * exists it replaces the laneAccessType attributes of network.xml.
 */
#pragma once
#ifndef DEDICATEDLANEARR_H
#define DEDICATEDLANEARR_H

#include <NextSim_io/inputclass/InputDedicatedLane.hpp>

#include <cstddef>
#include <filesystem>
#include <map>
#include <utility>

namespace NextSimIO
{
class DedicatedLaneArr
{
public:
    //! Reads dedicatedLane.xml next to network.xml. Without the file HasFile() is false.
    DedicatedLaneArr();
    explicit DedicatedLaneArr(const std::filesystem::path& path);

    [[nodiscard]] bool HasFile() const { return m_hasFile; }

    //! The lane's entry, or nullptr when the file does not list it
    [[nodiscard]] const InputDedicatedLane* Find(std::size_t linkId, std::size_t laneId) const;

    //! Access type of a lane: the file's when the file exists, else the network.xml attribute
    [[nodiscard]] std::string AccessType(std::size_t linkId, std::size_t laneId, const char* networkXmlType) const;

    [[nodiscard]] const std::map<std::pair<std::size_t, std::size_t>, InputDedicatedLane>& GetLanes() const
    {
        return m_lanes;
    }

private:
    bool m_hasFile = false;
    std::map<std::pair<std::size_t, std::size_t>, InputDedicatedLane> m_lanes;
};
}  // namespace NextSimIO

#endif
