#pragma once
#include <vector>
#include <thread>
#include "Searcher.h"
class SearcherScheduler
{
public:
    SearcherScheduler();
    ~SearcherScheduler();

    void Start();
    void RunSearchers();

    void GetFileNames(std::vector<std::string>& filePaths);

    void FileWorker();

    void AddSearcher(Searcher *searcher);

private:
    std::vector<Searcher*> m_searchers;

    std::mutex m_locker;
    std::size_t m_arrayPos = 0;
    std::vector<std::string> m_filePaths;
};

