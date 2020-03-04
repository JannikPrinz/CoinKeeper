#pragma once

#include <string>

namespace DataClasses
{
    class Value
    {
    public:
        /*
         * Creates a new instance with the given parameters.
         *
         * Parameters:
         * int vk0 : value before the comma (default = 0)
         * int nk0 : value after the comma. Should be >= 0 and < 100 (default = 0)
         */
        Value(int32_t vk0 = 0, int32_t nk0 = 0);

        std::string ToString() const;

        Value operator +(Value const& a) const;

        Value operator *(int32_t x) const;

        Value operator *=(int32_t x);

        Value operator +=(Value const& x);

        Value operator -(Value const& a) const;

        bool operator ==(Value const& a) const;

        bool operator !=(Value const& a) const;

        bool operator <(Value const& a) const;

        bool operator <=(Value const& a) const;

        bool operator >(Value const& a) const;

        bool operator >=(Value const& a) const;

    public:
        int32_t VK;
        int32_t NK;
    };
}
