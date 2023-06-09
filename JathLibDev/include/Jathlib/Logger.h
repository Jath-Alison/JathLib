#pragma once

#include "vex.h"
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <functional>
#include <memory>

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
        virtual void logHeader(std::ofstream* file) = 0;
        virtual void log(std::ofstream* file) = 0;
        virtual std::string getName() = 0;
      };

      struct LogItemB : public logItem{
        LogItemB(std::string name, std::function<bool(void)> func) : m_name(name), m_function(func){};
        LogItemB(const LogItemB& item) : m_name(item.m_name), m_function(item.m_function){};
        
        void logHeader(std::ofstream* file){ *file << m_name; }
        void log(std::ofstream* file){ *file << m_function(); }
        
        std::string getName(){ return m_name;}
        std::string m_name;
        
        std::function<bool(void)> m_function;
      };
      struct LogItemD : public logItem{
        LogItemD(std::string name, std::function<double(void)> func) : m_name(name), m_function(func){};
        LogItemD(const LogItemD& item) : m_name(item.m_name), m_function(item.m_function){};
        
        void logHeader(std::ofstream* file){ *file << m_name; }
        void log(std::ofstream* file){ *file << m_function(); }
        
        std::string getName(){ return m_name;}
        std::string m_name;
        
        std::function<double(void)> m_function;
      };
      struct LogItemS : public logItem{
        LogItemS(std::string name, std::function<std::string(void)> func) : m_name(name), m_function(func){};
        LogItemS(const LogItemS& item) : m_name(item.m_name), m_function(item.m_function){};
        
        void logHeader(std::ofstream* file){ *file << m_name; }
        void log(std::ofstream* file){ *file << m_function(); }
        
        std::string getName(){ return m_name;}
        std::string m_name;
        
        std::function<std::string(void)> m_function;
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

      
      void addLogItemB(const char* name, std::function<bool(void)> data){
        std::shared_ptr<logItem> temp = std::make_shared<LogItemB>(name,data);
        
        m_logItems.push_back(temp);
      }
      void addLogItemD(const char* name, std::function<double(void)> data){
        std::shared_ptr<logItem> temp = std::make_shared<LogItemD>(name,data);
        
        m_logItems.push_back(temp);
      }
      void addLogItemS(const char* name, std::function<std::string(void)> data){
        std::shared_ptr<logItem> temp = std::make_shared<LogItemS>(name,data);
        
        m_logItems.push_back(temp);
      }

      void logHeader(){
        std::ofstream file;
        file.open(m_path.c_str(),std::ios_base::app);
        for(size_t i = 0; i < m_logItems.size(); i++){
          m_logItems[i]->logHeader(&file);
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
          m_logItems[i]->log(&file);
          if(!(i == m_logItems.size()-1)){
            file << ",";
          }
        }
        file << std::endl;
        file.close();
      }

      std::string m_path;
    private:
      std::vector< std::shared_ptr<logItem> > m_logItems;

  };

  inline auto start_time = std::chrono::high_resolution_clock::now();
  inline auto current_time = std::chrono::high_resolution_clock::now();

  inline double timePassed() {
      current_time = std::chrono::high_resolution_clock::now();
      return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count()/1000.f;
  }

}