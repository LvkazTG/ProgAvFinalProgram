#include "searchcontrol.h"

using namespace Search;

SearchControl &SearchControl::getInstance()
{
    static SearchControl instance{SearchControl{}};

    return instance;
}

std::shared_ptr<Search::BaseSearch>& SearchControl::getSearch()
{
    return _searchMethod;
}

const Search::SearchStatistics &Search::SearchControl::getSearchStatisticsObj() const
{
    return _searchMethod->getSearchStatistics();
}

SearchControl::SearchControl()
{
}


