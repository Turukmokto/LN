#include "LN.h"
#include <cmath>

int LN::comparator(const LN &left, const LN &right)
{
    if (left.sign_ && !right.sign_) {
        return 1;
    }
    if (!left.sign_ && right.sign_) {
        return -1;
    }
    if (left.size_ > right.size_) {
        return !left.sign_ ? -1 : 1;
    }
    if (left.size_ < right.size_) {
        return left.sign_ ? -1 : 1;
    }
    for (int i = left.size_ - 1; i >= 0; i--) {
        if (left.number_[i] > right.number_[i]) {
            return !left.sign_ ? -1 : 1;
        }
        if (left.number_[i] < right.number_[i]) {
            return left.sign_ ? -1 : 1;
        }
    }
    return 0;
}

LN LN::rawAdd(const LN &left, const LN &right) {
    int *a = left.number_, *b = right.number_;
    LN res = LN();
    res.number_ = (int *) malloc(sizeof(int) * (std::max(left.size_, right.size_) + 1));
    if (res.number_ == nullptr) {
        throw "Error occurred when trying to allocate memory";
    }
    int carry = 0, n = 0;
    for (int i = 0; i < std::max(left.size_, right.size_) || carry; ++i) {
        n++;
        res.number_[i] = carry + (i < right.size_ ? b[i] : 0) + (i < left.size_ ? a[i] : 0);
        carry = res.number_[i] >= 10;
        if (carry) {
            res.number_[i] -= 10;
        }
    }
    int length = n;
    for (int i = n - 1; i > -1; --i) {
        if (res.number_[i] == 0) length--;
        else break;
    }
    if (length == 0) {
        LN zero = LN();
        zero.number_ = (int *) malloc(sizeof(int));
        if (zero.number_ == nullptr) {
            throw "Error occurred when trying to allocate memory";
        }
        zero.number_[0] = 0;
        zero.sign_ = true;
        zero.size_ = 1;
        return zero;
    }
    res.sign_ = left.sign_;
    res.size_ = length;
    return res;
}

LN LN::rawSubtract(const LN &left, const LN &right) {
    int *a = left.number_, *b = right.number_;
    LN res = LN();
    res.number_ = (int *) malloc(sizeof(int) * std::max(left.size_, right.size_));
    if (res.number_ == nullptr) {
        throw "Error occurred when trying to allocate memory";
    }
    int carry = 0, n = 0;
    for (int i = 0; i < left.size_ || carry; ++i) {
        n++;
        res.number_[i] = -carry - (i < right.size_ ? b[i] : 0) + (i < left.size_ ? a[i] : 0);
        carry = res.number_[i] < 0;
        if (carry) {
            res.number_[i] += 10;
        }
    }
    int length = n;
    for (int i = n - 1; i > -1; --i) {
        if (res.number_[i] == 0) length--;
        else break;
    }
    if (length == 0) {
        LN zero = LN();
        zero.number_ = (int *) malloc(sizeof(int));
        if (zero.number_ == nullptr) {
            throw "Error occurred when trying to allocate memory";
        }
        zero.number_[0] = 0;
        zero.sign_ = true;
        zero.size_ = 1;
        return zero;
    }
    res.sign_ = left.sign_;
    res.size_ = length;
    return res;
}

LN LN::add(const LN &left, const LN &right) {
    if (left.size_ == 0 or right.size_ == 0) {
        LN res = LN();
        res.size_ = 0;
        res.sign_ = true;
        res.number_ = nullptr;
        return res;
    }
    if (left.sign_ == right.sign_) {
        return rawAdd(left, right);
    } else if (left.sign_ and !right.sign_) {
        LN z = right;
        z.sign_ = true;
        return subtract(left, z);
    } else {
        LN z = left;
        z.sign_ = true;
        return subtract(right, z);
    }
}

LN LN::subtract(const LN &left, const LN &right) {
    if (left.size_ == 0 or right.size_ == 0) {
        LN res = LN();
        res.size_ = 0;
        res.sign_ = true;
        res.number_ = nullptr;
        return res;
    }
    if (left.sign_ xor right.sign_) {
        return rawAdd(left, right);
    } else if (left.sign_ and right.sign_) {
        if (left > right) {
            return rawSubtract(left, right);
        } else {
            LN z = rawSubtract(right, left);
            z.sign_ = false;
            return z;
        }
    } else {
        LN z = right;
        z.sign_ = true;
        return add(left, z);
    }
}

LN LN::multiply(const LN &left, const LN &right) {
    if (left.size_ == 0 or right.size_ == 0) {
        LN res = LN();
        res.size_ = 0;
        res.sign_ = true;
        res.number_ = nullptr;
        return res;
    }
    int *a = left.number_, *b = right.number_;
    LN res = LN();
    res.number_ = (int *) malloc(sizeof(int) * (left.size_ + right.size_));
    if (res.number_ == nullptr) {
        throw "Error occurred when trying to allocate memory";
    }
    for (int i = 0; i < left.size_ + right.size_; ++i) {
        res.number_[i] = 0;
    }
    for (int i = 0; i < left.size_; ++i) {
        for (int j = 0, carry = 0; j < right.size_ || carry; ++j) {
            long long cur = res.number_[i + j] + a[i] * (j < (int) right.size_ ? b[j] : 0) + carry;
            res.number_[i + j] = int(cur % 10);
            carry = int(cur / 10);
        }
    }
    int length = left.size_ + right.size_;
    for (int i = length - 1; i > -1; --i) {
        if (res.number_[i] == 0) length--;
        else {
            break;
        }
    }
    if (length == 0) {
        LN zero = LN();
        zero.number_ = (int *) malloc(sizeof(int));
        if (zero.number_ == nullptr) {
            throw "Error occurred when trying to allocate memory";
        }
        zero.number_[0] = 0;
        zero.size_ = 1;
        zero.sign_ = true;
        return zero;
    }
    res.sign_ = !(left.sign_ xor right.sign_);
    res.size_ = length;
    return res;
}

LN LN::divide(LN &left, LN &right) {
    if (left.size_ == 0 || right.size_ == 0 || right == LN()) {
        LN res = LN();
        res.size_ = 0;
        return res;
    }

    bool fl = false;
    if (!left.sign_) {
        left = -left;
        fl = !fl;
    }
    if (!right.sign_) {
        right = -right;
        fl = !fl;
    }

    long long lhs = 1;
    long long rhs = 1e9;
    LN num = LN();
    while (rhs - lhs > 1) {
        long long mid = (lhs + rhs) / 2;
        num = LN(mid) * right;
        if (num > lhs) {
            rhs = mid;
        } else {
            lhs = mid;
        }
    }
    LN res = LN(lhs);
    if (fl) {
        return -res;
    }
    return LN(lhs);
}

LN LN::mod(const LN &left, const LN &right) {
    return (left - (left / right) * right);
}

LN LN::sqrt(const LN &val) {
    if (!val.sign_) {
        LN res = LN();
        res.size_ = 0;
        res.sign_ = true;
        res.number_ = nullptr;
        return res;
    }
    if (val.size_ == 0) {
        return val;
    }
    LN zero = LN();
    zero.number_ = (int *) malloc(sizeof(int));
    if (zero.number_ == nullptr) {
        throw "Error occurred when trying to allocate memory";
    }
    zero.number_[0] = 0;
    zero.size_ = 1;
    zero.sign_ = true;
    LN left = zero;
    LN right = val;
    LN mid = (left + right) / LN(2);
    while (left < right) {
        if (val < mid * mid) {
            right = mid - LN(1);
        } else {
            left = mid + LN(1);
        }
        mid = (left + right) / LN(2);
    }
    return mid;
}

bool LN::eq(const LN &left, const LN &right) {
    if (left.size_ == 0 or right.size_ == 0) {
        return false;
    }
    return comparator(left, right) == 0;
}

bool LN::neq(const LN &left, const LN &right) {
    if (left.size_ == 0 or right.size_ == 0) {
        return true;
    }
    return comparator(left, right) != 0;
}

bool LN::gr(const LN &left, const LN &right) {
    if (left.size_ == 0 or right.size_ == 0) {
        return false;
    }
    return comparator(left, right) == 1;
}

bool LN::ls(const LN &left, const LN &right) {
    if (left.size_ == 0 or right.size_ == 0) {
        return false;
    }
    return comparator(left, right) < 0;
}

bool LN::geq(const LN &left, const LN &right) {
    if (left.size_ == 0 or right.size_ == 0) {
        return false;
    }
    return (comparator(left, right) > 0) || (comparator(left, right) == 0);
}

bool LN::leq(const LN &left, const LN &right) {
    if (left.size_ == 0 or right.size_ == 0) {
        return false;
    }
    return (comparator(left, right) < 0) || (comparator(left, right) == 0);
}

LN::LN(const long long &right) {
    long long left = right;
    sign_ = left >= 0;
    left = std::abs(left);
    long long temp = left;
    while (std::abs(temp) >= 1) {
        temp /= 10;
        size_++;
    }
    if (left == 0) {
        size_ = 1;
    }
    number_ = (int *) malloc(size_ * sizeof(int));
    if (number_ == nullptr) {
        throw "Error occurred when trying to allocate memory";
    }
    for (int i = 0; i < size_; ++i) {
        number_[i] = left % 10;
        left /= 10;
    }
}

LN::LN(const char *left) {
    char *right = (char *) left;
    sign_ = *right != '-';
    if (!sign_) {
        right++;
    }
    char *temp = right;
    while (*temp != 0) {
        size_++;
        temp++;
    }
    number_ = (int *) malloc(size_ * sizeof(int));
    if (number_ == nullptr) {
        throw "Error occurred when trying to allocate memory";
    }

    for (int i = 0; i < size_; ++i) {
        number_[i] = left[size_ - 1 - i] - 48;
    }
}

LN::LN(const std::string_view &left) {
    if (left == "NaN") {
        sign_ = true;
        size_ = 0;
        return;
    }
    sign_ = left[0] != '-';
    size_ = left.length() - (sign_ ? 0 : 1);
    number_ = (int *) malloc(size_ * sizeof(int));
    if (number_ == nullptr) {
        throw "Error occurred when trying to allocate memory";
    }
    for (int i = 0; i < size_; ++i) {
        number_[i] = left[size_ - 1 - i + (sign_ ? 0 : 1)] - 48;
    }
}

LN operator-(LN &left) {
    LN right = left;
    right.sign_ = !right.sign_;
    return right;
}

LN &LN::operator+=(const LN &left) {
    *this = add(*this, left);
    return *this;
}

LN &LN::operator-=(const LN &left) {
    *this = subtract(*this, left);
    return *this;
}

LN &LN::operator*=(const LN &left) {
    *this = multiply(left, *this);
    return *this;
}

LN &LN::operator/=(LN &left) {
    *this = divide(*this, left);
    return *this;
}

LN &LN::operator%=(const LN &left) {
    *this = mod(*this, left);
    return *this;
}

LN::operator long long() {
    long long left = 0;
    if (size_ == 0) {
        throw "Trying to cast Nan into a long long";
    }
    if (*this > LN(9223372036854775807ll)) {
        throw "Error occurred when trying to allocate memory";
    }
    for (int i = 0; i < size_; ++i) {
        left += number_[i] * (long long) std::pow(10, i);
    }
    return left;
}

LN::operator bool() const {
    if (size_ == 0) {
        throw "Trying to cast Nan into a bool";
    }
    long long temp = 0;
    return *this != LN(temp);
}

LN::~LN() {
    free(number_);
}

LN::LN(LN &&left) noexcept
        : number_(left.number_), size_(left.size_), sign_(left.sign_) {
    left.sign_ = false;
    left.size_ = 0;
    left.number_ = nullptr;
}

LN::LN(const LN &left) {
    size_ = left.size_;
    sign_ = left.sign_;
    number_ = (int *) malloc(sizeof(int) * size_);
    if (number_ == nullptr) {
        throw "Error occurred when trying to allocate memory";
    }
    for (int i = 0; i < size_; ++i) {
        number_[i] = left.number_[i];
    }
}

LN &LN::operator=(const LN &left) {
    if (&left == this) {
        return *this;
    }
    free(number_);
    size_ = left.size_;
    sign_ = left.sign_;
    number_ = (int *) malloc(sizeof(int) * size_);
    if (number_ == nullptr) {
        throw "Error occurred when trying to allocate memory";
    }
    for (int i = 0; i < size_; ++i) {
        number_[i] = left.number_[i];
    }
    return *this;
}

LN &LN::operator=(LN &&left) noexcept {
    number_ = left.number_;
    size_ = left.size_;
    sign_ = left.sign_;
    left.sign_ = false;
    left.size_ = 0;
    left.number_ = nullptr;
    return *this;
}

std::ostream &operator<<(std::ostream &os, LN number) {
    os << number.print();
    return os;
}

std::string LN::print() {
    if (this->size_ == 0) {
        return "NaN";
    }
    std::string ans = "";
    LN zero = LN();
    LN tmp = (this->sign_) ? *this : -*this;
    if (tmp != zero && !this->sign_) {
        ans += '-';
    }
    for (int i = this->size_ - 1; i >= 0; i--) {
        ans += std::to_string(this->number_[i]);
    }
    return ans;
}

LN operator/(const LN &left, const LN &right) {
    if (left.size_ == 0 or right.size_ == 0) {
        LN zero = LN();
        zero.size_ = 0;
        zero.number_ = nullptr;
        zero.sign_ = true;
        return zero;
    }
    LN a = left;
    LN b = right;
    a.sign_ = true;
    b.sign_ = true;
    LN c = LN::divide(a, b);
    c.sign_ = !(left.sign_ xor right.sign_);
    return c;
}

LN operator+(const LN &left, const LN &right) {
    return LN::add(left, right);
}

LN operator-(const LN &left, const LN &right) {
    return LN::subtract(left, right);
}

LN operator*(const LN &left, const LN &right) {
    return LN::multiply(left, right);
}

LN operator/(const LN &left, const LN &right);

LN operator%(const LN &left, const LN &right) {
    return LN::mod(left, right);
}

LN operator~(const LN &left) {
    return LN::sqrt(left);
}

LN operator-(LN &left);

bool operator>(const LN &left, const LN &right) {
    return LN::gr(left, right);
}

bool operator<(const LN &left, const LN &right) {
    return LN::ls(left, right);
}

bool operator==(const LN &left, const LN &right) {
    return LN::eq(left, right);
}

bool operator!=(const LN &left, const LN &right) {
    return LN::neq(left, right);
}

bool operator>=(const LN &left, const LN &right) {
    return LN::geq(left, right);
}

bool operator<=(const LN &left, const LN &right) {
    return LN::leq(left, right);
}

LN operator ""_ln(const char *left) {
    return LN(left);
}