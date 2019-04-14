#ifndef FORMATOP_H
#define FORMATOP_H

#include <QObject>
#include <string>
#include <memory>
#include <pointobj.h>
#include <vector>

class MapaObj;
class ConnList;

class FormatOp : public QObject
{
    Q_OBJECT
public:
    FormatOp(QObject *parent = nullptr);

    bool saveMap(const MapaObj& map, const std::string mapFile);

    MapaObj loadMap(const std::string mapFile);

private:
    QByteArray generateContentToSave(const MapaObj& map);
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

    ///
    /// \brief loadActions
    /// \return In order mapName, mapXSize, mapYSize, newConnList
    ///
    virtual std::tuple<const std::string, const uint8_t,
                       const uint8_t, ConnList> loadActions() = 0;


protected:
    std::unique_ptr<std::vector<std::shared_ptr<PointObj>>> _newPoints{};


};

#endif // FORMATOP_H
