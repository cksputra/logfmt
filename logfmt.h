#pragma once

#include <any>
#include <iostream>
#include <map>
#include <typeinfo>
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

class logfmt {
 private:
  // member of logfmt
  class Entry {
    // member of Entry
   private:
    std::map<std::string, std::any> entry_field;
    std::shared_ptr<spdlog::logger> entry_log;
    bool JSON;
    // function
    std::string add_quotation(std::string msg);  // add quotation into message
    void process_key(std::string& msg);          // process the custom key
    std::string cast_key(std::string key,
                         std::any val);  // cast any type to its original type
   public:
    // default ctor
    Entry();
    // ctor with parameter
    Entry(std::shared_ptr<spdlog::logger>& log, bool JSON);
    // function
    Entry& with_field(std::map<std::string, std::any>& key_map);
    void info(std::string msg);
    void trace(std::string msg);
    void debug(std::string msg);
    void warn(std::string msg);
    void error(std::string msg);
    void critical(std::string msg);
  };
  Entry logger_entry;
  std::shared_ptr<spdlog::logger> logger;
  bool JSON_status;
  bool write_file;  // make this true to write log into file

  // private function
  std::string JSON_formatter();  // make the log in JSON format
  std::string add_quotation(std::string msg);

 public:
  // member
  std::map<std::string, std::any> custom_field;
  // ctor
  logfmt(std::string name, bool to_file);
  // function
  void JSON_output();     // make output into JSON format
  void default_output();  // make output into default format
  logfmt::Entry& with_field(std::map<std::string, std::any>& key_map);

  // basic logging
  void info(std::string msg);
  void trace(std::string msg);
  void debug(std::string msg);
  void warn(std::string msg);
  void error(std::string msg);
  void critical(std::string msg);
};
