#ifndef SEARCHCONTROL_H
#define SEARCHCONTROL_H

#include <basesearch.h>
#include <mapaobj.h>

namespace Search
{
    class SearchControl
    {
    public:
        static SearchControl& getInstance();

        template<typename T>
        void createSearchType(const MapaObj& map)
        {
            _searchMethod = _searchMethod = std::make_shared<T>(map);
        }

        std::shared_ptr<BaseSearch>& getSearch();
         const SearchStatistics& getSearchStatisticsObj() const;

    private:
        std::shared_ptr<BaseSearch> _searchMethod{nullptr};

        SearchControl();
    };
}

#endif // SEARCHCONTROL_H
