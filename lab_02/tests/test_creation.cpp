#include "vector.h"
#include "gtest/gtest.h"

template <typename T, typename = void>
struct is_vector_constructible : std::false_type
{
};

template <typename T>
struct is_vector_constructible<T,
                               std::void_t<decltype(Vector<T>{})>> : std::true_type
{
};

// int add(int a, int b)
// {
//     return a + b;
// }

// TEST(MyCodeTest, BasicTest)
// {
//     EXPECT_EQ(2, add(1, 1));
// }

// TEST(MyCodeTest, NegativeTest)
// {
//     EXPECT_EQ(-1, add(-2, 1));
// }

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
    Vector<int> vec({ 1, 2, 3, 4, 5 });
    int excepected[5] = { 1, 2, 3, 4, 5 };

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
    Vector<float> vec({ 1.0, 2, 3.0f, 4.23232, 5.0 });
    float excepected[5] = { 1, 2.0, 3, 4.23232, 5 };

    EXPECT_EQ(vec.size(), 5); // Проверяем размер

    int i = 0;
    for (auto el : vec)
    {
        EXPECT_EQ(el, excepected[i]);
        i++;
    }
}

TEST(CreationTest, ConstructsFromConvertibleTypes)
{
    // 2. Проверка с типами, конвертируемыми в T (например, double -> int)
    // Vector<int> vec = {1.5, 2.7, 3.0};  // T1 = double (должно сработать, если ConvertAssignable<double, int>)

    // // Проверяем, что значения сконвертировались (отбрасывается дробная часть)
    // EXPECT_EQ(vec.size(), 3);
    // EXPECT_EQ(vec[0], 1);  // 1.5 -> 1
    // EXPECT_EQ(vec[1], 2);  // 2.7 -> 2
    // EXPECT_EQ(vec[2], 3);  // 3.0 -> 3
}

TEST(CreationTest, HandlesEmptyList)
{
    // 3. Проверка пустого списка
    // Vector<int> vec = {};

    // EXPECT_EQ(vec.size(), 0);
    // EXPECT_TRUE(vec.empty());
}

TEST(MyCodeTest, test_pos)
{

    // Vector<int> a = { -100, -4, 5 };
    std::vector<float> vec = { 1, 2.5, 3U, 4.2f, 5LL };
    // Vector<int> b = { 2, 2, 2 };

    // Vector<int> res(a + b);

    // int expect[3] = { -98, -2, 7 };
    // int i = 0;
    // for (auto el : res)
    // {
    //     EXPECT_EQ(el, expect[i++]);
    // }
}

// int main(int argc, char **argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
