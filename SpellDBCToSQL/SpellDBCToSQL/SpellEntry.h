#include "SharedDefines.h"

#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

struct ClassFamilyMask
{
    uint64 Flags;

    ClassFamilyMask() : Flags(0) {}
    explicit ClassFamilyMask(uint64 familyFlags) : Flags(familyFlags) {}

    bool Empty() const { return Flags == 0; }
    bool operator!() const { return Empty(); }
    operator void const* () const { return Empty() ? nullptr : this; } // for allow normal use in if(mask)

    bool IsFitToFamilyMask(uint64 familyFlags) const
    {
        return Flags & familyFlags;
    }

    bool IsFitToFamilyMask(ClassFamilyMask const& mask) const
    {
        return Flags & mask.Flags;
    }

    uint64 operator& (uint64 mask) const                    // possible will removed at finish convertion code use IsFitToFamilyMask
    {
        return Flags & mask;
    }

    ClassFamilyMask& operator|= (ClassFamilyMask const& mask)
    {
        Flags |= mask.Flags;
        return *this;
    }
};

struct SpellEntryWOTLK
{
    uint32    Id;                                       // 0        m_ID
    uint32    Category;                                 // 1        m_category
    uint32    Dispel;                                   // 2        m_dispelType
    uint32    Mechanic;                                 // 3        m_mechanic
    uint32    Attributes;                               // 4        m_attributes
    uint32    AttributesEx;                             // 5        m_attributesEx
    uint32    AttributesEx2;                            // 6        m_attributesExB
    uint32    AttributesEx3;                            // 7        m_attributesExC
    uint32    AttributesEx4;                            // 8        m_attributesExD
    uint32    AttributesEx5;                            // 9        m_attributesExE
    uint32    AttributesEx6;                            // 10       m_attributesExF
    uint32    AttributesEx7;                            // 11       m_attributesExG (0x20 - totems, 0x4 - paladin auras, etc...)
    uint32    Stances;                                  // 12       m_shapeshiftMask
    // uint32 unk_320_1;                                // 13       3.2.0
    uint32    StancesNot;                               // 14       m_shapeshiftExclude
    // uint32 unk_320_2;                                // 15       3.2.0
    uint32    Targets;                                  // 16       m_targets
    uint32    TargetCreatureType;                       // 17       m_targetCreatureType
    uint32    RequiresSpellFocus;                       // 18       m_requiresSpellFocus
    uint32    FacingCasterFlags;                        // 19       m_facingCasterFlags
    uint32    CasterAuraState;                          // 20       m_casterAuraState
    uint32    TargetAuraState;                          // 21       m_targetAuraState
    uint32    CasterAuraStateNot;                       // 22       m_excludeCasterAuraState
    uint32    TargetAuraStateNot;                       // 23       m_excludeTargetAuraState
    uint32    casterAuraSpell;                          // 24       m_casterAuraSpell
    uint32    targetAuraSpell;                          // 25       m_targetAuraSpell
    uint32    excludeCasterAuraSpell;                   // 26       m_excludeCasterAuraSpell
    uint32    excludeTargetAuraSpell;                   // 27       m_excludeTargetAuraSpell
    uint32    CastingTimeIndex;                         // 28       m_castingTimeIndex
    uint32    RecoveryTime;                             // 29       m_recoveryTime
    uint32    CategoryRecoveryTime;                     // 30       m_categoryRecoveryTime
    uint32    InterruptFlags;                           // 31       m_interruptFlags
    uint32    AuraInterruptFlags;                       // 32       m_auraInterruptFlags
    uint32    ChannelInterruptFlags;                    // 33       m_channelInterruptFlags
    uint32    procFlags;                                // 34       m_procTypeMask
    uint32    procChance;                               // 35       m_procChance
    uint32    procCharges;                              // 36       m_procCharges
    uint32    maxLevel;                                 // 37       m_maxLevel
    uint32    baseLevel;                                // 38       m_baseLevel
    uint32    spellLevel;                               // 39       m_spellLevel
    uint32    DurationIndex;                            // 40       m_durationIndex
    uint32    powerType;                                // 41       m_powerType
    uint32    manaCost;                                 // 42       m_manaCost
    uint32    manaCostPerlevel;                         // 43       m_manaCostPerLevel
    uint32    manaPerSecond;                            // 44       m_manaPerSecond
    uint32    manaPerSecondPerLevel;                    // 45       m_manaPerSecondPerLevel
    uint32    rangeIndex;                               // 46       m_rangeIndex
    float     speed;                                    // 47       m_speed
    // uint32    modalNextSpell;                        // 48       m_modalNextSpell not used
    uint32    StackAmount;                              // 49       m_cumulativeAura
    uint32    Totem[MAX_SPELL_TOTEMS];                  // 50-51    m_totem
    int32     Reagent[MAX_SPELL_REAGENTS];              // 52-59    m_reagent
    uint32    ReagentCount[MAX_SPELL_REAGENTS];         // 60-67    m_reagentCount
    int32     EquippedItemClass;                        // 68       m_equippedItemClass (value)
    int32     EquippedItemSubClassMask;                 // 69       m_equippedItemSubclass (mask)
    int32     EquippedItemInventoryTypeMask;            // 70       m_equippedItemInvTypes (mask)
    uint32    Effect[MAX_EFFECT_INDEX];                 // 71-73    m_effect
    int32     EffectDieSides[MAX_EFFECT_INDEX];         // 74-76    m_effectDieSides
    float     EffectRealPointsPerLevel[MAX_EFFECT_INDEX];   // 77-79    m_effectRealPointsPerLevel
    int32     EffectBasePoints[MAX_EFFECT_INDEX];       // 80-82    m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    uint32    EffectMechanic[MAX_EFFECT_INDEX];         // 83-85    m_effectMechanic
    uint32    EffectImplicitTargetA[MAX_EFFECT_INDEX];  // 86-88    m_implicitTargetA
    uint32    EffectImplicitTargetB[MAX_EFFECT_INDEX];  // 89-91    m_implicitTargetB
    uint32    EffectRadiusIndex[MAX_EFFECT_INDEX];      // 92-94    m_effectRadiusIndex - spellradius.dbc
    uint32    EffectApplyAuraName[MAX_EFFECT_INDEX];    // 95-97    m_effectAura
    uint32    EffectAmplitude[MAX_EFFECT_INDEX];        // 98-100   m_effectAuraPeriod
    float     EffectMultipleValue[MAX_EFFECT_INDEX];    // 101-103  m_effectAmplitude
    uint32    EffectChainTarget[MAX_EFFECT_INDEX];      // 104-106  m_effectChainTargets
    uint32    EffectItemType[MAX_EFFECT_INDEX];         // 107-109  m_effectItemType
    int32     EffectMiscValue[MAX_EFFECT_INDEX];        // 110-112  m_effectMiscValue
    int32     EffectMiscValueB[MAX_EFFECT_INDEX];       // 113-115  m_effectMiscValueB
    uint32    EffectTriggerSpell[MAX_EFFECT_INDEX];     // 116-118  m_effectTriggerSpell
    float     EffectPointsPerComboPoint[MAX_EFFECT_INDEX];  // 119-121  m_effectPointsPerCombo
    uint32    EffectSpellClassMask[MAX_EFFECT_INDEX][3];   // 122-130  m_effectSpellClassMaskA/B/C, effect 0/1/2
    uint32    SpellVisual[2];                           // 131-132  m_spellVisualID
    uint32    SpellIconID;                              // 133      m_spellIconID
    uint32    activeIconID;                             // 134      m_activeIconID
    uint32    spellPriority;                            // 135      m_spellPriority
    char*     SpellName[16];                            // 136-151  m_name_lang
    // uint32    SpellNameFlag;                         // 152      m_name_flag not used
    char*     Rank[16];                                 // 153-168  m_nameSubtext_lang
    // uint32    RankFlags;                             // 169      m_nameSubtext_flag not used
    // char*     Description[16];                       // 170-185  m_description_lang not used
    // uint32    DescriptionFlags;                      // 186      m_description_flag not used
    // char*     ToolTip[16];                           // 187-202  m_auraDescription_lang not used
    // uint32    ToolTipFlags;                          // 203      m_auraDescription_flag not used
    uint32    ManaCostPercentage;                       // 204      m_manaCostPct
    uint32    StartRecoveryCategory;                    // 205      m_startRecoveryCategory
    uint32    StartRecoveryTime;                        // 206      m_startRecoveryTime
    uint32    MaxTargetLevel;                           // 207      m_maxTargetLevel
    uint32    SpellFamilyName;                          // 208      m_spellClassSet
    uint32    SpellFamilyFlags[3];                      // 209-211  m_spellClassMask NOTE: size is 12 bytes!!!
    uint32    MaxAffectedTargets;                       // 212      m_maxTargets
    uint32    DmgClass;                                 // 213      m_defenseType
    uint32    PreventionType;                           // 214      m_preventionType
    // uint32    StanceBarOrder;                        // 215      m_stanceBarOrder not used
    float     DmgMultiplier[MAX_EFFECT_INDEX];          // 216-218  m_effectChainAmplitude
    // uint32    MinFactionId;                          // 219      m_minFactionID not used
    // uint32    MinReputation;                         // 220      m_minReputation not used
    // uint32    RequiredAuraVision;                    // 221      m_requiredAuraVision not used
    uint32    TotemCategory[MAX_SPELL_TOTEM_CATEGORIES];// 222-223  m_requiredTotemCategoryID
    int32     AreaGroupId;                              // 224      m_requiredAreasId
    uint32    SchoolMask;                               // 225      m_schoolMask
    uint32    runeCostID;                               // 226      m_runeCostID
    // uint32    spellMissileID;                        // 227      m_spellMissileID
    // uint32  PowerDisplayId;                          // 228      m_powerDisplayID (PowerDisplay.dbc)
    // float   effectBonusCoefficient[3];               // 229-231  m_effectBonusCoefficient
    // uint32  spellDescriptionVariableID;              // 232      m_descriptionVariablesID
    uint32  SpellDifficultyId;                          // 233      m_difficulty (SpellDifficulty.dbc)
};

struct SpellEntryTBC
{
    uint32    Id;                                       // 0        m_ID
    uint32    Category;                                 // 1        m_category
    // uint32     castUI                                // 2 not used
    uint32    Dispel;                                   // 3        m_dispelType
    uint32    Mechanic;                                 // 4        m_mechanic
    uint32    Attributes;                               // 5        m_attributes
    uint32    AttributesEx;                             // 6        m_attributesEx
    uint32    AttributesEx2;                            // 7        m_attributesExB
    uint32    AttributesEx3;                            // 8        m_attributesExC
    uint32    AttributesEx4;                            // 9        m_attributesExD
    uint32    AttributesEx5;                            // 10       m_attributesExE
    uint32    AttributesEx6;                            // 11       m_attributesExF
    uint32    Stances;                                  // 12       m_shapeshiftMask
    uint32    StancesNot;                               // 13       m_shapeshiftExclude
    uint32    Targets;                                  // 14       m_targets
    uint32    TargetCreatureType;                       // 15       m_targetCreatureType
    uint32    RequiresSpellFocus;                       // 16       m_requiresSpellFocus
    uint32    FacingCasterFlags;                        // 17       m_facingCasterFlags
    uint32    CasterAuraState;                          // 18       m_casterAuraState
    uint32    TargetAuraState;                          // 19       m_targetAuraState
    uint32    CasterAuraStateNot;                       // 20       m_excludeCasterAuraState
    uint32    TargetAuraStateNot;                       // 21       m_excludeTargetAuraState
    uint32    CastingTimeIndex;                         // 22       m_castingTimeIndex
    uint32    RecoveryTime;                             // 23       m_recoveryTime
    uint32    CategoryRecoveryTime;                     // 24       m_categoryRecoveryTime
    uint32    InterruptFlags;                           // 25       m_interruptFlags
    uint32    AuraInterruptFlags;                       // 26       m_auraInterruptFlags
    uint32    ChannelInterruptFlags;                    // 27       m_channelInterruptFlags
    uint32    procFlags;                                // 28       m_procTypeMask
    uint32    procChance;                               // 29       m_procChance
    uint32    procCharges;                              // 30       m_procCharges
    uint32    maxLevel;                                 // 31       m_maxLevel
    uint32    baseLevel;                                // 32       m_baseLevel
    uint32    spellLevel;                               // 33       m_spellLevel
    uint32    DurationIndex;                            // 34       m_durationIndex
    uint32    powerType;                                // 35       m_powerType
    uint32    manaCost;                                 // 36       m_manaCost
    uint32    manaCostPerlevel;                         // 37       m_manaCostPerLevel
    uint32    manaPerSecond;                            // 38       m_manaPerSecond
    uint32    manaPerSecondPerLevel;                    // 39       m_manaPerSecondPerLevel
    uint32    rangeIndex;                               // 40       m_rangeIndex
    float     speed;                                    // 41       m_speed
    // uint32    modalNextSpell;                        // 42       m_modalNextSpell not used
    uint32    StackAmount;                              // 43       m_cumulativeAura
    uint32    Totem[MAX_SPELL_TOTEMS];                  // 44-45    m_totem
    int32     Reagent[MAX_SPELL_REAGENTS];              // 46-53    m_reagent
    uint32    ReagentCount[MAX_SPELL_REAGENTS];         // 54-61    m_reagentCount
    int32     EquippedItemClass;                        // 62       m_equippedItemClass (value)
    int32     EquippedItemSubClassMask;                 // 63       m_equippedItemSubclass (mask)
    int32     EquippedItemInventoryTypeMask;            // 64       m_equippedItemInvTypes (mask)
    uint32    Effect[MAX_EFFECT_INDEX];                 // 65-67    m_effect
    int32     EffectDieSides[MAX_EFFECT_INDEX];         // 68-70    m_effectDieSides
    uint32    EffectBaseDice[MAX_EFFECT_INDEX];         // 71-73
    float     EffectDicePerLevel[MAX_EFFECT_INDEX];     // 74-76
    float     EffectRealPointsPerLevel[MAX_EFFECT_INDEX];   // 77-79    m_effectRealPointsPerLevel
    int32     EffectBasePoints[MAX_EFFECT_INDEX];       // 80-82    m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    uint32    EffectMechanic[MAX_EFFECT_INDEX];         // 83-85    m_effectMechanic
    uint32    EffectImplicitTargetA[MAX_EFFECT_INDEX];  // 86-88    m_implicitTargetA
    uint32    EffectImplicitTargetB[MAX_EFFECT_INDEX];  // 89-91    m_implicitTargetB
    uint32    EffectRadiusIndex[MAX_EFFECT_INDEX];      // 92-94    m_effectRadiusIndex - spellradius.dbc
    uint32    EffectApplyAuraName[MAX_EFFECT_INDEX];    // 95-97    m_effectAura
    uint32    EffectAmplitude[MAX_EFFECT_INDEX];        // 98-100   m_effectAuraPeriod
    float     EffectMultipleValue[MAX_EFFECT_INDEX];    // 101-103  m_effectAmplitude
    uint32    EffectChainTarget[MAX_EFFECT_INDEX];      // 104-106  m_effectChainTargets
    uint32    EffectItemType[MAX_EFFECT_INDEX];         // 107-109  m_effectItemType
    int32     EffectMiscValue[MAX_EFFECT_INDEX];        // 110-112  m_effectMiscValue
    int32     EffectMiscValueB[MAX_EFFECT_INDEX];       // 113-115  m_effectMiscValueB
    uint32    EffectTriggerSpell[MAX_EFFECT_INDEX];     // 116-118  m_effectTriggerSpell
    float     EffectPointsPerComboPoint[MAX_EFFECT_INDEX];  // 119-121  m_effectPointsPerCombo
    uint32    SpellVisual;                              // 122      m_spellVisualID
    // uint32    SpellVisual2;                          // 123 not used
    uint32    SpellIconID;                              // 124      m_spellIconID
    uint32    activeIconID;                             // 125      m_activeIconID
    uint32    spellPriority;                            // 126      m_spellPriority
    char*     SpellName[16];                            // 127-142  m_name_lang
    // uint32    SpellNameFlag;                         // 143      m_name_flag not used
    char*     Rank[16];                                 // 144-159  m_nameSubtext_lang
    // uint32    RankFlags;                             // 160      m_nameSubtext_flag not used
    // char*     Description[16];                       // 161-176  m_description_lang not used
    // uint32    DescriptionFlags;                      // 177      m_description_flag not used
    // char*     ToolTip[16];                           // 178-193  m_auraDescription_lang not used
    // uint32    ToolTipFlags;                          // 194      m_auraDescription_flag not used
    uint32    ManaCostPercentage;                       // 195      m_manaCostPct
    uint32    StartRecoveryCategory;                    // 196      m_startRecoveryCategory
    uint32    StartRecoveryTime;                        // 197      m_startRecoveryTime
    uint32    MaxTargetLevel;                           // 198      m_maxTargetLevel
    uint32    SpellFamilyName;                          // 199      m_spellClassSet
    uint32    SpellFamilyFlags[2];                         // 200-201  m_spellClassMask
    uint32    MaxAffectedTargets;                       // 202      m_maxTargets
    uint32    DmgClass;                                 // 203      m_defenseType
    uint32    PreventionType;                           // 204      m_preventionType
    // uint32    StanceBarOrder;                        // 205      m_stanceBarOrder not used
    float     DmgMultiplier[MAX_EFFECT_INDEX];          // 206-208  m_effectChainAmplitude
    // uint32    MinFactionId;                          // 209      m_minFactionID not used
    // uint32    MinReputation;                         // 210      m_minReputation not used
    // uint32    RequiredAuraVision;                    // 211      m_requiredAuraVision not used
    uint32    TotemCategory[MAX_SPELL_TOTEM_CATEGORIES];// 212-213  m_requiredTotemCategoryID
    uint32    AreaId;                                   // 214
    uint32    SchoolMask;                               // 215      m_schoolMask

                                                        // custom
    // uint32    IsServerSide;                             // 216
    // uint32    AtrributesServerside;                     // 217
};

struct SpellEntryClassic
{
    uint32    Id;                                       // 0 normally counted from 0 field (but some tools start counting from 1, check this before tool use for data view!)
    uint32    School;                                   // 1 not schoolMask from 2.x - just school type so everything linked with SpellEntry::SchoolMask must be rewrited
    uint32    Category;                                 // 2
    // uint32 castUI;                                   // 3 not used
    uint32    Dispel;                                   // 4
    uint32    Mechanic;                                 // 5
    uint32    Attributes;                               // 6
    uint32    AttributesEx;                             // 7
    uint32    AttributesEx2;                            // 8
    uint32    AttributesEx3;                            // 9
    uint32    AttributesEx4;                            // 10
    uint32    Stances;                                  // 11
    uint32    StancesNot;                               // 12
    uint32    Targets;                                  // 13
    uint32    TargetCreatureType;                       // 14
    uint32    RequiresSpellFocus;                       // 15
    uint32    CasterAuraState;                          // 16
    uint32    TargetAuraState;                          // 17
    uint32    CastingTimeIndex;                         // 18
    uint32    RecoveryTime;                             // 19
    uint32    CategoryRecoveryTime;                     // 20
    uint32    InterruptFlags;                           // 21
    uint32    AuraInterruptFlags;                       // 22
    uint32    ChannelInterruptFlags;                    // 23
    uint32    procFlags;                                // 24
    uint32    procChance;                               // 25
    uint32    procCharges;                              // 26
    uint32    maxLevel;                                 // 27
    uint32    baseLevel;                                // 28
    uint32    spellLevel;                               // 29
    uint32    DurationIndex;                            // 30
    uint32    powerType;                                // 31
    uint32    manaCost;                                 // 32
    uint32    manaCostPerlevel;                         // 33
    uint32    manaPerSecond;                            // 34
    uint32    manaPerSecondPerLevel;                    // 35
    uint32    rangeIndex;                               // 36
    float     speed;                                    // 37
    // uint32    modalNextSpell;                           // 38 not used
    uint32    StackAmount;                              // 39
    uint32    Totem[MAX_SPELL_TOTEMS];                  // 40-41
    int32     Reagent[MAX_SPELL_REAGENTS];              // 42-49
    uint32    ReagentCount[MAX_SPELL_REAGENTS];         // 50-57
    int32     EquippedItemClass;                        // 58 (value)
    int32     EquippedItemSubClassMask;                 // 59 (mask)
    int32     EquippedItemInventoryTypeMask;            // 60 (mask)
    uint32    Effect[MAX_EFFECT_INDEX];                 // 61-63
    int32     EffectDieSides[MAX_EFFECT_INDEX];         // 64-66
    uint32    EffectBaseDice[MAX_EFFECT_INDEX];         // 67-69
    float     EffectDicePerLevel[MAX_EFFECT_INDEX];     // 70-72
    float     EffectRealPointsPerLevel[MAX_EFFECT_INDEX];   // 73-75
    int32     EffectBasePoints[MAX_EFFECT_INDEX];       // 76-78 (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    uint32    EffectMechanic[MAX_EFFECT_INDEX];         // 79-81
    uint32    EffectImplicitTargetA[MAX_EFFECT_INDEX];  // 82-84
    uint32    EffectImplicitTargetB[MAX_EFFECT_INDEX];  // 85-87
    uint32    EffectRadiusIndex[MAX_EFFECT_INDEX];      // 88-90 - spellradius.dbc
    uint32    EffectApplyAuraName[MAX_EFFECT_INDEX];    // 91-93
    uint32    EffectAmplitude[MAX_EFFECT_INDEX];        // 94-96
    float     EffectMultipleValue[MAX_EFFECT_INDEX];    // 97-99
    uint32    EffectChainTarget[MAX_EFFECT_INDEX];      // 100-102
    uint32    EffectItemType[MAX_EFFECT_INDEX];         // 103-105
    int32     EffectMiscValue[MAX_EFFECT_INDEX];        // 106-108
    uint32    EffectTriggerSpell[MAX_EFFECT_INDEX];     // 109-111
    float     EffectPointsPerComboPoint[MAX_EFFECT_INDEX];  // 112-114
    uint32    SpellVisual;                              // 115
    // uint32    SpellVisual2                           // 116 not used
    uint32    SpellIconID;                              // 117
    uint32    activeIconID;                             // 118
    uint32    spellPriority;                            // 119
    char*     SpellName[8];                             // 120-127
    // uint32    SpellNameFlag;                         // 128
    char*     Rank[8];                                  // 129-136
    // uint32    RankFlags;                             // 137
    // char*     Description[8];                        // 138-145 not used
    // uint32    DescriptionFlags;                      // 146     not used
    // char*     ToolTip[8];                            // 147-154 not used
    // uint32    ToolTipFlags;                          // 155     not used
    uint32    ManaCostPercentage;                       // 156
    uint32    StartRecoveryCategory;                    // 157
    uint32    StartRecoveryTime;                        // 158
    uint32    MaxTargetLevel;                           // 159
    uint32    SpellFamilyName;                          // 160
    uint32    SpellFamilyFlags[2];                      // 161+162
    uint32    MaxAffectedTargets;                       // 163
    uint32    DmgClass;                                 // 164 defenseType
    uint32    PreventionType;                           // 165
    // uint32    StanceBarOrder;                        // 166 not used
    float     DmgMultiplier[MAX_EFFECT_INDEX];          // 167-169
    // uint32    MinFactionId;                          // 170 not used, and 0 in 2.4.2
    // uint32    MinReputation;                         // 171 not used, and 0 in 2.4.2
    // uint32    RequiredAuraVision;                    // 172 not used
};

struct DungeonEncounterEntry
{
    uint32 Id;                                              // 0        m_ID
    uint32 mapId;                                           // 1        m_mapID
    uint32 Difficulty;                                      // 2        m_difficulty
    uint32 encounterData;                                   // 3        m_orderIndex
    uint32 encounterIndex;                                  // 4        m_Bit
    char*  encounterName[16];                               // 5-20     m_name_lang
    uint32 nameLangFlags;                                // 21       m_name_lang_flags
    uint32 spellIconID;                                  // 22       m_spellIconID
};

struct FactionEntry
{
    uint32      Id;                                         // 0        m_ID
    int32       reputationListID;                           // 1        m_reputationIndex
    uint32      BaseRepRaceMask[4];                         // 2-5      m_reputationRaceMask
    uint32      BaseRepClassMask[4];                        // 6-9      m_reputationClassMask
    int32       BaseRepValue[4];                            // 10-13    m_reputationBase
    uint32      ReputationFlags[4];                         // 14-17    m_reputationFlags
    uint32      team;                                       // 18       m_parentFactionID
    float       spilloverRateIn;                            // 19       m_parentFactionMod[2] Faction gains incoming rep * spilloverRateIn
    float       spilloverRateOut;                           // 20       Faction outputs rep * spilloverRateOut as spillover reputation
    uint32      spilloverMaxRankIn;                         // 21       m_parentFactionCap[2] The highest rank the faction will profit from incoming spillover
    uint32      spilloverRank_unk;                          // 22       It does not seem to be the max standing at which a faction outputs spillover ...so no idea
    char*       name[16];                                   // 23-38    m_name_lang
                                                            // 39 string flags
                                                            // char*     description[16];                           // 40-55    m_description_lang
                                                            // 56 string flags
};

struct FactionEntryTBC
{
    uint32      Id;                                         // 0        m_ID
    int32       reputationListID;                           // 1        m_reputationIndex
    uint32      BaseRepRaceMask[4];                         // 2-5      m_reputationRaceMask
    uint32      BaseRepClassMask[4];                        // 6-9      m_reputationClassMask
    int32       BaseRepValue[4];                            // 10-13    m_reputationBase
    uint32      ReputationFlags[4];                         // 14-17    m_reputationFlags
    uint32      team;                                       // 18       m_parentFactionID
    char*       name[16];                                   // 23-38    m_name_lang
                                                            // 39 string flags
                                                            // char*     description[16];                           // 40-55    m_description_lang
                                                            // 56 string flags
};

struct AreaGroupEntry
{
    uint32  AreaGroupId;                                    // 0        m_ID
    uint32  AreaId[6];                                      // 1-6      m_areaID
    uint32  nextGroup;                                      // 7        m_nextAreaID
};

#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif
