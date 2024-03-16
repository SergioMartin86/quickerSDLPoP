#pragma once

#include "jaffarCommon/serializers/base.hpp"
#include "jaffarCommon/deserializers/base.hpp"
#include "jaffarCommon/logger.hpp"
#include <jaffarCommon/json.hpp>
#include "controller.hpp"

class SDLPoPInstanceBase
{
  public:

  SDLPoPInstanceBase(const nlohmann::json& config)
  {
    _sdlPopRootPath = jaffarCommon::json::getString(config, "SDLPoP Root Path");
    _levelsFilePath = jaffarCommon::json::getString(config, "Levels File Path");
    _overrideRNGEnabled = jaffarCommon::json::getBoolean(config, "Override RNG Enabled");
    _overrideRNGValue = jaffarCommon::json::getNumber<uint32_t>(config, "Override RNG Value");
    _overrideLooseTileSoundEnabled = jaffarCommon::json::getBoolean(config, "Override Loose Tile Sound Enabled");
    _overrideLooseTileSound = jaffarCommon::json::getNumber<uint32_t>(config, "Override Loose Tile Sound Value");
    _initializeCopyProtection = jaffarCommon::json::getBoolean(config, "Initialize Copy Protection");
  }

  virtual ~SDLPoPInstanceBase() = default;

  virtual void initialize() = 0;

  inline void advanceState(const std::string &input)
  {
  }

  inline void enableRendering() { _doRendering = true; };
  inline void disableRendering() { _doRendering = false; };

  virtual size_t getFullStateSize() const = 0;
  virtual size_t getDifferentialStateSize() const = 0;

  // Virtual functions

  virtual void serializeState(jaffarCommon::serializer::Base& serializer) const = 0;
  virtual void deserializeState(jaffarCommon::deserializer::Base& deserializer) = 0;

  virtual std::string getCoreName() const = 0;

  protected:

  virtual void advanceStateImpl(const Controller::input_t input) = 0;

  // Storage for the light state size
  size_t _stateSize;

  // Flag to determine whether to enable/disable rendering
  bool _doRendering = true;

  std::string _sdlPopRootPath;
  std::string _levelsFilePath;

  bool _overrideRNGEnabled;
  uint32_t _overrideRNGValue;

  bool _overrideLooseTileSoundEnabled;
  uint16_t _overrideLooseTileSound;
  
  bool _initializeCopyProtection;

  private:

  // Controller class for input parsing
  Controller _controller;
};
