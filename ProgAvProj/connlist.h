#ifndef CONNLIST_H
#define CONNLIST_H

#include <vector>
#include <map>
#include <memory>
#include <pointobj.h>

class ConnList
{
public:
    ConnList();


    void connectPoints(std::shared_ptr<PointObj> point, const std::map<uint16_t, uint8_t>& newConns);
    void connectPoints(const uint16_t pointHash, const std::map<uint16_t, uint8_t>& newConns);

    void connectPoints(std::shared_ptr<PointObj> point, const std::vector<std::tuple<uint8_t, uint16_t> > &newConns);

    void connectNewPoint(std::shared_ptr<PointObj> point, std::shared_ptr<PointObj> newPoint, const uint8_t connCost);
    void connectNewPoint(const uint16_t pointHash, std::shared_ptr<PointObj> newPoint, const uint8_t connCost);

    const std::map<uint16_t, uint8_t>& getConnectedMapElem(const uint16_t elemHash) const;
    const std::map<uint16_t, uint8_t>& getConnectedMapElem(std::shared_ptr<PointObj> point) const;

    const std::map<uint16_t, std::map<uint16_t, uint8_t>>& getConnectedMap() const;

private:
    // lets try map for now
    // hash and cost
    std::map<uint16_t, std::map<uint16_t, uint8_t>> _connectedPoints{};
};

#endif // CONNLIST_H
