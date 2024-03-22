#pragma once

#include <jaffarCommon/serializers/base.hpp>
#include <jaffarCommon/deserializers/base.hpp>
#include <jaffarCommon/logger.hpp>
#include "../sdlpopInstanceBase.hpp"
#include <filesystem>

extern void __SDLPoP_initialize(const char* sdlPopRootPath, const char* levelsFilePath, int gameVersion);
extern void __SDLPoP_startLevel(const uint16_t level);
extern void __SDLPoP_updateRenderer(uint32_t currentStep, const SDLPoP::Controller::input_t input);
extern void __SDLPoP_advanceState(const SDLPoP::Controller::input_t input);
extern void __SDLPoP_enableRendering(SDL_Window* window);
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

   void enableRendering(SDL_Window* window) override { __SDLPoP_enableRendering(window); };
   void disableRendering() override { __SDLPoP_disableRendering(); };
   void initialize() override 
   {
     int gameVersion;

         // Selecting game version
     bool versionRecognized = false;
     if (_gameVersion == "1.0") { gameVersion = 10; versionRecognized = true; }
     if (_gameVersion == "1.4") { gameVersion = 14; versionRecognized = true; }
     if (versionRecognized == false)  JAFFAR_THROW_LOGIC("[ERROR] Version string not recognized: '%s'\n", _gameVersion.c_str());

     __SDLPoP_initialize(_sdlPopRootPath.c_str(), _levelsFilePath.c_str(), gameVersion);
   }
   void printInfo() const override { __SDLPoP_printInfo();  }
   void advanceStateImpl(const SDLPoP::Controller::input_t input) override { __SDLPoP_advanceState(input); }
   void updateRenderer(const size_t stepId, const SDLPoP::Controller::input_t input) override { __SDLPoP_updateRenderer(stepId, input); }
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
