#pragma once

#include <string>
#include <unistd.h>
#include <SDL.h>
#include <jaffarCommon/serializers/contiguous.hpp>
#include <jaffarCommon/deserializers/contiguous.hpp>
#include <jaffarCommon/hash.hpp>
#include "sdlpopInstance.hpp"

#define _INVERSE_FRAME_RATE 16667

struct stepData_t
{
  std::string input;
  uint8_t *stateData;
  jaffarCommon::hash::hash_t hash;
};

class PlaybackInstance
{
  public:
  void addStep(const std::string &input)
  {
    stepData_t step;
    step.input = input;
    step.stateData = (uint8_t *)malloc(_emu->getFullStateSize());

    jaffarCommon::serializer::Contiguous serializer(step.stateData);
    _emu->serializeState(serializer);
    step.hash = jaffarCommon::hash::calculateMetroHash(step.stateData, _emu->getFullStateSize());

    // Adding the step into the sequence
    _stepSequence.push_back(step);
  }

  // Initializes the playback module instance
  PlaybackInstance(SDLPoPInstance *emu, const std::vector<std::string> &sequence, const std::string &overlayPath = "") : _emu(emu)
  {
    // Enabling emulation rendering
    _emu->enableRendering();

    // Building sequence information
    for (const auto &input : sequence)
    {
      // Adding new step
      addStep(input);

      // Advance state based on the input received
      _emu->advanceState(input);
    }

    // Adding last step with no input
    addStep("<End Of Sequence>");

  }

  // Function to render frame
  void renderFrame(const size_t stepId)
  {
    // Checking the required step id does not exceed contents of the sequence
    if (stepId > _stepSequence.size()) JAFFAR_THROW_LOGIC("[Error] Attempting to render a step larger than the step sequence");

    const auto stateData = getStateData(stepId);
    jaffarCommon::deserializer::Contiguous deserializer(stateData);
    _emu->deserializeState(deserializer);

    const auto stateInput = getStateInput(stepId);
    Controller controller;
    bool isInputValid = controller.parseInputString(stateInput);
    if (isInputValid == false) JAFFAR_THROW_LOGIC("Move provided cannot be parsed: '%s'\n", stateInput.c_str());
    auto input = controller.getParsedInput();

    _emu->updateRenderer(stepId, input);

  }

  size_t getSequenceLength() const
  {
    return _stepSequence.size();
  }

  const std::string getInput(const size_t stepId) const
  {
    // Checking the required step id does not exceed contents of the sequence
    if (stepId > _stepSequence.size()) JAFFAR_THROW_LOGIC("[Error] Attempting to render a step larger than the step sequence %lu > %lu", stepId, _stepSequence.size());

    // Getting step information
    const auto &step = _stepSequence[stepId];

    // Returning step input
    return step.input;
  }

  const uint8_t *getStateData(const size_t stepId) const
  {
    // Checking the required step id does not exceed contents of the sequence
    if (stepId > _stepSequence.size()) JAFFAR_THROW_LOGIC("[Error] Attempting to render a step larger than the step sequence %lu > %lu", stepId, _stepSequence.size());

    // Getting step information
    const auto &step = _stepSequence[stepId];

    // Returning step input
    return step.stateData;
  }

  const jaffarCommon::hash::hash_t getStateHash(const size_t stepId) const
  {
    // Checking the required step id does not exceed contents of the sequence
    if (stepId > _stepSequence.size()) JAFFAR_THROW_LOGIC("[Error] Attempting to render a step larger than the step sequence %lu > %lu", stepId, _stepSequence.size());

    // Getting step information
    const auto &step = _stepSequence[stepId];

    // Returning step input
    return step.hash;
  }

  const std::string getStateInput(const size_t stepId) const
  {
    // Checking the required step id does not exceed contents of the sequence
    if (stepId > _stepSequence.size()) JAFFAR_THROW_LOGIC("[Error] Attempting to render a step larger than the step sequence");

    // Getting step information
    const auto &step = _stepSequence[stepId];

    // Returning step input
    return step.input;
  }

  private:

  // Internal sequence information
  std::vector<stepData_t> _stepSequence;

  // Pointer to the contained emulator instance
  SDLPoPInstance *const _emu;

  // Flag to store whether to use the button overlay
  bool _useOverlay = false;
};
