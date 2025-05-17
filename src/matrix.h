#include <initializer_list>
#include <iterator>
#include <utility>
#include <vector>

template <typename T>
class Matrix
{
    public:
        Matrix(int rows, int columns);
        Matrix(std::initializer_list<T> l);
        Matrix(std::initializer_list<std::initializer_list<T>> l);

        T Get(int row, int column);
        void Set(int row, int column, T value);
        int Rows();
        int Columns();

    private:
        int rows_;
        int columns_;
        std::vector<T> data_;
};

template <typename T>
Matrix<T>::Matrix(int rows, int columns) : rows_ {rows}, columns_ {columns}, data_ {std::vector<T>(rows * columns)} {}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<T> l)
{
    
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> l)
{
    
}

template <typename T>
T Matrix<T>::Get(int row, int column)
{
    return data_[row * rows_ + column];
}

template <typename T>
void Matrix<T>::Set(int row, int column, T value)
{
    data_[row * rows_ + column] = value;
}

template <typename T>
int Matrix<T>::Rows() { return rows_; }
template <typename T>
int Matrix<T>::Columns() { return columns_; }


