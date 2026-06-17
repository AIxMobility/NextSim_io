/**
 * NextSim Captain
 * @file : DetectorArr.hpp
 * @version : 1.0
 * @author : Keunhee Cho
 */

#pragma once
#ifndef NEXTSIMIO_DETECTORARR_HPP
#define NEXTSIMIO_DETECTORARR_HPP

#include <vector>

#include <NextSim_io/inputclass/InputE1Detector.hpp>
#include <NextSim_io/inputclass/InputE2Detector.hpp>
#include <NextSim_io/inputclass/InputE3Detector.hpp>

namespace NextSimIO
{
class DetectorArr
{
public:
    DetectorArr();

    const std::vector<InputE1Detector>& GetE1Detectors() const
    {
        return m_e1Detectors;
    }
    const std::vector<InputE2Detector>& GetE2Detectors() const
    {
        return m_e2Detectors;
    }
    const std::vector<InputE3Detector>& GetE3Detectors() const
    {
        return m_e3Detectors;
    }

private:
    std::vector<InputE1Detector> m_e1Detectors;
    std::vector<InputE2Detector> m_e2Detectors;
    std::vector<InputE3Detector> m_e3Detectors;
};
} // namespace NextSimIO

#endif
