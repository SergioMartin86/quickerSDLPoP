#pragma once

#include "core/miniPoP.hpp"
#include "../sdlpopInstanceBase.hpp"

class QuickerSDLPoP final : public QuickerSDLPoPBase
{
  public:

  void serializeState(jaffarCommon::serializer::Base& serializer) const override { _nes.serializeState(serializer); }
  void deserializeState(jaffarCommon::deserializer::Base& deserializer) override { _nes.deserializeState(deserializer); }

  std::string getCoreName() const override { return "QuickerSDLPoP"; }
  
  void doSoftReset() override { _nes.reset(false); }
  void doHardReset() override { _nes.reset(true); }
  
  void *getInternalEmulatorPointer() override { return &_nes; }
  
  inline size_t getFullStateSize() const override
  {
    jaffarCommon::serializer::Contiguous serializer;
    serializeState(serializer);
    return serializer.getOutputSize();
  }

  inline size_t getDifferentialStateSize() const override
  {
    jaffarCommon::serializer::Differential serializer;
    serializeState(serializer);
    return serializer.getOutputSize();
  }

  protected:

  void enableStateBlockImpl(const std::string& block) override { _nes.enableStateBlock(block); };
  void disableStateBlockImpl(const std::string& block) override { _nes.disableStateBlock(block); };
  void advanceStateImpl(const Controller::port_t controller1, const Controller::port_t controller2) override
  {
    if (_doRendering == true) _nes.emulate_frame(controller1, controller2);
    if (_doRendering == false) _nes.emulate_skip_frame(controller1, controller2);
  }
};
