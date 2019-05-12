#ifndef SEARCHASTART_H
#define SEARCHASTART_H

#include "basesearch.h"

class searchAStart : public BaseSearch
{
public:
    searchAStart(const MapaObj& map, const std::string& startPoint,
                 const std::string& endPoint);

    virtual ~searchAStart() override = default;

private:
    virtual void initLoopConditions() override;
    virtual bool extraCoonditionLoopSearch() const override;
    virtual void principalLoopSearch() override;

    uint64_t calcHeuristicAStar(const uint16_t pointHash) const;
    void updateBestPath(const uint16_t lastPointHash, const uint64_t expectedTotalCost);

    const MapaObj* _mapInUse{nullptr};

    std::map<uint16_t, std::tuple<uint64_t, uint16_t>> _visitedPoints{};
    std::multimap<uint64_t, std::tuple<uint16_t, uint64_t, uint16_t>> _toCheckPoints{};
};

#endif // SEARCHASTART_H
