#include "constants.hpp"
#include "test_base.hpp"
#include "vector.hpp"

#include <gtest/gtest.h>

class VectorAddVector : public ::testing::Test
{
protected:
    Vector<int> vec_int_1 = {1, 2, 3};
    Vector<int> vec_int_2 = {4, 5, 6};
    Vector<double> vec_double = {1.5, 2.5, 3.5};
    Vector<long> vec_long = {10, 20, 30};
};

// Тесты для оператора +
TEST_F(VectorAddVector, PlusOperatorSameType)
{
    auto result = vec_int_1 + vec_int_2;
    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 7);
    EXPECT_EQ(result[2], 9);
}

TEST_F(VectorAddVector, PlusOperatorDifferentTypes)
{
    auto result = vec_int_1 + vec_double;
    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 2.5);
    EXPECT_DOUBLE_EQ(result[1], 4.5);
    EXPECT_DOUBLE_EQ(result[2], 6.5);
}

TEST_F(VectorAddVector, PlusOperatorWithLong)
{
    auto result = vec_int_1 + vec_long;
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 11);
    EXPECT_EQ(result[1], 22);
    EXPECT_EQ(result[2], 33);
}

TEST_F(VectorAddVector, PlusOperatorDifferentSizeThrows)
{
    Vector<int> short_vec{1, 2};
    MY_EXPECT_THROW((vec_int_1 + short_vec), errVectorsSizeNotEqual)
}

// Тесты для оператора +=
TEST_F(VectorAddVector, PlusAssignmentSameType)
{
    vec_int_1 += vec_int_2;
    ASSERT_EQ(vec_int_1.size(), 3);
    EXPECT_EQ(vec_int_1[0], 5);
    EXPECT_EQ(vec_int_1[1], 7);
    EXPECT_EQ(vec_int_1[2], 9);
}

TEST_F(VectorAddVector, PlusAssignmentDifferentTypes)
{
    vec_int_1 += vec_double;
    ASSERT_EQ(vec_int_1.size(), 3);
    EXPECT_EQ(vec_int_1[0], 2); // 1 + 1.5 = 2.5, но сохраняется как int
    EXPECT_EQ(vec_int_1[1], 4); // 2 + 2.5 = 4.5 -> 4
    EXPECT_EQ(vec_int_1[2], 6); // 3 + 3.5 = 6.5 -> 6
}

TEST_F(VectorAddVector, PlusAssignmentChain)
{
    Vector<int> vec{1, 1, 1};
    vec += vec_int_1 += vec_int_2;
    ASSERT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 6);
    EXPECT_EQ(vec[1], 8);
    EXPECT_EQ(vec[2], 10);
}

TEST_F(VectorAddVector, PlusAssignmentDifferentSizeThrows)
{
    Vector<int> short_vec{1, 2};
    MY_EXPECT_THROW((vec_int_1 += short_vec), errVectorsSizeNotEqual)
}

/// @brief Тесты для сложение вектора с числом
class VectorAddNumber : public ::testing::Test
{
protected:
    Vector<int> int_vec = {1, 2, 3};
    Vector<double> double_vec = {1.5, 2.5, 3.5};
    Vector<int> empty_vec = {};
};

// Тесты для operator+(const U& num)
TEST_F(VectorAddNumber, PlusScalarSameType)
{
    auto result = int_vec + 2;

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 5);
    static_assert(std::is_same_v<decltype(result)::value_type, int>);
}

TEST_F(VectorAddNumber, PlusScalarDifferentType)
{
    auto result = int_vec + 1.5;

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 2.5);
    EXPECT_DOUBLE_EQ(result[1], 3.5);
    EXPECT_DOUBLE_EQ(result[2], 4.5);
    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}

TEST_F(VectorAddNumber, PlusScalarReturnsNewVector)
{
    auto result = int_vec + 1;
    EXPECT_EQ(int_vec[0], 1); // Исходный вектор не изменился
    EXPECT_EQ(result[0], 2);
}

TEST_F(VectorAddNumber, PlusScalarEmptyVectorThrows){
    MY_EXPECT_THROW(empty_vec + 5, errNegSize)}

TEST_F(VectorAddNumber, PlusScalarWithZero)
{
    auto result = int_vec + 0;
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

TEST_F(VectorAddNumber, PlusScalarTypeDeduction)
{
    auto result1 = double_vec + 2;
    static_assert(std::is_same_v<decltype(result1)::value_type, double>);

    auto result2 = int_vec + 2L;
    static_assert(std::is_same_v<decltype(result2)::value_type, long>);
}

TEST_F(VectorAddNumber, PlusScalarChainOperation)
{
    auto result = int_vec + 1 + 2;
    EXPECT_EQ(result[0], 4); // (1 + 1) + 2
    EXPECT_EQ(result[1], 5); // (2 + 1) + 2
    EXPECT_EQ(result[2], 6); // (3 + 1) + 2
}

// Тесты для operator+=(const U& num)
TEST_F(VectorAddNumber, PlusAssignmentScalarSameType)
{
    int_vec += 2;

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 3);
    EXPECT_EQ(int_vec[1], 4);
    EXPECT_EQ(int_vec[2], 5);
}

TEST_F(VectorAddNumber, PlusAssignmentScalarDifferentType)
{
    int_vec += 1.5; // Должно сработать static_cast<int>

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 2); // 1 + 1.5 → 2.5 → static_cast<int> → 2
    EXPECT_EQ(int_vec[1], 3); // 2 + 1.5 → 3.5 → 3
    EXPECT_EQ(int_vec[2], 4); // 3 + 1.5 → 4.5 → 4
}

TEST_F(VectorAddNumber, PlusAssignmentScalarEmptyVectorThrows)
{
    MY_EXPECT_THROW(empty_vec += 5, errNegSize);
}

TEST_F(VectorAddNumber, PlusAssignmentScalarChainOperation)
{
    (int_vec += 1) += 2;
    EXPECT_EQ(int_vec[0], 4); // (1 + 1) + 2
    EXPECT_EQ(int_vec[1], 5); // (2 + 1) + 2
    EXPECT_EQ(int_vec[2], 6); // (3 + 1) + 2
}

TEST_F(VectorAddNumber, PlusAssignmentScalarWithDoubleVector)
{
    double_vec += 1.2;
    EXPECT_DOUBLE_EQ(double_vec[0], 2.7);
    EXPECT_DOUBLE_EQ(double_vec[1], 3.7);
    EXPECT_DOUBLE_EQ(double_vec[2], 4.7);
}

TEST_F(VectorAddNumber, PlusAssignmentScalarNegativeValue)
{
    int_vec += -1;
    EXPECT_EQ(int_vec[0], 0);
    EXPECT_EQ(int_vec[1], 1);
    EXPECT_EQ(int_vec[2], 2);
}

// ____________________________________________________
// ____________________________________________________
// ____________________________________________________
// ____________________________________________________
// ____________________________________________________
// ТЕСТИРОВАНИЕ ОТРИЦАНИЯ
// ____________________________________________________
// ____________________________________________________
// ____________________________________________________
// ____________________________________________________
// ____________________________________________________

class VectorSubVector : public ::testing::Test
{
protected:
    Vector<int> int_vec = {10, 20, 30};
    Vector<double> double_vec = {1.5, 2.5, 3.5};
    Vector<int> empty_vec = {};
};

// Класс для тестирования операций вычитания чисел
class VectorSubNum : public ::testing::Test
{
protected:
    Vector<int> int_vec = {10, 20, 30};
    Vector<double> double_vec = {1.5, 2.5, 3.5};
    Vector<int> empty_vec = {};
};

TEST_F(VectorSubVector, SameTypeSubtraction)
{
    Vector<int> other{1, 2, 3};
    auto result = int_vec - other;

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 9);
    EXPECT_EQ(result[1], 18);
    EXPECT_EQ(result[2], 27);
}

TEST_F(VectorSubVector, DifferentTypeSubtraction)
{
    auto result = int_vec - double_vec;

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 8.5);
    EXPECT_DOUBLE_EQ(result[1], 17.5);
    EXPECT_DOUBLE_EQ(result[2], 26.5);
}

TEST_F(VectorSubVector, ReturnsNewVector)
{
    Vector<int> other{1, 2, 3};
    auto result = int_vec - other;
    EXPECT_EQ(int_vec[0], 10); // Исходный вектор не изменился
    EXPECT_EQ(result[0], 9);
}

TEST_F(VectorSubVector, EmptyVectorThrows)
{
    MY_EXPECT_THROW((int_vec - empty_vec), errNegSize);
}

TEST_F(VectorSubVector, DifferentSizeThrows)
{
    Vector<int> shorter{1, 2};
    MY_EXPECT_THROW((int_vec - shorter), errVectorsSizeNotEqual);
}

TEST_F(VectorSubVector, InplaceSubtractionSameType)
{
    Vector<int> other{1, 2, 3};
    int_vec -= other;

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 9);
    EXPECT_EQ(int_vec[1], 18);
    EXPECT_EQ(int_vec[2], 27);
}

TEST_F(VectorSubVector, InplaceSubtractionDifferentType)
{
    int_vec -= double_vec;

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 8);
    EXPECT_EQ(int_vec[1], 17);
    EXPECT_EQ(int_vec[2], 26);
}

TEST_F(VectorSubVector, InplaceReturnsReference)
{
    Vector<int> other{1, 2, 3};
    Vector<int> &result = (int_vec -= other);
    EXPECT_EQ(&result, &int_vec);
}

TEST_F(VectorSubVector, InplaceSelfSubtraction)
{
    int_vec -= int_vec;
    EXPECT_EQ(int_vec[0], 0);
    EXPECT_EQ(int_vec[1], 0);
    EXPECT_EQ(int_vec[2], 0);
}

TEST_F(VectorSubNum, ScalarSubtractionSameType)
{
    auto result = int_vec - 5;

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 15);
    EXPECT_EQ(result[2], 25);
}

TEST_F(VectorSubNum, ScalarSubtractionDifferentType)
{
    auto result = int_vec - 0.5;

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 9.5);
    EXPECT_DOUBLE_EQ(result[1], 19.5);
    EXPECT_DOUBLE_EQ(result[2], 29.5);
}

TEST_F(VectorSubNum, ScalarReturnsNewVector)
{
    auto result = int_vec - 1;
    EXPECT_EQ(int_vec[0], 10);
    EXPECT_EQ(result[0], 9);
}

TEST_F(VectorSubNum, InplaceScalarSubtractionSameType)
{
    int_vec -= 5;

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 5);
    EXPECT_EQ(int_vec[1], 15);
    EXPECT_EQ(int_vec[2], 25);
}

TEST_F(VectorSubNum, InplaceScalarSubtractionDifferentType)
{
    int_vec -= 0.5;

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 9);
    EXPECT_EQ(int_vec[1], 19);
    EXPECT_EQ(int_vec[2], 29);
}

TEST_F(VectorSubNum, InplaceScalarReturnsReference)
{
    Vector<int> &result = (int_vec -= 5);
    EXPECT_EQ(&result, &int_vec);
}

TEST_F(VectorSubNum, InplaceScalarChain)
{
    (int_vec -= 5) -= 2;
    EXPECT_EQ(int_vec[0], 3);
    EXPECT_EQ(int_vec[1], 13);
    EXPECT_EQ(int_vec[2], 23);
}

TEST_F(VectorSubNum, NegativeScalarSubtraction)
{
    int_vec -= -3;
    EXPECT_EQ(int_vec[0], 13);
    EXPECT_EQ(int_vec[1], 23);
    EXPECT_EQ(int_vec[2], 33);
}

// _____________________________________________
// _____________________________________________
// _____________________________________________
// _____________________________________________
// ТЕСТИРОВАНИЕ ПОЭЛЕМЕНТНОГО УМНОЖЕНИЯ ВЕКТОРОВ
// _____________________________________________
// _____________________________________________

// Базовый класс с тестовыми данными
class VectorMultiplicationBase
{
protected:
    Vector<int> int_vec{2, 3, 4};
    Vector<double> double_vec{1.5, 2.5, 3.5};
    Vector<int> empty_vec{};
    Vector<int> short_vec{1, 2};
};

// Тесты для умножения векторов
class VectorMultVector : public ::testing::Test, protected VectorMultiplicationBase
{
};

// Тесты для умножения на скаляр
class VectorMultNumber : public ::testing::Test, protected VectorMultiplicationBase
{
};

/****************************************************
 * ТЕСТЫ УМНОЖЕНИЯ ВЕКТОРОВ (operator* и operator*=)
 ****************************************************/

TEST_F(VectorMultVector, MultiplySameType)
{
    Vector<int> other{5, 6, 7};
    auto result = int_vec * other;

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 10); // 2*5
    EXPECT_EQ(result[1], 18); // 3*6
    EXPECT_EQ(result[2], 28); // 4*7
}

TEST_F(VectorMultVector, MultiplyDifferentTypes)
{
    auto result = int_vec * double_vec;

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 3.0);  // 2*1.5
    EXPECT_DOUBLE_EQ(result[1], 7.5);  // 3*2.5
    EXPECT_DOUBLE_EQ(result[2], 14.0); // 4*3.5
}

TEST_F(VectorMultVector, MultiplyReturnsNewVector)
{
    Vector<int> other{1, 1, 1};
    auto result = int_vec * other;
    EXPECT_EQ(int_vec[0], 2); // Исходный вектор не изменился
    EXPECT_EQ(result[0], 2);
}

TEST_F(VectorMultVector, MultiplyEmptyVector)
{
    MY_EXPECT_THROW(int_vec * empty_vec, errNegSize);
    MY_EXPECT_THROW(empty_vec * int_vec, errNegSize);
}

TEST_F(VectorMultVector, MultiplyDifferentSizes)
{
    MY_EXPECT_THROW(int_vec * short_vec, errVectorsSizeNotEqual);
}

TEST_F(VectorMultVector, InplaceMultiplySameType)
{
    Vector<int> other{2, 3, 4};
    int_vec *= other;

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 4);  // 2*2
    EXPECT_EQ(int_vec[1], 9);  // 3*3
    EXPECT_EQ(int_vec[2], 16); // 4*4
}

TEST_F(VectorMultVector, InplaceMultiplyDifferentTypes)
{
    int_vec *= double_vec;

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 3);  // 2*1.5 → 3.0 → 3
    EXPECT_EQ(int_vec[1], 7);  // 3*2.5 → 7.5 → 7
    EXPECT_EQ(int_vec[2], 14); // 4*3.5 → 14.0 → 14
}

TEST_F(VectorMultVector, InplaceMultiplyReturnsReference)
{
    Vector<int> other{1, 1, 1};
    Vector<int> &result = (int_vec *= other);
    EXPECT_EQ(&result, &int_vec);
}

TEST_F(VectorMultVector, InplaceMultiplySelf)
{
    int_vec *= int_vec;
    EXPECT_EQ(int_vec[0], 4);  // 2*2
    EXPECT_EQ(int_vec[1], 9);  // 3*3
    EXPECT_EQ(int_vec[2], 16); // 4*4
}

/****************************************************
 * ТЕСТЫ УМНОЖЕНИЯ НА ЧИСЛО (operator* и operator*=)
 ****************************************************/

TEST_F(VectorMultNumber, MultiplyScalarSameType)
{
    auto result = int_vec * 3;

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 6);  // 2*3
    EXPECT_EQ(result[1], 9);  // 3*3
    EXPECT_EQ(result[2], 12); // 4*3
}

TEST_F(VectorMultNumber, MultiplyScalarDifferentType)
{
    auto result = int_vec * 1.5;

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 3.0); // 2*1.5
    EXPECT_DOUBLE_EQ(result[1], 4.5); // 3*1.5
    EXPECT_DOUBLE_EQ(result[2], 6.0); // 4*1.5
}

TEST_F(VectorMultNumber, MultiplyScalarReturnsNewVector)
{
    auto result = int_vec * 2;
    EXPECT_EQ(int_vec[0], 2); // Исходный вектор не изменился
    EXPECT_EQ(result[0], 4);
}

TEST_F(VectorMultNumber, MultiplyScalarByZero)
{
    auto result = int_vec * 0;
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 0);
}

TEST_F(VectorMultNumber, InplaceMultiplyScalarSameType)
{
    int_vec *= 3;

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 6);  // 2*3
    EXPECT_EQ(int_vec[1], 9);  // 3*3
    EXPECT_EQ(int_vec[2], 12); // 4*3
}

TEST_F(VectorMultNumber, InplaceMultiplyScalarDifferentType)
{
    int_vec *= 1.5;

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 3); // 2*1.5 → 3
    EXPECT_EQ(int_vec[1], 4); // 3*1.5 → 4.5 → 4
    EXPECT_EQ(int_vec[2], 6); // 4*1.5 → 6
}

TEST_F(VectorMultNumber, InplaceMultiplyScalarReturnsReference)
{
    Vector<int> &result = (int_vec *= 2);
    EXPECT_EQ(&result, &int_vec);
}

TEST_F(VectorMultNumber, InplaceMultiplyScalarChain)
{
    (int_vec *= 2) *= 3;
    EXPECT_EQ(int_vec[0], 12); // (2*2)*3
    EXPECT_EQ(int_vec[1], 18); // (3*2)*3
    EXPECT_EQ(int_vec[2], 24); // (4*2)*3
}

TEST_F(VectorMultNumber, MultiplyEmptyVectorByScalar)
{
    MY_EXPECT_THROW(empty_vec * 5, errNegSize);
    MY_EXPECT_THROW(empty_vec *= 5, errNegSize);
}

// ________________________________
// ________________________________
// ________________________________
// ________________________________
// ТЕСТИРОВАНИЕ СКАЛЯРНОГО УМНОЖЕНИЯ
// ________________________________
// ________________________________
TEST(scalar_mul, null_vector)
{
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2;
    MY_EXPECT_THROW((vec1 & vec2), errNegSize)
}

TEST(scalar_mul, vector_different_size)
{
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2 = {0, 0, 0, 0};
    MY_EXPECT_THROW((vec1 & vec2), errVectorsSizeNotEqual)
}

TEST(scalar_mul, zero_vector)
{
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2 = {0, 0, 0};

    EXPECT_EQ(vec1 & vec2, 0);
}

TEST(scalar_mul, int_vectors)
{
    Vector<int> v1({1, 2, 3});
    Vector<int> v2({4, 5, 6});
    EXPECT_EQ(v1 & v2, 1 * 4 + 2 * 5 + 3 * 6);
}

TEST(scalar_mul, commutative_operation)
{
    Vector<double> v1({1.1, 2.2, 3.3});
    Vector<double> v2({4.4, 5.5, 6.6});

    auto result1 = v1 & v2;
    auto result2 = v2 & v1;

    EXPECT_NEAR(result1, result2, EPS);
}

TEST(scalar_mul, double_vectors)
{
    Vector<double> v1({1.1, 2.2, 3.3});
    Vector<double> v2({4.4, 5.5, 6.6});

    auto result1 = v1 & v2;

    EXPECT_NEAR(result1, 1.1 * 4.4 + 2.2 * 5.5 + 3.3 * 6.6, EPS);
}

// ТЕСТИРОВАНИЕ ВЕКТОРНОГО ПРОИЗВЕДЕНИЯ
class VectorCrossVector : public ::testing::Test
{
protected:
    Vector<int> vec3d_int = {1, 0, 0}, vec3d_int2 = {0, 1, 0}, vec2d = {1, 2}, empty_vec = {};
    Vector<double> vec3d_double{1.5, 2.5, 3.5};
};

// Основные тесты для 3D векторов
TEST_F(VectorCrossVector, Basic3DCrossProduct)
{
    auto result = vec3d_int ^ vec3d_int2;

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 1);
}

TEST_F(VectorCrossVector, CrossProductDifferentTypes)
{
    auto result = vec3d_int ^ vec3d_double;

    ASSERT_EQ(result.size(), 3);

    EXPECT_DOUBLE_EQ(result[0], 0);
    EXPECT_DOUBLE_EQ(result[1], -3.5);
    EXPECT_DOUBLE_EQ(result[2], 2.5);
}

TEST_F(VectorCrossVector, AntiCommutativeProperty)
{
    auto result1 = vec3d_int ^ vec3d_int2;
    auto result2 = vec3d_int2 ^ vec3d_int;

    ASSERT_EQ(result1.size(), 3);
    EXPECT_EQ(result1[0], -result2[0]);
    EXPECT_EQ(result1[1], -result2[1]);
    EXPECT_EQ(result1[2], -result2[2]);
}

TEST_F(VectorCrossVector, SelfCrossProductIsZero)
{
    auto result = vec3d_int ^ vec3d_int;

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 0);
}

// Тесты обработки ошибок
TEST_F(VectorCrossVector, Non3DVectorsThrowException)
{
    MY_EXPECT_THROW(vec2d ^ vec3d_int, errVectorsSizeNotEqual);
    MY_EXPECT_THROW(vec3d_int ^ vec2d, errVectorsSizeNotEqual);
    MY_EXPECT_THROW(vec2d ^ vec2d, errSizeNotCompatible);
}

TEST_F(VectorCrossVector, DifferentSizesThrowException)
{
    Vector<int> vec4d{1, 2, 3, 4};
    MY_EXPECT_THROW(vec3d_int ^ vec4d, errVectorsSizeNotEqual);
}

TEST_F(VectorCrossVector, EmptyVectorThrowsException)
{
    MY_EXPECT_THROW(empty_vec ^ vec3d_int, errNegSize);
    MY_EXPECT_THROW(vec3d_int ^ empty_vec, errNegSize);
    MY_EXPECT_THROW(empty_vec ^ empty_vec, errNegSize);
}

// Тесты специальных случаев
TEST_F(VectorCrossVector, CrossProductWithZeroVector)
{
    Vector<int> zero_vec{0, 0, 0};
    auto result = vec3d_int ^ zero_vec;

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 0);
}

TEST_F(VectorCrossVector, CrossProductOrthogonalVectors)
{
    Vector<int> vec1{1, 0, 0};
    Vector<int> vec2{0, 1, 0};
    Vector<int> vec3{0, 0, 1};

    auto result1 = vec1 ^ vec2;
    EXPECT_EQ(result1[0], 0);
    EXPECT_EQ(result1[1], 0);
    EXPECT_EQ(result1[2], 1);

    auto result2 = vec2 ^ vec3;
    EXPECT_EQ(result2[0], 1);
    EXPECT_EQ(result2[1], 0);
    EXPECT_EQ(result2[2], 0);

    auto result3 = vec3 ^ vec1;
    EXPECT_EQ(result3[0], 0);
    EXPECT_EQ(result3[1], 1);
    EXPECT_EQ(result3[2], 0);
}

// Тест на правильность типа возвращаемого значения
TEST_F(VectorCrossVector, ReturnTypeDeduction)
{
    auto result1 = vec3d_int ^ vec3d_int2;
    static_assert(std::is_same_v<decltype(result1)::value_type, int>);

    auto result2 = vec3d_int ^ vec3d_double;
    static_assert(std::is_same_v<decltype(result2)::value_type, double>);
}

// _____________________________________________
// _____________________________________________
// _____________________________________________
// _____________________________________________
// ТЕСТИРОВАНИЕ ОПЕРАЦИИ УНАРНЫЙ МИНУС
// _____________________________________________
// _____________________________________________

class VectorUnaryMinus : public ::testing::Test
{
protected:
    Vector<int> vec_int = {1, -2, 3}, empty_vec = {};
    Vector<double> vec_double = {1.5, -2.5, 3.5};
};

// Основные тесты для разных типов данных
TEST_F(VectorUnaryMinus, InvertsIntegerVector)
{
    auto result = -vec_int;

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], -1);
    EXPECT_EQ(result[1], 2); // -(-2) = 2
    EXPECT_EQ(result[2], -3);
}

TEST_F(VectorUnaryMinus, InvertsDoubleVector)
{
    auto result = -vec_double;

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], -1.5);
    EXPECT_DOUBLE_EQ(result[1], 2.5); // -(-2.5) = 2.5
    EXPECT_DOUBLE_EQ(result[2], -3.5);
}

// Проверка возвращаемого типа
TEST_F(VectorUnaryMinus, ReturnsCorrectType)
{
    auto result1 = -vec_int;
    static_assert(std::is_same_v<decltype(result1), Vector<int>>);

    auto result2 = -vec_double;
    static_assert(std::is_same_v<decltype(result2), Vector<double>>);
}

// Проверка, что исходный вектор не изменяется
TEST_F(VectorUnaryMinus, OriginalVectorNotModified)
{
    auto original = vec_int;
    auto result = -vec_int;

    EXPECT_EQ(original[0], 1);
    EXPECT_EQ(original[1], -2);
    EXPECT_EQ(original[2], 3);
}

// Тест для пустого вектора
TEST_F(VectorUnaryMinus, EmptyVector){
    MY_EXPECT_THROW(-empty_vec, errNegSize)}

// Тест на двойное применение
TEST_F(VectorUnaryMinus, DoubleNegation)
{
    auto result = -(-vec_int);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 1);  // -(-1) = 1
    EXPECT_EQ(result[1], -2); // -(2) = -2
    EXPECT_EQ(result[2], 3);  // -(-3) = 3
}

// Тест с нулевыми элементами
TEST_F(VectorUnaryMinus, WithZeroElements)
{
    Vector<int> vec_with_zeros{0, -0, 1, -1};
    auto result = -vec_with_zeros;

    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], -1);
    EXPECT_EQ(result[3], 1);
}
