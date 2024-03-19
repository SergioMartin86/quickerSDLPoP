#pragma once

// Base controller class
// by eien86

#include <cstdint>
#include <string>
#include <sstream>

namespace SDLPoP 
{

class Controller
{
public:

  enum controller_t { none, joypad, fourscore1, fourscore2 };

  typedef uint8_t port_t;

  struct input_t
  {
    bool restart = false;
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shift = false;
  };

  inline bool parseInputString(const std::string& input)
  {
    // Parse valid flag
    bool isValid = true;
  
    input_t newInput;

    if (input.size() != 9) return false;
    if (input[0] != '|') return false;
    if (input[1] == 'r') newInput.restart = true;
    if (input[2] != '|') return false;
    if (input[3] == 'L') newInput.left = true;
    if (input[4] == 'R') newInput.right = true;
    if (input[5] == 'U') newInput.up = true;
    if (input[6] == 'D') newInput.down = true;
    if (input[7] == 'S') newInput.shift = true;
    if (input[8] != '|') return false;

    _input = newInput;
    
    // Returning valid flag
    return isValid;
  }

  inline input_t getParsedInput() { return _input; }

  private: 
  
  input_t _input;

}; // class Controller

} // namespace SDLPoP
