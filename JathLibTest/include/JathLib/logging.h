#pragma once
#include "vex.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <functional>
#include <utility>
#include <chrono>
#include <vector>
#include <thread>
#include "robot-config.h"

namespace Jath{

  auto start_time = std::chrono::high_resolution_clock::now();
  auto current_time = std::chrono::high_resolution_clock::now();

  double timePassed() {
      current_time = std::chrono::high_resolution_clock::now();
      return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count()/1000.f;
  }

  class LogFile{
    public:

      struct LogItem{
       LogItem(const char* name, std::function<double(void)> func) : m_function(func){
         std::strcpy(m_name, name);
       };
       LogItem(const LogItem& item) : m_function(item.m_function){
         std::strcpy(m_name, item.m_name);
       };
       char m_name[50];
       std::function<double(void)> m_function;
      };

      LogFile(const char* path){
        //m_path = new char[50];
        std::strcpy(m_path, path);
        std::strcat(m_path, ".csv");
        int count = 1;
        
        char temp[5];

        while(Brain.SDcard.exists(m_path)){
          std::strcpy(m_path, path);

          std::strcpy(temp, "");
          sprintf(temp, "%i", count);   

          std::strcat(m_path, temp);
          std::strcat(m_path, ".csv");
          count++;
        }
      }
       
      void addLogItem(const char* name, std::function<double(void)> data){
        LogItem temp(name,data);
        m_LogItems.push_back(temp);
      }
      void addLogItem(LogItem item){
        m_LogItems.push_back(item);
      }

      void openFile (){
        m_file.open(m_path,std::ios_base::app);
      }
      void closeFile(){
        m_file.close();
      }

      void LogHeader(){
        m_file.open(m_path,std::ios_base::app);
        for(size_t i = 0; i < m_LogItems.size(); i++){
          m_file << m_LogItems[i].m_name;
          if(!(i == m_LogItems.size()-1)){
            m_file << ",";
          }
        }
        m_file<<std::endl;
        m_file.close();
      }
      void Log(){
        m_file.open(m_path,std::ios_base::app);
        for(size_t i = 0; i<m_LogItems.size(); i++){
          m_file << m_LogItems[i].m_function();
          if(!(i == m_LogItems.size()-1)){
            m_file << ",";
          }
        }
        m_file << std::endl;
        m_file.close();
      }

    private:
      char m_path[50];
      std::vector<LogItem> m_LogItems;
      std::ofstream m_file;
  };

  std::vector<LogFile*> LogFiles;

  int LogAllHeaders(){
    for(int i = 0;i<LogFiles.size();i++){
      LogFiles[i]->LogHeader();
    }  
    return 0;
  }

  int LogAll(){
    for(int i = 0;i<LogFiles.size();i++){
      LogFiles[i]->Log();
    }  
    return 0;
  }

}