using namespace std;

template <class T>
class MyVector {
private:
    T* Mem;
    int size;
    int start;
    T zero;

public:
    // Конструктор
    MyVector(int sizeM = 10, int startN = 0) {
        if (sizeM < 0) {
            cout << "Отрицательный размер вектора" << endl;
            sizeM = 0;
        }

        size = sizeM;
        start = startN;
        zero = T(0);

        Mem = new T[size];

        for (int i = 0; i < size; i++) {
            Mem[i] = T(0);
        }
    }

    // Конструктор копирования
    MyVector(const MyVector<T>& tmp) {
        size = tmp.size;
        start = tmp.start;
        zero = T(0);

        Mem = new T[size];

        for (int i = 0; i < size; i++) {
            Mem[i] = tmp.Mem[i];
        }
    }

    // Оператор присваивания
    MyVector<T>& operator=(const MyVector<T>& tmp) {
        if (this == &tmp) {
            return *this;
        }

        T* newMem = new T[tmp.size];

        for (int i = 0; i < tmp.size; i++) {
            newMem[i] = tmp.Mem[i];
        }

        delete[] Mem;

        Mem = newMem;
        size = tmp.size;
        start = tmp.start;
        zero = T(0);

        return *this;
    }

    // Деструктор
    ~MyVector() {
        delete[] Mem;
    }

    // Перегрузка []
    T& operator[](int j) {
        if (j < start || j >= start + size) {
            zero = T(0);
            return zero;
        }

        return Mem[j - start];
    }

    // Получение размера и начального индекса
    int GetSize() const {
        return size;
    }

    int GetStart() const {
        return start;
    }

    // Сложение
    MyVector<T> operator+(const MyVector<T>& tmp) const {
        if (size != tmp.size || start != tmp.start) {
            cout << "Размер или начальный индекс не совпадают" << endl;
            return MyVector<T>(0, start);
        }

        MyVector<T> res(size, start);

        for (int i = 0; i < size; i++) {
            res.Mem[i] = Mem[i] + tmp.Mem[i];
        }

        return res;
    }

    // Вычитание
    MyVector<T> operator-(const MyVector<T>& tmp) const {
        if (size != tmp.size || start != tmp.start) {
            cout << "Размер или начальный индекс не совпадают" << endl;
            return MyVector<T>(0, start);
        }

        MyVector<T> res(size, start);

        for (int i = 0; i < size; i++) {
            res.Mem[i] = Mem[i] - tmp.Mem[i];
        }

        return res;
    }

    // Умножение на число
    MyVector<T> operator*(int k) const {
        MyVector<T> res(size, start);

        for (int i = 0; i < size; i++) {
            res.Mem[i] = Mem[i] * k;
        }

        return res;
    }

    // Скалярное произведение векторов
    T operator*(const MyVector<T>& tmp) const {
        if (size != tmp.size || start != tmp.start) {
            return T(0);
        }

        T res = T(0);

        for (int i = 0; i < size; i++) {
            res += Mem[i] * tmp.Mem[i];
        }

        return res;
    }
};
