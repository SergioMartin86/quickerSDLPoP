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

namespace quicker
{

  #define __QS_BASE_FPS 60
  #define __QS_FEATHER_FALL_LENGTH 18.75
  #define __QS_MAX_CACHED_FILES 2048
  #define __QS_POP_MAX_PATH 1024
  #define __QS__COUNT(array) (sizeof(array) / sizeof(array[0]))
  #define __QS_NUM_GUARD_SKILLS 12

typedef struct rect_type
{
  int16_t top, left, bottom, right;
} rect_type;

typedef struct piece
{
  uint8_t base_id;
  uint8_t floor_left;
  int8_t base_y;
  uint8_t right_id;
  uint8_t floor_right;
  int8_t right_y;
  uint8_t stripe_id;
  uint8_t topright_id;
  uint8_t bottom_id;
  uint8_t fore_id;
  uint8_t fore_x;
  int8_t fore_y;
} piece;
typedef struct tile_and_mod
{
  uint8_t tiletype;
  uint8_t modifier;
} tile_and_mod;

typedef int   (*add_table_type)(int16_t chtab_id, int id, int8_t xh, int8_t xl, int ybottom, int blit, uint8_t peel);

typedef struct back_table_type
{
  int8_t xh;
  int8_t xl;
  int16_t y;
  uint8_t chtab_id;
  uint8_t id;
  int blit;
} back_table_type;

typedef struct midtable_type
{
  int8_t xh;
  int8_t xl;
  int16_t y;
  uint8_t chtab_id;
  uint8_t id;
  uint8_t peel;
  rect_type clip;
  int blit;
} midtable_type;

typedef struct wipetable_type
{
  int16_t left;
  int16_t bottom;
  int8_t height;
  int16_t width;
  int8_t color;
  int8_t layer;
} wipetable_type;

enum soundflags
{
  sfDigi = 1,
  sfMidi = 2,
  soundflags_4 = 4,
  sfLoop = 0x80
};

enum tiles
{
  tiles_0_empty = 0,
  tiles_1_floor = 1,
  tiles_2_spike = 2,
  tiles_3_pillar = 3,
  tiles_4_gate = 4,
  tiles_5_stuck = 5,
  tiles_6_closer = 6,             // a.k.a. drop button
  tiles_7_doortop_with_floor = 7, // a.k.a. tapestry
  tiles_8_bigpillar_bottom = 8,
  tiles_9_bigpillar_top = 9,
  tiles_10_potion = 10,
  tiles_11_loose = 11,
  tiles_12_doortop = 12, // a.k.a. tapestry top
  tiles_13_mirror = 13,
  tiles_14_debris = 14,          // a.k.a. broken floor
  tiles_15_opener = 15,          // a.k.a. raise button
  tiles_16_level_door_left = 16, // a.k.a. exit door
  tiles_17_level_door_right = 17,
  tiles_18_chomper = 18,
  tiles_19_torch = 19,
  tiles_20_wall = 20,
  tiles_21_skeleton = 21,
  tiles_22_sword = 22,
  tiles_23_balcony_left = 23,
  tiles_24_balcony_right = 24,
  tiles_25_lattice_pillar = 25,
  tiles_26_lattice_down = 26, // a.k.a. lattice support
  tiles_27_lattice_small = 27,
  tiles_28_lattice_left = 28,
  tiles_29_lattice_right = 29,
  tiles_30_torch_with_debris = 30
};

enum chtabs
{
  id_chtab_0_sword = 0,
  id_chtab_1_flameswordpotion = 1,
  id_chtab_2_kid = 2,
  id_chtab_3_princessinstory = 3,
  id_chtab_4_jaffarinstory_princessincutscenes = 4,
  id_chtab_5_guard = 5,
  id_chtab_6_environment = 6,
  id_chtab_7_environmentwall = 7,
  id_chtab_8_princessroom = 8,
  id_chtab_9_princessbed = 9
};

enum blitters
{
  blitters_0_no_transp = 0,
  // It seems to me that the "or" blitter can be safely replaced with the "transparent" blitter.
  blitters_2_or = 2,
  blitters_3_xor = 3, // used for the shadow
  blitters_white = 8,
  blitters_9_black = 9,
  blitters_10h_transp = 0x10,
  /* 0x40..0x4F will draw a monochrome image with color 0..15 */
  blitters_40h_mono = 0x40,
  blitters_46h_mono_6 = 0x46,  // used for palace wall patterns
  blitters_4Ch_mono_12 = 0x4C, // used for chomper blood
};

enum full_image_id
{
  TITLE_MAIN = 0,
  TITLE_PRESENTS,
  TITLE_GAME,
  TITLE_POP,
  TITLE_MECHNER,
  HOF_POP,
  STORY_FRAME,
  STORY_ABSENCE,
  STORY_MARRY,
  STORY_HAIL,
  STORY_CREDITS,
  MAX_FULL_IMAGES
};

enum grmodes
{
  gmCga = 1,
  gmHgaHerc = 2,
  gmEga = 3,
  gmTga = 4,
  gmMcgaVga = 5
};

enum sound_modes
{
  smAuto = 0,
  smAdlib = 1,
  smGblast = 2,
  smSblast = 3,
  smCovox = 4,
  smIbmg = 5,
  smTandy = 6
};

  #pragma pack(push, 1)
typedef struct link_type
{
  uint8_t left, right, up, down;
} link_type;

typedef struct level_type
{
  uint8_t fg[720];
  uint8_t bg[720];
  uint8_t doorlinks1[256];
  uint8_t doorlinks2[256];
  link_type roomlinks[24];
  uint8_t used_rooms;
  uint8_t roomxs[24];
  uint8_t roomys[24];
  uint8_t fill_1[15];
  uint8_t start_room;
  uint8_t start_pos;
  int8_t start_dir;
  uint8_t fill_2[4];
  uint8_t guards_tile[24];
  uint8_t guards_dir[24];
  uint8_t guards_x[24];
  uint8_t guards_seq_lo[24];
  uint8_t guards_skill[24];
  uint8_t guards_seq_hi[24];
  uint8_t guards_color[24];
  uint8_t fill_3[18];
} level_type;
static_assert(sizeof(level_type) == 2305);
  #pragma pack(pop)

typedef struct image_type
{
  int h;
  int w;
} image_type;

typedef struct peel_type
{
  rect_type rect;
} peel_type;

typedef struct chtab_type
{
  uint16_t n_images;
  uint16_t chtab_palette_bits;
  uint16_t has_palette_bits;
  // This is a variable-size array, with n_images elements.
  image_type * images[];
} chtab_type;

typedef struct full_image_type
{
  int id;
  chtab_type **chtab;
  enum blitters blitter;
  int xpos, ypos;
} full_image_type;

  #pragma pack(push, 1)
typedef struct rgb_type
{
  uint8_t r, g, b;
} rgb_type;
typedef struct dat_pal_type
{
  uint16_t row_bits;
  uint8_t n_colors;
  rgb_type vga[16];
  uint8_t cga[16];
  uint8_t ega[32];
} dat_pal_type;
typedef struct dat_shpl_type
{
  uint8_t n_images;
  dat_pal_type palette;
} dat_shpl_type;
static_assert(sizeof(dat_shpl_type) == 100);
  #pragma pack(pop)

typedef struct char_type
{
  uint8_t frame;
  uint8_t x;
  uint8_t y;
  int8_t direction;
  int8_t curr_col;
  int8_t curr_row;
  uint8_t action;
  int8_t fall_x;
  int8_t fall_y;
  uint8_t room;
  uint8_t repeat;
  uint8_t charid;
  uint8_t sword;
  int8_t alive;
  uint16_t curr_seq;
} char_type;

enum charids
{
  charid_0_kid = 0,
  charid_1_shadow = 1,
  charid_2_guard = 2,
  charid_3 = 3,
  charid_4_skeleton = 4,
  charid_5_princess = 5,
  charid_6_vizier = 6,
  charid_24_mouse = 0x18
};

enum sword_status
{
  sword_0_sheathed = 0,
  sword_2_drawn = 2
};

typedef struct auto_move_type
{
  int16_t time, move;
} auto_move_type;

/* obj_type:
  0 = Kid, princess, vizier
  1 = shadow
  2 = Guard
  3 = sword
  4 = mirror image
  5 = hurt splash
  0x80 = loose floor
*/
typedef struct objtable_type
{
  int8_t xh;
  int8_t xl;
  int16_t y;
  uint8_t chtab_id;
  uint8_t id;
  int8_t direction;
  uint8_t obj_type;
  rect_type clip;
  uint8_t tilepos;
} objtable_type;

typedef struct frame_type
{
  uint8_t image;

  // 0x3F: sword image
  // 0xC0: chtab
  uint8_t sword;

  int8_t dx;
  int8_t dy;

  // 0x1F: weight x
  // 0x20: thin
  // 0x40: needs floor
  // 0x80: even/odd pixel
  uint8_t flags;
} frame_type;

enum frame_flags
{
  FRAME_WEIGHT_X = 0x1F,
  FRAME_THIN = 0x20,
  FRAME_NEEDS_FLOOR = 0x40,
  FRAME_EVEN_ODD_PIXEL = 0x80,
};

typedef struct trob_type
{
  uint8_t tilepos;
  uint8_t room;
  int8_t type;
} trob_type;

typedef struct mob_type
{
  uint8_t xh;
  uint8_t y;
  uint8_t room;
  int8_t speed;
  uint8_t type;
  uint8_t row;
} mob_type;

enum directions
{
  dir_0_right = 0x00,
  dir_56_none = 0x56,
  dir_FF_left = -1
};

enum actions
{
  actions_0_stand = 0,
  actions_1_run_jump = 1,
  actions_2_hang_climb = 2,
  actions_3_in_midair = 3,
  actions_4_in_freefall = 4,
  actions_5_bumped = 5,
  actions_6_hang_straight = 6,
  actions_7_turn = 7,
  actions_99_hurt = 99,
};

typedef struct sword_table_type
{
  uint8_t id;
  int8_t x;
  int8_t y;
} sword_table_type;

  #pragma pack(push, 1)
typedef struct dat_header_type
{
  uint32_t table_offset;
  uint16_t table_size;
} dat_header_type;
static_assert(sizeof(dat_header_type) == 6);

typedef struct dat_res_type
{
  uint16_t id;
  uint32_t offset;
  uint16_t size;
} dat_res_type;
static_assert(sizeof(dat_res_type) == 8);

typedef struct dat_table_type
{
  uint16_t res_count;
  dat_res_type entries[];
} dat_table_type;
static_assert(sizeof(dat_table_type) == 2);

typedef struct image_data_type
{
  uint16_t height;
  uint16_t width;
  uint16_t flags;
  uint8_t data[];
} image_data_type;
static_assert(sizeof(image_data_type) == 6);
  #pragma pack(pop)

typedef struct dat_type
{
  struct dat_type *next_dat;
  FILE *handle;
  char filename[__QS_POP_MAX_PATH];
  dat_table_type *dat_table;
  // handle and dat_table are NULL if the DAT is a directory.
} dat_type;

typedef void   (*cutscene_ptr_type)();

typedef enum data_location
{
  data_none = 0,
  data_DAT = 1,
  data_directory = 2
} data_location;

enum sound_type
{
  sound_speaker = 0,
  sound_digi = 1,
  sound_midi = 2,
  sound_chunk = 3,
  sound_music = 4,
  sound_digi_converted = 6,
};
  #pragma pack(push, 1)
typedef struct note_type
{
  uint16_t frequency; // 0x00 or 0x01 = rest, 0x12 = end
  uint8_t length;
} note_type;
static_assert(sizeof(note_type) == 3);
typedef struct speaker_type
{ // IBM
  uint16_t tempo;
  note_type notes[];
} speaker_type;
static_assert(sizeof(speaker_type) == 2);

typedef struct digi_type
{ // wave in 1.0 and 1.1
  uint16_t sample_rate;
  uint16_t sample_count;
  uint16_t unknown;
  uint8_t sample_size; // =8
  uint8_t samples[];
} digi_type;
static_assert(sizeof(digi_type) == 7);

typedef struct digi_new_type
{ // wave in 1.3 and 1.4 (and PoP2)
  uint16_t sample_rate;
  uint8_t sample_size; // =8
  uint16_t sample_count;
  uint16_t unknown;
  uint16_t unknown2;
  uint8_t samples[];
} digi_new_type;
static_assert(sizeof(digi_new_type) == 9);

typedef struct midi_type
{
  char chunk_type[4];
  uint32_t chunk_length;
  union
  {
    struct
    {
      uint16_t format;
      uint16_t num_tracks;
      uint16_t delta;
      uint8_t tracks[0];
    } header;
    uint8_t data[0];
  };

} midi_type;

typedef struct converted_audio_type
{
  int length;
  int16_t samples[];
} converted_audio_type;

typedef struct sound_buffer_type
{
  uint8_t type;
  union
  {
    speaker_type speaker;
    digi_type digi;
    digi_new_type digi_new;
    midi_type midi;
    converted_audio_type converted;
  };
} sound_buffer_type;

typedef struct midi_raw_chunk_type
{
  char chunk_type[4];
  uint32_t chunk_length;
  union
  {
    struct
    {
      uint16_t format;
      uint16_t num_tracks;
      uint16_t time_division;
      uint8_t tracks[0];
    } header;
    uint8_t data[0];
  };

} midi_raw_chunk_type;

typedef struct midi_event_type
{
  uint32_t delta_time;
  uint8_t event_type;
  union
  {
    struct
    {
      uint8_t channel;
      uint8_t param1;
      uint8_t param2;
    } channel;
    struct
    {
      uint32_t length;
      uint8_t *data;
    } sysex;
    struct
    {
      uint8_t type;
      uint32_t length;
      uint8_t *data;
    } meta;
  };

} midi_event_type;

typedef struct midi_track_type
{
  uint32_t size;
  int num_events;
  midi_event_type *events;
  int event_index;
  int64_t next_pause_tick;
} midi_track_type;

typedef struct parsed_midi_type
{
  int num_tracks;
  midi_track_type *tracks;
  uint32_t ticks_per_beat;
} parsed_midi_type;

  #pragma pack(push, 1)
typedef struct operator_type
{
  uint8_t mul;
  uint8_t ksl_tl;
  uint8_t a_d;
  uint8_t s_r;
  uint8_t waveform;
} operator_type;

typedef struct instrument_type
{
  uint8_t blocknum_low;
  uint8_t blocknum_high;
  uint8_t FB_conn;
  operator_type operators[2];
  uint8_t percussion;
  uint8_t unknown[2];
} instrument_type;
  #pragma pack(pop)

struct dialog_type; // (declaration only)
typedef struct dialog_settings_type
{
  void (*method_1)(struct dialog_type *dialog);
  void (*method_2_frame)(struct dialog_type *dialog);
  int16_t top_border;
  int16_t left_border;
  int16_t bottom_border;
  int16_t right_border;
  int16_t shadow_bottom;
  int16_t shadow_right;
  int16_t outer_border;
} dialog_settings_type;

typedef struct dialog_type
{
  dialog_settings_type *settings;
  rect_type text_rect;
  rect_type peel_rect;
  uint16_t has_peel;
  peel_type *peel;
} dialog_type;

  #pragma pack(pop)

enum soundids
{
  sound_0_fell_to_death = 0,
  sound_1_falling = 1,
  sound_2_tile_crashing = 2,
  sound_3_button_pressed = 3,
  sound_4_gate_closing = 4,
  sound_5_gate_opening = 5,
  sound_6_gate_closing_fast = 6,
  sound_7_gate_stop = 7,
  sound_8_bumped = 8,
  sound_9_grab = 9,
  sound_10_sword_vs_sword = 10,
  sound_11_sword_moving = 11,
  sound_12_guard_hurt = 12,
  sound_13_kid_hurt = 13,
  sound_14_leveldoor_closing = 14,
  sound_15_leveldoor_sliding = 15,
  sound_16_medium_land = 16,
  sound_17_soft_land = 17,
  sound_18_drink = 18,
  sound_19_draw_sword = 19,
  sound_20_loose_shake_1 = 20,
  sound_21_loose_shake_2 = 21,
  sound_22_loose_shake_3 = 22,
  sound_23_footstep = 23,
  sound_24_death_regular = 24,
  sound_25_presentation = 25,
  sound_26_embrace = 26,
  sound_27_cutscene_2_4_6_12 = 27,
  sound_28_death_in_fight = 28,
  sound_29_meet_Jaffar = 29,
  sound_30_big_potion = 30,
  // sound_31 = 31,
  sound_32_shadow_music = 32,
  sound_33_small_potion = 33,
  // sound_34 = 34,
  sound_35_cutscene_8_9 = 35,
  sound_36_out_of_time = 36,
  sound_37_victory = 37,
  sound_38_blink = 38,
  sound_39_low_weight = 39,
  sound_40_cutscene_12_short_time = 40,
  sound_41_end_level_music = 41,
  // sound_42 = 42,
  sound_43_victory_Jaffar = 43,
  sound_44_skel_alive = 44,
  sound_45_jump_through_mirror = 45,
  sound_46_chomped = 46,
  sound_47_chomper = 47,
  sound_48_spiked = 48,
  sound_49_spikes = 49,
  sound_50_story_2_princess = 50,
  sound_51_princess_door_opening = 51,
  sound_52_story_4_Jaffar_leaves = 52,
  sound_53_story_3_Jaffar_comes = 53,
  sound_54_intro_music = 54,
  sound_55_story_1_absence = 55,
  sound_56_ending_music = 56,
};

enum timerids
{
  timer_0 = 0,
  timer_1 = 1,
  timer_2 = 2,
};

enum frameids
{
  frame_0 = 0,
  frame_1_start_run = 1,
  frame_2_start_run = 2,
  frame_3_start_run = 3,
  frame_4_start_run = 4,
  frame_5_start_run = 5,
  frame_6_start_run = 6,
  frame_7_run = 7,
  frame_8_run = 8,
  frame_9_run = 9,
  frame_10_run = 10,
  frame_11_run = 11,
  frame_12_run = 12,
  frame_13_run = 13,
  frame_14_run = 14,
  frame_15_stand = 15,
  frame_16_standing_jump_1 = 16,
  frame_17_standing_jump_2 = 17,
  frame_18_standing_jump_3 = 18,
  frame_19_standing_jump_4 = 19,
  frame_20_standing_jump_5 = 20,
  frame_21_standing_jump_6 = 21,
  frame_22_standing_jump_7 = 22,
  frame_23_standing_jump_8 = 23,
  frame_24_standing_jump_9 = 24,
  frame_25_standing_jump_10 = 25,
  frame_26_standing_jump_11 = 26,
  frame_27_standing_jump_12 = 27,
  frame_28_standing_jump_13 = 28,
  frame_29_standing_jump_14 = 29,
  frame_30_standing_jump_15 = 30,
  frame_31_standing_jump_16 = 31,
  frame_32_standing_jump_17 = 32,
  frame_33_standing_jump_18 = 33,
  frame_34_start_run_jump_1 = 34,
  frame_35_start_run_jump_2 = 35,
  frame_36_start_run_jump_3 = 36,
  frame_37_start_run_jump_4 = 37,
  frame_38_start_run_jump_5 = 38,
  frame_39_start_run_jump_6 = 39,
  frame_40_running_jump_1 = 40,
  frame_41_running_jump_2 = 41,
  frame_42_running_jump_3 = 42,
  frame_43_running_jump_4 = 43,
  frame_44_running_jump_5 = 44,
  frame_45_turn = 45,
  frame_46_turn = 46,
  frame_47_turn = 47,
  frame_48_turn = 48,
  frame_49_turn = 49,
  frame_50_turn = 50,
  frame_51_turn = 51,
  frame_52_turn = 52,
  frame_53_runturn = 53,
  frame_54_runturn = 54,
  frame_55_runturn = 55,
  frame_56_runturn = 56,
  frame_57_runturn = 57,
  frame_58_runturn = 58,
  frame_59_runturn = 59,
  frame_60_runturn = 60,
  frame_61_runturn = 61,
  frame_62_runturn = 62,
  frame_63_runturn = 63,
  frame_64_runturn = 64,
  frame_65_runturn = 65,
  frame_67_start_jump_up_1 = 67,
  frame_68_start_jump_up_2 = 68,
  frame_69_start_jump_up_3 = 69,
  frame_70_jumphang = 70,
  frame_71_jumphang = 71,
  frame_72_jumphang = 72,
  frame_73_jumphang = 73,
  frame_74_jumphang = 74,
  frame_75_jumphang = 75,
  frame_76_jumphang = 76,
  frame_77_jumphang = 77,
  frame_78_jumphang = 78,
  frame_79_jumphang = 79,
  frame_80_jumphang = 80,
  frame_81_hangdrop_1 = 81,
  frame_82_hangdrop_2 = 82,
  frame_83_hangdrop_3 = 83,
  frame_84_hangdrop_4 = 84,
  frame_85_hangdrop_5 = 85,
  frame_86_test_foot = 86,
  frame_87_hanging_1 = 87,
  frame_88_hanging_2 = 88,
  frame_89_hanging_3 = 89,
  frame_90_hanging_4 = 90,
  frame_91_hanging_5 = 91,
  frame_92_hanging_6 = 92,
  frame_93_hanging_7 = 93,
  frame_94_hanging_8 = 94,
  frame_95_hanging_9 = 95,
  frame_96_hanging_10 = 96,
  frame_97_hanging_11 = 97,
  frame_98_hanging_12 = 98,
  frame_99_hanging_13 = 99,
  frame_102_start_fall_1 = 102,
  frame_103_start_fall_2 = 103,
  frame_104_start_fall_3 = 104,
  frame_105_start_fall_4 = 105,
  frame_106_fall = 106,
  frame_107_fall_land_1 = 107,
  frame_108_fall_land_2 = 108,
  frame_109_crouch = 109,
  frame_110_stand_up_from_crouch_1 = 110,
  frame_111_stand_up_from_crouch_2 = 111,
  frame_112_stand_up_from_crouch_3 = 112,
  frame_113_stand_up_from_crouch_4 = 113,
  frame_114_stand_up_from_crouch_5 = 114,
  frame_115_stand_up_from_crouch_6 = 115,
  frame_116_stand_up_from_crouch_7 = 116,
  frame_117_stand_up_from_crouch_8 = 117,
  frame_118_stand_up_from_crouch_9 = 118,
  frame_119_stand_up_from_crouch_10 = 119,
  frame_121_stepping_1 = 121,
  frame_122_stepping_2 = 122,
  frame_123_stepping_3 = 123,
  frame_124_stepping_4 = 124,
  frame_125_stepping_5 = 125,
  frame_126_stepping_6 = 126,
  frame_127_stepping_7 = 127,
  frame_128_stepping_8 = 128,
  frame_129_stepping_9 = 129,
  frame_130_stepping_10 = 130,
  frame_131_stepping_11 = 131,
  frame_132_stepping_12 = 132,
  frame_133_sheathe = 133,
  frame_134_sheathe = 134,
  frame_135_climbing_1 = 135,
  frame_136_climbing_2 = 136,
  frame_137_climbing_3 = 137,
  frame_138_climbing_4 = 138,
  frame_139_climbing_5 = 139,
  frame_140_climbing_6 = 140,
  frame_141_climbing_7 = 141,
  frame_142_climbing_8 = 142,
  frame_143_climbing_9 = 143,
  frame_144_climbing_10 = 144,
  frame_145_climbing_11 = 145,
  frame_146_climbing_12 = 146,
  frame_147_climbing_13 = 147,
  frame_148_climbing_14 = 148,
  frame_149_climbing_15 = 149,
  frame_150_parry = 150,
  frame_151_strike_1 = 151,
  frame_152_strike_2 = 152,
  frame_153_strike_3 = 153,
  frame_154_poking = 154,
  frame_155_guy_7 = 155,
  frame_156_guy_8 = 156,
  frame_157_walk_with_sword = 157,
  frame_158_stand_with_sword = 158,
  frame_159_fighting = 159,
  frame_160_fighting = 160,
  frame_161_parry = 161,
  frame_162_block_to_strike = 162,
  frame_163_fighting = 163,
  frame_164_fighting = 164,
  frame_165_walk_with_sword = 165,
  frame_166_stand_inactive = 166,
  frame_167_blocked = 167,
  frame_168_back = 168,
  frame_169_begin_block = 169,
  frame_170_stand_with_sword = 170,
  frame_171_stand_with_sword = 171,
  frame_172_jumpfall_2 = 172,
  frame_173_jumpfall_3 = 173,
  frame_174_jumpfall_4 = 174,
  frame_175_jumpfall_5 = 175,
  frame_177_spiked = 177,
  frame_178_chomped = 178,
  frame_179_collapse_1 = 179,
  frame_180_collapse_2 = 180,
  frame_181_collapse_3 = 181,
  frame_182_collapse_4 = 182,
  frame_183_collapse_5 = 183,
  frame_185_dead = 185,
  frame_186_mouse_1 = 186,
  frame_187_mouse_2 = 187,
  frame_188_mouse_stand = 188,
  frame_191_drink = 191,
  frame_192_drink = 192,
  frame_193_drink = 193,
  frame_194_drink = 194,
  frame_195_drink = 195,
  frame_196_drink = 196,
  frame_197_drink = 197,
  frame_198_drink = 198,
  frame_199_drink = 199,
  frame_200_drink = 200,
  frame_201_drink = 201,
  frame_202_drink = 202,
  frame_203_drink = 203,
  frame_204_drink = 204,
  frame_205_drink = 205,
  frame_207_draw_1 = 207,
  frame_208_draw_2 = 208,
  frame_209_draw_3 = 209,
  frame_210_draw_4 = 210,
  frame_217_exit_stairs_1 = 217,
  frame_218_exit_stairs_2 = 218,
  frame_219_exit_stairs_3 = 219,
  frame_220_exit_stairs_4 = 220,
  frame_221_exit_stairs_5 = 221,
  frame_222_exit_stairs_6 = 222,
  frame_223_exit_stairs_7 = 223,
  frame_224_exit_stairs_8 = 224,
  frame_225_exit_stairs_9 = 225,
  frame_226_exit_stairs_10 = 226,
  frame_227_exit_stairs_11 = 227,
  frame_228_exit_stairs_12 = 228,
  frame_229_found_sword = 229,
  frame_230_sheathe = 230,
  frame_231_sheathe = 231,
  frame_232_sheathe = 232,
  frame_233_sheathe = 233,
  frame_234_sheathe = 234,
  frame_235_sheathe = 235,
  frame_236_sheathe = 236,
  frame_237_sheathe = 237,
  frame_238_sheathe = 238,
  frame_239_sheathe = 239,
  frame_240_sheathe = 240,
};

enum altset2ids
{
  alt2frame_54_Vstand = 54,
  //... incomplete
};

enum seqids
{
  seq_1_start_run = 1,
  seq_2_stand = 2,
  seq_3_standing_jump = 3,
  seq_4_run_jump = 4,
  seq_5_turn = 5,
  seq_6_run_turn = 6,
  seq_7_fall = 7,
  seq_8_jump_up_and_grab_straight = 8,
  seq_10_climb_up = 10,
  seq_11_release_ledge_and_land = 11,
  seq_13_stop_run = 13,
  seq_14_jump_up_into_ceiling = 14,
  seq_15_grab_ledge_midair = 15,
  seq_16_jump_up_and_grab = 16,
  seq_17_soft_land = 17,
  seq_18_fall_after_standing_jump = 18,
  seq_19_fall = 19,
  seq_20_medium_land = 20,
  seq_21_fall_after_running_jump = 21,
  seq_22_crushed = 22,
  seq_23_release_ledge_and_fall = 23,
  seq_24_jump_up_and_grab_forward = 24,
  seq_25_hang_against_wall = 25,
  seq_26_crouch_while_running = 26,
  seq_28_jump_up_with_nothing_above = 28,
  seq_29_safe_step_1 = 29,
  seq_30_safe_step_2 = 30,
  seq_31_safe_step_3 = 31,
  seq_32_safe_step_4 = 32,
  seq_33_safe_step_5 = 33,
  seq_34_safe_step_6 = 34,
  seq_35_safe_step_7 = 35,
  seq_36_safe_step_8 = 36,
  seq_37_safe_step_9 = 37,
  seq_38_safe_step_10 = 38,
  seq_39_safe_step_11 = 39,
  seq_40_safe_step_12 = 40,
  seq_41_safe_step_13 = 41,
  seq_42_safe_step_14 = 42,
  seq_43_start_run_after_turn = 43,
  seq_44_step_on_edge = 44,
  seq_45_bumpfall = 45,
  seq_46_hardbump = 46,
  seq_47_bump = 47,
  seq_49_stand_up_from_crouch = 49,
  seq_50_crouch = 50,
  seq_51_spiked = 51,
  seq_52_loose_floor_fell_on_kid = 52,
  seq_54_chomped = 54,
  seq_55_draw_sword = 55,
  seq_56_guard_forward_with_sword = 56,
  seq_57_back_with_sword = 57,
  seq_58_guard_strike = 58,
  seq_60_turn_with_sword = 60,
  seq_61_parry_after_strike = 61,
  seq_62_parry = 62,
  seq_63_guard_stand_active = 63,
  seq_64_pushed_back_with_sword = 64,
  seq_65_bump_forward_with_sword = 65,
  seq_66_strike_after_parry = 66,
  seq_68_climb_down = 68,
  seq_69_attack_was_parried = 69,
  seq_70_go_up_on_level_door = 70,
  seq_71_dying = 71,
  seq_73_climb_up_to_closed_gate = 73,
  seq_74_hit_by_sword = 74,
  seq_75_strike = 75,
  seq_77_guard_stand_inactive = 77,
  seq_78_drink = 78,
  seq_79_crouch_hop = 79,
  seq_80_stand_flipped = 80,
  seq_81_kid_pushed_off_ledge = 81,
  seq_82_guard_pushed_off_ledge = 82,
  seq_83_guard_fall = 83,
  seq_84_run = 84,
  seq_85_stabbed_to_death = 85,
  seq_86_forward_with_sword = 86,
  seq_87_guard_become_inactive = 87,
  seq_88_skel_wake_up = 88,
  seq_89_turn_draw_sword = 89,
  seq_90_en_garde = 90,
  seq_91_get_sword = 91,
  seq_92_put_sword_away = 92,
  seq_93_put_sword_away_fast = 93,
  seq_94_princess_stand_PV1 = 94,
  seq_95_Jaffar_stand_PV1 = 95,
  seq_101_mouse_stands_up = 101,
  seq_103_princess_lying_PV2 = 103,
  seq_104_start_fall_in_front_of_wall = 104,
  seq_105_mouse_forward = 105,
  seq_106_mouse = 106,
  seq_107_mouse_stand_up_and_go = 107,
  seq_108_princess_turn_and_hug = 108,
  seq_109_princess_stand_PV2 = 109,
  seq_110_princess_crouching_PV2 = 110,
  seq_111_princess_stand_up_PV2 = 111,
  seq_112_princess_crouch_down_PV2 = 112,
  seq_114_mouse_stand = 114,
};

enum seqtbl_instructions
{
  SEQ_DX = 0xFB,
  SEQ_DY = 0xFA,
  SEQ_FLIP = 0xFE,
  SEQ_JMP_IF_FEATHER = 0xF7,
  SEQ_JMP = 0xFF,
  SEQ_UP = 0xFD,
  SEQ_DOWN = 0xFC,
  SEQ_ACTION = 0xF9,
  SEQ_SET_FALL = 0xF8,
  SEQ_KNOCK_UP = 0xF5,
  SEQ_KNOCK_DOWN = 0xF4,
  SEQ_SOUND = 0xF2,
  SEQ_END_LEVEL = 0xF1,
  SEQ_GET_ITEM = 0xF3,
  SEQ_DIE = 0xF6,
};

enum seqtbl_sounds
{
  SND_SILENT = 0,
  SND_FOOTSTEP = 1,
  SND_BUMP = 2,
  SND_DRINK = 3,
  SND_LEVEL = 4,
};

enum colorids
{
  color_0_black = 0,
  color_1_blue = 1,
  color_2_green = 2,
  color_3_cyan = 3,
  color_4_red = 4,
  color_5_magenta = 5,
  color_6_brown = 6,
  color_7_lightgray = 7,
  color_8_darkgray = 8,
  color_9_brightblue = 9,
  color_10_brightgreen = 10,
  color_11_brightcyan = 11,
  color_12_brightred = 12,
  color_13_brightmagenta = 13,
  color_14_brightyellow = 14,
  color_15_brightwhite = 15,
};

  #ifdef USE_REPLAY
enum replay_special_moves
{
  MOVE_RESTART_LEVEL = 1, // player pressed Ctrl+A
  MOVE_EFFECT_END = 2,    // music stops, causing the end of feather effect or level 1 crouch immobilization
};

enum replay_seek_targets
{
  replay_seek_0_next_room = 0,
  replay_seek_1_next_level = 1,
  replay_seek_2_end = 2,
};
  #endif

// These are or'ed with SDL_SCANCODE_* constants in last_key_scancode.
enum key_modifiers
{
  WITH_SHIFT = 0x8000,
  WITH_CTRL = 0x4000,
  WITH_ALT = 0x2000,
};


  #pragma pack(push, 1)
typedef struct fixes_options_type
{
  uint8_t enable_crouch_after_climbing;
  uint8_t enable_freeze_time_during_end_music;
  uint8_t enable_remember_guard_hp;
  uint8_t fix_gate_sounds;
  uint8_t fix_two_coll_bug;
  uint8_t fix_infinite_down_bug;
  uint8_t fix_gate_drawing_bug;
  uint8_t fix_bigpillar_climb;
  uint8_t fix_jump_distance_at_edge;
  uint8_t fix_edge_distance_check_when_climbing;
  uint8_t fix_painless_fall_on_guard;
  uint8_t fix_wall_bump_triggers_tile_below;
  uint8_t fix_stand_on_thin_air;
  uint8_t fix_press_through_closed_gates;
  uint8_t fix_grab_falling_speed;
  uint8_t fix_skeleton_chomper_blood;
  uint8_t fix_move_after_drink;
  uint8_t fix_loose_left_of_potion;
  uint8_t fix_guard_following_through_closed_gates;
  uint8_t fix_safe_landing_on_spikes;
  uint8_t fix_glide_through_wall;
  uint8_t fix_drop_through_tapestry;
  uint8_t fix_land_against_gate_or_tapestry;
  uint8_t fix_unintended_sword_strike;
  uint8_t fix_retreat_without_leaving_room;
  uint8_t fix_running_jump_through_tapestry;
  uint8_t fix_push_guard_into_wall;
  uint8_t fix_jump_through_wall_above_gate;
  uint8_t fix_chompers_not_starting;
  uint8_t fix_feather_interrupted_by_leveldoor;
  uint8_t fix_offscreen_guards_disappearing;
  uint8_t fix_move_after_sheathe;
  uint8_t fix_hidden_floors_during_flashing;
  uint8_t fix_hang_on_teleport;
  uint8_t fix_exit_door;
  uint8_t fix_quicksave_during_feather;
  uint8_t fix_quicksave_during_lvl1_music;
} fixes_options_type;

typedef struct custom_options_type
{
  uint16_t start_minutes_left;
  uint16_t start_ticks_left;
  uint16_t start_hitp;
  uint16_t max_hitp_allowed;
  uint16_t saving_allowed_first_level;
  uint16_t saving_allowed_last_level;
  uint8_t start_upside_down;
  uint8_t start_in_blind_mode;
  uint16_t copyprot_level;
  uint8_t drawn_tile_top_level_edge;
  uint8_t drawn_tile_left_level_edge;
  uint8_t level_edge_hit_tile;
  uint8_t allow_triggering_any_tile;
  uint8_t enable_wda_in_palace;
  uint16_t first_level;
  uint8_t skip_title;
  uint16_t shift_L_allowed_until_level;
  uint16_t shift_L_reduced_minutes;
  uint16_t shift_L_reduced_ticks;
  uint16_t demo_hitp;
  uint16_t demo_end_room;
  uint16_t intro_music_level;
  uint16_t intro_music_time_initial;
  uint16_t intro_music_time_restart;
  uint16_t have_sword_from_level;
  uint16_t checkpoint_level;
  int8_t checkpoint_respawn_dir;
  uint8_t checkpoint_respawn_room;
  uint8_t checkpoint_respawn_tilepos;
  uint8_t checkpoint_clear_tile_room;
  uint8_t checkpoint_clear_tile_col;
  uint8_t checkpoint_clear_tile_row;
  uint16_t skeleton_level;
  uint8_t skeleton_room;
  uint8_t skeleton_trigger_column_1;
  uint8_t skeleton_trigger_column_2;
  uint8_t skeleton_column;
  uint8_t skeleton_row;
  uint8_t skeleton_require_open_level_door;
  uint8_t skeleton_skill;
  uint8_t skeleton_reappear_room;
  uint8_t skeleton_reappear_x;
  uint8_t skeleton_reappear_row;
  uint8_t skeleton_reappear_dir;
  uint16_t mirror_level;
  uint8_t mirror_room;
  uint8_t mirror_column;
  uint8_t mirror_row;
  uint8_t mirror_tile;
  uint8_t show_mirror_image;
  uint16_t falling_exit_level;
  uint8_t falling_exit_room;
  uint16_t falling_entry_level;
  uint8_t falling_entry_room;
  uint16_t mouse_level;
  uint8_t mouse_room;
  uint16_t mouse_delay;
  uint8_t mouse_object;
  uint8_t mouse_start_x;
  uint16_t loose_tiles_level;
  uint8_t loose_tiles_room_1;
  uint8_t loose_tiles_room_2;
  uint8_t loose_tiles_first_tile;
  uint8_t loose_tiles_last_tile;
  uint16_t jaffar_victory_level;
  uint8_t jaffar_victory_flash_time;
  uint16_t hide_level_number_from_level;
  uint8_t level_13_level_number;
  uint16_t victory_stops_time_level;
  uint16_t win_level;
  uint8_t win_room;
  uint8_t loose_floor_delay;
  uint8_t tbl_level_type[16];
  uint16_t tbl_level_color[16];
  int16_t tbl_guard_type[16];
  uint8_t tbl_guard_hp[16];
  uint8_t tbl_cutscenes_by_index[16];
  uint8_t tbl_entry_pose[16];
  int8_t tbl_seamless_exit[16];

  // guard skills
  uint16_t strikeprob10[__QS_NUM_GUARD_SKILLS];
  uint16_t restrikeprob10[__QS_NUM_GUARD_SKILLS];
  uint16_t blockprob10[__QS_NUM_GUARD_SKILLS];
  uint16_t impblockprob10[__QS_NUM_GUARD_SKILLS];
  uint16_t advprob10[__QS_NUM_GUARD_SKILLS];
  uint16_t refractimer10[__QS_NUM_GUARD_SKILLS];
  uint16_t extrastrength10[__QS_NUM_GUARD_SKILLS];

  uint16_t strikeprob14[__QS_NUM_GUARD_SKILLS];
  uint16_t restrikeprob14[__QS_NUM_GUARD_SKILLS];
  uint16_t blockprob14[__QS_NUM_GUARD_SKILLS];
  uint16_t impblockprob14[__QS_NUM_GUARD_SKILLS];
  uint16_t advprob14[__QS_NUM_GUARD_SKILLS];
  uint16_t refractimer14[__QS_NUM_GUARD_SKILLS];
  uint16_t extrastrength14[__QS_NUM_GUARD_SKILLS];

  // shadow's starting positions
  uint8_t init_shad_6[8];
  uint8_t init_shad_5[8];
  uint8_t init_shad_12[8];
  // automatic moves
  auto_move_type demo_moves[25];     // prince on demo level
  auto_move_type shad_drink_move[8]; // shadow on level 5

  // speeds
  uint8_t base_speed;
  uint8_t fight_speed;
  uint8_t chomper_speed;

} custom_options_type;
  #pragma pack(pop)

typedef struct directory_listing_type directory_listing_type;


// SDLPop state to miniPop State conversion
#pragma pack(push, 1)
struct sdlPopState_t
{
  char quick_control[9];
  level_type level;
  uint16_t checkpoint;
  uint16_t upside_down;
  uint16_t drawn_room;
  uint16_t current_level;
  uint16_t next_level;
  int16_t mobs_count;
  mob_type mobs[14];
  int16_t trobs_count;
  trob_type trobs[30];
  uint16_t leveldoor_open;
  char_type Kid;
  uint16_t hitp_curr;
  uint16_t hitp_max;
  uint16_t hitp_beg_lev;
  uint16_t grab_timer;
  uint16_t holding_sword;
  int16_t united_with_shadow;
  uint16_t have_sword;
  uint16_t kid_sword_strike;
  int16_t pickup_obj_type;
  uint16_t offguard; // name from Apple II source
  char_type Guard;
  char_type Char;
  char_type Opp;
  uint16_t guardhp_curr;
  uint16_t guardhp_max;
  uint16_t demo_index;
  int16_t demo_time;
  uint16_t curr_guard_color;
  int16_t guard_notice_timer;
  uint16_t guard_skill;
  uint16_t shadow_initialized;
  uint16_t guard_refrac;
  uint16_t justblocked; // name from Apple II source
  uint16_t droppedout;  // name from Apple II source
  int8_t curr_row_coll_room[10];
  uint8_t curr_row_coll_flags[10];
  int8_t below_row_coll_room[10];
  uint8_t below_row_coll_flags[10];
  int8_t above_row_coll_room[10];
  uint8_t above_row_coll_flags[10];
  int8_t prev_collision_row;
  uint16_t flash_color;
  uint16_t flash_time;
  uint16_t need_level1_music;
  uint16_t is_screaming;
  uint16_t is_feather_fall;
  uint16_t last_loose_sound;
  uint32_t random_seed;
  int16_t rem_min;
  uint16_t rem_tick;
  int8_t control_x;
  int8_t control_y;
  int8_t control_shift;
  int8_t control_forward;
  int8_t control_backward;
  int8_t control_up;
  int8_t control_down;
  int8_t control_shift2;
  int8_t ctrl1_forward;
  int8_t ctrl1_backward;
  int8_t ctrl1_up;
  int8_t ctrl1_down;
  int8_t ctrl1_shift2;
  uint16_t exit_room_timer;
  float replay_curr_tick;
  uint16_t is_guard_notice;
  int16_t can_guard_see_kid;
  int8_t collision_row;
  int8_t prev_coll_room[10];
  uint8_t prev_coll_flags[10];
  int16_t jumped_through_mirror;
};
#pragma pack(pop)

} // namespace quicker