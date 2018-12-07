#include "DBCDeclarations.h"
#include "SharedDefines.h"
#include "ProgressBar.h"
#include <stdio.h>
#include <stdlib.h>
#include "DBCExport.h"
#include "Common.h"

static bool ReadDBCBuildFileText(const std::string& dbc_path, char const* localeName, std::string& text)
{
    std::string filename = dbc_path + "component.wow-" + localeName + ".txt";

    if (FILE* file = fopen(filename.c_str(), "rb"))
    {
        char buf[100];
        fread(buf, 1, 100 - 1, file);
        fclose(file);

        text = &buf[0];
        return true;
    }
    else
        return false;
}

static uint32 ReadDBCBuild(const std::string& dbc_path, LocaleNameStr const* localeNameStr = nullptr)
{
    std::string text;

    if (!localeNameStr)
    {
        for (LocaleNameStr const* itr = &fullLocaleNameList[0]; itr->name; ++itr)
        {
            if (ReadDBCBuildFileText(dbc_path, itr->name, text))
            {
                localeNameStr = itr;
                break;
            }
        }
    }
    else
        ReadDBCBuildFileText(dbc_path, localeNameStr->name, text);

    if (text.empty())
        return 0;

    size_t pos = text.find("version=\"");
    size_t pos1 = pos + strlen("version=\"");
    size_t pos2 = text.find("\"", pos1);
    if (pos == text.npos || pos2 == text.npos || pos1 >= pos2)
        return 0;

    std::string build_str = text.substr(pos1, pos2 - pos1);

    int build = atoi(build_str.c_str());
    if (build <= 0)
        return 0;

    return build;
}

struct LocalData
{
    LocalData(uint32 build)
        : main_build(build), availableDbcLocales(0xFFFFFFFF), checkedDbcLocaleBuilds(0) {}

    uint32 main_build;

    // bitmasks for index of fullLocaleNameList
    uint32 availableDbcLocales;
    uint32 checkedDbcLocaleBuilds;
};

#if COMPILER == COMPILER_MICROSOFT
#  define SIZEFMTD "%Iu"
#else
#  define SIZEFMTD "%zu"
#endif

#  define snprintf _snprintf

template<class T>
inline void LoadDBCWotlk(LocalData& localeData, BarGoLink& bar, StoreProblemList& errlist, DBCStorage<T>& storage, const std::string& dbc_path, const std::string& filename)
{
    // compatibility format and C++ structure sizes
    //MANGOS_ASSERT(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()) == sizeof(T) || LoadDBC_assert_print(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()), sizeof(T), filename));

    std::string dbc_filename = dbc_path + filename;
    if (storage.Load(dbc_filename.c_str()))
    {
        bar.step();
        for (uint8 i = 0; fullLocaleNameList[i].name; ++i)
        {
            if (!(localeData.availableDbcLocales & (1 << i)))
                continue;

            LocaleNameStr const* localStr = &fullLocaleNameList[i];

            std::string dbc_dir_loc = dbc_path + localStr->name + "/";

            if (!(localeData.checkedDbcLocaleBuilds & (1 << i)))
            {
                localeData.checkedDbcLocaleBuilds |= (1 << i); // mark as checked for speedup next checks

                uint32 build_loc = ReadDBCBuild(dbc_dir_loc, localStr);
                if (localeData.main_build != build_loc)
                {
                    localeData.availableDbcLocales &= ~(1 << i); // mark as not available for speedup next checks

                                                                 // exist but wrong build
                    if (build_loc)
                    {
                        std::string dbc_filename_loc = dbc_path + localStr->name + "/" + filename;
                        char buf[200];
                        snprintf(buf, 200, " (exist, but DBC locale subdir %s have DBCs for build %u instead expected build %u, it and other DBC from subdir skipped)", localStr->name, build_loc, localeData.main_build);
                        errlist.push_back(dbc_filename_loc + buf);
                    }

                    continue;
                }
            }

            std::string dbc_filename_loc = dbc_path + localStr->name + "/" + filename;
            if (!storage.LoadStringsFrom(dbc_filename_loc.c_str()))
                localeData.availableDbcLocales &= ~(1 << i);// mark as not available for speedup next checks
        }
    }
    else
    {
        // sort problematic dbc to (1) non compatible and (2) nonexistent
        FILE* f = fopen(dbc_filename.c_str(), "rb");
        if (f)
        {
            char buf[100];
            snprintf(buf, 100, " (exist, but have %u fields instead " SIZEFMTD ") Wrong client version DBC file?", storage.GetFieldCount(), strlen(storage.GetFormat()));
            errlist.push_back(dbc_filename + buf);
            fclose(f);
        }
        else
            errlist.push_back(dbc_filename);
    }
}

template<class T>
inline void LoadDBC(uint32& availableDbcLocales, BarGoLink& bar, StoreProblemList& errlist, DBCStorage<T>& storage, const std::string& dbc_path, const std::string& filename, bool vanilla)
{
    // compatibility format and C++ structure sizes
    //MANGOS_ASSERT(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()) == sizeof(T) || LoadDBC_assert_print(DBCFileLoader::GetFormatRecordSize(storage.GetFormat()), sizeof(T), filename));

    std::string dbc_filename = dbc_path + filename;
    if (storage.Load(dbc_filename.c_str()))
    {
        bar.step();
        if (vanilla)
        {
            for (uint8 i = 0; fullLocaleNameListVanilla[i].name; ++i)
            {
                if (!(availableDbcLocales & (1 << i)))
                    continue;

                std::string dbc_filename_loc = dbc_path + fullLocaleNameListVanilla[i].name + "/" + filename;
                if (!storage.LoadStringsFrom(dbc_filename_loc.c_str()))
                    availableDbcLocales &= ~(1 << i);           // mark as not available for speedup next checks
            }
        }
        {
            for (uint8 i = 0; fullLocaleNameList[i].name; ++i)
            {
                if (!(availableDbcLocales & (1 << i)))
                    continue;

                std::string dbc_filename_loc = dbc_path + fullLocaleNameList[i].name + "/" + filename;
                if (!storage.LoadStringsFrom(dbc_filename_loc.c_str()))
                    availableDbcLocales &= ~(1 << i);           // mark as not available for speedup next checks
            }
        }
    }
    else
    {
        // sort problematic dbc to (1) non compatible and (2) nonexistent
        FILE* f = fopen(dbc_filename.c_str(), "rb");
        if (f)
        {
            char buf[100];
            snprintf(buf, 100, " (exist, but have %u fields instead " SIZEFMTD ") Wrong client version DBC file?", storage.GetFieldCount(), strlen(storage.GetFormat()));
            errlist.push_back(dbc_filename + buf);
            fclose(f);
        }
        else
            errlist.push_back(dbc_filename);
    }
}

int main()
{
    std::string dbcPath = "dbc/";
    StoreProblemList bad_dbc_files;

    const uint32 DBCFilesCount = 1;    

    uint32 build = ReadDBCBuild(dbcPath);

    LocalData availableDbcLocalesWOTLK(build);

    BarGoLink bar(DBCFilesCount);
    //LoadDBCWotlk(availableDbcLocalesWOTLK, bar, bad_dbc_files, sSpellStoreWOTLK, dbcPath, "SpellWOTLK.dbc");
    //LoadDBCWotlk(availableDbcLocalesWOTLK, bar, bad_dbc_files, sDungeonEncounterStore, dbcPath, "DungeonEncounter.dbc");
    //LoadDBCWotlk(availableDbcLocalesWOTLK, bar, bad_dbc_files, sFactionStore, dbcPath, "Faction.dbc");
    //LoadDBCWotlk(availableDbcLocalesWOTLK, bar, bad_dbc_files, sAreaGroupStore, dbcPath, "AreaGroup.dbc");

    uint32 availableDbcLocales = 0xFFFFFFFF;
    LoadDBC(availableDbcLocales, bar, bad_dbc_files, sSpellStoreTBC, dbcPath, "SpellTBC.dbc", false);
    //LoadDBC(availableDbcLocales, bar, bad_dbc_files, sSpellStoreClassic, dbcPath, "SpellClassic.dbc", true);
    //LoadDBC(availableDbcLocales, bar, bad_dbc_files, sFactionStoreTBC, dbcPath, "FactionTBC.dbc", false);

    printf("\n");
    DBCExport exporter;
    //exporter.ExportDBCToSQLClassic("spell_template_classic");
    exporter.ExportDBCToSQLTBC("spell_template_tbc");
    //exporter.ExportDBCToSQLWotlk("spell_template_wotlk");
    //exporter.ExportDungeonEncounters("dungeon_encounter_store");
    //exporter.ExportFactionsWOTLK("faction_store");
    //exporter.ExportFactionsTBC("faction_storeTBC");
    //exporter.ExportDBCGeneric("area_group_template", &DBCExport::ExportAreaGroupWotlk);
}