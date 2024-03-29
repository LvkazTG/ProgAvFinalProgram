#ifndef SEARCHSTATISTICS_H
#define SEARCHSTATISTICS_H

#include <QDateTime>
#include <set>
#include <vector>


namespace Search
{
    class BaseSearch;

    class SearchStatistics
    {
        friend class BaseSearch;
    public:
        void addNewPointVisited(const uint16_t newPoint);

        void addIter();
        void addNewPathCost(const uint64_t newCost);

        int64_t getSearchTotalTime() const;
        int64_t getSearchTimeAfterStart() const;

        int64_t getNumIters() const;

        void addSearchMethodName(const std::string& newSearch);
        const std::string& getSearchMethodName() const;

        uint64_t getMaxPathCost() const;
        uint64_t getMinPathCost() const;
        uint64_t getNumPathsFound() const;
        uint64_t getMedPathCost() const;

    private:
        std::vector<uint64_t> _pathCostsFound{};
        std::set<uint16_t> _visitedPoints{};
        uint64_t _numIters{0};
        int64_t _searchStartTime{};
        int64_t _searchEndTime{};
        std::string _searchMethod{};

        SearchStatistics();

        void startSearchtime();
        void endSearchTime();

        void clear();

        void setSearchMethodName(const std::string& newName);

    };
}

#endif // SEARCHSTATISTICS_H
