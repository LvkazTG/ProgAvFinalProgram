#ifndef XMLOP_H
#define XMLOP_H

#include <QObject>
#include <QXmlStreamWriter>

#include "formatop.h"

class MapaObj;

class xmlOp : public FormatOp
{
    Q_OBJECT
public:
    explicit xmlOp(QObject *parent = nullptr);

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

    virtual void createStatInfo(const Search::SearchStatistics& statObj) override;
    virtual void createMapMinimumData(const MapaObj& map) override;

    ///
    /// \brief loadActions
    /// \return In order mapName, mapXSize, mapYSize, newConnList
    ///
    virtual std::tuple<const std::string, const uint8_t,
                       const uint8_t, ConnList> loadActions() override;


private:
    std::unique_ptr<QByteArray> _contentBuffer{nullptr};
    std::unique_ptr<QXmlStreamWriter> _xmlWriter{nullptr};
    std::unique_ptr<QXmlStreamReader> _xmlReader{nullptr};


};

#endif // XMLOP_H
