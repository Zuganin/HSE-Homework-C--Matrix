#define CATCH_CONFIG_MAIN


#include <array>
#include <iostream>


#include "rational.h"
#include "rational.h"
#include "matrix.h"
#include "matrix.h"

#include <numeric>
#include <sstream>

void REQUIRE(bool b) {
  if (!b) {
    std::cout << "Wrong answer" << "\n";
  }
}

void REQUIRE_FALSE(bool b) { return REQUIRE(!b); }

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




template <class T, size_t N, size_t M>
void EqualMatrix(const Matrix<T, N, M>& matrix, const std::array<std::array<T, M>, N>& arr) {
    for (size_t i = 0u; i < N; ++i) {
        for (size_t j = 0u; j < M; ++j) {
            std::cout<<(matrix(i, j) == arr[i][j]);
        }
    }
}


#ifdef MATRIX_SQUARE_MATRIX_IMPLEMENTED
int main() {
  {
    Matrix<Rational, 1, 1> matrix{3};
    EqualMatrix(GetInversed(matrix), std::array<std::array<Rational, 1>, 1>{Rational{1, 3}});

    using ReturnType = std::remove_const_t<decltype(GetInversed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<Rational, 1, 1>>));
  }

  {
    Matrix<Rational, 2, 2> matrix{-1, 4, 9, 2};
    EqualMatrix(GetInversed(matrix), std::array<std::array<Rational, 2>, 2>{Rational{-1, 19}, Rational{2, 19},
                                                                            Rational{9, 38}, Rational{1, 38}});

    using ReturnType = std::remove_const_t<decltype(GetInversed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<Rational, 2, 2>>));
  }

  {
    Matrix<Rational, 3, 3> matrix{-1, 4, 9, 2, 5, -7, 0, 2, 0};
    EqualMatrix(GetInversed(matrix), std::array<std::array<Rational, 3>, 3>{
                                         Rational{7, 11}, Rational{9, 11}, Rational{-73, 22}, Rational{0}, Rational{0},
                                         Rational{1, 2}, Rational{2, 11}, Rational{1, 11}, Rational{-13, 22}});

    using ReturnType = std::remove_const_t<decltype(GetInversed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<Rational, 3, 3>>));
  }

  {
    Matrix<Rational, 3, 3> matrix{Rational{1},    Rational{1, 2}, Rational{1, 3}, Rational{1, 4}, Rational{1, 5},
                                  Rational{1, 6}, Rational{1, 7}, Rational{1, 8}, Rational{1, 9}};
    EqualMatrix(GetInversed(matrix), std::array<std::array<Rational, 3>, 3>{
                                         Rational{14, 3}, Rational{-140, 3}, Rational{56}, Rational{-40, 3},
                                         Rational{640, 3}, Rational{-280}, Rational{9}, Rational{-180}, Rational{252}});

    using ReturnType = std::remove_const_t<decltype(GetInversed(matrix))>;
    static_assert((std::is_same_v<ReturnType, Matrix<Rational, 3, 3>>));
  }
}
#endif  // MATRIX_SQUARE_MATRIX_IMPLEMENTED