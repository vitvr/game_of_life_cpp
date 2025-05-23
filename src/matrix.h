#ifndef LIFE_MATRIX_H_
#define LIFE_MATRIX_H_

#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <vector>

template <typename T>
class Matrix
{
    public:
        Matrix();
        Matrix(int rows, int columns);
        Matrix(int rows, int columns, std::initializer_list<T> l);
        template<class It>
            requires std::convertible_to<typename std::iter_value_t<It>, T>
        Matrix(int rows, int columns, It first, It last);
        // Matrix(int rows, int columns
        // Matrix(std::initializer_list<T> l);
        // Matrix(std::initializer_list<std::initializer_list<T>> ll);

        std::vector<T> Data() const;
        int Rows() const;
        int Columns() const;

        bool empty() const;
        typename std::vector<T>::iterator begin();
        typename std::vector<T>::iterator end();

        // T& At(int row, int column);
        T Get(int row, int column);
        void Set(int row, int column, T elem);

        // These create copies rather than references to matrix elements
        std::vector<T> GetRow(int n);
        std::vector<T> GetSubRow(int n, int pos, int length);
        std::vector<T> GetColumn(int n);
        std::vector<T> GetSubColumn(int n, int pos, int length);
        
        void SetSubRow(int n, int pos, std::vector<T> row);
        
        void InsertRow(int pos, std::vector<T> row);
        void InsertColumn(int pos, std::vector<T> column);

        void RemoveRow(int n);
        void RemoveColumn(int n);

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

    if ((rows == 0 && columns != 0) || (rows != 0 && columns == 0))
        throw std::length_error{"Matrix constructor: cannot have rows when there are 0 columns and vice versa"};

    rows_ = rows;
    columns_ = columns;
    data_ = std::vector<T>(rows * columns);
}

template <typename T>
Matrix<T>::Matrix(int rows, int columns, std::initializer_list<T> l)
{
    if (rows < 0 || columns < 0)
        throw std::length_error{"Matrix constructor: negative size"};

    if ((rows == 0 && columns != 0) || (rows != 0 && columns == 0))
        throw std::length_error{"Matrix constructor: cannot have rows when there are 0 columns and vice versa"};

    if (static_cast<int>(l.size()) != rows * columns)
        throw std::length_error{"Matrix constructor: list does not match matrix size"};

    rows_ = rows;
    columns_ = columns;
    data_ = l;
}
template<typename T>
template<class It>
    requires std::convertible_to<typename std::iter_value_t<It>, T>
Matrix<T>::Matrix(int rows, int columns, It first, It last)
{
    if (rows < 0 || columns < 0)
        throw std::length_error{"Matrix constructor: negative size"};

    if ((rows == 0 && columns != 0) || (rows != 0 && columns == 0))
        throw std::length_error{"Matrix constructor: cannot have rows when there are 0 columns and vice versa"};

    std::vector<T> data {};
    data.reserve(rows * columns);
    for (It p = first; p != last; p = std::next(p))
    {
        data.push_back(*p);
    }

    if (data.size() != rows * columns)
        throw std::length_error{"Matrix constructor: list does not match matrix size"};

    rows_ = rows;
    columns_ = columns;
    data_ = data;
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
std::vector<T> Matrix<T>::Data() const { return data_; }

template <typename T>
int Matrix<T>::Rows() const { return rows_; }

template <typename T>
int Matrix<T>::Columns() const { return columns_; }

template <typename T>
bool Matrix<T>::empty() const { return data_.empty(); }

template <typename T>
typename std::vector<T>::iterator Matrix<T>::begin() { return data_.begin(); }

template <typename T>
typename std::vector<T>::iterator Matrix<T>::end() { return data_.end(); }

// template <typename T>
// T& Matrix<T>::At(int row, int column)
// {
//     if (row < 0 || row >= rows_ || column < 0 || column >= columns_)
//         throw std::out_of_range{""};

//     return data_[row * columns_ + column];
// }

template <typename T>
T Matrix<T>::Get(int row, int column)
{
    if (row < 0 || row >= rows_ || column < 0 || column >= columns_)
        throw std::out_of_range{"Matrix<T>::Get(int, int), out of range"};

    return data_[row * columns_ + column];
}

template <typename T>
void Matrix<T>::Set(int row, int column, T elem)
{
    if (row < 0 || row >= rows_ || column < 0 || column >= columns_)
        throw std::out_of_range{"Matrix<T>::Set(int, int, T), out of range"};

    data_[row * columns_ + column] = elem;
}

template <typename T>
std::vector<T> Matrix<T>::GetRow(int n)
{
    if (n < 0 || n >= rows_)
        throw std::out_of_range{"Matrix<T>::GetRow(int), out of range"};

    return std::vector<T>(std::next(data_.begin(), (n * columns_)), std::next(data_.begin(), (n * columns_) + columns_));
}

template <typename T>
std::vector<T> Matrix<T>::GetSubRow(int n, int pos, int length)
{
    if (n < 0 || n >= rows_)
        throw std::out_of_range{"Matrix<T>::GetSubRow(n, pos, length), n out of range"};

    if (pos < 0 || pos > columns_ || length < 0 || length > (columns_ - pos))
        throw std::out_of_range{"Matrix<T>::GetSubRow(n, pos, length), pos or length out of range"};

    return std::vector<T>(std::next(data_.begin(), (n * columns_) + pos), std::next(data_.begin(), (n * columns_) + pos + length));
}

template <typename T>
std::vector<T> Matrix<T>::GetColumn(int n)
{
    if (n < 0 || n >= columns_)
        throw std::out_of_range{""};
    
    std::vector<T> column;
    column.reserve(columns_);

    // for (typename std::vector<T>::iterator p = data_.begin(); p != data_.end(); p += columns_)
    for (auto p = std::next(data_.begin(), n); p != std::next(data_.end(), n); p = std::next(p, columns_))
        column.push_back(*p);

    return column;
}

template <typename T>
std::vector<T> Matrix<T>::GetSubColumn(int n, int pos, int length)
{
    if (n < 0 || n >= columns_)
        throw std::out_of_range{""};

    if (pos < 0 || pos > rows_ || length < 0 || length > (rows_ - pos))
        throw std::out_of_range{""};

    if (length == 1)
        return std::vector<T>({data_[pos * columns_ + n]});

    std::vector<T> column;
    column.reserve(length);

    for (auto p = std::next(data_.begin(), n + (columns_ * pos)); p != std::next(data_.begin(), n + (columns_ * (pos + length))); p = std::next(p, columns_))
        column.push_back(*p);

    return column;
}

template <typename T>
void Matrix<T>::SetSubRow(int n, int pos, std::vector<T> row)
{
    if (n < 0 || n >= rows_)
        throw std::out_of_range{"Matrix<T>::SetSubRow(n, pos, row), n out of range"};

    if (pos < 0 || pos >= columns_ || row.size() < 0 || row.size() > (columns_ - pos))
        throw std::out_of_range{"Matrix<T>::SetSubRow(n, pos, row), pos or row.size() out of range"};

    for (int i = 0; i != row.size(); ++i)
        Set(n, pos + i, row[i]);
}

template <typename T>
void Matrix<T>::InsertRow(int pos, std::vector<T> row)
{
    if (row.empty())
        throw std::length_error{"Input row is empty"};

    if (pos < 0 || pos > rows_)
        throw std::out_of_range{"Matrix<T>::InsertRow(pos, row), pos out of range"};
    
    if (data_.empty())
    {
        rows_ = 1;
        columns_ = row.size();
        data_ = row;

        return;
    }

    if (row.size() != columns_)
        throw std::length_error{"Input row length does not match matrix row length"};

    auto inner_pos = std::next(data_.begin(), pos * columns_);
    data_.insert(inner_pos, row.begin(), row.end());

    ++rows_;
}

template <typename T>
void Matrix<T>::InsertColumn(int pos, std::vector<T> column)
{
    if (column.empty())
        throw std::length_error{"Input column is empty"};

    if (pos < 0 || pos > columns_)
        throw std::out_of_range{"Matrix<T>::InsertColumn(pos, row), pos out of range"};

    if (data_.empty())
    {
        columns_ = 1;
        rows_ = column.size();
        data_ = column;

        return;
    }
    
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

template <typename T>
void Matrix<T>::RemoveRow(int n)
{
    if (n < 0 || n >= rows_)
        throw std::out_of_range{""};

    data_.erase(std::next(data_.begin(), (n * columns_)), std::next(data_.begin(), (n * columns_) + columns_));
    
    --rows_;
}

template <typename T>
void Matrix<T>::RemoveColumn(int n)
{
    if (n < 0 || n >= columns_)
        throw std::out_of_range{""};

    for (int i = 0; i != rows_; ++i)
    {
        auto inner_pos = std::next(data_.begin(), (n + (columns_ * i) - i));
        data_.erase(inner_pos);
    }

    --columns_;
}

#endif
