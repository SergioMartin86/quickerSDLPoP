#pragma once

// Base controller class
// by eien86

#include <cstdint>
#include <string>
#include <sstream>

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

    // Converting input into a stream for parsing
    std::istringstream ss(input);

    // Start separator
    if (ss.get() != '|') isValid = false;

    // Clearing input 
    _input = input_t();

    // Parsing console inputs
    isValid &= parseConsoleInput(_input.restart, ss);

    // Mid separator
    if (ss.get() != '|') isValid = false;

    // Parsing controller 1 inputs
    isValid &= parseGameInput(_input, ss);

    // End separator
    if (ss.get() != '|') isValid = false;

    // If its not the end of the stream, then extra values remain and its invalid
    ss.get();
    if (ss.eof() == false) isValid = false;

    // Returning valid flag
    return isValid;
  };

  inline input_t getParsedInput() { return _input; }

  private:

  static bool parseGameInput(input_t& input, std::istringstream& ss)
  {
    // Currently read character
    char c;

    // Left
    c = ss.get();
    if (c != '.' && c != 'L') return false;
    if (c == 'L') input.left = true;

    // Right
    c = ss.get();
    if (c != '.' && c != 'R') return false;
    if (c == 'R') input.right = true;

    // Up
    c = ss.get();
    if (c != '.' && c != 'U') return false;
    if (c == 'U') input.up = true;

    // Down
    c = ss.get();
    if (c != '.' && c != 'D') return false;
    if (c == 'D') input.down = true;

    // Shift
    c = ss.get();
    if (c != '.' && c != 'S') return false;
    if (c == 'S') input.shift = true;

    return true;
  }

  static bool parseConsoleInput(bool& restart, std::istringstream& ss)
  {
    // Parse valid flag
    bool isValid = true; 

    // Currently read character
    char c;

    // Reset trigger
    c = ss.get();
    if (c != '.' && c != 'r') isValid = false;
    if (c == 'r') restart = true;
    if (c == '.') restart = false;

    // Return valid flag
    return isValid;
  }

  input_t _input;
};
