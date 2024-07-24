In this README file, I want to talk about the task that needed to be completed, my solution (description of the Matrix class) is in the matrix file.h , in main.cpp there are a couple of tests using the rational class from a single task as the main data type (which is also in my repository).

Condition

In this task, you need to implement a template class for working with fixed-size matrices. The latter means that the dimensions of the matrix must be transmitted in the form of template parameters-integers (non-type template parameters),
and for a specific object cannot be changed during the program operation. On the one hand, this imposes restrictions - the size of the matrices must be rigidly set at the compilation stage and the user does not have the opportunity to change it.
In addition, changes to the parameters of the matrices will require a recompilation of the source code using these matrices. On the other hand, since matrix sizes are compile-time constants, we have the opportunity to use non-dynamic arrays (which significantly speeds up work with matrices),
the compiler has more opportunities to optimize the code, and incorrect work with matrices (multiplication of matrices of unsuitable sizes, inversion of non-square matrices, etc.) will be detected even at the stage of program assembly, not during execution.

Implementation Details

It is required to implement the template class Matrix, which takes as template parameters the type of stored elements, the number of rows of the matrix and the number of columns.
Since template parameters are compile-time constants, matrix elements can be stored in a two-dimensional C-style array (std::array is currently prohibited in this task).
This array field must be public for aggregate initialization to work correctly.

To work with the matrix, it is proposed to implement the following methods:
RowsNumber() and ColumnsNumber(), which return the number of rows and columns, respectively;
Operation () ("parentheses") to access the elements of the matrix and the possibility of changing them (think about why not []);
The At method is similar to the previous paragraph, but throws a MatrixOutOfRange exception in case of going beyond the bounds of the matrix;
The GetTransposed(matrix) function, which returns the transposed version of the transmitted matrix;
Operations of addition, subtraction, multiplication of matrices and their assignment versions. Note that these operations are not applicable to any pairs of matrices!;
Operations of multiplication and division by a number (left and right), as well as their assignment versions;
Comparison operations for equality and inequality of two matrices of the same size;
Input operations from the stream and output to the stream.
The Transpose(matrix) function, which transposes the original matrix by changing it (it is clear that only square matrices can be transposed without resizing);
The Trace() function
counting the trace of the matrix;
The Determinant() function
the determinant of the matrix;
GetInversed() functions and Inverse() to reverse the matrices (the first method returns the inverse, and the second modifies the original matrix).
When trying to reverse a degenerate matrix, it is necessary to throw a MatrixIsDegenerateError exception.
