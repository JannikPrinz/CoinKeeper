#include "DataClasses/value.h"

namespace DataClasses
{
    Value::Value(int32_t vk0, int32_t nk0)
        : VK(vk0), NK(nk0)
    {
    }

    std::string Value::ToString() const
    {
        std::string s = "";
        if (VK < 0 || (VK == 0 && NK < 0)) s.append("-");
        int v = (VK < 0) ? -VK : VK;
        std::string d = "";
        d = std::to_string(v % 10).append(d);
        v /= 10;
        int x = 0;
        while (v > 0)
        {
            if (x == 2) d = std::string(".").append(d);
            d = std::to_string(v % 10).append(d);
            v /= 10;
            x++;
            x %= 3;
        }
        s.append(d);
        s.append(",");
        if (NK < 0)
        {
            if (NK > -10) s.append("0");
            s.append(std::to_string(-NK));
        }
        else
        {
            if (NK < 10) s.append("0");
            s.append(std::to_string(NK));
        }
        return s;
    }

    Value Value::operator +(Value const& a) const
    {
        int v1 = VK;
        int v2 = a.VK;
        int n1 = (VK < 0) ? -NK : NK;
        int n2 = (a.VK < 0) ? -a.NK : a.NK;
        int v = v1 + v2;
        int n = n1 + n2;
        if (n >= 100)
        {
            n -= 100;
            v += 1;
        }
        if (n <= -100)
        {
            n += 100;
            v -= 1;
        }
        if (v >= 0 && n >= 0) return Value(v, n);
        if (v < 0 && n <= 0) return Value(v, -n);
        if (v == 0 && n < 0) return Value(v, n);
        if (v > 0 && n < 0) return Value(v - 1, n + 100);

        // v < 0 && n > 0
        v += 1;
        n = 100 - n;
        if (v == 0) n *= -1;
        return Value(v, n);
    }

    Value Value::operator *(int32_t x) const
    {
        if (x >= 0)
        {
            int y = NK * x;
            return Value(VK * x + (y / 100), y % 100);
        }
        else
        {
            int y = (VK != 0) ? NK * x * (-1) : NK * x;
            return Value(-(VK * (-x) + (y / 100)), y % 100);
        }
    }

    Value Value::operator *=(int32_t x)
    {
        *this = *this * x;
        return *this;
    }

    Value Value::operator +=(Value const& x)
    {
        *this = *this + x;
        return *this;
    }

    Value Value::operator -(Value const& a) const
    {
        return *this + (a * (-1));
    }

    bool Value::operator ==(Value const& a) const
    {
        return VK == a.VK && NK == a.NK;
    }

    bool Value::operator !=(Value const& a) const
    {
        return !(*this == a);
    }

    bool Value::operator <(Value const& a) const
    {
        if (VK < a.VK) return true;
        if (VK == a.VK && NK < a.NK) return true;
        return false;
    }

    bool Value::operator <=(Value const& a) const
    {
        return (*this < a) || (*this == a);
    }

    bool Value::operator >(Value const& a) const
    {
        return !(*this <= a);
    }

    bool Value::operator >=(Value const& a) const
    {
        return !(*this < a);
    }
}
