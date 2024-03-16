#pragma once

#include "jaffarCommon/serializers/base.hpp"
#include "jaffarCommon/deserializers/base.hpp"
#include "../sdlpopInstanceBase.hpp"
#include <filesystem>
#include "core/config.h"
#include "core/common.h"
#include "core/data.h"
#include "core/proto.h"
#include "core/types.h"

extern bool found_exe_dir;
extern char levels_file[POP_MAX_PATH];
extern dat_type * dathandle;
extern char exe_dir[POP_MAX_PATH];
extern byte* level_var_palettes;
extern bool enableSDL2Rendering;

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
    // Checking if rendering is enabled
    enableSDL2Rendering = _doRendering;

    // Initializing game
    found_exe_dir = false;
    if (std::filesystem::exists(_sdlPopRootPath.c_str()))
    {
      sprintf(exe_dir, "%s", _sdlPopRootPath.c_str());
      found_exe_dir = true;
    }
    if (found_exe_dir == false)  JAFFAR_THROW_LOGIC("[ERROR] Could not find the root folder (%s) for SDLPoP\n", _sdlPopRootPath.c_str());


    if (found_exe_dir == false)
    {
      fprintf(stderr, "[ERROR] Could not find the root folder for  Please set the SDLPOP_ROOT environment variable to the path where SDLPop is installed.\n");
      exit(-1);
    }

    // Setting levels.dat path
    sprintf(levels_file, "%s", _levelsFilePath.c_str());

    // Setting argument config
    is_validate_mode = byte(0);
    g_argc = 0;
    g_argv = NULL;

    fixes->fix_quicksave_during_feather = 1;
    fixes->fix_quicksave_during_lvl1_music = 1;

    // Game initialization
    prandom(1);


    // debug only: check that the sequence table deobfuscation did not mess things up
    load_global_options();
    check_mod_param();
    turn_sound_on_off(1);
    load_mod_options();

    // CusPop option
    is_blind_mode = 0;
    enable_quicksave_penalty = 0;

    // Fix bug: with start_in_blind_mode enabled, moving objects are not displayed
    // until blind mode is toggled off+on??
    need_drects = 1;

    apply_seqtbl_patches();
    dathandle = open_dat("PRINCE.DAT", 0);

    /*video_mode =*/
    parse_grmode();

    init_timer(BASE_FPS);
    parse_cmdline_sound();

    set_hc_pal();

    current_target_surface = rect_sthg(onscreen_surface_, &screen_rect);

    show_loading();
    set_joy_mode();

    cheats_enabled = 0;
    draw_mode = 0;
    demo_mode = 0;

    //init_copyprot_dialog();

    play_demo_level = 0;


    //////////////////////////////////////////////
    // init_game_main

    doorlink1_ad = /*&*/ level.doorlinks1;
    doorlink2_ad = /*&*/ level.doorlinks2;
    guard_palettes = (byte *)load_from_opendats_alloc(10, "bin", NULL, NULL);

    // (blood, hurt flash) #E00030 = red
    set_pal(12, 0x38, 0x00, 0x0C, 1);

    // (palace wall pattern) #C09850 = light brown
    set_pal(6, 0x30, 0x26, 0x14, 0);

    // Level color variations (1.3)
    level_var_palettes = reinterpret_cast<byte *>(load_from_opendats_alloc(20, "bin", NULL, NULL));

    // PRINCE.DAT: sword
    chtab_addrs[id_chtab_0_sword] = load_sprites_from_file(700, 1 << 2, 1);

    // PRINCE.DAT: flame, sword on floor, potion
    chtab_addrs[id_chtab_1_flameswordpotion] = load_sprites_from_file(150, 1 << 3, 1);

    close_dat(dathandle);
    load_all_sounds();
    hof_read();

    ///////////////////////////////////////////////////
    // start_game

    release_title_images(); // added
    free_optsnd_chtab();    // added
    start_level = 1;

    ///////////////////////////////////////////////////////////////
    // init_game

    offscreen_surface = make_offscreen_buffer(&rect_top);

    text_time_remaining = 0;
    text_time_total = 0;
    is_show_time = 1;
    checkpoint = 0;
    upside_down = 0; // N.B. upside_down is also reset in set_start_pos()
    resurrect_time = 0;
    rem_min = custom->start_minutes_left; // 60
    rem_tick = custom->start_ticks_left;  // 719
    hitp_beg_lev = custom->start_hitp;    // 3
    current_level = 0;
    startLevel(1);
    need_level1_music = custom->intro_music_time_initial;
   }

  void startLevel(const word level)
  {
    ///////////////////////////////////////////////////////////////
    // play_level
    if (level != current_level) load_lev_spr(level);

    load_kid_sprite();
    load_level();
    pos_guards();
    clear_coll_rooms();
    clear_saved_ctrl();

    drawn_room = 0;
    mobs_count = 0;
    trobs_count = 0;
    next_sound = -1;
    holding_sword = 0;
    grab_timer = 0;
    can_guard_see_kid = 0;
    united_with_shadow = 0;
    leveldoor_open = 0;
    demo_index = 0;
    demo_time = 0;
    guardhp_curr = 0;
    hitp_delta = 0;
    Guard.charid = charid_2_guard;
    Guard.direction = dir_56_none;
    do_startpos();

    // (level_number != 1)
    have_sword = (level == 0 || level >= custom->have_sword_from_level);

    find_start_level_door();

    if (need_level1_music != 0 && current_level == custom->intro_music_level)
      need_level1_music = custom->intro_music_time_restart;
  }
  
  __INLINE__ void printInfo() const override
  {
      printf("[]  + Kid Room: %u\n", Kid.room);
      printf("[]  + Kid X: %u\n", Kid.x);
      printf("[]  + Kid y: %u\n", Kid.y);
      printf("[]  + Last Tile Loost Sound: %u\n", last_loose_sound);
      printf("[]  + RNG: 0x%X\n", random_seed);
  }

  char quick_control[9] = "........";
  float replay_curr_tick = 0.0;

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
   AddItem(&dest, quick_control,        HASHABLE);
   AddItem(&dest, level,                NON_HASHABLE);
   AddItem(&dest, checkpoint,           HASHABLE);
   AddItem(&dest, upside_down,          HASHABLE);
   AddItem(&dest, drawn_room,           HASHABLE);
   AddItem(&dest, current_level,        HASHABLE);
   AddItem(&dest, next_level,           HASHABLE);
   AddItem(&dest, mobs_count,           HASHABLE);
   AddItem(&dest, mobs,                 HASHABLE);
   AddItem(&dest, trobs_count,          HASHABLE);
   AddItem(&dest, trobs,                HASHABLE);
   AddItem(&dest, leveldoor_open,       HASHABLE);
   AddItem(&dest, Kid,                  HASHABLE);
   AddItem(&dest, hitp_curr,            HASHABLE);
   AddItem(&dest, hitp_max,             HASHABLE);
   AddItem(&dest, hitp_beg_lev,         HASHABLE);
   AddItem(&dest, grab_timer,           HASHABLE);
   AddItem(&dest, holding_sword,        HASHABLE);
   AddItem(&dest, united_with_shadow,   HASHABLE);
   AddItem(&dest, have_sword,           HASHABLE);
   AddItem(&dest, kid_sword_strike,     HASHABLE);
   AddItem(&dest, pickup_obj_type,      HASHABLE);
   AddItem(&dest, offguard,             HASHABLE);
   AddItem(&dest, Guard,                HASHABLE);
   AddItem(&dest, Char,                 NON_HASHABLE);
   AddItem(&dest, Opp,                  NON_HASHABLE);
   AddItem(&dest, guardhp_curr,         HASHABLE);
   AddItem(&dest, guardhp_max,          HASHABLE);
   AddItem(&dest, demo_index,           NON_HASHABLE);
   AddItem(&dest, demo_time,            NON_HASHABLE);
   AddItem(&dest, curr_guard_color,     NON_HASHABLE);
   AddItem(&dest, guard_notice_timer,   HASHABLE);
   AddItem(&dest, guard_skill,          HASHABLE);
   AddItem(&dest, shadow_initialized,   HASHABLE);
   AddItem(&dest, guard_refrac,         HASHABLE);
   AddItem(&dest, justblocked,          HASHABLE);
   AddItem(&dest, droppedout,           HASHABLE);
   AddItem(&dest, curr_row_coll_room,   HASHABLE);
   AddItem(&dest, curr_row_coll_flags,  HASHABLE);
   AddItem(&dest, below_row_coll_room,  HASHABLE);
   AddItem(&dest, below_row_coll_flags, HASHABLE);
   AddItem(&dest, above_row_coll_room,  HASHABLE);
   AddItem(&dest, above_row_coll_flags, HASHABLE);
   AddItem(&dest, prev_collision_row,   HASHABLE);
   AddItem(&dest, flash_color,          HASHABLE);
   AddItem(&dest, flash_time,           HASHABLE);
   AddItem(&dest, need_level1_music,    HASHABLE);
   AddItem(&dest, is_screaming,         HASHABLE);
   AddItem(&dest, is_feather_fall,      HASHABLE);
   AddItem(&dest, last_loose_sound,     HASHABLE);
   AddItem(&dest, random_seed,          HASHABLE);
   AddItem(&dest, rem_min,              NON_HASHABLE);
   AddItem(&dest, rem_tick,             NON_HASHABLE);
   AddItem(&dest, control_x,            NON_HASHABLE);
   AddItem(&dest, control_y,            NON_HASHABLE);
   AddItem(&dest, control_shift,        NON_HASHABLE);
   AddItem(&dest, control_forward,      NON_HASHABLE);
   AddItem(&dest, control_backward,     NON_HASHABLE);
   AddItem(&dest, control_up,           NON_HASHABLE);
   AddItem(&dest, control_down,         NON_HASHABLE);
   AddItem(&dest, control_shift2,       NON_HASHABLE);
   AddItem(&dest, ctrl1_forward,        NON_HASHABLE);
   AddItem(&dest, ctrl1_backward,       NON_HASHABLE);
   AddItem(&dest, ctrl1_up,             NON_HASHABLE);
   AddItem(&dest, ctrl1_down,           NON_HASHABLE);
   AddItem(&dest, ctrl1_shift2,         NON_HASHABLE);
   AddItem(&dest, exit_room_timer,      HASHABLE);
   AddItem(&dest, replay_curr_tick,     HASHABLE);
   AddItem(&dest, is_guard_notice,      HASHABLE);
   AddItem(&dest, can_guard_see_kid,    HASHABLE);
   return dest;
 }

  void serializeState(jaffarCommon::serializer::Base& serializer) const override
  {
    for (const auto &item : _items)  serializer.push(item.ptr, item.size);
  }

  void deserializeState(jaffarCommon::deserializer::Base& deserializer) override
  {
    for (const auto &item : _items)  deserializer.pop(item.ptr, item.size);

    different_room = 1;
    // Show the room where the prince is, even if the player moved the view away
    // from it (with the H,J,U,N keys).
    next_room = drawn_room = Kid.room;
    load_room_links();
  }

  __INLINE__ size_t getFullStateSize() const
   {
     size_t stateSize = 0;
     for (const auto &item : _items) stateSize += item.size;
     return stateSize;
   }
   
  __INLINE__ size_t getDifferentialStateSize() const override { return getFullStateSize(); }

  std::string getCoreName() const override { return "SDLPoP"; }

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
    random_seed = rngValue;
  }

  void setLooseTileSound(const uint16_t looseTileSound) override
  {
    last_loose_sound = looseTileSound;
  }

  void initializeCopyProtection() override
  {
    init_copyprot();
  }

  jaffarCommon::hash::hash_t getStateHash() const override
  {
    // for (size_t i = 0; i < _items.size(); i++)
    //  if (_items[i].type == HASHABLE)
    //  printf("Item %lu, Hash: %s\n", i, jaffarCommon::hash::hashToString(jaffarCommon::hash::calculateMetroHash(_items[i].ptr, _items[i].size)).c_str());

    MetroHash128 hash;
    for (const auto &item : _items) if (item.type == HASHABLE) hash.Update(item.ptr, item.size);
    jaffarCommon::hash::hash_t result;
    hash.Finalize(reinterpret_cast<uint8_t *>(&result));
    return result;
  }
  
  __INLINE__ void advanceStateImpl(const Controller::input_t input) override
  {
    key_states[SDL_SCANCODE_UP] = input.up;
    key_states[SDL_SCANCODE_DOWN] = input.down;
    key_states[SDL_SCANCODE_LEFT] = input.left;
    key_states[SDL_SCANCODE_RIGHT] = input.right;
    key_states[SDL_SCANCODE_RSHIFT] = input.shift;
    is_restart_level = input.restart;

    if (is_restart_level == 0 || (is_restart_level == 1 && current_level == 3))
    {
      guardhp_delta = 0;
      hitp_delta = 0;
      timers();
      play_frame();
    }

    if (current_level == 1 && next_level == 2) next_level = 15;
    if (current_level == 15 && next_level == 16) next_level = 2;
    if (current_level != 15 && next_level != 15) rem_tick--;

    if (rem_tick == 0)
    {
      rem_tick = 720;
      rem_min--;
    }

    if (is_restart_level == 1)
    {
      startLevel(current_level);
      draw_level_first();
      is_restart_level = 0;
    }

    // if we're on lvl 4, check mirror
    if (current_level == 4)
    {
      if (jumped_through_mirror == -1) Guard.x = 245;
      check_mirror();
    }
  }

  private: 

  std::vector<Item> _items;
  
};
