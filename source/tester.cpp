#include <argparse/argparse.hpp>
#include <jaffarCommon/json.hpp>
#include <jaffarCommon/exceptions.hpp>
#include <jaffarCommon/serializers/contiguous.hpp>
#include <jaffarCommon/serializers/differential.hpp>
#include <jaffarCommon/deserializers/contiguous.hpp>
#include <jaffarCommon/deserializers/differential.hpp>
#include <jaffarCommon/hash.hpp>
#include <jaffarCommon/string.hpp>
#include <jaffarCommon/file.hpp>
#include "sdlpopInstance.hpp"
#include <chrono>
#include <sstream>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
  // Parsing command line arguments
  argparse::ArgumentParser program("tester", "1.0");

  program.add_argument("scriptFile")
    .help("Path to the test script file to run.")
    .required();

  program.add_argument("--cycleType")
    .help("Specifies the emulation actions to be performed per each input. Possible values: 'Simple': performs only advance state, 'Rerecord': performs load/advance/save, and 'Full': performs load/advance/save/advance.")
    .default_value(std::string("Simple"));

  program.add_argument("--hashOutputFile")
    .help("Path to write the hash output to.")
    .default_value(std::string(""));

  // Try to parse arguments
  try
  {
    program.parse_args(argc, argv);
  }
  catch (const std::runtime_error &err)
  {
    JAFFAR_THROW_LOGIC("%s\n%s", err.what(), program.help().str().c_str());
  }

  // Getting test script file path
  std::string scriptFilePath = program.get<std::string>("scriptFile");

  // Getting path where to save the hash output (if any)
  std::string hashOutputFile = program.get<std::string>("--hashOutputFile");

  // Getting reproduce flag
  std::string cycleType = program.get<std::string>("--cycleType");

  // Loading script file
  std::string scriptJsRaw;
  if (jaffarCommon::file::loadStringFromFile(scriptJsRaw, scriptFilePath) == false) JAFFAR_THROW_LOGIC("Could not find/read script file: %s\n", scriptFilePath.c_str());

  // Parsing script
  const auto scriptJs = nlohmann::json::parse(scriptJsRaw);

  // Getting initial state file path
  std::string stateFilePath = jaffarCommon::json::getString(scriptJs, "Initial State File");

  // Getting sequence file path
  std::string sequenceFilePath = jaffarCommon::json::getString(scriptJs, "Sequence File");

  // Getting differential compression configuration
  const auto& differentialCompressionJs = jaffarCommon::json::getObject(scriptJs, "Differential Compression");
  const auto differentialCompressionEnabled = jaffarCommon::json::getBoolean(differentialCompressionJs, "Enabled");
  const auto differentialCompressionMaxDifferences = jaffarCommon::json::getNumber<size_t>(differentialCompressionJs, "Max Differences"); 
  const auto differentialCompressionUseZlib = jaffarCommon::json::getBoolean(differentialCompressionJs, "Use Zlib"); 

  auto overrideRNGEnabled = jaffarCommon::json::getBoolean(scriptJs, "Override RNG Enabled");
  auto overrideRNGValue = jaffarCommon::json::getNumber<uint32_t>(scriptJs, "Override RNG Value");
  auto overrideLooseTileSoundEnabled = jaffarCommon::json::getBoolean(scriptJs, "Override Loose Tile Sound Enabled");
  auto overrideLooseTileSoundValue = jaffarCommon::json::getNumber<uint32_t>(scriptJs, "Override Loose Tile Sound Value");
  auto initializeCopyProtection = jaffarCommon::json::getBoolean(scriptJs, "Initialize Copy Protection");

  // Getting SDLPoP configuration
  const auto& SDLPoPConfigJs = jaffarCommon::json::getObject(scriptJs, "SDLPoP Configuration");

  // Creating emulator instance
  SDLPoPInstance e(SDLPoPConfigJs);

  // Disabling rendering
  e.disableRendering();

  // Initializing emulator instance
  e.initialize();

  // If an initial state is provided, load it now
  std::string stateFileData;
  if (jaffarCommon::file::loadStringFromFile(stateFileData, stateFilePath) == false) JAFFAR_THROW_LOGIC("Could not initial state file: %s\n", stateFilePath.c_str());
  jaffarCommon::deserializer::Contiguous d(stateFileData.data());
  e.deserializeState(d);
  
  // Check if RNG elements need overriding
  if (overrideRNGEnabled) e.setRNGValue(overrideRNGValue);
  if (overrideLooseTileSoundEnabled) e.setLooseTileSound(overrideLooseTileSoundValue);

  // Check if copy protection needs initializing
  if (initializeCopyProtection) e.initializeCopyProtection();

  // Disable rendering
  e.disableRendering();

  // Getting full state size
  const auto stateSize = e.getFullStateSize();

  // Getting differential state size
  const auto fixedDiferentialStateSize = e.getDifferentialStateSize();
  const auto fullDifferentialStateSize = fixedDiferentialStateSize + differentialCompressionMaxDifferences;

  // Loading sequence file
  std::string sequenceRaw;
  if (jaffarCommon::file::loadStringFromFile(sequenceRaw, sequenceFilePath) == false) JAFFAR_THROW_LOGIC("[ERROR] Could not find or read from input sequence file: %s\n", sequenceFilePath.c_str());

  // Building sequence information
  const auto sequence = jaffarCommon::string::split(sequenceRaw, ' ');

  // Getting sequence lenght
  const auto sequenceLength = sequence.size();

  // Getting emulation core name
  std::string emulationCoreName = e.getCoreName();

  // Getting intiial state hash
  auto initialHashString = jaffarCommon::hash::hashToString(e.getStateHash());

  // Printing test information
  printf("[] -----------------------------------------\n");
  printf("[] Running Script:                         '%s'\n", scriptFilePath.c_str());
  printf("[] Cycle Type:                             '%s'\n", cycleType.c_str());
  printf("[] Emulation Core:                         '%s'\n", emulationCoreName.c_str());
  printf("[] Sequence File:                          '%s'\n", sequenceFilePath.c_str());
  printf("[] Sequence Length:                        %lu\n", sequenceLength);
  printf("[] State Size:                             %lu bytes\n", stateSize);
  printf("[] Initial State Hash:                     %s\n", initialHashString.c_str());
  printf("[] Use Differential Compression:           %s\n", differentialCompressionEnabled ? "true" : "false");
  if (differentialCompressionEnabled == true) 
  { 
  printf("[]   + Max Differences:                    %lu\n", differentialCompressionMaxDifferences);    
  printf("[]   + Use Zlib:                           %s\n", differentialCompressionUseZlib ? "true" : "false");
  printf("[]   + Fixed Diff State Size:              %lu\n", fixedDiferentialStateSize);
  printf("[]   + Full Diff State Size:               %lu\n", fullDifferentialStateSize);
  }
  printf("[] ********** Running Test **********\n");

  fflush(stdout);

  // Serializing initial state
  auto currentState = (uint8_t *)malloc(stateSize);
  {
    jaffarCommon::serializer::Contiguous cs(currentState);
    e.serializeState(cs);
  }

  // Serializing differential state data (in case it's used)
  uint8_t *differentialStateData = nullptr;
  size_t differentialStateMaxSizeDetected = 0;

  // Allocating memory for differential data and performing the first serialization
  if (differentialCompressionEnabled == true) 
  {
    differentialStateData = (uint8_t *)malloc(fullDifferentialStateSize);
    auto s = jaffarCommon::serializer::Differential(differentialStateData, fullDifferentialStateSize, currentState, stateSize, differentialCompressionUseZlib);
    e.serializeState(s);
    differentialStateMaxSizeDetected = s.getOutputSize();
  }

  // Check whether to perform each action
  bool doPreAdvance = cycleType == "Full";
  bool doDeserialize = cycleType == "Rerecord" || cycleType == "Full";
  bool doSerialize = cycleType == "Rerecord" || cycleType == "Full";

  // Actually running the sequence
  auto t0 = std::chrono::high_resolution_clock::now();
  for (const std::string &input : sequence)
  {
    if (doPreAdvance == true)
    {
      e.advanceState(input);
    } 
    
    if (doDeserialize == true)
    {
      if (differentialCompressionEnabled == true) 
      {
       jaffarCommon::deserializer::Differential d(differentialStateData, fullDifferentialStateSize, currentState, stateSize, differentialCompressionUseZlib);
       e.deserializeState(d);
      }

      if (differentialCompressionEnabled == false)
      {
        jaffarCommon::deserializer::Contiguous d(currentState, stateSize);
        e.deserializeState(d);
      } 
    } 
    
    e.advanceState(input);

    if (doSerialize == true)
    {
      if (differentialCompressionEnabled == true)
      {
        auto s = jaffarCommon::serializer::Differential(differentialStateData, fullDifferentialStateSize, currentState, stateSize, differentialCompressionUseZlib);
        e.serializeState(s);
        differentialStateMaxSizeDetected = std::max(differentialStateMaxSizeDetected, s.getOutputSize());
      }  

      if (differentialCompressionEnabled == false) 
      {
        auto s = jaffarCommon::serializer::Contiguous(currentState, stateSize);
        e.serializeState(s);
      }
    } 
  }
  auto tf = std::chrono::high_resolution_clock::now();

  // Calculating running time
  auto dt = std::chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();
  double elapsedTimeSeconds = (double)dt * 1.0e-9;

  // Creating hash string
  auto hashString = jaffarCommon::hash::hashToString(e.getStateHash());

  // Printing time information
  printf("[] Elapsed time:                           %3.3fs (%lu ns)\n", (double)dt * 1.0e-9, dt);
  printf("[] Performance:                            %.3f inputs / s\n", (double)sequenceLength / elapsedTimeSeconds);
  printf("[] Final State Hash:                       %s\n", hashString.c_str());
  if (differentialCompressionEnabled == true)
  {
  printf("[] Differential State Max Size Detected:   %lu\n", differentialStateMaxSizeDetected);    
  }
  printf("[] Game Info: \n");
  e.printInfo();

  // If saving hash, do it now
  if (hashOutputFile != "") jaffarCommon::file::saveStringToFile(hashString, hashOutputFile.c_str());

  // If reached this point, everything ran ok
  return 0;
}
