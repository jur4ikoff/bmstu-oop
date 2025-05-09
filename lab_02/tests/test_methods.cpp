// ТЕСТИРОВАНИЕ МЕТОДОВ, РЕАЛИЗУЮЩИХ МАТЕМАТИЧЕСКИЕ ФУНКЦИИ, ПО ТИПУ СЛОЖЕНИЯ И ТД.

#include "test_base.hpp"
#include "vector.h"

#include <gtest/gtest.h>
#include <math.h>

class BaseVectors
{
protected:
    Vector<int> int_vec{ 2, 3, 4 };
    Vector<double> double_vec{ 1.5, 2.5, 3.5 };
    Vector<int> empty_vec{};
    Vector<int> short_vec{ 1, 2 };
};

// Класс для тестирования vec_sum()
class VectorSumOperator : public BaseVectors, public ::testing::Test
{
};

class VectorPlusNum : public BaseVectors, public ::testing::Test
{
};

class VectorSubOperator : public BaseVectors, public ::testing::Test
{
};

class VectorSubNumOperator : public BaseVectors, public ::testing::Test
{
};

/**********************************************
 * ТЕСТЫ ДЛЯ METOДА vec_sum()
 **********************************************/

TEST_F(VectorSumOperator, PlusSameType)
{
    Vector<int> other{ 5, 6, 7 };
    auto result = int_vec.vec_sum(other);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 7);  // 2 + 5
    EXPECT_EQ(result[1], 9);  // 3 + 6
    EXPECT_EQ(result[2], 11); // 4 + 7
}

TEST_F(VectorSumOperator, PlusDifferentTypes)
{
    auto result = int_vec.vec_sum(double_vec);

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 3.5); // 2 + 1.5
    EXPECT_DOUBLE_EQ(result[1], 5.5); // 3 + 2.5
    EXPECT_DOUBLE_EQ(result[2], 7.5); // 4 + 3.5
}

TEST_F(VectorSumOperator, PlusReturnsNewVector)
{
    Vector<int> other{ 1, 1, 1 };
    auto result = int_vec.vec_sum(other);
    EXPECT_EQ(int_vec[0], 2); // Исходный вектор не изменился
    EXPECT_EQ(result[0], 3);  // 2 + 1
}

TEST_F(VectorSumOperator, PlusEmptyVector)
{
    MY_EXPECT_THROW(int_vec.vec_sum(empty_vec), errNegSize);
    MY_EXPECT_THROW(empty_vec.vec_sum(int_vec), errNegSize);
}

TEST_F(VectorSumOperator, PlusDifferentSizes)
{
    MY_EXPECT_THROW(int_vec.vec_sum(short_vec), errVectorsSizeNotEqual);
}

TEST_F(VectorSumOperator, PlusReturnTypeDeduction)
{
    auto result1 = int_vec.vec_sum(int_vec);
    static_assert(std::is_same_v<decltype(result1), Vector<int>>);

    auto result2 = int_vec.vec_sum(double_vec);
    static_assert(std::is_same_v<decltype(result2), Vector<double>>);
}

/**********************************************
 * ТЕСТЫ ДЛЯ METOДА vec_sum_eq()
 **********************************************/

TEST_F(VectorSumOperator, PlusEqSameType)
{
    Vector<int> other{ 1, 2, 3 };
    Vector<int> original = int_vec;
    int_vec.vec_sum_eq(other);

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 3); // 2 + 1
    EXPECT_EQ(int_vec[1], 5); // 3 + 2
    EXPECT_EQ(int_vec[2], 7); // 4 + 3
}

TEST_F(VectorSumOperator, PlusEqDifferentTypes)
{
    Vector<double> other{ 0.5, 1.5, 2.5 };
    int_vec.vec_sum_eq(other);

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 2); // 2 + 0.5 → 2.5 → static_cast<int> → 2
    EXPECT_EQ(int_vec[1], 4); // 3 + 1.5 → 4.5 → 4
    EXPECT_EQ(int_vec[2], 6); // 4 + 2.5 → 6.5 → 6
}

TEST_F(VectorSumOperator, PlusEqReturnsReference)
{
    Vector<int> other{ 1, 1, 1 };
    Vector<int> &result = int_vec.vec_sum_eq(other);
    EXPECT_EQ(&result, &int_vec);
}

TEST_F(VectorSumOperator, PlusEqSelfAssignment)
{
    Vector<int> original = int_vec;
    int_vec.vec_sum_eq(int_vec);

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 4); // 2 + 2
    EXPECT_EQ(int_vec[1], 6); // 3 + 3
    EXPECT_EQ(int_vec[2], 8); // 4 + 4
}

TEST_F(VectorSumOperator, PlusEqEmptyVector)
{
    MY_EXPECT_THROW(int_vec.vec_sum_eq(empty_vec), errNegSize);
    MY_EXPECT_THROW(empty_vec.vec_sum_eq(int_vec), errNegSize);
}

TEST_F(VectorSumOperator, PlusEqDifferentSizes)
{
    MY_EXPECT_THROW(int_vec.vec_sum_eq(short_vec), errVectorsSizeNotEqual);
}

TEST_F(VectorSumOperator, PlusEqChainOperation)
{
    Vector<int> other1{ 1, 1, 1 };
    Vector<int> other2{ 2, 2, 2 };
    int_vec.vec_sum_eq(other1).vec_sum_eq(other2);

    EXPECT_EQ(int_vec[0], 5); // (2 + 1) + 2
    EXPECT_EQ(int_vec[1], 6); // (3 + 1) + 2
    EXPECT_EQ(int_vec[2], 7); // (4 + 1) + 2
}

/**********************************************
 * ТЕСТЫ ДЛЯ METOДА plus и plus_eq()
 **********************************************/

// Тесты для plus(const U& num)
TEST_F(VectorPlusNum, PlusScalarBasic)
{
    auto result = int_vec.plus(5);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 7); // 2+5
    EXPECT_EQ(result[1], 8); // 3+5
    EXPECT_EQ(result[2], 9); // 4+5
}

TEST_F(VectorPlusNum, PlusScalarTypeConversion)
{
    auto result = int_vec.plus(1.5);
    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 3.5); // 2+1.5
}

TEST_F(VectorPlusNum, PlusScalarEmpty)
{
    MY_EXPECT_THROW(empty_vec.plus(1), errNegSize);
}

// Тесты для plus_eq(const U& num)
TEST_F(VectorPlusNum, PlusEqScalarBasic)
{
    int_vec.plus_eq(2);
    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 4); // 2+2
    EXPECT_EQ(int_vec[1], 5); // 3+2
    EXPECT_EQ(int_vec[2], 6); // 4+2
}

TEST_F(VectorPlusNum, PlusEqScalarChain)
{
    int_vec.plus_eq(1).plus_eq(2);
    EXPECT_EQ(int_vec[0], 5); // (2+1)+2
}

TEST_F(VectorPlusNum, PlusEqScalarEmpty)
{
    MY_EXPECT_THROW(empty_vec.plus_eq(1), errNegSize);
}

/**********************************************
 * ТЕСТЫ ДЛЯ METOДОВ vec_sub и vec_sub_eq() Векторное вычитание
 **********************************************/

// Тесты для vec_sub (вычитание векторов)
TEST_F(VectorSubOperator, VecSubSameType)
{
    Vector<int> other{ 1, 1, 1 };
    auto result = int_vec.vec_sub(other);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 1); // 2-1
    EXPECT_EQ(result[1], 2); // 3-1
    EXPECT_EQ(result[2], 3); // 4-1
}

TEST_F(VectorSubOperator, VecSubDifferentTypes)
{
    auto result = double_vec.vec_sub(int_vec);

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], -0.5); // 1.5-2
    EXPECT_DOUBLE_EQ(result[1], -0.5); // 2.5-3
    EXPECT_DOUBLE_EQ(result[2], -0.5); // 3.5-4
}

TEST_F(VectorSubOperator, VecSubEmptyVector)
{
    MY_EXPECT_THROW(int_vec.vec_sub(empty_vec), errNegSize);
}

// Тесты для vec_sub_eq (вычитание с присваиванием)
TEST_F(VectorSubOperator, VecSubEqSameType)
{
    Vector<int> other{ 1, 2, 3 };
    int_vec.vec_sub_eq(other);

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 1); // 2-1
    EXPECT_EQ(int_vec[1], 1); // 3-2
    EXPECT_EQ(int_vec[2], 1); // 4-3
}

TEST_F(VectorSubOperator, VecSubEqDifferentTypes)
{
    Vector<double> other{ 0.5, 1.5, 2.5 };
    int_vec.vec_sub_eq(other);

    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 1); // 2-0.5 → 1.5 → 1
    EXPECT_EQ(int_vec[1], 1); // 3-1.5 → 1.5 → 1
    EXPECT_EQ(int_vec[2], 1); // 4-2.5 → 1.5 → 1
}

TEST_F(VectorSubOperator, VecSubEqChain)
{
    Vector<int> other1{ 1, 1, 1 };
    Vector<int> other2{ 2, 2, 2 };
    int_vec.vec_sub_eq(other1).vec_sub_eq(other2);

    EXPECT_EQ(int_vec[0], -1); // (2-1)-2
    EXPECT_EQ(int_vec[1], 0);  // (3-1)-2
    EXPECT_EQ(int_vec[2], 1);  // (4-1)-2
}

TEST_F(VectorSubOperator, VecSubEqEmptyVector)
{
    MY_EXPECT_THROW(int_vec.vec_sub_eq(empty_vec), errNegSize);
}

/**********************************************
 * ТЕСТЫ ДЛЯ METOДОВ minus и minus_eq() Векторное вычитание
 **********************************************/

// Тесты для minus(const U& num)
TEST_F(VectorSubNumOperator, MinusScalarBasic)
{
    auto result = int_vec.minus(1);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 1); // 2-1
    EXPECT_EQ(result[1], 2); // 3-1
    EXPECT_EQ(result[2], 3); // 4-1
}

TEST_F(VectorSubNumOperator, MinusScalarDouble)
{
    auto result = double_vec.minus(0.5);
    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 1.0); // 1.5-0.5
}

TEST_F(VectorSubNumOperator, MinusScalarEmpty)
{
    MY_EXPECT_THROW(empty_vec.minus(1), errNegSize);
}

// Тесты для minus_eq(const U& num)
TEST_F(VectorSubNumOperator, MinusEqScalarBasic)
{
    int_vec.minus_eq(2);
    ASSERT_EQ(int_vec.size(), 3);
    EXPECT_EQ(int_vec[0], 0); // 2-2
    EXPECT_EQ(int_vec[1], 1); // 3-2
    EXPECT_EQ(int_vec[2], 2); // 4-2
}

TEST_F(VectorSubNumOperator, MinusEqScalarChain)
{
    int_vec.minus_eq(1).minus_eq(1);
    EXPECT_EQ(int_vec[0], 0); // (2-1)-1
}

TEST_F(VectorSubNumOperator, MinusEqScalarEmpty)
{
    MY_EXPECT_THROW(empty_vec.minus_eq(1), errNegSize);
}

TEST_F(VectorSubNumOperator, MinusScalarNegative)
{
    auto result = int_vec.minus(-1);
    EXPECT_EQ(result[0], 3); // 2-(-1)
}

TEST_F(VectorSubNumOperator, MinusEqTypeConversion)
{
    double_vec.minus_eq(1);
    EXPECT_DOUBLE_EQ(double_vec[0], 0.5); // 1.5-1
}
