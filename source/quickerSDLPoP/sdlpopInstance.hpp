#pragma once

#include "core/miniPoP.hpp"
#include "../sdlpopInstanceBase.hpp"
#include <filesystem>

class SDLPoPInstance final : public SDLPoPInstanceBase
{
  public:

   SDLPoPInstance(const nlohmann::json& config) : SDLPoPInstanceBase(config)  {  }

   __INLINE__ void initialize() override
   {
    // If not found, looking for the SDLPOP_ROOT env variable
    found_exe_dir = false;
    if (std::filesystem::exists(_sdlPopRootPath.c_str()))
    {
      sprintf(exe_dir, "%s", _sdlPopRootPath.c_str());
      found_exe_dir = true;
    }
    if (found_exe_dir == false)  JAFFAR_THROW_LOGIC("[ERROR] Could not find the root folder (%s) for SDLPoP\n", _sdlPopRootPath.c_str());
    
   }

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
