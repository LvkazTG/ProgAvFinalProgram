#ifndef BASESEARCH_H
#define BASESEARCH_H

#include <list>

#include "connlist.h"
#include "pointconniter.h"

class MapaObj;

class baseSearch
{
public:
    baseSearch(const MapaObj& map, const std::string& startPoint, const std::string& endPoint);

    virtual ~baseSearch() = default;

    bool init();


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

private:
    virtual void initLoopConditions() = 0;
    virtual bool extraCoonditionLoopSearch() const = 0;
    virtual void principalLoopSearch() = 0;
};

#endif // BASESEARCH_H
