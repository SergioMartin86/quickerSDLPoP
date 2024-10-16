#pragma once

#include <jaffarCommon/serializers/base.hpp>
#include <jaffarCommon/deserializers/base.hpp>
#include <jaffarCommon/logger.hpp>
#include <jaffarCommon/json.hpp>
#include <jaffarCommon/hash.hpp>
#include <jaffarCommon/exceptions.hpp>
#include <SDL.h>
#include "inputParser.hpp"

class SDLPoPInstanceBase
{
  public:

  SDLPoPInstanceBase(const nlohmann::json &config)
  {
    _sdlPopRootPath = jaffarCommon::json::getString(config, "SDLPoP Root Path");
    _levelsFilePath = jaffarCommon::json::getString(config, "Levels File Path");
    _gameVersion = jaffarCommon::json::getString(config, "Game Version");

    _inputParser = std::make_unique<jaffar::InputParser>(config);
  }

  virtual ~SDLPoPInstanceBase() = default;

  virtual void initialize() = 0;

  virtual inline void advanceState(const jaffar::input_t &input)
  {
    advanceStateImpl(input);
  }
  
  virtual size_t getFullStateSize() const = 0;
  virtual size_t getDifferentialStateSize() const = 0;

  inline jaffar::InputParser *getInputParser() const { return _inputParser.get(); }

  // Virtual functions

  virtual void serializeState(jaffarCommon::serializer::Base& serializer) const = 0;
  virtual void deserializeState(jaffarCommon::deserializer::Base& deserializer) = 0;

  virtual std::string getCoreName() const = 0;

  virtual void setRNGValue(const uint32_t rngValue) = 0;
  virtual void setLooseTileSound(const uint16_t looseTileSound) = 0;
  virtual void initializeCopyProtection() = 0;
  virtual void updateRenderer(const size_t stepId, const jaffar::input_t &input) = 0;

  protected:

  virtual void enableRendering(SDL_Window* window) = 0;
  virtual void disableRendering() = 0;
  virtual jaffarCommon::hash::hash_t getStateHash() const = 0;
  virtual void printInfo() const = 0;
  virtual void advanceStateImpl(const jaffar::input_t &input) = 0;


  // Storage for the light state size
  size_t _stateSize;

  // Flag to determine whether to enable/disable rendering
  bool _doRendering = true;

  std::string _sdlPopRootPath;
  std::string _levelsFilePath;
  std::string _gameVersion;

  private:

  // Input parser instance
  std::unique_ptr<jaffar::InputParser> _inputParser;
};
