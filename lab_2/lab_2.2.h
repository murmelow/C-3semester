#include "MyVector.h"
using namespace std;

class TMatrix {
private:
    MyVector<MyVector<int>> Matr;
    int Msize;

public:
    // Конструктор
    TMatrix(int MTsize = 0) {
        Msize = MTsize;
        Matr = MyVector<MyVector<int>>(Msize);

        for (int i = 0; i < Msize; i++) {
            Matr[i] = MyVector<int>(Msize - i, i);

            for (int j = i; j < Msize; j++) {
                Matr[i][j] = 0;
            }
        }
    }

    // Конструктор копирования
    TMatrix(const TMatrix& tmp) {
        Msize = tmp.Msize;
        Matr = tmp.Matr;
    }

    // Оператор присваивания
    TMatrix& operator=(const TMatrix& tmp) {
        if (this == &tmp) {
            return *this;
        }

        Msize = tmp.Msize;
        Matr = tmp.Matr;

        return *this;
    }

    // Деструктор
    ~TMatrix() {}

    // Перегрузка []
    MyVector<int>& operator[](int k) {
        return Matr[k];
    }

    // Сложение
    TMatrix operator+(TMatrix tmp) {
        if (Msize != tmp.Msize) {
            throw "Размеры матриц не совпадают";
        }

        TMatrix res(Msize);

        for (int i = 0; i < Msize; i++) {
            res.Matr[i] = Matr[i] + tmp.Matr[i];
        }

        return res;
    }

    // Вычитание
    TMatrix operator-(TMatrix tmp) {
        if (Msize != tmp.Msize) {
            throw "Размеры матриц не совпадают";
        }

        TMatrix res(Msize);

        for (int i = 0; i < Msize; i++) {
            res.Matr[i] = Matr[i] - tmp.Matr[i];
        }

        return res;
    }

    // Умножение на число
    TMatrix operator*(int k) {
        TMatrix res(Msize);

        for (int i = 0; i < Msize; i++) {
            res[i] = Matr[i] * k;
        }

        return res;
    }

    // Умножение матриц
    TMatrix operator*(TMatrix tmp) {
        if (Msize != tmp.Msize) {
            throw "Размеры матриц не совпадают";
        }

        TMatrix res(Msize);

        for (int i = 0; i < Msize; i++) {
            for (int j = i; j < Msize; j++) {
                res[i][j] = 0;

                for (int k = i; k <= j; k++) {
                    res[i][j] += Matr[i][k] * tmp.Matr[k][j];
                }
            }
        }

        return res;
    }
};
