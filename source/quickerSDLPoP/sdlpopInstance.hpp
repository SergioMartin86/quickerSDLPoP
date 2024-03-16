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
      if (gameState.current_level != 3) gameState.curr_guard_color = 1;
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
};
