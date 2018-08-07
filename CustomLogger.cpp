#include "CustomLogger.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////

//class Entry

//private
std::string CustomLogger::Entry::AddQuotation(std::string msg) //return quotation in message input
{
  return "\"" + msg + "\"";
}

std::string CustomLogger::Entry::JSONformatter() //return json formatter
{
  return "\"date\" : \"%d-%m-%Y\" , \"time\" : \"%H:%M:%S\" , \"name\" : \"%n\" , \"level\" : \"%^%l%$\" , \"message\" : \"%v\" ";
}

std::string CustomLogger::Entry::processPattern(std::string pattern)
{
  if(JSON) //jsonform is true
  {
    return "{ " + JSONformatter() + pattern + "}";
  }
  else //jsonform is false
  {
    return "%+ " + pattern;
  }
}

std::string CustomLogger::Entry::processKey()
{
  std::string pattern ="";

  for (auto& [key,val] : entry_field)
  {
    pattern = pattern + casting(key, val);
  }
  return processPattern(pattern);
}

std::string CustomLogger::Entry::casting(std::string key, std::any val) //casting the value in map into string
{
  std::string custom_string;
  if(JSON)
  {
    custom_string = custom_string + ", " + AddQuotation(key) + " : " ;
    //check type for any_cast
    if (val.type() == typeid(char)) //char
    {
      custom_string = custom_string + "\"";
      custom_string += (std::any_cast<char>(val));
      custom_string = custom_string + "\" ";
    }
    else if (val.type() == typeid(const char *)) //array of char
    {
      std::string temp(std::any_cast<const char *>(val));
      custom_string = custom_string + AddQuotation(temp) + " ";
    }
    else if (val.type() == typeid(int)) //integer
    {
      custom_string = custom_string + std::to_string(std::any_cast<int>(val)) + " ";
    }
    else if (val.type() == typeid(float)) //float
    {
      custom_string = custom_string + std::to_string(std::any_cast<float>(val)) + " ";
    }
    else if (val.type() == typeid(double)) //double
    {
      custom_string = custom_string + std::to_string(std::any_cast<double>(val)) + " ";
    }
    else if (val.type() == typeid(bool)) //boolean
    {
      if (std::any_cast<bool>(val) == 1)
      {
        custom_string = custom_string + "true ";
      }
      else if (std::any_cast<bool>(val) == 0)
      {
        custom_string = custom_string + "false ";
      }
    }
    else if (val.type() == typeid(std::string)) //string
    {
      custom_string = custom_string + AddQuotation(std::any_cast<std::string>(val)) + " ";
    }
    else if (val.type() == typeid(long)) //long
    {
      custom_string = custom_string + std::to_string(std::any_cast<long>(val)) + " ";
    }
  }
  else
  {
    custom_string = custom_string + key + " = " ;
    //check type for any_cast
    if (val.type() == typeid(char))
    {
      custom_string = custom_string + "\"";
      custom_string += (std::any_cast<char>(val));
      custom_string = custom_string + "\" ";
    }
    else if (val.type() == typeid(const char *))
    {
      std::string temp(std::any_cast<const char *>(val));
      custom_string = custom_string + AddQuotation(temp) + " ";
    }
    else if (val.type() == typeid(int))
    {
      custom_string = custom_string + std::to_string(std::any_cast<int>(val)) + " ";
    }
    else if (val.type() == typeid(float))
    {
      custom_string = custom_string + std::to_string(std::any_cast<float>(val)) + " ";
    }
    else if (val.type() == typeid(double))
    {
      custom_string = custom_string + std::to_string(std::any_cast<double>(val)) + " ";
    }
    else if (val.type() == typeid(bool))
    {
      if (std::any_cast<bool>(val) == 1)
      {
        custom_string = custom_string + "true ";
      }
      else if (std::any_cast<bool>(val) == 0)
      {
        custom_string = custom_string + "false ";
      }
    }
    else if (val.type() == typeid(std::string))
    {
      custom_string = custom_string + AddQuotation(std::any_cast<std::string>(val)) + " ";
    }
    else if (val.type() == typeid(long))
    {
      custom_string = custom_string + std::to_string(std::any_cast<long>(val)) + " ";
    }
  }

  return custom_string;
}

//public
CustomLogger::Entry::Entry()
{
  //default ctor (not used)
}

CustomLogger::Entry::Entry(std::shared_ptr<spdlog::logger>& log, bool JSON ) //ctor
{
  entry_log = log;
  this -> JSON = JSON;
}

CustomLogger::Entry& CustomLogger::Entry::WithField(std::map<std::string, std::any>& keyMap)
{
  entry_field = keyMap;
  return *this;
}
void CustomLogger::Entry::info(std::string msg)
{
  entry_log -> set_pattern(processKey());
  entry_log -> info(msg);
}

void CustomLogger::Entry::trace(std::string msg)
{
  entry_log -> set_pattern(processKey());
  entry_log -> trace(msg);
}

void CustomLogger::Entry::debug(std::string msg)
{
  entry_log -> set_pattern(processKey());
  entry_log -> debug(msg);
}

void CustomLogger::Entry::warn(std::string msg)
{
  entry_log -> set_pattern(processKey());
  entry_log -> warn(msg);
}

void CustomLogger::Entry::error(std::string msg)
{
  entry_log -> set_pattern(processKey());
  entry_log -> error(msg);
}

void CustomLogger::Entry::critical(std::string msg)
{
  entry_log -> set_pattern(processKey());
  entry_log -> critical(msg);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
// CustomLogger implementation

CustomLogger::CustomLogger(std::string name, bool to_file) //constructor
{
  if (to_file)
  {
    logger = spdlog::basic_logger_mt(name , "logs/basic-log.txt");
  }
  else
  {
    logger = spdlog::stdout_color_mt(name);
  }
  WriteFile = to_file;
  JSONstatus = false;
}

// function
void CustomLogger::OutputJSON()
{
  JSONstatus = true;
}

void CustomLogger::OutputDefault()
{
  JSONstatus = false;
}

CustomLogger::Entry& CustomLogger::WithField(std::map<std::string, std::any>& keyMap)
{
  loggerEntry = Entry(logger, JSONstatus);
  return loggerEntry.WithField(keyMap);
}

std::string CustomLogger::JSONformatter()
{
  return "\"date\" : \"%d-%m-%Y\" , \"time\" : \"%H:%M:%S\" , \"name\" : \"%n\" , \"level\" : \"%^%l%$\" , \"message\" : \"%v\" ";
}

//basic logging
void CustomLogger::info(std::string msg)
{
  if(JSONstatus)
  {
    logger -> set_pattern("{ " + JSONformatter() + "}");
  }
  else
  {
    logger -> set_pattern("%+");
  }
  logger -> info(msg);
}

void CustomLogger::trace(std::string msg)
{
  if(JSONstatus)
  {
    logger -> set_pattern("{ " + JSONformatter() + "}");
  }
  else
  {
    logger -> set_pattern("%+");
  }
  logger -> trace(msg);
}
void CustomLogger::debug(std::string msg)
{
  if(JSONstatus)
  {
    logger -> set_pattern("{ " + JSONformatter() + "}");
  }
  else
  {
    logger -> set_pattern("%+");
  }
  logger -> debug(msg);
}
void CustomLogger::warn(std::string msg)
{
  if(JSONstatus)
  {
    logger -> set_pattern("{ " + JSONformatter() + "}");
  }
  else
  {
    logger -> set_pattern("%+");
  }
  logger -> warn(msg);
}
void CustomLogger::error(std::string msg)
{
  if(JSONstatus)
  {
    logger -> set_pattern("{ " + JSONformatter() + "}");
  }
  else
  {
    logger -> set_pattern("%+");
  }
  logger -> error(msg);
}
void CustomLogger::critical(std::string msg)
{
  if(JSONstatus)
  {
    logger -> set_pattern("{ " + JSONformatter() + "}");
  }
  else
  {
    logger -> set_pattern("%+");
  }
  logger -> critical(msg);
}
