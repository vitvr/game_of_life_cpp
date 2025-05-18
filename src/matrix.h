#include <cinttypes>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
class Matrix
{
    public:
        Matrix(int rows, int columns);
        Matrix(std::initializer_list<T> l);
        Matrix(std::initializer_list<std::initializer_list<T>> ll);

        T At(int row, int column);
        
        std::vector<T> Data();
        std::vector<T> GetRow(int n);
        std::vector<T> GetColumn(int n);
        // void InsertRow(std::vector<T> row);
        // void InsertColumn(std::vector<T> column);

        int Rows();
        int Columns();

    private:
        int rows_;
        int columns_;
        std::vector<T> data_;
};

template <typename T>
Matrix<T>::Matrix(int rows, int columns)
{
    if (rows < 0 || columns <0)
        throw std::length_error{"Matrix constructor: negative size"};

    rows_ = rows;
    columns_ = columns;
    data_ = std::vector<T>(rows * columns);
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<T> l) : columns_(static_cast<int>(l.size())), data_ {l}
{
    if (columns_ == 0)
        rows_ = 0;
    else
        rows_ = 1;
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> ll)
{
    unsigned int size = ll[0].size();
    for (std::initializer_list<T> l : ll)
    {
        if (l.size() != size)
            throw std::length_error{"Matrix constructor: rows differ in length"};
    }

    rows_ = static_cast<int>(ll.size());
    columns_ = static_cast<int>(ll[0].size());

    for (std::initializer_list<T> l : ll)
        data_.insert(data_.end(), l.begin(), l.end());
}

template <typename T>
T Matrix<T>::At(int row, int column)
{
    if (row >= 0 && row < rows_ && column >= 0 && column < columns_)
        return data_[row * rows_ + column];
    else
        throw std::out_of_range{""};
}

template <typename T>
std::vector<T> Matrix<T>::Data() { return data_; }

template <typename T>
std::vector<T> Matrix<T>::GetRow(int n) {
    if (n >= 0 && n < rows_)
        return std::vector<T>(data_.begin() + (n * columns_), data_.begin() + (n * columns_) + columns_);
    else
        throw std::out_of_range{""};
}

template <typename T>
std::vector<T> Matrix<T>::GetColumn(int n)
{
    if (n >= 0 && n < rows_)
    {
        std::vector<T> column(columns_);

        // for (typename std::vector<T>::iterator p = data_.begin(); p != data_.end(); p += columns_)
        for (auto p = data_.begin(); p != data_.end(); p += columns_)
            column.push_back(*p);
        return column;
    }
    else
        throw std::out_of_range{""};
}

template <typename T>
int Matrix<T>::Rows() { return rows_; }

template <typename T>
int Matrix<T>::Columns() { return columns_; }

// template <typename T>
// void Matrix<T>::InsertRow(std::vector<T> row)
// {
//     if (row.size() == columns_)
//     {
//         return
//     }
// }
