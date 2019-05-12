#ifndef SEARCHGRAPHPLANADAPT_H
#define SEARCHGRAPHPLANADAPT_H

#include "basesearch.h"

#include <set>

class SearchGraphplanAdapt : public BaseSearch
{
public:
    SearchGraphplanAdapt(const MapaObj& map);

    virtual ~SearchGraphplanAdapt() override = default;

private:
    virtual void initLoopConditions() override;
    virtual bool extraCoonditionLoopSearch() const override;
    virtual void principalLoopSearch() override;

    void backTrackPath();
    void backtrackFirstRoute();

    std::set<uint16_t> _allVisitedPoints{};
    std::list<std::set<uint16_t>> _newStatesPerIter{};
//    std::list<decltype(_allVisitedPoints)> _newStatesPerIter{};

    uint64_t _limitSearchLayer{1000};
};


#endif // SEARCHGRAPHPLANADAPT_H
