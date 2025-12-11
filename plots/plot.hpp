#ifndef PLOT_HPP
#define PLOT_HPP
#include <string>
class item;

class Plot {
public:
    virtual ~Plot() = default;

    virtual std::string symbol() = 0;

    virtual std::string myName() = 0;

    virtual void end_day() = 0;

    virtual int harvest() = 0;

    virtual void water() = 0;

    virtual item *seedPointer() = 0;

    virtual item *producePointer() = 0;

    virtual int seedDrops() = 0;

    virtual int produceDrops() = 0;
};
#endif