#include "tlist.h"

#include <gtest.h>



TEST(TList, can_get_length)
{
	TList<int>  bf;

	EXPECT_EQ(0, bf.GetLength());
}

TEST(TList, can_construct_copy)
{
	TList<int>  a;
	int* n{ new int[3] { 1, 2, 3 } };
	for (size_t i = 0; i < 3; i++)
	{
		a.PushEnd(&n[i]);
	}

	TList<int> b(a);
	TListIterator<int> iter = b.begin();
	EXPECT_EQ(1, **iter);
	++iter;
	EXPECT_EQ(2, **iter);
	++iter;
	EXPECT_EQ(3, **iter);
}
TEST(TList, operator_eq)
{
	TList<int>  a;
	int* n{ new int[3] { 1, 2, 3 } };
	for (size_t i = 0; i < 3; i++)
	{
		a.PushEnd(&n[i]);
	}
	TList<int> b, c;

	c = b = a;

	TListIterator<int> iter = b.begin();
	EXPECT_EQ(1, **iter);
	++iter;
	EXPECT_EQ(2, **iter);
	++iter;
	EXPECT_EQ(3, **iter);
	iter = c.begin();
	EXPECT_EQ(1, **iter);
	++iter;
	EXPECT_EQ(2, **iter);
	++iter;
	EXPECT_EQ(3, **iter);
}
TEST(TList, can_push_begin)
{
	TList<int>  a;
	int* n{ new int[3] { 1, 2, 3 } };
	for (size_t i = 0; i < 3; i++)
	{
		a.PushEnd(&n[i]);
	}
	int v = 4;
	a.PushBegin(&v);
	EXPECT_EQ(4, **a.begin());
}
TEST(TList, can_del_begin)
{
	TList<int>  a;
	int* n{ new int[3] { 1, 2, 3 } };
	for (size_t i = 0; i < 3; i++)
	{
		a.PushEnd(&n[i]);
	}
	a.DelBegin();
	EXPECT_EQ(2, **a.begin());
}
TEST(TList, can_push_end)
{
	TList<int>  a;
	int* n{ new int[3] { 1, 2, 3 } };
	for (size_t i = 0; i < 3; i++)
	{
		a.PushEnd(&n[i]);
	}
	int v = 4;
	a.PushEnd(&v);
	for (auto i = a.begin(); i != a.end(); ++i)
		if (++i == a.end()) {
			EXPECT_EQ(4, **i);
			break;
		}
}
TEST(TList, can_del_end)
{
	TList<int>  a;
	int* n{ new int[3] { 1, 2, 3 } };
	for (size_t i = 0; i < 3; i++)
	{
		a.PushEnd(&n[i]);
	}
	a.DelEnd();
	for (auto i = a.begin(); i != a.end(); ++i)
		if (++i == a.end()) {
			EXPECT_EQ(2, **i);
			break;
		}
}