#pragma once

#include "vex.h"
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <functional>

#include <iostream>

namespace Jath{

  // union data{
  //   int intData;
  //   double doubleData;
  //   std::string stringData;
  // };

  class Logger{
    public:

      struct logItem{
        logItem(std::string name, std::function<double(void)> func) : m_name(name), m_function(func){};
        logItem(const logItem& item) : m_name(item.m_name), m_function(item.m_function){};
        std::string m_name;
        std::function<double(void)> m_function;
      };

      Logger(std::string path){
        int count = 1;

        m_path = path + ".csv";

        while(Brain.SDcard.exists(m_path.c_str())){
          m_path = path;

          char tempPath[5] = "";
          sprintf(tempPath, "%i",count);

          m_path += tempPath;
          m_path += ".csv";
          count++;
        }
          
      }

      Logger(const Logger& logger) : m_logItems(logger.m_logItems), m_path(logger.m_path){}

      void addLogItem(const char* name, std::function<double(void)> data){
        logItem temp(name,data);
        m_logItems.push_back(temp);
      }
      void addLogItem(logItem item){
        m_logItems.push_back(item);
      }

      void logHeader(){
        std::ofstream file;
        file.open(m_path.c_str(),std::ios_base::app);
        for(size_t i = 0; i < m_logItems.size(); i++){
          file << m_logItems[i].m_name;
          if(!(i == m_logItems.size()-1)){
            file << ",";
          }
        }
        file<<std::endl;
        file.close();
      }
      void log(){
        std::ofstream file;
        file.open(m_path.c_str(),std::ios_base::app);
        for(size_t i = 0; i<m_logItems.size(); i++){
          file << m_logItems[i].m_function();
          if(!(i == m_logItems.size()-1)){
            file << ",";
          }
        }
        file << std::endl;
        file.close();
      }

      std::string m_path;
    private:
      std::vector<logItem> m_logItems;

  };

  inline auto start_time = std::chrono::high_resolution_clock::now();
  inline auto current_time = std::chrono::high_resolution_clock::now();

  inline double timePassed() {
      current_time = std::chrono::high_resolution_clock::now();
      return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count()/1000.f;
  }

}