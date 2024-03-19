#pragma once

#include <filesystem>
#include "core/miniPoP.hpp"
#include "../sdlpopInstanceBase.hpp"
#include <jaffarCommon/logger.hpp>
#include <jaffarCommon/serializers/contiguous.hpp>
#include <jaffarCommon/deserializers/contiguous.hpp>

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

   void enableRendering() override
   {
     __SDLPoP_enableRendering(); 
     __SDLPoP_initialize(_sdlPopRootPath.c_str(), _levelsFilePath.c_str()); 
   };

   void disableRendering() override { };

   SDLPoPInstance(const nlohmann::json& config) : SDLPoPInstanceBase(config)
   {
    // Initializing items map
    _items = GenerateItemsMap();
   }

    __INLINE__ void initialize() override
    {
      _emu.initialize(_sdlPopRootPath, _levelsFilePath, _gameVersion);
    }

    static uint32_t advanceRNGState(const uint32_t randomSeed)
    {
      return randomSeed * 214013 + 2531011;
    }

    static uint32_t reverseRNGState(const uint32_t randomSeed)
    {
      return (randomSeed + 4292436285) * 3115528533;
    }

    void setRNGValue(const uint32_t rngValue) override
    {
      _emu.gameState.random_seed = rngValue;
    }

    void setLooseTileSound(const uint16_t looseTileSound) override
    {
      _emu.gameState.last_loose_sound = looseTileSound;
    }

    void initializeCopyProtection() override
    {
      _emu.init_copyprot();
    }

    __INLINE__ void serializeState(jaffarCommon::serializer::Base& serializer) const override
    {
      serializer.push(&_emu.gameState, sizeof(_emu.gameState));
    }

    __INLINE__ void deserializeState(jaffarCommon::deserializer::Base& deserializer) override
    {
      deserializer.pop(&_emu.gameState, sizeof(_emu.gameState));

      _emu.next_room = _emu.gameState.drawn_room = _emu.gameState.Kid.room;
      _emu.load_room_links();
    }

    std::string getCoreName() const override { return "QuickerSDLPoP"; }
  
  
    __INLINE__ size_t getFullStateSize() const override
    {
      return sizeof(_emu.gameState);
    }

    __INLINE__ size_t getDifferentialStateSize() const override
    {
      // The entire state is differentiable, and no forced contiguous blocks are inside, so return zero
      return 0;
    }

    __INLINE__ void printInfo() const override
    {
      jaffarCommon::logger::log("[]    + Current/Next Level:   %2d / %2d\n", _emu.gameState.current_level, _emu.gameState.next_level);
      jaffarCommon::logger::log("[]    + [Kid]                 HP: %d/%d, Alive: %d\n", int(_emu.gameState.hitp_curr), int(_emu.gameState.hitp_max), int(_emu.gameState.Kid.alive));
      jaffarCommon::logger::log("[]    + [Kid]                 Room: %d, Pos.x: %3d, Pos.y: %3d, Frame: %3d, Action: %2d, Dir: %d\n", int(_emu.gameState.Kid.room), int(_emu.gameState.Kid.x), int(_emu.gameState.Kid.y), int(_emu.gameState.Kid.frame), int(_emu.gameState.Kid.action), int(_emu.gameState.Kid.direction));
      jaffarCommon::logger::log("[]    + [Guard]               Room: %d, Pos.x: %3d, Pos.y: %3d, Frame: %3d, Action: %2d, Color: %3u, Dir: %d, HP: %d/%d, Alive: %d\n", int(_emu.gameState.Guard.room), int(_emu.gameState.Guard.x), int(_emu.gameState.Guard.y), int(_emu.gameState.Guard.frame), int(_emu.gameState.Guard.action), int(_emu.gameState.curr_guard_color), int(_emu.gameState.Guard.direction), int(_emu.gameState.guardhp_curr), int(_emu.gameState.guardhp_max), int(_emu.gameState.Guard.alive));
      jaffarCommon::logger::log("[]    + Exit Room Timer:      %d\n", _emu.gameState.exit_room_timer);
      jaffarCommon::logger::log("[]    + Kid Has Sword:        %d\n", _emu.gameState.have_sword);
      jaffarCommon::logger::log("[]    + Last Tile Loost Sound: %u\n", _emu.gameState.last_loose_sound);
      jaffarCommon::logger::log("[]    + RNG: 0x%X\n", _emu.gameState.random_seed);
      jaffarCommon::logger::log("[]    + Current Step: %u\n", _emu.gameState.currentStep);
    }

      enum ItemType
  {
    HASHABLE,
    NON_HASHABLE,
  };

  struct Item
  {
    void *ptr;
    size_t size;
    ItemType type;
  };

  template <class T>
  void AddItem(std::vector<Item> *dest, T &val, ItemType type)
  {
    dest->push_back({&val, sizeof(val), type});
  }

 std::vector<Item> GenerateItemsMap()
 {
   std::vector<Item> dest;
   AddItem(&dest, _emu.gameState.quick_control,        HASHABLE);
   AddItem(&dest, _emu.gameState.level,                NON_HASHABLE);
   AddItem(&dest, _emu.gameState.checkpoint,           HASHABLE);
   AddItem(&dest, _emu.gameState.upside_down,          HASHABLE);
   AddItem(&dest, _emu.gameState.drawn_room,           HASHABLE);
   AddItem(&dest, _emu.gameState.current_level,        HASHABLE);
   AddItem(&dest, _emu.gameState.next_level,           HASHABLE);
   AddItem(&dest, _emu.gameState.mobs_count,           HASHABLE);
   AddItem(&dest, _emu.gameState.mobs,                 HASHABLE);
   AddItem(&dest, _emu.gameState.trobs_count,          HASHABLE);
   AddItem(&dest, _emu.gameState.trobs,                HASHABLE);
   AddItem(&dest, _emu.gameState.leveldoor_open,       HASHABLE);
   AddItem(&dest, _emu.gameState.Kid,                  HASHABLE);
   AddItem(&dest, _emu.gameState.hitp_curr,            HASHABLE);
   AddItem(&dest, _emu.gameState.hitp_max,             HASHABLE);
   AddItem(&dest, _emu.gameState.hitp_beg_lev,         HASHABLE);
   AddItem(&dest, _emu.gameState.grab_timer,           HASHABLE);
   AddItem(&dest, _emu.gameState.holding_sword,        HASHABLE);
   AddItem(&dest, _emu.gameState.united_with_shadow,   HASHABLE);
   AddItem(&dest, _emu.gameState.have_sword,           HASHABLE);
   AddItem(&dest, _emu.gameState.kid_sword_strike,     HASHABLE);
   AddItem(&dest, _emu.gameState.pickup_obj_type,      NON_HASHABLE);
   AddItem(&dest, _emu.gameState.offguard,             HASHABLE);
   AddItem(&dest, _emu.gameState.Guard,                HASHABLE);
   AddItem(&dest, _emu.gameState.Char,                 NON_HASHABLE);
   AddItem(&dest, _emu.gameState.Opp,                  NON_HASHABLE);
   AddItem(&dest, _emu.gameState.guardhp_curr,         HASHABLE);
   AddItem(&dest, _emu.gameState.guardhp_max,          HASHABLE);
   AddItem(&dest, _emu.gameState.demo_index,           NON_HASHABLE);
   AddItem(&dest, _emu.gameState.demo_time,            NON_HASHABLE);
   AddItem(&dest, _emu.gameState.curr_guard_color,     NON_HASHABLE);
   AddItem(&dest, _emu.gameState.guard_notice_timer,   HASHABLE);
   AddItem(&dest, _emu.gameState.guard_skill,          HASHABLE);
   AddItem(&dest, _emu.gameState.shadow_initialized,   HASHABLE);
   AddItem(&dest, _emu.gameState.guard_refrac,         HASHABLE);
   AddItem(&dest, _emu.gameState.justblocked,          HASHABLE);
   AddItem(&dest, _emu.gameState.droppedout,           HASHABLE);
   AddItem(&dest, _emu.gameState.curr_row_coll_room,   HASHABLE);
   AddItem(&dest, _emu.gameState.curr_row_coll_flags,  HASHABLE);
   AddItem(&dest, _emu.gameState.below_row_coll_room,  HASHABLE);
   AddItem(&dest, _emu.gameState.below_row_coll_flags, HASHABLE);
   AddItem(&dest, _emu.gameState.above_row_coll_room,  HASHABLE);
   AddItem(&dest, _emu.gameState.above_row_coll_flags, HASHABLE);
   AddItem(&dest, _emu.gameState.prev_collision_row,   HASHABLE);
   AddItem(&dest, _emu.gameState.flash_color,          NON_HASHABLE);
   AddItem(&dest, _emu.gameState.flash_time,           NON_HASHABLE);
   AddItem(&dest, _emu.gameState.need_level1_music,    HASHABLE);
   AddItem(&dest, _emu.gameState.is_screaming,         HASHABLE);
   AddItem(&dest, _emu.gameState.is_feather_fall,      HASHABLE);
   AddItem(&dest, _emu.gameState.last_loose_sound,     HASHABLE);
   AddItem(&dest, _emu.gameState.random_seed,          HASHABLE);
   AddItem(&dest, _emu.gameState.rem_min,              NON_HASHABLE);
   AddItem(&dest, _emu.gameState.rem_tick,             NON_HASHABLE);
   AddItem(&dest, _emu.gameState.control_x,            NON_HASHABLE);
   AddItem(&dest, _emu.gameState.control_y,            NON_HASHABLE);
   AddItem(&dest, _emu.gameState.control_shift,        NON_HASHABLE);
   AddItem(&dest, _emu.gameState.control_forward,      NON_HASHABLE);
   AddItem(&dest, _emu.gameState.control_backward,     NON_HASHABLE);
   AddItem(&dest, _emu.gameState.control_up,           NON_HASHABLE);
   AddItem(&dest, _emu.gameState.control_down,         NON_HASHABLE);
   AddItem(&dest, _emu.gameState.control_shift2,       NON_HASHABLE);
   AddItem(&dest, _emu.gameState.ctrl1_forward,        NON_HASHABLE);
   AddItem(&dest, _emu.gameState.ctrl1_backward,       NON_HASHABLE);
   AddItem(&dest, _emu.gameState.ctrl1_up,             NON_HASHABLE);
   AddItem(&dest, _emu.gameState.ctrl1_down,           NON_HASHABLE);
   AddItem(&dest, _emu.gameState.ctrl1_shift2,         NON_HASHABLE);
   AddItem(&dest, _emu.gameState.exit_room_timer,      HASHABLE);
   AddItem(&dest, _emu.gameState.replay_curr_tick,     HASHABLE);
   AddItem(&dest, _emu.gameState.is_guard_notice,      HASHABLE);
   AddItem(&dest, _emu.gameState.can_guard_see_kid,    HASHABLE);
   AddItem(&dest, _emu.gameState.currentStep,    NON_HASHABLE);
   return dest;
 }

   void updateRenderer() override
  {
    auto stateSize = getFullStateSize();
    uint8_t buffer[stateSize];
    jaffarCommon::serializer::Contiguous s(buffer, stateSize);
    serializeState(s);
    jaffarCommon::deserializer::Contiguous d(buffer, stateSize);
    __SDLPoP_deserializeState(d);
    __SDLPoP_updateRenderer(_emu.gameState.currentStep);
  }

  jaffarCommon::hash::hash_t getStateHash() const override
  {
    // for (size_t i = 0; i < _items.size(); i++)
    //  if (_items[i].type == HASHABLE)
    //   printf("Item %lu, Hash: %s\n", i, jaffarCommon::hash::hashToString(jaffarCommon::hash::calculateMetroHash(_items[i].ptr, _items[i].size)).c_str());

    MetroHash128 hash;
    for (const auto &item : _items) if (item.type == HASHABLE) hash.Update(item.ptr, item.size);
    jaffarCommon::hash::hash_t result;
    hash.Finalize(reinterpret_cast<uint8_t *>(&result));
    return result;
  }

  protected:

  __INLINE__ void advanceStateImpl(const Controller::input_t input) override
  {
    _emu.advanceState(input.up, input.down, input.left, input.right, input.shift, input.restart);
  }

  private: 

  quicker::QuickerSDLPoP _emu;
  std::vector<Item> _items;
};
