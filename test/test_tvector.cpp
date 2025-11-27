#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicVector<int> v(8));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 10));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(-7));
}

TEST(TDynamicVector, can_create_copied_vector)
{
    TDynamicVector<int> v(12);
    ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v(6);
    v[0] = 3; v[1] = 6; v[2] = 9; v[3] = 12; v[4] = 15; v[5] = 18;
    TDynamicVector<int> v1(v);

    EXPECT_EQ(v.size(), v1.size());
    for (size_t i = 0; i < v.size(); i++) {
        EXPECT_EQ(v[i], v1[i]);
    }
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(5);
    v[2] = 50;
    TDynamicVector<int> v1(v);
    v[2] = 100;
    EXPECT_NE(v[2], v1[2]);
}

TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(9);
    EXPECT_EQ(9, v.size());
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(5);
    ASSERT_ANY_THROW(v.at(-3));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(5);
    ASSERT_ANY_THROW(v.at(6));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(4);
    v[0] = 8; v[1] = 16; v[2] = 24; v[3] = 32;
    v = v;
    EXPECT_EQ(8, v[0]);
    EXPECT_EQ(16, v[1]);
    EXPECT_EQ(24, v[2]);
    EXPECT_EQ(32, v[3]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v1(4);
    v1[0] = 7; v1[1] = 14; v1[2] = 21; v1[3] = 28;
    TDynamicVector<int> v2(4);
    v2 = v1;
    EXPECT_EQ(7, v2[0]);
    EXPECT_EQ(14, v2[1]);
    EXPECT_EQ(21, v2[2]);
    EXPECT_EQ(28, v2[3]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v1(2);
    TDynamicVector<int> v2(7);
    v1 = v2;
    EXPECT_EQ(7, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v1(3);
    TDynamicVector<int> v2(8);
    ASSERT_NO_THROW(v2 = v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v1(4);
    v1[0] = 11; v1[1] = 22; v1[2] = 33; v1[3] = 44;
    TDynamicVector<int> v2(4);
    v2[0] = 11; v2[1] = 22; v2[2] = 33; v2[3] = 44;
    ASSERT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v1(6);
    v1[0] = 9; v1[5] = 54;
    ASSERT_TRUE(v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v1(5);
    TDynamicVector<int> v2(8);
    ASSERT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v1(3);
    v1[0] = 5; v1[1] = 10; v1[2] = 15;
    TDynamicVector<int> result = v1 + 20;
    EXPECT_EQ(25, result[0]);
    EXPECT_EQ(30, result[1]);
    EXPECT_EQ(35, result[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v1(3);
    v1[0] = 25; v1[1] = 30; v1[2] = 35;
    TDynamicVector<int> result = v1 - 10;
    EXPECT_EQ(15, result[0]);
    EXPECT_EQ(20, result[1]);
    EXPECT_EQ(25, result[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v1(3);
    v1[0] = 4; v1[1] = 8; v1[2] = 12;
    TDynamicVector<int> result = v1 * 3;
    EXPECT_EQ(12, result[0]);
    EXPECT_EQ(24, result[1]);
    EXPECT_EQ(36, result[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3);
    v1[0] = 6; v1[1] = 12; v1[2] = 18;
    TDynamicVector<int> v2(3);
    v2[0] = 4; v2[1] = 8; v2[2] = 12;
    TDynamicVector<int> result = v1 + v2;
    EXPECT_EQ(10, result[0]);
    EXPECT_EQ(20, result[1]);
    EXPECT_EQ(30, result[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(7);
    ASSERT_ANY_THROW(v1 + v2);
}
TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3);
    v1[0] = 15; v1[1] = 30; v1[2] = 45;
    TDynamicVector<int> v2(3);
    v2[0] = 5; v2[1] = 10; v2[2] = 15;
    TDynamicVector<int> result = v1 - v2;
    EXPECT_EQ(10, result[0]);
    EXPECT_EQ(20, result[1]);
    EXPECT_EQ(30, result[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(9);
    ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3);
    v1[0] = 2; v1[1] = 4; v1[2] = 6;
    TDynamicVector<int> v2(3);
    v2[0] = 3; v2[1] = 5; v2[2] = 7;
    int result = v1 * v2;
    EXPECT_EQ(68, result); // 2*3 + 4*5 + 6*7 = 6 + 20 + 42 = 68
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(4);
    TDynamicVector<int> v2(11);
    ASSERT_ANY_THROW(v1 * v2);
}
