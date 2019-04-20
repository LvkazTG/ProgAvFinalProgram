#ifndef POINTCONNITER_H
#define POINTCONNITER_H

#include <map>


class PointConnIter
{
public:
    PointConnIter(const uint16_t pointHash, const std::map<uint16_t, uint8_t>& pointConns);

    uint16_t getPointHash() const;

    bool isAtEnd() const;
    bool isOnLastValidIter() const;

    bool moveIter(const uint32_t howMuch = 1);
    bool moveNext();

    uint16_t getActualConnHash() const;
    uint16_t getActualConnCost() const;

    void viewAllConnHashes() const;

    bool moveUntilFind(const uint16_t searchPointHash);
    bool moveUntilFind(const uint16_t searchPointHash, const bool reset);

private:
    // This being const interfere with copy constructor
    uint16_t _pointHash{0};

    const std::map<uint16_t, uint8_t>* _conns{};
    std::_Rb_tree_const_iterator<std::pair<const uint16_t, uint8_t>> _actualIter{};
};

#endif // POINTCONNITER_H
