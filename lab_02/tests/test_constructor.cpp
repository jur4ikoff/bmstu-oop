#include "vector.h"
#include "gtest/gtest.h"
#include "test_base.hpp"

// ТЕСТИРОВАНИЕ КОНСТРУКТОРА

TEST(CreationTest, test_creation_pos_1)
{
    // Создание на основе всех математических типов, без начального добавления
    Vector<int> a;
    Vector<float> b;
    Vector<double> c;
    Vector<long double> d;
    Vector<short int> e;
    Vector<long long int> f;
    Vector<uint16_t> g;

    EXPECT_EQ(g.size(), 0);
}

TEST(CreationTest, test_copy_same_types)
{
    // Тестирование конструктора копирования
    Vector<int> a;
    Vector<int> b = Vector(a);

    EXPECT_EQ(0, b.size());
}

TEST(CreationTest, test_creation_neg_1)
{
    EXPECT_FALSE(is_vector_constructible<char *>::value);
    EXPECT_FALSE(is_vector_constructible<std::string>::value);
}

TEST(CreationTest, ConstructsFromInitializerList)
{
    // Проверка на инициализацию от списка инициализации целых чисел
    Vector<int> vec({1, 2, 3, 4, 5});
    int excepected[5] = {1, 2, 3, 4, 5};

    EXPECT_EQ(vec.size(), 5); // Проверяем размер

    int i = 0;
    for (auto el : vec)
    {
        EXPECT_EQ(el, excepected[i]);
        i++;
    }
}

TEST(CreationTest, ConstructsFromInitializerListFloat)
{
    // Проверка на инициализацию от списка инициализации целых чисел
    Vector<float> vec({1.0f, 2.f, 3.0f, 4.23232f, 5.0f});
    float excepected[5] = {1, 2.0, 3, 4.23232, 5};

    EXPECT_EQ(vec.size(), 5); // Проверяем размер

    int i = 0;
    for (auto el : vec)
    {
        EXPECT_EQ(el, excepected[i]);
        i++;
    }
}

TEST(CreationTest, constructs_from_arr_with_size)
{
    // Проверка на инициализацию от списка инициализации целых чисел
    int size = 5;
    int arr[5] = {1, 2, 3, 4, 5};

    Vector<int> vec(size, arr);

    EXPECT_EQ(vec.size(), 5); // Проверяем размер

    int i = 0;
    for (auto el : vec)
    {
        EXPECT_EQ(el, arr[i]);
        i++;
    }
}

TEST(CreationTest, constructs_from_size_and_nargs)
{
    // Проверка на инициализацию от списка инициализации целых чисел
    int size = 5;
    int arr[5] = {1, 2, 3, 4, 5};

    Vector<int> vec(size, 1, 2, 3, 4, 5);
    EXPECT_EQ(vec.size(), 5); // Проверяем размер

    int i = 0;
    for (auto el : vec)
    {
        EXPECT_EQ(el, arr[i]);
        i++;
    }
}

TEST(CreationTest, constructs_from_iterator)
{
    // Проверка на инициализацию от списка инициализации целых чисел
    int size = 5;
    std::vector<int> a = {1, 2, 3, 4, 5};

    Vector<int> my(a.begin(), a.end());

    EXPECT_EQ(my.size(), 5); // check size

    int i = 0;
    for (const auto el : my)
    {
        EXPECT_EQ(el, a[i++]);
    }
}
