#pragma once

#include <iostream>
#include <map>
#include <any>
#include <typeinfo>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

class logfmt
{
private:
  //member
  class Entry
  {
    private:
      //member
      std::map<std::string, std::any> entry_field;
      std::shared_ptr<spdlog::logger> entry_log;
      bool JSON;
      //function
      std::string AddQuotation(std::string msg);
      void processKey(std::string& msg);
      std::string casting(std::string key, std::any val);
    public:
      Entry(); //default ctor
      Entry(std::shared_ptr<spdlog::logger>& log, bool JSON ); //ctor with parameter
      Entry& WithField(std::map<std::string, std::any>& keyMap);
      void info(std::string msg);
      void trace(std::string msg);
      void debug(std::string msg);
      void warn(std::string msg);
      void error(std::string msg);
      void critical(std::string msg);
  };
  Entry loggerEntry;
  std::shared_ptr<spdlog::logger> logger;
  bool JSONstatus; // make this true to make log in JSON form / false in normal form
  bool WriteFile; // make this true to write log into file
public:
  //member
  std::map<std::string, std::any> custom_field;
  //ctor
  logfmt(std::string name, bool to_file);
  //function
  void OutputJSON();
  void OutputDefault();
  logfmt::Entry& WithField(std::map<std::string, std::any>& keyMap);
  std::string JSONformatter();
  std::string AddQuotation(std::string msg);

  //basic logging
  void info(std::string msg);
  void trace(std::string msg);
  void debug(std::string msg);
  void warn(std::string msg);
  void error(std::string msg);
  void critical(std::string msg);
};
