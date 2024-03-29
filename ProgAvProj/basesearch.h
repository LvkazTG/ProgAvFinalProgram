#ifndef BASESEARCH_H
#define BASESEARCH_H

#include <list>

#include "connlist.h"
#include "pointconniter.h"
#include "searchstatistics.h"

class MapaObj;

namespace Search
{
    class BaseSearch
    {
    public:
        BaseSearch(const MapaObj& map);

        virtual ~BaseSearch() = default;

        bool init();

        const SearchStatistics& getSearchStatistics() const;

        const std::string& getSearchType();

        const std::list<PointConnIter>& getBestPath() const;

        uint64_t getBestPathCost() const;

        void definePoints(const uint16_t startP, const uint16_t endP);

        void forceAddBestCost(const uint64_t newBestCost);

    protected:
        void calculateActualCost();
        bool validRoute() const;
        std::tuple<const bool, const bool> validateEnd(const uint16_t pointHash);

        bool _keepSearchGoing{false};
        uint16_t _startHash{0};
        uint16_t _endHash{0};

        std::list<PointConnIter> _actualPath{};
        std::list<PointConnIter> _bestPath{};

        uint64_t _actualPathCost{0};
        uint64_t _bestPathCost{0};

        ConnList const* _connMapList{nullptr};

        SearchStatistics _searchStats{};

        void setSearchType(const std::string& type);

    private:
        virtual void initLoopConditions() = 0;
        virtual bool extraConditionLoopSearch() const = 0;
        virtual void principalLoopSearch() = 0;

        const uint64_t _maxNumIters{250000};
    };
}

#endif // BASESEARCH_H
