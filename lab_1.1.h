#pragma once
#include <string>

class TBitField {
private:
    unsigned int* mem;
    int size;

    // Номер ячейки в массиве, в которой хранится бит с номером num
    int GetNumberMem(int num) { 
        return (num - 1) / (int)(sizeof(int) * 8);
    }

    // Номер бита в ячейке массива, в которой хранится бит с номером num
    int GetBit(int num) {
        return (num - 1) % (int)(sizeof(int) * 8);
    }

public:
    // Количество ячеек
    TBitField(unsigned int Usize = 0) {
        size = Usize / (int)(sizeof(int) * 8) + 1;
        mem = new unsigned int[size];

        for (int i = 0; i < size; i++) {
            mem[i] = 0;
        }
    }

    ~TBitField() {
        delete[] mem;
    }

    // Конструктор копирования
    TBitField(const TBitField& tmp) {
        size = tmp.size;
        mem = new unsigned int[size];

        for (int i = 0; i < size; i++) {
            mem[i] = tmp.mem[i];
        }
    }

    // Оператор присваивания
    TBitField& operator=(const TBitField& tmp) {
        if (this == &tmp) {
            return *this;
        }
        delete[] mem;

        size = tmp.size;
        mem = new unsigned int[size];

        for (int i = 0; i < size; i++) {
            mem[i] = tmp.mem[i];
        }

        return *this;
    }

    void Add(int num) {
        mem[GetNumberMem(num)] |= (1u << GetBit(num));
    }

    // Возвращает строку, содержащую номера установленных битов
    std::string BitToString(int sizeU) {
        std::string str = "";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < (int)(sizeof(int) * 8); j++) {
                if ((mem[i] & (1u << j)) != 0) {
                    int k = i * (int)(sizeof(int) * 8) + j + 1;
                    if (k <= sizeU) {
                        str = str + " " + std::to_string(k);
                    }
                }
            }
        }
        return str;
    }

    // Пересечение
    TBitField operator|(const TBitField& tmp) {
        TBitField res(*this);
        if (size == tmp.size) {
            for (int i = 0; i < size; i++) {
                res.mem[i] = mem[i] | tmp.mem[i];
            }
        }
        return res; 
    }

    // Обьединение
    TBitField operator&(const TBitField& tmp) {
        TBitField res(*this);
        if (size == tmp.size) {
            for (int i = 0; i < size; i++) {
                res.mem[i] = mem[i] & tmp.mem[i];
            }
       }
       return res;
    }

    // Дополнение
    TBitField operator~() {
        TBitField res(*this);
        for (int i = 0; i < size; i++) {
            res.mem[i] = ~mem[i];
        }
        return res;
    }
};