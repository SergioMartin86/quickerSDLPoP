#pragma once

#include <jaffarCommon/serializers/base.hpp>
#include <jaffarCommon/deserializers/base.hpp>
#include <jaffarCommon/logger.hpp>
#include "../sdlpopInstanceBase.hpp"
#include <filesystem>

extern void __SDLPoP_initialize(const char* sdlPopRootPath, const char* levelsFilePath);
extern void __SDLPoP_startLevel(const uint16_t level);
extern void __SDLPoP_updateRenderer(uint32_t currentStep);
extern void __SDLPoP_advanceState(const Controller::input_t input);
extern void __SDLPoP_enableRendering();
extern void __SDLPoP_disableRendering();
extern void __SDLPoP_printInfo();
extern void __SDLPoP_setRNGValue(const uint32_t rngValue);
extern void __SDLPoP_initializeCopyProtection();
extern void __SDLPoP_serializeState(jaffarCommon::serializer::Base& serializer);
extern void __SDLPoP_deserializeState(jaffarCommon::deserializer::Base& deserializer);
extern size_t __SDLPoP_getFullStateSize();
extern jaffarCommon::hash::hash_t __SDLPoP_getStateHash();
extern void __SDLPoP_setLooseTileSound(const uint16_t looseTileSound);

class SDLPoPInstance final : public SDLPoPInstanceBase
{
  public:
  SDLPoPInstance(const nlohmann::json& config) : SDLPoPInstanceBase(config)  { }

   void enableRendering() override { __SDLPoP_enableRendering(); };
   void disableRendering() override { __SDLPoP_disableRendering(); };
   void initialize() override { __SDLPoP_initialize(_sdlPopRootPath.c_str(), _levelsFilePath.c_str()); }
   void printInfo() const override { __SDLPoP_printInfo();  }
   void advanceStateImpl(const Controller::input_t input) override { __SDLPoP_advanceState(input); }
   void updateRenderer() override { __SDLPoP_updateRenderer(0); }
   void setRNGValue(const uint32_t rngValue) override { __SDLPoP_setRNGValue(rngValue); }
   void initializeCopyProtection() override { __SDLPoP_initializeCopyProtection(); }
   void serializeState(jaffarCommon::serializer::Base& serializer) const override { __SDLPoP_serializeState(serializer); }
   void deserializeState(jaffarCommon::deserializer::Base& deserializer) override { __SDLPoP_deserializeState(deserializer); }
   size_t getFullStateSize() const { return __SDLPoP_getFullStateSize(); }
   jaffarCommon::hash::hash_t getStateHash() const override { return __SDLPoP_getStateHash(); }
   void setLooseTileSound(const uint16_t looseTileSound) override { __SDLPoP_setLooseTileSound(looseTileSound); } 
   __INLINE__ size_t getDifferentialStateSize() const override { return getFullStateSize(); }
   std::string getCoreName() const override { return "SDLPoP"; }
};
