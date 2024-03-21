/*
quickerSDLPoP, a barebones thread-safe version of SDLPop for routing
Copyright (C) 2021 Sergio Martin

based on

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

#pragma once

#include "const.h"
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace quicker
{

class QuickerSDLPoP
{

public:

__attribute__((aligned(1024)))
sdlPopState_t gameState;

enum gameVersion_t 
{
  v10,
  v14
};

// Extracted values
gameVersion_t version;
int8_t control_x;
int8_t control_y;
int8_t control_shift;
int8_t control_forward;
int8_t control_backward;
int8_t control_up;
int8_t control_down;
int8_t control_shift2;
char_type Opp;
uint16_t flash_color;
uint16_t flash_time;
uint16_t upside_down;
custom_options_type *custom = &custom_defaults;
uint8_t is_validate_mode;
uint16_t text_time_remaining;
uint16_t text_time_total;
uint16_t is_show_time;
uint16_t resurrect_time;
uint16_t dont_reset_time;
uint8_t sound_flags = 0;
uint16_t draw_mode;
int16_t start_level = -1;
uint8_t *guard_palettes;
chtab_type *chtab_addrs[10];
uint16_t copyprot_plac;
uint16_t copyprot_idx;
uint16_t cplevel_entr[14];
dialog_type *copyprot_dialog;
rect_type dialog_rect_1 = {60, 56, 124, 264};
rect_type dialog_rect_2 = {61, 56, 120, 264};
uint8_t curr_tile;
uint8_t curr_modifier;
tile_and_mod leftroom_[3];
tile_and_mod row_below_left_[10];
uint8_t *curr_room_tiles;
uint8_t *curr_room_modif;
uint16_t draw_xh;
uint8_t graphics_mode = 0;
uint16_t room_L;
uint16_t room_R;
uint16_t room_A;
uint16_t room_B;
uint16_t room_BR;
uint16_t room_BL;
uint16_t room_AR;
uint16_t room_AL;
int16_t table_counts[5];
int16_t drects_count;
int16_t peels_count;
back_table_type foretable[200];
back_table_type backtable[200];
midtable_type midtable[50];
peel_type *peels_table[50];
rect_type drects[30];
int8_t obj_direction;
int16_t obj_clip_left;
int16_t obj_clip_top;
int16_t obj_clip_right;
int16_t obj_clip_bottom;
wipetable_type wipetable[300];
uint16_t need_drects;
uint16_t leveldoor_right;
uint16_t leveldoor_ybottom;
uint8_t palace_wall_colors[44 * 3];
uint16_t seed_was_init = 0;
uint8_t *doorlink2_ad;
uint8_t *doorlink1_ad;
uint16_t is_paused;
uint16_t is_restart_level;
uint8_t sound_mode = 0;
uint8_t is_sound_on = 0x0F;
int16_t guardhp_delta;
uint16_t next_room;
int16_t hitp_delta;
uint16_t need_quotes;
int16_t roomleave_result;
sound_buffer_type *sound_pointers[58];
chtab_type *chtab_title40;
chtab_type *chtab_title50;
int16_t hof_count;
uint16_t demo_mode = 0;
int16_t next_sound;
int16_t knock;
uint8_t wipe_frames[30];
int8_t wipe_heights[30];
uint8_t redraw_frames_anim[30];
uint8_t redraw_frames2[30];
uint8_t redraw_frames_floor_overlay[30];
uint8_t redraw_frames_full[30];
uint8_t redraw_frames_fore[30];
uint8_t tile_object_redraw[30];
uint8_t redraw_frames_above[10];
uint16_t need_full_redraw;
int16_t n_curr_objs;
objtable_type objtable[50];
int16_t curr_objs[50];
uint8_t obj_xh;
uint8_t obj_xl;
uint8_t obj_y;
uint8_t obj_chtab;
uint8_t obj_id;
uint8_t obj_tilepos;
int16_t obj_x;
frame_type cur_frame;
uint16_t seamless;
trob_type trob;
int16_t redraw_height;
uint8_t curr_tilepos;
int16_t curr_room;
mob_type curmob;
int16_t tile_col;

bool _upPressed;
bool _downPressed;
bool _rightPressed;
bool _leftPressed;
bool _shiftPressed;

int16_t char_col_right;
int16_t char_col_left;
int16_t char_top_row;
int16_t prev_char_top_row;
int16_t prev_char_col_right;
int16_t prev_char_col_left;
int16_t char_bottom_row;
uint8_t curr_tile2;
int16_t tile_row;
uint16_t char_width_half;
uint16_t char_height;
int16_t char_x_left;
int16_t char_x_left_coll;
int16_t char_x_right_coll;
int16_t char_x_right;
int16_t char_top_y;
uint8_t fall_frame;
uint8_t through_tile;
int8_t infrontx; // name from Apple II source
uint16_t current_sound;
uint8_t edge_type;
char **sound_names;
int g_argc;
int last_key_scancode;
uint16_t curmob_index;
dat_type *dathandle;
uint16_t need_redraw_because_flipped;
uint8_t *level_var_palettes;
uint16_t first_start = 1;
int8_t distance_mirror;
int8_t bump_col_left_of_wall;
int8_t bump_col_right_of_wall;
int8_t right_checked_col;
int8_t left_checked_col;
int16_t coll_tile_left_xpos;
uint16_t curr_tile_temp;
char exe_dir[__QS_POP_MAX_PATH] = ".";
bool found_exe_dir = false;
uint16_t which_quote;
dat_type *dat_chain_ptr = NULL;
char last_text_input;
int16_t drawn_row;
int16_t draw_bottom_y;
int16_t draw_main_y;
int16_t drawn_col;
uint8_t tile_left;
uint8_t modifier_left;
char levels_file[__QS_POP_MAX_PATH];
uint8_t obj2_tilepos;
uint16_t obj2_x;
uint8_t obj2_y;
int8_t obj2_direction;
uint8_t obj2_id;
uint8_t obj2_chtab;
int16_t obj2_clip_top;
int16_t obj2_clip_bottom;
int16_t obj2_clip_left;
int16_t obj2_clip_right;
uint16_t copyprot_room[14] = {3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
uint8_t sound_interruptible[58] = {
  0, // sound_0_fell_to_death
  1, // sound_1_falling
  1, // sound_2_tile_crashing
  1, // sound_3_button_pressed
  1, // sound_4_gate_closing
  1, // sound_5_gate_opening
  0, // sound_6_gate_closing_fast
  1, // sound_7_gate_stop
  1, // sound_8_bumped
  1, // sound_9_grab
  1, // sound_10_sword_vs_sword
  1, // sound_11_sword_moving
  1, // sound_12_guard_hurt
  1, // sound_13_kid_hurt
  0, // sound_14_leveldoor_closing
  0, // sound_15_leveldoor_sliding
  1, // sound_16_medium_land
  1, // sound_17_soft_land
  0, // sound_18_drink
  1, // sound_19_draw_sword
  1, // sound_20_loose_shake_1
  1, // sound_21_loose_shake_2
  1, // sound_22_loose_shake_3
  1, // sound_23_footstep
  0, // sound_24_death_regular
  0, // sound_25_presentation
  0, // sound_26_embrace
  0, // sound_27_cutscene_2_4_6_12
  0, // sound_28_death_in_fight
  1, // sound_29_meet_Jaffar
  0, // sound_30_big_potion
  0, // sound_31
  0, // sound_32_shadow_music
  0, // sound_33_small_potion
  0, // sound_34
  0, // sound_35_cutscene_8_9
  0, // sound_36_out_of_time
  0, // sound_37_victory
  0, // sound_38_blink
  0, // sound_39_low_weight
  0, // sound_40_cutscene_12_short_time
  0, // sound_41_end_level_music
  0, // sound_42
  0, // sound_43_victory_Jaffar
  0, // sound_44_skel_alive
  0, // sound_45_jump_through_mirror
  0, // sound_46_chomped
  1, // sound_47_chomper
  0, // sound_48_spiked
  0, // sound_49_spikes
  0, // sound_50_story_2_princess
  0, // sound_51_princess_door_opening
  0, // sound_52_story_4_Jaffar_leaves
  0, // sound_53_story_3_Jaffar_comes
  0, // sound_54_intro_music
  0, // sound_55_story_1_absence
  0, // sound_56_ending_music
  0};

 __INLINE__ void  initialize(const std::string& sdlpopDir, const std::string& levelsPath, const std::string& versionString)
 {
     // Selecting game version
     bool versionRecognized = false;
     if (versionString == "1.0") { version = gameVersion_t::v10; versionRecognized = true; }
     if (versionString == "1.4") { version = gameVersion_t::v14; versionRecognized = true; }
     if (versionRecognized == false)  JAFFAR_THROW_LOGIC("[ERROR] Version string not recognized: '%s'\n", versionString.c_str());

     found_exe_dir = false;
      if (std::filesystem::exists(sdlpopDir.c_str()))
      {
        sprintf(exe_dir, "%s", sdlpopDir.c_str());
        found_exe_dir = true;
      }
      if (found_exe_dir == false)  JAFFAR_THROW_LOGIC("[ERROR] Could not find the root folder (%s) for SDLPoP\n", sdlpopDir.c_str());

      // Setting levels.dat path
      sprintf(levels_file, "%s", levelsPath.c_str());

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
      guard_palettes = (uint8_t *)load_from_opendats_alloc(10, "bin", NULL, NULL);
      
      // Level color variations (1.3)
      level_var_palettes = reinterpret_cast<uint8_t *>(load_from_opendats_alloc(20, "bin", NULL, NULL));

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

  __INLINE__ void  advanceState(const bool upPressed, const bool downPressed, const bool leftPressed, const bool rightPressed, const bool shiftPressed, const bool restartPressed)
  {
    _upPressed = upPressed;
    _downPressed = downPressed;
    _leftPressed = leftPressed;
    _rightPressed = rightPressed;
    _shiftPressed = shiftPressed;
    is_restart_level = restartPressed ? 1 : 0;
    gameState.kidPreviousFrame = gameState.Kid.frame;

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

__INLINE__ void  startLevel(const uint16_t level)
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

__INLINE__ void  find_exe_dir()
{
  if (found_exe_dir)
    return;
  snprintf(exe_dir, sizeof(exe_dir), "%s", "g_argv[0]");
  char *last_slash = NULL;
  char *pos = exe_dir;
  char c;
  for (c = *pos; c != '\0'; c = *(++pos))
  {
    if (c == '/' || c == '\\')
    {
      last_slash = pos;
    }
  }
  if (last_slash != NULL)
  {
    *last_slash = '\0';
  }
  found_exe_dir = true;
}

__INLINE__ bool file_exists(const char *filename)
{
  return (access(filename, F_OK) != -1);
}

__INLINE__ const char *locate_file_(const char *filename, char *path_buffer, int buffer_size)
{
  if (file_exists(filename))
  {
    return filename;
  }
  else
  {
    // If failed, it may be that SDLPoP is being run from the wrong different working directory.
    // We can try to rescue the situation by loading from the directory of the executable.
    find_exe_dir();
    snprintf(path_buffer, 8192, "%s/%s", exe_dir, filename);
    return (const char *)path_buffer;
  }
}

// seg009:000D
__INLINE__ int read_key()
{
  // stub
  int key = last_key_scancode;
  last_key_scancode = 0;
  return key;
}

// seg009:019A
__INLINE__ void  clear_kbd_buf()
{
  // stub
  last_key_scancode = 0;
  last_text_input = 0;
}

// seg009:040A
__INLINE__ uint16_t prandom(uint16_t max)
{
  if (!seed_was_init)
  {
    // init from current time
    gameState.random_seed = time(NULL);
    seed_was_init = 1;
  }
  gameState.random_seed = gameState.random_seed * 214013 + 2531011;
  return (gameState.random_seed >> 16) % (max + 1);
}

__INLINE__ FILE *open_dat_from_root_or_data_dir(const char *filename)
{
  FILE *fp = NULL;
  fp = fopen(filename, "rb");

  // if failed, try if the DAT file can be opened in the data/ directory, instead of the main folder
  if (fp == NULL)
  {
    char data_path[__QS_POP_MAX_PATH + 4096];
    snprintf(data_path, sizeof(data_path), "data/%s", filename);

    if (!file_exists(data_path))
    {
      find_exe_dir();
      snprintf(data_path, sizeof(data_path), "%s/data/%s", exe_dir, filename);
    }

    // verify that this is a regular file and not a directory (otherwise, don't open)
    fp = fopen(data_path, "rb");
  }
  return fp;
}

// seg009:0F58
__INLINE__ dat_type *open_dat(const char *filename, int drive)
{
  FILE *fp = NULL;
  fp = open_dat_from_root_or_data_dir(filename);
  dat_header_type dat_header;
  dat_table_type *dat_table = NULL;

  dat_type *pointer = (dat_type *)calloc(1, sizeof(dat_type));
  snprintf(pointer->filename, sizeof(pointer->filename), "%s", filename);
  pointer->next_dat = dat_chain_ptr;
  dat_chain_ptr = pointer;

  if (fp != NULL)
  {
    if (fread(&dat_header, 6, 1, fp) != 1)
      goto failed;
    dat_table = (dat_table_type *)malloc(dat_header.table_size);
    if (dat_table == NULL ||
        fseek(fp, dat_header.table_offset, SEEK_SET) ||
        fread(dat_table, dat_header.table_size, 1, fp) != 1)
      goto failed;
    pointer->handle = fp;
    pointer->dat_table = dat_table;
  }

out:
  // stub
  return pointer;
failed:
  if (fp)
    fclose(fp);
  if (dat_table)
    free(dat_table);
  goto out;
}

// seg000:0000
__INLINE__ void pop_main()
{
  // Fix bug: with start_in_blind_mode enabled, moving objects are not displayed until blind mode is toggled off+on??
  need_drects = 1;

  dathandle = open_dat("PRINCE.DAT", 0);

  parse_cmdline_sound();

  init_game_main();
}

// seg009:9F80
__INLINE__ void *load_from_opendats_alloc(int resource, const char *extension, data_location *out_result, int *out_size)
{
  // stub
  // printf("id = %d\n",resource);
  dat_type *pointer;
  data_location result;
  uint8_t checksum;
  int size;
  FILE *fp = NULL;
  load_from_opendats_metadata(resource, extension, &fp, &result, &checksum, &size, &pointer);
  if (out_result != NULL)
    *out_result = result;
  if (out_size != NULL)
    *out_size = size;
  if (result == data_none)
    return NULL;

  void  *area = malloc(size);
  // read(fd, area, size);
  if (fread(area, size, 1, fp) != 1)
  {
    printf("ERROR\n");
    fprintf(stderr, "%s: %s, resource %d, size %d, failed: %s\n", __func__, pointer->filename, resource, size, strerror(errno));
    free(area);
    area = NULL;
  }

  if (result == data_directory)
    fclose(fp);
  /* XXX: check checksum */
  return area;
}

// seg009:121A
__INLINE__ image_type * load_image(int resource_id, dat_pal_type *palette)
{
  // stub
  data_location result;
  int size;
  image_data_type *image_data = (image_data_type *)load_from_opendats_alloc(resource_id, "png", &result, &size);
  image_type *image = (image_type *)malloc(sizeof(image_data));
  switch (result)
  {
  case data_none:
    return NULL;
    break;
  case data_DAT:
  { // DAT
    image->h = image_data->height;
    image->w = image_data->width;
  }
  break;
  case data_directory:
  { // directory
    SDL_RWops *rw = SDL_RWFromConstMem(image_data, size);
    SDL_Surface *image2 = IMG_Load_RW(rw, 0);
    image->h = image2->h;
    image->w = image2->w;
  }
  break;
  }
  if (image_data != NULL) free(image_data);

  return image;
}

// seg009:104E
__INLINE__ chtab_type *load_sprites_from_file(int resource, int palette_bits, int quit_on_error)
{
  int i;
  int n_images = 0;
  // int has_palette_bits = 1;
  chtab_type *chtab = NULL;
  dat_shpl_type *shpl = (dat_shpl_type *)load_from_opendats_alloc(resource, "pal", NULL, NULL);

  dat_pal_type *pal_ptr = &shpl->palette;

  n_images = shpl->n_images;
  size_t alloc_size = sizeof(chtab_type) + sizeof(void *) * n_images;
  chtab = (chtab_type *)malloc(alloc_size);
  memset(chtab, 0, alloc_size);
  chtab->n_images = n_images;
  for (i = 1; i <= n_images; i++)
  {
    chtab->images[i - 1] = load_image(resource + i, pal_ptr);
    ;
  }
  return chtab;
}

__INLINE__ void  load_from_opendats_metadata(int resource_id, const char *extension, FILE **out_fp, data_location *result, uint8_t *checksum, int *size, dat_type **out_pointer)
{
  char image_filename[__QS_POP_MAX_PATH];
  FILE *fp = NULL;
  dat_type *pointer;
  *result = data_none;
  // Go through all open DAT files.
  for (pointer = dat_chain_ptr; fp == NULL && pointer != NULL; pointer = pointer->next_dat)
  {
    *out_pointer = pointer;
    if (pointer->handle != NULL)
    {
      // If it's an actual DAT file:
      fp = pointer->handle;
      dat_table_type *dat_table = pointer->dat_table;
      int i;
      for (i = 0; i < dat_table->res_count; ++i)
      {
        if (dat_table->entries[i].id == resource_id)
        {
          break;
        }
      }
      if (i < dat_table->res_count)
      {
        // found
        *result = data_DAT;
        *size = dat_table->entries[i].size;
        if (fseek(fp, dat_table->entries[i].offset, SEEK_SET) ||
            fread(checksum, 1, 1, fp) != 1)
        {
          perror(pointer->filename);
          fp = NULL;
        }
      }
      else
      {
        // not found
        fp = NULL;
      }
    }
    else
    {
      // If it's a directory:
      char filename_no_ext[__QS_POP_MAX_PATH];
      // strip the .DAT file extension from the filename (use folders simply named TITLE, KID, VPALACE, etc.)
      strncpy(filename_no_ext, pointer->filename, sizeof(filename_no_ext));
      size_t len = strlen(filename_no_ext);
      if (len >= 5 && filename_no_ext[len - 4] == '.')
      {
        filename_no_ext[len - 4] = '\0'; // terminate, so ".DAT" is deleted from the filename
      }
      snprintf(image_filename, sizeof(image_filename), "data/%s/res%d.%s", filename_no_ext, resource_id, extension);

      // printf("loading (binary) %s",image_filename);
      
      char newPath[8192];
      const char *filename = locate_file_(image_filename, newPath, __QS_POP_MAX_PATH); 
      // printf("File: %s\n", filename);
      fp = fopen(filename, "rb");
      if (fp != NULL)
      {
        *result = data_directory;
      }

      if (fp != NULL)
      {
        *result = data_directory;

        fseek(fp, 0L, SEEK_END);
        *size = ftell(fp);
        fseek(fp, 0L, SEEK_SET);
      }
    }
  }
  *out_fp = fp;
  if (fp == NULL)
  {
    *result = data_none;
    //  printf(" FAILED\n");
    // return NULL;
  }
  //...
}

// seg009:9F34
__INLINE__ void  close_dat(dat_type*pointer)
{
  dat_type **prev = &dat_chain_ptr;
  dat_type *curr = dat_chain_ptr;
  while (curr != NULL)
  {
    if (curr == pointer)
    {
      *prev = curr->next_dat;
      if (curr->handle)
        fclose(curr->handle);
      if (curr->dat_table)
        free(curr->dat_table);
      free(curr);
      return;
    }
    curr = curr->next_dat;
    prev = &((*prev)->next_dat);
  }
  // stub
}

// seg009:A172
__INLINE__ int load_from_opendats_to_area(int resource, void *area, int length, const char *extension)
{
  // stub
  // return 0;
  dat_type *pointer;
  data_location result;
  uint8_t checksum;
  int size;
  FILE *fp = NULL;
  load_from_opendats_metadata(resource, extension, &fp, &result, &checksum, &size, &pointer);
  if (result == data_none)
    return 0;
  if (fread(area, std::min(size, length), 1, fp) != 1)
  {
    fprintf(stderr, "%s: %s, resource %d, size %d, failed: %s\n", __func__, pointer->filename, resource, size, strerror(errno));
    memset(area, 0, std::min(size, length));
  }
  if (result == data_directory)
    fclose(fp);
  /* XXX: check checksum */
  return 0;
}

// seg000:024F
__INLINE__ void  init_game_main()
{
  doorlink1_ad = /*&*/ gameState.level.doorlinks1;
  doorlink2_ad = /*&*/ gameState.level.doorlinks2;
  prandom(1);
  // PRINCE.DAT: sword
  chtab_addrs[id_chtab_0_sword] = load_sprites_from_file(700, 1 << 2, 1);
  // PRINCE.DAT: flame, sword on floor, potion
  chtab_addrs[id_chtab_1_flameswordpotion] = load_sprites_from_file(150, 1 << 3, 1);
  close_dat(dathandle);

  start_game();
}

__INLINE__ void  init_copyprot()
{
  uint16_t which_entry;
  uint16_t pos;
  uint16_t entry_used[40];
  uint8_t letts_used[27];

  copyprot_plac = prandom(13);
  memset(&entry_used, 0, sizeof(entry_used));
  memset(&letts_used, 0, sizeof(letts_used));
  for (pos = 0; pos < 14; ++pos)
  {
    do
    {
      if (pos == copyprot_plac)
      {
        which_entry = copyprot_idx = prandom(39);
      }
      else
      {
        which_entry = prandom(39);
      }
    } while (entry_used[which_entry] || letts_used[copyprot_letter[which_entry] - 'A']);
    cplevel_entr[pos] = which_entry;
    entry_used[which_entry] = 1;
    letts_used[copyprot_letter[which_entry] - 'A'] = 1;
  }
}

__INLINE__ void  start_game()
{
  // Prevent filling of stack.
  // start_game is called from many places to restart the game, for example:
  // process_key, play_frame, draw_game_frame, play_level, control_kid, end_sequence, expired
  // init_copyprot();

  init_game(start_level);
}

__INLINE__ void  restore_room_after_quick_load()
{
  int temp1 = gameState.curr_guard_color;
  int temp2 = gameState.next_level;
  reset_level_unused_fields(false);
  gameState.curr_guard_color = temp1;
  gameState.next_level = temp2;

  // need_full_redraw = 1;
  //  Show the room where the prince is, even if the player moved the view away from it (with the H,J,U,N keys).
  next_room = gameState.drawn_room = gameState.Kid.room;
  load_room_links();
  // draw_level_first();
  // gen_palace_wall_colors();
  gameState.is_guard_notice = 0; // prevent guard turning around immediately
  // redraw_screen(1); // for room_L

  hitp_delta = guardhp_delta = 1; // force HP redraw
  // Don't draw guard HP if a previously viewed room (with the H,J,U,N keys) had a guard but the current room doesn't have one.
  if (gameState.Guard.room != gameState.drawn_room)
  {
    // Like in clear_char().
    gameState.Guard.direction = dir_56_none;
    gameState.guardhp_curr = 0;
  }

  loadkid_and_opp();
  // Get rid of "press button" message if kid was dead before quickload.
  text_time_total = text_time_remaining = 0;
}

// seg000:04CD
__INLINE__ int process_key()
{

  return 1;
}

// seg000:08EB
__INLINE__ void  play_frame()
{
  do_mobs();
  process_trobs();
  check_skel();
  check_can_guard_see_kid();
  // if level is restarted, return immediately
  if (play_kid_frame())
    return;
  play_guard_frame();
  if (0 == resurrect_time)
  {
    check_sword_hurting();
    check_sword_hurt();
  }
  check_sword_vs_sword();
  do_delta_hp();
  exit_room();
  check_the_end();
  check_guard_fallout();
  if (gameState.current_level == 0)
  {
    // Special event: level 0 running exit
    if (gameState.Kid.room == 24)
    {
      start_level = -1;
      need_quotes = 1;
      start_game();
    }
  }
  else if (gameState.current_level == 6)
  {
    // Special event: level 6 falling exit
    if (roomleave_result == -2)
    {
      gameState.Kid.y = -1;
      ++gameState.next_level;
    }
  }
  else if (gameState.current_level == 12)
  {
    // Special event: level 12 running exit
    if (gameState.Kid.room == 23)
    {
      ++gameState.next_level;
      // Sounds must be stopped, because play_level_2() checks gameState.next_level only if there are no sounds playing.
      seamless = 1;
    }
  }
}

// seg007:1041
__INLINE__ int16_t get_curr_tile(int16_t tilepos)
{
  curr_modifier = curr_room_modif[tilepos];
  return curr_tile = curr_room_tiles[tilepos] & 0x1F;
}

// seg000:0B12
__INLINE__ void  anim_tile_modif()
{
  uint16_t tilepos;
  for (tilepos = 0; tilepos < 30; ++tilepos)
  {
    switch (get_curr_tile(tilepos))
    {
    case tiles_10_potion:
      start_anim_potion(gameState.drawn_room, tilepos);
      break;
    case tiles_19_torch:
    case tiles_30_torch_with_debris:
      start_anim_torch(gameState.drawn_room, tilepos);
      break;
    case tiles_22_sword:
      start_anim_sword(gameState.drawn_room, tilepos);
      break;
    }
  }

  // Animate torches in the rightmost column of the left-side room as well, because they are visible in the current room.
  int row;
  for (row = 0; row <= 2; row++)
  {
    switch (get_tile(room_L, 9, row))
    {
    case tiles_19_torch:
    case tiles_30_torch_with_debris:
      start_anim_torch(room_L, row * 10 + 9);
      break;
    }
  }
}

__INLINE__ void  load_lev_spr(int level)
{
  dat_type *dathandle;
  int16_t guardtype;
  char filename[20];
  dathandle = NULL;
  gameState.current_level = gameState.next_level = level;
  snprintf(filename, sizeof(filename), "%s%s.DAT", tbl_envir_gr[gmMcgaVga], tbl_envir_ki[custom->tbl_level_type[gameState.current_level]]);
  load_chtab_from_file(id_chtab_6_environment, 200, filename, 1 << 5);
  load_more_opt_graf(filename);
  guardtype = custom->tbl_guard_type[gameState.current_level];
  if (guardtype != -1)
  {
    if (guardtype == 0)
    {
      dathandle = open_dat(custom->tbl_level_type[gameState.current_level] ? "GUARD1.DAT" : "GUARD2.DAT", 0);
    }
    load_chtab_from_file(id_chtab_5_guard, 750, tbl_guard_dat[guardtype], 1 << 8);
    if (dathandle)
    {
      close_dat(dathandle);
    }
  }

  gameState.curr_guard_color = 0;
  load_chtab_from_file(id_chtab_7_environmentwall, 360, filename, 1 << 6);
}

// seg000:0E6C
__INLINE__ void  load_level()
{
  if (is_restart_level == 0)
  {
    dat_type *dathandle;
    dathandle = open_dat(levels_file, 0);
    load_from_opendats_to_area(gameState.current_level + 2000, &gameState.level, sizeof(gameState.level), "bin");
    close_dat(dathandle);
  }

  reset_level_unused_fields(true); // added
}

__INLINE__ void  reset_level_unused_fields(bool loading_clean_level)
{
  // Entirely unused fields in the level format: reset to zero for now
  // They can be repurposed to add new stuff to the level format in the future
  memset(gameState.level.roomxs, 0, sizeof(gameState.level.roomxs));
  memset(gameState.level.roomys, 0, sizeof(gameState.level.roomys));
  memset(gameState.level.fill_1, 0, sizeof(gameState.level.fill_1));
  memset(gameState.level.fill_2, 0, sizeof(gameState.level.fill_2));
  memset(gameState.level.fill_3, 0, sizeof(gameState.level.fill_3));

  // gameState.level.used_rooms is 25 on some levels. Limit it to the actual number of rooms.
  if (gameState.level.used_rooms > 24)
    gameState.level.used_rooms = 24;

  // For these fields, only use the bits that are actually used, and set the rest to zero.
  // Good for repurposing the unused bits in the future.
  int i;
  for (i = 0; i < gameState.level.used_rooms; ++i)
  {
    // gameState.level.guards_dir[i]   &= 0x01; // 1 bit in use
    gameState.level.guards_skill[i] &= 0x0F; // 4 bits in use
  }

  // In savestates, additional information may be stored (e.g. remembered guard hp) - should not reset this then!
  if (loading_clean_level)
  {
    for (i = 0; i < gameState.level.used_rooms; ++i)
    {
      gameState.level.guards_color[i] &= 0x0F; // 4 bits in use (other 4 bits repurposed as remembered guard hp)
    }
  }
}

// seg000:0EA8
// returns 1 if level is restarted, 0 otherwise
__INLINE__ int play_kid_frame()
{
  loadkid_and_opp();
  load_fram_det_col();
  check_killed_shadow();
  play_kid();
  if (upside_down && gameState.Char.alive >= 0)
  {
    upside_down = 0;
    need_redraw_because_flipped = 1;
  }
  if (is_restart_level)
  {
    return 1;
  }
  if (gameState.Char.room != 0)
  {
    play_seq();
    fall_accel();
    fall_speed();
    load_frame_to_obj();
    load_fram_det_col();
    set_char_collision();
    bump_into_opponent();
    check_collisions();
    check_bumped();
    check_gate_push();
    check_action();
    check_press();
    check_spike_below();
    if (resurrect_time == 0)
    {
      check_spiked();
      check_chomped_kid();
    }
    check_knock();
  }
  savekid();
  return 0;
}

// seg000:0F48
__INLINE__ void  play_guard_frame()
{
  if (gameState.Guard.direction != dir_56_none)
  {
    loadshad_and_opp();
    load_fram_det_col();
    check_killed_shadow();
    play_guard();
    if (gameState.Char.room == gameState.drawn_room)
    {
      play_seq();
      if (gameState.Char.x >= 44 && gameState.Char.x < 211)
      {
        fall_accel();
        fall_speed();
        load_frame_to_obj();
        load_fram_det_col();
        set_char_collision();
        check_guard_bumped();
        check_action();
        check_press();
        check_spike_below();
        check_spiked();
        check_chomped_guard();
      }
    }
    saveshad();
  }
}

// seg000:0FBD
__INLINE__ void  check_the_end()
{
  if (next_room != 0 && next_room != gameState.drawn_room)
  {
    gameState.drawn_room = next_room;
    load_room_links();
    gameState.exit_room_timer = 2; // Added to remember exit room timer
    loadkid();
    anim_tile_modif();
    start_chompers();
    check_fall_flo();
    check_shadow();
  }
}

// seg000:1009
__INLINE__ void  check_fall_flo()
{
  // Special event: falling floors
  if (gameState.current_level == /*13*/ custom->loose_tiles_level &&
      (gameState.drawn_room == /*23*/ custom->loose_tiles_room_1 || gameState.drawn_room == /*16*/ custom->loose_tiles_room_2))
  {
    get_room_address(curr_room = room_A);
    for (curr_tilepos = /*22*/ custom->loose_tiles_first_tile;
         curr_tilepos <= /*27*/ custom->loose_tiles_last_tile;
         ++curr_tilepos)
    {
      make_loose_fall(-(prandom(0xFF) & 0x0F));
    }
  }
}

// seg000:11EC
__INLINE__ void  add_life()
{
  int16_t hpmax = gameState.hitp_max;
  ++hpmax;
  // CusPop: set maximum number of hitpoints (max_hitp_allowed, default = 10)
  //	if (hpmax > 10) hpmax = 10; // original
  if (hpmax > custom->max_hitp_allowed)
    hpmax = custom->max_hitp_allowed;
  gameState.hitp_max = hpmax;
  set_health_life();
}

// seg000:1200
__INLINE__ void  set_health_life()
{
  hitp_delta = gameState.hitp_max - gameState.hitp_curr;
}

// seg000:127B
__INLINE__ void  do_delta_hp()
{
  // level 12: if the shadow is hurt, gameState.Kid is also hurt
  if (Opp.charid == charid_1_shadow &&
      gameState.current_level == 12 &&
      guardhp_delta != 0)
  {
    hitp_delta = guardhp_delta;
  }
  gameState.hitp_curr = std::min(std::max(gameState.hitp_curr + hitp_delta, 0), (int)gameState.hitp_max);
  gameState.guardhp_curr = std::min(std::max(gameState.guardhp_curr + guardhp_delta, 0), (int)gameState.guardhp_max);
}

// seg000:1353
__INLINE__ void  check_sword_vs_sword()
{
}

// seg000:136A
__INLINE__ void  load_chtab_from_file(int chtab_id, int resource, const char  *filename, int palette_bits)
{
  // printf("Loading chtab %d, id %d from %s\n",chtab_id,resource,filename);
  dat_type *dathandle;
  if (chtab_addrs[chtab_id] != NULL)
    return;
  dathandle = open_dat(filename, 0);
  chtab_addrs[chtab_id] = load_sprites_from_file(resource, palette_bits, 1);
  close_dat(dathandle);
}

// seg009:12EF
__INLINE__ void  load_one_optgraf(chtab_type *chtab_ptr, dat_pal_type*pal_ptr, int base_id, int min_index, int max_index)
{
  int16_t index;
  for (index = min_index; index <= max_index; ++index)
  {
    image_type *image = load_image(base_id + index + 1, pal_ptr);
    if (image != NULL)
      chtab_ptr->images[index] = image;
  }
}

// seg000:13FC
__INLINE__ void  load_more_opt_graf(const char *filename)
{
  // stub
  dat_type *dathandle;
  dat_shpl_type area;
  int16_t graf_index;
  dathandle = NULL;
  for (graf_index = 0; graf_index < 8; ++graf_index)
  {
    /*if (...) */ {
      if (dathandle == NULL)
      {
        dathandle = open_dat(filename, 0);
        load_from_opendats_to_area(200, &area, sizeof(area), "pal");
        area.palette.row_bits = 0x20;
      }
      load_one_optgraf(chtab_addrs[id_chtab_6_environment], &area.palette, 1200, optgraf_min[graf_index] - 1, optgraf_max[graf_index] - 1);
    }
  }
  if (dathandle != NULL)
  {
    close_dat(dathandle);
  }
}

// seg000:148D
__INLINE__ int do_paused()
{
  uint16_t key;
  key = 0;
  next_room = 0;
  control_shift = 0;
  control_y = 0;
  control_x = 0;
  read_keyb_control();
  key = process_key();
  return key || control_shift;
}

// seg000:1500
__INLINE__ void  read_keyb_control()
{
  if (_upPressed == true) control_y = -1;
  if (_upPressed == false && _downPressed == true) control_y = 1;
  if (_leftPressed == true) control_x = -1;
  if (_leftPressed == false && _rightPressed == true) control_x = 1;
  control_shift = _shiftPressed ? -1 : 1;
}

// seg000:15E9
__INLINE__ void  toggle_upside()
{
  upside_down = ~upside_down;
  need_redraw_because_flipped = 1;
}

// seg000:15F8
__INLINE__ void  feather_fall()
{
  gameState.is_feather_fall = 1;
  flash_color = 2; // green
  flash_time = 3;
}

// seg000:172C
__INLINE__ void  gen_palace_wall_colors()
{
  uint32_t old_randseed;
  uint16_t prev_color;
  int16_t row;
  int16_t subrow;
  uint16_t color_base;
  int16_t column;
  uint16_t color;

  old_randseed = gameState.random_seed;
  gameState.random_seed = gameState.drawn_room;
  prandom(1); // discard
  for (row = 0; row < 3; row++)
  {
    for (subrow = 0; subrow < 4; subrow++)
    {
      if (subrow % 2)
      {
        color_base = 0x61; // 0x61..0x64 in subrow 1 and 3
      }
      else
      {
        color_base = 0x66; // 0x66..0x69 in subrow 0 and 2
      }
      prev_color = -1;
      for (column = 0; column <= 10; ++column)
      {
        do
        {
          color = color_base + prandom(3);
        } while (color == prev_color);
        palace_wall_colors[44 * row + 11 * subrow + column] = color;
        // palace_wall_colors[row][subrow][column] = color;
        prev_color = color;
      }
    }
  }
  gameState.random_seed = old_randseed;
}

// seg000:1D2C
__INLINE__ void  load_kid_sprite()
{
  load_chtab_from_file(id_chtab_2_kid, 400, "KID.DAT", 1 << 7);
}

// seg000:1F7B
__INLINE__ void  parse_cmdline_sound()
{
  // Use digi (wave) sounds and MIDI music.
  sound_flags |= sfDigi;
  sound_flags |= sfMidi;
  sound_mode = smSblast;
}

// seg002:0000
__INLINE__ void  do_init_shad(const uint8_t *source, int seq_index)
{
  memcpy(&gameState.Char, source, 7);
  seqtbl_offset_char(seq_index);
  gameState.Char.charid = charid_1_shadow;
  gameState.demo_time = 0;
  gameState.guard_skill = 3;
  guardhp_delta = gameState.guardhp_curr = gameState.guardhp_max = 4;
  saveshad();
}

// seg002:0044
__INLINE__ void  get_guard_hp()
{
  auto guardExtraStrength = version == gameVersion_t::v10 ? custom->extrastrength10[gameState.guard_skill] : custom->extrastrength14[gameState.guard_skill];
  guardhp_delta = gameState.guardhp_curr = gameState.guardhp_max = guardExtraStrength + custom->tbl_guard_hp[gameState.current_level];
}

// seg002:0064
__INLINE__ void  check_shadow()
{
  gameState.offguard = 0;
  if (gameState.current_level == 12)
  {
    // Special event: level 12 shadow
    if (!gameState.united_with_shadow && gameState.drawn_room == 15)
    {
      gameState.Char.room = gameState.drawn_room;
      if (get_tile(15, 1, 0) == tiles_22_sword)
      {
        return;
      }
      gameState.shadow_initialized = 0;
      do_init_shad(/*&*/ custom->init_shad_12, 7 /*fall*/);
      return;
    }
  }
  else if (gameState.current_level == 6)
  {
    // Special event: level 6 shadow
    gameState.Char.room = gameState.drawn_room;
    if (gameState.Char.room == 1)
    {
      if (gameState.leveldoor_open != 0x4D)
      {
        gameState.leveldoor_open = 0x4D;
      }
      do_init_shad(/*&*/ custom->init_shad_6, 2 /*stand*/);
      return;
    }
  }
  else if (gameState.current_level == 5)
  {
    // Special event: level 5 shadow
    gameState.Char.room = gameState.drawn_room;
    if (gameState.Char.room == 24)
    {
      if (get_tile(24, 3, 0) != tiles_10_potion)
      {
        return;
      }
      do_init_shad(/*&*/ custom->init_shad_5, 2 /*stand*/);
      return;
    }
  }
  enter_guard();
}

// seg002:0112
__INLINE__ void  enter_guard()
{
  uint16_t room_minus_1;
  uint16_t guard_tile;
  uint16_t frame;
  uint8_t seq_hi;
  // arrays are indexed 0..23 instead of 1..24
  room_minus_1 = gameState.drawn_room - 1;
  frame = gameState.Char.frame; // hm?
  guard_tile = gameState.level.guards_tile[room_minus_1];
  if (guard_tile >= 30)
    return;

  gameState.Char.room = gameState.drawn_room;
  gameState.Char.curr_row = guard_tile / 10;
  gameState.Char.y = y_land[gameState.Char.curr_row + 1];
  gameState.Char.x = gameState.level.guards_x[room_minus_1];
  gameState.Char.curr_col = get_tile_div_mod_m7(gameState.Char.x);
  gameState.Char.direction = gameState.level.guards_dir[room_minus_1];
  // only regular guards have different colors (and only on VGA)
  gameState.curr_guard_color = 0;

#ifdef REMEMBER_GUARD_HP
  int remembered_hp = (gameState.level.guards_color[room_minus_1] & 0xF0) >> 4;
#endif
  gameState.curr_guard_color &= 0x0F; // added; only least significant 4 bits are used for guard color

  // level 3 has skeletons with infinite lives
  // if (gameState.current_level == 3) {
  if (custom->tbl_guard_type[gameState.current_level] == 2)
  {
    gameState.Char.charid = charid_4_skeleton;
  }
  else
  {
    gameState.Char.charid = charid_2_guard;
  }
  seq_hi = gameState.level.guards_seq_hi[room_minus_1];
  if (seq_hi == 0)
  {
    if (gameState.Char.charid == charid_4_skeleton)
    {
      gameState.Char.sword = sword_2_drawn;
      seqtbl_offset_char(seq_63_guard_stand_active); // stand active (when entering room) (skeleton)
    }
    else
    {
      gameState.Char.sword = sword_0_sheathed;
      seqtbl_offset_char(seq_77_guard_stand_inactive); // stand inactive (when entering room)
    }
  }
  else
  {
    gameState.Char.curr_seq = gameState.level.guards_seq_lo[room_minus_1] + (seq_hi << 8);
  }
  play_seq();
  gameState.guard_skill = gameState.level.guards_skill[room_minus_1];
  if (gameState.guard_skill >= __QS_NUM_GUARD_SKILLS)
  {
    gameState.guard_skill = 3;
  }
  frame = gameState.Char.frame;
  if (frame == frame_185_dead || frame == frame_177_spiked || frame == frame_178_chomped)
  {
    gameState.Char.alive = 1;
    gameState.guardhp_curr = 0;
  }
  else
  {
    gameState.Char.alive = -1;
    gameState.justblocked = 0;
    gameState.guard_refrac = 0;
    gameState.is_guard_notice = 0;
    get_guard_hp();
  }
  gameState.Char.fall_y = 0;
  gameState.Char.fall_x = 0;
  gameState.Char.action = actions_1_run_jump;
  saveshad();
}

// seg002:0269
__INLINE__ void  check_guard_fallout()
{
  if (gameState.Guard.direction == dir_56_none || gameState.Guard.y < 211)
  {
    return;
  }
  if (gameState.Guard.charid == charid_1_shadow)
  {
    if (gameState.Guard.action != actions_4_in_freefall)
    {
      return;
    }
    loadshad();
    clear_char();
    saveshad();
  }
  else if (gameState.Guard.charid == charid_4_skeleton &&
           (gameState.Guard.room = gameState.level.roomlinks[gameState.Guard.room - 1].down) == /*3*/ custom->skeleton_reappear_room)
  {
    // if skeleton falls down into room 3
    gameState.Guard.x = /*133*/ custom->skeleton_reappear_x;
    gameState.Guard.curr_row = /*1*/ custom->skeleton_reappear_row;
    gameState.Guard.direction = /*dir_0_right*/ custom->skeleton_reappear_dir;
    gameState.Guard.alive = -1;
    leave_guard();
  }
  else
  {
    on_guard_killed();
    gameState.level.guards_tile[gameState.drawn_room - 1] = -1;
    gameState.Guard.direction = dir_56_none;
    gameState.guardhp_curr = 0;
  }
}

// seg002:02F5
__INLINE__ void  leave_guard()
{
  uint16_t room_minus_1;
  if (gameState.Guard.direction == dir_56_none || gameState.Guard.charid == charid_1_shadow || gameState.Guard.charid == charid_24_mouse)
  {
    return;
  }
  // arrays are indexed 0..23 instead of 1..24
  room_minus_1 = gameState.Guard.room - 1;
  gameState.level.guards_tile[room_minus_1] = get_tilepos(0, gameState.Guard.curr_row);
  gameState.level.guards_color[room_minus_1] = gameState.curr_guard_color & 0x0F; // restriction to 4 bits added

  gameState.level.guards_x[room_minus_1] = gameState.Guard.x;
  gameState.level.guards_dir[room_minus_1] = gameState.Guard.direction;
  gameState.level.guards_skill[room_minus_1] = gameState.guard_skill;
  if (gameState.Guard.alive < 0)
  {
    gameState.level.guards_seq_hi[room_minus_1] = 0;
  }
  else
  {
    gameState.level.guards_seq_lo[room_minus_1] = gameState.Guard.curr_seq;
    gameState.level.guards_seq_hi[room_minus_1] = gameState.Guard.curr_seq >> 8;
  }
  gameState.Guard.direction = dir_56_none;
  gameState.guardhp_curr = 0;
}

// seg002:0486
__INLINE__ int goto_other_room(int16_t direction)
{
  // printf("goto_other_room: direction = %d, gameState.Char.room = %d\n", direction, gameState.Char.room);
  int16_t opposite_dir;
  uint8_t other_room = ((uint8_t *)&gameState.level.roomlinks[gameState.Char.room - 1])[direction];
  gameState.Char.room = other_room;
  if (direction == 0)
  {
    // left
    gameState.Char.x += 140;
    opposite_dir = 1;
  }
  else if (direction == 1)
  {
    // right
    gameState.Char.x -= 140;
    opposite_dir = 0;
  }
  else if (direction == 2)
  {
    // up
    gameState.Char.y += 189;
    gameState.Char.curr_row = y_to_row_mod4(gameState.Char.y);
    opposite_dir = 3;
  }
  else
  {
    // down
    gameState.Char.y -= 189;
    gameState.Char.curr_row = y_to_row_mod4(gameState.Char.y);
    opposite_dir = 2;
  }
  return opposite_dir;
}

// seg002:039E
__INLINE__ void  follow_guard()
{
  gameState.level.guards_tile[gameState.Kid.room - 1] = 0xFF;
  gameState.level.guards_tile[gameState.Guard.room - 1] = 0xFF;
  loadshad();
  goto_other_room(roomleave_result);
  saveshad();
}

// seg002:0504
__INLINE__ int16_t leave_room()
{
  int16_t frame;
  uint16_t action;
  int16_t chary;
  int16_t leave_dir;
  chary = gameState.Char.y;
  action = gameState.Char.action;
  frame = gameState.Char.frame;
  if (action != actions_5_bumped &&
      action != actions_4_in_freefall &&
      action != actions_3_in_midair &&
      (int8_t)chary < 10 && (int8_t)chary > -16)
  {
    leave_dir = 2; // up
  }
  else if (chary >= 211)
  {
    leave_dir = 3; // down
  }
  else if (
    // frames 135..149: climb up
    (frame >= frame_135_climbing_1 && frame < 150) ||
    // frames 110..119: standing up from crouch
    (frame >= frame_110_stand_up_from_crouch_1 && frame < 120) ||
    // frames 150..162: with sword
    (frame >= frame_150_parry && frame < 163) ||
    // frames 166..168: with sword
    (frame >= frame_166_stand_inactive && frame < 169) ||
    action == actions_7_turn // turn
  )
  {
    return -1;
  }
  else if (gameState.Char.direction != dir_0_right)
  {
    // looking left
    if (char_x_left <= 54)
    {
      leave_dir = 0; // left
    }
    else if (char_x_left >= 198)
    {
      leave_dir = 1; // right
    }
    else
    {
      return -1;
    }
  }
  else
  {
    // looking right
    get_tile(gameState.Char.room, 9, gameState.Char.curr_row);
    if (curr_tile2 != tiles_7_doortop_with_floor &&
        curr_tile2 != tiles_12_doortop &&
        char_x_right >= 201)
    {
      leave_dir = 1; // right
    }
    else if (char_x_right <= 57)
    {
      leave_dir = 0; // left
    }
    else
    {
      return -1;
    }
  }
  switch (leave_dir)
  {
  case 0: // left
    play_mirr_mus();
    level3_set_chkp();
    Jaffar_exit();
    break;
  case 1: // right
    sword_disappears();
    meet_Jaffar();
    break;
  // case 2: // up
  case 3: // down
    // Special event: falling exit
    if (gameState.current_level == custom->falling_exit_level /*6*/ && gameState.Char.room == custom->falling_exit_room /*1*/)
    {
      return -2;
    }
    break;
  }
  goto_other_room(leave_dir);
#ifdef USE_REPLAY
  if (skipping_replay && replay_seek_target == replay_seek_0_next_room)
    skipping_replay = 0;
#endif
  return leave_dir;
}

// seg002:03C7
__INLINE__ void  exit_room()
{
  uint16_t leave;
  uint16_t kid_room_m1;
  leave = 0;
  if (gameState.exit_room_timer != 0)
  {
    --gameState.exit_room_timer;
    return;
  }
  loadkid();
  load_frame_to_obj();
  set_char_collision();
  roomleave_result = leave_room();
  if (roomleave_result < 0)
  {
    return;
  }
  savekid();
  next_room = gameState.Char.room;
  if (gameState.Guard.direction == dir_56_none)
    return;
  if (gameState.Guard.alive < 0 && gameState.Guard.sword == sword_2_drawn)
  {
    kid_room_m1 = gameState.Kid.room - 1;
    // kid_room_m1 might be 65535 (-1) when the prince fell out of the level (to room 0) while a guard was active.
    // In this case, the indexing in the following condition crashes on Linux.
    if ((kid_room_m1 >= 0 && kid_room_m1 <= 23) &&
        (gameState.level.guards_tile[kid_room_m1] >= 30 || gameState.level.guards_seq_hi[kid_room_m1] != 0))
    {
      if (roomleave_result == 0)
      {
        // left
        if (gameState.Guard.x >= 91)
          leave = 1;
      }
      else if (roomleave_result == 1)
      {
        // right
        if (gameState.Guard.x < 165)
          leave = 1;
      }
      else if (roomleave_result == 2)
      {
        // up
        if (gameState.Guard.curr_row >= 0)
          leave = 1;
      }
      else
      {
        // down
        if (gameState.Guard.curr_row < 3)
          leave = 1;
      }
    }
    else
    {
      leave = 1;
    }
  }
  else
  {
    leave = 1;
  }
  if (leave)
  {
    leave_guard();
  }
  else
  {
    follow_guard();
  }
}

// seg002:0643
__INLINE__ void  Jaffar_exit()
{
  if (gameState.leveldoor_open == 2)
  {
    get_tile(24, 0, 0);
    trigger_button(0, 0, -1);
  }
}

// seg002:0665
__INLINE__ void  level3_set_chkp()
{
  // Special event: set gameState.checkpoint
  if (gameState.current_level == /*3*/ custom->checkpoint_level && gameState.Char.room == 7 /* TODO: add a custom option */)
  {
    gameState.checkpoint = 1;
    gameState.hitp_beg_lev = gameState.hitp_max;
  }
}

// seg002:0680
__INLINE__ void  sword_disappears()
{
  // Special event: sword disappears
  if (gameState.current_level == 12 && gameState.Char.room == 18)
  {
    get_tile(15, 1, 0);
    curr_room_tiles[curr_tilepos] = tiles_1_floor;
    curr_room_modif[curr_tilepos] = 0; // added, a nonzero modifier may show fake tiles
  }
}

// seg002:06AE
__INLINE__ void  meet_Jaffar()
{
  // Special event: play music
  if (gameState.current_level == 13 && gameState.leveldoor_open == 0 && gameState.Char.room == 3)
  {
    // Special event: Jaffar waits a bit (28/12=2.33 seconds)
    gameState.guard_notice_timer = 28;
  }
}

// seg002:06D3
__INLINE__ void  play_mirr_mus()
{
  // Special event: mirror music
  if (
    gameState.leveldoor_open != 0 &&
    gameState.leveldoor_open != 0x4D && // was the music played already?
    gameState.current_level == /*4*/ custom->mirror_level &&
    gameState.Char.curr_row == /*0*/ custom->mirror_row &&
    gameState.Char.room == 11 /* TODO: add a custom option */
  )
  {
    gameState.leveldoor_open = 0x4D;
  }
}

// seg002:0706
__INLINE__ void  move_0_nothing()
{
  control_shift = 0;
  control_y = 0;
  control_x = 0;
  control_shift2 = 0;
  control_down = 0;
  control_up = 0;
  control_backward = 0;
  control_forward = 0;
}

// seg002:0721
__INLINE__ void  move_1_forward()
{
  control_x = -1;
  control_forward = -1;
}

// seg002:072A
__INLINE__ void  move_2_backward()
{
  control_backward = -1;
  control_x = 1;
}

// seg002:0735
__INLINE__ void  move_3_up()
{
  control_y = -1;
  control_up = -1;
}

// seg002:073E
__INLINE__ void  move_4_down()
{
  control_down = -1;
  control_y = 1;
}

// seg002:0749
__INLINE__ void  move_up_back()
{
  control_up = -1;
  move_2_backward();
}

// seg002:0753
__INLINE__ void  move_down_back()
{
  control_down = -1;
  move_2_backward();
}

// seg002:075D
__INLINE__ void  move_down_forw()
{
  control_down = -1;
  move_1_forward();
}

// seg002:0767
__INLINE__ void  move_6_shift()
{
  control_shift = -1;
  control_shift2 = -1;
}

// seg002:0770
__INLINE__ void  move_7()
{
  control_shift = 0;
}

// seg002:0776
__INLINE__ void  autocontrol_opponent()
{
  uint16_t charid;
  move_0_nothing();
  charid = gameState.Char.charid;
  if (charid == charid_0_kid)
  {
    autocontrol_kid();
  }
  else
  {
    if (gameState.justblocked)
      --gameState.justblocked;
    if (gameState.kid_sword_strike)
      --gameState.kid_sword_strike;
    if (gameState.guard_refrac)
      --gameState.guard_refrac;
    if (charid == charid_24_mouse)
    {
      autocontrol_mouse();
    }
    else if (charid == charid_4_skeleton)
    {
      autocontrol_skeleton();
    }
    else if (charid == charid_1_shadow)
    {
      autocontrol_shadow();
    }
    else if (gameState.current_level == 13)
    {
      autocontrol_Jaffar();
    }
    else
    {
      autocontrol_guard();
    }
  }
}

// seg002:07EB
__INLINE__ void  autocontrol_mouse()
{
  if (gameState.Char.direction == dir_56_none)
  {
    return;
  }
  if (gameState.Char.action == actions_0_stand)
  {
    if (gameState.Char.x >= 200)
    {
      clear_char();
    }
  }
  else
  {
    if (gameState.Char.x < 166)
    {
      seqtbl_offset_char(seq_107_mouse_stand_up_and_go); // mouse
      play_seq();
    }
  }
}

// seg002:081D
__INLINE__ void  autocontrol_shadow()
{
  if (gameState.current_level == 4)
  {
    autocontrol_shadow_level4();
  }
  else if (gameState.current_level == 5)
  {
    autocontrol_shadow_level5();
  }
  else if (gameState.current_level == 6)
  {
    autocontrol_shadow_level6();
  }
  else if (gameState.current_level == 12)
  {
    autocontrol_shadow_level12();
  }
}

// seg002:0850
__INLINE__ void  autocontrol_skeleton()
{
  gameState.Char.sword = sword_2_drawn;
  autocontrol_guard();
}

// seg002:085A
__INLINE__ void  autocontrol_Jaffar()
{
  autocontrol_guard();
}

// seg002:085F
__INLINE__ void  autocontrol_kid()
{
  autocontrol_guard();
}

// seg002:0864
__INLINE__ void  autocontrol_guard()
{
  if (gameState.Char.sword < sword_2_drawn)
  {
    autocontrol_guard_inactive();
  }
  else
  {
    autocontrol_guard_active();
  }
}

// seg002:0876
__INLINE__ void  autocontrol_guard_inactive()
{
  int16_t distance;
  if (gameState.Kid.alive >= 0)
    return;
  distance = char_opp_dist();
  if (Opp.curr_row != gameState.Char.curr_row || (uint16_t)distance < (uint16_t)-8)
  {
    // If gameState.Kid made a sound ...
    if (gameState.is_guard_notice)
    {
      gameState.is_guard_notice = 0;
      if (distance < 0)
      {
        // ... and gameState.Kid is behind Guard, Guard turns around.
        if ((uint16_t)distance < (uint16_t)-4)
        {
          move_4_down();
        }
        return;
      }
    }
    else if (distance < 0)
    {
      return;
    }
  }
  if (gameState.can_guard_see_kid)
  {
    // If Guard can see gameState.Kid, Guard moves to fighting pose.
    if (gameState.current_level != 13 || gameState.guard_notice_timer == 0)
    {
      move_down_forw();
    }
  }
}

// seg002:08DC
__INLINE__ void  autocontrol_guard_active()
{
  int16_t opp_frame;
  int16_t char_frame;
  int16_t distance;
  char_frame = gameState.Char.frame;
  if (char_frame != frame_166_stand_inactive && char_frame >= 150 && gameState.can_guard_see_kid != 1)
  {
    if (gameState.can_guard_see_kid == 0)
    {
      if (gameState.droppedout != 0)
      {
        guard_follows_kid_down();
        // return;
      }
      else if (gameState.Char.charid != charid_4_skeleton)
      {
        move_down_back();
      }
      // return;
    }
    else
    { // gameState.can_guard_see_kid == 2
      opp_frame = Opp.frame;
      distance = char_opp_dist();
      if (distance >= 12 &&
          // frames 102..117: falling and landing
          opp_frame >= frame_102_start_fall_1 && opp_frame < frame_118_stand_up_from_crouch_9 &&
          Opp.action == actions_5_bumped)
      {
        return;
      }
      if (distance < 35)
      {
        if ((gameState.Char.sword < sword_2_drawn && distance < 8) || distance < 12)
        {
          if (gameState.Char.direction == Opp.direction)
          {
            // turn around
            move_2_backward();
            // return;
          }
          else
          {
            move_1_forward();
            // return;
          }
        }
        else
        {
          autocontrol_guard_kid_in_sight(distance);
          // return;
        }
      }
      else
      {
        if (gameState.guard_refrac != 0)
          return;
        if (gameState.Char.direction != Opp.direction)
        {
          // frames 7..14: running
          // frames 34..43: run-jump
          if (opp_frame >= frame_7_run && opp_frame < 15)
          {
            if (distance < 40)
              move_6_shift();
            return;
          }
          else if (opp_frame >= frame_34_start_run_jump_1 && opp_frame < 44)
          {
            if (distance < 50)
              move_6_shift();
            return;
            // return;
          }
        }
        autocontrol_guard_kid_far();
      }
      //...
    }
    //...
  }
}

// seg006:0FC3
__INLINE__ int wall_type(uint8_t tiletype)
{
  switch (tiletype)
  {
  case tiles_4_gate:
  case tiles_7_doortop_with_floor:
  case tiles_12_doortop:
    return 1; // wall at right
  case tiles_13_mirror:
    return 2; // wall at left
  case tiles_18_chomper:
    return 3; // chomper at left
  case tiles_20_wall:
    return 4; // wall at both sides
  default:
    return 0; // no wall
  }
}

// seg002:09CB
__INLINE__ void  autocontrol_guard_kid_far()
{
  if (tile_is_floor(get_tile_infrontof_char()) ||
      tile_is_floor(get_tile_infrontof2_char()))
  {
    move_1_forward();
  }
  else
  {
    move_2_backward();
  }
}

// seg002:09F8
__INLINE__ void  guard_follows_kid_down()
{
  // This is called from autocontrol_guard_active, so char=Guard, Opp=gameState.Kid
  uint16_t opp_action;
  opp_action = Opp.action;
  if (opp_action == actions_2_hang_climb || opp_action == actions_6_hang_straight)
  {
    return;
  }
  if ( // there is wall in front of Guard
    wall_type(get_tile_infrontof_char()) != 0 ||
    (!tile_is_floor(curr_tile2) && ((get_tile(curr_room, tile_col, ++tile_row) == tiles_2_spike ||
                                     // Guard would fall on loose floor
                                     curr_tile2 == tiles_11_loose ||
                                     // ... or wall (?)
                                     wall_type(curr_tile2) != 0 ||
                                     // ... or into a chasm
                                     !tile_is_floor(curr_tile2)) ||
                                    // ... or gameState.Kid is not below
                                    gameState.Char.curr_row + 1 != Opp.curr_row)))
  {
    // don't follow
    gameState.droppedout = 0;
    move_2_backward();
  }
  else
  {
    // follow
    move_1_forward();
  }
}

// seg002:0A93
__INLINE__ void  autocontrol_guard_kid_in_sight(int16_t distance)
{
  if (Opp.sword == sword_2_drawn)
  {
    autocontrol_guard_kid_armed(distance);
  }
  else if (gameState.guard_refrac == 0)
  {
    if (distance < 29)
    {
      move_6_shift();
    }
    else
    {
      move_1_forward();
    }
  }
}

// seg002:0AC1
__INLINE__ void  autocontrol_guard_kid_armed(int16_t distance)
{
  if (distance < 10 || distance >= 29)
  {
    guard_advance();
  }
  else
  {
    guard_block();
    if (gameState.guard_refrac == 0)
    {
      if (distance < 12 || distance >= 29)
      {
        guard_advance();
      }
      else
      {
        guard_strike();
      }
    }
  }
}

// seg002:0AF5
__INLINE__ void  guard_advance()
{
  if (gameState.guard_skill == 0 || gameState.kid_sword_strike == 0)
  {
    auto advProb = version == gameVersion_t::v10 ? custom->advprob10[gameState.guard_skill] : custom->advprob14[gameState.guard_skill];
    if (advProb> prandom(255))
    {
      move_1_forward();
    }
  }
}

// seg002:0B1D
__INLINE__ void  guard_block()
{
  uint16_t opp_frame;
  opp_frame = Opp.frame;
  if (opp_frame == frame_152_strike_2 || opp_frame == frame_153_strike_3 || opp_frame == frame_162_block_to_strike)
  {
    if (gameState.justblocked != 0)
    {
      auto impblockprob = version == gameVersion_t::v10 ? custom->impblockprob10[gameState.guard_skill] : custom->impblockprob14[gameState.guard_skill];
      if (impblockprob > prandom(255))
      {
        move_3_up();
      }
    }
    else
    {
      auto blockprob = version == gameVersion_t::v10 ? custom->blockprob10[gameState.guard_skill] : custom->blockprob14[gameState.guard_skill];
      if (blockprob > prandom(255))
      {
        move_3_up();
      }
    }
  }
}

// seg002:0B73
__INLINE__ void  guard_strike()
{
  uint16_t opp_frame;
  uint16_t char_frame;
  opp_frame = Opp.frame;
  if (opp_frame == frame_169_begin_block || opp_frame == frame_151_strike_1)
    return;
  char_frame = gameState.Char.frame;
  if (char_frame == frame_161_parry || char_frame == frame_150_parry)
  {
    auto restrikeprob = version == gameVersion_t::v10 ? custom->restrikeprob10[gameState.guard_skill] : custom->restrikeprob14[gameState.guard_skill];
    if (restrikeprob > prandom(255))
    {
      move_6_shift();
    }
  }
  else
  {
    auto strikeprob = version == gameVersion_t::v10 ? custom->strikeprob10[gameState.guard_skill] : custom->strikeprob14[gameState.guard_skill];
    if (strikeprob > prandom(255))
    {
      move_6_shift();
    }
  }
}

// seg002:0BCD
__INLINE__ void  hurt_by_sword()
{
  int16_t distance;
  if (gameState.Char.alive >= 0)
    return;
  if (gameState.Char.sword != sword_2_drawn)
  {
    // Being hurt when not in fighting pose means death.
    take_hp(100);
    seqtbl_offset_char(seq_85_stabbed_to_death); // dying (stabbed unarmed)
  loc_4276:
    if (get_tile_behind_char() != 0 ||
        (distance = distance_to_edge_weight()) < 4)
    {
      seqtbl_offset_char(seq_85_stabbed_to_death); // dying (stabbed)
      if (gameState.Char.charid != charid_0_kid &&
          gameState.Char.direction < dir_0_right && // looking left
          (curr_tile2 == tiles_4_gate || get_tile_at_char() == tiles_4_gate))
      {
        gameState.Char.x = x_bump[tile_col - (curr_tile2 != tiles_4_gate) + 5] + 7;
        gameState.Char.x = char_dx_forward(10);
      }
      gameState.Char.y = y_land[gameState.Char.curr_row + 1];
      gameState.Char.fall_y = 0;
    }
    else
    {
      gameState.Char.x = char_dx_forward(distance - 20);
      load_fram_det_col();
      inc_curr_row();
      seqtbl_offset_char(seq_81_kid_pushed_off_ledge); // gameState.Kid/Guard is killed and pushed off the ledge
    }
  }
  else
  {
    // You can't hurt skeletons
    if (gameState.Char.charid != charid_4_skeleton)
    {
      if (take_hp(1))
        goto loc_4276;
    }
    seqtbl_offset_char(seq_74_hit_by_sword); // being hit with sword
    gameState.Char.y = y_land[gameState.Char.curr_row + 1];
    gameState.Char.fall_y = 0;
  }
  // sound 13: gameState.Kid hurt (by sword), sound 12: Guard hurt (by sword)
  play_seq();
}

// seg002:0CD4
__INLINE__ void  check_sword_hurt()
{
  if (gameState.Guard.action == actions_99_hurt)
  {
    if (gameState.Kid.action == actions_99_hurt)
    {
      gameState.Kid.action = actions_1_run_jump;
    }
    loadshad();
    hurt_by_sword();
    saveshad();

    auto refractimer = version == gameVersion_t::v10 ? custom->refractimer10[gameState.guard_skill] : custom->refractimer14[gameState.guard_skill];
    gameState.guard_refrac = refractimer;
  }
  else
  {
    if (gameState.Kid.action == actions_99_hurt)
    {
      loadkid();
      hurt_by_sword();
      savekid();
    }
  }
}

// seg002:0D1A
__INLINE__ void  check_sword_hurting()
{
  int16_t kid_frame;
  kid_frame = gameState.Kid.frame;
  // frames 217..228: go up on stairs
  if (kid_frame != 0 && (kid_frame < frame_219_exit_stairs_3 || kid_frame >= 229))
  {
    loadshad_and_opp();
    check_hurting();
    saveshad_and_opp();
    loadkid_and_opp();
    check_hurting();
    savekid_and_opp();
  }
}

// seg002:0D56
__INLINE__ void  check_hurting()
{
  int16_t opp_frame, char_frame, distance, min_hurt_range;
  if (gameState.Char.sword != sword_2_drawn)
    return;
  if (gameState.Char.curr_row != Opp.curr_row)
    return;
  char_frame = gameState.Char.frame;
  // frames 153..154: poking with sword
  if (char_frame != frame_153_strike_3 && char_frame != frame_154_poking)
    return;
  // If char is poking ...
  distance = char_opp_dist();
  opp_frame = Opp.frame;
  // frames 161 and 150: parrying
  if (distance < 0 || distance >= 29 ||
      (opp_frame != frame_161_parry && opp_frame != frame_150_parry))
  {
    // ... and Opp is not parrying
    // frame 154: poking
    if (gameState.Char.frame == frame_154_poking)
    {
      if (Opp.sword < sword_2_drawn)
      {
        min_hurt_range = 8;
      }
      else
      {
        min_hurt_range = 12;
      }
      distance = char_opp_dist();
      if (distance >= min_hurt_range && distance < 29)
      {
        Opp.action = actions_99_hurt;
      }
    }
  }
  else
  {
    Opp.frame = frame_161_parry;
    if (gameState.Char.charid != charid_0_kid)
    {
      gameState.justblocked = 4;
    }
    seqtbl_offset_char(seq_69_attack_was_parried); // attack was parried
    play_seq();
  }
  if (gameState.Char.direction == dir_56_none)
    return; // Fix looping "sword moving" sound.
  // frame 154: poking
  // frame 161: parrying
  if (gameState.Char.frame == frame_154_poking && Opp.frame != frame_161_parry && Opp.action != actions_99_hurt)
  {
  }
}

// seg002:0E1F
__INLINE__ void  check_skel()
{
  // Special event: skeleton wakes
  if (gameState.current_level == /*3*/ custom->skeleton_level &&
      gameState.Guard.direction == dir_56_none &&
      gameState.drawn_room == /*1*/ custom->skeleton_room &&
      (gameState.leveldoor_open != 0 || !custom->skeleton_require_open_level_door) &&
      (gameState.Kid.curr_col == /*2*/ custom->skeleton_trigger_column_1 ||
       gameState.Kid.curr_col == /*3*/ custom->skeleton_trigger_column_2))
  {
    get_tile(gameState.drawn_room, /*5*/ custom->skeleton_column, /*1*/ custom->skeleton_row);
    if (curr_tile2 == tiles_21_skeleton)
    {
      // erase skeleton
      curr_room_tiles[curr_tilepos] = tiles_1_floor;
      redraw_height = 24;
      ++curr_tilepos;
      gameState.Char.room = gameState.drawn_room;
      gameState.Char.curr_row = /*1*/ custom->skeleton_row;
      gameState.Char.y = y_land[gameState.Char.curr_row + 1];
      gameState.Char.curr_col = /*5*/ custom->skeleton_column;
      gameState.Char.x = x_bump[gameState.Char.curr_col + 5] + 14;
      gameState.Char.direction = dir_FF_left;
      seqtbl_offset_char(seq_88_skel_wake_up); // skel wake up
      play_seq();
      gameState.guard_skill = /*2*/ custom->skeleton_skill;
      gameState.Char.alive = -1;
      gameState.guardhp_max = gameState.guardhp_curr = 3;
      gameState.Char.fall_x = gameState.Char.fall_y = 0;
      gameState.is_guard_notice = gameState.guard_refrac = 0;
      gameState.Char.sword = sword_2_drawn;
      gameState.Char.charid = charid_4_skeleton;
      saveshad();
    }
  }
}

// seg002:0F3F
__INLINE__ void  do_auto_moves(const auto_move_type *moves_ptr)
{
  int16_t demoindex;
  int16_t curr_move;
  if (gameState.demo_time >= 0xFE)
    return;
  ++gameState.demo_time;
  demoindex = gameState.demo_index;
  if (moves_ptr[demoindex].time <= gameState.demo_time)
  {
    ++gameState.demo_index;
  }
  else
  {
    demoindex = gameState.demo_index - 1;
  }
  curr_move = moves_ptr[demoindex].move;
  switch (curr_move)
  {
  case -1:
    break;
  case 0:
    move_0_nothing();
    break;
  case 1:
    move_1_forward();
    break;
  case 2:
    move_2_backward();
    break;
  case 3:
    move_3_up();
    break;
  case 4:
    move_4_down();
    break;
  case 5:
    move_3_up();
    move_1_forward();
    break;
  case 6:
    move_6_shift();
    break;
  case 7:
    move_7();
    break;
  }
}

// seg002:1000
__INLINE__ void  autocontrol_shadow_level4()
{
  if (gameState.Char.room == 4)
  {
    if (gameState.Char.x < 80)
    {
      clear_char();
    }
    else
    {
      move_1_forward();
    }
  }
}

// seg002:101A
__INLINE__ void  autocontrol_shadow_level5()
{
  if (gameState.Char.room == 24)
  {
    if (gameState.demo_time == 0)
    {
      get_tile(24, 1, 0);
      // is the door open?
      if (curr_room_modif[curr_tilepos] < 80)
        return;
      gameState.demo_index = 0;
    }
    do_auto_moves(custom->shad_drink_move);
    if (gameState.Char.x < 15)
    {
      clear_char();
    }
  }
}

// seg002:1064
__INLINE__ void  autocontrol_shadow_level6()
{
  if (gameState.Char.room == 1 &&
      gameState.Kid.frame == frame_43_running_jump_4 && // a frame in run-jump
      gameState.Kid.x < 128)
  {
    move_6_shift();
    move_1_forward();
  }
}

// seg002:1082
__INLINE__ void  autocontrol_shadow_level12()
{
  int16_t opp_frame;
  int16_t xdiff;
  if (gameState.Char.room == 15 && gameState.shadow_initialized == 0)
  {
    if (Opp.x >= 150)
    {
      do_init_shad(/*&*/ custom->init_shad_12, 7 /*fall*/);
      return;
    }
    gameState.shadow_initialized = 1;
  }
  if (gameState.Char.sword >= sword_2_drawn)
  {
    // if the gameState.Kid puts his sword away, the shadow does the same,
    // but only if the shadow was already hurt (?)
    if (gameState.offguard == 0 || gameState.guard_refrac == 0)
    {
      autocontrol_guard_active();
    }
    else
    {
      move_4_down();
    }
    return;
  }
  if (Opp.sword >= sword_2_drawn || gameState.offguard == 0)
  {
    xdiff = 0x7000; // bugfix/workaround
    // This behavior matches the DOS version but not the Apple II source.
    if (gameState.can_guard_see_kid < 2 || (xdiff = char_opp_dist()) >= 90)
    {
      if (xdiff < 0)
      {
        move_2_backward();
      }
      return;
    }
    // Shadow draws his sword
    if (gameState.Char.frame == 15)
    {
      move_down_forw();
    }
    return;
  }
  if (char_opp_dist() < 10)
  {
    // unite with the shadow
    flash_color = color_15_brightwhite; // white
    flash_time = 18;
    // get an extra HP for uniting the shadow
    add_life();
    // time of gameState.Kid-shadow flash
    gameState.united_with_shadow = 42;
    // put the gameState.Kid where the shadow was
    gameState.Char.charid = charid_0_kid;
    savekid();
    // remove the shadow
    clear_char();
    return;
  }
  if (gameState.can_guard_see_kid == 2)
  {
    // If gameState.Kid runs to shadow, shadow runs to gameState.Kid.
    opp_frame = Opp.frame;
    // frames 1..14: running
    // frames 121..132: stepping
    if ((opp_frame >= frame_3_start_run && opp_frame < frame_15_stand) ||
        (opp_frame >= frame_127_stepping_7 && opp_frame < 133))
    {
      move_1_forward();
    }
  }
}

// seg003:0000
__INLINE__ void  init_game(int level)
{
  load_kid_sprite();
  text_time_remaining = 0;
  text_time_total = 0;
  gameState.checkpoint = 0;
  upside_down = 0; // N.B. upside_down is also reset in set_start_pos()
  resurrect_time = 0;
  if (!dont_reset_time)
  {
    gameState.hitp_beg_lev = custom->start_hitp; // 3
  }

  gameState.need_level1_music = (level == /*1*/ custom->intro_music_level);
  play_level(level);
}

// seg003:005C
__INLINE__ void  play_level(int level_number)
{
  if (level_number == custom->copyprot_level)
  {
    level_number = 15;
  }
  for (;;)
  {
    if (demo_mode && level_number > 2)
    {
      start_level = -1;
      need_quotes = 1;
      start_game();
    }
    if (level_number != gameState.current_level)
    {
    }
    if (level_number != gameState.current_level)
    {
      load_lev_spr(level_number);
    }
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
    flash_time = 0;
    gameState.leveldoor_open = 0;
    gameState.demo_index = 0;
    gameState.demo_time = 0;
    gameState.guardhp_curr = 0;
    hitp_delta = 0;
    gameState.Guard.charid = charid_2_guard;
    gameState.Guard.direction = dir_56_none;
    do_startpos();
    gameState.have_sword = /*(level_number != 1)*/ (level_number == 0 || level_number >= custom->have_sword_from_level);
    find_start_level_door();
    // busy waiting?
    draw_level_first();
    level_number = play_level_2();
    // hacked...
    if (level_number == custom->copyprot_level && !demo_mode)
    {
      level_number = 15;
    }
    else
    {
      if (level_number == 16)
      {
        level_number = custom->copyprot_level;
        custom->copyprot_level = -1;
      }
    }
  }
}

// seg003:01A3
__INLINE__ void  do_startpos()
{
  uint16_t x;
  // Special event: start at gameState.checkpoint
  if (gameState.current_level == /*3*/ custom->checkpoint_level && gameState.checkpoint)
  {
    gameState.level.start_dir = /*dir_FF_left*/ custom->checkpoint_respawn_dir;
    gameState.level.start_room = /*2*/ custom->checkpoint_respawn_room;
    gameState.level.start_pos = /*6*/ custom->checkpoint_respawn_tilepos;
    // Special event: remove loose floor
    get_tile(/*7*/ custom->checkpoint_clear_tile_room,
             /*4*/ custom->checkpoint_clear_tile_col,
             /*0*/ custom->checkpoint_clear_tile_row);
    curr_room_tiles[curr_tilepos] = tiles_0_empty;
  }
  next_room = gameState.Char.room = gameState.level.start_room;
  x = gameState.level.start_pos;
  gameState.Char.curr_col = x % 10;
  gameState.Char.curr_row = x / 10;
  gameState.Char.x = x_bump[gameState.Char.curr_col + 5] + 14;
  // Start in the opposite direction (and turn into the correct one).
  gameState.Char.direction = ~gameState.level.start_dir;
  if (seamless == 0)
  {
    if (gameState.current_level != 0)
    {
      x = gameState.hitp_beg_lev;
    }
    else
    {
      // HP on demo level
      x = /*4*/ custom->demo_hitp;
    }
    gameState.hitp_max = gameState.hitp_curr = x;
  }
  if (/*gameState.current_level == 1*/ custom->tbl_entry_pose[gameState.current_level] == 1)
  {
    // Special event: press button + falling entry
    get_tile(5, 2, 0);
    trigger_button(0, 0, -1);
    seqtbl_offset_char(seq_7_fall); // fall
  }
  else if (/*gameState.current_level == 13*/ custom->tbl_entry_pose[gameState.current_level] == 2)
  {
    // Special event: running entry
    seqtbl_offset_char(seq_84_run); // run
  }
  else
  {
    seqtbl_offset_char(seq_5_turn); // turn
  }
  set_start_pos();
}

// seg003:028A
__INLINE__ void  set_start_pos()
{
  gameState.Char.y = y_land[gameState.Char.curr_row + 1];
  gameState.Char.alive = -1;
  gameState.Char.charid = charid_0_kid;
  gameState.is_screaming = 0;
  knock = 0;
  upside_down = custom->start_upside_down; // 0
  gameState.is_feather_fall = 0;
  gameState.Char.fall_y = 0;
  gameState.Char.fall_x = 0;
  gameState.offguard = 0;
  gameState.Char.sword = sword_0_sheathed;
  gameState.droppedout = 0;
  play_seq();
  if (gameState.current_level == /*7*/ custom->falling_entry_level && gameState.Char.room == /*17*/ custom->falling_entry_room)
  {
    // Special event: level 7 falling entry
    // level 7, room 17: show room below
    goto_other_room(3);
  }
  savekid();
}

// seg003:02E6
__INLINE__ void  find_start_level_door()
{
  int16_t tilepos;
  get_room_address(gameState.Kid.room);
  for (tilepos = 0; tilepos < 30; ++tilepos)
  {
    if ((curr_room_tiles[tilepos] & 0x1F) == tiles_16_level_door_left)
    {
      start_level_door(gameState.Kid.room, tilepos);
    }
  }
}

// seg003:0326
__INLINE__ void  draw_level_first()
{
  next_room = gameState.Kid.room;
  check_the_end();
  if (custom->tbl_level_type[gameState.current_level])
  {
    gen_palace_wall_colors();
  }
  redraw_screen(0);
}

// seg003:037B
__INLINE__ void  redraw_screen(int drawing_different_room)
{
  clear_kbd_buf();
  gameState.exit_room_timer = 2;
}

// seg003:04F8
__INLINE__ int play_level_2()
{
  while (1)
  { // main loop
    guardhp_delta = 0;
    hitp_delta = 0;
    timers();
    play_frame();

    if (is_restart_level)
    {
      is_restart_level = 0;
      return gameState.current_level;
    }
    else
    {
      if (gameState.next_level == gameState.current_level)
      {
      }
      else
      {
        gameState.hitp_beg_lev = gameState.hitp_max;
        gameState.checkpoint = 0;

        return gameState.next_level;
      }
    }
  }
}

// seg003:0706
__INLINE__ void  check_knock()
{
  if (knock)
  {
    do_knock(gameState.Char.room, gameState.Char.curr_row - (knock > 0));
    knock = 0;
  }
}

// seg003:0735
__INLINE__ void  timers()
{
  if (gameState.united_with_shadow > 0)
  {
    --gameState.united_with_shadow;
    if (gameState.united_with_shadow == 0)
    {
      --gameState.united_with_shadow;
    }
  }
  if (gameState.guard_notice_timer > 0)
  {
    --gameState.guard_notice_timer;
  }
  if (resurrect_time > 0)
  {
    --resurrect_time;
  }

  if (gameState.is_feather_fall) gameState.is_feather_fall++;

  if (gameState.is_feather_fall > 225)
  {
    gameState.is_feather_fall = 0;
  }

  // Special event: mouse
  if (gameState.current_level == /*8*/ custom->mouse_level && gameState.Char.room == /*16*/ custom->mouse_room && gameState.leveldoor_open)
  {
    ++gameState.leveldoor_open;
    // time before mouse comes: 150/12=12.5 seconds
    if (gameState.leveldoor_open == /*150*/ custom->mouse_delay)
    {
      do_mouse();
    }
  }
}

// seg003:0798
__INLINE__ void  check_mirror()
{
  if (gameState.jumped_through_mirror == -1)
  {
    jump_through_mirror();
  }
}

// seg003:080A
__INLINE__ void  jump_through_mirror()
{
  gameState.jumped_through_mirror = 0;
  gameState.Char.charid = charid_1_shadow;
  gameState.guardhp_max = gameState.guardhp_curr = gameState.hitp_max;
  gameState.hitp_curr = 1;
}

// seg003:085B
__INLINE__ void  check_mirror_image()
{
  int16_t distance;
  int16_t xpos;
  xpos = x_bump[gameState.Char.curr_col + 5] + 10;
  distance = distance_to_edge_weight();
  if (gameState.Char.direction >= dir_0_right)
  {
    distance = (~distance) + 14;
  }
  distance_mirror = distance - 2;
  gameState.Char.x = (xpos << 1) - gameState.Char.x;
  gameState.Char.direction = ~gameState.Char.direction;
}

// seg003:08AA
__INLINE__ void  bump_into_opponent()
{
  // This is called from play_kid_frame, so char=gameState.Kid, Opp=Guard
  int16_t distance;
  if (gameState.can_guard_see_kid >= 2 &&
      gameState.Char.sword == sword_0_sheathed && // gameState.Kid must not be in fighting pose
      Opp.sword != sword_0_sheathed &&            // but Guard must
      Opp.action < 2 &&
      gameState.Char.direction != Opp.direction // must be facing toward each other
  )
  {
    distance = char_opp_dist();
    if (std::abs(distance) <= 15)
    {
      gameState.Char.y = y_land[gameState.Char.curr_row + 1];
      gameState.Char.fall_y = 0;
      seqtbl_offset_char(seq_47_bump); // bump into opponent
      play_seq();
    }
  }
}

// seg003:0913
__INLINE__ void  pos_guards()
{
  int16_t guard_tile;
  int16_t room1;
  for (room1 = 0; room1 < 24; ++room1)
  {
    guard_tile = gameState.level.guards_tile[room1];
    if (guard_tile < 30)
    {
      gameState.level.guards_x[room1] = x_bump[guard_tile % 10 + 5] + 14;
      gameState.level.guards_seq_hi[room1] = 0;
    }
  }
}

// seg003:0A99
__INLINE__ uint8_t get_tile_at_kid(int xpos)
{
  return get_tile(gameState.Kid.room, get_tile_div_mod_m7(xpos), gameState.Kid.curr_row);
}

// seg003:0959
__INLINE__ void  check_can_guard_see_kid()
{
  /*
Possible results in gameState.can_guard_see_kid:
0: Guard can't see gameState.Kid
1: Guard can see gameState.Kid, but won't come
2: Guard can see gameState.Kid, and will come
*/
  int16_t kid_frame;
  int16_t left_pos;
  int16_t temp;
  int16_t right_pos;
  kid_frame = gameState.Kid.frame;
  if (gameState.Guard.charid == charid_24_mouse)
  {
    // If the prince is fighting a guard, and the player does a quickload to a state where the prince is  the mouse, the prince would draw the sword.
    // The following line prevents this.
    gameState.can_guard_see_kid = 0;
    return;
  }
  if ((gameState.Guard.charid != charid_1_shadow || gameState.current_level == 12) &&
      // frames 217..228: going up on stairs
      kid_frame != 0 && (kid_frame < frame_219_exit_stairs_3 || kid_frame >= 229) &&
      gameState.Guard.direction != dir_56_none && gameState.Kid.alive < 0 && gameState.Guard.alive < 0 && gameState.Kid.room == gameState.Guard.room && gameState.Kid.curr_row == gameState.Guard.curr_row)
  {
    gameState.can_guard_see_kid = 2;
    left_pos = x_bump[gameState.Kid.curr_col + 5] + 7;
    right_pos = x_bump[gameState.Guard.curr_col + 5] + 7;
    if (left_pos > right_pos)
    {
      temp = left_pos;
      left_pos = right_pos;
      right_pos = temp;
    }
    // A chomper is on the left side of a tile, so it doesn't count.
    if (get_tile_at_kid(left_pos) == tiles_18_chomper)
    {
      left_pos += 14;
    }
    // A gate is on the right side of a tile, so it doesn't count.
    if (get_tile_at_kid(right_pos) == tiles_4_gate)
    {
      right_pos -= 14;
    }

    if (right_pos >= left_pos)
    {
      while (left_pos <= right_pos)
      {
        // Can't see through these tiles.
        if (get_tile_at_kid(left_pos) == tiles_20_wall ||
            curr_tile2 == tiles_7_doortop_with_floor ||
            curr_tile2 == tiles_12_doortop)
        {
          gameState.can_guard_see_kid = 0;
          return;
        }
        // Can see through these, but won't go through them.
        if (curr_tile2 == tiles_11_loose ||
            curr_tile2 == tiles_18_chomper ||
            (curr_tile2 == tiles_4_gate && curr_room_modif[curr_tilepos] < 112) ||
            !tile_is_floor(curr_tile2))
        {
          gameState.can_guard_see_kid = 1;
        }
        left_pos += 14;
      }
    }
  }
  else
  {
    gameState.can_guard_see_kid = 0;
  }
}

// seg003:0ABA
__INLINE__ void  do_mouse()
{
  loadkid();
  gameState.Char.charid = /*charid_24_mouse*/ custom->mouse_object;
  gameState.Char.x = /*200*/ custom->mouse_start_x;
  gameState.Char.curr_row = 0;
  gameState.Char.y = y_land[gameState.Char.curr_row + 1];
  gameState.Char.alive = -1;
  gameState.Char.direction = dir_FF_left;
  gameState.guardhp_curr = 1;
  seqtbl_offset_char(seq_105_mouse_forward); // mouse forward
  play_seq();
  saveshad();
}

// seg006:0006
__INLINE__ int get_tile(const int room, const int col, const int row)
{
  curr_room = room;
  tile_col = col;
  tile_row = row;

  while (tile_col < 0)
  {
    tile_col += 10;
    if (curr_room) curr_room = gameState.level.roomlinks[curr_room - 1].left;
  }
  while (tile_col >= 10)
  {
    tile_col -= 10;
    if (curr_room) curr_room = gameState.level.roomlinks[curr_room - 1].right;
  }
  while (tile_row < 0)
  {
    tile_row += 3;
    if (curr_room) curr_room = gameState.level.roomlinks[curr_room - 1].up;
  }
  while (tile_row >= 3)
  {
    tile_row -= 3;
    if (curr_room) curr_room = gameState.level.roomlinks[curr_room - 1].down;
  }

  // bugfix: check_chomped_kid may call with room = -1
  if (curr_room > 0 && curr_room <= 24)
  {
    get_room_address(curr_room);
    curr_tilepos = tbl_line[tile_row] + tile_col;
    curr_tile2 = curr_room_tiles[curr_tilepos] & 0x1F;
  }
  else
  {
    // wall in room 0
    curr_tile2 = custom->level_edge_hit_tile; // tiles_20_wall
  }

  return curr_tile2;
}

// seg006:00EC
__INLINE__ int get_tilepos(int tile_col, int tile_row)
{
  if (tile_row < 0)
  {
    return -(tile_col + 1);
  }
  else if (tile_row >= 3 || tile_col >= 10 || tile_col < 0)
  {
    return 30;
  }
  else
  {
    return tbl_line[tile_row] + tile_col;
  }
}

// seg006:01F5
__INLINE__ int16_t dx_weight()
{
  int8_t var_2;
  var_2 = cur_frame.dx - (cur_frame.flags & FRAME_WEIGHT_X);
  return char_dx_forward(var_2);
}

// seg006:0124
__INLINE__ int get_tilepos_nominus(int tile_col, int tile_row)
{
  int16_t var_2;
  var_2 = get_tilepos(tile_col, tile_row);
  if (var_2 < 0)
    return 30;
  else
    return var_2;
}

// seg006:0144
__INLINE__ void  load_fram_det_col()
{
  load_frame();
  determine_col();
}

// seg006:014D
__INLINE__ void  determine_col()
{
  gameState.Char.curr_col = get_tile_div_mod_m7(dx_weight());
}

__INLINE__ void  get_frame_internal(const frame_type frame_table[], int frame, const char *frame_table_name, int count)
{
  if (frame >= 0 && frame < count)
  {
    cur_frame = frame_table[frame];
  }
  else
  {
    // printf("Tried to use %s[%d], not in 0..%d\n", frame_table_name, frame, count - 1);
    static const frame_type blank_frame = {255, 0, 0, 0, 0};
    cur_frame = blank_frame;
  }
}

// seg006:015A
__INLINE__ void  load_frame()
{
  int16_t frame;
  int16_t add_frame;
  frame = gameState.Char.frame;
  add_frame = 0;
  switch (gameState.Char.charid)
  {
  case charid_0_kid:
  case charid_24_mouse:
  use_table_kid:
    get_frame_internal(frame_table_kid, frame, "frame_table_kid", __QS__COUNT(frame_table_kid));
    break;
  case charid_2_guard:
  case charid_4_skeleton:
    if (frame >= 102 && frame < 107)
      add_frame = 70;
    goto use_table_guard;
  case charid_1_shadow:
    if (frame < 150 || frame >= 190)
      goto use_table_kid;
  use_table_guard:
    get_frame_internal(frame_tbl_guard, frame + add_frame - 149, "frame_tbl_guard", __QS__COUNT(frame_tbl_guard));
    break;
  case charid_5_princess:
  case charid_6_vizier:
    //  use_table_cutscene:
    get_frame_internal(frame_tbl_cuts, frame, "frame_tbl_cuts", __QS__COUNT(frame_tbl_cuts));
    break;
  }
}

// seg006:0213
__INLINE__ int char_dx_forward(int delta_x)
{
  if (gameState.Char.direction < dir_0_right)
  {
    delta_x = -delta_x;
  }
  return delta_x + gameState.Char.x;
}

// seg006:0234
__INLINE__ int obj_dx_forward(int delta_x)
{
  if (obj_direction < dir_0_right)
  {
    delta_x = -delta_x;
  }
  obj_x += delta_x;
  return obj_x;
}

// seg006:0254
__INLINE__ void  play_seq()
{
  for (;;)
  {
    uint8_t item = *(__QS_SEQTBL_0 + gameState.Char.curr_seq++);
    switch (item)
    {
    case SEQ_DX: // dx
      gameState.Char.x = char_dx_forward(*(__QS_SEQTBL_0 + gameState.Char.curr_seq++));
      break;
    case SEQ_DY: // dy
      gameState.Char.y += *(__QS_SEQTBL_0 + gameState.Char.curr_seq++);
      break;
    case SEQ_FLIP: // flip
      gameState.Char.direction = ~gameState.Char.direction;
      break;
    case SEQ_JMP_IF_FEATHER: // jump if feather
      if (!gameState.is_feather_fall)
      {
        ++gameState.Char.curr_seq;
        ++gameState.Char.curr_seq;
        break;
      }
      // fallthrough!
    case SEQ_JMP: // jump
      gameState.Char.curr_seq = *(const uint16_t *)(__QS_SEQTBL_0 + gameState.Char.curr_seq);
      break;
    case SEQ_UP: // up
      --gameState.Char.curr_row;
      start_chompers();
      break;
    case SEQ_DOWN: // down
      inc_curr_row();
      start_chompers();
      break;
    case SEQ_ACTION: // action
      gameState.Char.action = *(__QS_SEQTBL_0 + gameState.Char.curr_seq++);
      break;
    case SEQ_SET_FALL: // set fall
      gameState.Char.fall_x = *(__QS_SEQTBL_0 + gameState.Char.curr_seq++);
      gameState.Char.fall_y = *(__QS_SEQTBL_0 + gameState.Char.curr_seq++);
      break;
    case SEQ_KNOCK_UP: // knock up
      knock = 1;
      break;
    case SEQ_KNOCK_DOWN: // knock down
      knock = -1;
      break;
    case SEQ_SOUND: // sound
      switch (*(__QS_SEQTBL_0 + gameState.Char.curr_seq++))
      {
      case SND_SILENT: // no sound actually played, but guards still notice the kid
        gameState.is_guard_notice = 1;
        break;
      case SND_FOOTSTEP: // feet
        gameState.is_guard_notice = 1;
        break;
      case SND_BUMP: // bump
        gameState.is_guard_notice = 1;
        break;
      case SND_DRINK: // drink
        break;
      case SND_LEVEL: // level
        if (is_sound_on)
        {
          if (gameState.current_level == 4)
          {
          }
          else if (gameState.current_level != 13 && gameState.current_level != 15)
          {
          }
        }
        break;
      }
      break;
    case SEQ_END_LEVEL: // end level
      ++gameState.next_level;
      break;
    case SEQ_GET_ITEM: // get item
      if (*(__QS_SEQTBL_0 + gameState.Char.curr_seq++) == 1)
      {
        proc_get_object();
      }
      break;
    case SEQ_DIE: // nop
      break;
    default:
      gameState.Char.frame = item;
      // if (gameState.Char.frame == 185) gameState.Char.frame = 185;
      return;
    }
  }
}

// seg006:03DE
__INLINE__ int get_tile_div_mod_m7(int xpos)
{
  return get_tile_div_mod(xpos - 7);
}

// seg006:03F0
__INLINE__ int get_tile_div_mod(const int xpos)
{
  // Determine tile column (xh) and the position within the tile (xl) from xpos.

  // DOS PoP does this:
  // obj_xl = tile_mod_tbl[xpos];
  // return tile_div_tbl[xpos];

  // xpos uses a coordinate system in which the left edge of the screen is 58, and each tile is 14 units wide.
  int x = xpos - 58;
  int xl = x % 14;
  int xh = x / 14;
  if (xl < 0)
  {
    // Integer division rounds towards zero, but we want to round down.
    --xh;
    // Modulo returns a negative number if x is negative, but we want 0 <= xl < 14.
    xl += 14;
  }

  // For compatibility with the DOS version, we allow for overflow access to these tables
  // Considering the case of negative overflow
  if (xpos < 0)
  {
    // In this case DOS PoP reads the bytes directly before tile_div_tbl[] and tile_mod_tbl[] in the memory.
    // Here we simulate these reads.
    // Before tile_mod_tbl[] is tile_div_tbl[], and before tile_div_tbl[] are the following bytes:
    static const uint8_t bogus[] = {0x02, 0x00, 0x41, 0x00, 0x80, 0x00, 0xBF, 0x00, 0xFE, 0x00, 0xFF, 0x01, 0x01, 0xFF, 0xC4, 0xFF, 0x03, 0x00, 0x42, 0x00, 0x81, 0x00, 0xC0, 0x00, 0xF8, 0xFF, 0x37, 0x00, 0x76, 0x00, 0xB5, 0x00, 0xF4, 0x00};
    if (__QS__COUNT(bogus) + xpos >= 0)
    {
      xh = bogus[__QS__COUNT(bogus) + xpos];               // simulating tile_div_tbl[xpos]
      xl = tile_div_tbl[__QS__COUNT(tile_div_tbl) + xpos]; // simulating tile_mod_tbl[xpos]
    }
    else
    {
      printf("xpos = %d (< %d) out of range for simulation of index overflow!\n", xpos, -(int)__QS__COUNT(bogus));
    }
  }

  // Considering the case of positive overflow
  int tblSize = 256;

  if (xpos >= tblSize)
  {
    // In this case DOS PoP reads the bytes directly after tile_div_tbl[], that is: and tile_mod_tbl[]
    // Here we simulate these reads.
    // After tile_mod_tbl[] there are the following bytes:
    static const uint8_t bogus[] = {0xF4, 0x02, 0x10, 0x1E, 0x2C, 0x3A, 0x48, 0x56, 0x64, 0x72, 0x80, 0x8E, 0x9C, 0xAA, 0xB8, 0xC6, 0xD4, 0xE2, 0xF0, 0xFE, 0x00, 0x0A, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x0D, 0x00, 0x00, 0x00, 0x00};
    if ((int8_t)xpos - (int8_t)tblSize < (int8_t)__QS__COUNT(bogus))
    {
      xh = tile_mod_tbl[xpos - tblSize]; // simulating tile_div_tbl[xpos]
      xl = bogus[xpos - tblSize];        // simulating tile_mod_tbl[xpos]
    }
    else
    {
      printf("xpos = %d (> %d) out of range for simulation of index overflow!\n", xpos, (int)__QS__COUNT(bogus) + tblSize);
    }
  }

  obj_xl = xl;
  return xh;
}

// seg006:0433
__INLINE__ int y_to_row_mod4(int ypos)
{
  return (ypos + 60) / 63 % 4 - 1;
}

// seg006:044F
__INLINE__ void  loadkid()
{
  gameState.Char = gameState.Kid;
}

// seg006:0464
__INLINE__ void  savekid()
{
  gameState.Kid = gameState.Char;
}

// seg006:0479
__INLINE__ void  loadshad()
{
  gameState.Char = gameState.Guard;
}

// seg006:048E
__INLINE__ void  saveshad()
{
  gameState.Guard = gameState.Char;
}

// seg006:04A3
__INLINE__ void  loadkid_and_opp()
{
  loadkid();
  Opp = gameState.Guard;
}

// seg006:04BC
__INLINE__ void  savekid_and_opp()
{
  savekid();
  gameState.Guard = Opp;
}

// seg006:04D5
__INLINE__ void  loadshad_and_opp()
{
  loadshad();
  Opp = gameState.Kid;
}

// seg006:04EE
__INLINE__ void  saveshad_and_opp()
{
  saveshad();
  gameState.Kid = Opp;
}

// seg006:0507
__INLINE__ void  reset_obj_clip()
{
  obj_clip_left = 0;
  obj_clip_top = 0;
  obj_clip_right = 320;
  obj_clip_bottom = 192;
}

// seg006:051C
__INLINE__ void  x_to_xh_and_xl(int xpos, int8_t *xh_addr, int8_t *xl_addr)
{
  if (xpos < 0)
  {
    *xh_addr = -((std::abs(-xpos) >> 3) + 1);
    *xl_addr = -((-xpos - 1) % 8 - 7);
  }
  else
  {
    *xh_addr = std::abs(xpos) >> 3;
    *xl_addr = xpos % 8;
  }
}

// seg006:057C
__INLINE__ void  fall_accel()
{
  if (gameState.Char.action == actions_4_in_freefall)
  {
    if (gameState.is_feather_fall)
    {
      ++gameState.Char.fall_y;
      if (gameState.Char.fall_y > 4)
        gameState.Char.fall_y = 4;
    }
    else
    {
      gameState.Char.fall_y += 3;
      if (gameState.Char.fall_y > 33)
        gameState.Char.fall_y = 33;
    }
  }
}

// seg006:05AE
__INLINE__ void  fall_speed()
{
  gameState.Char.y += gameState.Char.fall_y;
  if (gameState.Char.action == actions_4_in_freefall)
  {
    gameState.Char.x = char_dx_forward(gameState.Char.fall_x);
    load_fram_det_col();
  }
}

// seg006:05CD
__INLINE__ void  check_action()
{
  int16_t frame;
  int16_t action;
  action = gameState.Char.action;
  frame = gameState.Char.frame;
  // frame 109: crouching
  if (action == actions_6_hang_straight ||
      action == actions_5_bumped)
  {
    if (frame == frame_109_crouch)
    {
      check_on_floor();
    }
  }
  else if (action == actions_4_in_freefall)
  {
    do_fall();
  }
  else if (action == actions_3_in_midair)
  {
    // frame 102..106: start fall + fall
    if (frame >= frame_102_start_fall_1 && frame < frame_106_fall)
    {
      check_grab();
    }
  }
  else if (action != actions_2_hang_climb)
  {
    check_on_floor();
  }
}

// seg006:0628
__INLINE__ int tile_is_floor(int tiletype)
{
  switch (tiletype)
  {
  case tiles_0_empty:
  case tiles_9_bigpillar_top:
  case tiles_12_doortop:
  case tiles_20_wall:
  case tiles_26_lattice_down:
  case tiles_27_lattice_small:
  case tiles_28_lattice_left:
  case tiles_29_lattice_right:
    return 0;
  default:
    return 1;
  }
}

// seg006:0658
__INLINE__ void  check_spiked()
{
  int16_t harmful;
  int16_t frame;
  frame = gameState.Char.frame;
  if (get_tile(gameState.Char.room, gameState.Char.curr_col, gameState.Char.curr_row) == tiles_2_spike)
  {
    harmful = is_spike_harmful();
    // frames 7..14: running
    // frames 34..39: start run-jump
    // frame 43: land from run-jump
    // frame 26: lang from standing jump
    if (
      (harmful >= 2 && ((frame >= frame_7_run && frame < 15) || (frame >= frame_34_start_run_jump_1 && frame < 40))) ||
      ((frame == frame_43_running_jump_4 || frame == frame_26_standing_jump_11) && harmful != 0))
    {
      spiked();
    }
  }
}

// seg006:06BD
__INLINE__ int take_hp(int count)
{
  uint16_t dead;
  dead = 0;
  if (gameState.Char.charid == charid_0_kid)
  {
    if (count >= gameState.hitp_curr)
    {
      hitp_delta = -gameState.hitp_curr;
      dead = 1;
    }
    else
    {
      hitp_delta = -count;
    }
  }
  else
  {
    if (count >= gameState.guardhp_curr)
    {
      guardhp_delta = -gameState.guardhp_curr;
      dead = 1;
    }
    else
    {
      guardhp_delta = -count;
    }
  }
  return dead;
}

// seg006:070D
__INLINE__ int get_tile_at_char()
{
  return get_tile(gameState.Char.room, gameState.Char.curr_col, gameState.Char.curr_row);
}

// Get an image, with index and NULL checks.
__INLINE__ image_type *get_image(int16_t chtab_id, int id)
{
  if ((ssize_t)chtab_id < 0 || (ssize_t)chtab_id > (ssize_t)__QS__COUNT(chtab_addrs))
  {
    //  printf("Tried to use chtab %d not in 0..%d\n", chtab_id, (int)__QS__COUNT(chtab_addrs));
    return NULL;
  }
  chtab_type *chtab = chtab_addrs[chtab_id];
  if (chtab == NULL)
  {
    //  printf("Tried to use null chtab %d\n", chtab_id);
    return NULL;
  }
  if (id < 0 || id >= chtab->n_images)
  {
    //  if (id != 255) printf("Tried to use image %d of chtab %d, not in 0..%d\n", id, chtab_id, chtab->n_images-1);
    return NULL;
  }
  return chtab->images[id];
}

// seg006:0723
__INLINE__ void  set_char_collision()
{
  image_type *image = get_image(obj_chtab, obj_id);
  if (image == NULL)
  {
    char_width_half = 0;
    char_height = 0;
  }
  else
  {
    char_width_half = (image->/*width*/ w + 1) / 2;
    char_height = image->/*height*/ h;
  }
  char_x_left = obj_x / 2 + 58;
  if (gameState.Char.direction >= dir_0_right)
  {
    char_x_left -= char_width_half;
  }
  char_x_left_coll = char_x_left;
  char_x_right_coll = char_x_right = char_x_left + char_width_half;
  char_top_y = obj_y - char_height + 1;
  if (char_top_y >= 192)
  {
    char_top_y = 0;
  }
  char_top_row = y_to_row_mod4(char_top_y);
  char_bottom_row = y_to_row_mod4(obj_y);
  if (char_bottom_row == -1)
  {
    char_bottom_row = 3;
  }
  char_col_left = std::max(get_tile_div_mod(char_x_left), 0);
  char_col_right = std::min(get_tile_div_mod(char_x_right), 9);
  if (cur_frame.flags & FRAME_THIN)
  {
    // "thin" this frame for collision detection
    char_x_left_coll += 4;
    char_x_right_coll -= 4;
  }
}

// seg006:0815
__INLINE__ void  check_on_floor()
{
  if (cur_frame.flags & FRAME_NEEDS_FLOOR)
  {
    if (get_tile_at_char() == tiles_20_wall)
    {
      in_wall();
    }
    if (!tile_is_floor(curr_tile2))
    {
      // Special event: floors appear
      if (gameState.current_level == 12 &&
          gameState.united_with_shadow < 0 &&
          gameState.Char.curr_row == 0 &&
          (gameState.Char.room == 2 || (gameState.Char.room == 13 && tile_col >= 6)))
      {
        curr_room_tiles[curr_tilepos] = tiles_1_floor;
        ++curr_tilepos;
      }
      else
      {
        start_fall();
      }
    }
  }
}

// seg006:08B9
__INLINE__ void  start_fall()
{
  int16_t frame;
  uint16_t seq_id;
  frame = gameState.Char.frame;
  gameState.Char.sword = sword_0_sheathed;
  inc_curr_row();
  start_chompers();
  fall_frame = frame;
  if (frame == frame_9_run)
  {
    // frame 9: run
    seq_id = seq_7_fall; // fall (when?)
  }
  else if (frame == frame_13_run)
  {
    // frame 13: run
    seq_id = seq_19_fall; // fall (when?)
  }
  else if (frame == frame_26_standing_jump_11)
  {
    // frame 26: land after standing jump
    seq_id = seq_18_fall_after_standing_jump; // fall after standing jump
  }
  else if (frame == frame_44_running_jump_5)
  {
    // frame 44: land after running jump
    seq_id = seq_21_fall_after_running_jump; // fall after running jump
  }
  else if (frame >= frame_81_hangdrop_1 && frame < 86)
  {
    // frame 81..85: land after jump up
    seq_id = seq_19_fall; // fall after jumping up
    gameState.Char.x = char_dx_forward(5);
    load_fram_det_col();
  }
  else if (frame >= 150 && frame < 180)
  {
    // frame 150..179: with sword + fall + dead
    if (gameState.Char.charid == charid_2_guard)
    {
      if (gameState.Char.curr_row == 3 && gameState.Char.curr_col == 10)
      {
        clear_char();
        return;
      }
      if (gameState.Char.fall_x < 0)
      {
        seq_id = seq_82_guard_pushed_off_ledge; // Guard is pushed off the ledge
        if (gameState.Char.direction < dir_0_right && distance_to_edge_weight() <= 7)
        {
          gameState.Char.x = char_dx_forward(-5);
        }
      }
      else
      {
        gameState.droppedout = 0;
        seq_id = seq_83_guard_fall; // fall after forwarding with sword
      }
    }
    else
    {
      gameState.droppedout = 1;
      if (gameState.Char.direction < dir_0_right && distance_to_edge_weight() <= 7)
      {
        gameState.Char.x = char_dx_forward(-5);
      }
      seq_id = seq_81_kid_pushed_off_ledge; // fall after backing with sword / gameState.Kid is pushed off the ledge
    }
  }
  else
  {
    seq_id = seq_7_fall; // fall after stand, run, step, crouch
  }
  seqtbl_offset_char(seq_id);
  play_seq();
  load_fram_det_col();
  if (get_tile_at_char() == tiles_20_wall)
  {
    in_wall();
    return;
  }
  int tile = get_tile_infrontof_char();
  if (tile == tiles_20_wall)
  {
    if (fall_frame != 44 || distance_to_edge_weight() >= 6)
    {
      gameState.Char.x = char_dx_forward(-1);
    }
    else
    {
      seqtbl_offset_char(seq_104_start_fall_in_front_of_wall); // start fall (when?)
      play_seq();
    }
    load_fram_det_col();
  }
}

// seg006:0A19
__INLINE__ void  check_grab()
{
  uint16_t old_x;

  if (control_shift < 0 &&                              // press Shift to grab
      gameState.Char.fall_y < __QS__MAX_GRAB_FALLING_SPEED && // you can't grab if you're falling too fast ...
      gameState.Char.alive < 0 &&                       // ... or dead
      (uint16_t)y_land[gameState.Char.curr_row + 1] <= (uint16_t)(gameState.Char.y + 25))
  {
    // printf("Falling speed: %d\t x: %d\n", gameState.Char.fall_y, gameState.Char.x);
    old_x = gameState.Char.x;
    gameState.Char.x = char_dx_forward(-8);
    load_fram_det_col();
    if (!can_grab_front_above())
    {
      gameState.Char.x = old_x;
    }
    else
    {
      gameState.Char.x = char_dx_forward(distance_to_edge_weight());
      gameState.Char.y = y_land[gameState.Char.curr_row + 1];
      gameState.Char.fall_y = 0;
      seqtbl_offset_char(seq_15_grab_ledge_midair); // grab a ledge (after falling)
      play_seq();
      gameState.grab_timer = 12;
      gameState.is_screaming = 0;
    }
  }
}

// seg006:0ABD
__INLINE__ int can_grab_front_above()
{
  through_tile = get_tile_above_char();
  get_tile_front_above_char();
  return can_grab();
}

// seg006:0ACD
__INLINE__ void  in_wall()
{
  int16_t delta_x;
  delta_x = distance_to_edge_weight();
  if (delta_x >= 8 || get_tile_infrontof_char() == tiles_20_wall)
  {
    delta_x = 6 - delta_x;
  }
  else
  {
    delta_x += 4;
  }
  gameState.Char.x = char_dx_forward(delta_x);
  load_fram_det_col();
  get_tile_at_char();
}

// seg006:0B0C
__INLINE__ int get_tile_infrontof_char()
{
  return get_tile(gameState.Char.room, infrontx = dir_front[gameState.Char.direction + 1] + gameState.Char.curr_col, gameState.Char.curr_row);
}

// seg006:0B30
__INLINE__ int get_tile_infrontof2_char()
{
  int16_t var_2;
  var_2 = dir_front[gameState.Char.direction + 1];
  return get_tile(gameState.Char.room, infrontx = (var_2 << 1) + gameState.Char.curr_col, gameState.Char.curr_row);
}

// seg006:0B66
__INLINE__ int get_tile_behind_char()
{
  return get_tile(gameState.Char.room, dir_behind[gameState.Char.direction + 1] + gameState.Char.curr_col, gameState.Char.curr_row);
}

// seg006:0B8A
__INLINE__ int distance_to_edge_weight()
{
  return distance_to_edge(dx_weight());
}

// seg006:0B94
__INLINE__ int distance_to_edge(int xpos)
{
  int16_t distance;
  get_tile_div_mod_m7(xpos);
  distance = obj_xl;
  if (gameState.Char.direction == dir_0_right)
  {
    distance = 13 - distance;
  }
  return distance;
}

// seg006:0BC4
__INLINE__ void  fell_out()
{
  if (gameState.Char.alive < 0 && gameState.Char.room == 0)
  {
    take_hp(100);
    gameState.Char.alive = 0;
    gameState.Char.frame = frame_185_dead; // dead
  }
}

// seg006:0BEE
__INLINE__ void  play_kid()
{
  fell_out();
  control_kid();
  if (gameState.Char.alive >= 0 && is_dead())
  {
    if (resurrect_time)
    {
      loadkid();
      hitp_delta = gameState.hitp_max;
      seqtbl_offset_char(seq_2_stand); // stand
      gameState.Char.x += 8;
      play_seq();
      load_fram_det_col();
      set_start_pos();
    }
    is_show_time = 0;
    ++gameState.Char.alive;
  }
}

// seg006:0CD1
__INLINE__ void  control_kid()
{
  if (gameState.Char.alive < 0 && gameState.hitp_curr == 0)
  {
    gameState.Char.alive = 0;
  }
  if (gameState.grab_timer != 0)
  {
    --gameState.grab_timer;
  }
  rest_ctrl_1();
  do_paused();
  read_user_control();
  user_control();
  save_ctrl_1();
}

// seg006:0D49
__INLINE__ void  do_demo()
{
  if (gameState.checkpoint)
  {
    control_shift2 = release_arrows();
    control_forward = control_x = -1;
  }
  else if (gameState.Char.sword)
  {
    gameState.guard_skill = 10;
    autocontrol_opponent();
    gameState.guard_skill = 11;
  }
  else
  {
    do_auto_moves(custom->demo_moves);
  }
}

// seg006:0D85
__INLINE__ void  play_guard()
{
  if (gameState.Char.charid == charid_24_mouse)
  {
    autocontrol_opponent();
  }
  else
  {
    if (gameState.Char.alive < 0)
    {
      if (gameState.guardhp_curr == 0)
      {
        gameState.Char.alive = 0;
        on_guard_killed();
      }
      else
      {
        goto loc_7A65;
      }
    }
    if (gameState.Char.charid == charid_1_shadow)
    {
      clear_char();
    }
  loc_7A65:
    autocontrol_opponent();
    control();
  }
}

// seg006:0DC0
__INLINE__ void  user_control()
{
  if (gameState.Char.direction >= dir_0_right)
  {
    flip_control_x();
    control();
    flip_control_x();
  }
  else
  {
    control();
  }
}

// seg006:0DDC
__INLINE__ void  flip_control_x()
{
  uint8_t temp;
  control_x = -control_x;
  temp = control_forward;
  control_forward = control_backward;
  control_backward = temp;
}

// seg006:0E00
__INLINE__ int release_arrows()
{
  control_backward = control_forward = control_up = control_down = 0;
  return 1;
}

// seg006:0E12
__INLINE__ void  save_ctrl_1()
{
  gameState.ctrl1_forward = control_forward;
  gameState.ctrl1_backward = control_backward;
  gameState.ctrl1_up = control_up;
  gameState.ctrl1_down = control_down;
  gameState.ctrl1_shift2 = control_shift2;
}

// seg006:0E31
__INLINE__ void  rest_ctrl_1()
{
  control_forward = gameState.ctrl1_forward;
  control_backward = gameState.ctrl1_backward;
  control_up = gameState.ctrl1_up;
  control_down = gameState.ctrl1_down;
  control_shift2 = gameState.ctrl1_shift2;
}

// seg006:0E8E
__INLINE__ void  clear_saved_ctrl()
{
  gameState.ctrl1_forward = gameState.ctrl1_backward = gameState.ctrl1_up = gameState.ctrl1_down = gameState.ctrl1_shift2 = 0;
}

// seg006:0EAF
__INLINE__ void  read_user_control()
{
  if (control_forward >= 0)
  {
    if (control_x < 0)
    {
      if (control_forward == 0)
      {
        control_forward = -1;
      }
    }
    else
    {
      control_forward = 0;
    }
  }
  if (control_backward >= 0)
  {
    if (control_x == 1)
    {
      if (control_backward == 0)
      {
        control_backward = -1;
      }
    }
    else
    {
      control_backward = 0;
    }
  }
  if (control_up >= 0)
  {
    if (control_y < 0)
    {
      if (control_up == 0)
      {
        control_up = -1;
      }
    }
    else
    {
      control_up = 0;
    }
  }
  if (control_down >= 0)
  {
    if (control_y == 1)
    {
      if (control_down == 0)
      {
        control_down = -1;
      }
    }
    else
    {
      control_down = 0;
    }
  }
  if (control_shift2 >= 0)
  {
    if (control_shift < 0)
    {
      if (control_shift2 == 0)
      {
        control_shift2 = -1;
      }
    }
    else
    {
      control_shift2 = 0;
    }
  }
}

// seg006:0F55
__INLINE__ int can_grab()
{
  // Can char grab curr_tile2 through through_tile?
  uint8_t modifier;
  modifier = curr_room_modif[curr_tilepos];
  // can't grab through wall
  if (through_tile == tiles_20_wall)
    return 0;
  // can't grab through a door top if looking right
  if (through_tile == tiles_12_doortop && gameState.Char.direction >= dir_0_right)
    return 0;
  // can't grab through floor
  if (tile_is_floor(through_tile))
    return 0;
  // can't grab a shaking loose floor
  // Allow climbing onto a shaking loose floor if the delay is greater than the default. TODO: This should be a separate option.
  if (curr_tile2 == tiles_11_loose && modifier != 0 && !(custom->loose_floor_delay > 11))
    return 0;
  // a doortop with floor can be grabbed only from the left (looking right)
  if (curr_tile2 == tiles_7_doortop_with_floor && gameState.Char.direction < dir_0_right)
    return 0;
  // can't grab something that has no floor
  if (!tile_is_floor(curr_tile2))
    return 0;
  return 1;
}

// seg006:1005
__INLINE__ int get_tile_above_char()
{
  return get_tile(gameState.Char.room, gameState.Char.curr_col, gameState.Char.curr_row - 1);
}

// seg006:1020
__INLINE__ int get_tile_behind_above_char()
{
  return get_tile(gameState.Char.room, dir_behind[gameState.Char.direction + 1] + gameState.Char.curr_col, gameState.Char.curr_row - 1);
}

// seg006:1049
__INLINE__ int get_tile_front_above_char()
{
  return get_tile(gameState.Char.room, infrontx = dir_front[gameState.Char.direction + 1] + gameState.Char.curr_col, gameState.Char.curr_row - 1);
}

// seg006:1072
__INLINE__ int back_delta_x(int delta_x)
{
  if (gameState.Char.direction < dir_0_right)
  {
    // direction = left
    return delta_x;
  }
  else
  {
    // direction = right
    return -delta_x;
  }
}

// seg006:108A
__INLINE__ void  do_pickup(int obj_type)
{
  gameState.pickup_obj_type = obj_type;
  control_shift2 = 1;
  // erase picked up item
  curr_room_tiles[curr_tilepos] = tiles_1_floor;
  curr_room_modif[curr_tilepos] = 0;
  redraw_height = 35;
}

// seg006:10E6
__INLINE__ void  check_press()
{
  int16_t frame;
  int16_t action;
  frame = gameState.Char.frame;
  action = gameState.Char.action;
  // frames 87..99: hanging
  // frames 135..140: start climb up
  if ((frame >= frame_87_hanging_1 && frame < 100) || (frame >= frame_135_climbing_1 && frame < frame_141_climbing_7))
  {
    // the pressed tile is the one that the char is grabbing
    get_tile_above_char();
  }
  else if (action == actions_7_turn || action == actions_5_bumped || action < actions_2_hang_climb)
  {
    // frame 79: jumping up
    if (frame == frame_79_jumphang && get_tile_above_char() == tiles_11_loose)
    {
      // break a loose floor from above
      make_loose_fall(1);
    }
    else
    {
      // the pressed tile is the one that the char is standing on
      if (!(cur_frame.flags & FRAME_NEEDS_FLOOR))
        return;
      get_tile_at_char();
    }
  }
  else
  {
    return;
  }
  if (curr_tile2 == tiles_15_opener || curr_tile2 == tiles_6_closer)
  {
    if (gameState.Char.alive < 0)
    {
      trigger_button(1, 0, -1);
    }
    else
    {
      died_on_button();
    }
  }
  else if (curr_tile2 == tiles_11_loose)
  {
    gameState.is_guard_notice = 1;
    make_loose_fall(1);
  }
}

// seg006:1199
__INLINE__ void  check_spike_below()
{
  int16_t not_finished;
  int16_t room;
  int16_t row;
  int16_t col;
  int16_t right_col;
  right_col = get_tile_div_mod_m7(char_x_right);
  if (right_col < 0)
    return;
  row = gameState.Char.curr_row;
  room = gameState.Char.room;
  for (col = get_tile_div_mod_m7(char_x_left); col <= right_col; ++col)
  {
    row = gameState.Char.curr_row;
    do
    {
      not_finished = 0;
      if (get_tile(room, col, row) == tiles_2_spike)
      {
        start_anim_spike(curr_room, curr_tilepos);
      }
      else if (
        !tile_is_floor(curr_tile2) &&
        curr_room != 0 &&
        room == curr_room)
      {
        ++row;
        not_finished = 1;
      }
    } while (not_finished);
  }
}

// seg006:1231
__INLINE__ void  clip_char()
{
  int16_t frame;
  int16_t room;
  int16_t action;
  int16_t col;
  int16_t var_A;
  int16_t row;
  int16_t var_E;
  frame = gameState.Char.frame;
  action = gameState.Char.action;
  room = gameState.Char.room;
  row = gameState.Char.curr_row;
  reset_obj_clip();
  // frames 217..228: going up the level door
  if (frame >= frame_224_exit_stairs_8 && frame < 229)
  {
    obj_clip_top = leveldoor_ybottom + 1;
    obj_clip_right = leveldoor_right;
  }
  else
  {
    if (
      get_tile(room, char_col_left, char_top_row) == tiles_20_wall ||
      tile_is_floor(curr_tile2))
    {
      // frame 79: jump up, frame 81: grab
      if ((action == actions_0_stand && (frame == frame_79_jumphang || frame == frame_81_hangdrop_1)) ||
          get_tile(room, char_col_right, char_top_row) == tiles_20_wall ||
          tile_is_floor(curr_tile2))
      {
        var_E = row + 1;
        if (var_E == 1 ||
            ((var_A = y_clip[var_E]) < obj_y && var_A - 15 < char_top_y))
        {
          obj_clip_top = char_top_y = y_clip[var_E];
        }
      }
    }
    col = get_tile_div_mod(char_x_left_coll - 4);
    if (get_tile(room, col + 1, row) == tiles_7_doortop_with_floor ||
        curr_tile2 == tiles_12_doortop)
    {
      obj_clip_right = (tile_col << 5) + 32;
    }
    else
    {
      if ((get_tile(room, col, row) != tiles_7_doortop_with_floor &&
           curr_tile2 != tiles_12_doortop) ||
          action == actions_3_in_midair ||
          (action == actions_4_in_freefall && frame == frame_106_fall) ||
          (action == actions_5_bumped && frame == frame_107_fall_land_1) ||
          (gameState.Char.direction < dir_0_right && (action == actions_2_hang_climb ||
                                                      action == actions_6_hang_straight ||
                                                      (action == actions_1_run_jump &&
                                                       frame >= frame_137_climbing_3 && frame < frame_140_climbing_6))))
      {
        if (
          (get_tile(room, col = get_tile_div_mod(char_x_right_coll), row) == tiles_20_wall ||
           (curr_tile2 == tiles_13_mirror && gameState.Char.direction == dir_0_right)) &&
          (get_tile(room, col, char_top_row) == tiles_20_wall ||
           curr_tile2 == tiles_13_mirror) &&
          room == curr_room)
        {
          obj_clip_right = tile_col << 5;
        }
      }
      else
      {
        obj_clip_right = (tile_col << 5) + 32;
      }
    }
  }
}

// seg006:13E6
__INLINE__ void  stuck_lower()
{
  if (get_tile_at_char() == tiles_5_stuck)
  {
    ++gameState.Char.y;
  }
}

// seg006:13F3
__INLINE__ void  set_objtile_at_char()
{
  int16_t char_frame;
  int16_t char_action;
  char_frame = gameState.Char.frame;
  char_action = gameState.Char.action;
  if (char_action == actions_1_run_jump)
  {
    tile_row = char_bottom_row;
    tile_col = char_col_left;
  }
  else
  {
    tile_row = gameState.Char.curr_row;
    tile_col = gameState.Char.curr_col;
  }
  // frame 135..148: climbing
  if ((char_frame >= frame_135_climbing_1 && char_frame < 149) ||
      char_action == actions_2_hang_climb ||
      char_action == actions_3_in_midair ||
      char_action == actions_4_in_freefall ||
      char_action == actions_6_hang_straight)
  {
    --tile_col;
  }
  obj_tilepos = get_tilepos_nominus(tile_col, tile_row);
  // printf("set_objtile_at_char: obj_tile = %d\n", obj_tile); // debug
}

// seg006:1463
__INLINE__ void  proc_get_object()
{
  if (gameState.Char.charid != charid_0_kid || gameState.pickup_obj_type == 0)
    return;
  if (gameState.pickup_obj_type == -1)
  {
    gameState.have_sword = -1;
    flash_color = color_14_brightyellow;
    flash_time = 8;
  }
  else
  {
    switch (--gameState.pickup_obj_type)
    {
    case 0: // health
      if (gameState.hitp_curr != gameState.hitp_max)
      {
        hitp_delta = 1;
        flash_color = color_4_red;
        flash_time = 2;
      }
      break;
    case 1: // life
      flash_color = color_4_red;
      flash_time = 4;
      add_life();
      break;
    case 2: // feather
      feather_fall();
      break;
    case 3: // invert
      toggle_upside();
      break;
    case 5: // open
      get_tile(8, 0, 0);
      trigger_button(0, 0, -1);
      break;
    case 4: // hurt
      // Special event: blue potions on potions level take half of HP
      if (gameState.current_level == 15)
      {
        hitp_delta = -((gameState.hitp_max + 1) >> 1);
      }
      else
      {
        hitp_delta = -1;
      }
      break;
    }
  }
}

// seg006:1599
__INLINE__ int is_dead()
{
  // 177: spiked, 178: chomped, 185: dead
  // or maybe this was a switch-case?
  return gameState.Char.frame >= frame_177_spiked && (gameState.Char.frame <= frame_178_chomped || gameState.Char.frame == frame_185_dead);
}

// seg006:15E8
__INLINE__ void  on_guard_killed()
{
  if (gameState.current_level == 0)
  {
    // demo level: after killing Guard, run out of room
    gameState.checkpoint = 1;
    gameState.demo_index = gameState.demo_time = 0;
  }
  else if (gameState.current_level == /*13*/ custom->jaffar_victory_level)
  {
    // Jaffar's level: flash
    flash_color = color_15_brightwhite; // white
    flash_time = /*18*/ custom->jaffar_victory_flash_time;
    is_show_time = 1;
    gameState.leveldoor_open = 2;
  }
  else if (gameState.Char.charid != charid_1_shadow)
  {
  }
}

// seg006:1634
__INLINE__ void  clear_char()
{
  gameState.Char.direction = dir_56_none;
  gameState.Char.alive = 0;
  gameState.Char.action = 0;
  gameState.guardhp_curr = 0;
}

// seg006:1654
__INLINE__ void  save_obj()
{
  obj2_tilepos = obj_tilepos;
  obj2_x = obj_x;
  obj2_y = obj_y;
  obj2_direction = obj_direction;
  obj2_id = obj_id;
  obj2_chtab = obj_chtab;
  obj2_clip_top = obj_clip_top;
  obj2_clip_bottom = obj_clip_bottom;
  obj2_clip_left = obj_clip_left;
  obj2_clip_right = obj_clip_right;
}

// seg006:1691
__INLINE__ void  load_obj()
{
  obj_tilepos = obj2_tilepos;
  obj_x = obj2_x;
  obj_y = obj2_y;
  obj_direction = obj2_direction;
  obj_id = obj2_id;
  obj_chtab = obj2_chtab;
  obj_clip_top = obj2_clip_top;
  obj_clip_bottom = obj2_clip_bottom;
  obj_clip_left = obj2_clip_left;
  obj_clip_right = obj2_clip_right;
}

// seg006:16CE
__INLINE__ void  draw_hurt_splash()
{
  int16_t frame;
  frame = gameState.Char.frame;
  if (frame != frame_178_chomped)
  { // chomped
    save_obj();
    obj_tilepos = -1;
    // frame 185: dead
    // frame 106..110: fall + land
    if (frame == frame_185_dead || (frame >= frame_106_fall && frame < 111))
    {
      obj_y += 4;
      obj_dx_forward(5);
    }
    else if (frame == frame_177_spiked)
    { // spiked
      obj_dx_forward(-5);
    }
    else
    {
      obj_y -= ((gameState.Char.charid == charid_0_kid) << 2) + 11;
      obj_dx_forward(5);
    }
    if (gameState.Char.charid == charid_0_kid)
    {
      obj_chtab = id_chtab_2_kid;
      obj_id = 218; // splash!
    }
    else
    {
      obj_chtab = id_chtab_5_guard;
      obj_id = 1; // splash!
    }
    reset_obj_clip();
    load_obj();
  }
}

// seg006:175D
__INLINE__ void  check_killed_shadow()
{
  // Special event: killed the shadow
  if (gameState.current_level == 12)
  {
    if ((gameState.Char.charid | Opp.charid) == charid_1_shadow &&
        gameState.Char.alive < 0 && Opp.alive >= 0)
    {
      flash_color = color_15_brightwhite; // white
      flash_time = 5;
      take_hp(100);
    }
  }
}

// seg006:1827
__INLINE__ void  control_guard_inactive()
{
  if (gameState.Char.frame == frame_166_stand_inactive && control_down < 0)
  {
    if (control_forward < 0)
    {
      draw_sword();
    }
    else
    {
      control_down = 1;
      seqtbl_offset_char(seq_80_stand_flipped); // stand flipped
    }
  }
}

// seg006:1852
__INLINE__ int char_opp_dist()
{
  // >0 if Opp is in front of char
  // <0 if Opp is behind char
  int16_t distance;
  if (gameState.Char.room != Opp.room)
  {
    return 999;
  }
  distance = Opp.x - gameState.Char.x;
  if (gameState.Char.direction < dir_0_right)
  {
    distance = -distance;
  }
  if (distance >= 0 && gameState.Char.direction != Opp.direction)
  {
    distance += 13;
  }
  return distance;
}

// seg006:189B
__INLINE__ void  inc_curr_row()
{
  ++gameState.Char.curr_row;
}

// seg004:0004
__INLINE__ void  check_collisions()
{
  int16_t column;
  bump_col_left_of_wall = bump_col_right_of_wall = -1;
  if (gameState.Char.action == actions_7_turn)
    return;
  gameState.collision_row = gameState.Char.curr_row;
  move_coll_to_prev();
  gameState.prev_collision_row = gameState.collision_row;
  right_checked_col = std::min(get_tile_div_mod_m7(char_x_right_coll) + 2, 11);
  left_checked_col = get_tile_div_mod_m7(char_x_left_coll) - 1;
  get_row_collision_data(gameState.collision_row, gameState.curr_row_coll_room, gameState.curr_row_coll_flags);
  get_row_collision_data(gameState.collision_row + 1, gameState.below_row_coll_room, gameState.below_row_coll_flags);
  get_row_collision_data(gameState.collision_row - 1, gameState.above_row_coll_room, gameState.above_row_coll_flags);
  for (column = 9; column >= 0; --column)
  {
    if (gameState.curr_row_coll_room[column] >= 0 &&
        gameState.prev_coll_room[column] == gameState.curr_row_coll_room[column])
    {
      // char bumps into left of wall
      if (
        (gameState.prev_coll_flags[column] & 0x0F) == 0 &&
        (gameState.curr_row_coll_flags[column] & 0x0F) != 0)
      {
        bump_col_left_of_wall = column;
      }
      // char bumps into right of wall
      if (
        (gameState.prev_coll_flags[column] & 0xF0) == 0 &&
        (gameState.curr_row_coll_flags[column] & 0xF0) != 0)
      {
        bump_col_right_of_wall = column;
      }
    }
  }
}

// seg004:00DF
__INLINE__ void  move_coll_to_prev()
{
  int8_t *row_coll_room_ptr;
  uint8_t *row_coll_flags_ptr;
  int16_t column;
  if (gameState.collision_row == gameState.prev_collision_row ||
      gameState.collision_row + 3 == gameState.prev_collision_row ||
      gameState.collision_row - 3 == gameState.prev_collision_row)
  {
    row_coll_room_ptr = gameState.curr_row_coll_room;
    row_coll_flags_ptr = gameState.curr_row_coll_flags;
  }
  else if (
    gameState.collision_row + 1 == gameState.prev_collision_row ||
    gameState.collision_row - 2 == gameState.prev_collision_row)
  {
    row_coll_room_ptr = gameState.above_row_coll_room;
    row_coll_flags_ptr = gameState.above_row_coll_flags;
  }
  else
  {
    row_coll_room_ptr = gameState.below_row_coll_room;
    row_coll_flags_ptr = gameState.below_row_coll_flags;
  }
  for (column = 0; column < 10; ++column)
  {
    gameState.prev_coll_room[column] = row_coll_room_ptr[column];
    gameState.prev_coll_flags[column] = row_coll_flags_ptr[column];
    gameState.below_row_coll_room[column] = -1;
    gameState.above_row_coll_room[column] = -1;
    gameState.curr_row_coll_room[column] = -1;
  }
}

// seg004:0185
__INLINE__ void  get_row_collision_data(int16_t row, int8_t *row_coll_room_ptr, uint8_t *row_coll_flags_ptr)
{
  int16_t right_wall_xpos;
  uint8_t curr_flags;
  int16_t room;
  int16_t column;
  int16_t left_wall_xpos;
  room = gameState.Char.room;
  coll_tile_left_xpos = x_bump[left_checked_col + 5] + 7;
  for (column = left_checked_col; column <= right_checked_col; ++column)
  {
    left_wall_xpos = get_left_wall_xpos(room, column, row);
    right_wall_xpos = get_right_wall_xpos(room, column, row);
    // char bumps into left of wall
    curr_flags = left_wall_xpos < char_x_right_coll ? 0x0F : 0x00;
    // char bumps into right of wall
    curr_flags |= right_wall_xpos > char_x_left_coll ? 0xF0 : 0x00;
    row_coll_flags_ptr[tile_col] = curr_flags;
    row_coll_room_ptr[tile_col] = curr_room;
    coll_tile_left_xpos += 14;
  }
}

// seg004:0226
__INLINE__ int get_left_wall_xpos(int room, int column, int row)
{
  int16_t type;
  type = wall_type(get_tile(room, column, row));
  if (type)
  {
    return wall_dist_from_left[type] + coll_tile_left_xpos;
  }
  else
  {
    return 0xFF;
  }
}

// seg004:025F
__INLINE__ int get_right_wall_xpos(int room, int column, int row)
{
  int16_t type;
  type = wall_type(get_tile(room, column, row));
  if (type)
  {
    return coll_tile_left_xpos - wall_dist_from_right[type] + 13;
  }
  else
  {
    return 0;
  }
}

// seg004:029D
__INLINE__ void  check_bumped()
{
  if (
    gameState.Char.action != actions_2_hang_climb &&
    gameState.Char.action != actions_6_hang_straight &&
    // frames 135..149: climb up
    (gameState.Char.frame < frame_135_climbing_1 || gameState.Char.frame >= 149))
  {
    if (bump_col_left_of_wall >= 0)
    {
      check_bumped_look_right();
    }
    else if (bump_col_right_of_wall >= 0)
    {
      check_bumped_look_left();
    }
  }
}

// seg004:02D2
__INLINE__ void  check_bumped_look_left()
{
  if ((gameState.Char.sword == sword_2_drawn || gameState.Char.direction < dir_0_right) && // looking left
      is_obstacle_at_col(bump_col_right_of_wall))
  {
    bumped(get_right_wall_xpos(curr_room, tile_col, tile_row) - char_x_left_coll, dir_0_right);
  }
}

// seg004:030A
__INLINE__ void  check_bumped_look_right()
{
  if ((gameState.Char.sword == sword_2_drawn || gameState.Char.direction == dir_0_right) && // looking right
      is_obstacle_at_col(bump_col_left_of_wall))
  {
    bumped(get_left_wall_xpos(curr_room, tile_col, tile_row) - char_x_right_coll, dir_FF_left);
  }
}

// seg004:0343
__INLINE__ int is_obstacle_at_col(int tile_col)
{
  int16_t tile_row;
  tile_row = gameState.Char.curr_row;
  if (tile_row < 0)
  {
    tile_row += 3;
  }
  if (tile_row >= 3)
  {
    tile_row -= 3;
  }
  get_tile(gameState.curr_row_coll_room[tile_col], tile_col, tile_row);
  return is_obstacle();
}

// seg004:037E
__INLINE__ int is_obstacle()
{
  if (curr_tile2 == tiles_10_potion)
  {
    return 0;
  }
  else if (curr_tile2 == tiles_4_gate)
  {
    if (!can_bump_into_gate())
      return 0;
  }
  else if (curr_tile2 == tiles_18_chomper)
  {
    // is the chomper closed?
    if (curr_room_modif[curr_tilepos] != 2)
      return 0;
  }
  else if (
    curr_tile2 == tiles_13_mirror &&
    gameState.Char.charid == charid_0_kid &&
    gameState.Char.frame >= frame_39_start_run_jump_6 && gameState.Char.frame < frame_44_running_jump_5 && // run-jump
    gameState.Char.direction < dir_0_right                                                                 // right-to-left only
  )
  {
    curr_room_modif[curr_tilepos] = 0x56; // broken mirror or what?
    gameState.jumped_through_mirror = -1;
    return 0;
  }
  coll_tile_left_xpos = xpos_in_drawn_room(x_bump[tile_col + 5]) + 7;
  return 1;
}

// seg004:0405
__INLINE__ int xpos_in_drawn_room(int xpos)
{
  if (curr_room != gameState.drawn_room)
  {
    if (curr_room == room_L || curr_room == room_BL)
    {
      xpos -= 140;
    }
    else if (curr_room == room_R || curr_room == room_BR)
    {
      xpos += 140;
    }
  }
  return xpos;
}

// seg004:0448
__INLINE__ void  bumped(int8_t delta_x, int8_t push_direction)
{
  // frame 177: spiked
  if (gameState.Char.alive < 0 && gameState.Char.frame != frame_177_spiked)
  {
    gameState.Char.x += delta_x;
    if (push_direction < dir_0_right)
    {
      // pushing left
      if (curr_tile2 == tiles_20_wall)
      {
        get_tile(curr_room, --tile_col, tile_row);
      }
    }
    else
    {
      // pushing right
      if (curr_tile2 == tiles_12_doortop ||
          curr_tile2 == tiles_7_doortop_with_floor ||
          curr_tile2 == tiles_20_wall)
      {
        ++tile_col;
        if (curr_room == 0 && tile_col == 10)
        {
          curr_room = gameState.Char.room;
          tile_col = 0;
        }
        get_tile(curr_room, tile_col, tile_row);
      }
    }
    if (tile_is_floor(curr_tile2))
    {
      bumped_floor(push_direction);
    }
    else
    {
      bumped_fall();
    }
  }
}

// seg004:0A10
__INLINE__ int dist_from_wall_forward(uint8_t tiletype)
{
  int16_t type;
  if (tiletype == tiles_4_gate && !can_bump_into_gate())
  {
    return -1;
  }
  else
  {
    coll_tile_left_xpos = x_bump[tile_col + 5] + 7;
    type = wall_type(tiletype);
    if (type == 0)
      return -1;
    if (gameState.Char.direction < dir_0_right)
    {
      // looking left
      // return wall_dist_from_right[type] + char_x_left_coll - coll_tile_left_xpos - 13;
      return char_x_left_coll - (coll_tile_left_xpos + 13 - wall_dist_from_right[type]);
    }
    else
    {
      // looking right
      return wall_dist_from_left[type] + coll_tile_left_xpos - char_x_right_coll;
    }
  }
}

// seg004:04E4
__INLINE__ void  bumped_fall()
{
  int16_t action;
  action = gameState.Char.action;
  gameState.Char.x = char_dx_forward(-4);
  if (action == actions_4_in_freefall)
  {
    gameState.Char.fall_x = 0;
  }
  else
  {
    seqtbl_offset_char(seq_45_bumpfall); // fall after bumped
    play_seq();
  }
  bumped_sound();
}

// seg004:0520
__INLINE__ void  bumped_floor(int8_t push_direction)
{
  int16_t frame;
  int16_t seq_index;
  if (gameState.Char.sword != sword_2_drawn && (uint16_t)(y_land[gameState.Char.curr_row + 1] - gameState.Char.y) >= (uint16_t)15)
  {
    bumped_fall();
  }
  else
  {
    gameState.Char.y = y_land[gameState.Char.curr_row + 1];
    if (gameState.Char.fall_y >= 22)
    {
      gameState.Char.x = char_dx_forward(-5);
    }
    else
    {
      gameState.Char.fall_y = 0;
      if (gameState.Char.alive)
      {
        if (gameState.Char.sword == sword_2_drawn)
        {
          if (push_direction == gameState.Char.direction)
          {
            seqtbl_offset_char(seq_65_bump_forward_with_sword); // pushed forward with sword (gameState.Kid)
            play_seq();
            gameState.Char.x = char_dx_forward(1);
            return;
          }
          else
          {
            seq_index = seq_64_pushed_back_with_sword; // pushed back with sword
          }
        }
        else
        {
          frame = gameState.Char.frame;
          if (frame == 24 || frame == 25 ||
              (frame >= 40 && frame < 43) ||
              (frame >= frame_102_start_fall_1 && frame < 107))
          {
            seq_index = seq_46_hardbump; // bump into wall after run-jump (crouch)
          }
          else
          {
            seq_index = seq_47_bump; // bump into wall
          }
        }
        seqtbl_offset_char(seq_index);
        play_seq();
        bumped_sound();
      }
    }
  }
}

// seg004:05F1
__INLINE__ void  bumped_sound()
{
  gameState.is_guard_notice = 1;
}

// seg004:0601
__INLINE__ void  clear_coll_rooms()
{
  memset(gameState.prev_coll_room, -1, sizeof(gameState.prev_coll_room));
  memset(gameState.curr_row_coll_room, -1, sizeof(gameState.curr_row_coll_room));
  memset(gameState.below_row_coll_room, -1, sizeof(gameState.below_row_coll_room));
  memset(gameState.above_row_coll_room, -1, sizeof(gameState.above_row_coll_room));
  gameState.prev_collision_row = -1;
}

// seg004:0657
__INLINE__ int can_bump_into_gate()
{
  return (curr_room_modif[curr_tilepos] >> 2) + 6 < char_height;
}

// seg004:067C
__INLINE__ int get_edge_distance()
{
  /*
Possible results in edge_type:
0: closer/sword/potion
1: edge
2: floor (nothing  char)
*/
  int16_t distance;
  uint8_t tiletype;
  determine_col();
  load_frame_to_obj();
  set_char_collision();
  tiletype = get_tile_at_char();
  if (wall_type(tiletype) != 0)
  {
    tile_col = gameState.Char.curr_col;
    distance = dist_from_wall_forward(tiletype);
    if (distance >= 0)
    {
    loc_59DD:
      if (distance < 14)
      {
        edge_type = 1;
      }
      else
      {
        edge_type = 2;
        distance = 11;
      }
    }
    else
    {
      goto loc_59E8;
    }
  }
  else
  {
  loc_59E8:
    tiletype = get_tile_infrontof_char();
    if (tiletype == tiles_12_doortop && gameState.Char.direction >= dir_0_right)
    {
    loc_59FB:
      edge_type = 0;
      distance = distance_to_edge_weight();
    }
    else
    {
      if (wall_type(tiletype) != 0)
      {
        tile_col = infrontx;
        distance = dist_from_wall_forward(tiletype);
        if (distance >= 0)
          goto loc_59DD;
      }
      if (tiletype == tiles_11_loose)
        goto loc_59FB;
      if (
        tiletype == tiles_6_closer ||
        tiletype == tiles_22_sword ||
        tiletype == tiles_10_potion)
      {
        distance = distance_to_edge_weight();
        if (distance != 0)
        {
          edge_type = 0;
        }
        else
        {
          edge_type = 2;
          distance = 11;
        }
      }
      else
      {
        if (tile_is_floor(tiletype))
        {
          edge_type = 2;
          distance = 11;
        }
        else
        {
          goto loc_59FB;
        }
      }
    }
  }
  curr_tile2 = tiletype;
  return distance;
}

// seg004:076B
__INLINE__ void  check_chomped_kid()
{
  int16_t tile_col;
  int16_t tile_row;
  tile_row = gameState.Char.curr_row;
  for (tile_col = 0; tile_col < 10; ++tile_col)
  {
    if (gameState.curr_row_coll_flags[tile_col] == 0xFF &&
        get_tile(gameState.curr_row_coll_room[tile_col], tile_col, tile_row) == tiles_18_chomper &&
        (curr_room_modif[curr_tilepos] & 0x7F) == 2 // closed chomper
    )
    {
      chomped();
    }
  }
}

// seg004:07BF
__INLINE__ void  chomped()
{
  curr_room_modif[curr_tilepos] |= 0x80; // put blood
  if (gameState.Char.frame != frame_178_chomped && gameState.Char.room == curr_room)
  {
    gameState.Char.x = x_bump[tile_col + 5] + 7;
    gameState.Char.x = char_dx_forward(7 - !gameState.Char.direction);
    gameState.Char.y = y_land[gameState.Char.curr_row + 1];
    take_hp(100);
    seqtbl_offset_char(seq_54_chomped); // chomped
    play_seq();
  }
}

// seg004:0A7B
__INLINE__ int dist_from_wall_behind(uint8_t tiletype)
{
  int16_t type;
  type = wall_type(tiletype);
  if (type == 0)
  {
    return 99;
  }
  else
  {
    if (gameState.Char.direction >= dir_0_right)
    {
      // looking right
      // return wall_dist_from_right[type] + char_x_left_coll - coll_tile_left_xpos - 13;
      return char_x_left_coll - (coll_tile_left_xpos + 13 - wall_dist_from_right[type]);
    }
    else
    {
      // looking left
      return wall_dist_from_left[type] + coll_tile_left_xpos - char_x_right_coll;
    }
  }
}

// seg004:0833
__INLINE__ void  check_gate_push()
{
  // Closing gate pushes gameState.Kid
  int16_t frame;
  int16_t orig_col;
  frame = gameState.Char.frame;
  if (gameState.Char.action == actions_7_turn ||
      frame == frame_15_stand ||                      // stand
      (frame >= frame_108_fall_land_2 && frame < 111) // crouch
  )
  {
    get_tile_at_char();
    orig_col = tile_col;
    if ((curr_tile2 == tiles_4_gate ||
         get_tile(curr_room, --tile_col, tile_row) == tiles_4_gate) &&
        (gameState.curr_row_coll_flags[tile_col] & gameState.prev_coll_flags[tile_col]) == 0xFF &&
        can_bump_into_gate())
    {
      bumped_sound();
      // printf("check_gate_push: orig_col = %d, tile_col = %d, curr_room = %d, gameState.Char.room = %d, orig_room = %d\n", orig_col, tile_col, curr_room, gameState.Char.room, orig_room);
      //  push gameState.Kid left if orig_col <= tile_col, gate at char's tile
      //  push gameState.Kid right if orig_col > tile_col, gate is left from char's tile
      gameState.Char.x += 5 - (orig_col <= tile_col) * 10;
    }
  }
}

// seg004:08C3
__INLINE__ void  check_guard_bumped()
{
  if (
    gameState.Char.action == actions_1_run_jump &&
    gameState.Char.alive < 0 &&
    gameState.Char.sword >= sword_2_drawn)
  {
    if (

      get_tile_at_char() == tiles_20_wall ||
      curr_tile2 == tiles_7_doortop_with_floor ||
      (curr_tile2 == tiles_4_gate && can_bump_into_gate()) ||
      (gameState.Char.direction >= dir_0_right && (get_tile(curr_room, --tile_col, tile_row) == tiles_7_doortop_with_floor ||
                                                   (curr_tile2 == tiles_4_gate && can_bump_into_gate()))))
    {
      load_frame_to_obj();
      set_char_collision();
      if (is_obstacle())
      {
        int16_t delta_x;
        delta_x = dist_from_wall_behind(curr_tile2);
        if (delta_x < 0 && delta_x > -13)
        {
          gameState.Char.x = char_dx_forward(-delta_x);
          seqtbl_offset_char(seq_65_bump_forward_with_sword); // pushed to wall with sword (Guard)
          play_seq();
          load_fram_det_col();
        }
      }
    }
  }
}

// seg004:0989
__INLINE__ void  check_chomped_guard()
{
  get_tile_at_char();
  if (!check_chomped_here())
  {
    get_tile(curr_room, ++tile_col, tile_row);
    check_chomped_here();
  }
}

// seg004:09B0
__INLINE__ int check_chomped_here()
{
  if (curr_tile2 == tiles_18_chomper &&
      (curr_room_modif[curr_tilepos] & 0x7F) == 2)
  {
    coll_tile_left_xpos = x_bump[tile_col + 5] + 7;
    if (get_left_wall_xpos(curr_room, tile_col, tile_row) < char_x_right_coll &&
        get_right_wall_xpos(curr_room, tile_col, tile_row) > char_x_left_coll)
    {
      chomped();
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

// seg007:0000
__INLINE__ void  process_trobs()
{
  uint16_t need_delete;
  uint16_t index;
  uint16_t new_index;
  need_delete = 0;
  if (gameState.trobs_count == 0)
    return;
  for (index = 0; index < gameState.trobs_count; ++index)
  {
    trob = gameState.trobs[index];
    animate_tile();
    gameState.trobs[index].type = trob.type;
    if (trob.type < 0)
    {
      need_delete = 1;
    }
  }
  if (need_delete)
  {
    for (index = new_index = 0; index < gameState.trobs_count; ++index)
    {
      if (gameState.trobs[index].type >= 0)
      {
        gameState.trobs[new_index++] = gameState.trobs[index];
      }
    }
    gameState.trobs_count = new_index;
  }
}

// seg007:00AF
__INLINE__ void  animate_tile()
{
  get_room_address(trob.room);
  switch (get_curr_tile(trob.tilepos))
  {
  case tiles_19_torch:
  case tiles_30_torch_with_debris:
    animate_torch();
    break;
  case tiles_6_closer:
  case tiles_15_opener:
    animate_button();
    break;
  case tiles_2_spike:
    animate_spike();
    break;
  case tiles_11_loose:
    animate_loose();
    break;
  case tiles_0_empty:
    animate_empty();
    break;
  case tiles_18_chomper:
    animate_chomper();
    break;
  case tiles_4_gate:
    animate_door();
    break;
  case tiles_16_level_door_left:
    animate_leveldoor();
    break;
  case tiles_10_potion:
    animate_potion();
    break;
  case tiles_22_sword:
    animate_sword();
    break;
  default:
    trob.type = -1;
    break;
  }
  curr_room_modif[trob.tilepos] = curr_modifier;
}

// seg007:0166
__INLINE__ int16_t is_trob_in_drawn_room()
{
  if (trob.room != gameState.drawn_room)
  {
    trob.type = -1;
    return 0;
  }
  else
  {
    return 1;
  }
}

// seg007:0258
__INLINE__ int16_t get_trob_pos_in_drawn_room()
{
  int16_t tilepos;
  tilepos = trob.tilepos;
  if (trob.room == room_A)
  {
    if (tilepos >= 20 && tilepos < 30)
    {
      // 20..29 -> -1..-10
      tilepos = 19 - tilepos;
    }
    else
    {
      tilepos = 30;
    }
  }
  else
  {
    if (trob.room != gameState.drawn_room)
    {
      tilepos = 30;
    }
  }
  return tilepos;
}

// seg007:029D
__INLINE__ int16_t get_trob_right_pos_in_drawn_room()
{
  uint16_t tilepos;
  tilepos = trob.tilepos;
  if (trob.room == gameState.drawn_room)
  {
    if (tilepos % 10 != 9)
    {
      ++tilepos;
    }
    else
    {
      tilepos = 30;
    }
  }
  else if (trob.room == room_L)
  {
    if (tilepos % 10 == 9)
    {
      tilepos -= 9;
    }
    else
    {
      tilepos = 30;
    }
  }
  else if (trob.room == room_A)
  {
    if (tilepos >= 20 && tilepos < 29)
    {
      // 20..28 -> -2..-10
      tilepos = 18 - tilepos;
    }
    else
    {
      tilepos = 30;
    }
  }
  else if (trob.room == room_AL && tilepos == 29)
  {
    tilepos = -1;
  }
  else
  {
    tilepos = 30;
  }
  return tilepos;
}

// seg007:032C
__INLINE__ int16_t get_trob_right_above_pos_in_drawn_room()
{
  uint16_t tilepos;
  tilepos = trob.tilepos;
  if (trob.room == gameState.drawn_room)
  {
    if (tilepos % 10 != 9)
    {
      if (tilepos < 10)
      {
        // 0..8 -> -2..-10
        tilepos = -(tilepos + 2);
      }
      else
      {
        tilepos -= 9;
      }
    }
    else
    {
      tilepos = 30;
    }
  }
  else if (trob.room == room_L)
  {
    if (tilepos == 9)
    {
      tilepos = -1;
    }
    else
    {
      if (tilepos % 10 == 9)
      {
        tilepos -= 19;
      }
      else
      {
        tilepos = 30;
      }
    }
  }
  else if (trob.room == room_B)
  {
    if (tilepos < 9)
    {
      tilepos += 21;
    }
    else
    {
      tilepos = 30;
    }
  }
  else if (trob.room == room_BL && tilepos == 9)
  {
    tilepos = 20;
  }
  else
  {
    tilepos = 30;
  }
  return tilepos;
}

// seg007:06CD
__INLINE__ int16_t get_torch_frame(int16_t curr)
{
  int16_t next;
  next = prandom(255);
  if (next != curr)
  {
    if (next < 9)
    {
      return next;
    }
    else
    {
      next = curr;
    }
  }
  ++next;
  if (next >= 9)
    next = 0;
  return next;
}

// seg007:03CF
__INLINE__ void  animate_torch()
{
  // if (is_trob_in_drawn_room()) {
  //  Keep animating torches in the rightmost column of the left-side room as well, because they are visible in the current room.
  if (trob.room == gameState.drawn_room || (trob.room == room_L && (trob.tilepos % 10) == 9))
  {
    curr_modifier = get_torch_frame(curr_modifier);
  }
  else
  {
    trob.type = -1;
  }
}

// seg007:06AD
__INLINE__ int16_t bubble_next_frame(int16_t curr)
{
  int16_t next;
  next = curr + 1;
  if (next >= 8)
    next = 1;
  return next;
}

// seg007:03E9
__INLINE__ void  animate_potion()
{
  uint16_t type;
  if (trob.type >= 0 && is_trob_in_drawn_room())
  {
    type = curr_modifier & 0xF8;
    curr_modifier = bubble_next_frame(curr_modifier & 0x07) | type;
  }
}

// seg007:0425
__INLINE__ void  animate_sword()
{
  if (is_trob_in_drawn_room())
  {
    --curr_modifier;
    if (curr_modifier == 0)
    {
      curr_modifier = (prandom(255) & 0x3F) + 0x28;
    }
  }
}

// seg007:0448
__INLINE__ void  animate_chomper()
{
  uint16_t blood;
  uint16_t frame;
  if (trob.type >= 0)
  {
    blood = curr_modifier & 0x80;
    frame = (curr_modifier & 0x7F) + 1;
    if (frame > /*15*/ custom->chomper_speed)
    {
      frame = 1;
    }
    curr_modifier = blood | frame;
    if (frame == 2)
    {
    }
    // If either:
    // - gameState.Kid left this room
    // - gameState.Kid left this row
    // - gameState.Kid died but not in this chomper
    // and chomper is past frame 6
    // then stop.
    if ((trob.room != gameState.drawn_room || trob.tilepos / 10 != gameState.Kid.curr_row ||
         (gameState.Kid.alive >= 0 && blood == 0)) &&
        (curr_modifier & 0x7F) >= 6)
    {
      trob.type = -1;
    }
  }
}

// seg007:04D3
__INLINE__ void  animate_spike()
{
  if (trob.type >= 0)
  {
    // 0xFF means a disabled spike.
    if (curr_modifier == 0xFF)
      return;
    if (curr_modifier & 0x80)
    {
      --curr_modifier;
      if (curr_modifier & 0x7F)
        return;
      curr_modifier = 6;
    }
    else
    {
      ++curr_modifier;
      if (curr_modifier == 5)
      {
        curr_modifier = 0x8F;
      }
      else if (curr_modifier == 9)
      {
        curr_modifier = 0;
        trob.type = -1;
      }
    }
  }
}

// seg007:0522
__INLINE__ void  animate_door()
{
  /*
Possible values of anim_type:
0: closing
1: open
2: permanent open
3,4,5,6,7,8: fast closing with speeds 20,40,60,80,100,120 /4 pixel/frame
*/
  int8_t anim_type;
  anim_type = trob.type;
  if (anim_type >= 0)
  {
    if (anim_type >= 3)
    {
      // closing fast
      if (anim_type < 8)
      {
        ++anim_type;
        trob.type = anim_type;
      }
      int16_t new_mod = curr_modifier - gate_close_speeds[anim_type];
      curr_modifier = new_mod;
      // if ((int8_t)curr_modifier < 0) {
      if (new_mod < 0)
      {
        // if ((curr_modifier -= gate_close_speeds[anim_type]) < 0) {
        curr_modifier = 0;
        trob.type = -1;
      }
    }
    else
    {
      if (curr_modifier != 0xFF)
      {
        // 0xFF means permanently open.
        curr_modifier += door_delta[anim_type];
        if (anim_type == 0)
        {
          // closing
          if (curr_modifier != 0)
          {
            if (curr_modifier < 188)
            {
              if ((curr_modifier & 3) == 3)
              {
              }
            }
          }
          else
          {
            gate_stop();
          }
        }
        else
        {
          // opening
          if (curr_modifier < 188)
          {
            if ((curr_modifier & 7) == 0)
            {
            }
          }
          else
          {
            // stop
            if (anim_type < 2)
            {
              // after regular open
              curr_modifier = 238;
              trob.type = 0; // closing
            }
            else
            {
              // after permanent open
              curr_modifier = 0xFF; // keep open
              gate_stop();
            }
          }
        }
      }
      else
      {
        gate_stop();
      }
    }
  }
}

// seg007:05E3
__INLINE__ void  gate_stop()
{
  trob.type = -1;
}

// seg007:05F1
__INLINE__ void  animate_leveldoor()
{
  /*
Possible values of trob_type:
0: open
1: open (with button)
2: open
3,4,5,6: fast closing with speeds 0,5,17,99 pixel/frame
*/
  uint16_t trob_type;
  trob_type = trob.type;
  if (trob.type >= 0)
  {
    if (trob_type >= 3)
    {
      // closing
      ++trob.type;
      curr_modifier -= leveldoor_close_speeds[trob.type - 3];
      if ((int8_t)curr_modifier < 0)
      {
        curr_modifier = 0;
        trob.type = -1;
      }
      else
      {
        if (trob.type == 4)
        {
          sound_interruptible[sound_15_leveldoor_sliding] = 1;
        }
      }
    }
    else
    {
      // opening
      ++curr_modifier;
      if (curr_modifier >= 43)
      {
        trob.type = -1;
        if (gameState.leveldoor_open == 0 || gameState.leveldoor_open == 2)
        {
          gameState.leveldoor_open = 1;
          if (gameState.current_level == /*4*/ custom->mirror_level)
          {
            // Special event: place mirror
            get_tile(/*4*/ custom->mirror_room, /*4*/ custom->mirror_column, /*0*/ custom->mirror_row);
            curr_room_tiles[curr_tilepos] = /*tiles_13_mirror*/ custom->mirror_tile;
          }
        }
      }
      else
      {
        sound_interruptible[sound_15_leveldoor_sliding] = 0;
      }
    }
  }
}

// seg007:081E
__INLINE__ void  start_anim_torch(int16_t room, int16_t tilepos)
{
  curr_room_modif[tilepos] = prandom(8);
  add_trob(room, tilepos, 1);
}

// seg007:0847
__INLINE__ void  start_anim_potion(int16_t room, int16_t tilepos)
{
  curr_room_modif[tilepos] &= 0xF8;
  curr_room_modif[tilepos] |= prandom(6) + 1;
  add_trob(room, tilepos, 1);
}

// seg007:087C
__INLINE__ void  start_anim_sword(int16_t room, int16_t tilepos)
{
  curr_room_modif[tilepos] = prandom(0xFF) & 0x1F;
  add_trob(room, tilepos, 1);
}

// seg007:08A7
__INLINE__ void  start_anim_chomper(int16_t room, int16_t tilepos, uint8_t modifier)
{
  int16_t old_modifier;
  old_modifier = curr_room_modif[tilepos];
  if (old_modifier == 0 || old_modifier >= 6)
  {
    curr_room_modif[tilepos] = modifier;
    add_trob(room, tilepos, 1);
  }
}

// seg007:08E3
__INLINE__ void  start_anim_spike(int16_t room, int16_t tilepos)
{
  int8_t old_modifier;
  old_modifier = curr_room_modif[tilepos];
  if (old_modifier <= 0)
  {
    if (old_modifier == 0)
    {
      add_trob(room, tilepos, 1);
    }
    else
    {
      // 0xFF means a disabled spike.
      if (old_modifier != (int8_t)0xFF)
      {
        curr_room_modif[tilepos] = 0x8F;
      }
    }
  }
}

// seg007:092C
__INLINE__ int16_t trigger_gate(int16_t room, int16_t tilepos, int16_t button_type)
{
  uint8_t modifier;
  modifier = curr_room_modif[tilepos];
  if (button_type == tiles_15_opener)
  {
    // If the gate is permanently open, don't to anything.
    if (modifier == 0xFF)
      return -1;
    if (modifier >= 188)
    {                                 // if it's already open
      curr_room_modif[tilepos] = 238; // keep it open for a while
      return -1;
    }
    curr_room_modif[tilepos] = (modifier + 3) & 0xFC;
    return 1; // regular open
  }
  else if (button_type == tiles_14_debris)
  {
    // If it's not fully open:
    if (modifier < 188)
      return 2;                      // permanent open
    curr_room_modif[tilepos] = 0xFF; // keep open
    return -1;
  }
  else
  {
    if (modifier != 0)
    {
      return 3; // close fast
    }
    else
    {
      // already closed
      return -1;
    }
  }
}

// seg007:0999
__INLINE__ int16_t trigger_1(int16_t target_type, int16_t room, int16_t tilepos, int16_t button_type)
{
  int16_t result;
  result = -1;
  if (target_type == tiles_4_gate)
  {
    result = trigger_gate(room, tilepos, button_type);
  }
  else if (target_type == tiles_16_level_door_left)
  {
    if (curr_room_modif[tilepos] != 0)
    {
      result = -1;
    }
    else
    {
      result = 1;
    }
  }
  else if (custom->allow_triggering_any_tile)
  { // allow_triggering_any_tile hack
    result = 1;
  }
  return result;
}

// seg007:0BF2
__INLINE__ int16_t get_doorlink_tile(int16_t index)
{
  return doorlink1_ad[index] & 0x1F;
}

// seg007:0C09
__INLINE__ int16_t get_doorlink_next(int16_t index)
{
  return !(doorlink1_ad[index] & 0x80);
}

// seg007:0C26
__INLINE__ int16_t get_doorlink_room(int16_t index)
{
  return ((doorlink1_ad[index] & 0x60) >> 5) +
         ((doorlink2_ad[index] & 0xE0) >> 3);
}

// seg007:09E5
__INLINE__ void  do_trigger_list(int16_t index, int16_t button_type)
{
  uint16_t room;
  uint16_t tilepos;
  uint8_t target_type;
  int8_t trigger_result;
  // while (doorlink1_ad[index] != -1) { // these can't be equal!
  while (1)
  { // Same as the above but just a little faster and no compiler warning.
    room = get_doorlink_room(index);
    get_room_address(room);
    tilepos = get_doorlink_tile(index);
    target_type = curr_room_tiles[tilepos] & 0x1F;
    trigger_result = trigger_1(target_type, room, tilepos, button_type);
    if (trigger_result >= 0)
    {
      add_trob(room, tilepos, trigger_result);
    }
    if (get_doorlink_next(index++) == 0)
      break;
  }
}

// seg007:0ACA
__INLINE__ int16_t find_trob()
{
  int16_t index;
  for (index = 0; index < gameState.trobs_count; ++index)
  {
    if (gameState.trobs[index].tilepos == trob.tilepos &&
        gameState.trobs[index].room == trob.room)
      return index;
  }
  return -1;
}

// seg007:0A5A
__INLINE__ void  add_trob(uint8_t room, uint8_t tilepos, int8_t type)
{
  int16_t found;
  trob.room = room;
  trob.tilepos = tilepos;
  trob.type = type;
  found = find_trob();
  if (found == -1)
  {
    // add new
    if (gameState.trobs_count == 30)
      return;
    gameState.trobs[gameState.trobs_count++] = trob;
  }
  else
  {
    // change existing
    gameState.trobs[found].type = trob.type;
  }
}

// seg007:0BB6
__INLINE__ int16_t get_doorlink_timer(int16_t index)
{
  return doorlink2_ad[index] & 0x1F;
}

// seg007:0BCD
__INLINE__ int16_t set_doorlink_timer(int16_t index, uint8_t value)
{
  doorlink2_ad[index] &= 0xE0;
  doorlink2_ad[index] |= value & 0x1F;
  return doorlink2_ad[index];
}

// seg007:0C53
__INLINE__ void  trigger_button(int playsound, int button_type, int modifier)
{
  int8_t link_timer;
  get_curr_tile(curr_tilepos);
  if (button_type == 0)
  {
    // 0 means currently selected
    button_type = curr_tile;
  }
  if (modifier == -1)
  {
    // -1 means currently selected
    modifier = curr_modifier;
  }
  link_timer = get_doorlink_timer(modifier);
  // is the event jammed?
  if (link_timer != 0x1F)
  {
    set_doorlink_timer(modifier, 5);
    if (link_timer < 2)
    {
      add_trob(curr_room, curr_tilepos, 1);
      gameState.is_guard_notice = 1;
    }
    do_trigger_list(modifier, button_type);
  }
}

// seg007:0CD9
__INLINE__ void  died_on_button()
{
  uint16_t button_type;
  uint16_t modifier;
  button_type = get_curr_tile(curr_tilepos);
  modifier = curr_modifier;
  if (curr_tile == tiles_15_opener)
  {
    curr_room_tiles[curr_tilepos] = tiles_1_floor;
    curr_room_modif[curr_tilepos] = 0;
    button_type = tiles_14_debris; // force permanent open
  }
  else
  {
    curr_room_tiles[curr_tilepos] = tiles_5_stuck;
  }
  trigger_button(1, button_type, modifier);
}

// seg007:0D3A
__INLINE__ void  animate_button()
{
  uint16_t var_2;
  if (trob.type >= 0)
  {
    set_doorlink_timer(curr_modifier, var_2 = get_doorlink_timer(curr_modifier) - 1);
    if (var_2 < 2)
    {
      trob.type = -1;
    }
  }
}

// seg007:0D72
__INLINE__ void  start_level_door(int16_t room, int16_t tilepos)
{
  curr_room_modif[tilepos] = 43; // start fully open
  add_trob(room, tilepos, 3);
}

// seg007:0D93
__INLINE__ void  animate_empty()
{
  trob.type = -1;
}

// seg007:0D9D
__INLINE__ void  animate_loose()
{
  uint16_t room;
  uint16_t row;
  uint16_t tilepos;
  int16_t anim_type;
  anim_type = trob.type;
  if (anim_type >= 0)
  {
    ++curr_modifier;
    if (curr_modifier & 0x80)
    {
      // just shaking
      // don't stop on level 13, needed for the auto-falling floors
      if (gameState.current_level == 13)
        return;
      if (curr_modifier >= 0x84)
      {
        curr_modifier = 0;
        trob.type = -1;
      }
      loose_shake(!curr_modifier);
    }
    else
    {
      // something is on the floor
      // should it fall already?
      if (curr_modifier >= /*11*/ custom->loose_floor_delay)
      {
        curr_modifier = remove_loose(room = trob.room, tilepos = trob.tilepos);
        trob.type = -1;
        curmob.xh = (tilepos % 10) << 2;
        row = tilepos / 10;
        curmob.y = y_loose_land[row + 1];
        curmob.room = room;
        curmob.speed = 0;
        curmob.type = 0;
        curmob.row = row;
        add_mob();
      }
      else
      {
        loose_shake(0);
      }
    }
  }
}

// seg007:0E55
__INLINE__ void  loose_shake(int arg_0)
{
  uint16_t sound_id;
  if (arg_0 || loose_sound[curr_modifier & 0x7F])
  {
    do
    {
      // Sounds 20,21,22: loose floor shaking
      sound_id = prandom(2) + sound_20_loose_shake_1;
    } while (sound_id == gameState.last_loose_sound);

    prandom(2); // For vanilla pop compatibility, an RNG cycle is wasted here
                // Note: In DOS PoP, it's wasted a few lines below.
    gameState.last_loose_sound = sound_id;
  }
}

// seg007:0EB8
__INLINE__ int remove_loose(int room, int tilepos)
{
  curr_room_tiles[tilepos] = tiles_0_empty;
  // note: the level type is used to determine the modifier of the empty space left behind
  return custom->tbl_level_type[gameState.current_level];
}

// seg007:0ED5
__INLINE__ void  make_loose_fall(uint8_t modifier)
{
  // is it a "solid" loose floor?
  if ((curr_room_tiles[curr_tilepos] & 0x20) == 0)
  {
    if ((int8_t)curr_room_modif[curr_tilepos] <= 0)
    {
      curr_room_modif[curr_tilepos] = modifier;
      add_trob(curr_room, curr_tilepos, 0);
    }
  }
}

// seg007:0F9A
__INLINE__ int next_chomper_timing(uint8_t timing)
{
  // 15,12,9,6,13,10,7,14,11,8,repeat
  timing -= 3;
  if (timing < 6)
  {
    timing += 10;
  }
  return timing;
}

// seg007:0F13
__INLINE__ void  start_chompers()
{
  int16_t timing;
  int16_t modifier;
  int16_t tilepos;
  int16_t column;
  timing = 15;
  if ((uint8_t)gameState.Char.curr_row < 3)
  {
    get_room_address(gameState.Char.room);
    for (column = 0, tilepos = tbl_line[gameState.Char.curr_row];
         column < 10;
         ++column, ++tilepos)
    {
      if (get_curr_tile(tilepos) == tiles_18_chomper)
      {
        modifier = curr_modifier & 0x7F;
        if (modifier == 0 || modifier >= 6)
        {
          start_anim_chomper(gameState.Char.room, tilepos, timing | (curr_modifier & 0x80));
          timing = next_chomper_timing(timing);
        }
      }
    }
  }
}

// seg007:0FB4
__INLINE__ void  loose_make_shake()
{
  // don't shake on level 13
  if (curr_room_modif[curr_tilepos] == 0 && gameState.current_level != 13)
  {
    curr_room_modif[curr_tilepos] = 0x80;
    add_trob(curr_room, curr_tilepos, 1);
  }
}

// seg007:0FE0
__INLINE__ void  do_knock(int room, int tile_row)
{
  int16_t tile_col;
  for (tile_col = 0; tile_col < 10; ++tile_col)
  {
    if (get_tile(room, tile_col, tile_row) == tiles_11_loose)
    {
      loose_make_shake();
    }
  }
}

// seg007:1010
__INLINE__ void  add_mob()
{
  gameState.mobs[gameState.mobs_count++] = curmob;
}

// seg007:1063
__INLINE__ void  do_mobs()
{
  int16_t n_mobs;
  int16_t index;
  int16_t new_index;
  n_mobs = gameState.mobs_count;
  for (curmob_index = 0; n_mobs > curmob_index; ++curmob_index)
  {
    curmob = gameState.mobs[curmob_index];
    move_mob();
    check_loose_fall_on_kid();
    gameState.mobs[curmob_index] = curmob;
  }
  new_index = 0;
  for (index = 0; index < gameState.mobs_count; ++index)
  {
    if (gameState.mobs[index].speed != -1)
    {
      gameState.mobs[new_index++] = gameState.mobs[index];
    }
  }
  gameState.mobs_count = new_index;
}

// seg007:110F
__INLINE__ void  move_mob()
{
  if (curmob.type == 0)
  {
    move_loose();
  }
  if (curmob.speed <= 0)
  {
    ++curmob.speed;
  }
}

// seg007:1126
__INLINE__ void  move_loose()
{
  if (curmob.speed < 0)
    return;
  if (curmob.speed < 29)
    curmob.speed += 3;
  curmob.y += curmob.speed;
  if (curmob.room == 0)
  {
    if (curmob.y < 210)
    {
      return;
    }
    else
    {
      curmob.speed = -2;
      return;
    }
  }
  if (curmob.y < 226 && y_something[curmob.row + 1] <= curmob.y)
  {
    // fell into a different row
    curr_tile_temp = get_tile(curmob.room, curmob.xh >> 2, curmob.row);
    if (curr_tile_temp == tiles_11_loose)
    {
      loose_fall();
    }
    if (curr_tile_temp == tiles_0_empty ||
        curr_tile_temp == tiles_11_loose)
    {
      mob_down_a_row();
      return;
    }
    do_knock(curmob.room, curmob.row);
    curmob.y = y_something[curmob.row + 1];
    curmob.speed = -2;
    loose_land();
  }
}

// seg007:11E8
__INLINE__ void  loose_land()
{
  int16_t button_type;
  int16_t tiletype;
  button_type = 0;
  tiletype = get_tile(curmob.room, curmob.xh >> 2, curmob.row);
  switch (tiletype)
  {
  case tiles_15_opener:
    curr_room_tiles[curr_tilepos] = tiles_14_debris;
    button_type = tiles_14_debris;
  // fallthrough!
  case tiles_6_closer:
    trigger_button(1, button_type, -1);
    tiletype = get_tile(curmob.room, curmob.xh >> 2, curmob.row);
  // fallthrough!
  case tiles_1_floor:
  case tiles_2_spike:
  case tiles_10_potion:
  case tiles_19_torch:
  case tiles_30_torch_with_debris:
    if (tiletype == tiles_19_torch ||
        tiletype == tiles_30_torch_with_debris)
    {
      curr_room_tiles[curr_tilepos] = tiles_30_torch_with_debris;
    }
    else
    {
      curr_room_tiles[curr_tilepos] = tiles_14_debris;
    }
  }
}

// seg007:12CB
__INLINE__ void  loose_fall()
{
  curr_room_modif[curr_tilepos] = remove_loose(curr_room, curr_tilepos);
  curmob.speed >>= 1;
  gameState.mobs[curmob_index] = curmob;
  curmob.y += 6;
  mob_down_a_row();
  add_mob();
  curmob = gameState.mobs[curmob_index];
}

// seg007:1387
__INLINE__ void  mob_down_a_row()
{
  ++curmob.row;
  if (curmob.row >= 3)
  {
    curmob.y -= 192;
    curmob.row = 0;
    curmob.room = gameState.level.roomlinks[curmob.room - 1].down;
  }
}

// seg007:14DE
__INLINE__ void  add_mob_to_objtable(int ypos)
{
  uint16_t index;
  objtable_type *curr_obj;
  index = __QS_objtable_count++;
  curr_obj = &objtable[index];
  curr_obj->obj_type = curmob.type | 0x80;
  curr_obj->xh = curmob.xh;
  curr_obj->xl = 0;
  curr_obj->y = ypos;
  curr_obj->chtab_id = id_chtab_6_environment;
  curr_obj->id = 10;
  curr_obj->clip.top = 0;
  curr_obj->clip.left = 0;
  curr_obj->clip.right = 40;
}

// seg007:1556
__INLINE__ int is_spike_harmful()
{
  int8_t modifier;
  modifier = curr_room_modif[curr_tilepos];
  if (modifier == 0 || modifier == -1)
  {
    return 0;
  }
  else if (modifier < 0)
  {
    return 1;
  }
  else if (modifier < 5)
  {
    return 2;
  }
  else
  {
    return 0;
  }
}

// seg007:1591
__INLINE__ void  check_loose_fall_on_kid()
{
  loadkid();
  if (gameState.Char.room == curmob.room &&
      gameState.Char.curr_col == curmob.xh >> 2 &&
      curmob.y < gameState.Char.y &&
      gameState.Char.y - 30 < curmob.y)
  {
    fell_on_your_head();
    savekid();
  }
}

// seg007:15D3
__INLINE__ void  fell_on_your_head()
{
  int16_t frame;
  int16_t action;
  frame = gameState.Char.frame;
  action = gameState.Char.action;
  // loose floors hurt you in frames 5..14 (running) only on level 13
  if (
    (gameState.current_level == 13 || (frame < frame_5_start_run || frame >= 15)) &&
    (action < actions_2_hang_climb || action == actions_7_turn))
  {
    gameState.Char.y = y_land[gameState.Char.curr_row + 1];
    if (take_hp(1))
    {
      seqtbl_offset_char(seq_22_crushed); // dead (because of loose floor)
      if (frame == frame_177_spiked)
      { // spiked
        gameState.Char.x = char_dx_forward(-12);
      }
    }
    else
    {
      if (frame != frame_109_crouch)
      { // crouching
        if (get_tile_behind_char() == 0)
        {
          gameState.Char.x = char_dx_forward(-2);
        }
        seqtbl_offset_char(seq_52_loose_floor_fell_on_kid); // loose floor fell on gameState.Kid
      }
    }
  }
}

// seg005:000A
__INLINE__ void  seqtbl_offset_char(int16_t seq_index)
{
  gameState.Char.curr_seq = seqtbl_offsets[seq_index];
}

// seg005:001D
__INLINE__ void  seqtbl_offset_opp(int seq_index)
{
  Opp.curr_seq = seqtbl_offsets[seq_index];
}

// seg005:0030
__INLINE__ void  do_fall()
{
  if (gameState.is_screaming == 0 && gameState.Char.fall_y >= 31)
  {
    gameState.is_screaming = 1;
  }
  if ((uint16_t)y_land[gameState.Char.curr_row + 1] > (uint16_t)gameState.Char.y)
  {
    check_grab();
  }
  else
  {
    if (get_tile_at_char() == tiles_20_wall)
    {
      in_wall();
    }

    if (tile_is_floor(curr_tile2))
    {
      land();
    }
    else
    {
      inc_curr_row();
    }
  }
}

// seg005:0090
__INLINE__ void  land()
{
  uint16_t seq_id;
  gameState.is_screaming = 0;
  gameState.Char.y = y_land[gameState.Char.curr_row + 1];
  if (get_tile_at_char() != tiles_2_spike)
  {
    if (!tile_is_floor(get_tile_infrontof_char()) &&
        distance_to_edge_weight() < 3) gameState.Char.x = char_dx_forward(-3);
    start_chompers();
  }
  else
  {
    // fell on spikes
    goto loc_5EE6;
  }
  if (gameState.Char.alive < 0)
  {
    // alive
    if ((distance_to_edge_weight() >= 12 &&
         get_tile_behind_char() == tiles_2_spike) ||
        get_tile_at_char() == tiles_2_spike)
    {
    // fell on spikes
    loc_5EE6:
      if (is_spike_harmful())
      {
        spiked();
        return;
      }
    }
    {
      if (gameState.Char.fall_y < 22)
      {
      // fell 1 row
      loc_5EFD:
        if (gameState.Char.charid >= charid_2_guard || gameState.Char.sword == sword_2_drawn)
        {
          gameState.Char.sword = sword_2_drawn;
          seq_id = seq_63_guard_stand_active; // stand active after landing
        }
        else
        {
          seq_id = seq_17_soft_land; // crouch (soft land)
        }
        if (gameState.Char.charid == charid_0_kid)
        {
          gameState.is_guard_notice = 1;
        }
      }
      else if (gameState.Char.fall_y < 33)
      {
        // fell 2 rows
        if (gameState.Char.charid == charid_1_shadow)
          goto loc_5EFD;
        if (gameState.Char.charid == charid_2_guard)
          goto loc_5F6C;
        // kid (or skeleton (bug!))
        if (!take_hp(1))
        {
          // still alive
          gameState.is_guard_notice = 1;
          seq_id = seq_20_medium_land; // medium land (lose 1 HP, crouch)
        }
        else
        {
          // dead (this was the last HP)
          goto loc_5F75;
        }
      }
      else
      {
        // fell 3 or more rows
        goto loc_5F6C;
      }
    }
  }
  else
  {
  // dead
  loc_5F6C:
    take_hp(100);
  loc_5F75:
    seq_id = seq_22_crushed; // dead (after falling)
  }
  seqtbl_offset_char(seq_id);
  play_seq();
  gameState.Char.fall_y = 0;
}

// seg005:01B7
__INLINE__ void  spiked()
{
  // If someone falls into spikes, those spikes become harmless (to others).
  curr_room_modif[curr_tilepos] = 0xFF;
  gameState.Char.y = y_land[gameState.Char.curr_row + 1];
  gameState.Char.x = x_bump[tile_col + 5] + 10;
  gameState.Char.x = char_dx_forward(8);
  gameState.Char.fall_y = 0;
  take_hp(100);
  seqtbl_offset_char(seq_51_spiked); // spiked
  play_seq();
}

// seg005:0213
__INLINE__ void  control()
{
  int16_t char_frame;
  int16_t char_action;
  char_frame = gameState.Char.frame;
  if (gameState.Char.alive >= 0)
  {
    if (char_frame == frame_15_stand ||             // stand
        char_frame == frame_166_stand_inactive ||   // stand
        char_frame == frame_158_stand_with_sword || // stand with sword
        char_frame == frame_171_stand_with_sword    // stand with sword
    )
    {
      seqtbl_offset_char(seq_71_dying); // dying (not stabbed)
    }
  }
  else
  {
    char_action = gameState.Char.action;
    if (char_action == actions_5_bumped ||
        char_action == actions_4_in_freefall)
    {
      release_arrows();
    }
    else if (gameState.Char.sword == sword_2_drawn)
    {
      control_with_sword();
    }
    else if (gameState.Char.charid >= charid_2_guard)
    {
      control_guard_inactive();
    }
    else if (char_frame == frame_15_stand ||                  // standing
             (char_frame >= frame_50_turn && char_frame < 53) // end of turning
    )
    {
      control_standing();
    }
    else if (char_frame == frame_48_turn)
    { // a frame in turning
      control_turning();
    }
    else if (char_frame < 4)
    { // start run
      control_startrun();
    }
    else if (char_frame >= frame_67_start_jump_up_1 && char_frame < frame_70_jumphang)
    { // start jump up
      control_jumpup();
    }
    else if (char_frame < 15)
    { // running
      control_running();
    }
    else if (char_frame >= frame_87_hanging_1 && char_frame < 100)
    { // hanging
      control_hanging();
    }
    else if (char_frame == frame_109_crouch)
    { // crouching
      control_crouched();
    }
  }
}

// seg005:02EB
__INLINE__ void  control_crouched()
{
  if (gameState.need_level1_music != 0 && gameState.current_level == /*1*/ custom->intro_music_level)
  {
    gameState.need_level1_music--;
  }
  else
  {
    gameState.need_level1_music = 0;
    if (control_shift2 < 0 && check_get_item()) return;
    if (control_y != 1)
    {
      seqtbl_offset_char(seq_49_stand_up_from_crouch); // stand up from crouch
    }
    else
    {
      if (control_forward < 0)
      {
        control_forward = 1;                   // disable automatic repeat
        seqtbl_offset_char(seq_79_crouch_hop); // crouch-hop
      }
    }
  }
}

// seg005:0358
__INLINE__ void  control_standing()
{
  int16_t var_2;
  if (control_shift2 < 0 && control_shift < 0 && check_get_item())
  {
    return;
  }
  if (gameState.Char.charid != charid_0_kid && control_down < 0 && control_forward < 0)
  {
    draw_sword();
    return;
  } // else
  if (gameState.have_sword)
  {
    if (gameState.offguard != 0 && control_shift >= 0)
      goto loc_6213;
    if (gameState.can_guard_see_kid >= 2)
    {
      var_2 = char_opp_dist();
      if (var_2 >= -10 && var_2 < 90)
      {
        gameState.holding_sword = 1;
        if ((uint16_t)var_2 < (uint16_t)-6)
        {
          if (Opp.charid == charid_1_shadow &&
              (Opp.action == actions_3_in_midair || (Opp.frame >= frame_107_fall_land_1 && Opp.frame < 118)))
          {
            gameState.offguard = 0;
          }
          else
          {
            draw_sword();
            return;
          }
        }
        else
        {
          back_pressed();
          return;
        }
      }
    }
    else
    {
      gameState.offguard = 0;
    }
  }
  if (control_shift < 0)
  {
    if (control_backward < 0)
    {
      back_pressed();
    }
    else if (control_up < 0)
    {
      up_pressed();
    }
    else if (control_down < 0)
    {
      down_pressed();
    }
    else if (control_x < 0 && control_forward < 0)
    {
      safe_step();
    }
  }
  else
  loc_6213:
    if (control_forward < 0)
    {
      if (control_up < 0)
      {
        standing_jump();
      }
      else
      {
        forward_pressed();
      }
    }
    else if (control_backward < 0)
    {
      back_pressed();
    }
    else if (control_up < 0)
    {
      if (control_forward < 0)
      {
        standing_jump();
      }
      else
      {
        up_pressed();
      }
    }
    else if (control_down < 0)
    {
      down_pressed();
    }
    else if (control_x < 0)
    {
      forward_pressed();
    }
}

// seg005:0482
__INLINE__ void  up_pressed()
{
  int leveldoor_tilepos = -1;
  if (get_tile_at_char() == tiles_16_level_door_left)
    leveldoor_tilepos = curr_tilepos;
  else if (get_tile_behind_char() == tiles_16_level_door_left)
    leveldoor_tilepos = curr_tilepos;
  else if (get_tile_infrontof_char() == tiles_16_level_door_left)
    leveldoor_tilepos = curr_tilepos;
  if ((leveldoor_tilepos != -1) && gameState.level.start_room != gameState.drawn_room && gameState.leveldoor_open)
  {
    go_up_leveldoor();
  }
  else
  {
    if (control_x < 0)
    {
      standing_jump();
    }
    else
    {
      check_jump_up();
    }
  }
}

// seg005:04C7
__INLINE__ void  down_pressed()
{
  control_down = 1; // disable automatic repeat
  if (!tile_is_floor(get_tile_infrontof_char()) &&
      distance_to_edge_weight() < 3)
  {
    gameState.Char.x = char_dx_forward(5);
    load_fram_det_col();
  }
  else
  {
    if (!tile_is_floor(get_tile_behind_char()) &&
        distance_to_edge_weight() >= 8)
    {
      through_tile = get_tile_behind_char();
      get_tile_at_char();
      if (can_grab() &&
          (gameState.Char.direction >= dir_0_right ||
           get_tile_at_char() != tiles_4_gate ||
           curr_room_modif[curr_tilepos] >> 2 >= 6))
      {
        gameState.Char.x = char_dx_forward(distance_to_edge_weight() - 9);
        seqtbl_offset_char(seq_68_climb_down); // climb down
      }
      else
      {
        crouch();
      }
    }
    else
    {
      crouch();
    }
  }
}

// seg005:0574
__INLINE__ void  go_up_leveldoor()
{
  gameState.Char.x = x_bump[tile_col + 5] + 10;
  gameState.Char.direction = dir_FF_left;         // right
  seqtbl_offset_char(seq_70_go_up_on_level_door); // go up on level door
}

// seg005:058F
__INLINE__ void  control_turning()
{
  if (control_shift >= 0 && control_x < 0 && control_y >= 0)
  {
    seqtbl_offset_char(seq_43_start_run_after_turn); // start run and run (after turning)
  }
}

// seg005:05AD
__INLINE__ void  crouch()
{
  seqtbl_offset_char(seq_50_crouch); // crouch
  control_down = release_arrows();
}

// seg005:05BE
__INLINE__ void  back_pressed()
{
  uint16_t seq_id;
  control_backward = release_arrows();
  // After turn, gameState.Kid will draw sword if ...
  if (gameState.have_sword == 0 ||       // if gameState.Kid has sword
      gameState.can_guard_see_kid < 2 || // and can see Guard
      char_opp_dist() > 0 ||             // and Guard was behind him
      distance_to_edge_weight() < 2)
  {
    seq_id = seq_5_turn; // turn
  }
  else
  {
    gameState.Char.sword = sword_2_drawn;
    gameState.offguard = 0;
    seq_id = seq_89_turn_draw_sword; // turn and draw sword
  }
  seqtbl_offset_char(seq_id);
}

// seg005:060F
__INLINE__ void  forward_pressed()
{
  int16_t distance;
  distance = get_edge_distance();

  if (edge_type == 1 && curr_tile2 != tiles_18_chomper && distance < 8)
  {
    // If char is  a wall, step instead of run.
    if (control_forward < 0)
    {
      safe_step();
    }
  }
  else
  {
    seqtbl_offset_char(seq_1_start_run); // start run and run
  }
}

// seg005:0649
__INLINE__ void  control_running()
{
  if (control_x == 0 && (gameState.Char.frame == frame_7_run || gameState.Char.frame == frame_11_run))
  {
    control_forward = release_arrows();
    seqtbl_offset_char(seq_13_stop_run); // stop run
  }
  else if (control_x > 0)
  {
    control_backward = release_arrows();
    seqtbl_offset_char(seq_6_run_turn); // run-turn
  }
  else if (control_y < 0 && control_up < 0)
  {
    run_jump();
  }
  else if (control_down < 0)
  {
    control_down = 1;                                // disable automatic repeat
    seqtbl_offset_char(seq_26_crouch_while_running); // crouch while running
  }
}

// seg005:06A8
__INLINE__ void  safe_step()
{
  int16_t distance;
  control_shift2 = 1;  // disable automatic repeat
  control_forward = 1; // disable automatic repeat
  distance = get_edge_distance();
  if (distance)
  {
    gameState.Char.repeat = 1;
    seqtbl_offset_char(distance + 28); // 29..42: safe step to edge
  }
  else if (edge_type != 1 && gameState.Char.repeat != 0)
  {
    gameState.Char.repeat = 0;
    seqtbl_offset_char(seq_44_step_on_edge); // step on edge
  }
  else
  {
    seqtbl_offset_char(seq_39_safe_step_11); // unsafe step (off ledge)
  }
}

// seg005:06F0
__INLINE__ int check_get_item()
{
  if (get_tile_at_char() == tiles_10_potion ||
      curr_tile2 == tiles_22_sword)
  {
    if (!tile_is_floor(get_tile_behind_char()))
    {
      return 0;
    }
    gameState.Char.x = char_dx_forward(-14);
    load_fram_det_col();
  }
  if (get_tile_infrontof_char() == tiles_10_potion ||
      curr_tile2 == tiles_22_sword)
  {
    get_item();
    return 1;
  }
  return 0;
}

// seg005:073E
__INLINE__ void  get_item()
{
  int16_t distance;
  if (gameState.Char.frame != frame_109_crouch)
  { // crouching
    distance = get_edge_distance();
    if (edge_type != 2)
    {
      gameState.Char.x = char_dx_forward(distance);
    }
    if (gameState.Char.direction >= dir_0_right)
    {
      gameState.Char.x = char_dx_forward((curr_tile2 == tiles_10_potion) - 2);
    }
    crouch();
  }
  else if (curr_tile2 == tiles_22_sword)
  {
    do_pickup(-1);
    seqtbl_offset_char(seq_91_get_sword); // get sword
  }
  else
  { // potion
    do_pickup(curr_room_modif[curr_tilepos] >> 3);
    seqtbl_offset_char(seq_78_drink); // drink
    if (gameState.current_level == 15)
    {
      int16_t index;
      for (index = 0; index < 14; ++index)
      {
        // remove letter on potions level
        if (copyprot_room[index] == curr_room &&
            copyprot_tile[index] == curr_tilepos)
        {
          copyprot_room[index] = 0;
          break;
        }
      }
    }
  }
}

// seg005:07FF
__INLINE__ void  control_startrun()
{
  if (control_y < 0 && control_x < 0)
  {
    standing_jump();
  }
}

// seg005:0812
__INLINE__ void  control_jumpup()
{
  if (control_x < 0 || control_forward < 0)
  {
    standing_jump();
  }
}

// seg005:0825
__INLINE__ void  standing_jump()
{
  control_up = control_forward = 1;        // disable automatic repeat
  seqtbl_offset_char(seq_3_standing_jump); // standing jump
}

// seg005:0836
__INLINE__ void  check_jump_up()
{
  control_up = release_arrows();
  through_tile = get_tile_above_char();
  get_tile_front_above_char();
  if (can_grab())
  {
    grab_up_with_floor_behind();
  }
  else
  {
    through_tile = get_tile_behind_above_char();
    get_tile_above_char();
    if (can_grab())
    {
      jump_up_or_grab();
    }
    else
    {
      jump_up();
    }
  }
}

// seg005:087B
__INLINE__ void  jump_up_or_grab()
{
  int16_t distance;
  distance = distance_to_edge_weight();
  if (distance < 6)
  {
    jump_up();
  }
  else if (!tile_is_floor(get_tile_behind_char()))
  {
    // There is not floor behind char.
    grab_up_no_floor_behind();
  }
  else
  {
    // There is floor behind char, go back a bit.
    gameState.Char.x = char_dx_forward(distance - 14);
    load_fram_det_col();
    grab_up_with_floor_behind();
  }
}

// seg005:08C7
__INLINE__ void  grab_up_no_floor_behind()
{
  get_tile_above_char();
  gameState.Char.x = char_dx_forward(distance_to_edge_weight() - 10);
  seqtbl_offset_char(seq_16_jump_up_and_grab); // jump up and grab (no floor behind)
}

// seg005:08E6
__INLINE__ void  jump_up()
{
  int16_t distance;
  control_up = release_arrows();
  distance = get_edge_distance();
  if (distance < 4 && edge_type == 1)
  {
    gameState.Char.x = char_dx_forward(distance - 3);
  }
  get_tile(gameState.Char.room, get_tile_div_mod(back_delta_x(0) + dx_weight() - 6), gameState.Char.curr_row - 1);
  if (curr_tile2 != tiles_20_wall && !tile_is_floor(curr_tile2))
  {
    seqtbl_offset_char(seq_28_jump_up_with_nothing_above); // jump up with nothing above
  }
  else
  {
    seqtbl_offset_char(seq_14_jump_up_into_ceiling); // jump up with wall or floor above
  }
}

// seg005:0968
__INLINE__ void  control_hanging()
{
  if (gameState.Char.alive < 0)
  {
    if (gameState.grab_timer == 0 && control_y < 0)
    {
      can_climb_up();
    }
    else if (control_shift < 0)
    {
      // hanging against a wall or a doortop
      if (gameState.Char.action != actions_6_hang_straight &&
          (get_tile_at_char() == tiles_20_wall ||
           (gameState.Char.direction == dir_FF_left && ( // facing left
                                                         curr_tile2 == tiles_7_doortop_with_floor ||
                                                         curr_tile2 == tiles_12_doortop))))
      {
        if (gameState.grab_timer == 0)
        {
        }
        seqtbl_offset_char(seq_25_hang_against_wall); // hang against wall (straight)
      }
      else
      {
        if (!tile_is_floor(get_tile_above_char()))
        {
          hang_fall();
        }
      }
    }
    else
    {
      hang_fall();
    }
  }
  else
  {
    hang_fall();
  }
}

// seg005:09DF
__INLINE__ void  can_climb_up()
{
  int16_t seq_id;
  seq_id = seq_10_climb_up; // climb up
  control_up = control_shift2 = release_arrows();
  get_tile_above_char();
  if (((curr_tile2 == tiles_13_mirror || curr_tile2 == tiles_18_chomper) &&
       gameState.Char.direction == dir_0_right) ||
      (curr_tile2 == tiles_4_gate && gameState.Char.direction != dir_0_right &&
       curr_room_modif[curr_tilepos] >> 2 < 6))
  {
    seq_id = seq_73_climb_up_to_closed_gate; // climb up to closed gate and down
  }
  seqtbl_offset_char(seq_id);
}

// seg005:0A46
__INLINE__ void  hang_fall()
{
  control_down = release_arrows();
  if (!tile_is_floor(get_tile_behind_char()) &&
      !tile_is_floor(get_tile_at_char()))
  {
    seqtbl_offset_char(seq_23_release_ledge_and_fall); // release ledge and fall
  }
  else
  {
    if (get_tile_at_char() == tiles_20_wall ||
        (gameState.Char.direction < dir_0_right && ( // looking left
                                                     curr_tile2 == tiles_7_doortop_with_floor ||
                                                     curr_tile2 == tiles_12_doortop)))
    {
      gameState.Char.x = char_dx_forward(-7);
    }
    seqtbl_offset_char(seq_11_release_ledge_and_land); // end of climb down
  }
}

// seg005:0AA8
__INLINE__ void  grab_up_with_floor_behind()
{
  int16_t distance;
  distance = distance_to_edge_weight();

  // The global variable edge_type (which we need!) gets set as a side effect of get_edge_distance()
  int16_t edge_distance = get_edge_distance();
  // printf("Distance to edge weight: %d\tedge type: %d\tedge distance: %d\n", distance, edge_type, edge_distance);

  if (__QS_JUMP_STRAIGHT_CONDITION)
  {
    gameState.Char.x = char_dx_forward(distance);
    seqtbl_offset_char(seq_8_jump_up_and_grab_straight); // jump up and grab (when?)
  }
  else
  {
    gameState.Char.x = char_dx_forward(distance - 4);
    seqtbl_offset_char(seq_24_jump_up_and_grab_forward); // jump up and grab (with floor behind)
  }
}

// seg005:0AF7
__INLINE__ void  run_jump()
{
  int16_t var_2;
  int16_t xpos;
  int16_t col;
  int16_t var_8;
  if (gameState.Char.frame >= frame_7_run)
  {
    // Align gameState.Kid to edge of floor.
    xpos = char_dx_forward(4);
    col = get_tile_div_mod_m7(xpos);
    for (var_2 = 0; var_2 < 2; ++var_2)
    {
      col += dir_front[gameState.Char.direction + 1];
      get_tile(gameState.Char.room, col, gameState.Char.curr_row);
      if (curr_tile2 == tiles_2_spike || !tile_is_floor(curr_tile2))
      {
        var_8 = distance_to_edge(xpos) + 14 * var_2 - 14;
        if ((uint16_t)var_8 < (uint16_t)-8 || var_8 >= 2)
        {
          if (var_8 < 128)
            return;
          var_8 = -3;
        }
        gameState.Char.x = char_dx_forward(var_8 + 4);
        break;
      }
    }
    control_up = release_arrows();      // disable automatic repeat
    seqtbl_offset_char(seq_4_run_jump); // run-jump
  }
}

// sseg005:0BB5
__INLINE__ void  back_with_sword()
{
  int16_t frame;
  frame = gameState.Char.frame;
  if (frame == frame_158_stand_with_sword || frame == frame_170_stand_with_sword || frame == frame_171_stand_with_sword)
  {
    control_backward = 1;                       // disable automatic repeat
    seqtbl_offset_char(seq_57_back_with_sword); // back with sword
  }
}

// seg005:0BE3
__INLINE__ void  forward_with_sword()
{
  int16_t frame;
  frame = gameState.Char.frame;
  if (frame == frame_158_stand_with_sword || frame == frame_170_stand_with_sword || frame == frame_171_stand_with_sword)
  {
    control_forward = 1; // disable automatic repeat
    if (gameState.Char.charid != charid_0_kid)
    {
      seqtbl_offset_char(seq_56_guard_forward_with_sword); // forward with sword (Guard)
    }
    else
    {
      seqtbl_offset_char(seq_86_forward_with_sword); // forward with sword (gameState.Kid)
    }
  }
}

// seg005:0C1D
__INLINE__ void  draw_sword()
{
  uint16_t seq_id;
  seq_id = seq_55_draw_sword; // draw sword
  control_forward = control_shift2 = release_arrows();
  if (gameState.Char.charid == charid_0_kid)
  {
    gameState.offguard = 0;
  }
  else if (gameState.Char.charid != charid_1_shadow)
  {
    seq_id = seq_90_en_garde; // stand active
  }
  gameState.Char.sword = sword_2_drawn;
  seqtbl_offset_char(seq_id);
}

// seg005:0C67
__INLINE__ void  control_with_sword()
{
  int16_t distance;
  if (gameState.Char.action < actions_2_hang_climb)
  {
    if (get_tile_at_char() == tiles_11_loose || gameState.can_guard_see_kid >= 2)
    {
      distance = char_opp_dist();
      if ((uint16_t)distance < (uint16_t)90)
      {
        swordfight();
        return;
      }
      else if (distance < 0)
      {
        if ((uint16_t)distance < (uint16_t)-4)
        {
          seqtbl_offset_char(seq_60_turn_with_sword); // turn with sword (after switching places)
          return;
        }
        else
        {
          swordfight();
          return;
        }
      }
    } /*else*/
    {
      if (gameState.Char.charid == charid_0_kid && gameState.Char.alive < 0)
      {
        gameState.holding_sword = 0;
      }
      if (gameState.Char.charid < charid_2_guard)
      {
        // frame 171: stand with sword
        if (gameState.Char.frame == frame_171_stand_with_sword)
        {
          gameState.Char.sword = sword_0_sheathed;
          seqtbl_offset_char(seq_92_put_sword_away); // put sword away (Guard died)
        }
      }
      else
      {
        swordfight();
      }
    }
  }
}

// seg005:0CDB
__INLINE__ void  swordfight()
{
  int16_t frame;
  int16_t seq_id;
  int16_t charid;
  frame = gameState.Char.frame;
  charid = gameState.Char.charid;
  // frame 161: parry
  if (frame == frame_161_parry && control_shift2 >= 0)
  {
    seqtbl_offset_char(seq_57_back_with_sword); // back with sword (when parrying)
    return;
  }
  else if (control_shift2 < 0)
  {
    if (charid == charid_0_kid)
    {
      gameState.kid_sword_strike = 15;
    }
    sword_strike();
    if (control_shift2 == 1)
      return;
  }
  if (control_down < 0)
  {
    if (frame == frame_158_stand_with_sword || frame == frame_170_stand_with_sword || frame == frame_171_stand_with_sword)
    {
      control_down = 1; // disable automatic repeat
      gameState.Char.sword = sword_0_sheathed;
      if (charid == charid_0_kid)
      {
        gameState.offguard = 1;
        gameState.guard_refrac = 9;
        gameState.holding_sword = 0;
        seq_id = seq_93_put_sword_away_fast; // put sword away fast (down pressed)
      }
      else if (charid == charid_1_shadow)
      {
        seq_id = seq_92_put_sword_away; // put sword away
      }
      else
      {
        seq_id = seq_87_guard_become_inactive; // stand inactive (when gameState.Kid leaves sight)
      }
      seqtbl_offset_char(seq_id);
    }
  }
  else if (control_up < 0)
  {
    parry();
  }
  else if (control_forward < 0)
  {
    forward_with_sword();
  }
  else if (control_backward < 0)
  {
    back_with_sword();
  }
}

// seg005:0DB0
__INLINE__ void  sword_strike()
{
  int16_t frame;
  int16_t seq_id;
  frame = gameState.Char.frame;
  if (frame == frame_157_walk_with_sword ||  // walk with sword
      frame == frame_158_stand_with_sword || // stand with sword
      frame == frame_170_stand_with_sword || // stand with sword
      frame == frame_171_stand_with_sword || // stand with sword
      frame == frame_165_walk_with_sword     // walk with sword
  )
  {
    if (gameState.Char.charid == charid_0_kid)
    {
      seq_id = seq_75_strike; // strike with sword (gameState.Kid)
    }
    else
    {
      seq_id = seq_58_guard_strike; // strike with sword (Guard)
    }
  }
  else if (frame == frame_150_parry || frame == frame_161_parry)
  {                                     // parry
    seq_id = seq_66_strike_after_parry; // strike with sword after parrying
  }
  else
  {
    return;
  }
  control_shift2 = 1; // disable automatic repeat
  seqtbl_offset_char(seq_id);
}

// seg005:0E0F
__INLINE__ void  parry()
{
  int16_t opp_frame;
  int16_t char_frame;
  int16_t var_6;
  int16_t seq_id;
  int16_t char_charid;
  char_frame = gameState.Char.frame;
  opp_frame = Opp.frame;
  char_charid = gameState.Char.charid;
  seq_id = seq_62_parry; // defend (parry) with sword
  var_6 = 0;
  if (
    char_frame == frame_158_stand_with_sword || // stand with sword
    char_frame == frame_170_stand_with_sword || // stand with sword
    char_frame == frame_171_stand_with_sword || // stand with sword
    char_frame == frame_168_back ||             // back?
    char_frame == frame_165_walk_with_sword     // walk with sword
  )
  {
    if (char_opp_dist() >= 32 && char_charid != charid_0_kid)
    {
      back_with_sword();
      return;
    }
    else if (char_charid == charid_0_kid)
    {
      if (opp_frame == frame_168_back)
        return;
      if (opp_frame != frame_151_strike_1 &&
          opp_frame != frame_152_strike_2 &&
          opp_frame != frame_162_block_to_strike)
      {
        if (opp_frame == frame_153_strike_3)
        { // strike
          var_6 = 1;
        }
        else if (char_charid != charid_0_kid)
        {
          back_with_sword();
          return;
        }
      }
    }
    else
    {
      if (opp_frame != frame_152_strike_2)
        return;
    }
  }
  else
  {
    if (char_frame != frame_167_blocked)
      return;
    seq_id = seq_61_parry_after_strike; // parry after striking with sword
  }
  control_up = 1; // disable automatic repeat
  seqtbl_offset_char(seq_id);
  if (var_6)
  {
    play_seq();
  }
}

// seg008:0006
__INLINE__ void  redraw_room()
{
  memset(table_counts, 0, sizeof(table_counts));
  reset_obj_clip();
  draw_room();
}

// seg008:0035
__INLINE__ void  load_room_links()
{
  room_BR = 0;
  room_BL = 0;
  room_AR = 0;
  room_AL = 0;
  if (gameState.drawn_room)
  {
    get_room_address(gameState.drawn_room);
    room_L = gameState.level.roomlinks[gameState.drawn_room - 1].left;
    room_R = gameState.level.roomlinks[gameState.drawn_room - 1].right;
    room_A = gameState.level.roomlinks[gameState.drawn_room - 1].up;
    room_B = gameState.level.roomlinks[gameState.drawn_room - 1].down;
    if (room_A)
    {
      room_AL = gameState.level.roomlinks[room_A - 1].left;
      room_AR = gameState.level.roomlinks[room_A - 1].right;
    }
    else
    {
      if (room_L)
      {
        room_AL = gameState.level.roomlinks[room_L - 1].up;
      }
      if (room_R)
      {
        room_AR = gameState.level.roomlinks[room_R - 1].up;
      }
    }
    if (room_B)
    {
      room_BL = gameState.level.roomlinks[room_B - 1].left;
      room_BR = gameState.level.roomlinks[room_B - 1].right;
    }
    else
    {
      if (room_L)
      {
        room_BL = gameState.level.roomlinks[room_L - 1].down;
      }
      if (room_R)
      {
        room_BR = gameState.level.roomlinks[room_R - 1].down;
      }
    }
  }
  else
  {
    room_B = 0;
    room_A = 0;
    room_R = 0;
    room_L = 0;
  }
}

// seg008:0125
__INLINE__ void  draw_room()
{
  uint16_t saved_room;
  saved_room = gameState.drawn_room;
  gameState.drawn_room = room_A;
  load_room_links();
  drawn_row = 2;
  for (drawn_col = 0; drawn_col < 10; ++drawn_col)
  {
    draw_main_y = -1;
    draw_bottom_y = 2;
  }
  gameState.drawn_room = saved_room;
  load_room_links();
}

// seg008:1E0C
__INLINE__ void  get_room_address(int room)
{
  if (room)
  {
    curr_room_tiles = &gameState.level.fg[(room - 1) * 30];
    curr_room_modif = &gameState.level.bg[(room - 1) * 30];
  }
}

// seg008:2448
__INLINE__ void  load_frame_to_obj()
{
  uint16_t chtab_base;
  chtab_base = id_chtab_2_kid;
  reset_obj_clip();
  load_frame();
  obj_direction = gameState.Char.direction;
  obj_id = cur_frame.image;
  // top 6 bits of sword are the chtab
  obj_chtab = chtab_base + (cur_frame.sword >> 6);
  obj_x = (char_dx_forward(cur_frame.dx) << 1) - 116;
  obj_y = cur_frame.dy + gameState.Char.y;
  if ((int8_t)(cur_frame.flags ^ obj_direction) >= 0)
  {
    // 0x80: even/odd pixel
    ++obj_x;
  }
}

}; // class quickerSDLPoP

} // namespace quicker