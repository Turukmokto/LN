#ifndef LAB4
#define LAB4
#include <iostream>
#include <cstdlib>

class LN
{
public:
    LN(const char *x);
    LN(const std::string_view& x);
    LN(const long long& x = 0);

    ~LN();

    LN(const LN &x);
    LN(LN &&x) noexcept;
    LN &operator=(const LN &x);
    LN &operator=(LN &&x) noexcept;

    friend LN operator""_ln(const char *x);

    friend LN operator+(const LN &x, const LN &y);
    friend LN operator-(const LN &x, const LN &y);
    friend LN operator*(const LN &x, const LN &y);
    friend LN operator/(const LN &x, const LN &y);
    friend LN operator%(const LN &x, const LN &y);
    friend LN operator~(const LN &x);

    LN &operator+=(const LN &x);
    LN &operator-=(const LN &x);
    LN &operator*=(const LN &x);
    LN &operator/=(LN &x);
    LN &operator%=(const LN &x);

    friend bool operator>(const LN &x, const LN &y);
    friend bool operator<(const LN &x, const LN &y);
    friend bool operator==(const LN &x, const LN &y);
    friend bool operator!=(const LN &x, const LN &y);
    friend bool operator>=(const LN &x, const LN &y);
    friend bool operator<=(const LN &x, const LN &y);

    friend LN operator-(LN &x);

    explicit operator long long ();
    explicit operator bool () const;

    friend std::ostream& operator<<(std::ostream& os, LN number);

private:
    int size_ = 0;
    int *number_;
    bool sign_ = true;

    static LN rawAdd(const LN& x, const LN& y);
    static LN rawSubtract(const LN& x, const LN& y);

    static LN add(const LN& x, const LN& y);
    static LN subtract(const LN& x, const LN& y);
    static LN multiply(const LN& x, const LN& y);
    static LN divide(LN& x, LN& y);
    static LN mod(const LN& x, const LN& y);
    static LN sqrt(const LN& x);

    static bool eq(const LN& x, const LN& y);
    static bool neq(const LN& x, const LN& y);
    static bool gr(const LN& x, const LN& y);
    static bool ls(const LN& x, const LN& y);
    static bool geq(const LN& x, const LN& y);
    static bool leq(const LN& x, const LN& y);

    static int comparator(const LN& x, const LN& y);

    std::string print();
};

#endif