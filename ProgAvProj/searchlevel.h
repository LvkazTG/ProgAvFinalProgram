#ifndef SEARCHLEVEL_H
#define SEARCHLEVEL_H

#include "basesearch.h"

namespace Search
{
    class SearchLevel : public BaseSearch
    {
    public:
        SearchLevel(const MapaObj& map);

        virtual ~SearchLevel() override = default;

    private:
        virtual void initLoopConditions() override;
        virtual bool extraConditionLoopSearch() const override;
        virtual void principalLoopSearch() override;

        std::list<PointConnIter> _startingPath{};
        uint64_t _actuallvlSearch{0};
        const uint64_t _maxlvlSearch{500};
    };
}

#endif // SEARCHLEVEL_H
