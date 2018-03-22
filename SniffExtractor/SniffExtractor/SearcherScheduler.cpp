#include "SearcherScheduler.h"
#include <thread>
#include <windows.h>

std::string sniffDirs[] =
{
    "D:\\BigData\\sniffs\\tbcv2\\tbc_new\\",
    "D:\\BigData\\sniffs\\2017_03_29_parsed_tbc_sniffs\\",
    "C:\\2017_03_29_parsed_tbc_sniffs\\",
};

#define CHOSEN_DIR 1
#define THREAD_COUNT 8

SearcherScheduler::SearcherScheduler()
{
}


SearcherScheduler::~SearcherScheduler()
{
}

void SearcherScheduler::Start()
{
    GetFileNames(m_filePaths);
    //for (std::string& path : filePaths)
    //    printf("%s\n",path.data());
    std::thread threads[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads[i] = std::thread([this] { this->FileWorker(); });
    }
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads[i].join();
    }
}

void SearcherScheduler::GetFileNames(std::vector<std::string>& filePaths)
{
    int i = 0;
    std::string start = sniffDirs[CHOSEN_DIR] + "*.*";
    std::wstring stemp = std::wstring(start.begin(), start.end());
    LPCWSTR sw = stemp.c_str();
    HANDLE hFind;
    WIN32_FIND_DATA data;
    hFind = FindFirstFile(sw, &data);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            i++;
            if (i < 3)
                continue;
            stemp = data.cFileName;
            std::string tempPosition = std::string(stemp.begin(), stemp.end());
            //std::cout << temp << "\n";
            filePaths.push_back(sniffDirs[CHOSEN_DIR] + tempPosition);
        } while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }
}

void RunSearcher(Searcher* searcher, std::string* buffer)
{
    searcher->RunSearch(*buffer);
}

void SearcherScheduler::FileWorker()
{
    while (1)
    {
        std::string path;
        {
            std::lock_guard<std::mutex> guard(m_locker);
            if (m_arrayPos < m_filePaths.size())
            {
                path = m_filePaths[m_arrayPos];
                m_arrayPos++;
            }
            else
                return;
        }
        printf("Started file %s\n", path.data());
        std::ifstream sniffFile(path);
        sniffFile.seekg(0, std::ios::end);
        size_t size = sniffFile.tellg();
        std::string buffer(size, ' ');
        sniffFile.seekg(0);
        sniffFile.read(&buffer[0], size);
        std::vector<std::thread> threads;
        for (int i = 0; i < m_searchers.size(); i++)
        {
            Searcher *searcher = m_searchers[i];
            threads.push_back(std::move(std::thread(RunSearcher, searcher, &buffer)));
        }
        for (int i = 0; i < threads.size(); i++)
            threads[i].join();
        printf("Finished file %s\n", path.data());
    }
}

void SearcherScheduler::AddSearcher(Searcher *searcher)
{
    m_searchers.push_back(searcher);
}
