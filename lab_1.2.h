#pragma once
#include "TBitField.h"
#include <string>
#include <vector>
using namespace std;

class TSet {
private:
    TBitField tb;
    int U;

public:
    // Конструктор пустого множества
    TSet(int Un = 0) {
        U = Un;
        tb = TBitField(U);
    }

    ~TSet() {}

    // Оператор присваивания
    TSet& operator=(TSet tmp) {
        tb = tmp.tb;
        U = tmp.U;
        return *this;
    }

    // Конструктор копирования
    TSet(const TSet& tmp) {
        tb = tmp.tb;
        U = tmp.U;
    }

    // Добавление элемента
    void Add(int num) {
        if (num > 0 && num <= U) {
            tb.Add(num);
        }
    }

    // Конструктор множества из строки
    TSet(int Un, string st) {
    U = Un;
    tb = TBitField(U);

    vector<string> words;

    string delimiters = " ,.;/";
    string word = "";

    for (char c : st) {
        if (delimiters.find(c) == string::npos) {
            word += c;
        }
        else {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    for (const string& current : words) {
        int num = stoi(current);

        if (num > 0 && num <= U) {
            tb.Add(num);
            }
        }
    }   

    // Преобразование множества в строку
    string TsetToString() {
        return tb.BitToString(U);
    }

    // Пересечение
    TSet operator|(TSet tmp) {
        TSet res(*this);
        res.tb = tb | tmp.tb;
        return res;
    }

    // Объединение
    TSet operator&(TSet tmp) {
        TSet res(*this);
        res.tb = tb & tmp.tb;
        return res;
    }


    // Дополнение
    TSet operator~() {
        TSet res(*this);
        res.tb = ~tb;
        return res;
    }
};