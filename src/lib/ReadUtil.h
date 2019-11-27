#ifndef READUTIL_H
#define READUTIL_H
#include <type_traits>
#include <istream>

struct ReadUtil
{
    template <class T, typename std::enable_if<std::is_fundamental<T>::value, int>::type = 0 >
    static std::istream& readLE32Num (std::istream& is, T& x)
    {
        const size_t sz = sizeof(x);
        uint8_t buf;
        buf = is.get();
        if (!is) {
            return is;
        }
        uint32_t *tmp  = reinterpret_cast<uint32_t *>(&x);
        *tmp = buf;

        for (int i = 1; i < sz && is; ++i) {
            buf = is.get();
            *tmp |= ((uint32_t)buf) << (8*i);
        }
        
        return is;
    }
};



#endif

