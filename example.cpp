#include "logfmt.h"

#define toFile false

// Compile with "g++ example.cpp logfmt.cpp -o example -Wall -Wextra -pedantic -std=c++17 -pthread -Iexternal/spdlog/include -fmax-errors=1 -O3 -march=native"
// dont forget to create logs folder if logging to file

int main()
{
  std::string a ="testing";
  float float_test = 2.8;
  long long_test = 100;
  logfmt log("test", toFile);

  spdlog::set_level(spdlog::level::trace);
  log.WithField(log.custom_field={{"animal", "walrus"}, {"total", 100}}).info("INFO of WALRUS and its total");
  log.info("No Walrus ");
  log.WithField(log.custom_field={{"animal", "horse"}, {"total", 90}}).debug("DEBUG of HORSE and its total");
  log.debug("No Horse");

  log.OutputJSON(); //output in JSON format
  log.WithField(log.custom_field={{"animal", "bird"}, {"total", 40.5}}).trace("TRACE of BIRD and its total");
  log.trace("No Bird");
  log.WithField(log.custom_field={{"animal", "dog"}, {"total", float_test}}).warn("WARN of DOG and its total");
  log.warn("No Dog");

  log.OutputDefault(); //output in default format
  log.WithField(log.custom_field={{"animal", "cat"}, {"total", long_test}}).critical("CRITICAL of CAT and its total");
  log.critical("No Cat");
  log.WithField(log.custom_field={{"animal", "falcon"}, {"total", 10}}).error("ERROR of FALCON and its total");
  log.error("No Falcon");

  log.OutputJSON();
  auto staticformat = log.WithField(log.custom_field={{"float",float_test}, {"long", long_test}, {"string", a}});
  staticformat.info("This is INFO with custom key");
  staticformat.debug("This is DEBUG with custom key");
  staticformat.trace("This is TRACE with custom key");
  staticformat.warn("This is WARN with custom key");
  staticformat.critical("This is CRITICAL with custom key");
  staticformat.error("This is ERROR with custom key");

  log.OutputDefault();
  auto staticformat2 = log.WithField(log.custom_field={{"animal","griffin"}, {"rider", "azure"}, {"weapon", "spear"}});
  staticformat2.info("This is INFO with custom key");
  staticformat2.debug("This is DEBUG with custom key");
  staticformat2.trace("This is TRACE with custom key");
  staticformat2.warn("This is WARN with custom key");
  staticformat2.critical("This is CRITICAL with custom key");
  staticformat2.error("This is ERROR with custom key");
}
