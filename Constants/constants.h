#pragma once
#include "./utils.h"

#define ATK "ATK"
#define ATK_PERCENT "ATK%"
#define HP "HP"
#define HP_PERCENT "HP%"
#define DEF "DEF"
#define DEF_PERCENT "DEF%"
#define ELEMENTAL_MASTERY "EM"
#define ENERGY_RECHARGE "ER%"
#define CRIT_RATE "Crit Rate%"
#define CRIT_DAMAGE "Crit Dmg%"
#define ELEMENTAL_DAMAGE_BONUS "Elemental Damage Bonus"
#define PHYSICAL_DAMAGE_BONUS "Physical Damage Bonus"

#define MAX_ATK_ROLL 19.45
#define MAX_ATK_PERCENT_ROLL 5.83
#define MAX_HP_ROLL 298.75
#define MAX_HP_PERCENT_ROLL 5.83
#define MAX_DEF_ROLL 23.15
#define MAX_DEF_PERCENT_ROLL 7.29
#define MAX_EM_ROLL 23.31
#define MAX_ER_PERCENT_ROLL 6.48
#define MAX_CRIT_RATE_ROLL 3.87
#define MAX_CRIT_DAMAGE_ROLL 7.77

#define MAX_ATK_MAIN 311
#define MAX_ATK_PERCENT_MAIN 46.6
#define MAX_HP_MAIN 4780
#define MAX_HP_PERCENT_MAIN 46.6
#define MAX_DEF_MAIN 0
#define MAX_DEF_PERCENT_MAIN 58.3
#define MAX_EM_MAIN 187
#define MAX_ER_PERCENT_MAIN 51.8
#define MAX_CRIT_RATE_MAIN 35.9
#define MAX_CRIT_DAMAGE_MAIN 62.2
#define MAX_ELEMENTAL_DAMAGE_BONUS_MAIN 46.6
#define MAX_PHYSICAL_DAMAGE_BONUS_MAIN 58.3

#define FLOWER "Flower"
#define FEATHER "Feather"
#define SANDS "Sands"
#define GOBLET "Goblet"
#define CIRCLET "Circlet"

#define FLOWER_MAIN_STATS \
  { HP }
#define FEATHER_MAIN_STATS \
  { ATK }
#define SANDS_MAIN_STATS \
  { ATK_PERCENT, HP_PERCENT, DEF_PERCENT, ELEMENTAL_MASTERY, ENERGY_RECHARGE }
#define GOBLET_MAIN_STATS \
  { ATK_PERCENT, HP_PERCENT, DEF_PERCENT, ELEMENTAL_MASTERY, ELEMENTAL_DAMAGE_BONUS, PHYSICAL_DAMAGE_BONUS }
#define CIRCLET_MAIN_STATS \
  { ATK_PERCENT, HP_PERCENT, DEF_PERCENT, ELEMENTAL_MASTERY, CRIT_RATE, CRIT_DAMAGE }

#define FLOWER_SUBSTATS \
  { HP }
#define FEATHER_SUBSTATS \
  { ATK }
#define SANDS_SUBSTATS \
  { ATK_PERCENT, HP_PERCENT, DEF_PERCENT, ELEMENTAL_MASTERY, ENERGY_RECHARGE }
#define GOBLET_SUBSTATS \
  { ATK_PERCENT, HP_PERCENT, DEF_PERCENT, ELEMENTAL_MASTERY, ELEMENTAL_DAMAGE_BONUS, PHYSICAL_DAMAGE_BONUS }
#define CIRCLET_SUBSTATS \
  { ATK_PERCENT, HP_PERCENT, DEF_PERCENT, ELEMENTAL_MASTERY, CRIT_RATE, CRIT_DAMAGE }

namespace Constants {

std::vector<std::string> possible_substats_ = {
    ATK,
    ATK_PERCENT,
    HP,
    HP_PERCENT,
    DEF,
    DEF_PERCENT,
    ELEMENTAL_MASTERY,
    ENERGY_RECHARGE,
    CRIT_RATE,
    CRIT_DAMAGE,
};

// retrieve max roll for a single substat
std::unordered_map<std::string, double>
    substat_max_roll_mapping_ = {
        {ATK, MAX_ATK_ROLL},
        {ATK_PERCENT, MAX_ATK_PERCENT_ROLL},
        {HP, MAX_HP_ROLL},
        {HP_PERCENT, MAX_HP_PERCENT_ROLL},
        {DEF, MAX_DEF_ROLL},
        {DEF_PERCENT, MAX_DEF_PERCENT_ROLL},
        {ELEMENTAL_MASTERY, MAX_EM_ROLL},
        {ENERGY_RECHARGE, MAX_ER_PERCENT_ROLL},
        {CRIT_RATE, MAX_CRIT_RATE_ROLL},
        {CRIT_DAMAGE, MAX_CRIT_DAMAGE_ROLL},
};

// retrieve lv. 20 values for a single main stat
std::unordered_map<std::string, double> main_stat_max_roll_mapping_ = {
    {ATK, MAX_ATK_MAIN},
    {ATK_PERCENT, MAX_ATK_PERCENT_MAIN},
    {HP, MAX_HP_MAIN},
    {HP_PERCENT, MAX_HP_PERCENT_MAIN},
    {DEF, MAX_DEF_MAIN},
    {DEF_PERCENT, MAX_DEF_PERCENT_MAIN},
    {ELEMENTAL_MASTERY, MAX_EM_MAIN},
    {ENERGY_RECHARGE, MAX_ER_PERCENT_MAIN},
    {CRIT_RATE, MAX_CRIT_RATE_MAIN},
    {CRIT_DAMAGE, MAX_CRIT_DAMAGE_MAIN},
};

// possible main stats for artifact pieces
std::unordered_map<std::string, std::vector<std::string>> artifact_main_stats_ = {
    {FLOWER, FLOWER_MAIN_STATS},
    {FEATHER, FEATHER_MAIN_STATS},
    {SANDS, SANDS_MAIN_STATS},
    {GOBLET, GOBLET_MAIN_STATS},
    {CIRCLET, CIRCLET_MAIN_STATS},
};

};  // namespace Constants
