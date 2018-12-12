#include "DBCDeclarations.h"

const char SpellEntryfmtWOTLK[] = "niiiiiiiiiiiixixiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifxiiiiiiiiiiiiiiiiiiiiiiiiiiiifffiiiiiiiiiiiiiiiiiiiiifffiiiiiiiiiiiiiiifffiiiiiiiiiiiiiissssssssssssssssxssssssssssssssssxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxiiiiiiiiiiixfffxxxiiiiixxxxxxi";
const char SpellEntryfmtTBC[] = "niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffffffiiiiiiiiiiiiiiiiiiiiifffiiiiiiiiiiiiiiifffixiiissssssssssssssssxssssssssssssssssxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxiiiiiiiiiiifffiiiiiii";
const char SpellEntryfmtClassic[] = "niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffffffiiiiiiiiiiiiiiiiiiiiifffiiiiiiiiiiiifffixiiissssssssxssssssssxxxxxxxxxxxxxxxxxxxiiiiiiiiiiifffiii";
const char DungeonEncounterFmt[] = "iiiiissssssssssssssssii";
const char FactionEntryfmt[]    = "niiiiiiiiiiiiiiiiiiffiissssssssssssssssxxxxxxxxxxxxxxxxxx";
const char FactionEntryTBCfmt[] = "niiiiiiiiiiiiiiiiiissssssssssssssssxxxxxxxxxxxxxxxxxx";
const char AreaGroupFmt[] = "niiiiiii";

// to get respective SQL to C++ fmt just remove all x

DBCStorage <SpellEntryWOTLK> sSpellStoreWOTLK(SpellEntryfmtWOTLK);
DBCStorage <SpellEntryTBC> sSpellStoreTBC(SpellEntryfmtTBC);
DBCStorage <SpellEntryClassic> sSpellStoreClassic(SpellEntryfmtClassic);
DBCStorage <DungeonEncounterEntry> sDungeonEncounterStore(DungeonEncounterFmt);
DBCStorage <FactionEntry> sFactionStore(FactionEntryfmt);
DBCStorage <FactionEntryTBC> sFactionStoreTBC(FactionEntryTBCfmt);
DBCStorage <AreaGroupEntry> sAreaGroupStore(AreaGroupFmt);
