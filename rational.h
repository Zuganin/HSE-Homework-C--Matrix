

#ifndef SEM4_A_RATIONAL_H
#define SEM4_A_RATIONAL_H

#include <cstdint>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {}
};

class Rational {
 private:
  int32_t numerator_{};
  int32_t denominator_{};
  void SimplifyFraction(int& num, int& denom);
  void CheckDenominator(int32_t denominator);

 public:
  Rational(int32_t num, int32_t denom);
  Rational(int32_t num);  // NOLINT
  Rational();

 public:
  [[nodiscard]] int32_t GetNumerator() const;
  [[nodiscard]] int32_t GetDenominator() const;
  void SetNumerator(int32_t num);
  void SetDenominator(int32_t denom);

 public:
  Rational operator+(const Rational& other) const;
  Rational operator-(const Rational& other) const;
  Rational operator*(const Rational& other) const;
  Rational operator/(const Rational& other) const;

  Rational operator-() const;
  Rational operator+() const;

  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);

  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);

  bool operator==(const Rational& y) const;
  bool operator!=(const Rational& y) const;
  friend bool operator>(const Rational& x, const Rational& y);
  friend bool operator<(const Rational& x, const Rational& y);
  friend bool operator>=(const Rational& x, const Rational& y);
  friend bool operator<=(const Rational& x, const Rational& y);

  friend std::ostream& operator<<(std::ostream& ostream, const Rational& x);
  friend std::istream& operator>>(std::istream& istream, Rational& x);
};

#endif  // SEM4_A_RATIONAL_H
