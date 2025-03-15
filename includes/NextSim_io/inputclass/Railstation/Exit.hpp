/**
 * NextSim Captain
 * @file : Exit.hpp
 * @version : 1.0
 * @author : YuseockHwang
 */

 #pragma once
 #ifndef Exit_H
 #define Exit_H
 
 #include <string>
 
 namespace NextSimIO
 {
 /**
  * @class Exit
  * @brief Class for Exit information
  */
 class Exit
 {
 public:
     /**
      * @details Constructor
      * @param id exit ID
      * @param link 
      * @param offset 
      * @param accesstime 
      */
    Exit(int id, int link, int offset, double accesstime);
 
     /**
      * @details 
      * @return 
      */
    int GetId() { return m_id; }

     /**
      * @details 
      * @return 
      */
    int GetLink() { return m_link; }

      /**
      * @details 
      * @return 
      */
    int GetOffset() { return m_offset; }

     /**
      * @details 
      * @return 
      */
    double GetAccesstime() { return m_accesstime; }

 
 private:
     /**
      * @details Exit ID
     */
    int m_id;

     /**
      * @details 
     */
    int m_link;

     /**
      * @details 
     */
    int m_offset;

     /**
      * @details 
     */
    double m_accesstime;

 };
 } // namespace NextSimIO
 
 #endif