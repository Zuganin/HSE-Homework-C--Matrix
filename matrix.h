

#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_SQUARE_MATRIX_IMPLEMENTED

#include <stdexcept>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {}
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {}
};

template <class T, size_t Rows, size_t Columns>
class Matrix {
 public:
  T data[Rows][Columns];
  [[nodiscard]] size_t RowsNumber() const { return Rows; }
  [[nodiscard]] size_t ColumnsNumber() const { return Columns; }

  friend Matrix<T, Columns, Rows> GetTransposed(
      const Matrix<T, Rows, Columns>& matrix) {
    Matrix<T, Columns, Rows> transposed;
    for (std::size_t i = 0; i < Rows; ++i) {
      for (std::size_t j = 0; j < Columns; ++j) {
        transposed(j, i) = matrix(i, j);
      }
    }
    return transposed;
  }

  Matrix<T, Rows, Columns> operator+(
      const Matrix<T, Rows, Columns>& other) const {
    const size_t rows = RowsNumber();
    const size_t columns = ColumnsNumber();
    if (rows != other.RowsNumber() || columns != other.ColumnsNumber()) {
      throw std::invalid_argument("Matrices have different size!");
    }
    Matrix<T, Rows, Columns> c;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        c(i, j) = data[i][j] + other(i, j);
      }
    }
    return c;
  }

  Matrix<T, Rows, Columns> operator-(
      const Matrix<T, Rows, Columns>& other) const {
    const size_t rows = RowsNumber();
    const size_t columns = ColumnsNumber();
    if (rows != other.RowsNumber() || columns != other.ColumnsNumber()) {
      throw std::invalid_argument("Matrices have different size!");
    }
    Matrix<T, Rows, Columns> c;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        c(i, j) = data[i][j] - other(i, j);
      }
    }
    return c;
  }

  template <size_t OtherColumns>
  Matrix<T, Rows, OtherColumns> operator*(
      const Matrix<T, Columns, OtherColumns>& other) const {
    Matrix<T, Rows, OtherColumns> result;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < OtherColumns; ++j) {
        result(i, j) = T{};
        for (size_t k = 0; k < Columns; ++k) {
          result(i, j) += data[i][k] * other(k, j);
        }
      }
    }
    return result;
  }

  Matrix<T, Rows, Columns>& operator+=(const Matrix<T, Rows, Columns>& other) {
    const size_t rows = RowsNumber();
    const size_t columns = ColumnsNumber();
    if (rows != other.RowsNumber() || columns != other.ColumnsNumber()) {
      throw std::invalid_argument("Matrices have different size!");
    }
    *this = *this + other;
    return *this;
  }

  Matrix<T, Rows, Columns>& operator-=(const Matrix<T, Rows, Columns>& other) {
    const size_t rows = RowsNumber();
    const size_t columns = ColumnsNumber();
    if (rows != other.RowsNumber() || columns != other.ColumnsNumber()) {
      throw std::invalid_argument("Matrices have different size!");
    }
    *this = *this - other;
    return *this;
  }

  template <size_t OtherColumns>
  Matrix<T, Rows, OtherColumns>& operator*=(
      const Matrix<T, Columns, OtherColumns>& other) {
    const size_t columns = ColumnsNumber();
    if (other.RowsNumber() != columns) {
      throw std::invalid_argument("Matrices have different size!");
    }
    *this = *this * other;
    return *this;
  }

  Matrix<T, Rows, Columns> operator*(const T& scalar) const {
    Matrix<T, Rows, Columns> result;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result(i, j) = data[i][j] * scalar;
      }
    }
    return result;
  }

  friend Matrix<T, Rows, Columns> operator*(
      const T& scalar, const Matrix<T, Rows, Columns>& matrix) {
    return matrix * scalar;
  }

  Matrix<T, Rows, Columns>& operator*=(const T& scalar) {
    *this = *this * scalar;
    return *this;
  }

  Matrix<T, Rows, Columns> operator/(const T& scalar) const {
    Matrix<T, Rows, Columns> result;
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        result(i, j) = data[i][j] / scalar;
      }
    }
    return result;
  }

  friend Matrix<T, Rows, Columns> operator/(
      const T& scalar, const Matrix<T, Rows, Columns>& matrix) {
    return matrix / scalar;
  }

  Matrix<T, Rows, Columns>& operator/=(const T& scalar) {
    return (*this = *this / scalar);
  }

  T& operator()(size_t row, size_t col) { return data[row][col]; }

  const T& operator()(size_t row, size_t col) const { return data[row][col]; }
  T& At(size_t row, size_t col) {
    if (row >= Rows || col >= Columns) {
      throw MatrixOutOfRange();
    }
    return data[row][col];
  }

  const T& At(size_t row, size_t col) const {
    if (row >= Rows || col >= Columns) {
      throw MatrixOutOfRange();
    }
    return data[row][col];
  }

  friend bool operator==(const Matrix& lmatrix, const Matrix& rmatrix) {
    for (std::size_t i = 0; i < Rows; ++i) {
      for (std::size_t j = 0; j < Columns; ++j) {
        if (lmatrix(i, j) != rmatrix(i, j)) {
          return false;
        }
      }
    }
    return true;
  }

  friend bool operator!=(const Matrix& lmatrix, const Matrix& rmatrix) {
    return !(lmatrix == rmatrix);
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        os << matrix(i, j) << (j + 1 == Columns ? "" : " ");
      }
      os << "\n";
    }
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Matrix& matrix) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Columns; ++j) {
        is >> matrix(i, j);
      }
    }
    return is;
  }
};

template <class T, size_t N>
Matrix<T, N, N> Transpose(Matrix<T, N, N>& matrix) {
  Matrix<T, N, N> temp;
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < N; ++j) {
      temp(i, j) = matrix(j, i);
    }
  }
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < N; ++j) {
      matrix(i, j) = temp(i, j);
    }
  }
  return matrix;
}
template <class T, size_t N>
T Trace(const Matrix<T, N, N>& matrix) {
  size_t j = 0;
  T sum = 0;
  for (size_t i = 0; i < N; ++i) {
    sum += matrix(i, j);
    ++j;
  }
  return sum;
}
template <class T, size_t N>
T Determinant(const Matrix<T, N, N>& matrix) {
  Matrix<T, N, N> minor = matrix;
  int dim = N;
  for (int k = 0; k < dim - 1; k++) {
    for (int i = k + 1; i < dim; i++) {
      for (int j = k + 1; j < dim; j++) {
        minor(i, j) = (minor(k, k) * minor(i, j) - minor(i, k) * minor(k, j));
        if (k != 0) {
          minor(i, j) /= minor(k - 1, k - 1);
        }
      }
    }
  }
  return minor(dim - 1, dim - 1);
}
template <class T, size_t N>
void Inverse(Matrix<T, N, N>& matrix) {
  matrix = GetInversed(matrix);
}

template <class T>
Matrix<T, 1, 1> GetInversed(const Matrix<T, 1, 1>& matrix) {
  if (Determinant(matrix) == 0) {
    throw MatrixIsDegenerateError();
  }
  Matrix<T, 1, 1> new_matrix;
  new_matrix.data[0][0] = T{1} / matrix.data[0][0];
  return new_matrix;
}
template <class T>
void Inverse(Matrix<T, 1, 1>& matrix) {
  matrix = GetInversed(matrix);
}

template <class T, size_t N>
Matrix<T, N, N> GetInversed(const Matrix<T, N, N>& matrix)  {
  if (Determinant(matrix) == 0) {
    throw MatrixIsDegenerateError();
  }
  return GetUnionMatrix(matrix) / Determinant(matrix);
}

template <class T, size_t N>
Matrix<T, N, N> GetUnionMatrix(const Matrix<T, N, N>& matrix) {
  Matrix<T, N, N> un{1};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      Matrix<T, N - 1, N - 1> minor = GetMinorMatrix(i, j, matrix);
      un(i, j) = (i + j) % 2 == 0 ? Determinant(minor) : -Determinant(minor);
    }
  }
  return Transpose(un);
}

template <class T, size_t N>
Matrix<T, N - 1, N - 1> GetMinorMatrix(size_t row, size_t col,const
                                       Matrix<T, N, N>& matrix) {
  Matrix<T, N - 1, N - 1> new_matrix;
  size_t new_i = 0;
  for (size_t i = 0; i < N; ++i) {
    if (row == i) {
      continue;
    }
    size_t new_j = 0;
    for (size_t j = 0; j < N; ++j) {
      if (col == j) {
        continue;
      }
      new_matrix.data[new_i][new_j] = matrix.data[i][j];
      ++new_j;
    }
    ++new_i;
  }
  return new_matrix;
}

#endif  // MATRIX_H
