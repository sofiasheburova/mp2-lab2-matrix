#include "tmatrix.h"

#include <gtest.h>
TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicMatrix<int> m(7));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 5));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-8));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
    TDynamicMatrix<int> m(6);
    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(4);
    m[0][0] = 5; m[0][1] = 10; m[0][2] = 15; m[0][3] = 20;
    m[1][0] = 25; m[1][1] = 30; m[1][2] = 35; m[1][3] = 40;
    m[2][0] = 45; m[2][1] = 50; m[2][2] = 55; m[2][3] = 60;
    m[3][0] = 65; m[3][1] = 70; m[3][2] = 75; m[3][3] = 80;

    TDynamicMatrix<int> m1(m);
    EXPECT_EQ(m.size(), m1.size());
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            EXPECT_EQ(m[i][j], m1[i][j]);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(3);
    m[1][1] = 100;
    TDynamicMatrix<int> m1(m);
    m[1][1] = 200;
    EXPECT_NE(m[1][1], m1[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(8);
    EXPECT_EQ(8, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(5);
    m[2][3] = 42;
    EXPECT_EQ(42, m[2][3]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(4);
    ASSERT_ANY_THROW(m.at(-2)[0] = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(4);
    ASSERT_ANY_THROW(m.at(5)[0] = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(3);
    m[0][0] = 7; m[1][1] = 14; m[2][2] = 21;
    m = m;
    EXPECT_EQ(7, m[0][0]);
    EXPECT_EQ(14, m[1][1]);
    EXPECT_EQ(21, m[2][2]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m(4);
    m[0][0] = 11; m[1][1] = 22;
    TDynamicMatrix<int> m1(4);
    m1 = m;
    EXPECT_EQ(11, m1[0][0]);
    EXPECT_EQ(22, m1[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m(2);
    TDynamicMatrix<int> m1(5);
    m1 = m;
    EXPECT_EQ(2, m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m(2);
    TDynamicMatrix<int> m1(6);
    ASSERT_NO_THROW(m1 = m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m(3);
    m[0][0] = 9; m[1][1] = 18; m[2][2] = 27;
    TDynamicMatrix<int> m1(3);
    m1[0][0] = 9; m1[1][1] = 18; m1[2][2] = 27;
    ASSERT_TRUE(m1 == m);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(4);
    m[0][0] = 12; m[3][3] = 48;
    ASSERT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m(3);
    TDynamicMatrix<int> m1(7);
    EXPECT_TRUE(m != m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(3);
    m1[0][0] = 6; m1[1][1] = 12;
    TDynamicMatrix<int> m2(3);
    m2[0][0] = 4; m2[1][1] = 8;
    TDynamicMatrix<int> result = m1 + m2;
    EXPECT_EQ(10, result[0][0]);
    EXPECT_EQ(20, result[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(3);
    TDynamicMatrix<int> m1(8);
    ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(3);
    m[0][0] = 15; m[1][1] = 30;
    TDynamicMatrix<int> m1(3);
    m1[0][0] = 5; m1[1][1] = 10;
    TDynamicMatrix<int> result = m - m1;
    EXPECT_EQ(10, result[0][0]);
    EXPECT_EQ(20, result[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m(3);
    TDynamicMatrix<int> m1(9);
    ASSERT_ANY_THROW(m - m1);
}