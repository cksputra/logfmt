#include "logfmt.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////

// class Entry

// private
std::string logfmt::Entry::add_quotation(std::string msg) {
  return "\"" + msg + "\"";
}

void logfmt::Entry::process_key(std::string& msg) {
  std::string pattern = " ";

  for (auto& [key, val] : entry_field) {
    pattern = pattern + cast_key(key, val);
  }

  if (JSON) {
    msg = add_quotation(msg);
  }

  msg = msg + pattern;
}

std::string logfmt::Entry::cast_key(std::string key, std::any val) {
  std::string custom_string;

  if (JSON) {
    custom_string = ", " + add_quotation(key) + " : ";
  } else {
    custom_string = custom_string + key + " = ";
  }
  if (val.type() == typeid(char)) {
    custom_string = custom_string + "\"";
    custom_string += (std::any_cast<char>(val));
    custom_string = custom_string + "\" ";
  } else if (val.type() == typeid(const char*)) {
    std::string temp(std::any_cast<const char*>(val));
    custom_string = custom_string + add_quotation(temp) + " ";
  } else if (val.type() == typeid(int)) {
    custom_string =
        custom_string + std::to_string(std::any_cast<int>(val)) + " ";
  } else if (val.type() == typeid(float)) {
    custom_string =
        custom_string + std::to_string(std::any_cast<float>(val)) + " ";
  } else if (val.type() == typeid(double)) {
    custom_string =
        custom_string + std::to_string(std::any_cast<double>(val)) + " ";
  } else if (val.type() == typeid(bool)) {
    if (std::any_cast<bool>(val) == 1) {
      custom_string = custom_string + "true ";
    } else if (std::any_cast<bool>(val) == 0) {
      custom_string = custom_string + "false ";
    }
  } else if (val.type() == typeid(std::string)) {
    custom_string =
        custom_string + add_quotation(std::any_cast<std::string>(val)) + " ";
  } else if (val.type() == typeid(long)) {
    custom_string =
        custom_string + std::to_string(std::any_cast<long>(val)) + " ";
  }

  return custom_string;
}

// public
logfmt::Entry::Entry() {
  // default ctor (not used)
}

logfmt::Entry::Entry(std::shared_ptr<spdlog::logger>& log, bool JSON) {
  entry_log = log;
  this->JSON = JSON;
}

logfmt::Entry& logfmt::Entry::with_field(
    std::map<std::string, std::any>& key_map) {
  entry_field = key_map;
  return *this;
}
void logfmt::Entry::info(std::string msg) {
  process_key(msg);
  entry_log->info(msg);
}

void logfmt::Entry::trace(std::string msg) {
  process_key(msg);
  entry_log->trace(msg);
}

void logfmt::Entry::debug(std::string msg) {
  process_key(msg);
  entry_log->debug(msg);
}

void logfmt::Entry::warn(std::string msg) {
  process_key(msg);
  entry_log->warn(msg);
}

void logfmt::Entry::error(std::string msg) {
  process_key(msg);
  entry_log->error(msg);
}

void logfmt::Entry::critical(std::string msg) {
  process_key(msg);
  entry_log->critical(msg);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
// logfmt implementation

// ctor
logfmt::logfmt(std::string name, bool to_file) {
  if (to_file) {
    logger = spdlog::basic_logger_mt(name, "logs/basic-log.txt");
  } else {
    logger = spdlog::stdout_color_mt(name);
  }
  write_file = to_file;
  JSON_status = false;
}

// function
void logfmt::JSON_output() {
  JSON_status = true;
  logger->set_pattern(JSON_formatter());
}

void logfmt::default_output() {
  JSON_status = false;
  logger->set_pattern("%+");
}

logfmt::Entry& logfmt::with_field(std::map<std::string, std::any>& key_map) {
  logger_entry = Entry(logger, JSON_status);
  return logger_entry.with_field(key_map);
}

std::string logfmt::add_quotation(std::string msg) {
  return "\"" + msg + "\" ";
}

std::string logfmt::JSON_formatter() {
  return "{ \"date\" : \"%d-%m-%Y\" , \"time\" : \"%H:%M:%S\" , \"name\" : "
         "\"%n\" , \"level\" : \"%^%l%$\" , \"message\" : %v}";
}

// basic logging
void logfmt::info(std::string msg) {
  if (JSON_status) {
    msg = add_quotation(msg);
  }

  logger->info(msg);
}

void logfmt::trace(std::string msg) {
  if (JSON_status) {
    msg = add_quotation(msg);
  }

  logger->trace(msg);
}
void logfmt::debug(std::string msg) {
  if (JSON_status) {
    msg = add_quotation(msg);
  }

  logger->debug(msg);
}
void logfmt::warn(std::string msg) {
  if (JSON_status) {
    msg = add_quotation(msg);
  }

  logger->warn(msg);
}
void logfmt::error(std::string msg) {
  if (JSON_status) {
    msg = add_quotation(msg);
  }

  logger->error(msg);
}
void logfmt::critical(std::string msg) {
  if (JSON_status) {
    msg = add_quotation(msg);
  }

  logger->critical(msg);
}
