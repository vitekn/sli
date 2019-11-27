#ifndef MACHINECOMMANDS_H
#define MACHINECOMMANDS_H

#include "Point.h"
#include <ostream>

class MachineCommand
{
public:
    virtual void print(std::ostream& os) = 0;


    static void printIntAsF(std::ostream& os, int64_t v)
    {
        os << v/1000;
        int dec = v%1000;
        if (dec) {
            os << '.';
            if (dec < 100) {
                os << '0';
            }
            if (dec < 10) {
                os << '0';
            }
            while (dec%10 == 0) {
                dec/=10;
            }
            os << dec;
        }
    }
};

class ExtrudeCommand : public MachineCommand
{
public:
    
    ExtrudeCommand (int64_t l, int eNum)
    :_l(l)
    ,_eNum(eNum)
    {}
    
    void print(std::ostream& os) override
    {
        os << 'E';
        MachineCommand::printIntAsF(os, _l);
    }
    
private:
    int64_t _l;
    int     _eNum;
};

class MoveCommand : public MachineCommand
{
public:
    MoveCommand (const Point& p, int mt = 0): _p(p), _mt(mt){}
    
    void print(std::ostream& os) override
    {
        _c = 0;
        os << 'G' << _mt << ' ';
        print(os, _p.x, 'X');
        print(os, _p.y, 'Y');
        print(os, _p.z, 'Z');
    }
    
private:
    
    void print(std::ostream& os, int64_t v, char d)
    {
        if (v != Point::NO_VALUE) {
            if (_c) {
                os << ' ';
            }
            os << d;
            MachineCommand::printIntAsF(os, v);
            ++_c;
        }
    }
    
    Point _p;
    int   _mt;
    int   _c;
};

template <class C1, class C2>
class CommandCombination : public MachineCommand
{
public:
    CommandCombination(const C1& c1, const C2& c2)
    : _c1(c1)
    , _c2(c2)
    {}
    
    void print(std::ostream & os) override
    {
        _c1.print(os);
        os << " ";
        _c2.print(os);
    }
    
private:
    C1 _c1;
    C2 _c2;
};

template <class C1, class C2>
CommandCombination<C1, C2> operator+(const C1& c1, const C2& c2)
{
    return CommandCombination<C1, C2>(c1, c2);
}

#endif

