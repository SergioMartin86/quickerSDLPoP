#pragma once

// Base controller class
// by eien86

#include <cstdint>
#include <jaffarCommon/exceptions.hpp>
#include <jaffarCommon/json.hpp>
#include <string>
#include <sstream>

namespace jaffar
{

struct input_t
{
  bool restart = false;
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  bool shift = false;
};

class InputParser
{
public:

  InputParser(const nlohmann::json &config) {}

  inline input_t parseInputString(const std::string &inputString) const
  {
    // Storage for the input
    input_t input;

    // Converting input into a stream for parsing
    std::istringstream ss(inputString);

    if (inputString.size() != 9) reportBadInputString(inputString);
    if (inputString[0] != '|') reportBadInputString(inputString);
    if (inputString[1] == 'r') input.restart = true;
    if (inputString[2] != '|') reportBadInputString(inputString);
    if (inputString[3] == 'L') input.left = true;
    if (inputString[4] == 'R') input.right = true;
    if (inputString[5] == 'U') input.up = true;
    if (inputString[6] == 'D') input.down = true;
    if (inputString[7] == 'S') input.shift = true;
    if (inputString[8] != '|') reportBadInputString(inputString);

    // Returning input
    return input;
  }

private:

  static inline void reportBadInputString(const std::string &inputString)
  {
    JAFFAR_THROW_LOGIC("Could not decode input string: '%s'\n", inputString.c_str());
  }

}; // class InputParser

} // namespace jaffar
