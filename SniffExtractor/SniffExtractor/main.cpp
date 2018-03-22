#include "SearcherScheduler.h"
#include "PositionSearcher.h"
#include "CreatureTemplateSearcher.h"
#include "CreateObjectSearcher.h"
#include "SpellPacketSearcher.h"

int main()
{
    SearcherScheduler scheduler;
    PositionSearcher posSearch;
    scheduler.AddSearcher(&posSearch);
    scheduler.Start();
    return 0;
}

