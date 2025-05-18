#include <cinttypes>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
class Matrix
{
    public:
        Matrix();
        Matrix(int rows, int columns);
        Matrix(int rows, int columns, std::initializer_list<T> l);
        // Matrix(std::initializer_list<T> l);
        // Matrix(std::initializer_list<std::initializer_list<T>> ll);

        std::vector<T> Data();
        int Rows();
        int Columns();

        T& At(int row, int column);

        // These create copiess rather than references to matrix elements
        std::vector<T> GetRow(int n);
        std::vector<T> GetColumn(int n);

        void InsertRow(int pos, std::vector<T> row);
        void InsertColumn(int pos, std::vector<T> column);


    private:
        int rows_;
        int columns_;
        std::vector<T> data_;
};

template <typename T>
Matrix<T>::Matrix() : rows_ {0}, columns_ {0}, data_ {std::vector<T>()} {}

template <typename T>
Matrix<T>::Matrix(int rows, int columns)
{
    if (rows < 0 || columns < 0)
        throw std::length_error{"Matrix constructor: negative size"};

    rows_ = rows;
    columns_ = columns;
    data_ = std::vector<T>(rows * columns);
}

template <typename T>
Matrix<T>::Matrix(int rows, int columns, std::initializer_list<T> l)
{
    if (rows < 0 || columns < 0)
        throw std::length_error{"Matrix constructor: negative size"};

    if (static_cast<int>(l.size()) != rows * columns)
        throw std::length_error{"Matrix constructor: list does not match matrix size"};

    rows_ = rows;
    columns_ = columns;
    data_ = l;
}

// template <typename T>
// Matrix<T>::Matrix(std::initializer_list<T> l) : columns_(static_cast<int>(l.size())), data_ {l}
// {
//     if (columns_ == 0)
//         rows_ = 0;
//     else
//         rows_ = 1;
// }

// template <typename T>
// Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> ll)
// {
//     unsigned int size = ll[0].size();
//     for (std::initializer_list<T> l : ll)
//     {
//         if (l.size() != size)
//             throw std::length_error{"Matrix constructor: rows differ in length"};
//     }

//     rows_ = static_cast<int>(ll.size());
//     columns_ = static_cast<int>(ll[0].size());

//     for (std::initializer_list<T> l : ll)
//         data_.insert(data_.end(), l.begin(), l.end());
// }

template <typename T>
std::vector<T> Matrix<T>::Data() { return data_; }

template <typename T>
int Matrix<T>::Rows() { return rows_; }

template <typename T>
int Matrix<T>::Columns() { return columns_; }

template <typename T>
T& Matrix<T>::At(int row, int column)
{
    if (row >= 0 && row < rows_ && column >= 0 && column < columns_)
        return data_[row * rows_ + column];
    else
        throw std::out_of_range{""};
}

template <typename T>
std::vector<T> Matrix<T>::GetRow(int n) {
    if (n >= 0 && n < rows_)
        return std::vector<T>(std::next(data_.begin(), (n * columns_)), std::next(data_.begin(), (n * columns_) + columns_));
    else
        throw std::out_of_range{""};
}

template <typename T>
std::vector<T> Matrix<T>::GetColumn(int n)
{
    if (n >= 0 && n < columns_)
    {
        std::vector<T> column;
        column.reserve(columns_);

        // for (typename std::vector<T>::iterator p = data_.begin(); p != data_.end(); p += columns_)
        for (auto p = std::next(data_.begin(), n); p != std::next(data_.end(), n); p = std::next(p, columns_))
            column.push_back(*p);

        return column;
    }
    else
        throw std::out_of_range{""};
}

template <typename T>
void Matrix<T>::InsertRow(int pos, std::vector<T> row)
{
    if (pos < 0 || pos > rows_)
        throw std::out_of_range{""};
    if (row.size() != columns_)
        throw std::length_error{"Input row length does not match matrix row length"};

    auto inner_pos = std::next(data_.begin(), pos * columns_);
    data_.insert(inner_pos, row.begin(), row.end());

    ++rows_;
}

template <typename T>
void Matrix<T>::InsertColumn(int pos, std::vector<T> column)
{
    if (pos < 0 || pos > columns_)
        throw std::out_of_range{""};
    if (column.size() != rows_)
        throw std::length_error{"Input row length does not match matrix row length"};

    // int i = 0;
    // for (T elem : column)
    // {
    //     auto inner_pos = std::next(data_.begin(), (pos + (columns_ * i) + i));
    //     data_.insert(inner_pos, elem);
    //     ++i;
    // }

    for (int i = 0; i != rows_; ++i)
    {
        auto inner_pos = std::next(data_.begin(), (pos + (columns_ * i) + i));
        data_.insert(inner_pos, column[i]);
    }

    ++columns_;
}
