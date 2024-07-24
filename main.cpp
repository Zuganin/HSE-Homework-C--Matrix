#define CATCH_CONFIG_MAIN

#include <array>
#include <iostream>

// In this task, we used the rational class from the previous task as the main data type our matrix.
#include "rational.h"
#include "matrix.h"


#include <numeric>
#include <sstream>

void REQUIRE(bool b) {
  if (!b) {
    std::cout << "Wrong answer" << "\n";
  }
}

void REQUIRE_FALSE(bool b) { return REQUIRE(!b); }

template <class T, size_t N, size_t M>
void EqualMatrix(const Matrix<T, N, M>& matrix, const std::array<std::array<T, M>, N>& arr) {
    for (size_t i = 0u; i < N; ++i) {
        for (size_t j = 0u; j < M; ++j) {
            std::cout<<(matrix(i, j) == arr[i][j]);
        }
    }
}

//Some of the tests to check the health of the code

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