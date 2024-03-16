#pragma once

#include "jaffarCommon/serializers/base.hpp"
#include "jaffarCommon/deserializers/base.hpp"
#include "../sdlpopInstanceBase.hpp"

class SDLPoPInstance final : public SDLPoPInstanceBase
{
  public:
  SDLPoPInstance(const nlohmann::json& config) : SDLPoPInstanceBase(config)  {  }

   __INLINE__ void initialize() override
   {
    
   }

  void serializeState(jaffarCommon::serializer::Base& serializer) const override
  {
  }

  void deserializeState(jaffarCommon::deserializer::Base& deserializer) override
  {
  }

  __INLINE__ size_t getFullStateSize() const { return 0; }
  __INLINE__ size_t getDifferentialStateSize() const override { return getFullStateSize(); }

  std::string getCoreName() const override { return "SDLPoP"; }

  void setRNGValue(const uint32_t rngValue) override
  {
  }

  void setLooseTileSound(const uint16_t looseTileSound) override
  {
  }

  void initializeCopyProtection() override
  {
  }
  
  protected:

  __INLINE__ void advanceStateImpl(const Controller::input_t input) override
  {
  }
};
