#ifndef SEARCHLEVEL_H
#define SEARCHLEVEL_H

#include "basesearch.h"

class SearchLevel : public baseSearch
{
public:
    SearchLevel(const MapaObj& map, const std::string& startPoint, const std::string& endPoint);

    virtual ~SearchLevel() override = default;

private:
    virtual void initLoopConditions() override;
    virtual bool extraCoonditionLoopSearch() const override;
    virtual void principalLoopSearch() override;

    std::list<PointConnIter> _startingPath{};
    uint64_t _actuallvlSearch{0};
    const uint64_t _maxlvlSearch{500};
};

#endif // SEARCHLEVEL_H
