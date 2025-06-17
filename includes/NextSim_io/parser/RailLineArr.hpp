/**
 * NextSim Captain
 * @file : RailLineArr.hpp
 * @version : 1.0
 * @author : Yuseock Hwang
 */


 #ifndef RAILLineARR_H
 #define RAILLineARR_H
 
 #include <NextSim_io/inputclass/InputRailLine.hpp>
 
 namespace NextSimIO
 {
 /**
  * @class RailLineArr
  * @brief 
  */
 class RailLineArr
 {
 public:
     /**
      * @details Constructor 
     */
    RailLineArr();
 
     /**
      * @details
      * @return 
     */
    std::vector<InputRailLine> GetRailLine() const { return m_railLine; }
 
 
 private:
 
     /**
      * @details Vector of all signal plans
     */
    std::vector<InputRailLine> m_railLine;
 
 };
 } // namespace NextSimIO
 
 
 
 #endif