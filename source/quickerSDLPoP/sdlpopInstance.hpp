#pragma once

#include <filesystem>
#include "core/miniPoP.hpp"
#include "../sdlpopInstanceBase.hpp"


class SDLPoPInstance final : public SDLPoPInstanceBase
{
  public:

   SDLPoPInstance(const nlohmann::json& config) : SDLPoPInstanceBase(config)
   {
    // Initializing items map
    _items = GenerateItemsMap();
   }

    __INLINE__ void initialize() override
    {
      found_exe_dir = false;
      if (std::filesystem::exists(_sdlPopRootPath.c_str()))
      {
        sprintf(exe_dir, "%s", _sdlPopRootPath.c_str());
        found_exe_dir = true;
      }
      if (found_exe_dir == false)  JAFFAR_THROW_LOGIC("[ERROR] Could not find the root folder (%s) for SDLPoP\n", _sdlPopRootPath.c_str());

      // Setting levels.dat path
      sprintf(levels_file, "%s", _levelsFilePath.c_str());

      // Game initialization
      prandom(1);

      // Setting argument config
      is_validate_mode = true;
      g_argc = 1;

      // Fix bug: with start_in_blind_mode enabled, moving objects are not displayed
      // until blind mode is toggled off+on??
      need_drects = 1;

      dathandle = open_dat("PRINCE.DAT", 0);

      parse_cmdline_sound();

      //////////////////////////////////////////////
      // init_game_main

      doorlink1_ad = /*&*/ gameState.level.doorlinks1;
      doorlink2_ad = /*&*/ gameState.level.doorlinks2;
      guard_palettes = (byte *)load_from_opendats_alloc(10, "bin", NULL, NULL);
      
      // Level color variations (1.3)
      level_var_palettes = reinterpret_cast<byte *>(load_from_opendats_alloc(20, "bin", NULL, NULL));

      // PRINCE.DAT: sword
      chtab_addrs[id_chtab_0_sword] = load_sprites_from_file(700, 1 << 2, 1);

      // PRINCE.DAT: flame, sword on floor, potion
      chtab_addrs[id_chtab_1_flameswordpotion] = load_sprites_from_file(150, 1 << 3, 1);
      close_dat(dathandle);

      // start_game

      start_level = 1;

      ///////////////////////////////////////////////////////////////
      // init_game

      text_time_remaining = 0;
      is_show_time = 1;
      gameState.checkpoint = 0;
      resurrect_time = 0;
      gameState.hitp_beg_lev = custom->start_hitp;    // 3
      gameState.current_level = 0;
      startLevel(1);
      gameState.need_level1_music = custom->intro_music_time_initial;
    }

    static uint32_t advanceRNGState(const dword randomSeed)
    {
      return randomSeed * 214013 + 2531011;
    }

    static uint32_t reverseRNGState(const uint32_t randomSeed)
    {
      return (randomSeed + 4292436285) * 3115528533;
    }

    void setRNGValue(const uint32_t rngValue) override
    {
      gameState.random_seed = rngValue;
    }

    void setLooseTileSound(const uint16_t looseTileSound) override
    {
      gameState.last_loose_sound = looseTileSound;
    }

    void initializeCopyProtection() override
    {
      init_copyprot();
    }

    void startLevel(const word level)
    {
      ///////////////////////////////////////////////////////////////
      // play_level
      if (level != gameState.current_level) load_lev_spr(level);

      load_kid_sprite();
      load_level();
      pos_guards();
      clear_coll_rooms();
      clear_saved_ctrl();

      gameState.drawn_room = 0;
      gameState.mobs_count = 0;
      gameState.trobs_count = 0;
      next_sound = -1;
      gameState.holding_sword = 0;
      gameState.grab_timer = 0;
      gameState.can_guard_see_kid = 0;
      gameState.united_with_shadow = 0;
      gameState.leveldoor_open = 0;
      gameState.demo_index = 0;
      gameState.demo_time = 0;
      gameState.guardhp_curr = 0;
      hitp_delta = 0;
      gameState.Guard.charid = charid_2_guard;
      gameState.Guard.direction = dir_56_none;
      do_startpos();

      // (level_number != 1)
      gameState.have_sword = (level == 0 || level >= custom->have_sword_from_level);

      find_start_level_door();

      if (gameState.need_level1_music != 0 && gameState.current_level == custom->intro_music_level)
        gameState.need_level1_music = custom->intro_music_time_restart;
    }

    __INLINE__ void serializeState(jaffarCommon::serializer::Base& serializer) const override
    {
      serializer.push(&gameState, sizeof(gameState));
    }

    __INLINE__ void deserializeState(jaffarCommon::deserializer::Base& deserializer) override
    {
      deserializer.pop(&gameState, sizeof(gameState));

      next_room = gameState.drawn_room = gameState.Kid.room;
      load_room_links();
    }

    std::string getCoreName() const override { return "QuickerSDLPoP"; }
  
  
    __INLINE__ size_t getFullStateSize() const override
    {
      return sizeof(gameState);
    }

    __INLINE__ size_t getDifferentialStateSize() const override
    {
      // The entire state is differentiable, and no forced contiguous blocks are inside, so return zero
      return 0;
    }

    __INLINE__ void printInfo() const override
    {
       printf("[]  + Kid Room: %u\n", gameState.Kid.room);
       printf("[]  + Kid X: %u\n", gameState.Kid.x);
       printf("[]  + Kid y: %u\n", gameState.Kid.y);
       printf("[]  + Last Tile Loost Sound: %u\n", gameState.last_loose_sound);
       printf("[]  + RNG: 0x%X\n", gameState.random_seed);
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
   AddItem(&dest, gameState.quick_control,        HASHABLE);
   AddItem(&dest, gameState.level,                NON_HASHABLE);
   AddItem(&dest, gameState.checkpoint,           HASHABLE);
   AddItem(&dest, gameState.upside_down,          HASHABLE);
   AddItem(&dest, gameState.drawn_room,           HASHABLE);
   AddItem(&dest, gameState.current_level,        HASHABLE);
   AddItem(&dest, gameState.next_level,           HASHABLE);
   AddItem(&dest, gameState.mobs_count,           HASHABLE);
   AddItem(&dest, gameState.mobs,                 HASHABLE);
   AddItem(&dest, gameState.trobs_count,          HASHABLE);
   AddItem(&dest, gameState.trobs,                HASHABLE);
   AddItem(&dest, gameState.leveldoor_open,       HASHABLE);
   AddItem(&dest, gameState.Kid,                  HASHABLE);
   AddItem(&dest, gameState.hitp_curr,            HASHABLE);
   AddItem(&dest, gameState.hitp_max,             HASHABLE);
   AddItem(&dest, gameState.hitp_beg_lev,         HASHABLE);
   AddItem(&dest, gameState.grab_timer,           HASHABLE);
   AddItem(&dest, gameState.holding_sword,        HASHABLE);
   AddItem(&dest, gameState.united_with_shadow,   HASHABLE);
   AddItem(&dest, gameState.have_sword,           HASHABLE);
   AddItem(&dest, gameState.kid_sword_strike,     HASHABLE);
   AddItem(&dest, gameState.pickup_obj_type,      HASHABLE);
   AddItem(&dest, gameState.offguard,             HASHABLE);
   AddItem(&dest, gameState.Guard,                HASHABLE);
   AddItem(&dest, gameState.Char,                 NON_HASHABLE);
   AddItem(&dest, gameState.Opp,                  NON_HASHABLE);
   AddItem(&dest, gameState.guardhp_curr,         HASHABLE);
   AddItem(&dest, gameState.guardhp_max,          HASHABLE);
   AddItem(&dest, gameState.demo_index,           NON_HASHABLE);
   AddItem(&dest, gameState.demo_time,            NON_HASHABLE);
   AddItem(&dest, gameState.curr_guard_color,     NON_HASHABLE);
   AddItem(&dest, gameState.guard_notice_timer,   HASHABLE);
   AddItem(&dest, gameState.guard_skill,          HASHABLE);
   AddItem(&dest, gameState.shadow_initialized,   HASHABLE);
   AddItem(&dest, gameState.guard_refrac,         HASHABLE);
   AddItem(&dest, gameState.justblocked,          HASHABLE);
   AddItem(&dest, gameState.droppedout,           HASHABLE);
   AddItem(&dest, gameState.curr_row_coll_room,   HASHABLE);
   AddItem(&dest, gameState.curr_row_coll_flags,  HASHABLE);
   AddItem(&dest, gameState.below_row_coll_room,  HASHABLE);
   AddItem(&dest, gameState.below_row_coll_flags, HASHABLE);
   AddItem(&dest, gameState.above_row_coll_room,  HASHABLE);
   AddItem(&dest, gameState.above_row_coll_flags, HASHABLE);
   AddItem(&dest, gameState.prev_collision_row,   HASHABLE);
   AddItem(&dest, gameState.flash_color,          HASHABLE);
   AddItem(&dest, gameState.flash_time,           HASHABLE);
   AddItem(&dest, gameState.need_level1_music,    HASHABLE);
   AddItem(&dest, gameState.is_screaming,         HASHABLE);
   AddItem(&dest, gameState.is_feather_fall,      HASHABLE);
   AddItem(&dest, gameState.last_loose_sound,     HASHABLE);
   AddItem(&dest, gameState.random_seed,          HASHABLE);
   AddItem(&dest, gameState.rem_min,              NON_HASHABLE);
   AddItem(&dest, gameState.rem_tick,             NON_HASHABLE);
   AddItem(&dest, gameState.control_x,            NON_HASHABLE);
   AddItem(&dest, gameState.control_y,            NON_HASHABLE);
   AddItem(&dest, gameState.control_shift,        NON_HASHABLE);
   AddItem(&dest, gameState.control_forward,      NON_HASHABLE);
   AddItem(&dest, gameState.control_backward,     NON_HASHABLE);
   AddItem(&dest, gameState.control_up,           NON_HASHABLE);
   AddItem(&dest, gameState.control_down,         NON_HASHABLE);
   AddItem(&dest, gameState.control_shift2,       NON_HASHABLE);
   AddItem(&dest, gameState.ctrl1_forward,        NON_HASHABLE);
   AddItem(&dest, gameState.ctrl1_backward,       NON_HASHABLE);
   AddItem(&dest, gameState.ctrl1_up,             NON_HASHABLE);
   AddItem(&dest, gameState.ctrl1_down,           NON_HASHABLE);
   AddItem(&dest, gameState.ctrl1_shift2,         NON_HASHABLE);
   AddItem(&dest, gameState.exit_room_timer,      HASHABLE);
   AddItem(&dest, gameState.replay_curr_tick,     HASHABLE);
   AddItem(&dest, gameState.is_guard_notice,      HASHABLE);
   AddItem(&dest, gameState.can_guard_see_kid,    HASHABLE);
   return dest;
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
    key_states[SDL_SCANCODE_UP] = input.up;
    key_states[SDL_SCANCODE_DOWN] = input.down;
    key_states[SDL_SCANCODE_LEFT] = input.left;
    key_states[SDL_SCANCODE_RIGHT] = input.right;
    key_states[SDL_SCANCODE_RSHIFT] = input.shift;
    is_restart_level = input.restart;

    if (is_restart_level == 0 || (is_restart_level == 1 && gameState.current_level == 3))
    {
      guardhp_delta = 0;
      hitp_delta = 0;
      timers();
      play_frame();
    }

    if (gameState.current_level == 1 && gameState.next_level == 2) gameState.next_level = 15;
    if (gameState.current_level == 15 && gameState.next_level == 16) gameState.next_level = 2;
    if (gameState.current_level != 15 && gameState.next_level != 15) gameState.rem_tick--;

    if (gameState.rem_tick == 0)
    {
      gameState.rem_tick = 720;
      gameState.rem_min--;
    }

    if (is_restart_level == 1)
    {
      startLevel(gameState.current_level);
      draw_level_first();
      is_restart_level = 0;
    }

    // if we're on lvl 4, check mirror
    if (gameState.current_level == 4)
    {
      if (gameState.jumped_through_mirror == -1) gameState.Guard.x = 245;
      check_mirror();
    }
  }

  private: 

  std::vector<Item> _items;
};
