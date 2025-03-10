/**
 * NextSim Captain
 * @file : InputStation.hpp
 * @version : 1.0
 * @author : Sujae Jeon
 */

 #pragma once
 #ifndef INPUTSTATION_H
 #define INPUTSTATION_H
 
 #include <vector>
 #include <string>
 
 namespace NextSimIO
 {
 /**
  * @class InputStation
  * @brief Class for each public transit station information
  */
 class InputStation
 {
 public:
     /**
      * @details Constructor
      * @param id Station ID
      * @param link Link ID
      * @param lane Lane ID
      * @param pos Position of station
      * @param parkingLots Number of parking lots
      */
     InputStation(int id, int link, int lane, double pos, int parkingLots);
 
     /**
      * @details Set sequence of line IDs
      * @param lineList Sequence of line IDs that pass the station
     */
     void SetLineList(std::string lineList);
 
     /**
      * @details Set number of parking lots
      * @param parkingLots Number of parking lots at this station
     */
     void SetParkingLots(int parkingLots);
 
     /**
      * @details Set sequence of garage IDs (for rail transit)
      * @param garageList Sequence of garage IDs linked to this station
     */
     void SetGarageList(std::string garageList);
 
     /**
      * @details Get station ID
      * @return Station ID
     */
     int GetId() const { return m_id; }
 
     /**
      * @details Get link ID
      * @return Link ID where the station is located
     */
     int GetLink() const { return m_link; }
 
     /**
      * @details Get lane ID
      * @return Lane ID where the station is located
     */
     int GetLane() const { return m_lane; }
 
     /**
      * @details Get position of station
      * @return Position of station (from link start point)
     */
     double GetPos() const { return m_pos; }
 
     /**
      * @details Get number of parking lots
      * @return Number of parking lots
     */
     int GetParkingLots() const { return m_parkingLots; }
 
     /**
      * @details Get sequence of line IDs
      * @return Sequence of line IDs that pass the station
     */
     std::vector<int> GetLineList() const { return m_lineList; }
 
     /**
      * @details Get sequence of garage IDs (for rail transit)
      * @return Sequence of garage IDs linked to this station
     */
     std::vector<int> GetGarageList() const { return m_garageList; }
 
 private:
     /**
      * @details Station ID
     */
     int m_id;
 
     /**
      * @details Link ID where the station is located
     */
     int m_link;
 
     /**
      * @details Lane ID where the station is located
     */
     int m_lane;
 
     /**
      * @details Position of station (from link start point)
     */
     double m_pos;
 
     /**
      * @details Number of parking lots at this station
     */
     int m_parkingLots;
 
     /**
      * @details Sequence of line IDs that pass the station
     */
     std::vector<int> m_lineList;
 
     /**
      * @details Sequence of garage IDs linked to this station (for rail transit)
     */
     std::vector<int> m_garageList;
 };
 
 /**
  * @class InputDRTStation
  * @brief Class for each Demand-Responsive Transit (DRT) station information
  */
 class InputDRTStation
 {
 public:
     /**
      * @details Constructor
      * @param id DRT station ID
      * @param link Link ID
      * @param lane Lane ID
     */
     InputDRTStation(int id, int link, int lane);
 
     /**
      * @details Set position range of DRT station
      * @param posRange Pair of start and end position (from link start point)
     */
     void SetPosRange(std::string posRange);
 
     /**
      * @details Get DRT station ID
      * @return DRT station ID
     */
     int GetId() const { return m_id; }
     
     /**
      * @details Get link ID
      * @return Link ID where the station is located
     */
     int GetLink() const { return m_link; }
     
     /**
      * @details Get lane ID
      * @return Lane ID where the station is located
     */
     int GetLane() const { return m_lane; }
 
     /**
      * @details Get position range of DRT station
      * @return Pair of start and end position (from link start point)
     */
     std::pair<double, double> GetPosRange() { return m_posRange; }
 
 private:
     /**
      * @details DRT station ID
     */
     int m_id;
 
     /**
      * @details Link ID where the station is located
     */
     int m_link;
 
     /**
      * @details Lane ID where the station is located
     */
     int m_lane;
 
     /**
      * @details Position range of DRT station
     */
     std::pair<double, double> m_posRange;
 };
 } // namespace NextSimIO
 
 #endif
 