#ifndef JSONOP_H
#define JSONOP_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#include "formatop.h"

class MapaObj;

class JsonOp : public FormatOp
{
    Q_OBJECT
public:
    explicit JsonOp(QObject *parent = nullptr);

private:
    virtual void initialActionsSave() override;
    virtual void createMapHeaderData(const MapaObj& map) override;
    virtual void createPointData(const std::shared_ptr<PointObj>& point) override;
    virtual void createPointConnData(const std::pair<uint16_t, uint8_t>& pointSingleConnData) override;
    virtual void connectPointToItsData() override;
    virtual void connectPointsInMapData() override;
    virtual QByteArray getDataToSave() override;

    virtual bool checkAllKeys() override;

    virtual void initialActions(const QByteArray fileContent) override;

    ///
    /// \brief loadActions
    /// \return In order mapName, mapXSize, mapYSize, newConnList
    ///
    virtual std::tuple<const std::string, const uint8_t,
                       const uint8_t, ConnList> loadActions() override;

private:
    std::unique_ptr<QJsonObject> _obj{nullptr};
    std::unique_ptr<QJsonArray> _objPoints{nullptr};
    std::unique_ptr<QJsonObject> _objSinglePoint{nullptr};
    std::unique_ptr<QJsonArray> _objPointsConn{nullptr};

};

#endif // JSONOP_H
