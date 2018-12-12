#include "DBCExport.h"
#include <set>
#include "DBCDeclarations.h"
#include "PreparedStatementMaker.h"
#include <stdexcept>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#define TARGET_HOST "localhost:2045"
#define TARGET_USER "root"
#define TARGET_PASS "deadlydeath"
#define TARGET_DB "spelldbc"

DBCExport::DBCExport()
{
}

DBCExport::~DBCExport()
{
}

void escapeString(std::string& string)
{
    std::string output;
    for (int i = 0; i < string.size(); i++)
    {
        if (string[i] == '\'')
            output += "'";
        output += string[i];
    }
    string = output;
}

void DBCExport::ExportDBCToSQLWotlk(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt)
{
    //sLog.WaitBeforeContinueIfNeed();
    for (uint32 i = 1; i < 80900; ++i)
    {
        SpellEntryWOTLK const* spellEntry = sSpellStoreWOTLK.LookupEntry(i);
        if (!spellEntry)
            continue;

        std::string spellNameEscaped[16];
        for (int k = 0; k < 16; k++)
        {
            std::string spellName = spellEntry->SpellName[k];
            escapeString(spellName);
            spellNameEscaped[k] = spellName;
        }

        std::string rankEscaped[16];
        for (int k = 0; k < 16; k++)
        {
            std::string rank = spellEntry->Rank[k];
            escapeString(rank);
            rankEscaped[k] = rank;
        }
        char buff[8000];
        //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45    46    47    48    49    50    51    52    53    54    55    56    57    58    59    60    61    62    63    64    65    66    67    68    69    70    71    72    73    74    75    76    77    78    79    80    82    83    84    85    86    87    88    89    90    91    92    93    94    95    96    97    98    99   100   101   102   103   104   105   106   107   108   109   110   111   112   113   114   115   116   117   118   119   120   121   122   123   124   125   126
        snprintf(buff, sizeof(buff), statement.data(),
            tableName.data(),
            spellEntry->Id,
            spellEntry->Category,
            spellEntry->Dispel,
            spellEntry->Mechanic,
            spellEntry->Attributes,
            spellEntry->AttributesEx,
            spellEntry->AttributesEx2,
            spellEntry->AttributesEx3,
            spellEntry->AttributesEx4,
            spellEntry->AttributesEx5,
            spellEntry->AttributesEx6,
            spellEntry->AttributesEx7,
            spellEntry->Stances[0],
            spellEntry->Stances[1],
            spellEntry->StancesNot[0],
            spellEntry->StancesNot[1],
            spellEntry->Targets,
            spellEntry->TargetCreatureType,
            spellEntry->RequiresSpellFocus,
            spellEntry->FacingCasterFlags,
            spellEntry->CasterAuraState,
            spellEntry->TargetAuraState,
            spellEntry->CasterAuraStateNot,
            spellEntry->TargetAuraStateNot,
            spellEntry->casterAuraSpell,
            spellEntry->targetAuraSpell,
            spellEntry->excludeCasterAuraSpell,
            spellEntry->excludeTargetAuraSpell,
            spellEntry->CastingTimeIndex,
            spellEntry->RecoveryTime,
            spellEntry->CategoryRecoveryTime,
            spellEntry->InterruptFlags,
            spellEntry->AuraInterruptFlags,
            spellEntry->ChannelInterruptFlags,
            spellEntry->procFlags,
            spellEntry->procChance,
            spellEntry->procCharges,
            spellEntry->maxLevel,
            spellEntry->baseLevel,
            spellEntry->spellLevel,
            spellEntry->DurationIndex,
            spellEntry->powerType,
            spellEntry->manaCost,
            spellEntry->manaCostPerlevel,
            spellEntry->manaPerSecond,
            spellEntry->manaPerSecondPerLevel,
            spellEntry->rangeIndex,
            spellEntry->speed,
            spellEntry->modalNextSpell,
            spellEntry->StackAmount,
            spellEntry->Totem[0],
            spellEntry->Totem[1],
            spellEntry->Reagent[0],
            spellEntry->Reagent[1],
            spellEntry->Reagent[2],
            spellEntry->Reagent[3],
            spellEntry->Reagent[4],
            spellEntry->Reagent[5],
            spellEntry->Reagent[6],
            spellEntry->Reagent[7],
            spellEntry->ReagentCount[0],
            spellEntry->ReagentCount[1],
            spellEntry->ReagentCount[2],
            spellEntry->ReagentCount[3],
            spellEntry->ReagentCount[4],
            spellEntry->ReagentCount[5],
            spellEntry->ReagentCount[6],
            spellEntry->ReagentCount[7],
            spellEntry->EquippedItemClass,
            spellEntry->EquippedItemSubClassMask,
            spellEntry->EquippedItemInventoryTypeMask,
            spellEntry->Effect[0],
            spellEntry->Effect[1],
            spellEntry->Effect[2],
            spellEntry->EffectDieSides[0],
            spellEntry->EffectDieSides[1],
            spellEntry->EffectDieSides[2],
            spellEntry->EffectRealPointsPerLevel[0],
            spellEntry->EffectRealPointsPerLevel[1],
            spellEntry->EffectRealPointsPerLevel[2],
            spellEntry->EffectBasePoints[0],
            spellEntry->EffectBasePoints[1],
            spellEntry->EffectBasePoints[2],
            spellEntry->EffectMechanic[0],
            spellEntry->EffectMechanic[1],
            spellEntry->EffectMechanic[2],
            spellEntry->EffectImplicitTargetA[0],
            spellEntry->EffectImplicitTargetA[1],
            spellEntry->EffectImplicitTargetA[2],
            spellEntry->EffectImplicitTargetB[0],
            spellEntry->EffectImplicitTargetB[1],
            spellEntry->EffectImplicitTargetB[2],
            spellEntry->EffectRadiusIndex[0],
            spellEntry->EffectRadiusIndex[1],
            spellEntry->EffectRadiusIndex[2],
            spellEntry->EffectApplyAuraName[0],
            spellEntry->EffectApplyAuraName[1],
            spellEntry->EffectApplyAuraName[2],
            spellEntry->EffectAmplitude[0],
            spellEntry->EffectAmplitude[1],
            spellEntry->EffectAmplitude[2],
            spellEntry->EffectMultipleValue[0],
            spellEntry->EffectMultipleValue[1],
            spellEntry->EffectMultipleValue[2],
            spellEntry->EffectChainTarget[0],
            spellEntry->EffectChainTarget[1],
            spellEntry->EffectChainTarget[2],
            spellEntry->EffectItemType[0],
            spellEntry->EffectItemType[1],
            spellEntry->EffectItemType[2],
            spellEntry->EffectMiscValue[0],
            spellEntry->EffectMiscValue[1],
            spellEntry->EffectMiscValue[2],
            spellEntry->EffectMiscValueB[0],
            spellEntry->EffectMiscValueB[1],
            spellEntry->EffectMiscValueB[2],
            spellEntry->EffectTriggerSpell[0],
            spellEntry->EffectTriggerSpell[1],
            spellEntry->EffectTriggerSpell[2],
            spellEntry->EffectPointsPerComboPoint[0],
            spellEntry->EffectPointsPerComboPoint[1],
            spellEntry->EffectPointsPerComboPoint[2],
            spellEntry->EffectSpellClassMask[0][0],
            spellEntry->EffectSpellClassMask[0][1],
            spellEntry->EffectSpellClassMask[0][2],
            spellEntry->EffectSpellClassMask[1][0],
            spellEntry->EffectSpellClassMask[1][1],
            spellEntry->EffectSpellClassMask[1][2],
            spellEntry->EffectSpellClassMask[2][0],
            spellEntry->EffectSpellClassMask[2][1],
            spellEntry->EffectSpellClassMask[2][2],
            spellEntry->SpellVisual[0],
            spellEntry->SpellVisual[1],
            spellEntry->SpellIconID,
            spellEntry->activeIconID,
            spellEntry->spellPriority,
            spellNameEscaped[0].c_str(),
            spellNameEscaped[1].c_str(),
            spellNameEscaped[2].c_str(),
            spellNameEscaped[3].c_str(),
            spellNameEscaped[4].c_str(),
            spellNameEscaped[5].c_str(),
            spellNameEscaped[6].c_str(),
            spellNameEscaped[7].c_str(),
            spellNameEscaped[8].c_str(),
            spellNameEscaped[9].c_str(),
            spellNameEscaped[10].c_str(),
            spellNameEscaped[11].c_str(),
            spellNameEscaped[12].c_str(),
            spellNameEscaped[13].c_str(),
            spellNameEscaped[14].c_str(),
            spellNameEscaped[15].c_str(), // 140
            rankEscaped[0].c_str(),
            rankEscaped[1].c_str(),
            rankEscaped[2].c_str(),
            rankEscaped[3].c_str(),
            rankEscaped[4].c_str(),
            rankEscaped[5].c_str(),
            rankEscaped[6].c_str(),
            rankEscaped[7].c_str(),
            rankEscaped[8].c_str(),
            rankEscaped[9].c_str(),
            rankEscaped[10].c_str(),
            rankEscaped[11].c_str(),
            rankEscaped[12].c_str(),
            rankEscaped[13].c_str(),
            rankEscaped[14].c_str(),
            rankEscaped[15].c_str(),
            spellEntry->ManaCostPercentage,
            spellEntry->StartRecoveryCategory,
            spellEntry->StartRecoveryTime,
            spellEntry->MaxTargetLevel, // 160
            spellEntry->SpellFamilyName,
            uint64(spellEntry->SpellFamilyFlags[0] + ((uint64)spellEntry->SpellFamilyFlags[1] << 32)),
            spellEntry->SpellFamilyFlags[2],
            spellEntry->MaxAffectedTargets,
            spellEntry->DmgClass,
            spellEntry->PreventionType,
            spellEntry->StanceBarOrder,
            spellEntry->DmgMultiplier[0],
            spellEntry->DmgMultiplier[1],
            spellEntry->DmgMultiplier[2],
            spellEntry->MinFactionId,
            spellEntry->MinReputation,
            spellEntry->RequiredAuraVision,
            spellEntry->TotemCategory[0],
            spellEntry->TotemCategory[1],
            spellEntry->AreaGroupId,
            spellEntry->SchoolMask,
            spellEntry->runeCostID,
            spellEntry->spellMissileID,
            spellEntry->PowerDisplayId,
            spellEntry->effectBonusCoefficient[0],
            spellEntry->effectBonusCoefficient[1],
            spellEntry->effectBonusCoefficient[2],
            spellEntry->spellDescriptionVariableID,
            spellEntry->SpellDifficultyId,
                0
        );

        std::string outputString(buff);
        //printf("%s\n",outputString.data());
        stmt->execute(outputString);
    }
}

void DBCExport::ExportDBCToSQLClassic(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt)
{
    //sLog.WaitBeforeContinueIfNeed();
    for (uint32 i = 1; i < 53090; ++i)
    {
        SpellEntryClassic const* spellEntry = sSpellStoreClassic.LookupEntry(i);
        if (!spellEntry)
            continue;

        std::string spellNameEscaped[8];
        for (int k = 0; k < 8; k++)
        {
            std::string spellName = spellEntry->SpellName[k];
            escapeString(spellName);
            spellNameEscaped[k] = spellName;
        }

        std::string rankEscaped[8];
        for (int k = 0; k < 8; k++)
        {
            std::string rank = spellEntry->Rank[k];
            escapeString(rank);
            rankEscaped[k] = rank;
        }
        char buff[5000];
        //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45    46    47    48    49    50    51    52    53    54    55    56    57    58    59    60    61    62    63    64    65    66    67    68    69    70    71    72    73    74    75    76    77    78    79    80    82    83    84    85    86    87    88    89    90    91    92    93    94    95    96    97    98    99   100   101   102   103   104   105   106   107   108   109   110   111   112   113   114   115   116   117   118   119   120   121   122   123   124   125   126
        snprintf(buff, sizeof(buff), statement.data(),
            tableName.data(),
            spellEntry->Id,
            spellEntry->School,
            spellEntry->Category,
            spellEntry->CastUI,
            spellEntry->Dispel,
            spellEntry->Mechanic,
            spellEntry->Attributes,
            spellEntry->AttributesEx,
            spellEntry->AttributesEx2,
            spellEntry->AttributesEx3,
            spellEntry->AttributesEx4,
            spellEntry->Stances,
            spellEntry->StancesNot,
            spellEntry->Targets,
            spellEntry->TargetCreatureType,
            spellEntry->RequiresSpellFocus,
            spellEntry->CasterAuraState,
            spellEntry->TargetAuraState,
            spellEntry->CastingTimeIndex,
            spellEntry->RecoveryTime,
            spellEntry->CategoryRecoveryTime,
            spellEntry->InterruptFlags,
            spellEntry->AuraInterruptFlags,
            spellEntry->ChannelInterruptFlags,
            spellEntry->procFlags,
            spellEntry->procChance,
            spellEntry->procCharges,
            spellEntry->maxLevel,
            spellEntry->baseLevel,
            spellEntry->spellLevel,
            spellEntry->DurationIndex,
            spellEntry->powerType,
            spellEntry->manaCost,
            spellEntry->manaCostPerlevel,
            spellEntry->manaPerSecond,
            spellEntry->manaPerSecondPerLevel,
            spellEntry->rangeIndex,
            spellEntry->speed,
            spellEntry->modalNextSpell,
            spellEntry->StackAmount,
            spellEntry->Totem[0],
            spellEntry->Totem[1],
            spellEntry->Reagent[0],
            spellEntry->Reagent[1],
            spellEntry->Reagent[2],
            spellEntry->Reagent[3],
            spellEntry->Reagent[4],
            spellEntry->Reagent[5],
            spellEntry->Reagent[6],
            spellEntry->Reagent[7],
            spellEntry->ReagentCount[0],
            spellEntry->ReagentCount[1],
            spellEntry->ReagentCount[2],
            spellEntry->ReagentCount[3],
            spellEntry->ReagentCount[4],
            spellEntry->ReagentCount[5],
            spellEntry->ReagentCount[6],
            spellEntry->ReagentCount[7], // 60
            spellEntry->EquippedItemClass,
            spellEntry->EquippedItemSubClassMask,
            spellEntry->EquippedItemInventoryTypeMask,
            spellEntry->Effect[0],
            spellEntry->Effect[1],
            spellEntry->Effect[2],
            spellEntry->EffectDieSides[0],
            spellEntry->EffectDieSides[1],
            spellEntry->EffectDieSides[2],
            spellEntry->EffectBaseDice[0],
            spellEntry->EffectBaseDice[1],
            spellEntry->EffectBaseDice[2],
            spellEntry->EffectDicePerLevel[0],
            spellEntry->EffectDicePerLevel[1],
            spellEntry->EffectDicePerLevel[2],
            spellEntry->EffectRealPointsPerLevel[0],
            spellEntry->EffectRealPointsPerLevel[1],
            spellEntry->EffectRealPointsPerLevel[2],
            spellEntry->EffectBasePoints[0],
            spellEntry->EffectBasePoints[1], // 80
            spellEntry->EffectBasePoints[2],
            spellEntry->EffectMechanic[0],
            spellEntry->EffectMechanic[1],
            spellEntry->EffectMechanic[2],
            spellEntry->EffectImplicitTargetA[0],
            spellEntry->EffectImplicitTargetA[1],
            spellEntry->EffectImplicitTargetA[2],
            spellEntry->EffectImplicitTargetB[0],
            spellEntry->EffectImplicitTargetB[1],
            spellEntry->EffectImplicitTargetB[2],
            spellEntry->EffectRadiusIndex[0],
            spellEntry->EffectRadiusIndex[1],
            spellEntry->EffectRadiusIndex[2],
            spellEntry->EffectApplyAuraName[0],
            spellEntry->EffectApplyAuraName[1],
            spellEntry->EffectApplyAuraName[2],
            spellEntry->EffectAmplitude[0],
            spellEntry->EffectAmplitude[1],
            spellEntry->EffectAmplitude[2],
            spellEntry->EffectMultipleValue[0], // 100
            spellEntry->EffectMultipleValue[1],
            spellEntry->EffectMultipleValue[2],
            spellEntry->EffectChainTarget[0],
            spellEntry->EffectChainTarget[1],
            spellEntry->EffectChainTarget[2],
            spellEntry->EffectItemType[0],
            spellEntry->EffectItemType[1],
            spellEntry->EffectItemType[2],
            spellEntry->EffectMiscValue[0],
            spellEntry->EffectMiscValue[1],
            spellEntry->EffectMiscValue[2],
            spellEntry->EffectTriggerSpell[0],
            spellEntry->EffectTriggerSpell[1],
            spellEntry->EffectTriggerSpell[2],
            spellEntry->EffectPointsPerComboPoint[0],
            spellEntry->EffectPointsPerComboPoint[1],
            spellEntry->EffectPointsPerComboPoint[2], // 120 - 121
            spellEntry->SpellVisual,
            spellEntry->SpellIconID,
            spellEntry->activeIconID,
            spellEntry->spellPriority,
            spellNameEscaped[0].c_str(),
            spellNameEscaped[1].c_str(),
            spellNameEscaped[2].c_str(),
            spellNameEscaped[3].c_str(),
            spellNameEscaped[4].c_str(),
            spellNameEscaped[5].c_str(),
            spellNameEscaped[6].c_str(),
            spellNameEscaped[7].c_str(),
            rankEscaped[0].c_str(),
            rankEscaped[1].c_str(),
            rankEscaped[2].c_str(),
            rankEscaped[3].c_str(),
            rankEscaped[4].c_str(),
            rankEscaped[5].c_str(),
            rankEscaped[6].c_str(),
            rankEscaped[7].c_str(),
            spellEntry->ManaCostPercentage,
            spellEntry->StartRecoveryCategory,
            spellEntry->StartRecoveryTime,
            spellEntry->MaxTargetLevel,
            spellEntry->SpellFamilyName,
            uint64(spellEntry->SpellFamilyFlags[0] + ((uint64)spellEntry->SpellFamilyFlags[1] << 32)),
            spellEntry->MaxAffectedTargets,
            spellEntry->DmgClass,
            spellEntry->PreventionType,
            spellEntry->StanceBarOrder,
            spellEntry->DmgMultiplier[0],
            spellEntry->DmgMultiplier[1],
            spellEntry->DmgMultiplier[2],
            spellEntry->MinFactionId,
            spellEntry->MinReputation,
            spellEntry->RequiredAuraVision,
            0
        );

        std::string outputString(buff);
        //printf("%s\n",outputString.data());
        stmt->execute(outputString);
    }
}

void DBCExport::ExportDBCToSQLTBC(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt)
{
    //sLog.WaitBeforeContinueIfNeed();
    for (uint32 i = 1; i < 53090; ++i)
    {
        SpellEntryTBC const* spellEntry = sSpellStoreTBC.LookupEntry(i);
        if (!spellEntry)
            continue;

        std::string spellNameEscaped[16];
        for (int k = 0; k < 16; k++)
        {
            std::string spellName = spellEntry->SpellName[k];
            escapeString(spellName);
            spellNameEscaped[k] = spellName;
        }

        std::string rankEscaped[16];
        for (int k = 0; k < 16; k++)
        {
            std::string rank = spellEntry->Rank[k];
            escapeString(rank);
            rankEscaped[k] = rank;
        }
        char buff[5000];
        /*
        //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45    46    47    48    49    50    51    52    53    54    55    56    57    58    59    60    61    62    63    64    65    66    67    68    69    70    71    72    73    74    75    76    77    78    79    80    81    82    83    84    85    86    87    88    89    90    91    92    94    95    96    97    98    99   100   101   102   103   104   105   106   107   108   109   110   111   112   113   114   115   116   117   118   119   120   121   122   123   124   125   126   127   128   129   130   131   132   133   134   135   136   137   138   139   140   141   142   143   144   145   146   147   148   149   150   151   152   153   154   155   156   157   158   159   160   161   162   163     164   165   166   167   168   169   170   171   172   173
        snprintf(buff, sizeof(buff), "INSERT INTO %s (`Id`,  `Category`,  `Dispel`,  `Mechanic`,  `Attributes`,  `AttributesEx`,  `AttributesEx2`,  `AttributesEx3`,  `AttributesEx4`,  `AttributesEx5`,  `AttributesEx6`,  `Stances`,  `StancesNot`,  `Targets`,  `TargetCreatureType`,  `RequiresSpellFocus`,  `FacingCasterFlags`,  `CasterAuraState`,  `TargetAuraState`,  `CasterAuraStateNot`,  `TargetAuraStateNot`,  `CastingTimeIndex`,  `RecoveryTime`,  `CategoryRecoveryTime`,  `InterruptFlags`,  `AuraInterruptFlags`,  `ChannelInterruptFlags`,  `procFlags`,  `procChance`,  `procCharges`,  `maxLevel`,  `baseLevel`,  `spellLevel`,  `DurationIndex`,  `powerType`,  `manaCost`,  `manaCostPerlevel`,  `manaPerSecond`,  `manaPerSecondPerLevel`,  `rangeIndex`,  `speed`,  `StackAmount`,  `Totem1`,  `Totem2`,  `Reagent1`,  `Reagent2`,  `Reagent3`,  `Reagent4`,  `Reagent5`,  `Reagent6`,  `Reagent7`,  `Reagent8`,  `ReagentCount1`,  `ReagentCount2`,  `ReagentCount3`,  `ReagentCount4`,  `ReagentCount5`,  `ReagentCount6`,  `ReagentCount7`,  `ReagentCount8`,  `EquippedItemClass`,  `EquippedItemSubClassMask`,  `EquippedItemInventoryTypeMask`,  `Effect1`,  `Effect2`,  `Effect3`,  `EffectDieSides1`,  `EffectDieSides2`,  `EffectDieSides3`,  `EffectBaseDice1`,  `EffectBaseDice2`,  `EffectBaseDice3`,  `EffectDicePerLevel1`,  `EffectDicePerLevel2`,  `EffectDicePerLevel3`,  `EffectRealPointsPerLevel1`,  `EffectRealPointsPerLevel2`,  `EffectRealPointsPerLevel3`,  `EffectBasePoints1`,  `EffectBasePoints2`,  `EffectBasePoints3`,  `EffectMechanic1`,  `EffectMechanic2`,  `EffectMechanic3`,  `EffectImplicitTargetA1`,  `EffectImplicitTargetA2`,  `EffectImplicitTargetA3`,  `EffectImplicitTargetB1`,  `EffectImplicitTargetB2`,  `EffectImplicitTargetB3`,  `EffectRadiusIndex1`,  `EffectRadiusIndex2`,  `EffectRadiusIndex3`,  `EffectApplyAuraName1`,  `EffectApplyAuraName2`,  `EffectApplyAuraName3`,  `EffectAmplitude1`,  `EffectAmplitude2`,  `EffectAmplitude3`,  `EffectMultipleValue1`,  `EffectMultipleValue2`,  `EffectMultipleValue3`,  `EffectChainTarget1`,  `EffectChainTarget2`,  `EffectChainTarget3`,  `EffectItemType1`,  `EffectItemType2`,  `EffectItemType3`,  `EffectMiscValue1`,  `EffectMiscValue2`,  `EffectMiscValue3`,  `EffectMiscValueB1`,  `EffectMiscValueB2`,  `EffectMiscValueB3`,  `EffectTriggerSpell1`,  `EffectTriggerSpell2`,  `EffectTriggerSpell3`,  `EffectPointsPerComboPoint1`,  `EffectPointsPerComboPoint2`,  `EffectPointsPerComboPoint3`,  `SpellVisual`,  `SpellIconID`,  `activeIconID`,  `spellPriority`,  `SpellName`,  `SpellName2`,  `SpellName3`,  `SpellName4`,  `SpellName5`,  `SpellName6`,  `SpellName7`,  `SpellName8`,  `SpellName9`,  `SpellName10`,  `SpellName11`,  `SpellName12`,  `SpellName13`,  `SpellName14`,  `SpellName15`,  `SpellName16`,  `Rank`,  `Rank2`,  `Rank3`,  `Rank4`,  `Rank5`,  `Rank6`,  `Rank7`,  `Rank8`,  `Rank9`,  `Rank10`,  `Rank11`,  `Rank12`,  `Rank13`,  `Rank14`,  `Rank15`,  `Rank16`,  `ManaCostPercentage`,  `StartRecoveryCategory`,  `StartRecoveryTime`,  `MaxTargetLevel`,  `SpellFamilyName`,  `SpellFamilyFlags`,  `MaxAffectedTargets`,  `DmgClass`,  `PreventionType`,  `DmgMultiplier1`,  `DmgMultiplier2`,  `DmgMultiplier3`,  `TotemCategory1`,  `TotemCategory2`,  `AreaId`,  `SchoolMask`) VALUES ('%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%f', '%u', '%u', '%u', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%i', '%i', '%i', '%u', '%u', '%u', '%i', '%i', '%i', '%u', '%u', '%u', '%f', '%f', '%f', '%f', '%f', '%f', '%i', '%i', '%i', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%f', '%f', '%f', '%u', '%u', '%u', '%u', '%u', '%u', '%i', '%i', '%i', '%i', '%i', '%i', '%u', '%u', '%u', '%f', '%f', '%f', '%u', '%u', '%u', '%u', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%u', '%u', '%u', '%u', '%u', '%llu', '%u', '%u', '%u', '%f', '%f', '%f', '%u', '%u', '%u', '%u')",
        */
        //                INSERT INTO %s (`Id`,  `Category`,  `Dispel`,  `Mechanic`,  `Attributes`,  `AttributesEx`,  `AttributesEx2`,  `AttributesEx3`,  `AttributesEx4`,  `AttributesEx5`,  `AttributesEx6`,  `Stances`,  `StancesNot`,  `Targets`,  `TargetCreatureType`,  `RequiresSpellFocus`,  `FacingCasterFlags`,  `CasterAuraState`,  `TargetAuraState`,  `CasterAuraStateNot`,  `TargetAuraStateNot`,  `CastingTimeIndex`,  `RecoveryTime`,  `CategoryRecoveryTime`,  `InterruptFlags`,  `AuraInterruptFlags`,  `ChannelInterruptFlags`,  `procFlags`,  `procChance`,  `procCharges`,  `maxLevel`,  `baseLevel`,  `spellLevel`,  `DurationIndex`,  `powerType`,  `manaCost`,  `manaCostPerlevel`,  `manaPerSecond`,  `manaPerSecondPerLevel`,  `rangeIndex`,  `speed`,  `StackAmount`,  `Totem1`,  `Totem2`,  `Reagent1`,  `Reagent2`,  `Reagent3`,  `Reagent4`,  `Reagent5`,  `Reagent6`,  `Reagent7`,  `Reagent8`,  `ReagentCount1`,  `ReagentCount2`,  `ReagentCount3`,  `ReagentCount4`,  `ReagentCount5`,  `ReagentCount6`,  `ReagentCount7`,  `ReagentCount8`,  `EquippedItemClass`,  `EquippedItemSubClassMask`,  `EquippedItemInventoryTypeMask`,  `Effect1`,  `Effect2`,  `Effect3`,  `EffectDieSides1`,  `EffectDieSides2`,  `EffectDieSides3`,  `EffectBaseDice1`,  `EffectBaseDice2`,  `EffectBaseDice3`,  `EffectDicePerLevel1`,  `EffectDicePerLevel2`,  `EffectDicePerLevel3`,  `EffectRealPointsPerLevel1`,  `EffectRealPointsPerLevel2`,  `EffectRealPointsPerLevel3`,  `EffectBasePoints1`,  `EffectBasePoints2`,  `EffectBasePoints3`,  `EffectMechanic1`,  `EffectMechanic2`,  `EffectMechanic3`,  `EffectImplicitTargetA1`,  `EffectImplicitTargetA2`,  `EffectImplicitTargetA3`,  `EffectImplicitTargetB1`,  `EffectImplicitTargetB2`,  `EffectImplicitTargetB3`,  `EffectRadiusIndex1`,  `EffectRadiusIndex2`,  `EffectRadiusIndex3`,  `EffectApplyAuraName1`,  `EffectApplyAuraName2`,  `EffectApplyAuraName3`,  `EffectAmplitude1`,  `EffectAmplitude2`,  `EffectAmplitude3`,  `EffectMultipleValue1`,  `EffectMultipleValue2`,  `EffectMultipleValue3`,  `EffectChainTarget1`,  `EffectChainTarget2`,  `EffectChainTarget3`,  `EffectItemType1`,  `EffectItemType2`,  `EffectItemType3`,  `EffectMiscValue1`,  `EffectMiscValue2`,  `EffectMiscValue3`,  `EffectMiscValueB1`,  `EffectMiscValueB2`,  `EffectMiscValueB3`,  `EffectTriggerSpell1`,  `EffectTriggerSpell2`,  `EffectTriggerSpell3`,  `EffectPointsPerComboPoint1`,  `EffectPointsPerComboPoint2`,  `EffectPointsPerComboPoint3`,  `SpellVisual`,  `SpellIconID`,  `activeIconID`,  `spellPriority`,  `SpellName`,  `SpellName2`,  `SpellName3`,  `SpellName4`,  `SpellName5`,  `SpellName6`,  `SpellName7`,  `SpellName8`,  `SpellName9`,  `SpellName10`,  `SpellName11`,  `SpellName12`,  `SpellName13`,  `SpellName14`,  `SpellName15`,  `SpellName16`,  `Rank`,  `Rank2`,  `Rank3`,  `Rank4`,  `Rank5`,  `Rank6`,  `Rank7`,  `Rank8`,  `Rank9`,  `Rank10`,  `Rank11`,  `Rank12`,  `Rank13`,  `Rank14`,  `Rank15`,  `Rank16`,  `ManaCostPercentage`,  `StartRecoveryCategory`,  `StartRecoveryTime`,  `MaxTargetLevel`,  `SpellFamilyName`,  `SpellFamilyFlags`,  `MaxAffectedTargets`,  `DmgClass`,  `PreventionType`,  `DmgMultiplier1`,  `DmgMultiplier2`,  `DmgMultiplier3`,  `TotemCategory1`,  `TotemCategory2`,  `AreaId`,  `SchoolMask`) VALUES ('%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%f', '%u', '%u', '%u', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%i', '%i', '%i', '%u', '%u', '%u', '%i', '%i', '%i', '%u', '%u', '%u', '%f', '%f', '%f', '%f', '%f', '%f', '%i', '%i', '%i', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%u', '%f', '%f', '%f', '%u', '%u', '%u', '%u', '%u', '%u', '%i', '%i', '%i', '%i', '%i', '%i', '%u', '%u', '%u', '%f', '%f', '%f', '%u', '%u', '%u', '%u', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%u', '%u', '%u', '%u', '%u', '%llu', '%u', '%u', '%u', '%f', '%f', '%f', '%u', '%u', '%u', '%u')
        snprintf(buff, sizeof(buff), statement.data(),
            tableName.data(),
            spellEntry->Id,
            spellEntry->Category,
            spellEntry->CastUI,
            spellEntry->Dispel,
            spellEntry->Mechanic,
            spellEntry->Attributes,
            spellEntry->AttributesEx,
            spellEntry->AttributesEx2,
            spellEntry->AttributesEx3,
            spellEntry->AttributesEx4,
            spellEntry->AttributesEx5,
            spellEntry->AttributesEx6,
            spellEntry->Stances,
            spellEntry->StancesNot,
            spellEntry->Targets,
            spellEntry->TargetCreatureType,
            spellEntry->RequiresSpellFocus,
            spellEntry->FacingCasterFlags,
            spellEntry->CasterAuraState,
            spellEntry->TargetAuraState,
            spellEntry->CasterAuraStateNot,
            spellEntry->TargetAuraStateNot,
            spellEntry->CastingTimeIndex,
            spellEntry->RecoveryTime,
            spellEntry->CategoryRecoveryTime,
            spellEntry->InterruptFlags,
            spellEntry->AuraInterruptFlags,
            spellEntry->ChannelInterruptFlags,
            spellEntry->procFlags,
            spellEntry->procChance,
            spellEntry->procCharges,
            spellEntry->maxLevel,
            spellEntry->baseLevel,
            spellEntry->spellLevel,
            spellEntry->DurationIndex,
            spellEntry->powerType,
            spellEntry->manaCost,
            spellEntry->manaCostPerlevel,
            spellEntry->manaPerSecond,
            spellEntry->manaPerSecondPerLevel,
            spellEntry->rangeIndex, // 40
            spellEntry->speed,
            spellEntry->modalNextSpell,
            spellEntry->StackAmount,
            spellEntry->Totem[0],
            spellEntry->Totem[1],
            spellEntry->Reagent[0],
            spellEntry->Reagent[1],
            spellEntry->Reagent[2],
            spellEntry->Reagent[3],
            spellEntry->Reagent[4],
            spellEntry->Reagent[5],
            spellEntry->Reagent[6],
            spellEntry->Reagent[7],
            spellEntry->ReagentCount[0],
            spellEntry->ReagentCount[1],
            spellEntry->ReagentCount[2],
            spellEntry->ReagentCount[3],
            spellEntry->ReagentCount[4],
            spellEntry->ReagentCount[5],
            spellEntry->ReagentCount[6],
            spellEntry->ReagentCount[7], // 60
            spellEntry->EquippedItemClass,
            spellEntry->EquippedItemSubClassMask,
            spellEntry->EquippedItemInventoryTypeMask,
            spellEntry->Effect[0],
            spellEntry->Effect[1],
            spellEntry->Effect[2],
            spellEntry->EffectDieSides[0],
            spellEntry->EffectDieSides[1],
            spellEntry->EffectDieSides[2],
            spellEntry->EffectBaseDice[0],
            spellEntry->EffectBaseDice[1],
            spellEntry->EffectBaseDice[2],
            spellEntry->EffectDicePerLevel[0],
            spellEntry->EffectDicePerLevel[1],
            spellEntry->EffectDicePerLevel[2],
            spellEntry->EffectRealPointsPerLevel[0],
            spellEntry->EffectRealPointsPerLevel[1],
            spellEntry->EffectRealPointsPerLevel[2],
            spellEntry->EffectBasePoints[0],
            spellEntry->EffectBasePoints[1], // 80
            spellEntry->EffectBasePoints[2],
            spellEntry->EffectMechanic[0],
            spellEntry->EffectMechanic[1],
            spellEntry->EffectMechanic[2],
            spellEntry->EffectImplicitTargetA[0],
            spellEntry->EffectImplicitTargetA[1],
            spellEntry->EffectImplicitTargetA[2],
            spellEntry->EffectImplicitTargetB[0],
            spellEntry->EffectImplicitTargetB[1],
            spellEntry->EffectImplicitTargetB[2],
            spellEntry->EffectRadiusIndex[0],
            spellEntry->EffectRadiusIndex[1],
            spellEntry->EffectRadiusIndex[2],
            spellEntry->EffectApplyAuraName[0],
            spellEntry->EffectApplyAuraName[1],
            spellEntry->EffectApplyAuraName[2],
            spellEntry->EffectAmplitude[0],
            spellEntry->EffectAmplitude[1],
            spellEntry->EffectAmplitude[2],
            spellEntry->EffectMultipleValue[0], // 100
            spellEntry->EffectMultipleValue[1],
            spellEntry->EffectMultipleValue[2],
            spellEntry->EffectChainTarget[0],
            spellEntry->EffectChainTarget[1],
            spellEntry->EffectChainTarget[2],
            spellEntry->EffectItemType[0],
            spellEntry->EffectItemType[1],
            spellEntry->EffectItemType[2],
            spellEntry->EffectMiscValue[0],
            spellEntry->EffectMiscValue[1],
            spellEntry->EffectMiscValue[2],
            spellEntry->EffectMiscValueB[0],
            spellEntry->EffectMiscValueB[1],
            spellEntry->EffectMiscValueB[2],
            spellEntry->EffectTriggerSpell[0],
            spellEntry->EffectTriggerSpell[1],
            spellEntry->EffectTriggerSpell[2],
            spellEntry->EffectPointsPerComboPoint[0],
            spellEntry->EffectPointsPerComboPoint[1],
            spellEntry->EffectPointsPerComboPoint[2], // 120 - 121
            spellEntry->SpellVisual,
            spellEntry->SpellIconID,
            spellEntry->activeIconID,
            spellEntry->spellPriority,
            spellNameEscaped[0].c_str(),
            spellNameEscaped[1].c_str(),
            spellNameEscaped[2].c_str(),
            spellNameEscaped[3].c_str(),
            spellNameEscaped[4].c_str(),
            spellNameEscaped[5].c_str(),
            spellNameEscaped[6].c_str(),
            spellNameEscaped[7].c_str(),
            spellNameEscaped[8].c_str(),
            spellNameEscaped[9].c_str(),
            spellNameEscaped[10].c_str(),
            spellNameEscaped[11].c_str(),
            spellNameEscaped[12].c_str(),
            spellNameEscaped[13].c_str(),
            spellNameEscaped[14].c_str(),
            spellNameEscaped[15].c_str(), // 140
            rankEscaped[0].c_str(),
            rankEscaped[1].c_str(),
            rankEscaped[2].c_str(),
            rankEscaped[3].c_str(),
            rankEscaped[4].c_str(),
            rankEscaped[5].c_str(),
            rankEscaped[6].c_str(),
            rankEscaped[7].c_str(),
            rankEscaped[8].c_str(),
            rankEscaped[9].c_str(),
            rankEscaped[10].c_str(),
            rankEscaped[11].c_str(),
            rankEscaped[12].c_str(),
            rankEscaped[13].c_str(),
            rankEscaped[14].c_str(),
            rankEscaped[15].c_str(),
            spellEntry->ManaCostPercentage,
            spellEntry->StartRecoveryCategory,
            spellEntry->StartRecoveryTime,
            spellEntry->MaxTargetLevel, // 160
            spellEntry->SpellFamilyName,
            uint64(spellEntry->SpellFamilyFlags[0] + ((uint64)spellEntry->SpellFamilyFlags[1] << 32)),
            spellEntry->MaxAffectedTargets,
            spellEntry->DmgClass,
            spellEntry->PreventionType,
            spellEntry->StanceBarOrder,
            spellEntry->DmgMultiplier[0],
            spellEntry->DmgMultiplier[1],
            spellEntry->DmgMultiplier[2],
            spellEntry->MinFactionId,
            spellEntry->MinReputation,
            spellEntry->RequiredAuraVision,
            spellEntry->TotemCategory[0],
            spellEntry->TotemCategory[1],
            spellEntry->AreaId,
            spellEntry->SchoolMask,
            0);


        std::string outputString(buff);
        //printf("%s\n",outputString.data());
        stmt->execute(outputString);
    }
}

void DBCExport::ExportDungeonEncounters(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt)
{
    //sLog.WaitBeforeContinueIfNeed();
    for (uint32 i = 1; i < 80900; ++i)
    {
        DungeonEncounterEntry const* dungEntry = sDungeonEncounterStore.LookupEntry(i);
        if (!dungEntry)
            continue;

        std::string dungNameEscaped[16];
        for (int k = 0; k < 16; k++)
        {
            std::string dungName = dungEntry->encounterName[k];
            escapeString(dungName);
            dungNameEscaped[k] = dungName;
        }

        char buff[5000];
        //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45    46    47    48    49    50    51    52    53    54    55    56    57    58    59    60    61    62    63    64    65    66    67    68    69    70    71    72    73    74    75    76    77    78    79    80    82    83    84    85    86    87    88    89    90    91    92    93    94    95    96    97    98    99   100   101   102   103   104   105   106   107   108   109   110   111   112   113   114   115   116   117   118   119   120   121   122   123   124   125   126
        snprintf(buff, sizeof(buff), statement.data(),
            tableName.data(),
            dungEntry->Id,
            dungEntry->mapId,
            dungEntry->Difficulty,
            dungEntry->encounterData,
            dungEntry->encounterIndex,
            dungNameEscaped[0].data(),
            dungNameEscaped[1].data(),
            dungNameEscaped[2].data(),
            dungNameEscaped[3].data(),
            dungNameEscaped[4].data(),
            dungNameEscaped[5].data(),
            dungNameEscaped[6].data(),
            dungNameEscaped[7].data(),
            dungNameEscaped[8].data(),
            dungNameEscaped[9].data(),
            dungNameEscaped[10].data(),
            dungNameEscaped[11].data(),
            dungNameEscaped[12].data(),
            dungNameEscaped[13].data(),
            dungNameEscaped[14].data(),
            dungNameEscaped[15].data(),
            dungEntry->nameLangFlags,
            dungEntry->spellIconID
        );

        std::string outputString(buff);
        //printf("%s\n",outputString.data());
        stmt->execute(outputString);
    }
}

void DBCExport::ExportFactionsTBC(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt)
{
    //sLog.WaitBeforeContinueIfNeed();
    for (uint32 i = 1; i < 80900; ++i)
    {
        FactionEntryTBC const* factionEntry = sFactionStoreTBC.LookupEntry(i);
        if (!factionEntry)
            continue;

        std::string factionNameEscaped[16];
        for (int k = 0; k < 16; k++)
        {
            std::string factionName = factionEntry->name[k];
            escapeString(factionName);
            factionNameEscaped[k] = factionName;
        }

        char buff[5000];
        //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45    46    47    48    49    50    51    52    53    54    55    56    57    58    59    60    61    62    63    64    65    66    67    68    69    70    71    72    73    74    75    76    77    78    79    80    82    83    84    85    86    87    88    89    90    91    92    93    94    95    96    97    98    99   100   101   102   103   104   105   106   107   108   109   110   111   112   113   114   115   116   117   118   119   120   121   122   123   124   125   126
        snprintf(buff, sizeof(buff), statement.data(),
            tableName.data(),
            factionEntry->Id,
            factionEntry->reputationListID,
            factionEntry->BaseRepRaceMask[0],
            factionEntry->BaseRepRaceMask[1],
            factionEntry->BaseRepRaceMask[2],
            factionEntry->BaseRepRaceMask[3],
            factionEntry->BaseRepClassMask[0],
            factionEntry->BaseRepClassMask[1],
            factionEntry->BaseRepClassMask[2],
            factionEntry->BaseRepClassMask[3],
            factionEntry->BaseRepValue[0],
            factionEntry->BaseRepValue[1],
            factionEntry->BaseRepValue[2],
            factionEntry->BaseRepValue[3],
            factionEntry->ReputationFlags[0],
            factionEntry->ReputationFlags[1],
            factionEntry->ReputationFlags[2],
            factionEntry->ReputationFlags[3],
            factionEntry->team,
            factionNameEscaped[0].data(),
            factionNameEscaped[1].data(),
            factionNameEscaped[2].data(),
            factionNameEscaped[3].data(),
            factionNameEscaped[4].data(),
            factionNameEscaped[5].data(),
            factionNameEscaped[6].data(),
            factionNameEscaped[7].data(),
            factionNameEscaped[8].data(),
            factionNameEscaped[9].data(),
            factionNameEscaped[10].data(),
            factionNameEscaped[11].data(),
            factionNameEscaped[12].data(),
            factionNameEscaped[13].data(),
            factionNameEscaped[14].data(),
            factionNameEscaped[15].data()
        );

        std::string outputString(buff);
        //printf("%s\n",outputString.data());
        stmt->execute(outputString);
    }
}

void DBCExport::ExportDBCGeneric(std::string tableName, std::function<void(std::string&, std::string&, std::unique_ptr<sql::Statement>&)> executor)
{
    //sLog.WaitBeforeContinueIfNeed();

    std::string url(TARGET_HOST);
    const std::string user(TARGET_USER);
    const std::string pass(TARGET_PASS);
    const std::string database(TARGET_DB);
    PreparedStatementMaker maker;
    std::string statement;
    maker.MakePreparedStatement(tableName, statement);
    try {

        sql::Driver* driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
        con->setSchema(database);
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        executor(tableName, statement, stmt);
    }
    catch (sql::SQLException &e) {
        /*
        MySQL Connector/C++ throws three different exceptions:

        - sql::MethodNotImplementedException (derived from sql::SQLException)
        - sql::InvalidArgumentException (derived from sql::SQLException)
        - sql::SQLException (derived from std::runtime_error)
        */
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        /* what() (derived from std::runtime_error) fetches error message */
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        return;
    }

    std::cout << "Done." << std::endl;
    return;
}

void DBCExport::ExportAreaGroupWotlk(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt)
{
    for (uint32 i = 1; i < sAreaGroupStore.GetNumRows(); ++i)
    {
        AreaGroupEntry const* areaEntry = sAreaGroupStore.LookupEntry(i);
        if (!areaEntry)
            continue;

        char buff[5000];
        //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45    46    47    48    49    50    51    52    53    54    55    56    57    58    59    60    61    62    63    64    65    66    67    68    69    70    71    72    73    74    75    76    77    78    79    80    82    83    84    85    86    87    88    89    90    91    92    93    94    95    96    97    98    99   100   101   102   103   104   105   106   107   108   109   110   111   112   113   114   115   116   117   118   119   120   121   122   123   124   125   126
        snprintf(buff, sizeof(buff), statement.data(),
            tableName.data(),
            areaEntry->AreaGroupId,
            areaEntry->AreaId[0],
            areaEntry->AreaId[1],
            areaEntry->AreaId[2],
            areaEntry->AreaId[3],
            areaEntry->AreaId[4],
            areaEntry->AreaId[5],
            areaEntry->nextGroup
        );

        std::string outputString(buff);
        //printf("%s\n",outputString.data());
        stmt->execute(outputString);
    }
}

void DBCExport::ExportFactionsWOTLK(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt)
{
    //sLog.WaitBeforeContinueIfNeed();
    for (uint32 i = 1; i < 80900; ++i)
    {
        FactionEntry const* factionEntry = sFactionStore.LookupEntry(i);
        if (!factionEntry)
            continue;

        std::string factionNameEscaped[16];
        for (int k = 0; k < 16; k++)
        {
            std::string factionName = factionEntry->name[k];
            escapeString(factionName);
            factionNameEscaped[k] = factionName;
        }

        char buff[5000];
        //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45    46    47    48    49    50    51    52    53    54    55    56    57    58    59    60    61    62    63    64    65    66    67    68    69    70    71    72    73    74    75    76    77    78    79    80    82    83    84    85    86    87    88    89    90    91    92    93    94    95    96    97    98    99   100   101   102   103   104   105   106   107   108   109   110   111   112   113   114   115   116   117   118   119   120   121   122   123   124   125   126
        snprintf(buff, sizeof(buff), statement.data(),
            tableName.data(),
            factionEntry->Id,
            factionEntry->reputationListID,
            factionEntry->BaseRepRaceMask[0],
            factionEntry->BaseRepRaceMask[1],
            factionEntry->BaseRepRaceMask[2],
            factionEntry->BaseRepRaceMask[3],
            factionEntry->BaseRepClassMask[0],
            factionEntry->BaseRepClassMask[1],
            factionEntry->BaseRepClassMask[2],
            factionEntry->BaseRepClassMask[3],
            factionEntry->BaseRepValue[0],
            factionEntry->BaseRepValue[1],
            factionEntry->BaseRepValue[2],
            factionEntry->BaseRepValue[3],
            factionEntry->ReputationFlags[0],
            factionEntry->ReputationFlags[1],
            factionEntry->ReputationFlags[2],
            factionEntry->ReputationFlags[3],
            factionEntry->team,
            factionEntry->spilloverRateIn,
            factionEntry->spilloverRateOut,
            factionEntry->spilloverMaxRankIn,
            factionEntry->spilloverRank_unk,
            factionNameEscaped[0].data(),
            factionNameEscaped[1].data(),
            factionNameEscaped[2].data(),
            factionNameEscaped[3].data(),
            factionNameEscaped[4].data(),
            factionNameEscaped[5].data(),
            factionNameEscaped[6].data(),
            factionNameEscaped[7].data(),
            factionNameEscaped[8].data(),
            factionNameEscaped[9].data(),
            factionNameEscaped[10].data(),
            factionNameEscaped[11].data(),
            factionNameEscaped[12].data(),
            factionNameEscaped[13].data(),
            factionNameEscaped[14].data(),
            factionNameEscaped[15].data()
        );

        std::string outputString(buff);
        //printf("%s\n",outputString.data());
        stmt->execute(outputString);
    }
}