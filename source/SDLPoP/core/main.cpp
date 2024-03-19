/*
SDLPoP, a port/conversion of the DOS game Prince of Persia.
Copyright (C) 2013-2020  Dávid Nagy

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

The authors of this program may be contacted at https://forum.princed.org
*/

#include <filesystem>
#include <vector>
#include <jaffarCommon/serializers/base.hpp>
#include <jaffarCommon/deserializers/base.hpp>
#include <jaffarCommon/hash.hpp>
#include <jaffarCommon/logger.hpp>
#include "../../controller.hpp"
#include "config.h"
#include "common.h"
#include "data.h"
#include "proto.h"
#include "types.h"

extern bool found_exe_dir;
extern char levels_file[POP_MAX_PATH];
extern dat_type * dathandle;
extern char exe_dir[POP_MAX_PATH];
extern byte* level_var_palettes;
extern bool enableSDL2Rendering;

SDL_Surface* _downSurface;
SDL_Surface* _upSurface;
SDL_Surface* _leftSurface;
SDL_Surface* _rightSurface;
SDL_Surface* _shiftSurface;
SDL_Surface* _restartSurface;
SDL_Surface* _down2Surface;
SDL_Surface* _up2Surface;
SDL_Surface* _left2Surface;
SDL_Surface* _right2Surface;
SDL_Surface* _shift2Surface;
SDL_Surface* _restart2Surface;

	enum __SDLPoP_ItemType
	{
			HASHABLE,
			NON_HASHABLE,
	};

	struct __SDLPoP_Item
	{
			void *ptr;
			size_t size;
			__SDLPoP_ItemType type;
	};
	
	  template <class T>
  void __SDLPoP_AddItem(std::vector<__SDLPoP_Item> *dest, T &val, __SDLPoP_ItemType type)
  {
    dest->push_back({&val, sizeof(val), type});
  }

	std::vector<__SDLPoP_Item> __SDLPoP_items;

	char __SDLPoP_quick_control[9] = "........";
	float __SDLPoP_replay_curr_tick = 0.0;


std::vector<__SDLPoP_Item> GenerateItemsMap()
 {
   std::vector<__SDLPoP_Item> dest;
   __SDLPoP_AddItem(&dest, __SDLPoP_quick_control,        HASHABLE); 
   __SDLPoP_AddItem(&dest, level,                NON_HASHABLE);
   __SDLPoP_AddItem(&dest, checkpoint,           HASHABLE);
   __SDLPoP_AddItem(&dest, upside_down,          HASHABLE);
   __SDLPoP_AddItem(&dest, drawn_room,           HASHABLE);
   __SDLPoP_AddItem(&dest, current_level,        HASHABLE);
   __SDLPoP_AddItem(&dest, next_level,           HASHABLE);
   __SDLPoP_AddItem(&dest, mobs_count,           HASHABLE);
   __SDLPoP_AddItem(&dest, mobs,                 HASHABLE);
   __SDLPoP_AddItem(&dest, trobs_count,          HASHABLE);
   __SDLPoP_AddItem(&dest, trobs,                HASHABLE);
   __SDLPoP_AddItem(&dest, leveldoor_open,       HASHABLE);
   __SDLPoP_AddItem(&dest, Kid,                  HASHABLE);
   __SDLPoP_AddItem(&dest, hitp_curr,            HASHABLE);
   __SDLPoP_AddItem(&dest, hitp_max,             HASHABLE);
   __SDLPoP_AddItem(&dest, hitp_beg_lev,         HASHABLE);
   __SDLPoP_AddItem(&dest, grab_timer,           HASHABLE);
   __SDLPoP_AddItem(&dest, holding_sword,        HASHABLE);
   __SDLPoP_AddItem(&dest, united_with_shadow,   HASHABLE);
   __SDLPoP_AddItem(&dest, have_sword,           HASHABLE);
   __SDLPoP_AddItem(&dest, kid_sword_strike,     HASHABLE);
   __SDLPoP_AddItem(&dest, pickup_obj_type,      NON_HASHABLE);
   __SDLPoP_AddItem(&dest, offguard,             HASHABLE);
   __SDLPoP_AddItem(&dest, Guard,                HASHABLE);
   __SDLPoP_AddItem(&dest, Char,                 NON_HASHABLE);
   __SDLPoP_AddItem(&dest, Opp,                  NON_HASHABLE);
   __SDLPoP_AddItem(&dest, guardhp_curr,         HASHABLE);
   __SDLPoP_AddItem(&dest, guardhp_max,          HASHABLE);
   __SDLPoP_AddItem(&dest, demo_index,           NON_HASHABLE);
   __SDLPoP_AddItem(&dest, demo_time,            NON_HASHABLE);
   __SDLPoP_AddItem(&dest, curr_guard_color,     NON_HASHABLE);
   __SDLPoP_AddItem(&dest, guard_notice_timer,   HASHABLE);
   __SDLPoP_AddItem(&dest, guard_skill,          HASHABLE);
   __SDLPoP_AddItem(&dest, shadow_initialized,   HASHABLE);
   __SDLPoP_AddItem(&dest, guard_refrac,         HASHABLE);
   __SDLPoP_AddItem(&dest, justblocked,          HASHABLE);
   __SDLPoP_AddItem(&dest, droppedout,           HASHABLE);
   __SDLPoP_AddItem(&dest, curr_row_coll_room,   HASHABLE);
   __SDLPoP_AddItem(&dest, curr_row_coll_flags,  HASHABLE);
   __SDLPoP_AddItem(&dest, below_row_coll_room,  HASHABLE);
   __SDLPoP_AddItem(&dest, below_row_coll_flags, HASHABLE);
   __SDLPoP_AddItem(&dest, above_row_coll_room,  HASHABLE);
   __SDLPoP_AddItem(&dest, above_row_coll_flags, HASHABLE);
   __SDLPoP_AddItem(&dest, prev_collision_row,   HASHABLE);
   __SDLPoP_AddItem(&dest, flash_color,          NON_HASHABLE);
   __SDLPoP_AddItem(&dest, flash_time,           NON_HASHABLE);
   __SDLPoP_AddItem(&dest, need_level1_music,    HASHABLE);
   __SDLPoP_AddItem(&dest, is_screaming,         HASHABLE);
   __SDLPoP_AddItem(&dest, is_feather_fall,      HASHABLE);
   __SDLPoP_AddItem(&dest, last_loose_sound,     HASHABLE);
   __SDLPoP_AddItem(&dest, random_seed,          HASHABLE);
   __SDLPoP_AddItem(&dest, rem_min,              NON_HASHABLE);
   __SDLPoP_AddItem(&dest, rem_tick,             NON_HASHABLE);
   __SDLPoP_AddItem(&dest, control_x,            NON_HASHABLE);
   __SDLPoP_AddItem(&dest, control_y,            NON_HASHABLE);
   __SDLPoP_AddItem(&dest, control_shift,        NON_HASHABLE);
   __SDLPoP_AddItem(&dest, control_forward,      NON_HASHABLE);
   __SDLPoP_AddItem(&dest, control_backward,     NON_HASHABLE);
   __SDLPoP_AddItem(&dest, control_up,           NON_HASHABLE);
   __SDLPoP_AddItem(&dest, control_down,         NON_HASHABLE);
   __SDLPoP_AddItem(&dest, control_shift2,       NON_HASHABLE);
   __SDLPoP_AddItem(&dest, ctrl1_forward,        NON_HASHABLE);
   __SDLPoP_AddItem(&dest, ctrl1_backward,       NON_HASHABLE);
   __SDLPoP_AddItem(&dest, ctrl1_up,             NON_HASHABLE);
   __SDLPoP_AddItem(&dest, ctrl1_down,           NON_HASHABLE);
   __SDLPoP_AddItem(&dest, ctrl1_shift2,         NON_HASHABLE);
   __SDLPoP_AddItem(&dest, exit_room_timer,      HASHABLE);
   __SDLPoP_AddItem(&dest, __SDLPoP_replay_curr_tick,     HASHABLE);
   __SDLPoP_AddItem(&dest, is_guard_notice,      HASHABLE);
   __SDLPoP_AddItem(&dest, can_guard_see_kid,    HASHABLE);
   return dest;
 }

  void __SDLPoP_startLevel(const word level)
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

	void __SDLPoP_initialize(const char* sdlPopRootPath, const char* levelsFilePath, int gameVersion) 
	{
    version = gameVersion;

						// Initializing items map
			__SDLPoP_items = GenerateItemsMap();

		// Initializing game
		found_exe_dir = false;
		if (std::filesystem::exists(sdlPopRootPath))
		{
				sprintf(exe_dir, "%s", sdlPopRootPath);
				found_exe_dir = true;
		}

		if (found_exe_dir == false)
		{
				fprintf(stderr, "[ERROR] Could not find the root folder for  Please set the SDLPOP_ROOT environment variable to the path where SDLPop is installed.\n");
				exit(-1);
		}

    std::string overlayPath = sdlPopRootPath + std::string("/overlay");
    std::string imagePath;

    imagePath = overlayPath + std::string("/down.png");
    _downSurface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/up.png");
    _upSurface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/left.png");
    _leftSurface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/right.png");
    _rightSurface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/shift.png");
    _shiftSurface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/restart.png");
    _restartSurface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/down2.png");
    _down2Surface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/up2.png");
    _up2Surface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/left2.png");
    _left2Surface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/right2.png");
    _right2Surface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/shift2.png");
    _shift2Surface = IMG_Load(imagePath.c_str());

    imagePath = overlayPath + std::string("/restart2.png");
    _restart2Surface = IMG_Load(imagePath.c_str());

		// Setting levels.dat path
		sprintf(levels_file, "%s", levelsFilePath);

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
		__SDLPoP_startLevel(1);
		need_level1_music = custom->intro_music_time_initial;
	}

	void __SDLPoP_updateRenderer(uint32_t currentStep, const SDLPoP::Controller::input_t input) 
	{
		 auto tmp = curr_guard_color;
		 if (current_level != 3) curr_guard_color = 1;
			restore_room_after_quick_load();

		 // Calculating timing
			size_t curMins = currentStep / 720;
			size_t curSecs = (currentStep % 720) / 12;
			size_t curMilliSecs = floor((double)(currentStep % 12) / 0.012);

			char IGTText[512];
			sprintf(IGTText, "IGT %2lu:%02lu.%03lu", curMins, curSecs, curMilliSecs);
	  //  sprintf(IGTText, "Cutscene: %02u / %04u", gameState.currentCutsceneDelay, gameState.cumulativeCutsceneDelay);
			display_text_bottom(IGTText);

			draw_game_frame();

      SDL_Surface* downSurface = _downSurface;
      SDL_Surface* upSurface = _upSurface;
      SDL_Surface* leftSurface = _leftSurface;
      SDL_Surface* rightSurface = _rightSurface;
      SDL_Surface* shiftSurface = _shiftSurface;
      SDL_Surface* restartSurface = _restartSurface;

      if (input.down == true)  downSurface = _down2Surface;
      if (input.up == true) upSurface = _up2Surface;
      if (input.left == true) leftSurface = _left2Surface;
      if (input.right == true)  rightSurface = _right2Surface;
      if (input.shift == true) shiftSurface = _shift2Surface;
      if (input.restart == true) restartSurface = _restart2Surface;

      draw_image_transp_vga(downSurface, 280, 170);
      draw_image_transp_vga(upSurface, 280, 150);
      draw_image_transp_vga(leftSurface, 260, 170);
      draw_image_transp_vga(rightSurface, 300, 170);
      draw_image_transp_vga(shiftSurface, 260, 150);
      draw_image_transp_vga(restartSurface, 300, 150);

			update_screen();

			if (Kid.sword == sword_2_drawn) set_timer_length(timer_1, 5);
			else set_timer_length(timer_1, 4);
			do_simple_wait(timer_1);

			SDL_RenderClear(renderer_);
			SDL_RenderCopy(renderer_, target_texture, NULL, NULL);
			SDL_RenderPresent(renderer_);
			curr_guard_color = tmp;
	}

	  void __SDLPoP_advanceState(const SDLPoP::Controller::input_t input)
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
      __SDLPoP_startLevel(current_level);
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

		void __SDLPoP_enableRendering() { enableSDL2Rendering = true; };
  void __SDLPoP_disableRendering() { enableSDL2Rendering = false; };

  #ifdef NCURSES
    #define log printw
  #else
    #define log printf
  #endif

		void __SDLPoP_printInfo()
		{
      log("[]    + Current/Next Level:   %2d / %2d\n", current_level, next_level);
      log("[]    + [Kid]                 HP: %d/%d, Alive: %d\n", int(hitp_curr), int(hitp_max), int(Kid.alive));
      log("[]    + [Kid]                 Room: %d, Pos.x: %3d, Pos.y: %3d, Frame: %3d, Action: %2d, Dir: %d\n", int(Kid.room), int(Kid.x), int(Kid.y), int(Kid.frame), int(Kid.action), int(Kid.direction));
      log("[]    + [Guard]               Room: %d, Pos.x: %3d, Pos.y: %3d, Frame: %3d, Action: %2d, Color: %3u, Dir: %d, HP: %d/%d, Alive: %d\n", int(Guard.room), int(Guard.x), int(Guard.y), int(Guard.frame), int(Guard.action), int(curr_guard_color), int(Guard.direction), int(guardhp_curr), int(guardhp_max), int(Guard.alive));
      log("[]    + Exit Room Timer:      %d\n", exit_room_timer);
      log("[]    + Kid Has Sword:        %d\n", have_sword);
      log("[]    + Last Tile Loost Sound: %u\n", last_loose_sound);
      log("[]    + RNG: 0x%X\n", random_seed);
		}

	 void __SDLPoP_setRNGValue(const uint32_t rngValue) { random_seed = rngValue;}
  void __SDLPoP_initializeCopyProtection() { init_copyprot(); }
		void __SDLPoP_serializeState(jaffarCommon::serializer::Base& serializer)
		{
     for (const auto &item : __SDLPoP_items)  serializer.push(item.ptr, item.size);
		}

		void __SDLPoP_deserializeState(jaffarCommon::deserializer::Base& deserializer)
  {
    for (const auto &item : __SDLPoP_items)  deserializer.pop(item.ptr, item.size);

    different_room = 1;
    // Show the room where the prince is, even if the player moved the view away
    // from it (with the H,J,U,N keys).
    next_room = drawn_room = Kid.room;
    load_room_links();
  }

		size_t __SDLPoP_getFullStateSize()
		{
				size_t stateSize = 0;
				for (const auto &item : __SDLPoP_items) stateSize += item.size;
				return stateSize;
		}
   
		jaffarCommon::hash::hash_t  __SDLPoP_getStateHash()
  {
    // for (size_t i = 0; i < __SDLPoP_items.size(); i++)
    //  if (__SDLPoP_items[i].type == HASHABLE)
    //  printf("__SDLPoP_Item %lu, Hash: %s\n", i, jaffarCommon::hash::hashToString(jaffarCommon::hash::calculateMetroHash(__SDLPoP_items[i].ptr, __SDLPoP_items[i].size)).c_str());

    MetroHash128 hash;
    for (const auto &item : __SDLPoP_items) if (item.type == HASHABLE) hash.Update(item.ptr, item.size);
    jaffarCommon::hash::hash_t result;
    hash.Finalize(reinterpret_cast<uint8_t *>(&result));
    return result;
  }

		void __SDLPoP_setLooseTileSound(const uint16_t looseTileSound)
  {
    last_loose_sound = looseTileSound;
  }