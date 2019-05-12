#ifndef SEARCHDEEP_H
#define SEARCHDEEP_H

#include "basesearch.h"

class SearchDeep : public BaseSearch
{
public:
    SearchDeep(const MapaObj& map);

    virtual ~SearchDeep() override = default;

private:
    virtual void initLoopConditions() override;
    virtual bool extraCoonditionLoopSearch() const override;
    virtual void principalLoopSearch() override;

    bool _previousError{false};
    bool _popLastElem{false};
};

#endif // SEARCHDEEP_H
