#ifndef FORMATOP_H
#define FORMATOP_H

#include <QObject>
#include <string>
#include <memory>
#include <vector>

#include "pointobj.h"

class MapaObj;
class ConnList;
class SearchStatistics;

class FormatOp : public QObject
{
    Q_OBJECT
public:
    FormatOp(QObject *parent = nullptr);

    bool saveMap(const MapaObj& map, const std::string& mapFile);

    MapaObj loadMap(const std::string mapFile);

    bool saveStatistics(const SearchStatistics& statObj, const MapaObj& actualMap,
                        const std::string& statFile);

private:
    QByteArray generateContentToSaveMap(const MapaObj& map);
    virtual void initialActionsSave() = 0;
    virtual void createMapHeaderData(const MapaObj& map) = 0;
    virtual void createPointData(const std::shared_ptr<PointObj>& point) = 0;
    virtual void createPointConnData(const std::pair<uint16_t, uint8_t>& pointSingleConnData) = 0;
    virtual void connectPointToItsData() = 0;
    virtual void connectPointsInMapData() = 0;
    virtual QByteArray getDataToSave() = 0;

    MapaObj generateLoadContent(const QByteArray fileContent);
    virtual bool checkAllKeys() = 0;

    virtual void initialActions(const QByteArray fileContent) = 0;

    QByteArray generateContentToSaveStatistics(const SearchStatistics& statObj,
                                               const MapaObj& actualMap);
    virtual void createStatInfo(const SearchStatistics& statObj) = 0;
    virtual void createMapMinimumData(const MapaObj& map) = 0;

    ///
    /// \brief loadActions
    /// \return In order mapName, mapXSize, mapYSize, newConnList
    ///
    virtual std::tuple<const std::string, const uint8_t,
                       const uint8_t, ConnList> loadActions() = 0;

    bool execSaveOperations(const std::string& filename, const QByteArray content) const;

protected:
    std::unique_ptr<std::vector<std::shared_ptr<PointObj>>> _newPoints{};


};

#endif // FORMATOP_H
