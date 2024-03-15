#pragma once

#include "jaffarCommon/serializers/base.hpp"
#include "jaffarCommon/deserializers/base.hpp"
#include "jaffarCommon/logger.hpp"
#include "controller.hpp"

class SDLPoPInstanceBase
{
  public:

  SDLPoPInstanceBase() = default;
  virtual ~SDLPoPInstanceBase() = default;

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

  private:

  // Controller class for input parsing
  Controller _controller;
};
