/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TRINITYCORE_QUEST_H
#define TRINITYCORE_QUEST_H

#include "Define.h"
#include "SharedDefines.h"
#include "WorldPacket.h"
#include "DBCEnums.h"
#include "EnumFlag.h"

#include <string>
#include <vector>

class Player;

class ObjectMgr;

#define MAX_QUEST_LOG_SIZE 25

#define QUEST_OBJECTIVES_COUNT 4
#define QUEST_ITEM_DROP_COUNT 4
#define QUEST_REWARD_CHOICES_COUNT 6
#define QUEST_REWARD_ITEM_COUNT 4
#define QUEST_DEPLINK_COUNT 10
#define QUEST_REWARD_REPUTATIONS_COUNT 5
#define QUEST_EMOTE_COUNT 4
#define QUEST_REWARD_CURRENCY_COUNT 4
#define QUEST_SOURCE_ITEM_COUNT 1

enum QuestFailedReason : uint32
{
    QUEST_ERR_NONE                        = 0,
    QUEST_ERR_FAILED_LOW_LEVEL            = 1,        // DESCRIPTION "You are not high enough level for that quest."
    QUEST_ERR_FAILED_WRONG_RACE           = 6,        // DESCRIPTION "That quest is not available to your race."
    QUEST_ERR_ALREADY_DONE                = 7,        // DESCRIPTION "You have completed that quest."
    QUEST_ERR_ONLY_ONE_TIMED              = 12,       // DESCRIPTION "You can only be on one timed quest at a time."
    QUEST_ERR_ALREADY_ON1                 = 13,       // DESCRIPTION "You are already on that quest."
    QUEST_ERR_FAILED_EXPANSION            = 16,       // DESCRIPTION "This quest requires an expansion enabled account."
    QUEST_ERR_ALREADY_ON2                 = 18,       // DESCRIPTION "You are already on that quest."
    QUEST_ERR_FAILED_MISSING_ITEMS        = 21,       // DESCRIPTION "You don't have the required items with you. Check storage."
    QUEST_ERR_FAILED_NOT_ENOUGH_MONEY     = 23,       // DESCRIPTION "You don't have enough money for that quest."
    QUEST_ERR_DAILY_QUESTS_REMAINING      = 26,       // DESCRIPTION "You have already completed 25 daily quests today."
    QUEST_ERR_FAILED_CAIS                 = 27,       // DESCRIPTION "You cannot complete quests once you have reached tired time."
    QUEST_ERR_ALREADY_DONE_DAILY          = 29        // DESCRIPTION "You have completed that daily quest today."
};

enum QuestShareMessages : uint8
{
    QUEST_PARTY_MSG_SHARING_QUEST           = 0,
    QUEST_PARTY_MSG_CANT_TAKE_QUEST         = 1,
    QUEST_PARTY_MSG_ACCEPT_QUEST            = 2,
    QUEST_PARTY_MSG_DECLINE_QUEST           = 3,
    QUEST_PARTY_MSG_BUSY                    = 4,
    QUEST_PARTY_MSG_LOG_FULL                = 5,
    QUEST_PARTY_MSG_HAVE_QUEST              = 6,
    QUEST_PARTY_MSG_FINISH_QUEST            = 7,
    QUEST_PARTY_MSG_CANT_BE_SHARED_TODAY    = 8,
    QUEST_PARTY_MSG_SHARING_TIMER_EXPIRED   = 9,
    QUEST_PARTY_MSG_NOT_IN_PARTY            = 10,
    QUEST_PARTY_MSG_NOT_ELIGIBLE_TODAY      = 11
};

enum QuestTradeSkill
{
    QUEST_TRSKILL_NONE           = 0,
    QUEST_TRSKILL_ALCHEMY        = 1,
    QUEST_TRSKILL_BLACKSMITHING  = 2,
    QUEST_TRSKILL_COOKING        = 3,
    QUEST_TRSKILL_ENCHANTING     = 4,
    QUEST_TRSKILL_ENGINEERING    = 5,
    QUEST_TRSKILL_FIRSTAID       = 6,
    QUEST_TRSKILL_HERBALISM      = 7,
    QUEST_TRSKILL_LEATHERWORKING = 8,
    QUEST_TRSKILL_POISONS        = 9,
    QUEST_TRSKILL_TAILORING      = 10,
    QUEST_TRSKILL_MINING         = 11,
    QUEST_TRSKILL_FISHING        = 12,
    QUEST_TRSKILL_SKINNING       = 13,
    QUEST_TRSKILL_JEWELCRAFTING  = 14
};

enum QuestStatus : uint8
{
    QUEST_STATUS_NONE           = 0,
    QUEST_STATUS_COMPLETE       = 1,
    //QUEST_STATUS_UNAVAILABLE    = 2,
    QUEST_STATUS_INCOMPLETE     = 3,
    //QUEST_STATUS_AVAILABLE      = 4,
    QUEST_STATUS_FAILED         = 5,
    QUEST_STATUS_REWARDED       = 6,        // Not used in DB
    MAX_QUEST_STATUS
};

enum class QuestGiverStatus : uint32
{
    None                         = 0x0000,
    Future                       = 0x0002,
    Trivial                      = 0x0004,
    TrivialRepeatableTurnin      = 0x0008,
    TrivialDailyQuest            = 0x0010,
    Incomplete                   = 0x0020,
    RepeatableTurnin             = 0x0040,
    DailyQuest                   = 0x0080,
    Quest                        = 0x0100,
    RewardCompleteNoPOI          = 0x0200,
    RewardCompletePOI            = 0x0400,
    LegendaryQuest               = 0x0800,
    LegendaryRewardCompleteNoPOI = 0x1000,
    LegendaryRewardCompletePOI   = 0x2000
};

DEFINE_ENUM_FLAG(QuestGiverStatus);

enum QuestFlags : uint32
{
    QUEST_FLAGS_NONE                        = 0x00000000,
    QUEST_FLAGS_COMPLETION_NO_DEATH         = 0x00000001,   // Not used currently
    QUEST_FLAGS_PARTY_ACCEPT                = 0x00000002,   // Not used currently. If player in party, all players that can accept this quest will receive confirmation box to accept quest CMSG_QUEST_CONFIRM_ACCEPT/SMSG_QUEST_CONFIRM_ACCEPT
    QUEST_FLAGS_COMPLETION_AREA_TRIGGER     = 0x00000004,   // Not used currently
    QUEST_FLAGS_SHARABLE                    = 0x00000008,   // Can be shared: Player::CanShareQuest()
    QUEST_FLAGS_HAS_CONDITION               = 0x00000010,   // Not used currently
    QUEST_FLAGS_HIDE_REWARD_POI             = 0x00000020,   // Not used currently: Unsure of content
    QUEST_FLAGS_RAID_GROUP_OK               = 0x00000040,   // Can be completed while in raid
    QUEST_FLAGS_EXPANSION_ONLY              = 0x00000080,   // Not used currently: Available if TBC expansion enabled only
    QUEST_FLAGS_NO_MONEY_FOR_XP             = 0x00000100,   // Not used currently: Experience is not converted to gold at max level
    QUEST_FLAGS_HIDE_REWARD                 = 0x00000200,   // Items and money rewarded only sent in SMSG_QUESTGIVER_OFFER_REWARD (not in SMSG_QUESTGIVER_QUEST_DETAILS or in client quest log(SMSG_QUEST_QUERY_RESPONSE))
    QUEST_FLAGS_TRACKING_EVENT              = 0x00000400,   // These quests are automatically rewarded on quest complete and they will never appear in quest log client side.
    QUEST_FLAGS_DEPRECATE_REPUTATION        = 0x00000800,   // Not used currently
    QUEST_FLAGS_DAILY                       = 0x00001000,   // Used to know quest is Daily one
    QUEST_FLAGS_FLAGS_PVP                   = 0x00002000,   // Having this quest in log forces PvP flag
    QUEST_FLAGS_DEPRECATED                  = 0x00004000,   // Used on quests that are not generically available
    QUEST_FLAGS_WEEKLY                      = 0x00008000,
    QUEST_FLAGS_AUTO_COMPLETE               = 0x00010000,   // auto complete
    QUEST_FLAGS_DISPLAY_ITEM_IN_TRACKER     = 0x00020000,   // Displays usable item in quest tracker
    QUEST_FLAGS_DISPLAY_COMPLETION_TEXT     = 0x00040000,   // use Objective text as Complete text
    QUEST_FLAGS_AUTO_ACCEPT                 = 0x00080000,   // The client recognizes this flag as auto-accept. However, NONE of the current quests (3.3.5a) have this flag. Maybe blizz used to use it, or will use it in the future.
    QUEST_FLAGS_AUTO_SUBMIT                 = 0x00100000,   // Quests with this flag player submit automatically by special button in player gui
    QUEST_FLAGS_AUTO_TAKE                   = 0x00200000,   // Automatically suggestion of accepting quest. Not from npc.
    QUEST_FLAGS_WELL_KNOWN                  = 0x04000000,   // Well-Known
    QUEST_FLAGS_PORTRAIT_IN_QUEST_LOG       = 0x08000000,   // Portrait from Log
    QUEST_FLAGS_SHOW_ITEM_WHEN_COMPLETED    = 0x10000000,   // Show Item When Completed
    QUEST_FLAGS_LAUNCH_GOSSIP_ACCEPT        = 0x20000000,   // Gossip on Quest Accept - Force Gossip
    QUEST_FLAGS_ITEMS_GLOW_WHEN_COMPLETE    = 0x40000000,   // Items Glow When Done
    QUEST_FLAGS_FAIL_ON_LOGOUT              = 0x80000000    // Fail on Logout
};

enum QuestFlagsEx : uint32
{
    QUEST_FLAGS_EX_NONE                             = 0x00000000,
    QUEST_FLAGS_EX_NO_ITEM_REMOVAL                  = 0x00000001,   // Keep Additional Items
    QUEST_FLAGS_EX_SUPPRESS_GOSSIP_COMPLETE         = 0x00000002,   // Gossip on Quest Completion - Suppress Gossip
    QUEST_FLAGS_EX_SUPPRESS_GOSSIP_ACCEPT           = 0x00000004,   // Gossip on Quest Accept - Suppress Gossip
    QUEST_FLAGS_EX_DENY_PLAYER_QUESTGIVER           = 0x00000008,   // Disallow Player as Questgiver (advanced)
    QUEST_FLAGS_EX_DISPLAY_CLASS_CHOICE_REWARDS     = 0x00000010,   // Choice Reward Filter - Matches Class
    QUEST_FLAGS_EX_DISPLAY_SPEC_CHOICE_REWARDS      = 0x00000020,   // Choice Reward Filter - Matches Spec
    QUEST_FLAGS_EX_REMOVE_ON_PERIODIC_RESET         = 0x00000040,   // Remove from Log on Periodic Reset
    QUEST_FLAGS_EX_ACCOUNT                          = 0x00000080,   // Account-Level Quest
    QUEST_FLAGS_EX_LEGENDARY                        = 0x00000100,   // Legendary Quest
    QUEST_FLAGS_EX_NO_GUILD_XP                      = 0x00000200,   // No Guild XP
    QUEST_FLAGS_EX_RESET_CACHE_ON_ACCEPT            = 0x00000400,   // Reset Cache on Accept (internal)
    QUEST_FLAGS_EX_NO_ABANDON_ONCE_BEGUN            = 0x00000800,   // No Abandon Once Any Objective Complete
    QUEST_FLAGS_EX_RECAST_ACCEPT_SPELL_ON_LOGIN     = 0x00001000,   // Recast accept spell on login
};

enum QuestSpecialFlags
{
    QUEST_SPECIAL_FLAGS_NONE                 = 0x000,
    // Trinity flags for set SpecialFlags in DB if required but used only at server
    QUEST_SPECIAL_FLAGS_REPEATABLE           = 0x001,   // Set by 1 in SpecialFlags from DB
    QUEST_SPECIAL_FLAGS_EXPLORATION_OR_EVENT = 0x002,   // Set by 2 in SpecialFlags from DB (if required area explore, spell SPELL_EFFECT_QUEST_COMPLETE casting, table `FECT_QUEST_COMPLETE casting, table `*_script` command SCRIPT_COMMAND_QUEST_EXPLORED use, set from script)
    QUEST_SPECIAL_FLAGS_AUTO_ACCEPT          = 0x004,   // Set by 4 in SpecialFlags in DB if the quest is to be auto-accepted.
    QUEST_SPECIAL_FLAGS_DF_QUEST             = 0x008,   // Set by 8 in SpecialFlags in DB if the quest is used by Dungeon Finder.
    QUEST_SPECIAL_FLAGS_MONTHLY              = 0x010,   // Set by 16 in SpecialFlags in DB if the quest is reset at the begining of the month
    QUEST_SPECIAL_FLAGS_CAST                 = 0x020,   // Set by 32 in SpecialFlags in DB if the quest requires RequiredOrNpcGo killcredit but NOT kill (a spell cast)
    // room for more custom flags

    // i-core-specific flags, going from the opposite direction
    QUEST_SPECIAL_FLAGS_project_DAILY_QUEST = 0x01000000,   // Set by 16777216 in SpecialFlags in DB for some very specific quests
    QUEST_SPECIAL_FLAGS_NO_REPUTATION_RATE   = 0x02000000,   // Set by 33554432 in SpecialFlags in DB if the quest reward should disregard server reputation gain rates

    QUEST_SPECIAL_FLAGS_DB_ALLOWED = QUEST_SPECIAL_FLAGS_REPEATABLE | QUEST_SPECIAL_FLAGS_EXPLORATION_OR_EVENT | QUEST_SPECIAL_FLAGS_AUTO_ACCEPT | QUEST_SPECIAL_FLAGS_DF_QUEST | QUEST_SPECIAL_FLAGS_MONTHLY | QUEST_SPECIAL_FLAGS_CAST | QUEST_SPECIAL_FLAGS_project_DAILY_QUEST | QUEST_SPECIAL_FLAGS_NO_REPUTATION_RATE,

    //QUEST_SPECIAL_FLAGS_DELIVER              = 0x080,   // Internal flag computed only
    //QUEST_SPECIAL_FLAGS_SPEAKTO              = 0x100,   // Internal flag computed only
    //QUEST_SPECIAL_FLAGS_KILL                 = 0x200,   // Internal flag computed only
    QUEST_SPECIAL_FLAGS_TIMED                = 0x400,   // Internal flag computed only
    //QUEST_SPECIAL_FLAGS_PLAYER_KILL          = 0x800    // Internal flag computed only
};

enum QuestObjectiveType
{
    QUEST_OBJECTIVE_MONSTER                = 0,
    QUEST_OBJECTIVE_ITEM                   = 1,
    QUEST_OBJECTIVE_GAMEOBJECT             = 2,
    QUEST_OBJECTIVE_TALKTO                 = 3,
    QUEST_OBJECTIVE_CURRENCY               = 4,
    QUEST_OBJECTIVE_LEARNSPELL             = 5,
    QUEST_OBJECTIVE_MIN_REPUTATION         = 6,
    QUEST_OBJECTIVE_MAX_REPUTATION         = 7,
    QUEST_OBJECTIVE_MONEY                  = 8,
    QUEST_OBJECTIVE_PLAYERKILLS            = 9,
    QUEST_OBJECTIVE_AREATRIGGER            = 10,
    QUEST_OBJECTIVE_WINPETBATTLEAGAINSTNPC = 11,
    QUEST_OBJECTIVE_DEFEATBATTLEPET        = 12,
    QUEST_OBJECTIVE_WINPVPPETBATTLES       = 13,

    MAX_QUEST_OBJECTIVE_TYPE
};

struct QuestGreeting
{
    uint16 EmoteType;
    uint32 EmoteDelay;
    std::string Text;

    QuestGreeting() : EmoteType(0), EmoteDelay(0) { }
    QuestGreeting(uint16 emoteType, uint32 emoteDelay, std::string text)
        : EmoteType(emoteType), EmoteDelay(emoteDelay), Text(std::move(text)) { }
};

struct QuestGreetingLocale
{
    std::vector<std::string> Greeting;
};

struct QuestTemplateLocale
{
    std::vector<std::string> LogTitle;
    std::vector<std::string> LogDescription;
    std::vector<std::string> QuestDescription;
    std::vector<std::string> AreaDescription;
    std::vector<std::string> PortraitGiverText;
    std::vector<std::string> PortraitGiverName;
    std::vector<std::string> PortraitTurnInText;
    std::vector<std::string> PortraitTurnInName;
    std::vector<std::string> QuestCompletionLog;
};

struct QuestRequestItemsLocale
{
    std::vector<std::string> CompletionText;
};

struct QuestObjectivesLocale
{
    std::vector<std::string> Description;
};

struct QuestOfferRewardLocale
{
    std::vector<std::string> RewardText;
};

struct QuestObjective
{
    QuestObjective(uint32 id, uint32 questID, uint8 type, int8 storageIndex, uint32 objectId, int32 amount, uint32 flags, std::string description)
        : ID(id), QuestID(questID), Type(type), StorageIndex(storageIndex), ObjectID(objectId), Amount(amount), Flags(flags), Description(description) { }

    uint32 ID;
    uint32 QuestID;
    uint8 Type;
    int8 StorageIndex;
    uint32 ObjectID;
    int32 Amount;
    uint32 Flags;
    std::string Description;
    std::vector<uint32> VisualEffects;
};

using QuestObjectives = std::vector<QuestObjective>;

// This Quest class provides a convenient way to access a few pretotaled (cached) quest details,
// all base quest information, and any utility functions such as generating the amount of
// xp to give
class Quest
{
    friend class ObjectMgr;
    public:
        Quest(Field* questRecord);
        uint32 XPValue(Player* player) const;

        bool HasFlag(uint32 flag) const { return (Flags & flag) != 0; }
        void SetFlag(uint32 flag) { Flags |= flag; }
        bool HasFlag2(uint32 flag) const { return (Flags2 & flag) != 0; }
        void SetFlag2(uint32 flag) { Flags2 |= flag; }

        bool HasSpecialFlag(uint32 flag) const { return (SpecialFlags & flag) != 0; }
        void SetSpecialFlag(uint32 flag) { SpecialFlags |= flag; }
        bool HasQuestObjectiveType(QuestObjectiveType type) const { return _usedQuestObjectiveTypes[type]; }

        // table data accessors:
        uint32 GetQuestId() const { return Id; }
        uint32 GetQuestMethod() const { return Method; }
        int32  GetZoneOrSort() const { return ZoneOrSort; }
        uint32 GetMinLevel() const { return MinLevel; }
        uint32 GetMaxLevel() const { return MaxLevel; }
        int32  GetQuestLevel() const { return Level; }
        uint32 GetType() const { return Type; }
        uint32 GetRequiredClasses() const { return RequiredClasses; }
        uint32 GetRequiredRaces() const { return RequiredRaces; }
        uint32 GetRequiredSkill() const { return RequiredSkillId; }
        uint32 GetRequiredSkillValue() const { return RequiredSkillPoints; }
        uint32 GetRequiredMinRepFaction() const { return RequiredMinRepFaction; }
        int32  GetRequiredMinRepValue() const { return RequiredMinRepValue; }
        uint32 GetRequiredMaxRepFaction() const { return RequiredMaxRepFaction; }
        int32  GetRequiredMaxRepValue() const { return RequiredMaxRepValue; }
        uint32 GetSuggestedPlayers() const { return SuggestedPlayers; }
        uint32 GetLimitTime() const { return LimitTime; }
        int32  GetPrevQuestId() const { return PrevQuestId; }
        int32  GetNextQuestId() const { return NextQuestId; }
        int32  GetExclusiveGroup() const { return ExclusiveGroup; }
        uint32 GetNextQuestInChain() const { return NextQuestIdChain; }
        uint32 GetCharTitleId() const { return RewardTitleId; }
        uint32 GetBonusTalents() const { return RewardTalents; }
        int32  GetRewArenaPoints() const {return RewardArenaPoints; }
        uint32 GetXPId() const { return RewardXPId; }
        uint32 GetSrcItemId() const { return SourceItemId; }
        uint32 GetSrcSpell() const { return SourceSpellid; }
        std::string const& GetTitle() const { return Title; }
        std::string const& GetDetails() const { return Details; }
        std::string const& GetObjectives() const { return Objectives; }
        std::string const& GetOfferRewardText() const { return OfferRewardText; }
        std::string const& GetRequestItemsText() const { return RequestItemsText; }
        std::string const& GetEndText() const { return EndText; }
        std::string const& GetCompletedText() const { return CompletedText; }
        std::string const& GetQuestGiverTextWindow() const { return QuestGiverTextWindow; }
        std::string const& GetQuestGiverTargetName() const { return QuestGiverTargetName; }
        std::string const& GetQuestTurnTextWindow() const { return QuestTurnTextWindow; }
        std::string const& GetQuestTurnTargetName() const { return QuestTurnTargetName; }
        int32  GetRewardOrRequiredMoney() const;
        uint32 GetRewHonorAddition() const { return RewardHonor; }
        float GetRewHonorMultiplier() const { return RewardHonorMultiplier; }
        uint32 GetRewMoneyMaxLevel() const; // use in XP calculation at client
        uint32 GetRewSpell() const { return RewardSpell; }
        int32  GetRewSpellCast() const { return RewardSpellCast; }
        uint32 GetRewMailTemplateId() const { return RewardMailTemplateId; }
        uint32 GetRewMailDelaySecs() const { return RewardMailDelay; }
        uint32 GetPointMapId() const { return PointMapId; }
        float  GetPointX() const { return PointX; }
        float  GetPointY() const { return PointY; }
        uint32 GetPointOpt() const { return PointOption; }
        uint32 GetSoundAccept() const { return SoundAccept; }
        uint32 GetSoundTurnIn() const { return SoundTurnIn; }
        uint32 GetIncompleteEmote() const { return EmoteOnIncomplete; }
        uint32 GetCompleteEmote() const { return EmoteOnComplete; }
        bool   IsRepeatable() const { return SpecialFlags & QUEST_SPECIAL_FLAGS_REPEATABLE; }
        bool   IsAutoAccept() const;
        bool   IsAutoComplete() const;
        uint32 GetFlags() const { return Flags; }
        uint32 GetFlags2() const { return Flags2; }
        uint32 GetSpecialFlags() const { return SpecialFlags; }
        uint32 GetMinimapTargetMark() const { return MinimapTargetMark; }
        uint32 GetRewardSkillId() const { return RewardSkillId; }
        uint32 GetRewardSkillPoints() const { return RewardSkillPoints; }
        uint32 GetRewardReputationMask() const { return RewardReputationMask; }
        uint32 GetQuestGiverPortrait() const { return QuestGiverPortrait; }
        uint32 GetQuestTurnInPortrait() const { return QuestTurnInPortrait; }
        uint32 GetRewChoiceItemCount(uint32 itemId) const;
        bool   IsDaily() const { return Flags & QUEST_FLAGS_DAILY; }
        bool   IsWeekly() const { return Flags & QUEST_FLAGS_WEEKLY; }
        bool   IsMonthly() const { return SpecialFlags & QUEST_SPECIAL_FLAGS_MONTHLY; }
        bool   IsSeasonal() const { return (ZoneOrSort == -QUEST_SORT_SEASONAL || ZoneOrSort == -QUEST_SORT_SPECIAL || ZoneOrSort == -QUEST_SORT_LUNAR_FESTIVAL || ZoneOrSort == -QUEST_SORT_MIDSUMMER || ZoneOrSort == -QUEST_SORT_BREWFEST || ZoneOrSort == -QUEST_SORT_LOVE_IS_IN_THE_AIR || ZoneOrSort == -QUEST_SORT_NOBLEGARDEN || ZoneOrSort == -QUEST_SORT_CHILDRENS_WEEK) && !IsRepeatable(); }
        bool   IsDailyOrWeekly() const { return Flags & (QUEST_FLAGS_DAILY | QUEST_FLAGS_WEEKLY); }
        bool   IsRaidQuest(Difficulty difficulty) const;
        bool   IsAllowedInRaid(Difficulty difficulty) const;
        bool   IsDFQuest() const { return SpecialFlags & QUEST_SPECIAL_FLAGS_DF_QUEST; }
        bool   IsRewChoiceItemValid(uint32 itemId) const;
        uint32 CalculateHonorGain(uint8 level) const;

        // multiple values
        uint32 RequiredSourceItemId[QUEST_ITEM_DROP_COUNT];
        uint32 RequiredSourceItemCount[QUEST_ITEM_DROP_COUNT];
        uint32 RewardChoiceItemId[QUEST_REWARD_CHOICES_COUNT];
        uint32 RewardChoiceItemCount[QUEST_REWARD_CHOICES_COUNT];
        uint32 RewardItemId[QUEST_REWARD_ITEM_COUNT];
        uint32 RewardItemIdCount[QUEST_REWARD_ITEM_COUNT];
        uint32 RewardFactionId[QUEST_REWARD_REPUTATIONS_COUNT];
        int32  RewardFactionValueId[QUEST_REWARD_REPUTATIONS_COUNT];
        int32  RewardFactionValueIdOverride[QUEST_REWARD_REPUTATIONS_COUNT];
        uint32 DetailsEmote[QUEST_EMOTE_COUNT];
        uint32 DetailsEmoteDelay[QUEST_EMOTE_COUNT];
        uint32 OfferRewardEmote[QUEST_EMOTE_COUNT];
        uint32 OfferRewardEmoteDelay[QUEST_EMOTE_COUNT];
        // 4.x
        uint32 RewardCurrencyId[QUEST_REWARD_CURRENCY_COUNT];
        uint32 RewardCurrencyCount[QUEST_REWARD_CURRENCY_COUNT];

        uint32 GetRewChoiceItemsCount() const { return _rewChoiceItemsCount; }
        uint32 GetRewItemsCount() const { return _rewItemsCount; }
        uint32 GetRewCurrencyCount() const { return _rewCurrencyCount; }
        // 5.x
        uint32 GetRewardPackageItemId() const { return RewardPackageItemId; }

        typedef std::vector<int32> PrevQuests;
        PrevQuests prevQuests;
        typedef std::vector<uint32> PrevChainQuests;
        PrevChainQuests prevChainQuests;

        // objective stuff
        QuestObjectives m_questObjectives;

        // cached data
    private:
        uint32 _rewChoiceItemsCount;
        uint32 _rewItemsCount;
        uint32 _rewCurrencyCount;

        // table data
    protected:
        uint32 Id;
        uint32 Method;
        int32  ZoneOrSort;
        uint32 MinLevel;
        uint32 MaxLevel;
        int32  Level;
        uint32 Type;
        uint32 RequiredClasses;
        uint32 RequiredRaces;
        uint32 RequiredSkillId;
        uint32 RequiredSkillPoints;
        uint32 RequiredMinRepFaction;
        int32  RequiredMinRepValue;
        uint32 RequiredMaxRepFaction;
        int32  RequiredMaxRepValue;
        uint32 SuggestedPlayers;
        uint32 LimitTime;
        uint32 Flags;
        uint32 RewardTitleId;
        uint32 RequiredPlayerKills;
        uint32 RewardTalents;
        int32  RewardArenaPoints;
        int32  PrevQuestId;
        int32  NextQuestId;
        int32  ExclusiveGroup;
        uint32 NextQuestIdChain;
        uint32 RewardXPId;
        uint32 SourceItemId;
        uint32 SourceSpellid;
        std::string Title;
        std::string Details;
        std::string Objectives;
        std::string OfferRewardText;
        std::string RequestItemsText;
        std::string EndText;
        std::string CompletedText;
        uint32 RewardHonor;
        float RewardHonorMultiplier;
        int32  RewardOrRequiredMoney;
        uint32 RewardMoneyMaxLevel;
        uint32 RewardSpell;
        int32  RewardSpellCast;
        uint32 RewardMailTemplateId;
        uint32 RewardMailDelay;
        uint32 PointMapId;
        float  PointX;
        float  PointY;
        uint32 PointOption;
        uint32 EmoteOnIncomplete;
        uint32 EmoteOnComplete;
        // new in 4.x
        uint32 MinimapTargetMark;
        uint32 RewardSkillId;
        uint32 RewardSkillPoints;
        uint32 RewardReputationMask;
        uint32 QuestGiverPortrait;
        uint32 QuestTurnInPortrait;
        std::string QuestGiverTextWindow;
        std::string QuestGiverTargetName;
        std::string QuestTurnTextWindow;
        std::string QuestTurnTargetName;
        uint32 SoundAccept;
        uint32 SoundTurnIn;
        // new in 5.x
        uint32 Flags2;
        uint32 RewardPackageItemId;

        uint32 SpecialFlags; // custom flags, not sniffed/WDB

        std::bitset<MAX_QUEST_OBJECTIVE_TYPE> _usedQuestObjectiveTypes;
};

struct QuestStatusData
{
    QuestStatusData() : Status(QUEST_STATUS_NONE), Timer(0), Explored(false) { }

    QuestStatus Status;
    uint32 Timer;
    bool Explored;
};
#endif
