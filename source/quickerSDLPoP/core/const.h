/*__QS_DW
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

#include "types.h"

namespace quicker
{


#define __QS_objtable_count table_counts[4]
#define __QS_SEQTBL_BASE 0x196E
#define __QS_SEQTBL_0 (seqtbl - __QS_SEQTBL_BASE)
#define __QS_DW(data_word) (data_word) & 0x00FF, (((data_word)&0xFF00) >> 8)
#define __QS_ACT(action) SEQ_ACTION, action
#define __QS_JMP(dest) SEQ_JMP, __QS_DW(dest)
#define __QS_JMP_IF_FEATHER(dest) SEQ_JMP_IF_FEATHER, __QS_DW(dest)
#define __QS_DX(amount) SEQ_DX, (uint8_t)amount
#define __QS_DY(amount) SEQ_DY, (uint8_t)amount
#define __QS_SND(sound) SEQ_SOUND, sound
#define __QS_SET_FALL(x, y) SEQ_SET_FALL, (uint8_t)x, (uint8_t)y
#define __QS_LABEL(label) // disable
#define __QS__MAX_GRAB_FALLING_SPEED 32
#define __QS_JUMP_STRAIGHT_CONDITION distance < 4 && edge_distance < 4 && edge_type != 1

// Labels
enum sequence_t
{
 running = __QS_SEQTBL_BASE                , // 0x196E
 startrun = 5 + running               , // __QS_SEQTBL_BASE + 5     // 0x1973
 runstt1 = 2 + startrun               , // __QS_SEQTBL_BASE + 7     // 0x1975
 runstt4 = 3 + runstt1                , // __QS_SEQTBL_BASE + 10    // 0x1978
 runcyc1 = 9 + runstt4                , // __QS_SEQTBL_BASE + 19    // 0x1981
 runcyc7 = 20 + runcyc1               , // __QS_SEQTBL_BASE + 39    // 0x1995
 stand = 11 + runcyc7                 , // __QS_SEQTBL_BASE + 50    // 0x19A0
 goalertstand = 6 + stand             , // __QS_SEQTBL_BASE + 56    // 0x19A6
 alertstand = 2 + goalertstand        , // __QS_SEQTBL_BASE + 58    // 0x19A8
 arise = 4 + alertstand               , // __QS_SEQTBL_BASE + 62    // 0x19AC
 guardengarde = 21 + arise            , // __QS_SEQTBL_BASE + 83    // 0x19C1
 engarde = 3 + guardengarde           , // __QS_SEQTBL_BASE + 86    // 0x19C4
 ready = 14 + engarde                 , // __QS_SEQTBL_BASE + 100   // 0x19D2
 ready_loop = 6 + ready               , // __QS_SEQTBL_BASE + 106   // 0x19D8
 stabbed = 4 + ready_loop             , // __QS_SEQTBL_BASE + 110   // 0x19DC
 strikeadv = 29 + stabbed             , // __QS_SEQTBL_BASE + 139   // 0x19F9
 strikeret = 14 + strikeadv           , // __QS_SEQTBL_BASE + 153   // 0x1A07
 charAdvance = 12 + strikeret         ,     // __QS_SEQTBL_BASE + 165   // 0x1A13
 fastadvance = 15 + charAdvance       ,     // __QS_SEQTBL_BASE + 180   // 0x1A22
 retreat = 12 + fastadvance           , // __QS_SEQTBL_BASE + 192   // 0x1A2E
 strike = 14 + retreat                , // __QS_SEQTBL_BASE + 206   // 0x1A3C
 faststrike = 6 + strike              , // __QS_SEQTBL_BASE + 212   // 0x1A42
 guy4 = 3 + faststrike                , // __QS_SEQTBL_BASE + 215   // 0x1A45
 guy7 = 5 + guy4                      , // __QS_SEQTBL_BASE + 220   // 0x1A4A
 guy8 = 3 + guy7                      , // __QS_SEQTBL_BASE + 223   // 0x1A4D
 blockedstrike = 7 + guy8             , // __QS_SEQTBL_BASE + 230   // 0x1A54
 blocktostrike = 6 + blockedstrike    , // __QS_SEQTBL_BASE + 236   // 0x1A5A
 readyblock = 4 + blocktostrike       , // __QS_SEQTBL_BASE + 240   // 0x1A5E
 blocking = 1 + readyblock            , // __QS_SEQTBL_BASE + 241   // 0x1A5F
 striketoblock = 4 + blocking         , // __QS_SEQTBL_BASE + 245   // 0x1A63
 landengarde = 5 + striketoblock      , // __QS_SEQTBL_BASE + 250   // 0x1A68
 bumpengfwd = 6 + landengarde         , // __QS_SEQTBL_BASE + 256   // 0x1A6E
 bumpengback = 7 + bumpengfwd         , // __QS_SEQTBL_BASE + 263   // 0x1A75
 flee = 7 + bumpengback               , // __QS_SEQTBL_BASE + 270   // 0x1A7C
 turnengarde = 7 + flee               , // __QS_SEQTBL_BASE + 277   // 0x1A83
 alertturn = 8 + turnengarde          , // __QS_SEQTBL_BASE + 285   // 0x1A8B
 standjump = 8 + alertturn            , // __QS_SEQTBL_BASE + 293   // 0x1A93
 sjland = 29 + standjump              , // __QS_SEQTBL_BASE + 322   // 0x1AB0
 runjump = 29 + sjland                , // __QS_SEQTBL_BASE + 351   // 0x1ACD
 rjlandrun = 46 + runjump             , // __QS_SEQTBL_BASE + 397   // 0x1AFB
 rdiveroll = 9 + rjlandrun            , // __QS_SEQTBL_BASE + 406   // 0x1B04
 rdiveroll_crouch = 18 + rdiveroll    , // __QS_SEQTBL_BASE + 424   // 0x1B16
 sdiveroll = 4 + rdiveroll_crouch     , // __QS_SEQTBL_BASE + 428   // 0x1B1A
 crawl = 1 + sdiveroll                , // __QS_SEQTBL_BASE + 429   // 0x1B1B
 crawl_crouch = 14 + crawl            , // __QS_SEQTBL_BASE + 443   // 0x1B29
 turndraw = 4 + crawl_crouch          , // __QS_SEQTBL_BASE + 447   // 0x1B2D
 turn = 12 + turndraw                 , // __QS_SEQTBL_BASE + 459   // 0x1B39
 turnrun = 26 + turn                  , // __QS_SEQTBL_BASE + 485   // 0x1B53
 runturn = 7 + turnrun                , // __QS_SEQTBL_BASE + 492   // 0x1B5A
 fightfall = 43 + runturn             , // __QS_SEQTBL_BASE + 535   // 0x1B85
 efightfall = 28 + fightfall          , // __QS_SEQTBL_BASE + 563   // 0x1BA1
 efightfallfwd = 30 + efightfall      , // __QS_SEQTBL_BASE + 593   // 0x1BBF
 stepfall = 28 + efightfallfwd        , // __QS_SEQTBL_BASE + 621   // 0x1BDB
 fall1 = 9 + stepfall                 , // __QS_SEQTBL_BASE + 630   // 0x1BE4
 patchfall = 22 + fall1               , // __QS_SEQTBL_BASE + 652   // 0x1BFA
 stepfall2 = 7 + patchfall            , // __QS_SEQTBL_BASE + 659   // 0x1C01
 stepfloat = 5 + stepfall2            , // __QS_SEQTBL_BASE + 664   // 0x1C06
 jumpfall = 22 + stepfloat            , // __QS_SEQTBL_BASE + 686   // 0x1C1C
 rjumpfall = 28 + jumpfall            , // __QS_SEQTBL_BASE + 714   // 0x1C38
 jumphangMed = 28 + rjumpfall         , // __QS_SEQTBL_BASE + 742   // 0x1C54
 jumphangLong = 21 + jumphangMed      , // __QS_SEQTBL_BASE + 763   // 0x1C69
 jumpbackhang = 27 + jumphangLong     , // __QS_SEQTBL_BASE + 790   // 0x1C84
 hang = 29 + jumpbackhang             , // __QS_SEQTBL_BASE + 819   // 0x1CA1
 hang1 = 3 + hang                     , // __QS_SEQTBL_BASE + 822   // 0x1CA4
 hangstraight = 45 + hang1            , // __QS_SEQTBL_BASE + 867   // 0x1CD1
 hangstraight_loop = 7 + hangstraight , // __QS_SEQTBL_BASE + 874   // 0x1CD8
 climbfail = 4 + hangstraight_loop    , // __QS_SEQTBL_BASE + 878   // 0x1CDC
 climbdown = 16 + climbfail           , // __QS_SEQTBL_BASE + 894   // 0x1CEC
 climbup = 24 + climbdown             , // __QS_SEQTBL_BASE + 918   // 0x1D04
 hangdrop = 33 + climbup              , // __QS_SEQTBL_BASE + 951   // 0x1D25
 hangfall = 17 + hangdrop             , // __QS_SEQTBL_BASE + 968   // 0x1D36
 freefall = 19 + hangfall             , // __QS_SEQTBL_BASE + 987   // 0x1D49
 freefall_loop = 2 + freefall         , // __QS_SEQTBL_BASE + 989   // 0x1D4B
 runstop = 4 + freefall_loop          , // __QS_SEQTBL_BASE + 993   // 0x1D4F
 jumpup  = 25 + runstop                , // __QS_SEQTBL_BASE + 1018  // 0x1D68
 highjump  = 21 + jumpup               , // __QS_SEQTBL_BASE + 1039  // 0x1D7D
 superhijump  = 30 + highjump          , // __QS_SEQTBL_BASE + 1069  // 0x1D9B
 fallhang  = 91 + superhijump          , // __QS_SEQTBL_BASE + 1160  // 0x1DF6
 bump  = 6 + fallhang                  , // __QS_SEQTBL_BASE + 1166  // 0x1DFC
 bumpfall  = 10 + bump                 , // __QS_SEQTBL_BASE + 1176  // 0x1E06
 bumpfloat  = 31 + bumpfall            , // __QS_SEQTBL_BASE + 1207  // 0x1E25
 hardbump  = 22 + bumpfloat            , // __QS_SEQTBL_BASE + 1229  // 0x1E3B
 testfoot  = 30 + hardbump             , // __QS_SEQTBL_BASE + 1259  // 0x1E59
 stepback  = 31 + testfoot             , // __QS_SEQTBL_BASE + 1290  // 0x1E78
 step14  = 5 + stepback                , // __QS_SEQTBL_BASE + 1295  // 0x1E7D
 step13  = 31 + step14                 , // __QS_SEQTBL_BASE + 1326  // 0x1E9C
 step12  = 31 + step13                 , // __QS_SEQTBL_BASE + 1357  // 0x1EBB
 step11  = 31 + step12                 , // __QS_SEQTBL_BASE + 1388  // 0x1EDA
 step10 =  29 + step11                 , // __QS_SEQTBL_BASE + 1417  // 0x1EF7
 step10a  = 5 + step10                 , // __QS_SEQTBL_BASE + 1422  // 0x1EFC
 step9  = 23 + step10a                 , // __QS_SEQTBL_BASE + 1445  // 0x1F13
 step8  = 6 + step9                    , // __QS_SEQTBL_BASE + 1451  // 0x1F19
 step7  = 26 + step8                   , // __QS_SEQTBL_BASE + 1477  // 0x1F33
 step6  = 21 + step7                   , // __QS_SEQTBL_BASE + 1498  // 0x1F48
 step5  = 21 + step6                   , // __QS_SEQTBL_BASE + 1519  // 0x1F5D
 step4  = 21 + step5                   , // __QS_SEQTBL_BASE + 1540  // 0x1F72
 step3  = 16 + step4                   , // __QS_SEQTBL_BASE + 1556  // 0x1F82
 step2  = 16 + step3                   , // __QS_SEQTBL_BASE + 1572  // 0x1F92
 step1  = 12 + step2                   , // __QS_SEQTBL_BASE + 1584  // 0x1F9E
 stoop  = 9 + step1                    , // __QS_SEQTBL_BASE + 1593  // 0x1FA7
 stoop_crouch  = 8 + stoop             , // __QS_SEQTBL_BASE + 1601  // 0x1FAF
 standup  = 4 + stoop_crouch           , // __QS_SEQTBL_BASE + 1605  // 0x1FB3
 pickupsword  = 23 + standup           , // __QS_SEQTBL_BASE + 1628  // 0x1FCA
 resheathe  = 16 + pickupsword         , // __QS_SEQTBL_BASE + 1644  // 0x1FDA
 fastsheathe  = 33 + resheathe         , // __QS_SEQTBL_BASE + 1677  // 0x1FFB
 drinkpotion  = 14 + fastsheathe       , // __QS_SEQTBL_BASE + 1691  // 0x2009
 softland  = 34 + drinkpotion          , // __QS_SEQTBL_BASE + 1725  // 0x202B
 softland_crouch  = 11 + softland      , // __QS_SEQTBL_BASE + 1736  // 0x2036
 landrun  = 4 + softland_crouch        , // __QS_SEQTBL_BASE + 1740  // 0x203A
 medland  = 32 + landrun               , // __QS_SEQTBL_BASE + 1772  // 0x205A
 hardland  = 66 + medland              , // __QS_SEQTBL_BASE + 1838  // 0x209C
 hardland_dead =  9 + hardland         , // __QS_SEQTBL_BASE + 1847  // 0x20A5
 stabkill  = 4 + hardland_dead         , // __QS_SEQTBL_BASE + 1851  // 0x20A9
 dropdead  = 5 + stabkill              , // __QS_SEQTBL_BASE + 1856  // 0x20AE
 dropdead_dead  = 12 + dropdead        , // __QS_SEQTBL_BASE + 1868  // 0x20BA
 impale  = 4 + dropdead_dead           , // __QS_SEQTBL_BASE + 1872  // 0x20BE
 impale_dead  = 7 + impale             , // __QS_SEQTBL_BASE + 1879  // 0x20C5
 halve  = 4 + impale_dead              , // __QS_SEQTBL_BASE + 1883  // 0x20C9
 halve_dead  = 4 + halve               , // __QS_SEQTBL_BASE + 1887  // 0x20CD
 crush  = 4 + halve_dead               , // __QS_SEQTBL_BASE + 1891  // 0x20D1
 deadfall  = 3 + crush                 , // __QS_SEQTBL_BASE + 1894  // 0x20D4
 deadfall_loop  = 5 + deadfall         , // __QS_SEQTBL_BASE + 1899  // 0x20D9
 climbstairs  = 4 + deadfall_loop      , // __QS_SEQTBL_BASE + 1903  // 0x20DD
 climbstairs_loop  = 81 + climbstairs  , // __QS_SEQTBL_BASE + 1984  // 0x212E
 Vstand  = 4 + climbstairs_loop        , // __QS_SEQTBL_BASE + 1988  // 0x2132
 Vraise  = 4 + Vstand                  , // __QS_SEQTBL_BASE + 1992  // 0x2136
 Vraise_loop  = 21 + Vraise            , // __QS_SEQTBL_BASE + 2013  // 0x214B
 Vwalk  = 4 + Vraise_loop              , // __QS_SEQTBL_BASE + 2017  // 0x214F
 Vwalk1  = 2 + Vwalk                   , // __QS_SEQTBL_BASE + 2019  // 0x2151
 Vwalk2  = 3 + Vwalk1                  , // __QS_SEQTBL_BASE + 2022  // 0x2154
 Vstop  = 18 + Vwalk2                  , // __QS_SEQTBL_BASE + 2040  // 0x2166
 Vexit  = 7 + Vstop                    , // __QS_SEQTBL_BASE + 2047  // 0x216D
 Pstand  = 40 + Vexit                  , // __QS_SEQTBL_BASE + 2087  // 0x2195
 Palert  = 4 + Pstand                  , // __QS_SEQTBL_BASE + 2091  // 0x2199
 Pstepback  = 15 + Palert              , // __QS_SEQTBL_BASE + 2106  // 0x21A8
 Pstepback_loop  = 16 + Pstepback      , // __QS_SEQTBL_BASE + 2122  // 0x21B8
 Plie  = 4 + Pstepback_loop            , // __QS_SEQTBL_BASE + 2126  // 0x21BC
 Pwaiting  = 4 + Plie                  , // __QS_SEQTBL_BASE + 2130  // 0x21C0
 Pembrace  = 4 + Pwaiting              , // __QS_SEQTBL_BASE + 2134  // 0x21C4
 Pembrace_loop  = 30 + Pembrace        , // __QS_SEQTBL_BASE + 2164  // 0x21E2
 Pstroke  = 4 + Pembrace_loop          , // __QS_SEQTBL_BASE + 2168  // 0x21E6
 Prise  = 4 + Pstroke                  , // __QS_SEQTBL_BASE + 2172  // 0x21EA
 Prise_loop  = 14 + Prise              , // __QS_SEQTBL_BASE + 2186  // 0x21F8
 Pcrouch  = 4 + Prise_loop             , // __QS_SEQTBL_BASE + 2190  // 0x21FC
 Pcrouch_loop  = 64 + Pcrouch          , // __QS_SEQTBL_BASE + 2254  // 0x223C
 Pslump  = 4 + Pcrouch_loop            , // __QS_SEQTBL_BASE + 2258  // 0x2240
 Pslump_loop  = 1 + Pslump             , // __QS_SEQTBL_BASE + 2259  // 0x2241
 Mscurry =  4 + Pslump_loop            , // __QS_SEQTBL_BASE + 2263  // 0x2245
 Mscurry1  = 2 + Mscurry               , // __QS_SEQTBL_BASE + 2265  // 0x2247
 Mstop  = 12 + Mscurry1                , // __QS_SEQTBL_BASE + 2277  // 0x2253
 Mraise  = 4 + Mstop                   , // __QS_SEQTBL_BASE + 2281  // 0x2257
 Mleave  = 4 + Mraise                  , // __QS_SEQTBL_BASE + 2285  // 0x225B
 Mclimb  = 19 + Mleave                 , // __QS_SEQTBL_BASE + 2304  // 0x226E
 Mclimb_loop  = 2 + Mclimb             // __QS_SEQTBL_BASE + 2306  // 0x2270
};

const uint16_t seqtbl_offsets[] = {
  0x0000, startrun, stand, standjump, runjump, turn, runturn, stepfall, jumphangMed, hang, climbup, hangdrop, freefall, runstop, jumpup, fallhang, jumpbackhang, softland, jumpfall, stepfall2, medland, rjumpfall, hardland, hangfall, jumphangLong, hangstraight, rdiveroll, sdiveroll, highjump, step1, step2, step3, step4, step5, step6, step7, step8, step9, step10, step11, step12, step13, step14, turnrun, testfoot, bumpfall, hardbump, bump, superhijump, standup, stoop, impale, crush, deadfall, halve, engarde, charAdvance, retreat, strike, flee, turnengarde, striketoblock, readyblock, landengarde, bumpengfwd, bumpengback, blocktostrike, strikeadv, climbdown, blockedstrike, climbstairs, dropdead, stepback, climbfail, stabbed, faststrike, strikeret, alertstand, drinkpotion, crawl, alertturn, fightfall, efightfall, efightfallfwd, running, stabkill, fastadvance, goalertstand, arise, turndraw, guardengarde, pickupsword, resheathe, fastsheathe, Pstand, Vstand, Vwalk, Vstop, Palert, Pstepback, Vexit, Mclimb, Vraise, Plie, patchfall, Mscurry, Mstop, Mleave, Pembrace, Pwaiting, Pstroke, Prise, Pcrouch, Pslump, Mraise};

// data:196E
static const uint8_t seqtbl[] = {

  __QS_LABEL(running) // running
  __QS_ACT(actions_1_run_jump),
  __QS_JMP(runcyc1), // goto running: frame 7

  __QS_LABEL(startrun) // startrun
  __QS_ACT(actions_1_run_jump),
  __QS_LABEL(runstt1) frame_1_start_run,
  frame_2_start_run,
  frame_3_start_run,
  __QS_LABEL(runstt4) frame_4_start_run,
  __QS_DX(8),
  frame_5_start_run,
  __QS_DX(3),
  frame_6_start_run,
  __QS_DX(3),
  __QS_LABEL(runcyc1) frame_7_run,
  __QS_DX(5),
  frame_8_run,
  __QS_DX(1),
  __QS_SND(SND_FOOTSTEP),
  frame_9_run,
  __QS_DX(2),
  frame_10_run,
  __QS_DX(4),
  frame_11_run,
  __QS_DX(5),
  frame_12_run,
  __QS_DX(2),
  __QS_LABEL(runcyc7) __QS_SND(SND_FOOTSTEP),
  frame_13_run,
  __QS_DX(3),
  frame_14_run,
  __QS_DX(4),
  __QS_JMP(runcyc1),

  __QS_LABEL(stand) // stand
  __QS_ACT(actions_0_stand),
  frame_15_stand,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(goalertstand) // alert stand
  __QS_ACT(actions_1_run_jump),
  __QS_LABEL(alertstand) frame_166_stand_inactive,
  __QS_JMP(alertstand), // goto "alertstand"

  __QS_LABEL(arise) // arise (skeleton)
  __QS_ACT(actions_5_bumped),
  __QS_DX(10),
  frame_177_spiked,
  frame_177_spiked,
  __QS_DX(-7),
  __QS_DY(-2),
  frame_178_chomped,
  __QS_DX(5),
  __QS_DY(2),
  frame_166_stand_inactive,
  __QS_DX(-1),
  __QS_JMP(ready), // goto "ready"

  // guard engarde
  __QS_LABEL(guardengarde)
    __QS_JMP(ready), // goto "ready"

  // engarde
  __QS_LABEL(engarde)
    __QS_ACT(actions_1_run_jump),
  __QS_DX(2),
  frame_207_draw_1,
  frame_208_draw_2,
  __QS_DX(2),
  frame_209_draw_3,
  __QS_DX(2),
  frame_210_draw_4,
  __QS_DX(3),
  __QS_LABEL(ready) __QS_ACT(actions_1_run_jump),
  __QS_SND(SND_SILENT),
  frame_158_stand_with_sword,
  frame_170_stand_with_sword,
  __QS_LABEL(ready_loop) frame_171_stand_with_sword,
  __QS_JMP(ready_loop), // goto ":loop"

  __QS_LABEL(stabbed) // stabbed
  __QS_ACT(actions_5_bumped),
  __QS_SET_FALL(-1, 0),
  frame_172_jumpfall_2,
  __QS_DX(-1),
  __QS_DY(1),
  frame_173_jumpfall_3,
  __QS_DX(-1),
  frame_174_jumpfall_4,
  __QS_DX(-1),
  __QS_DY(2), // frame 175 is commented out in the Apple II source
  __QS_DX(-2),
  __QS_DY(1),
  __QS_DX(-5),
  __QS_DY(-4),
  __QS_JMP(guy8), // goto "guy8"

  // strike - charAdvance
  __QS_LABEL(strikeadv)
    __QS_ACT(actions_1_run_jump),
  __QS_SET_FALL(1, 0),
  frame_155_guy_7,
  __QS_DX(2),
  frame_165_walk_with_sword,
  __QS_DX(-2),
  __QS_JMP(ready), // goto "ready"

  __QS_LABEL(strikeret) // strike - retreat
  __QS_ACT(actions_1_run_jump),
  __QS_SET_FALL(-1, 0),
  frame_155_guy_7,
  frame_156_guy_8,
  frame_157_walk_with_sword,
  frame_158_stand_with_sword,
  __QS_JMP(retreat), // goto "retreat"

  __QS_LABEL(charAdvance) // charAdvance
  __QS_ACT(actions_1_run_jump),
  __QS_SET_FALL(1, 0),
  __QS_DX(2),
  frame_163_fighting,
  __QS_DX(4),
  frame_164_fighting,
  frame_165_walk_with_sword,
  __QS_JMP(ready), // goto "ready"

  __QS_LABEL(fastadvance) // fast charAdvance
  __QS_ACT(actions_1_run_jump),
  __QS_SET_FALL(1, 0),
  __QS_DX(6),
  frame_164_fighting,
  frame_165_walk_with_sword,
  __QS_JMP(ready), // goto "ready"

  __QS_LABEL(retreat) // retreat
  __QS_ACT(actions_1_run_jump),
  __QS_SET_FALL(-1, 0),
  __QS_DX(-3),
  frame_160_fighting,
  __QS_DX(-2),
  frame_157_walk_with_sword,
  __QS_JMP(ready), // goto "ready"

  __QS_LABEL(strike) // strike
  __QS_ACT(actions_1_run_jump),
  __QS_SET_FALL(-1, 0),
  frame_168_back,
  __QS_LABEL(faststrike) __QS_ACT(actions_1_run_jump),
  frame_151_strike_1,
  __QS_LABEL(guy4) __QS_ACT(actions_1_run_jump),
  frame_152_strike_2,
  frame_153_strike_3,
  frame_154_poking,
  __QS_LABEL(guy7) __QS_ACT(actions_5_bumped),
  frame_155_guy_7,
  __QS_LABEL(guy8) __QS_ACT(actions_1_run_jump),
  frame_156_guy_8,
  frame_157_walk_with_sword,
  __QS_JMP(ready), // goto "ready"

  __QS_LABEL(blockedstrike) // blocked strike
  __QS_ACT(actions_1_run_jump),
  frame_167_blocked,
  __QS_JMP(guy7), // goto "guy7"

  // block to strike
  __QS_LABEL(blocktostrike) // "blocktostrike"
  frame_162_block_to_strike,
  __QS_JMP(guy4), // goto "guy4"

  __QS_LABEL(readyblock) // ready block
  frame_169_begin_block,
  __QS_LABEL(blocking) frame_150_parry,
  __QS_JMP(ready), // goto "ready"

  __QS_LABEL(striketoblock) // strike to block
  frame_159_fighting,
  frame_160_fighting,
  __QS_JMP(blocking), // goto "blocking"

  __QS_LABEL(landengarde) // land en garde
  __QS_ACT(actions_1_run_jump),
  SEQ_KNOCK_DOWN,
  __QS_JMP(ready), // goto "ready"

  __QS_LABEL(bumpengfwd) // bump en garde (forward)
  __QS_ACT(actions_5_bumped),
  __QS_DX(-8),
  __QS_JMP(ready), // goto "ready"

  __QS_LABEL(bumpengback) // bump en garde (back)
  __QS_ACT(actions_5_bumped),
  frame_160_fighting,
  frame_157_walk_with_sword,
  __QS_JMP(ready), // goto "ready"

  __QS_LABEL(flee) // flee
  __QS_ACT(actions_7_turn),
  __QS_DX(-8),
  __QS_JMP(turn), // goto "turn"

  __QS_LABEL(turnengarde) // turn en garde
  __QS_ACT(actions_5_bumped),
  SEQ_FLIP,
  __QS_DX(5),
  __QS_JMP(retreat), // goto "retreat"

  __QS_LABEL(alertturn) // alert turn (for enemies)
  __QS_ACT(actions_5_bumped),
  SEQ_FLIP,
  __QS_DX(18),
  __QS_JMP(goalertstand), // goto "goalertstand"

  __QS_LABEL(standjump) // standing jump
  __QS_ACT(actions_1_run_jump),
  frame_16_standing_jump_1,
  frame_17_standing_jump_2,
  __QS_DX(2),
  frame_18_standing_jump_3,
  __QS_DX(2),
  frame_19_standing_jump_4,
  __QS_DX(2),
  frame_20_standing_jump_5,
  __QS_DX(2),
  frame_21_standing_jump_6,
  __QS_DX(2),
  frame_22_standing_jump_7,
  __QS_DX(7),
  frame_23_standing_jump_8,
  __QS_DX(9),
  frame_24_standing_jump_9,
  __QS_DX(5),
  __QS_DY(-6),
  /* "sjland" */ __QS_LABEL(sjland) frame_25_standing_jump_10,
  __QS_DX(1),
  __QS_DY(6),
  frame_26_standing_jump_11,
  __QS_DX(4),
  SEQ_KNOCK_DOWN,
  __QS_SND(SND_FOOTSTEP),
  frame_27_standing_jump_12,
  __QS_DX(-3),
  frame_28_standing_jump_13,
  __QS_DX(5),
  frame_29_standing_jump_14,
  __QS_SND(SND_FOOTSTEP),
  frame_30_standing_jump_15,
  frame_31_standing_jump_16,
  frame_32_standing_jump_17,
  frame_33_standing_jump_18,
  __QS_DX(1),
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(runjump) // running jump
  __QS_ACT(actions_1_run_jump),
  __QS_SND(SND_FOOTSTEP),
  frame_34_start_run_jump_1,
  __QS_DX(5),
  frame_35_start_run_jump_2,
  __QS_DX(6),
  frame_36_start_run_jump_3,
  __QS_DX(3),
  frame_37_start_run_jump_4,
  __QS_DX(5),
  __QS_SND(SND_FOOTSTEP),
  frame_38_start_run_jump_5,
  __QS_DX(7),
  frame_39_start_run_jump_6,
  __QS_DX(12),
  __QS_DY(-3),
  frame_40_running_jump_1,
  __QS_DX(8),
  __QS_DY(-9),
  frame_41_running_jump_2,
  __QS_DX(8),
  __QS_DY(-2),
  frame_42_running_jump_3,
  __QS_DX(4),
  __QS_DY(11),
  frame_43_running_jump_4,
  __QS_DX(4),
  __QS_DY(3),
  /* "rjlandrun" */ __QS_LABEL(rjlandrun) frame_44_running_jump_5,
  __QS_DX(5),
  SEQ_KNOCK_DOWN,
  __QS_SND(SND_FOOTSTEP),
  __QS_JMP(runcyc1), // goto "runcyc1"

  __QS_LABEL(rdiveroll) // run dive roll
  __QS_ACT(actions_1_run_jump),
  __QS_DX(1),
  frame_107_fall_land_1,
  __QS_DX(2),
  __QS_DX(2),
  frame_108_fall_land_2,
  __QS_DX(2),
  frame_109_crouch,
  __QS_DX(2),
  frame_109_crouch,
  __QS_DX(2),
  /* ":crouch" */ __QS_LABEL(rdiveroll_crouch) frame_109_crouch,
  __QS_JMP(rdiveroll_crouch), // goto ":crouch"

  __QS_LABEL(sdiveroll) 0x00, // stand dive roll; not implemented

  __QS_LABEL(crawl) // crawl
  __QS_ACT(actions_1_run_jump),
  __QS_DX(1),
  frame_110_stand_up_from_crouch_1,
  frame_111_stand_up_from_crouch_2,
  __QS_DX(2),
  frame_112_stand_up_from_crouch_3,
  __QS_DX(2),
  frame_108_fall_land_2,
  __QS_DX(2),
  /* ":crouch" */ __QS_LABEL(crawl_crouch) frame_109_crouch,
  __QS_JMP(crawl_crouch), // goto ":crouch"

  __QS_LABEL(turndraw) // turn draw
  __QS_ACT(actions_7_turn),
  SEQ_FLIP,
  __QS_DX(6),
  frame_45_turn,
  __QS_DX(1),
  frame_46_turn,
  __QS_JMP(engarde), // goto "engarde"

  __QS_LABEL(turn) // turn
  __QS_ACT(actions_7_turn),
  SEQ_FLIP,
  __QS_DX(6),
  frame_45_turn,
  __QS_DX(1),
  frame_46_turn,
  __QS_DX(2),
  frame_47_turn,
  __QS_DX(-1),
  /* "finishturn" */ frame_48_turn,
  __QS_DX(1),
  frame_49_turn,
  __QS_DX(-2),
  frame_50_turn,
  frame_51_turn,
  frame_52_turn,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(turnrun) // turnrun (from frame 48)
  __QS_ACT(actions_1_run_jump),
  __QS_DX(-1),
  __QS_JMP(runstt1), // goto "runstt1"

  __QS_LABEL(runturn) // runturn
  __QS_ACT(actions_1_run_jump),
  __QS_DX(1),
  frame_53_runturn,
  __QS_DX(1),
  __QS_SND(SND_FOOTSTEP),
  frame_54_runturn,
  __QS_DX(8),
  frame_55_runturn,
  __QS_SND(SND_FOOTSTEP),
  frame_56_runturn,
  __QS_DX(7),
  frame_57_runturn,
  __QS_DX(3),
  frame_58_runturn,
  __QS_DX(1),
  frame_59_runturn,
  frame_60_runturn,
  __QS_DX(2),
  frame_61_runturn,
  __QS_DX(-1),
  frame_62_runturn,
  frame_63_runturn,
  frame_64_runturn,
  __QS_DX(-1),
  frame_65_runturn,
  __QS_DX(-14),
  SEQ_FLIP,
  __QS_JMP(runcyc7), // goto "runcyc7"

  __QS_LABEL(fightfall) // fightfall (backward)
  __QS_ACT(actions_3_in_midair),
  __QS_DY(-1),
  frame_102_start_fall_1,
  __QS_DX(-2),
  __QS_DY(6),
  frame_103_start_fall_2,
  __QS_DX(-2),
  __QS_DY(9),
  frame_104_start_fall_3,
  __QS_DX(-1),
  __QS_DY(12),
  frame_105_start_fall_4,
  __QS_DX(-3),
  __QS_SET_FALL(0, 15),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(efightfall) // enemy fight fall
  __QS_ACT(actions_3_in_midair),
  __QS_DY(-1),
  __QS_DX(-2),
  frame_102_start_fall_1,
  __QS_DX(-3),
  __QS_DY(6),
  frame_103_start_fall_2,
  __QS_DX(-3),
  __QS_DY(9),
  frame_104_start_fall_3,
  __QS_DX(-2),
  __QS_DY(12),
  frame_105_start_fall_4,
  __QS_DX(-3),
  __QS_SET_FALL(0, 15),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(efightfallfwd) // enemy fight fall forward
  __QS_ACT(actions_3_in_midair),
  __QS_DX(1),
  __QS_DY(-1),
  frame_102_start_fall_1,
  __QS_DX(2),
  __QS_DY(6),
  frame_103_start_fall_2,
  __QS_DX(-1),
  __QS_DY(9),
  frame_104_start_fall_3,
  __QS_DY(12),
  frame_105_start_fall_4,
  __QS_DX(-2),
  __QS_SET_FALL(1, 15),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(stepfall) // stepfall
  __QS_ACT(actions_3_in_midair),
  __QS_DX(1),
  __QS_DY(3),
  __QS_JMP_IF_FEATHER(stepfloat), // goto "stepfloat"
  /* "fall1" */ __QS_LABEL(fall1) frame_102_start_fall_1,
  __QS_DX(2),
  __QS_DY(6),
  frame_103_start_fall_2,
  __QS_DX(-1),
  __QS_DY(9),
  frame_104_start_fall_3,
  __QS_DY(12),
  frame_105_start_fall_4,
  __QS_DX(-2),
  __QS_SET_FALL(1, 15),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(patchfall) // patchfall
  __QS_DX(-1),
  __QS_DY(-3),
  __QS_JMP(fall1), // goto "fall1"

  __QS_LABEL(stepfall2) // stepfall2 (from frame 12)
  __QS_DX(1),
  __QS_JMP(stepfall), // goto "stepfall"

  __QS_LABEL(stepfloat) // stepfloat
  frame_102_start_fall_1,
  __QS_DX(2),
  __QS_DY(3),
  frame_103_start_fall_2,
  __QS_DX(-1),
  __QS_DY(4),
  frame_104_start_fall_3,
  __QS_DY(5),
  frame_105_start_fall_4,
  __QS_DX(-2),
  __QS_SET_FALL(1, 6),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(jumpfall) // jump fall (from standing jump)
  __QS_ACT(actions_3_in_midair),
  __QS_DX(1),
  __QS_DY(3),
  frame_102_start_fall_1,
  __QS_DX(2),
  __QS_DY(6),
  frame_103_start_fall_2,
  __QS_DX(1),
  __QS_DY(9),
  frame_104_start_fall_3,
  __QS_DX(2),
  __QS_DY(12),
  frame_105_start_fall_4,
  __QS_SET_FALL(2, 15),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(rjumpfall) // running jump fall
  __QS_ACT(actions_3_in_midair),
  __QS_DX(1),
  __QS_DY(3),
  frame_102_start_fall_1,
  __QS_DX(3),
  __QS_DY(6),
  frame_103_start_fall_2,
  __QS_DX(2),
  __QS_DY(9),
  frame_104_start_fall_3,
  __QS_DX(3),
  __QS_DY(12),
  frame_105_start_fall_4,
  __QS_SET_FALL(3, 15),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(jumphangMed) // jumphang (medium: DX = 0)
  __QS_ACT(actions_1_run_jump),
  frame_67_start_jump_up_1,
  frame_68_start_jump_up_2,
  frame_69_start_jump_up_3,
  frame_70_jumphang,
  frame_71_jumphang,
  frame_72_jumphang,
  frame_73_jumphang,
  frame_74_jumphang,
  frame_75_jumphang,
  frame_76_jumphang,
  frame_77_jumphang,
  __QS_ACT(actions_2_hang_climb),
  frame_78_jumphang,
  frame_79_jumphang,
  frame_80_jumphang,
  __QS_JMP(hang), // goto "hang"

  __QS_LABEL(jumphangLong) // jumphang (long: DX = 4)
  __QS_ACT(actions_1_run_jump),
  frame_67_start_jump_up_1,
  frame_68_start_jump_up_2,
  frame_69_start_jump_up_3,
  frame_70_jumphang,
  frame_71_jumphang,
  frame_72_jumphang,
  frame_73_jumphang,
  frame_74_jumphang,
  frame_75_jumphang,
  frame_76_jumphang,
  frame_77_jumphang,
  __QS_ACT(actions_2_hang_climb),
  __QS_DX(1),
  frame_78_jumphang,
  __QS_DX(2),
  frame_79_jumphang,
  __QS_DX(1),
  frame_80_jumphang,
  __QS_JMP(hang), // goto "hang"

  __QS_LABEL(jumpbackhang) // jumpbackhang
  __QS_ACT(actions_1_run_jump),
  frame_67_start_jump_up_1,
  frame_68_start_jump_up_2,
  frame_69_start_jump_up_3,
  frame_70_jumphang,
  frame_71_jumphang,
  frame_72_jumphang,
  frame_73_jumphang,
  frame_74_jumphang,
  frame_75_jumphang,
  frame_76_jumphang,
  __QS_DX(-1),
  frame_77_jumphang,
  __QS_ACT(actions_2_hang_climb),
  __QS_DX(-2),
  frame_78_jumphang,
  __QS_DX(-1),
  frame_79_jumphang,
  __QS_DX(-1),
  frame_80_jumphang,
  __QS_JMP(hang), // goto "hang"

  __QS_LABEL(hang) // hang
  __QS_ACT(actions_2_hang_climb),
  frame_91_hanging_5,
  /* "hang1" */ __QS_LABEL(hang1) frame_90_hanging_4,
  frame_89_hanging_3,
  frame_88_hanging_2,
  frame_87_hanging_1,
  frame_87_hanging_1,
  frame_87_hanging_1,
  frame_88_hanging_2,
  frame_89_hanging_3,
  frame_90_hanging_4,
  frame_91_hanging_5,
  frame_92_hanging_6,
  frame_93_hanging_7,
  frame_94_hanging_8,
  frame_95_hanging_9,
  frame_96_hanging_10,
  frame_97_hanging_11,
  frame_98_hanging_12,
  frame_99_hanging_13,
  frame_97_hanging_11,
  frame_96_hanging_10,
  frame_95_hanging_9,
  frame_94_hanging_8,
  frame_93_hanging_7,
  frame_92_hanging_6,
  frame_91_hanging_5,
  frame_90_hanging_4,
  frame_89_hanging_3,
  frame_88_hanging_2,
  frame_87_hanging_1,
  frame_88_hanging_2,
  frame_89_hanging_3,
  frame_90_hanging_4,
  frame_91_hanging_5,
  frame_92_hanging_6,
  frame_93_hanging_7,
  frame_94_hanging_8,
  frame_95_hanging_9,
  frame_96_hanging_10,
  frame_95_hanging_9,
  frame_94_hanging_8,
  frame_93_hanging_7,
  frame_92_hanging_6,
  __QS_JMP(hangdrop), // goto "hangdrop"

  __QS_LABEL(hangstraight) // hangstraight
  __QS_ACT(actions_6_hang_straight),
  frame_92_hanging_6, // Apple II source has a bump sound here
  frame_93_hanging_7,
  frame_93_hanging_7,
  frame_92_hanging_6,
  frame_92_hanging_6,
  /* ":loop" */ __QS_LABEL(hangstraight_loop) frame_91_hanging_5,
  __QS_JMP(hangstraight_loop), // goto ":loop"

  __QS_LABEL(climbfail) // climbfail
  frame_135_climbing_1,
  frame_136_climbing_2,
  frame_137_climbing_3,
  frame_137_climbing_3,
  frame_138_climbing_4,
  frame_138_climbing_4,
  frame_138_climbing_4,
  frame_138_climbing_4,
  frame_137_climbing_3,
  frame_136_climbing_2,
  frame_135_climbing_1,
  __QS_DX(-7),
  __QS_JMP(hangdrop), // goto "hangdrop"

  __QS_LABEL(climbdown) // climbdown
  __QS_ACT(actions_1_run_jump),
  frame_148_climbing_14,
  frame_145_climbing_11,
  frame_144_climbing_10,
  frame_143_climbing_9,
  frame_142_climbing_8,
  frame_141_climbing_7,
  __QS_DX(-5),
  __QS_DY(63),
  SEQ_DOWN,
  __QS_ACT(actions_3_in_midair),
  frame_140_climbing_6,
  frame_138_climbing_4,
  frame_136_climbing_2,
  frame_91_hanging_5,
  __QS_ACT(actions_2_hang_climb),
  __QS_JMP(hang1), // goto "hang1"

  __QS_LABEL(climbup) // climbup
  __QS_ACT(actions_1_run_jump),
  frame_135_climbing_1,
  frame_136_climbing_2,
  frame_137_climbing_3,
  frame_138_climbing_4,
  frame_139_climbing_5,
  frame_140_climbing_6,
  __QS_DX(5),
  __QS_DY(-63),
  SEQ_UP,
  frame_141_climbing_7,
  frame_142_climbing_8,
  frame_143_climbing_9,
  frame_144_climbing_10,
  frame_145_climbing_11,
  frame_146_climbing_12,
  frame_147_climbing_13,
  frame_148_climbing_14,
  __QS_ACT(actions_5_bumped), // to clear flags
  frame_149_climbing_15,
  __QS_ACT(actions_1_run_jump),
  frame_118_stand_up_from_crouch_9,
  frame_119_stand_up_from_crouch_10,
  __QS_DX(1),
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(hangdrop) // hangdrop
  frame_81_hangdrop_1,
  frame_82_hangdrop_2,
  __QS_ACT(actions_5_bumped),
  frame_83_hangdrop_3,
  __QS_ACT(actions_1_run_jump),
  SEQ_KNOCK_DOWN,
  __QS_SND(SND_SILENT),
  frame_84_hangdrop_4,
  frame_85_hangdrop_5,
  __QS_DX(3),
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(hangfall) // hangfall
  __QS_ACT(actions_3_in_midair),
  frame_81_hangdrop_1,
  __QS_DY(6),
  frame_81_hangdrop_1,
  __QS_DY(9),
  frame_81_hangdrop_1,
  __QS_DY(12),
  __QS_DX(2),
  __QS_SET_FALL(0, 12),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(freefall) // freefall
  __QS_ACT(actions_4_in_freefall),
  /* ":loop" */ __QS_LABEL(freefall_loop) frame_106_fall,
  __QS_JMP(freefall_loop), // goto :loop

  __QS_LABEL(runstop) // runstop
  __QS_ACT(actions_1_run_jump),
  frame_53_runturn,
  __QS_DX(2),
  __QS_SND(SND_FOOTSTEP),
  frame_54_runturn,
  __QS_DX(7),
  frame_55_runturn,
  __QS_SND(SND_FOOTSTEP),
  frame_56_runturn,
  __QS_DX(2),
  frame_49_turn,
  __QS_DX(-2),
  frame_50_turn,
  frame_51_turn,
  frame_52_turn,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(jumpup) // jump up (and touch ceiling)
  __QS_ACT(actions_1_run_jump),
  frame_67_start_jump_up_1,
  frame_68_start_jump_up_2,
  frame_69_start_jump_up_3,
  frame_70_jumphang,
  frame_71_jumphang,
  frame_72_jumphang,
  frame_73_jumphang,
  frame_74_jumphang,
  frame_75_jumphang,
  frame_76_jumphang,
  frame_77_jumphang,
  frame_78_jumphang,
  __QS_ACT(actions_0_stand),
  SEQ_KNOCK_UP,
  frame_79_jumphang,
  __QS_JMP(hangdrop), // goto "hangdrop"

  __QS_LABEL(highjump) // highjump (no ceiling above)
  __QS_ACT(actions_1_run_jump),
  frame_67_start_jump_up_1,
  frame_68_start_jump_up_2,
  frame_69_start_jump_up_3,
  frame_70_jumphang,
  frame_71_jumphang,
  frame_72_jumphang,
  frame_73_jumphang,
  frame_74_jumphang,
  frame_75_jumphang,
  frame_76_jumphang,
  frame_77_jumphang,
  frame_78_jumphang,
  frame_79_jumphang,
  __QS_DY(-4),
  frame_79_jumphang,
  __QS_DY(-2),
  frame_79_jumphang,
  frame_79_jumphang,
  __QS_DY(2),
  frame_79_jumphang,
  __QS_DY(4),
  __QS_JMP(hangdrop), // goto "hangdrop"

  __QS_LABEL(superhijump) // superhijump (when weightless)
  frame_67_start_jump_up_1,
  frame_68_start_jump_up_2,
  frame_69_start_jump_up_3,
  frame_70_jumphang,
  frame_71_jumphang,
  frame_72_jumphang,
  frame_73_jumphang,
  frame_74_jumphang,
  frame_75_jumphang,
  frame_76_jumphang,
  __QS_DY(-1),
  frame_77_jumphang,
  __QS_DY(-3),
  frame_78_jumphang,
  __QS_DY(-4),
  frame_79_jumphang,
  __QS_DY(-10),
  frame_79_jumphang,
  __QS_DY(-9),
  frame_79_jumphang,
  __QS_DY(-8),
  frame_79_jumphang,
  __QS_DY(-7),
  frame_79_jumphang,
  __QS_DY(-6),
  frame_79_jumphang,
  __QS_DY(-5),
  frame_79_jumphang,
  __QS_DY(-4),
  frame_79_jumphang,
  __QS_DY(-3),
  frame_79_jumphang,
  __QS_DY(-2),
  frame_79_jumphang,
  __QS_DY(-2),
  frame_79_jumphang,
  __QS_DY(-1),
  frame_79_jumphang,
  __QS_DY(-1),
  frame_79_jumphang,
  __QS_DY(-1),
  frame_79_jumphang,
  frame_79_jumphang,
  frame_79_jumphang,
  frame_79_jumphang,
  __QS_DY(1),
  frame_79_jumphang,
  __QS_DY(1),
  frame_79_jumphang,
  __QS_DY(2),
  frame_79_jumphang,
  __QS_DY(2),
  frame_79_jumphang,
  __QS_DY(3),
  frame_79_jumphang,
  __QS_DY(4),
  frame_79_jumphang,
  __QS_DY(5),
  frame_79_jumphang,
  __QS_DY(6),
  frame_79_jumphang,
  __QS_SET_FALL(0, 6),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(fallhang) // fall hang
  __QS_ACT(actions_3_in_midair),
  frame_80_jumphang,
  __QS_JMP(hang), // goto "hang"

  __QS_LABEL(bump) // bump
  __QS_ACT(actions_5_bumped),
  __QS_DX(-4),
  frame_50_turn,
  frame_51_turn,
  frame_52_turn,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(bumpfall) // bumpfall
  __QS_ACT(actions_5_bumped),
  __QS_DX(1),
  __QS_DY(3),
  __QS_JMP_IF_FEATHER(bumpfloat),
  frame_102_start_fall_1,
  __QS_DX(2),
  __QS_DY(6),
  frame_103_start_fall_2,
  __QS_DX(-1),
  __QS_DY(9),
  frame_104_start_fall_3,
  __QS_DY(12),
  frame_105_start_fall_4,
  __QS_DX(-2),
  __QS_SET_FALL(0, 15),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(bumpfloat) // bumpfloat
  frame_102_start_fall_1,
  __QS_DX(2),
  __QS_DY(3),
  frame_103_start_fall_2,
  __QS_DX(-1),
  __QS_DY(4),
  frame_104_start_fall_3,
  __QS_DY(5),
  frame_105_start_fall_4,
  __QS_DX(-2),
  __QS_SET_FALL(0, 6),
  __QS_JMP(freefall), // goto "freefall"

  __QS_LABEL(hardbump) // hard bump
  __QS_ACT(actions_5_bumped),
  __QS_DX(-1),
  __QS_DY(-4),
  frame_102_start_fall_1,
  __QS_DX(-1),
  __QS_DY(3),
  __QS_DX(-3),
  __QS_DY(1),
  SEQ_KNOCK_DOWN,
  __QS_DX(1),
  __QS_SND(SND_FOOTSTEP),
  frame_107_fall_land_1,
  __QS_DX(2),
  frame_108_fall_land_2,
  __QS_SND(SND_FOOTSTEP),
  frame_109_crouch,
  __QS_JMP(standup), // goto "standup"

  __QS_LABEL(testfoot) // test foot
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  frame_123_stepping_3,
  __QS_DX(2),
  frame_124_stepping_4,
  __QS_DX(4),
  frame_125_stepping_5,
  __QS_DX(3),
  frame_126_stepping_6,
  __QS_DX(-4),
  frame_86_test_foot,
  __QS_SND(SND_FOOTSTEP),
  SEQ_KNOCK_DOWN,
  __QS_DX(-4),
  frame_116_stand_up_from_crouch_7,
  __QS_DX(-2),
  frame_117_stand_up_from_crouch_8,
  frame_118_stand_up_from_crouch_9,
  frame_119_stand_up_from_crouch_10,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(stepback) // step back
  __QS_DX(-5),
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step14) // step forward 14 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(3),
  frame_124_stepping_4,
  __QS_DX(4),
  frame_125_stepping_5,
  __QS_DX(3),
  frame_126_stepping_6,
  __QS_DX(-1),
  __QS_DX(3),
  frame_127_stepping_7,
  frame_128_stepping_8,
  frame_129_stepping_9,
  frame_130_stepping_10,
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step13) // step forward 13 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(3),
  frame_124_stepping_4,
  __QS_DX(4),
  frame_125_stepping_5,
  __QS_DX(3),
  frame_126_stepping_6,
  __QS_DX(-1),
  __QS_DX(2),
  frame_127_stepping_7,
  frame_128_stepping_8,
  frame_129_stepping_9,
  frame_130_stepping_10,
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step12) // step forward 12 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(3),
  frame_124_stepping_4,
  __QS_DX(4),
  frame_125_stepping_5,
  __QS_DX(3),
  frame_126_stepping_6,
  __QS_DX(-1),
  __QS_DX(1),
  frame_127_stepping_7,
  frame_128_stepping_8,
  frame_129_stepping_9,
  frame_130_stepping_10,
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step11) // step forward 11 pixels (normal step)
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(3),
  frame_124_stepping_4,
  __QS_DX(4),
  frame_125_stepping_5,
  __QS_DX(3),
  frame_126_stepping_6,
  __QS_DX(-1),
  frame_127_stepping_7,
  frame_128_stepping_8,
  frame_129_stepping_9,
  frame_130_stepping_10,
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step10) // step forward 10 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  /* "step10a "*/ __QS_LABEL(step10a) frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(3),
  frame_124_stepping_4,
  __QS_DX(4),
  frame_125_stepping_5,
  __QS_DX(3),
  frame_126_stepping_6,
  __QS_DX(-) 2,
  frame_128_stepping_8,
  frame_129_stepping_9,
  frame_130_stepping_10,
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step9) // step forward 9 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_JMP(step10a), // goto "step10a"

  __QS_LABEL(step8) // step forward 8 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(3),
  frame_124_stepping_4,
  __QS_DX(4),
  frame_125_stepping_5,
  __QS_DX(-1),
  frame_127_stepping_7,
  frame_128_stepping_8,
  frame_129_stepping_9,
  frame_130_stepping_10,
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step7) // step forward 7 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(3),
  frame_124_stepping_4,
  __QS_DX(2),
  frame_129_stepping_9,
  frame_130_stepping_10,
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step6) // step forward 6 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(2),
  frame_124_stepping_4,
  __QS_DX(2),
  frame_129_stepping_9,
  frame_130_stepping_10,
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step5) // step forward 5 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(2),
  frame_124_stepping_4,
  __QS_DX(1),
  frame_129_stepping_9,
  frame_130_stepping_10,
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step4) // step forward 4 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(2),
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step3) // step forward 3 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_123_stepping_3,
  __QS_DX(1),
  frame_131_stepping_11,
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step2) // step forward 2 pixels
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_122_stepping_2,
  __QS_DX(1),
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(step1) // step forward 1 pixel
  __QS_ACT(actions_1_run_jump),
  frame_121_stepping_1,
  __QS_DX(1),
  frame_132_stepping_12,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(stoop) // stoop
  __QS_ACT(actions_1_run_jump),
  __QS_DX(1),
  frame_107_fall_land_1,
  __QS_DX(2),
  frame_108_fall_land_2,
  /* ":crouch" */ __QS_LABEL(stoop_crouch) frame_109_crouch,
  __QS_JMP(stoop_crouch), // goto ":crouch

  __QS_LABEL(standup) // stand up
  __QS_ACT(actions_5_bumped),
  __QS_DX(1),
  frame_110_stand_up_from_crouch_1,
  frame_111_stand_up_from_crouch_2,
  __QS_DX(2),
  frame_112_stand_up_from_crouch_3,
  frame_113_stand_up_from_crouch_4,
  __QS_DX(1),
  frame_114_stand_up_from_crouch_5,
  frame_115_stand_up_from_crouch_6,
  frame_116_stand_up_from_crouch_7,
  __QS_DX(-4),
  frame_117_stand_up_from_crouch_8,
  frame_118_stand_up_from_crouch_9,
  frame_119_stand_up_from_crouch_10,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(pickupsword) // pick up sword
  __QS_ACT(actions_1_run_jump),
  SEQ_GET_ITEM,
  1,
  frame_229_found_sword,
  frame_229_found_sword,
  frame_229_found_sword,
  frame_229_found_sword,
  frame_229_found_sword,
  frame_229_found_sword,
  frame_230_sheathe,
  frame_231_sheathe,
  frame_232_sheathe,
  __QS_JMP(resheathe), // goto "resheathe"

  __QS_LABEL(resheathe) // resheathe
  __QS_ACT(actions_1_run_jump),
  __QS_DX(-5),
  frame_233_sheathe,
  frame_234_sheathe,
  frame_235_sheathe,
  frame_236_sheathe,
  frame_237_sheathe,
  frame_238_sheathe,
  frame_239_sheathe,
  frame_240_sheathe,
  frame_133_sheathe,
  frame_133_sheathe,
  frame_134_sheathe,
  frame_134_sheathe,
  frame_134_sheathe,
  frame_48_turn,
  __QS_DX(1),
  frame_49_turn,
  __QS_DX(-2),
  __QS_ACT(actions_5_bumped),
  frame_50_turn,
  __QS_ACT(actions_1_run_jump),
  frame_51_turn,
  frame_52_turn,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(fastsheathe) // fast sheathe
  __QS_ACT(actions_1_run_jump),
  __QS_DX(-5),
  frame_234_sheathe,
  frame_236_sheathe,
  frame_238_sheathe,
  frame_240_sheathe,
  frame_134_sheathe,
  __QS_DX(-1),
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(drinkpotion) // drink potion
  __QS_ACT(actions_1_run_jump),
  __QS_DX(4),
  frame_191_drink,
  frame_192_drink,
  frame_193_drink,
  frame_194_drink,
  frame_195_drink,
  frame_196_drink,
  frame_197_drink,
  __QS_SND(SND_DRINK),
  frame_198_drink,
  frame_199_drink,
  frame_200_drink,
  frame_201_drink,
  frame_202_drink,
  frame_203_drink,
  frame_204_drink,
  frame_205_drink,
  frame_205_drink,
  frame_205_drink,
  SEQ_GET_ITEM,
  1,
  frame_205_drink,
  frame_205_drink,
  frame_201_drink,
  frame_198_drink,
  __QS_DX(-4),
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(softland) // soft land
  __QS_ACT(actions_5_bumped),
  SEQ_KNOCK_DOWN,
  __QS_DX(1),
  frame_107_fall_land_1,
  __QS_DX(2),
  frame_108_fall_land_2,
  __QS_ACT(actions_1_run_jump),
  /* ":crouch" */ __QS_LABEL(softland_crouch) frame_109_crouch,
  __QS_JMP(softland_crouch), // goto ":crouch"

  __QS_LABEL(landrun) // land run
  __QS_ACT(actions_1_run_jump),
  __QS_DY(-2),
  __QS_DX(1),
  frame_107_fall_land_1,
  __QS_DX(2),
  frame_108_fall_land_2,
  frame_109_crouch,
  __QS_DX(1),
  frame_110_stand_up_from_crouch_1,
  frame_111_stand_up_from_crouch_2,
  __QS_DX(2),
  frame_112_stand_up_from_crouch_3,
  frame_113_stand_up_from_crouch_4,
  __QS_DX(1),
  __QS_DY(1),
  frame_114_stand_up_from_crouch_5,
  __QS_DY(1),
  frame_115_stand_up_from_crouch_6,
  __QS_DX(-2),
  __QS_JMP(runstt4), // goto "runstt4"

  __QS_LABEL(medland) // medium land (1.5 - 2 stories)
  __QS_ACT(actions_5_bumped),
  SEQ_KNOCK_DOWN,
  __QS_DY(-2),
  __QS_DX(1),
  __QS_DX(2),
  frame_108_fall_land_2,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  frame_109_crouch,
  __QS_DX(1),
  frame_110_stand_up_from_crouch_1,
  frame_110_stand_up_from_crouch_1,
  frame_110_stand_up_from_crouch_1,
  frame_111_stand_up_from_crouch_2,
  __QS_DX(2),
  frame_112_stand_up_from_crouch_3,
  frame_113_stand_up_from_crouch_4,
  __QS_DX(1),
  __QS_DY(1),
  frame_114_stand_up_from_crouch_5,
  __QS_DY(1),
  frame_115_stand_up_from_crouch_6,
  frame_116_stand_up_from_crouch_7,
  __QS_DX(-4),
  frame_117_stand_up_from_crouch_8,
  frame_118_stand_up_from_crouch_9,
  frame_119_stand_up_from_crouch_10,
  __QS_JMP(stand), // goto "stand"

  __QS_LABEL(hardland) // hard land (splat!; >2 stories)
  __QS_ACT(actions_5_bumped),
  SEQ_KNOCK_DOWN,
  __QS_DY(-2),
  __QS_DX(3),
  frame_185_dead,
  SEQ_DIE,
  /* ":dead" */ __QS_LABEL(hardland_dead) frame_185_dead,
  __QS_JMP(hardland_dead), // goto ":dead"

  __QS_LABEL(stabkill) // stabkill
  __QS_ACT(actions_5_bumped),
  __QS_JMP(dropdead), // goto "dropdead"

  __QS_LABEL(dropdead) // dropdead
  __QS_ACT(actions_1_run_jump),
  SEQ_DIE,
  frame_179_collapse_1,
  frame_180_collapse_2,
  frame_181_collapse_3,
  frame_182_collapse_4,
  __QS_DX(1),
  frame_183_collapse_5,
  __QS_DX(-4),
  /* ":dead" */ __QS_LABEL(dropdead_dead) frame_185_dead,
  __QS_JMP(dropdead_dead), // goto ":dead"

  __QS_LABEL(impale) // impale
  __QS_ACT(actions_1_run_jump),
  SEQ_KNOCK_DOWN,
  __QS_DX(4),
  frame_177_spiked,
  SEQ_DIE,
  /* ":dead" */ __QS_LABEL(impale_dead) frame_177_spiked,
  __QS_JMP(impale_dead), // goto ":dead"

  __QS_LABEL(halve) // halve
  __QS_ACT(actions_1_run_jump),
  frame_178_chomped,
  SEQ_DIE,
  /* ":dead" */ __QS_LABEL(halve_dead) frame_178_chomped,
  __QS_JMP(halve_dead), // goto ":dead"

  __QS_LABEL(crush)  // crush
  __QS_JMP(medland), // goto "medland"

  __QS_LABEL(deadfall) // deadfall
  __QS_SET_FALL(0, 0),
  __QS_ACT(actions_4_in_freefall),
  /* ":loop"*/ __QS_LABEL(deadfall_loop) frame_185_dead,
  __QS_JMP(deadfall_loop), // goto ":loop"

  __QS_LABEL(climbstairs) // climb stairs
  __QS_ACT(actions_5_bumped),
  __QS_DX(-5),
  __QS_DY(-1),
  __QS_SND(SND_FOOTSTEP),
  frame_217_exit_stairs_1,
  frame_218_exit_stairs_2,
  frame_219_exit_stairs_3,
  __QS_DX(1),
  frame_220_exit_stairs_4,
  __QS_DX(-4),
  __QS_DY(-3),
  __QS_SND(SND_FOOTSTEP),
  frame_221_exit_stairs_5,
  __QS_DX(-4),
  __QS_DY(-2),
  frame_222_exit_stairs_6,
  __QS_DX(-2),
  __QS_DY(-3),
  frame_223_exit_stairs_7,
  __QS_DX(-3),
  __QS_DY(-8),
  __QS_SND(SND_LEVEL),
  __QS_SND(SND_FOOTSTEP),
  frame_224_exit_stairs_8,
  __QS_DX(-1),
  __QS_DY(-1),
  frame_225_exit_stairs_9,
  __QS_DX(-3),
  __QS_DY(-4),
  frame_226_exit_stairs_10,
  __QS_DX(-1),
  __QS_DY(-5),
  __QS_SND(SND_FOOTSTEP),
  frame_227_exit_stairs_11,
  __QS_DX(-2),
  __QS_DY(-1),
  frame_228_exit_stairs_12,
  frame_0,
  __QS_SND(SND_FOOTSTEP),
  frame_0,
  frame_0,
  frame_0, // these footsteps are only heard when the music is off
  __QS_SND(SND_FOOTSTEP),
  frame_0,
  frame_0,
  frame_0,
  __QS_SND(SND_FOOTSTEP),
  frame_0,
  frame_0,
  frame_0,
  __QS_SND(SND_FOOTSTEP),
  SEQ_END_LEVEL,
  /* ":loop" */ __QS_LABEL(climbstairs_loop) frame_0,
  __QS_JMP(climbstairs_loop), // goto ":loop"

  __QS_LABEL(Vstand) // Vizier: stand
  alt2frame_54_Vstand,
  __QS_JMP(Vstand), // goto "Vstand"

  __QS_LABEL(Vraise) // Vizier: raise arms
  85,
  67,
  67,
  67, // numbers refer to frames in the "alternate" frame sets
  67,
  67,
  67,
  67,
  67,
  67,
  67,
  68,
  69,
  70,
  71,
  72,
  73,
  74,
  75,
  83,
  84,
  /* ":loop" */ __QS_LABEL(Vraise_loop) 76,
  __QS_JMP(Vraise_loop), // goto ":loop"

  __QS_LABEL(Vwalk) // Vizier: walk
  __QS_DX(1),
  /* "Vwalk1" */ __QS_LABEL(Vwalk1) 48,
  __QS_DX(2),
  /* "Vwalk2" */ __QS_LABEL(Vwalk2) 49,
  __QS_DX(6),
  50,
  __QS_DX(1),
  51,
  __QS_DX(-1),
  52,
  __QS_DX(1),
  53,
  __QS_DX(1),
  __QS_JMP(Vwalk1), // goto "Vwalk1"

  __QS_LABEL(Vstop) // Vizier: stop
  __QS_DX(1),
  55,
  56,
  __QS_JMP(Vstand),

  __QS_LABEL(Vexit) // Vizier: lower arms, turn & exit ("Vexit")
  77,
  78,
  79,
  80,
  81,
  82,
  __QS_DX(1),
  54,
  54,
  54,
  54,
  54,
  54,
  57,
  58,
  59,
  60,
  61,
  __QS_DX(2),
  62,
  __QS_DX(-1),
  63,
  __QS_DX(-3),
  64,
  65,
  __QS_DX(-1),
  66,
  SEQ_FLIP,
  __QS_DX(16),
  __QS_DX(3),
  __QS_JMP(Vwalk2), // goto "Vwalk2"

  // Princess: stand
  __QS_LABEL(Pstand) 11,
  __QS_JMP(Pstand), // goto "Pstand"

  __QS_LABEL(Palert) // Princess: alert
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  SEQ_FLIP,
  __QS_DX(8),
  11,
  __QS_JMP(Pstand),

  __QS_LABEL(Pstepback) // Princess: step back
  SEQ_FLIP,
  __QS_DX(11),
  12,
  __QS_DX(1),
  13,
  __QS_DX(1),
  14,
  __QS_DX(3),
  15,
  __QS_DX(1),
  16,
  /* ":loop" */ __QS_LABEL(Pstepback_loop) 17,
  __QS_JMP(Pstepback_loop), // goto ":loop"

  __QS_LABEL(Plie) // Princess lying on cushions ("Plie")
  19,
  __QS_JMP(Plie), // goto "Plie"

  __QS_LABEL(Pwaiting) // Princess: waiting
  /* ":loop" */ 20,
  __QS_JMP(Pwaiting), // goto ":loop"

  __QS_LABEL(Pembrace) // Princess: embrace
  21,
  __QS_DX(1),
  22,
  23,
  24,
  __QS_DX(1),
  25,
  __QS_DX(-3),
  26,
  __QS_DX(-2),
  27,
  __QS_DX(-4),
  28,
  __QS_DX(-3),
  29,
  __QS_DX(-2),
  30,
  __QS_DX(-3),
  31,
  __QS_DX(-1),
  32,
  /* ":loop" */ __QS_LABEL(Pembrace_loop) 33,
  __QS_JMP(Pembrace_loop), // goto ":loop"

  __QS_LABEL(Pstroke) // Princess: stroke mouse
  /* ":loop" */ 37,
  __QS_JMP(Pstroke), // goto ":loop"

  __QS_LABEL(Prise) // Princess: rise
  37,
  38,
  39,
  40,
  41,
  42,
  43,
  44,
  45,
  46,
  47,
  SEQ_FLIP,
  __QS_DX(12),
  /* ":loop" */ __QS_LABEL(Prise_loop) 11,
  __QS_JMP(Prise_loop), // goto ":loop"

  __QS_LABEL(Pcrouch) // Princess: crouch & stroke mouse
  11,
  11,
  SEQ_FLIP,
  __QS_DX(13),
  47,
  46,
  45,
  44,
  43,
  42,
  41,
  40,
  39,
  38,
  37,
  36,
  36,
  36,
  35,
  35,
  35,
  34,
  34,
  34,
  34,
  34,
  34,
  34,
  35,
  35,
  36,
  36,
  36,
  35,
  35,
  35,
  34,
  34,
  34,
  34,
  34,
  34,
  34,
  35,
  35,
  36,
  36,
  36,
  35,
  35,
  35,
  34,
  34,
  34,
  34,
  34,
  34,
  34,
  34,
  34,
  35,
  35,
  35,
  /* ":loop" */ __QS_LABEL(Pcrouch_loop) 36,
  __QS_JMP(Pcrouch_loop), // goto ":loop"

  __QS_LABEL(Pslump) // Princess: slump shoulders
  1,
  /* ":loop" */ __QS_LABEL(Pslump_loop) 18,
  __QS_JMP(Pslump_loop), // goto ":loop"

  __QS_LABEL(Mscurry) // Mouse: scurry
  __QS_ACT(actions_1_run_jump),
  /* "Mscurry1" */ __QS_LABEL(Mscurry1) frame_186_mouse_1,
  __QS_DX(5),
  frame_186_mouse_1,
  __QS_DX(3),
  frame_187_mouse_2,
  __QS_DX(4),
  __QS_JMP(Mscurry1), // goto "Mscurry1"

  __QS_LABEL(Mstop) // Mouse: stop
  /* ":loop" */ frame_186_mouse_1,
  __QS_JMP(Mstop), // goto ":loop"

  __QS_LABEL(Mraise) // Mouse: raise head
  /* ":loop" */ frame_188_mouse_stand,
  __QS_JMP(Mraise), // goto ":loop"

  __QS_LABEL(Mleave) // Mouse: leave
  __QS_ACT(actions_0_stand),
  frame_186_mouse_1,
  frame_186_mouse_1,
  frame_186_mouse_1,
  frame_188_mouse_stand,
  frame_188_mouse_stand,
  frame_188_mouse_stand,
  frame_188_mouse_stand,
  frame_188_mouse_stand,
  frame_188_mouse_stand,
  frame_188_mouse_stand,
  frame_188_mouse_stand,
  SEQ_FLIP,
  __QS_DX(8),
  __QS_JMP(Mscurry1), // goto "Mscurry1"

  __QS_LABEL(Mclimb) // Mouse: climb
  frame_186_mouse_1,
  frame_186_mouse_1,
  /* ":loop" */ __QS_LABEL(Mclimb_loop) frame_188_mouse_stand,
  __QS_JMP(Mclimb_loop) // goto ":loop"

};
extern const uint8_t seqtbl[]; // the sequence table is defined in seqtbl.c
extern const uint16_t seqtbl_offsets[];
static const uint8_t optgraf_min[] = {0x01, 0x1E, 0x4B, 0x4E, 0x56, 0x65, 0x7F, 0x0A};
static const uint8_t optgraf_max[] = {0x09, 0x1F, 0x4D, 0x53, 0x5B, 0x7B, 0x8F, 0x0D};

static const char *const tbl_guard_dat[] = {"GUARD.DAT", "FAT.DAT", "SKEL.DAT", "VIZIER.DAT", "SHADOW.DAT"};
static const char *const tbl_envir_gr[] = {"", "C", "C", "E", "E", "V"};
static const char *const tbl_envir_ki[] = {"DUNGEON", "PALACE"};
static const rect_type rect_titles = {106, 24, 195, 296};

static const int16_t y_something[] = {-1, 62, 125, 188, 25};
static const uint8_t loose_sound[] = {0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0};
static const uint16_t y_loose_land[] = {2, 65, 128, 191, 254};
static const uint8_t leveldoor_close_speeds[] = {0, 5, 17, 99, 0};
static const uint8_t gate_close_speeds[] = {0, 0, 0, 20, 40, 60, 80, 100, 120};
static const int8_t door_delta[] = {-1, 4, 4};
static const uint8_t door_fram_slice[] = {67, 59, 58, 57, 56, 55, 54, 53, 52};
static const uint16_t floor_left_overlay[] = {32, 151, 151, 150, 150, 151, 32, 32};
static const uint8_t spikes_fram_fore[] = {0, 139, 140, 141, 142, 143, 142, 140, 139, 0};
static const uint8_t chomper_fram_for[] = {106, 107, 108, 109, 110, 0};
static const uint8_t wall_fram_main[] = {8, 10, 6, 4};
static const uint8_t spikes_fram_left[] = {0, 128, 129, 130, 131, 132, 131, 129, 128, 0};
static const uint8_t potion_fram_bubb[] = {0, 16, 17, 18, 19, 20, 21, 22};
static const uint8_t chomper_fram1[] = {3, 2, 0, 1, 4, 3, 3, 0};
static const uint8_t chomper_fram_bot[] = {101, 102, 103, 104, 105, 0};
static const uint8_t chomper_fram_top[] = {0, 0, 111, 112, 113, 0};
static const uint8_t chomper_fram_y[] = {0, 0, 0x25, 0x2F, 0x32};
static const uint8_t loose_fram_left[] = {41, 69, 41, 70, 70, 41, 41, 41, 70, 70, 70, 0};
static const uint8_t loose_fram_bottom[] = {43, 73, 43, 74, 74, 43, 43, 43, 74, 74, 74, 0};
static const uint8_t wall_fram_bottom[] = {7, 9, 5, 3};
static const uint8_t spikes_fram_right[] = {0, 134, 135, 136, 137, 138, 137, 135, 134, 0};
static const uint8_t loose_fram_right[] = {42, 71, 42, 72, 72, 42, 42, 42, 72, 72, 72, 0};
static const uint8_t blueline_fram1[] = {0, 124, 125, 126};
static const int8_t blueline_fram_y[] = {0, -20, -20, 0};
static const uint8_t blueline_fram3[] = {44, 44, 45, 45};
static const uint8_t doortop_fram_bot[] = {78, 80, 82, 0};
static const uint8_t door_fram_top[] = {60, 61, 62, 63, 64, 65, 66, 67};
static const uint8_t doortop_fram_top[] = {0, 81, 83, 0};
static const uint16_t col_xh[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36};

static const piece tile_table[31] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},        // 0x00 empty
  {41, 1, 0, 42, 1, 2, 145, 0, 43, 0, 0, 0},   // 0x01 floor
  {127, 1, 0, 133, 1, 2, 145, 0, 43, 0, 0, 0}, // 0x02 spike
  {92, 1, 0, 93, 1, 2, 0, 94, 43, 95, 1, 0},   // 0x03 pillar
  {46, 1, 0, 47, 1, 2, 0, 48, 43, 49, 3, 0},   // 0x04 door
  {41, 1, 1, 35, 1, 3, 145, 0, 36, 0, 0, 0},   // 0x05 stuck floor
  {41, 1, 0, 42, 1, 2, 145, 0, 96, 0, 0, 0},   // 0x06 close button
  {46, 1, 0, 0, 0, 2, 0, 0, 43, 49, 3, 0},     // 0x07 door top with floor
  {86, 1, 0, 87, 1, 2, 0, 0, 43, 88, 1, 0},    // 0x08 big pillar bottom
  {0, 0, 0, 89, 0, 3, 0, 90, 0, 91, 1, 3},     // 0x09 big pillar top
  {41, 1, 0, 42, 1, 2, 145, 0, 43, 12, 2, -3}, // 0x0A potion
  {0, 1, 0, 0, 0, 0, 145, 0, 0, 0, 0, 0},      // 0x0B loose floor
  {0, 0, 0, 0, 0, 2, 0, 0, 85, 49, 3, 0},      // 0x0C door top
  {75, 1, 0, 42, 1, 2, 0, 0, 43, 77, 0, 0},    // 0x0D mirror
  {97, 1, 0, 98, 1, 2, 145, 0, 43, 100, 0, 0}, // 0x0E debris
  {147, 1, 0, 42, 1, 1, 145, 0, 149, 0, 0, 0}, // 0x0F open button
  {41, 1, 0, 37, 0, 0, 0, 38, 43, 0, 0, 0},    // 0x10 leveldoor left
  {0, 0, 0, 39, 1, 2, 0, 40, 43, 0, 0, 0},     // 0x11 leveldoor right
  {0, 0, 0, 42, 1, 2, 145, 0, 43, 0, 0, 0},    // 0x12 chomper
  {41, 1, 0, 42, 1, 2, 0, 0, 43, 0, 0, 0},     // 0x13 torch
  {0, 0, 0, 1, 1, 2, 0, 2, 0, 0, 0, 0},        // 0x14 wall
  {30, 1, 0, 31, 1, 2, 0, 0, 43, 0, 0, 0},     // 0x15 skeleton
  {41, 1, 0, 42, 1, 2, 145, 0, 43, 0, 0, 0},   // 0x16 sword
  {41, 1, 0, 10, 0, 0, 0, 11, 43, 0, 0, 0},    // 0x17 balcony left
  {0, 0, 0, 12, 1, 2, 0, 13, 43, 0, 0, 0},     // 0x18 balcony right
  {92, 1, 0, 42, 1, 2, 145, 0, 43, 95, 1, 0},  // 0x19 lattice pillar
  {1, 0, 0, 0, 0, 0, 0, 0, 2, 9, 0, -53},      // 0x1A lattice down
  {3, 0, -10, 0, 0, 0, 0, 0, 0, 9, 0, -53},    // 0x1B lattice small
  {4, 0, -10, 0, 0, 0, 0, 0, 0, 9, 0, -53},    // 0x1C lattice left
  {5, 0, -10, 0, 0, 0, 0, 0, 0, 9, 0, -53},    // 0x1D lattice right
  {97, 1, 0, 98, 1, 2, 0, 0, 43, 100, 0, 0},   // 0x1E debris with torch
};

static const uint8_t sound_prio_table[] = {
  0x14, // sound_0_fell_to_death
  0x1E, // sound_1_falling
  0x23, // sound_2_tile_crashing
  0x66, // sound_3_button_pressed
  0x32, // sound_4_gate_closing
  0x37, // sound_5_gate_opening
  0x30, // sound_6_gate_closing_fast
  0x30, // sound_7_gate_stop
  0x4B, // sound_8_bumped
  0x50, // sound_9_grab
  0x0A, // sound_10_sword_vs_sword
  0x12, // sound_11_sword_moving
  0x0C, // sound_12_guard_hurt
  0x0B, // sound_13_kid_hurt
  0x69, // sound_14_leveldoor_closing
  0x6E, // sound_15_leveldoor_sliding
  0x73, // sound_16_medium_land
  0x78, // sound_17_soft_land
  0x7D, // sound_18_drink
  0x82, // sound_19_draw_sword
  0x91, // sound_20_loose_shake_1
  0x96, // sound_21_loose_shake_2
  0x9B, // sound_22_loose_shake_3
  0xA0, // sound_23_footstep
  0x01, // sound_24_death_regular
  0x01, // sound_25_presentation
  0x01, // sound_26_embrace
  0x01, // sound_27_cutscene_2_4_6_12
  0x01, // sound_28_death_in_fight
  0x13, // sound_29_meet_Jaffar
  0x01, // sound_30_big_potion
  0x01, // sound_31
  0x01, // sound_32_shadow_music
  0x01, // sound_33_small_potion
  0x01, // sound_34
  0x01, // sound_35_cutscene_8_9
  0x01, // sound_36_out_of_time
  0x01, // sound_37_victory
  0x01, // sound_38_blink
  0x00, // sound_39_low_weight
  0x01, // sound_40_cutscene_12_short_time
  0x01, // sound_41_end_level_music
  0x01, // sound_42
  0x01, // sound_43_victory_Jaffar
  0x87, // sound_44_skel_alive
  0x8C, // sound_45_jump_through_mirror
  0x0F, // sound_46_chomped
  0x10, // sound_47_chomper
  0x19, // sound_48_spiked
  0x16, // sound_49_spikes
  0x01, // sound_50_story_2_princess
  0x00, // sound_51_princess_door_opening
  0x01, // sound_52_story_4_Jaffar_leaves
  0x01, // sound_53_story_3_Jaffar_comes
  0x01, // sound_54_intro_music
  0x01, // sound_55_story_1_absence
  0x01, // sound_56_ending_music
  0x00};

static const uint8_t sound_pcspeaker_exists[] = {
  1, // sound_0_fell_to_death
  0, // sound_1_falling
  1, // sound_2_tile_crashing
  1, // sound_3_button_pressed
  1, // sound_4_gate_closing
  1, // sound_5_gate_opening
  1, // sound_6_gate_closing_fast
  1, // sound_7_gate_stop
  1, // sound_8_bumped
  1, // sound_9_grab
  1, // sound_10_sword_vs_sword
  0, // sound_11_sword_moving
  1, // sound_12_guard_hurt
  1, // sound_13_kid_hurt
  1, // sound_14_leveldoor_closing
  1, // sound_15_leveldoor_sliding
  1, // sound_16_medium_land
  1, // sound_17_soft_land
  1, // sound_18_drink
  0, // sound_19_draw_sword
  0, // sound_20_loose_shake_1
  0, // sound_21_loose_shake_2
  0, // sound_22_loose_shake_3
  1, // sound_23_footstep
  1, // sound_24_death_regular
  1, // sound_25_presentation
  1, // sound_26_embrace
  1, // sound_27_cutscene_2_4_6_12
  1, // sound_28_death_in_fight
  1, // sound_29_meet_Jaffar
  1, // sound_30_big_potion
  1, // sound_31
  1, // sound_32_shadow_music
  1, // sound_33_small_potion
  1, // sound_34
  1, // sound_35_cutscene_8_9
  1, // sound_36_out_of_time
  1, // sound_37_victory
  1, // sound_38_blink
  1, // sound_39_low_weight
  1, // sound_40_cutscene_12_short_time
  1, // sound_41_end_level_music
  1, // sound_42
  1, // sound_43_victory_Jaffar
  1, // sound_44_skel_alive
  1, // sound_45_jump_through_mirror
  1, // sound_46_chomped
  1, // sound_47_chomper
  1, // sound_48_spiked
  1, // sound_49_spikes
  1, // sound_50_story_2_princess
  1, // sound_51_princess_door_opening
  1, // sound_52_story_4_Jaffar_leaves
  1, // sound_53_story_3_Jaffar_comes
  1, // sound_54_intro_music
  1, // sound_55_story_1_absence
  1, // sound_56_ending_music
  0};

static char const *const tbl_quotes[2] = {
  "\"(****/****) Incredibly realistic. . . The "
  "adventurer character actually looks human as he "
  "runs, jumps, climbs, and hangs from ledges.\"\n"
  "\n"
  "                                  Computer Entertainer\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\"A tremendous achievement. . . Mechner has crafted "
  "the smoothest animation ever seen in a game of this "
  "type.\n"
  "\n"
  "\"PRINCE OF PERSIA is the STAR WARS of its field.\"\n"
  "\n"
  "                                  Computer Gaming World",
  "\"An unmitigated delight. . . comes as close to "
  "(perfection) as any arcade game has come in a long, "
  "long time. . . what makes this game so wonderful (am "
  "I gushing?) is that the little onscreen character "
  "does not move like a little onscreen character -- he "
  "moves like a person.\"\n"
  "\n"
  "                                      Nibble"};

// data:017A
static const uint16_t copyprot_word[] = {9, 1, 6, 4, 5, 3, 6, 3, 4, 4, 3, 2, 12, 5, 13, 1, 9, 2, 2, 4, 9, 4, 11, 8, 5, 4, 1, 6, 2, 4, 6, 8, 4, 2, 7, 11, 5, 4, 1, 2};
// data:012A
static const uint16_t copyprot_line[] = {2, 1, 5, 4, 3, 5, 1, 3, 7, 2, 2, 4, 6, 6, 2, 6, 3, 1, 2, 3, 2, 2, 3, 10, 5, 6, 5, 6, 3, 5, 7, 2, 2, 4, 5, 7, 2, 6, 5, 5};
// data:00DA
static const uint16_t copyprot_page[] = {5, 3, 7, 3, 3, 4, 1, 5, 12, 5, 11, 10, 1, 2, 8, 8, 2, 4, 6, 1, 4, 7, 3, 2, 1, 7, 10, 1, 4, 3, 4, 1, 4, 1, 8, 1, 1, 10, 3, 3};

static const int8_t wall_dist_from_left[] = {0, 10, 0, -1, 0, 0};
static const int8_t wall_dist_from_right[] = {0, 0, 10, 13, 0, 0};

// data:1712
static const sword_table_type sword_tbl[] = {
  {255, 0, 0},
  {0, 0, -9},
  {5, -9, -29},
  {1, 7, -25},
  {2, 17, -26},
  {6, 7, -14},
  {7, 0, -5},
  {3, 17, -16},
  {4, 16, -19},
  {30, 12, -9},
  {8, 13, -34},
  {9, 7, -25},
  {10, 10, -16},
  {11, 10, -11},
  {12, 22, -21},
  {13, 28, -23},
  {14, 13, -35},
  {15, 0, -38},
  {16, 0, -29},
  {17, 21, -19},
  {18, 14, -23},
  {19, 21, -22},
  {19, 22, -23},
  {17, 7, -13},
  {17, 15, -18},
  {7, 0, -8},
  {1, 7, -27},
  {28, 14, -28},
  {8, 7, -27},
  {4, 6, -23},
  {4, 9, -21},
  {10, 11, -18},
  {13, 24, -23},
  {13, 19, -23},
  {13, 21, -23},
  {20, 7, -32},
  {21, 14, -32},
  {22, 14, -31},
  {23, 14, -29},
  {24, 28, -28},
  {25, 28, -28},
  {26, 21, -25},
  {27, 14, -22},
  {255, 14, -25},
  {255, 21, -25},
  {29, 0, -16},
  {8, 8, -37},
  {31, 14, -24},
  {32, 14, -24},
  {33, 7, -14},
  {8, 8, -37},
};

// data:22A6
static const int8_t tile_div_tbl[256] = {
  -5, -5, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14};

// data:23A6
static const uint8_t tile_mod_tbl[256] = {
  12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 1};

// data:0FE0
static const frame_type frame_table_kid[] = {
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {0, 0x00 | 0, 1, 0, 0xC0 | 4},
  {1, 0x00 | 0, 1, 0, 0x40 | 4},
  {2, 0x00 | 0, 3, 0, 0x40 | 7},
  {3, 0x00 | 0, 4, 0, 0x40 | 8},
  {4, 0x00 | 0, 0, 0, 0xE0 | 6},
  {5, 0x00 | 0, 0, 0, 0x40 | 9},
  {6, 0x00 | 0, 0, 0, 0x40 | 10},
  {7, 0x00 | 0, 0, 0, 0xC0 | 5},
  {8, 0x00 | 0, 0, 0, 0x40 | 4},
  {9, 0x00 | 0, 0, 0, 0x40 | 7},
  {10, 0x00 | 0, 0, 0, 0x40 | 11},
  {11, 0x00 | 0, 0, 0, 0x40 | 3},
  {12, 0x00 | 0, 0, 0, 0xC0 | 3},
  {13, 0x00 | 0, 0, 0, 0x40 | 7},
  {14, 0x00 | 9, 0, 0, 0x40 | 3},
  {15, 0x00 | 0, 0, 0, 0xC0 | 3},
  {16, 0x00 | 0, 0, 0, 0x40 | 4},
  {17, 0x00 | 0, 0, 0, 0x40 | 6},
  {18, 0x00 | 0, 0, 0, 0x40 | 8},
  {19, 0x00 | 0, 0, 0, 0x80 | 9},
  {20, 0x00 | 0, 0, 0, 0x00 | 11},
  {21, 0x00 | 0, 0, 0, 0x80 | 11},
  {22, 0x00 | 0, 0, 0, 0x00 | 17},
  {23, 0x00 | 0, 0, 0, 0x00 | 7},
  {24, 0x00 | 0, 0, 0, 0x00 | 5},
  {25, 0x00 | 0, 0, 0, 0xC0 | 1},
  {26, 0x00 | 0, 0, 0, 0xC0 | 6},
  {27, 0x00 | 0, 0, 0, 0x40 | 3},
  {28, 0x00 | 0, 0, 0, 0x40 | 8},
  {29, 0x00 | 0, 0, 0, 0x40 | 2},
  {30, 0x00 | 0, 0, 0, 0x40 | 2},
  {31, 0x00 | 0, 0, 0, 0xC0 | 2},
  {32, 0x00 | 0, 0, 0, 0xC0 | 2},
  {33, 0x00 | 0, 0, 0, 0x40 | 3},
  {34, 0x00 | 0, 0, 0, 0x40 | 8},
  {35, 0x00 | 0, 0, 0, 0xC0 | 14},
  {36, 0x00 | 0, 0, 0, 0xC0 | 1},
  {37, 0x00 | 0, 0, 0, 0x40 | 5},
  {38, 0x00 | 0, 0, 0, 0x80 | 14},
  {39, 0x00 | 0, 0, 0, 0x00 | 11},
  {40, 0x00 | 0, 0, 0, 0x80 | 11},
  {41, 0x00 | 0, 0, 0, 0x80 | 10},
  {42, 0x00 | 0, 0, 0, 0x00 | 1},
  {43, 0x00 | 0, 0, 0, 0xC0 | 4},
  {44, 0x00 | 0, 0, 0, 0xC0 | 3},
  {45, 0x00 | 0, 0, 0, 0xC0 | 3},
  {46, 0x00 | 0, 0, 0, 0xA0 | 5},
  {47, 0x00 | 0, 0, 0, 0xA0 | 4},
  {48, 0x00 | 0, 0, 0, 0x60 | 6},
  {49, 0x00 | 0, 4, 0, 0x60 | 7},
  {50, 0x00 | 0, 3, 0, 0x60 | 6},
  {51, 0x00 | 0, 1, 0, 0x40 | 4},
  {64, 0x00 | 0, 0, 0, 0xC0 | 2},
  {65, 0x00 | 0, 0, 0, 0x40 | 1},
  {66, 0x00 | 0, 0, 0, 0x40 | 2},
  {67, 0x00 | 0, 0, 0, 0x00 | 0},
  {68, 0x00 | 0, 0, 0, 0x00 | 0},
  {69, 0x00 | 0, 0, 0, 0x80 | 0},
  {70, 0x00 | 0, 0, 0, 0x00 | 0},
  {71, 0x00 | 0, 0, 0, 0x80 | 0},
  {72, 0x00 | 0, 0, 0, 0x00 | 0},
  {73, 0x00 | 0, 0, 0, 0x80 | 0},
  {74, 0x00 | 0, 0, 0, 0x00 | 0},
  {75, 0x00 | 0, 0, 0, 0x00 | 0},
  {76, 0x00 | 0, 0, 0, 0x80 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {80, 0x00 | 0, -2, 0, 0x40 | 1},
  {81, 0x00 | 0, -2, 0, 0x40 | 1},
  {82, 0x00 | 0, -1, 0, 0xC0 | 2},
  {83, 0x00 | 0, -2, 0, 0x40 | 2},
  {84, 0x00 | 0, -2, 0, 0x40 | 1},
  {85, 0x00 | 0, -2, 0, 0x40 | 1},
  {86, 0x00 | 0, -2, 0, 0x40 | 1},
  {87, 0x00 | 0, -1, 0, 0x00 | 7},
  {88, 0x00 | 0, -1, 0, 0x00 | 5},
  {89, 0x00 | 0, 2, 0, 0x00 | 7},
  {90, 0x00 | 0, 2, 0, 0x00 | 7},
  {91, 0x00 | 0, 2, -3, 0x00 | 0},
  {92, 0x00 | 0, 2, -10, 0x00 | 0},
  {93, 0x00 | 0, 2, -11, 0x80 | 0},
  {94, 0x00 | 0, 3, -2, 0x40 | 3},
  {95, 0x00 | 0, 3, 0, 0xC0 | 3},
  {96, 0x00 | 0, 3, 0, 0xC0 | 3},
  {97, 0x00 | 0, 3, 0, 0x60 | 3},
  {98, 0x00 | 0, 4, 0, 0xE0 | 3},
  {28, 0x00 | 0, 0, 0, 0x00 | 0},
  {99, 0x00 | 0, 7, -14, 0x80 | 0},
  {100, 0x00 | 0, 7, -12, 0x80 | 0},
  {101, 0x00 | 0, 4, -12, 0x00 | 0},
  {102, 0x00 | 0, 3, -10, 0x80 | 0},
  {103, 0x00 | 0, 2, -10, 0x80 | 0},
  {104, 0x00 | 0, 1, -10, 0x80 | 0},
  {105, 0x00 | 0, 0, -11, 0x00 | 0},
  {106, 0x00 | 0, -1, -12, 0x00 | 0},
  {107, 0x00 | 0, -1, -14, 0x00 | 0},
  {108, 0x00 | 0, -1, -14, 0x00 | 0},
  {109, 0x00 | 0, -1, -15, 0x80 | 0},
  {110, 0x00 | 0, -1, -15, 0x80 | 0},
  {111, 0x00 | 0, 0, -15, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {112, 0x00 | 0, 0, 0, 0xC0 | 6},
  {113, 0x00 | 0, 0, 0, 0x40 | 6},
  {114, 0x00 | 0, 0, 0, 0xC0 | 5},
  {115, 0x00 | 0, 0, 0, 0x40 | 5},
  {116, 0x00 | 0, 0, 0, 0xC0 | 2},
  {117, 0x00 | 0, 0, 0, 0xC0 | 4},
  {118, 0x00 | 0, 0, 0, 0xC0 | 5},
  {119, 0x00 | 0, 0, 0, 0x40 | 6},
  {120, 0x00 | 0, 0, 0, 0x40 | 7},
  {121, 0x00 | 0, 0, 0, 0x40 | 7},
  {122, 0x00 | 0, 0, 0, 0x40 | 9},
  {123, 0x00 | 0, 0, 0, 0xC0 | 8},
  {124, 0x00 | 0, 0, 0, 0xC0 | 9},
  {125, 0x00 | 0, 0, 0, 0x40 | 9},
  {126, 0x00 | 0, 0, 0, 0x40 | 5},
  {127, 0x00 | 0, 2, 0, 0x40 | 5},
  {128, 0x00 | 0, 2, 0, 0xC0 | 5},
  {129, 0x00 | 0, 0, 0, 0xC0 | 3},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {133, 0x00 | 0, 0, 0, 0x40 | 3},
  {134, 0x00 | 0, 0, 0, 0xC0 | 4},
  {135, 0x00 | 0, 0, 0, 0xC0 | 5},
  {136, 0x00 | 0, 0, 0, 0x40 | 8},
  {137, 0x00 | 0, 0, 0, 0x60 | 12},
  {138, 0x00 | 0, 0, 0, 0xE0 | 15},
  {139, 0x00 | 0, 0, 0, 0x60 | 3},
  {140, 0x00 | 0, 0, 0, 0xC0 | 3},
  {141, 0x00 | 0, 0, 0, 0x40 | 3},
  {142, 0x00 | 0, 0, 0, 0x40 | 3},
  {143, 0x00 | 0, 0, 0, 0x40 | 4},
  {144, 0x00 | 0, 0, 0, 0x40 | 4},
  {172, 0x00 | 0, 0, 1, 0xC0 | 1},
  {173, 0x00 | 0, 0, 1, 0xC0 | 7},
  {145, 0x00 | 0, 0, -12, 0x00 | 1},
  {146, 0x00 | 0, 0, -21, 0x00 | 0},
  {147, 0x00 | 0, 1, -26, 0x80 | 0},
  {148, 0x00 | 0, 4, -32, 0x80 | 0},
  {149, 0x00 | 0, 6, -36, 0x80 | 1},
  {150, 0x00 | 0, 7, -41, 0x80 | 2},
  {151, 0x00 | 0, 2, 17, 0x40 | 2},
  {152, 0x00 | 0, 4, 9, 0xC0 | 4},
  {153, 0x00 | 0, 4, 5, 0xC0 | 9},
  {154, 0x00 | 0, 4, 4, 0xC0 | 8},
  {155, 0x00 | 0, 5, 0, 0x60 | 9},
  {156, 0x00 | 0, 5, 0, 0xE0 | 9},
  {157, 0x00 | 0, 5, 0, 0xE0 | 8},
  {158, 0x00 | 0, 5, 0, 0x60 | 9},
  {159, 0x00 | 0, 5, 0, 0x60 | 9},
  {184, 0x00 | 16, 0, 2, 0x80 | 0},
  {174, 0x00 | 26, 0, 2, 0x80 | 0},
  {175, 0x00 | 18, 3, 2, 0x00 | 0},
  {176, 0x00 | 22, 7, 2, 0xC0 | 4},
  {177, 0x00 | 21, 10, 2, 0x00 | 0},
  {178, 0x00 | 23, 7, 2, 0x80 | 0},
  {179, 0x00 | 25, 4, 2, 0x80 | 0},
  {180, 0x00 | 24, 0, 2, 0xC0 | 14},
  {181, 0x00 | 15, 0, 2, 0xC0 | 13},
  {182, 0x00 | 20, 3, 2, 0x00 | 0},
  {183, 0x00 | 31, 3, 2, 0x00 | 0},
  {184, 0x00 | 16, 0, 2, 0x80 | 0},
  {185, 0x00 | 17, 0, 2, 0x80 | 0},
  {186, 0x00 | 32, 0, 2, 0x00 | 0},
  {187, 0x00 | 33, 0, 2, 0x80 | 0},
  {188, 0x00 | 34, 2, 2, 0xC0 | 3},
  {14, 0x00 | 0, 0, 0, 0x40 | 3},
  {189, 0x00 | 19, 7, 2, 0x80 | 0},
  {190, 0x00 | 14, 1, 2, 0x80 | 0},
  {191, 0x00 | 27, 0, 2, 0x80 | 0},
  {181, 0x00 | 15, 0, 2, 0xC0 | 13},
  {181, 0x00 | 15, 0, 2, 0xC0 | 13},
  {112, 0x00 | 43, 0, 0, 0xC0 | 6},
  {113, 0x00 | 44, 0, 0, 0x40 | 6},
  {114, 0x00 | 45, 0, 0, 0xC0 | 5},
  {115, 0x00 | 46, 0, 0, 0x40 | 5},
  {114, 0x00 | 0, 0, 0, 0xC0 | 5},
  {78, 0x00 | 0, 0, 3, 0x80 | 10},
  {77, 0x00 | 0, 4, 3, 0x80 | 7},
  {211, 0x00 | 0, 0, 1, 0x40 | 4},
  {212, 0x00 | 0, 0, 1, 0x40 | 4},
  {213, 0x00 | 0, 0, 1, 0x40 | 4},
  {214, 0x00 | 0, 0, 1, 0x40 | 7},
  {215, 0x00 | 0, 0, 7, 0x40 | 11},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {79, 0x00 | 0, 4, 7, 0x40 | 9},
  {130, 0x00 | 0, 0, 0, 0x40 | 4},
  {131, 0x00 | 0, 0, 0, 0x40 | 4},
  {132, 0x00 | 0, 0, 2, 0x40 | 4},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {192, 0x00 | 0, 0, 0, 0x00 | 0},
  {193, 0x00 | 0, 0, 1, 0x00 | 0},
  {194, 0x00 | 0, 0, 0, 0x80 | 0},
  {195, 0x00 | 0, 0, 0, 0x00 | 0},
  {196, 0x00 | 0, -1, 0, 0x00 | 0},
  {197, 0x00 | 0, -1, 0, 0x00 | 0},
  {198, 0x00 | 0, -1, 0, 0x00 | 0},
  {199, 0x00 | 0, -4, 0, 0x00 | 0},
  {200, 0x00 | 0, -4, 0, 0x80 | 0},
  {201, 0x00 | 0, -4, 0, 0x00 | 0},
  {202, 0x00 | 0, -4, 0, 0x00 | 0},
  {203, 0x00 | 0, -4, 0, 0x00 | 0},
  {204, 0x00 | 0, -4, 0, 0x00 | 0},
  {205, 0x00 | 0, -5, 0, 0x00 | 0},
  {206, 0x00 | 0, -5, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {207, 0x00 | 0, 0, 1, 0x40 | 6},
  {208, 0x00 | 0, 0, 1, 0xC0 | 6},
  {209, 0x00 | 0, 0, 1, 0xC0 | 8},
  {210, 0x00 | 0, 0, 1, 0x40 | 10},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {52, 0x00 | 0, 0, 0, 0x80 | 0},
  {53, 0x00 | 0, 0, 0, 0x00 | 0},
  {54, 0x00 | 0, 0, 0, 0x00 | 0},
  {55, 0x00 | 0, 0, 0, 0x00 | 0},
  {56, 0x00 | 0, 0, 0, 0x80 | 0},
  {57, 0x00 | 0, 0, 0, 0x00 | 0},
  {58, 0x00 | 0, 0, 0, 0x00 | 0},
  {59, 0x00 | 0, 0, 0, 0x00 | 0},
  {60, 0x00 | 0, 0, 0, 0x80 | 0},
  {61, 0x00 | 0, 0, 0, 0x00 | 0},
  {62, 0x00 | 0, 0, 0, 0x80 | 0},
  {63, 0x00 | 0, 0, 0, 0x00 | 0},
  {160, 0x00 | 35, 1, 1, 0xC0 | 3},
  {161, 0x00 | 36, 0, 1, 0x40 | 9},
  {162, 0x00 | 37, 0, 1, 0xC0 | 3},
  {163, 0x00 | 38, 0, 1, 0x40 | 9},
  {164, 0x00 | 39, 0, 1, 0xC0 | 3},
  {165, 0x00 | 40, 1, 1, 0x40 | 9},
  {166, 0x00 | 41, 1, 1, 0x40 | 3},
  {167, 0x00 | 42, 1, 1, 0xC0 | 9},
  {168, 0x00 | 0, 4, 1, 0xC0 | 6},
  {169, 0x00 | 0, 3, 1, 0xC0 | 10},
  {170, 0x00 | 0, 1, 1, 0x40 | 3},
  {171, 0x00 | 0, 1, 1, 0xC0 | 8},
};

// data:1496
static const frame_type frame_tbl_guard[] = {
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {12, 0xC0 | 13, 2, 1, 0x00 | 0},
  {2, 0xC0 | 1, 3, 1, 0x00 | 0},
  {3, 0xC0 | 2, 4, 1, 0x00 | 0},
  {4, 0xC0 | 3, 7, 1, 0x40 | 4},
  {5, 0xC0 | 4, 10, 1, 0x00 | 0},
  {6, 0xC0 | 5, 7, 1, 0x80 | 0},
  {7, 0xC0 | 6, 4, 1, 0x80 | 0},
  {8, 0xC0 | 7, 0, 1, 0x80 | 0},
  {9, 0xC0 | 8, 0, 1, 0xC0 | 13},
  {10, 0xC0 | 11, 7, 1, 0x80 | 0},
  {11, 0xC0 | 12, 3, 1, 0x00 | 0},
  {12, 0xC0 | 13, 2, 1, 0x00 | 0},
  {13, 0xC0 | 0, 2, 1, 0x00 | 0},
  {14, 0xC0 | 28, 0, 1, 0x00 | 0},
  {15, 0xC0 | 29, 0, 1, 0x80 | 0},
  {16, 0xC0 | 30, 2, 1, 0xC0 | 3},
  {17, 0xC0 | 9, -1, 1, 0x40 | 8},
  {18, 0xC0 | 10, 7, 1, 0x80 | 0},
  {19, 0xC0 | 14, 3, 1, 0x80 | 0},
  {9, 0xC0 | 8, 0, 1, 0x80 | 0},
  {20, 0xC0 | 8, 0, 1, 0xC0 | 13},
  {21, 0xC0 | 8, 0, 1, 0xC0 | 13},
  {22, 0xC0 | 47, 0, 0, 0xC0 | 6},
  {23, 0xC0 | 48, 0, 0, 0x40 | 6},
  {24, 0xC0 | 49, 0, 0, 0xC0 | 5},
  {24, 0xC0 | 49, 0, 0, 0xC0 | 5},
  {24, 0xC0 | 49, 0, 0, 0xC0 | 5},
  {26, 0xC0 | 0, 0, 3, 0x80 | 10},
  {27, 0xC0 | 0, 4, 4, 0x80 | 7},
  {28, 0xC0 | 0, -2, 1, 0x40 | 4},
  {29, 0xC0 | 0, -2, 1, 0x40 | 4},
  {30, 0xC0 | 0, -2, 1, 0x40 | 4},
  {31, 0xC0 | 0, -2, 2, 0x40 | 7},
  {32, 0xC0 | 0, -2, 2, 0x40 | 10},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {33, 0xC0 | 0, 3, 4, 0xC0 | 9},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
};

// data:1564
static const frame_type frame_tbl_cuts[] = {
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {15, 0x40 | 0, 0, 0, 0x00 | 0},
  {1, 0x40 | 0, 0, 0, 0x80 | 0},
  {2, 0x40 | 0, 0, 0, 0x80 | 0},
  {3, 0x40 | 0, 0, 0, 0x80 | 0},
  {4, 0x40 | 0, -1, 0, 0x00 | 0},
  {5, 0x40 | 0, 2, 0, 0x80 | 0},
  {6, 0x40 | 0, 2, 0, 0x00 | 0},
  {7, 0x40 | 0, 0, 0, 0x80 | 0},
  {8, 0x40 | 0, 1, 0, 0x80 | 0},
  {255, 0x00 | 0, 0, 0, 0x00 | 0},
  {0, 0x40 | 0, 0, 0, 0x80 | 0},
  {9, 0x40 | 0, 0, 0, 0x80 | 0},
  {10, 0x40 | 0, 0, 0, 0x00 | 0},
  {11, 0x40 | 0, 0, 0, 0x80 | 0},
  {12, 0x40 | 0, 0, 0, 0x80 | 0},
  {13, 0x40 | 0, 0, 0, 0x80 | 0},
  {14, 0x40 | 0, 0, 0, 0x00 | 0},
  {16, 0x40 | 0, 0, 0, 0x00 | 0},
  {0, 0x80 | 0, 0, 0, 0x00 | 0},
  {2, 0x80 | 0, 0, 0, 0x00 | 0},
  {3, 0x80 | 0, 0, 0, 0x00 | 0},
  {4, 0x80 | 0, 0, 0, 0x80 | 0},
  {5, 0x80 | 0, 0, 0, 0x00 | 0},
  {6, 0x80 | 0, 0, 0, 0x80 | 0},
  {7, 0x80 | 0, 0, 0, 0x80 | 0},
  {8, 0x80 | 0, 0, 0, 0x00 | 0},
  {9, 0x80 | 0, 0, 0, 0x00 | 0},
  {10, 0x80 | 0, 0, 0, 0x00 | 0},
  {11, 0x80 | 0, 0, 0, 0x00 | 0},
  {12, 0x80 | 0, 0, 0, 0x00 | 0},
  {13, 0x80 | 0, 0, 0, 0x00 | 0},
  {14, 0x80 | 0, 0, 0, 0x00 | 0},
  {15, 0x80 | 0, 0, 0, 0x00 | 0},
  {16, 0x80 | 0, 0, 0, 0x00 | 0},
  {17, 0x80 | 0, 0, 0, 0x00 | 0},
  {18, 0x80 | 0, 0, 0, 0x00 | 0},
  {19, 0x80 | 0, 0, 0, 0x00 | 0},
  {20, 0x80 | 0, 0, 0, 0x80 | 0},
  {21, 0x80 | 0, 0, 0, 0x80 | 0},
  {22, 0x80 | 0, 1, 0, 0x00 | 0},
  {23, 0x80 | 0, -1, 0, 0x00 | 0},
  {24, 0x80 | 0, 2, 0, 0x00 | 0},
  {25, 0x80 | 0, 1, 0, 0x80 | 0},
  {26, 0x80 | 0, 0, 0, 0x80 | 0},
  {27, 0x80 | 0, 0, 0, 0x80 | 0},
  {28, 0x80 | 0, 0, 0, 0x80 | 0},
  {29, 0x80 | 0, -1, 0, 0x00 | 0},
  {0, 0x80 | 0, 0, 0, 0x80 | 0},
  {1, 0x80 | 0, 0, 0, 0x80 | 0},
  {2, 0x80 | 0, 0, 0, 0x80 | 0},
  {3, 0x80 | 0, 0, 0, 0x00 | 0},
  {4, 0x80 | 0, 0, 0, 0x00 | 0},
  {5, 0x80 | 0, 0, 0, 0x80 | 0},
  {6, 0x80 | 0, 0, 0, 0x80 | 0},
  {7, 0x80 | 0, 0, 0, 0x80 | 0},
  {8, 0x80 | 0, 0, 0, 0x80 | 0},
  {9, 0x80 | 0, 0, 0, 0x80 | 0},
  {10, 0x80 | 0, 0, 0, 0x80 | 0},
  {11, 0x80 | 0, 0, 0, 0x80 | 0},
  {12, 0x80 | 0, 0, 0, 0x80 | 0},
  {13, 0x80 | 0, 0, 0, 0x00 | 0},
  {14, 0x80 | 0, 0, 0, 0x80 | 0},
  {15, 0x80 | 0, 0, 0, 0x00 | 0},
  {16, 0x80 | 0, 0, 0, 0x00 | 0},
  {17, 0x80 | 0, 0, 0, 0x80 | 0},
  {18, 0x80 | 0, 0, 0, 0x00 | 0},
  {19, 0x80 | 0, 3, 0, 0x00 | 0},
  {20, 0x80 | 0, 3, 0, 0x00 | 0},
  {21, 0x80 | 0, 3, 0, 0x00 | 0},
  {22, 0x80 | 0, 2, 0, 0x00 | 0},
  {23, 0x80 | 0, 3, 0, 0x80 | 0},
  {24, 0x80 | 0, 5, 0, 0x00 | 0},
  {25, 0x80 | 0, 5, 0, 0x00 | 0},
  {26, 0x80 | 0, 1, 0, 0x80 | 0},
  {27, 0x80 | 0, 2, 0, 0x80 | 0},
  {28, 0x80 | 0, 2, 0, 0x80 | 0},
  {29, 0x80 | 0, 1, 0, 0x80 | 0},
  {30, 0x80 | 0, 1, 0, 0x00 | 0},
  {31, 0x80 | 0, 2, 0, 0x00 | 0},
  {32, 0x80 | 0, 3, 0, 0x00 | 0},
  {33, 0x80 | 0, 3, 0, 0x00 | 0},
  {34, 0x80 | 0, 0, 0, 0x80 | 0},
  {35, 0x80 | 0, 2, 0, 0x80 | 0},
  {36, 0x80 | 0, 2, 0, 0x80 | 0},
  {37, 0x80 | 0, 1, 0, 0x00 | 0},
};

static const rect_type screen_rect = {0, 0, 200, 320};
// 1.0//static const char copyprot_letter[] = {'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'F', 'F', 'G', 'H', 'H', 'I', 'I', 'J', 'J', 'K', 'L', 'L', 'M', 'M', 'N', 'O', 'O', 'P', 'P', 'R', 'R', 'S', 'S', 'T', 'T', 'U', 'U', 'V', 'Y', 'W', 'Y'};
static const char copyprot_letter[] = {'W', 'O', 'E', 'S', 'P', 'B', 'Y', 'S', 'K', 'J', 'T', 'B', 'C', 'F', 'E', 'S', 'K', 'M', 'M', 'T', 'P', 'Y', 'K', 'C', 'G', 'S', 'U', 'L', 'J', 'C', 'D', 'I', 'L', 'T', 'T', 'A', 'M', 'C', 'S', 'G'};
static const uint16_t tbl_line[] = {0, 10, 20};
static const uint8_t chtab_flip_clip[10] = {1, 0, 1, 1, 1, 1, 0, 0, 0, 0};
static const uint8_t chtab_shift[10] = {0, 1, 0, 0, 0, 0, 1, 1, 1, 0};
static const rect_type rect_top = {0, 0, 192, 320};
static const rect_type rect_bottom_text = {193, 70, 202, 250};
static const int16_t y_land[] = {-8, 55, 118, 181, 244};
static const uint16_t copyprot_tile[] = {1, 5, 7, 9, 11, 21, 1, 3, 7, 11, 17, 21, 25, 27};
static const uint8_t x_bump[] = {244, 2, 16, 30, 44, 58, 72, 86, 100, 114, 128, 142, 156, 170, 184, 198, 212, 226, 240, 254}; // 244 = -12
static const int16_t y_clip[] = {-60, 3, 66, 129, 192};
static const int8_t dir_front[] = {-1, 1};
static const int8_t dir_behind[] = {1, -1};

static custom_options_type custom_defaults = {
  .start_minutes_left = 60,
  .start_ticks_left = 719,
  .start_hitp = 3,
  .max_hitp_allowed = 10,
  .saving_allowed_first_level = 3,
  .saving_allowed_last_level = 13,
  .start_upside_down = 0,
  .start_in_blind_mode = 0,
  // data:009E
  .copyprot_level = 2,
  .drawn_tile_top_level_edge = tiles_1_floor,
  .drawn_tile_left_level_edge = tiles_20_wall,
  .level_edge_hit_tile = tiles_20_wall,
  .allow_triggering_any_tile = 0,
  .enable_wda_in_palace = 0,
  .first_level = 1,
  .skip_title = 0,
  .shift_L_allowed_until_level = 4,
  .shift_L_reduced_minutes = 15,
  .shift_L_reduced_ticks = 719,
  .demo_hitp = 4,
  .demo_end_room = 24,
  .intro_music_level = 1,
  .intro_music_time_initial = 33,
  .intro_music_time_restart = 4,
  .have_sword_from_level = 2,
  .checkpoint_level = 3,
  .checkpoint_respawn_dir = dir_FF_left,
  .checkpoint_respawn_room = 2,
  .checkpoint_respawn_tilepos = 6,
  .checkpoint_clear_tile_room = 7,
  .checkpoint_clear_tile_col = 4,
  .checkpoint_clear_tile_row = 0,
  .skeleton_level = 3,
  .skeleton_room = 1,
  .skeleton_trigger_column_1 = 2,
  .skeleton_trigger_column_2 = 3,
  .skeleton_column = 5,
  .skeleton_row = 1,
  .skeleton_require_open_level_door = 1,
  .skeleton_skill = 2,
  .skeleton_reappear_room = 3,
  .skeleton_reappear_x = 133,
  .skeleton_reappear_row = 1,
  .skeleton_reappear_dir = dir_0_right,
  .mirror_level = 4,
  .mirror_room = 4,
  .mirror_column = 4,
  .mirror_row = 0,
  .mirror_tile = tiles_13_mirror,
  .show_mirror_image = 1,
  .falling_exit_level = 6,
  .falling_exit_room = 1,
  .falling_entry_level = 7,
  .falling_entry_room = 17,
  .mouse_level = 8,
  .mouse_room = 16,
  .mouse_delay = 150,
  .mouse_object = 24,
  .mouse_start_x = 200,
  .loose_tiles_level = 13,
  .loose_tiles_room_1 = 23,
  .loose_tiles_room_2 = 16,
  .loose_tiles_first_tile = 22,
  .loose_tiles_last_tile = 27,
  .jaffar_victory_level = 13,
  .jaffar_victory_flash_time = 18,
  .hide_level_number_from_level = 14,
  .level_13_level_number = 12,
  .victory_stops_time_level = 13,
  .win_level = 14,
  .win_room = 5,
  .loose_floor_delay = 11,
  // data:02B2
  .tbl_level_type = {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0},
  // 1.3
  .tbl_level_color = {0, 0, 0, 1, 0, 0, 0, 1, 2, 2, 0, 0, 3, 3, 4, 0},
  // data:03D4
  .tbl_guard_type = {0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 4, 3, -1, -1},
  // data:0EDA
  .tbl_guard_hp = {4, 3, 3, 3, 3, 4, 5, 4, 4, 5, 5, 5, 4, 6, 0, 0},
  .tbl_cutscenes_by_index = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
  .tbl_entry_pose = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
  .tbl_seamless_exit = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, -1, -1, -1},

  // guard skills 1.0
  .strikeprob10 =    { 61, 100, 61, 61, 61, 40, 100, 220, 0, 48, 32, 48},
  .restrikeprob10 =  { 0, 0, 0, 5, 5, 175, 16, 8, 0, 255, 255, 150},
  .blockprob10 =     { 0, 150, 150, 200, 200, 255, 200, 250, 0, 255, 255, 255},
  .impblockprob10 =  { 0, 61, 61, 100, 100, 145, 100, 250, 0, 145, 255, 175},
  .advprob10 =       { 255, 200, 200, 200, 255, 255, 200, 0, 0, 255, 100, 100},
  .refractimer10 =   { 16, 16, 16, 16, 8, 8, 8, 8, 0, 8, 0, 0},
  .extrastrength10 = { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},

  // guard skills 1.4
  .strikeprob14 = {75, 100, 75, 75, 75, 50, 100, 220, 0, 60, 40, 60},
  .restrikeprob14 = {0, 0, 0, 5, 5, 175, 20, 10, 0, 255, 255, 150},
  .blockprob14 = {0, 150, 150, 200, 200, 255, 200, 250, 0, 255, 255, 255},
  .impblockprob14 = {0, 75, 75, 100, 100, 145, 100, 250, 0, 145, 255, 175},
  .advprob14 = {255, 200, 200, 200, 255, 255, 200, 0, 0, 255, 100, 100},
  .refractimer14 = {20, 20, 20, 20, 10, 10, 10, 10, 0, 10, 0, 0},
  .extrastrength14 = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},

  // shadow's starting positions
  .init_shad_6 = {0x0F, 0x51, 0x76, 0, 0, 1, 0, 0},
  .init_shad_5 = {0x0F, 0x37, 0x37, 0, 0xFF, 0, 0, 0},
  .init_shad_12 = {0x0F, 0x51, 0xE8, 0, 0, 0, 0, 0},
  // automatic moves
  .demo_moves = {{0x00, 0}, {0x01, 1}, {0x0D, 0}, {0x1E, 1}, {0x25, 5}, {0x2F, 0}, {0x30, 1}, {0x41, 0}, {0x49, 2}, {0x4B, 0}, {0x63, 2}, {0x64, 0}, {0x73, 5}, {0x80, 6}, {0x88, 3}, {0x9D, 7}, {0x9E, 0}, {0x9F, 1}, {0xAB, 4}, {0xB1, 0}, {0xB2, 1}, {0xBC, 0}, {0xC1, 1}, {0xCD, 0}, {0xE9, -1}},
  .shad_drink_move = {{0x00, 0}, {0x01, 1}, {0x0E, 0}, {0x12, 6}, {0x1D, 7}, {0x2D, 2}, {0x31, 1}, {0xFF, -2}},

  // speeds
  .base_speed = 5,
  .fight_speed = 6,
  .chomper_speed = 15,
};
char *g_argv[] = {(char *)"prince"};

} // namespace quickerSDLPoP