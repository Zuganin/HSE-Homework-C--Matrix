
#include "rational.h"

#include <iostream>
#include <numeric>

void Rational::SimplifyFraction(int& num, int& denom) {
  int common_divisor = std::gcd(num, denom);
  num /= common_divisor;
  denom /= common_divisor;
  if (denom < 0) {
    num = -num;
    denom = -denom;
  }
}

Rational::Rational(int num, int denom) {
  numerator_ = num;
  CheckDenominator(denom);
  denominator_ = denom;
  SimplifyFraction(numerator_, denominator_);
};

Rational::Rational(int num) {
  numerator_ = num;
  denominator_ = 1;
};

Rational::Rational() {
  numerator_ = 0;
  denominator_ = 1;
};

int32_t Rational::GetNumerator() const { return numerator_; }
int32_t Rational::GetDenominator() const { return denominator_; }

void Rational::SetNumerator(int32_t num) {
  numerator_ = num;
  SimplifyFraction(numerator_, denominator_);
}

void Rational::SetDenominator(int32_t denom) {
  if (denom == 0) {
    throw RationalDivisionByZero{};
  }
  denominator_ = denom;
  SimplifyFraction(numerator_, denominator_);
}

Rational Rational::operator+(const Rational& other) const {
  return {numerator_ * other.denominator_ + other.numerator_ * denominator_,
          denominator_ * other.denominator_};
}

Rational Rational::operator-(const Rational& other) const {
  return {numerator_ * other.denominator_ - other.numerator_ * denominator_,
          denominator_ * other.denominator_};
}

Rational Rational::operator*(const Rational& other) const {
  return {numerator_ * other.numerator_, denominator_ * other.denominator_};
}

Rational Rational::operator/(const Rational& other) const {
  if (other.numerator_ == 0) {
    throw RationalDivisionByZero();
  }
  return {numerator_ * other.denominator_, denominator_ * other.numerator_};
}

Rational& Rational::operator++() {
  numerator_ += denominator_;
  SimplifyFraction(numerator_, denominator_);
  return *this;
}

Rational Rational::operator++(int) {
  Rational temp = *this;
  ++(*this);
  temp.SimplifyFraction(numerator_, denominator_);
  return temp;
}
Rational& Rational::operator--() {
  numerator_ -= denominator_;
  SimplifyFraction(numerator_, denominator_);
  return *this;
}

Rational Rational::operator--(int) {
  Rational temp = *this;
  --(*this);
  temp.SimplifyFraction(numerator_, denominator_);
  return temp;
}

Rational& Rational::operator+=(const Rational& other) {
  *this = *this + other;
  SimplifyFraction(numerator_, denominator_);
  return *this;
}

Rational& Rational::operator-=(const Rational& other) {
  *this = *this - other;
  SimplifyFraction(numerator_, denominator_);
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  *this = *this * other;
  SimplifyFraction(numerator_, denominator_);
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  if (other.numerator_ == 0) {
    throw RationalDivisionByZero();
  }
  *this = *this / other;
  SimplifyFraction(numerator_, denominator_);
  return *this;
}

Rational Rational::operator+() const { return *this; }

Rational Rational::operator-() const { return {-numerator_, denominator_}; }

bool Rational::operator==(const Rational& y) const {
  return (numerator_ == y.numerator_ && denominator_ == y.denominator_);
}

bool Rational::operator!=(const Rational& y) const {
  return (numerator_ != y.numerator_ || denominator_ != y.denominator_);
}

bool operator>(const Rational& x, const Rational& y) {
  return (x.numerator_ * y.denominator_ > y.numerator_ * x.denominator_);
}

bool operator<(const Rational& x, const Rational& y) {
  return (x.numerator_ * y.denominator_ < y.numerator_ * x.denominator_);
}

bool operator>=(const Rational& x, const Rational& y) {
  return (x.numerator_ * y.denominator_ >= y.numerator_ * x.denominator_);
}

bool operator<=(const Rational& x, const Rational& y) {
  return (x.numerator_ * y.denominator_ <= y.numerator_ * x.denominator_);
}

std::ostream& operator<<(std::ostream& ostream, const Rational& x) {
  if (x.denominator_ != 1) {
    ostream << x.numerator_ << '/' << x.denominator_;
  } else {
    ostream << x.numerator_;
  }
  return ostream;
}

std::istream& operator>>(std::istream& istream, Rational& x) {
  std::string slash;
  istream >> slash;

  if (slash.find('/') != std::string::npos) {
    auto chr = slash.find('/');
    x.SetNumerator(std::stoi(slash.substr(0, chr)));

    if (std::stoi(slash.substr(chr + 1, slash.length() - chr - 1)) == 0) {
      throw RationalDivisionByZero();
    }

    x.SetDenominator(
        std::stoi(slash.substr(chr + 1, slash.length() - chr - 1)));
  } else {
    x.SetNumerator(std::stoi(slash));
    x.SetDenominator(1);
  }
  return istream;
}

void Rational::CheckDenominator(int32_t denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }
}
