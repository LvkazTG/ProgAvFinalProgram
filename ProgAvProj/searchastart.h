#ifndef SEARCHASTART_H
#define SEARCHASTART_H

#include "basesearch.h"

namespace Search
{
    class SearchAStart : public BaseSearch
    {
    public:
        SearchAStart(const MapaObj& map);

        virtual ~SearchAStart() override = default;

    private:
        virtual void initLoopConditions() override;
        virtual bool extraConditionLoopSearch() const override;
        virtual void principalLoopSearch() override;

        uint64_t calcHeuristicAStar(const uint16_t pointHash) const;
        void updateBestPath(const uint16_t lastPointHash, const uint64_t expectedTotalCost);

        const MapaObj* _mapInUse{nullptr};

        std::map<uint16_t, std::tuple<uint64_t, uint16_t>> _visitedPoints{};
        std::multimap<uint64_t, std::tuple<uint16_t, uint64_t, uint16_t>> _toCheckPoints{};
    };
}

#endif // SEARCHASTART_H
