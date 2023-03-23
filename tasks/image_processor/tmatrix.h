#ifndef UNTITLED1_TMATRIX_H
#define UNTITLED1_TMATRIX_H

#include <cstddef>
#include <stdexcept>

template <typename T>
class TMatrix {
public:
    using ValueType = T;
    using Pointer = T*;
    using ConstPointer = const T*;
    using Reference = ValueType&;

    class Row {
        friend class TMatrix<T>;

    public:
        T& operator[](size_t colnum) const {
            return matrix_->operator()(rownum_, colnum);
        }

        size_t Size() const {
            return matrix_->GetCollsNum();
        }

    private:
        Row(TMatrix<T>* m, size_t rownum) : rownum_(rownum), matrix_(m) {
        }

    private:
        size_t rownum_;
        TMatrix<T>* matrix_;
    };

    class ConstRow {
        friend class TMatrix<T>;

    public:
        T operator[](size_t colnum) const {
            return matrix_->operator()(rownum_, colnum);
        }

        size_t Size() const {
            return matrix_->cols_num_;
        }

    private:
        ConstRow(const TMatrix<T>* m, size_t rownum) : rownum_(rownum), matrix_(m) {
        }

    private:
        size_t rownum_;
        const TMatrix<T>* matrix_;
    };

    class Col {
        friend class Matrix;

    public:
        T& operator[](size_t rownum) const {
            return matrix_->operator()(rownum, colnum_);
        }

        size_t Size() const {
            return matrix_->rows_num_;
        }

    private:
        Col(TMatrix<T>* m, size_t colnum) : colnum_(colnum), matrix_(m) {
        }

    private:
        size_t colnum_;
        TMatrix<T>* matrix_;
    };

    class ConstCol {
        friend class TMatrix<T>;

    public:
        T operator[](size_t rownum) const {
            return matrix_->operator()(rownum, colnum_);
        }

        size_t Size() const {
            return matrix_->rows_num_;
        }

    private:
        ConstCol(const TMatrix<T>* m, size_t colnum) : colnum_(colnum), matrix_(m) {
        }

    private:
        size_t colnum_;
        const TMatrix<T>* matrix_;
    };

public:
    TMatrix() : table_(nullptr), rows_num_{0}, cols_num_(0) {
    }

    TMatrix(const TMatrix<T>&) = delete;

    TMatrix(size_t rows_num, size_t cols_num, T def = T{}) {
        if (rows_num == 0 && cols_num == 0) {
            rows_num_ = 0;
            cols_num_ = 0;
            table_ = nullptr;
            throw std::invalid_argument("Can't make matrix with 0 rows or columns");
        }

        if (rows_num == 0 || cols_num == 0) {
            throw std::invalid_argument("Can't make matrix with 0 rows or columns");
        }
        rows_num_ = rows_num;
        cols_num_ = cols_num;
        table_ = AllocateMatrix(rows_num_, cols_num_);

        for (size_t i = 0; i < rows_num; ++i) {
            for (size_t j = 0; j < cols_num; ++j) {
                this->operator()(i, j) = def;
            }
        }
    }

    ~TMatrix() {
        Clear();
    }

    T operator()(size_t i, size_t j) const {
        return GetElementByIndex(table_, i, j, cols_num_);
    }

    T& operator()(size_t i, size_t j) {
        return GetElementByIndex(table_, i, j, cols_num_);
    }

    Row operator[](size_t i) {
        TMatrix<T>::Row ri(this, i);
        return ri;
    }

    ConstRow operator[](size_t i) const {
        return ConstRow(this, i);
    };

    T At(size_t i, size_t j) const {
        if (i < rows_num_ && j < cols_num_) {
            return this->operator()(i, j);
        }
        throw std::out_of_range("IOJ (matrix).");
    }

    Reference At(size_t i, size_t j) {
        if (i < rows_num_ && j < cols_num_) {
            return this->operator()(i, j);
        }
        throw std::out_of_range("IOJ (matrix).");
    }

public:
    void Resize(size_t new_col_num, size_t new_row_num, T def = T{}) {
        if (new_col_num == 0 && new_row_num == 0) {
            Clear();
            throw std::invalid_argument("Can't make matrix with 0 rows or columns");
        }
        if (new_row_num == 0 || new_col_num == 0) {
            Clear();
            throw std::invalid_argument("Can't make matrix with 0 rows or columns");
        }

        T* new_table = AllocateMatrix(new_row_num, new_col_num);
        for (size_t i = 0; i < new_row_num; ++i) {
            for (size_t j = 0; j < new_col_num; ++j) {
                if (i < rows_num_ && j < cols_num_) {
                    GetElementByIndex(new_table, i, j, new_col_num) = GetElementByIndex(table_, i, j, cols_num_);
                } else {
                    GetElementByIndex(new_table, i, j, new_col_num) = def;
                }
            }
        }
        delete[] table_;
        table_ = new_table;
        rows_num_ = new_row_num;
        cols_num_ = new_col_num;
    }

    void Clear() {
        if (!table_) {
            return;
        }
        delete[] table_;
        rows_num_ = 0;
        cols_num_ = 0;
    }

    size_t GetRowsNum() const {
        return rows_num_;
    }

    size_t GetCollsNum() const {
        return cols_num_;
    }

    T* GetPtr() {
        return table_;
    }

    const T* GetPtr() const {
        return table_;
    }

    static Reference GetElementByIndex(T* arr, size_t i, size_t j, size_t cols_num) {
        return arr[i * cols_num + j];
    }

private:
    static T* AllocateMatrix(size_t rows_n, size_t cols_m) {
        T* ans = new T[rows_n * cols_m];
        return ans;
    }

private:
    Pointer table_;
    size_t rows_num_;
    size_t cols_num_;
};

#endif
