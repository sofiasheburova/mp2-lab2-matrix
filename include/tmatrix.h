// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <utility> 
#include <limits>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0 || sz > static_cast<size_t>(MAX_VECTOR_SIZE))
            throw out_of_range("Vector size should be greater than zero and less than MAX_VECTOR_SIZE");
        pMem = new T[sz]();
    }

    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz == 0 || sz > static_cast<size_t>(MAX_VECTOR_SIZE))
            throw out_of_range("Vector size invalid");
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz)
    {
        if (sz == 0 || sz > static_cast<size_t>(MAX_VECTOR_SIZE))
            throw out_of_range("Vector size invalid");
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVector(TDynamicVector&& v) noexcept : sz(0), pMem(nullptr)
    {
        swap(*this, v);
    }

    ~TDynamicVector()
    {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            TDynamicVector temp(v);
            swap(*this, temp);
        }
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v)
            swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; ++i)
            if (!(pMem[i] == v.pMem[i])) return false;
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; ++i) res.pMem[i] = pMem[i] + val;
        return res;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; ++i) res.pMem[i] = pMem[i] - val;
        return res;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; ++i) res.pMem[i] = pMem[i] * val;
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw length_error("Vectors must be same size for addition");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; ++i) res.pMem[i] = pMem[i] + v.pMem[i];
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw length_error("Vectors must be same size for subtraction");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; ++i) res.pMem[i] = pMem[i] - v.pMem[i];
        return res;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz) throw length_error("Vectors must be same size for dot product");
        T sum = T();
        for (size_t i = 0; i < sz; ++i) sum += pMem[i] * v.pMem[i];
        return sum;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' ';
        return ostr;
    }
};


// Динамическая матрица - шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz == 0 || sz > static_cast<size_t>(MAX_MATRIX_SIZE))
            throw out_of_range("Matrix size should be greater than zero and less than MAX_MATRIX_SIZE");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    TDynamicMatrix(const TDynamicMatrix& m) : TDynamicVector<TDynamicVector<T>>(m.sz)
    {
        for (size_t i = 0; i < sz; ++i)
            pMem[i] = m.pMem[i];
    }

    TDynamicMatrix(TDynamicMatrix&& m) noexcept : TDynamicVector<TDynamicVector<T>>(0)
    {
        swap(*this, m);
    }

    ~TDynamicMatrix() = default;

    TDynamicMatrix& operator=(const TDynamicMatrix& m)
    {
        if (this != &m) {
            TDynamicMatrix temp(m);
            swap(*this, temp);
        }
        return *this;
    }

    TDynamicMatrix& operator=(TDynamicMatrix&& m) noexcept
    {
        if (this != &m)
            swap(*this, m);
        return *this;
    }


    size_t size() const noexcept { return sz; }


    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m);
    }

    friend void swap(TDynamicMatrix& lhs, TDynamicMatrix& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];


    TDynamicVector<T>& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Matrix index out of range");
        return pMem[ind];
    }

    const TDynamicVector<T>& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Matrix index out of range");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; ++i)
            if (!(pMem[i] == m.pMem[i])) return false;
        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i)
            for (size_t j = 0; j < sz; ++j)
                res[i][j] = pMem[i][j] * val;
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (v.size() != sz) throw length_error("Vector size must equal matrix size for multiplication");
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; ++i) {
            T sum = T();
            for (size_t j = 0; j < sz; ++j)
                sum += pMem[i][j] * v[j];
            res[i] = sum;
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw length_error("Matrix sizes must be equal for addition");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i)
            for (size_t j = 0; j < sz; ++j)
                res[i][j] = pMem[i][j] + m.pMem[i][j];
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw length_error("Matrix sizes must be equal for subtraction");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i)
            for (size_t j = 0; j < sz; ++j)
                res[i][j] = pMem[i][j] - m.pMem[i][j];
        return res;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw length_error("Matrix sizes must be equal for multiplication");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i) {
            for (size_t j = 0; j < sz; ++j) {
                T sum = T();
                for (size_t k = 0; k < sz; ++k)
                    sum += pMem[i][k] * m.pMem[k][j];
                res[i][j] = sum;
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i)
            for (size_t j = 0; j < v.sz; ++j)
                istr >> v.pMem[i][j];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i) {
            for (size_t j = 0; j < v.sz; ++j)
                ostr << v.pMem[i][j] << ' ';
            ostr << endl;
        }
        return ostr;
    }
};

#endif