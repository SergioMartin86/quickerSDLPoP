#pragma once

#include "core/miniPoP.hpp"
#include "../sdlpopInstanceBase.hpp"

class SDLPoPInstance final : public SDLPoPInstanceBase
{
  public:

  __INLINE__ void serializeState(jaffarCommon::serializer::Base& serializer) const override {  }
  __INLINE__ void deserializeState(jaffarCommon::deserializer::Base& deserializer) override {  }

  std::string getCoreName() const override { return "QuickerSDLPoP"; }
  
  __INLINE__ size_t getFullStateSize() const override
  {
    return 0;
  }

  __INLINE__ size_t getDifferentialStateSize() const override
  {
    return 0;
  }

  protected:

  __INLINE__ void advanceStateImpl(const Controller::input_t input) override
  {
  }
};
