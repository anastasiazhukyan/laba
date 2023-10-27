#include <cassert>
#include<iostream>

template <typename T>
class Grid {
public:
    using value_type = T;
    using size_type = unsigned;

    // Конструктор для создания сетки заданных размеров
    Grid(size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size), data(new T[y_size * x_size]) {
        defaultInitialize();
    }

    // Конструктор для создания сетки заданных размеров и заполнения значениями по умолчанию
    Grid(size_type y_size, size_type x_size, T const& t) : y_size(y_size), x_size(x_size), data(new T[y_size * x_size]) {
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = t;
        }
    }

    // Конструктор для создания сетки размером 1x1 с заданным значением
    Grid(T const& t) : y_size(1), x_size(1), data(new T[1]) {
        data[0] = t;
    }

    // Конструктор копирования (часть правила пяти)
    Grid(const Grid& other) : y_size(other.y_size), x_size(other.x_size), data(new T[y_size * x_size]) {
        copyFromOther(other);
    }

    // Оператор присваивания (часть правила пяти)
    Grid& operator=(const Grid& other) {
        if (this != &other) {
            delete[] data;
            y_size = other.y_size;
            x_size = other.x_size;
            data = new T[y_size * x_size];
            copyFromOther(other);
        }
        return *this;
    }

    // Конструктор перемещения (часть правила пяти)
    Grid(Grid&& other) noexcept : y_size(0), x_size(0), data(nullptr) {
        swap(*this, other);
    }

    // Оператор перемещения (часть правила пяти)
    Grid& operator=(Grid&& other) noexcept {
        if (this != &other) {
            delete[] data;
            swap(*this, other);
        }
        return *this;
    }

    // Деструктор (часть правила пяти)
    ~Grid() {
        delete[] data;
    }

    // Операторы доступа к элементам:
    // Оператор [] для чтения (const)
    T const* operator [] (size_type y_idx) const {
        return data + y_idx * x_size;
    }

    // Оператор [] для записи
    T* operator [] (size_type y_idx) {
        return data + y_idx * x_size;
    }

    // Оператор () для чтения (const)
    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    // Оператор () для записи
    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    // Получение размеров сетки:
    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

private:
    T* data;
    size_type y_size, x_size;

    // Заполнение сетки значениями по умолчанию
    void defaultInitialize() {
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = T();
        }
    }

    // Копирование данных из другой сетки
    void copyFromOther(const Grid& other) {
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = other.data[i];
        }
    }

   
};

int main() {
    
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    for (unsigned y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (unsigned x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    for (unsigned y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (unsigned x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0;
            for (unsigned y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
                for (unsigned x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
                    assert(1.0f == g(y_idx, x_idx));

    Grid<float> g2(2, 3);
    assert(2 == g2.get_y_size());
    assert(3 == g2.get_x_size());

    for (unsigned y_idx = 0; y_idx != g2.get_y_size(); ++y_idx)
        for (unsigned x_idx = 0; x_idx != g2.get_x_size(); ++x_idx)
            assert(0.0f == g2[y_idx][x_idx]);

    for (unsigned y_idx = 0; y_idx != g2.get_y_size(); ++y_idx)
        for (unsigned x_idx = 0; x_idx != g2.get_x_size(); ++x_idx)
            g2[y_idx][x_idx] = 2.0f;

    for (unsigned y_idx = 0; y_idx != g2.get_y_size(); ++y_idx)
        for (unsigned x_idx = 0; x_idx != g2.get_x_size(); ++x_idx)
            assert(2.0f == g2(y_idx, x_idx));

    return 0;
}
