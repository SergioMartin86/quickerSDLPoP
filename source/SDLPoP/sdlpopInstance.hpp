#pragma once

#include "jaffarCommon/serializers/base.hpp"
#include "jaffarCommon/deserializers/base.hpp"
#include "../sdlpopInstanceBase.hpp"

class SDLPoPInstance final : public SDLPoPInstanceBase
{
  public:
  SDLPoPInstance() : SDLPoPInstanceBase()
  {
  }

  void serializeState(jaffarCommon::serializer::Base& serializer) const override
  {
  }

  void deserializeState(jaffarCommon::deserializer::Base& deserializer) override
  {
  }

  inline size_t getDifferentialStateSize() const override { return getFullStateSize(); }

  std::string getCoreName() const override { return "SDLPoP"; }

  protected:

  void advanceStateImpl(const Controller::port_t controller1, const Controller::port_t controller2) override
  {
  }
};
