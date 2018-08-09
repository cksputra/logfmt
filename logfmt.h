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
      std::string add_quotation(std::string msg); 
      void process_key(std::string& msg);
      std::string cast_default(std::string key, std::any val);
      std::string cast_JSON(std::string key, std::any val);
    public:
      Entry(); //default ctor
      Entry(std::shared_ptr<spdlog::logger>& log, bool JSON ); //ctor with parameter
      Entry& with_field(std::map<std::string, std::any>& keyMap);
      void info(std::string msg);
      void trace(std::string msg);
      void debug(std::string msg);
      void warn(std::string msg);
      void error(std::string msg);
      void critical(std::string msg);
  };
  Entry logger_entry;
  std::shared_ptr<spdlog::logger> logger;
  bool JSON_status; // make this true to make log in JSON form / false in normal form
  bool write_file; // make this true to write log into file
  //private function
  std::string JSON_formatter(); // make the log in JSON format
  std::string add_quotation(std::string msg);
public:
  //member
  std::map<std::string, std::any> custom_field;
  //ctor
  logfmt(std::string name, bool to_file);
  //function
  void JSON_output();
  void default_output();
  logfmt::Entry& with_field(std::map<std::string, std::any>& keyMap);
  
  //basic logging
  void info(std::string msg);
  void trace(std::string msg);
  void debug(std::string msg);
  void warn(std::string msg);
  void error(std::string msg);
  void critical(std::string msg);
};
