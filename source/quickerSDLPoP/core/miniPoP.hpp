/*
MiniPop, a barebones thread-safe version of SDLPop for routing
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
#include "types.h"

extern struct sdlPopState_t gameState;
extern word* copyprot_room;
extern byte* sound_interruptible;
extern custom_options_type *custom;
extern byte is_validate_mode;
extern word text_time_remaining;
extern word text_time_minipop_total;
extern word is_show_time;
extern word resurrect_time;
extern word dont_reset_time;
extern byte sound_flags;
extern word draw_mode;
extern short start_level;
extern byte *guard_palettes;
extern chtab_type *chtab_addrs[10];
extern word copyprot_plac;
extern word copyprot_idx;
extern word cplevel_entr[14];
extern dialog_type *copyprot_dialog;
extern rect_type dialog_rect_1;
extern rect_type dialog_rect_2;
extern byte curr_minipop_tile;
extern byte curr_modifier;
extern tile_and_mod leftroom_[3];
extern tile_and_mod row_below_left_[10];
extern word loaded_room;
extern byte *curr_room_minipop_tiles;
extern byte *curr_room_modif;
extern word draw_xh;
extern byte graphics_mode;
extern word room_L;
extern word room_R;
extern word room_A;
extern word room_B;
extern word room_BR;
extern word room_BL;
extern word room_AR;
extern word room_AL;
extern short table_counts[5];
extern short drects_count;
extern short peels_count;
extern back_table_type foretable[200];
extern back_table_type backtable[200];
extern midtable_type midtable[50];
extern peel_type *peels_minipop_table[50];
extern rect_type drects[30];
extern sbyte obj_direction;
extern short obj_clip_left;
extern short obj_clip_minipop_top;
extern short obj_clip_right;
extern short obj_clip_bottom;
extern wipetable_type wipetable[300];
extern word need_drects;
extern word leveldoor_right;
extern word leveldoor_ybottom;
extern byte palace_wall_colors[44 * 3];
extern word seed_was_init;
extern byte *doorlink2_ad;
extern byte *doorlink1_ad;
extern word is_paused;
extern word is_restart_level;
extern byte sound_mode;
extern byte is_sound_on;
extern short guardhp_delta;
extern word next_room;
extern short hitp_delta;
extern word need_quotes;
extern short roomleave_result;
extern sound_buffer_type *sound_pointers[58];
extern chtab_type *chtab_minipop_title40;
extern chtab_type *chtab_minipop_title50;
extern short hof_count;
extern word demo_mode;
extern short next_sound;
extern short knock;
extern byte wipe_frames[30];
extern sbyte wipe_heights[30];
extern byte redraw_frames_anim[30];
extern byte redraw_frames2[30];
extern byte redraw_frames_floor_overlay[30];
extern byte redraw_frames_full[30];
extern byte redraw_frames_fore[30];
extern byte tile_object_redraw[30];
extern byte redraw_frames_above[10];
extern word need_full_redraw;
extern short n_curr_objs;
extern objtable_type objtable[50];
extern short curr_objs[50];
extern byte obj_xh;
extern byte obj_xl;
extern byte obj_y;
extern byte obj_chtab;
extern byte obj_id;
extern byte obj_minipop_tilepos;
extern short obj_x;
extern frame_type cur_frame;
extern word seamless;
extern trob_type trob;
extern short redraw_height;
extern byte curr_minipop_tilepos;
extern short curr_room;
extern mob_type curmob;
extern short tile_col;
extern byte key_states[SDL_NUM_SCANCODES];
extern short char_col_right;
extern short char_col_left;
extern short char_minipop_top_row;
extern short prev_char_minipop_top_row;
extern short prev_char_col_right;
extern short prev_char_col_left;
extern short char_bottom_row;
extern short jumped_through_mirror;
extern byte curr_minipop_tile2;
extern short tile_row;
extern word char_width_half;
extern word char_height;
extern short char_x_left;
extern short char_x_left_coll;
extern short char_x_right_coll;
extern short char_x_right;
extern short char_minipop_top_y;
extern byte fall_frame;
extern byte through_minipop_tile;
extern sbyte infrontx; // name from Apple II source
extern word current_sound;
extern byte edge_type;
extern char **sound_names;
extern int g_argc;
extern int last_key_scancode;
extern word curmob_index;
extern dat_type *dathandle;
extern word need_redraw_because_flipped;
extern byte *level_var_palettes;
extern word first_start;
extern sbyte distance_mirror;
extern Uint64 last_minipop_transition_counter;
extern sbyte bump_col_left_of_wall;
extern sbyte bump_col_right_of_wall;
extern sbyte right_checked_col;
extern sbyte left_checked_col;
extern short coll_minipop_tile_left_xpos;
extern word curr_minipop_tile_minipop_temp;
extern char exe_dir[POP_MAX_PATH];
extern bool found_exe_dir;
extern word which_quote;
extern dat_type *dat_chain_ptr;
extern char last_minipop_text_input;
extern short drawn_row;
extern short draw_bottom_y;
extern short draw_main_y;
extern short drawn_col;
extern byte tile_left;
extern byte modifier_left;
extern byte kidSeqId;
extern char levels_file[POP_MAX_PATH];

typedef void restore_room_after_quick_load_minipop_t(void);
typedef void load_global_options_minipop_t(void);
typedef void check_mod_param_minipop_t(void);
typedef void load_ingame_settings_minipop_t(void);
typedef void turn_sound_on_off_minipop_t(byte);
typedef void load_mod_options_minipop_t(void);
typedef void apply_seqtbl_patches_minipop_t(void);
typedef dat_type *__pascal open_dat_minipop_t(const char *file, int drive);
typedef int  parse_grmode_minipop_t(void);
typedef void  init_timer_minipop_t(int frequency);
typedef void  parse_cmdline_sound_minipop_t(void);
typedef void  set_hc_pal_minipop_t(void);
typedef void  show_loading_minipop_t(void);
typedef int  set_joy_mode_minipop_t(void);
typedef void  init_copyprot_dialog_minipop_t(void);
typedef void init_record_replay_minipop_t(void);
typedef void init_menu_minipop_t(void);
typedef word  prandom_minipop_t(word max);
typedef void far *__pascal load_from_opendats_alloc_minipop_t(int resource, const char *extension, data_location *out_result, int *out_size);
typedef void  set_pal_256_minipop_t(rgb_type far *source);
typedef void  set_pal_minipop_t(int index, int red, int green, int blue, int vsync);
typedef chtab_type *__pascal load_sprites_from_file_minipop_t(int resource, int palette_bits, int quit_on_error);
typedef void  close_dat_minipop_t(dat_type far *pointer);
typedef void init_lighting_minipop_t(void);
typedef void load_all_sounds_minipop_t(void);
typedef void  hof_read_minipop_t(void);
typedef void  release_minipop_title_images_minipop_t(void);
typedef void  free_optsnd_chtab_minipop_t(void);
typedef void  load_kid_sprite_minipop_t(void);
typedef void  load_lev_spr_minipop_t(int level);
typedef void  load_level_minipop_t(void);
typedef void  pos_guards_minipop_t(void);
typedef void  clear_coll_rooms_minipop_t(void);
typedef void  clear_saved_ctrl_minipop_t(void);
typedef void  do_startpos_minipop_t(void);
typedef void  find_start_level_door_minipop_t(void);
typedef int  check_sound_playing_minipop_t(void);
typedef int  do_paused_minipop_t(void);
typedef void idle_minipop_t(void);
typedef void  stop_sounds_minipop_t(void);
typedef void  show_copyprot_minipop_t(int where);
typedef void reset_timer_minipop_t(int timer_index);
typedef void  free_peels_minipop_t(void);
typedef int  play_level_2_minipop_t(void);
typedef void  timers_minipop_t(void);
typedef void  start_game_minipop_t(void);
typedef void  check_fall_flo_t(void);
typedef void  play_frame_minipop_t(void);
typedef void  draw_game_frame_minipop_t(void);
typedef void update_screen_minipop_t(void);
typedef void __pascal do_simple_wait_minipop_t(int timer_index);
typedef void reset_level_unused_fields_minipop_t(bool loading_clean_level);
typedef void  load_room_links_minipop_t(void);
typedef void set_timer_length_minipop_t(int timer_index, int length);
typedef void  draw_level_first_minipop_t(void);
typedef void  play_level_minipop_t(int level_number);
typedef int save_recorded_replay_minipop_t(const char *full_filename);
typedef void start_recording_minipop_t(void);
typedef void add_replay_move_minipop_t(void);
typedef void  process_minipop_trobs_minipop_t(void);
typedef void  do_mobs_minipop_t(void);
typedef void  check_skel_minipop_t(void);
typedef void  check_can_guard_see_kid_minipop_t(void);
typedef void  check_mirror_minipop_t(void);
typedef void  init_copyprot_minipop_t(void);
typedef void  alter_mods_allrm_minipop_t(void);
typedef void  start_replay_minipop_t(void);
typedef void  display_minipop_text_bottom_minipop_t(const char near *text);
typedef void  redraw_screen_minipop_t(int drawing_different_room);
typedef void  anim_minipop_tile_modif_minipop_t();

extern restore_room_after_quick_load_minipop_t restore_room_after_quick_load;
extern load_global_options_minipop_t load_global_options;
extern check_mod_param_minipop_t check_mod_param;
extern load_ingame_settings_minipop_t load_ingame_settings;
extern turn_sound_on_off_minipop_t turn_sound_on_off;
extern load_mod_options_minipop_t load_mod_options;
extern apply_seqtbl_patches_minipop_t apply_seqtbl_patches;
extern open_dat_minipop_t open_dat;
extern parse_grmode_minipop_t parse_grmode;
extern init_timer_minipop_t init_timer;
extern parse_cmdline_sound_minipop_t parse_cmdline_sound;
extern set_hc_pal_minipop_t set_hc_pal;
extern show_loading_minipop_t show_loading;
extern set_joy_mode_minipop_t set_joy_mode;
extern init_copyprot_dialog_minipop_t init_copyprot_dialog;
extern init_record_replay_minipop_t init_record_replay;
extern init_menu_minipop_t init_menu;
extern prandom_minipop_t prandom;
extern load_from_opendats_alloc_minipop_t load_from_opendats_alloc;
extern set_pal_256_minipop_t set_pal_256;
extern set_pal_minipop_t set_pal;
extern load_sprites_from_file_minipop_t load_sprites_from_file;
extern close_dat_minipop_t close_dat;
extern init_lighting_minipop_t init_lighting;
extern load_all_sounds_minipop_t load_all_sounds;
extern hof_read_minipop_t hof_read;
extern release_minipop_title_images_minipop_t release_minipop_title_images;
extern free_optsnd_chtab_minipop_t free_optsnd_chtab;
extern load_kid_sprite_minipop_t load_kid_sprite;
extern load_lev_spr_minipop_t load_lev_spr;
extern load_level_minipop_t load_level;
extern pos_guards_minipop_t pos_guards;
extern clear_coll_rooms_minipop_t clear_coll_rooms;
extern clear_saved_ctrl_minipop_t clear_saved_ctrl;
extern do_startpos_minipop_t do_startpos;
extern find_start_level_door_minipop_t find_start_level_door;
extern check_sound_playing_minipop_t check_sound_playing;
extern do_paused_minipop_t do_paused;
extern idle_minipop_t idle;
extern stop_sounds_minipop_t stop_sounds;
extern show_copyprot_minipop_t show_copyprot;
extern reset_timer_minipop_t reset_timer;
extern free_peels_minipop_t free_peels;
extern play_level_2_minipop_t play_level_2;
extern timers_minipop_t timers;
extern play_frame_minipop_t play_frame;
extern draw_game_frame_minipop_t draw_game_frame;
extern update_screen_minipop_t update_screen;
extern do_simple_wait_minipop_t do_simple_wait;
extern reset_level_unused_fields_minipop_t reset_level_unused_fields;
extern load_room_links_minipop_t load_room_links;
extern set_timer_length_minipop_t set_timer_length;
extern draw_level_first_minipop_t draw_level_first;
extern play_level_minipop_t play_level;
extern save_recorded_replay_minipop_t save_recorded_replay;
extern start_recording_minipop_t start_recording;
extern add_replay_move_minipop_t add_replay_move;
extern process_minipop_trobs_minipop_t process_minipop_trobs;
extern do_mobs_minipop_t do_mobs;
extern check_skel_minipop_t check_skel;
extern check_can_guard_see_kid_minipop_t check_can_guard_see_kid;
extern check_mirror_minipop_t check_mirror;
extern init_copyprot_minipop_t init_copyprot;
extern alter_mods_allrm_minipop_t alter_mods_allrm;
extern start_replay_minipop_t start_replay;
extern start_game_minipop_t start_game;
extern display_minipop_text_bottom_minipop_t display_minipop_text_bottom;
extern redraw_screen_minipop_t redraw_screen;
extern anim_minipop_tile_modif_minipop_t anim_minipop_tile_modif;
extern void gen_palace_wall_colors_randomizer();
extern void check_fall_flo();

