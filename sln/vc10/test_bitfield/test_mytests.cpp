#include "tbitfield.h"
#include "tset.h"
#include <gtest.h>

TEST(MyTests, can_create_bitfield_with_size_default)
{
	ASSERT_NO_THROW(TBitField bf());
}

TEST(MyTests, check_clear_bit_twice)
{
	TBitField bf(3),_bf(3);
	bf = ~bf;
	bf.ClrBit(0);
	bf.ClrBit(0);

	_bf.SetBit(1);
	_bf.SetBit(2);
	EXPECT_EQ(_bf, bf);
}

TEST(MyTests, check_set_bit_twice)
{
	TBitField bf(3), _bf(3);
	bf.SetBit(1);
	bf.SetBit(1);

	_bf.SetBit(1);
	//_bf=010;
	EXPECT_EQ(_bf, bf);
}

TEST(MyTests, or_operator_applied_to_three_bitfields)
{
	TBitField bf1(4), bf2(4), bf3(4), _bf(4);
	//bf1=0010
	bf1.SetBit(2);
	//bf2=1000
	bf2.SetBit(0);
	//bf3=1100
	bf3.SetBit(0);
	bf3.SetBit(1);

	//_bf=1110
	_bf.SetBit(0);
	_bf.SetBit(1);
	_bf.SetBit(2);
	EXPECT_EQ(_bf, bf1 | bf2 | bf3);
}

TEST(MyTests, and_operator_applied_to_three_bitfields)
{
	TBitField bf1(4), bf2(4), bf3(4), _bf(4);
	//bf1=0110
	bf1.SetBit(1);
	bf1.SetBit(2);
	//bf2=1011
	bf2.SetBit(0);
	bf2.SetBit(2);
	bf2.SetBit(3);
	//bf3=1110
	bf3.SetBit(0);
	bf3.SetBit(1);
	bf3.SetBit(2);

	//_bf=0010
	_bf.SetBit(2);
	EXPECT_EQ(_bf, bf1 & bf2 & bf3);
}

TEST(MyTests, can_combine_three_sets)
{
	TSet s1(4), s2(4), s3(4), _s(4);
	//s1=1
	s1.InsElem(1);
	//s2=0
	s2.InsElem(0);
	//s3=0, 2
	s3.InsElem(0);
	s3.InsElem(2);

	//_s=0, 1, 2
	_s.InsElem(0);
	_s.InsElem(1);
	_s.InsElem(2);
	EXPECT_EQ(_s, s1 + s2 + s3);
}

TEST(MyTests, can_intersect_three_sets)
{
	TSet s1(4), s2(4), s3(4), _s(4);
	//s1=1, 2
	s1.InsElem(1);
	s1.InsElem(2);
	//s2=0, 2, 3
	s2.InsElem(0);
	s2.InsElem(2);
	s2.InsElem(3);
	//s3=0, 1, 2
	s3.InsElem(0);
	s3.InsElem(1);
	s3.InsElem(2);

	//_bf=2
	_s.InsElem(2);
	EXPECT_EQ(_s, s1 * s2 * s3);
}

TEST(MyTests, can_combine_set_with_elem)
{
	const int size = 5;
	const int k = 2;
	TSet s1(size), s2(size);
	s1 = s1 + k;

	s2.InsElem(2);
	EXPECT_EQ(s2, s1);
}

TEST(MyTests, can_difference_set_with_elem)
{
	const int size = 5;
	const int k = 2;
	TSet s1(size), s2(size);
	s1 = ~s1;
	s1 = s1 - k;

	s2.InsElem(2);
	s2 = ~s2;
	s2.DelElem(2);
	EXPECT_EQ(s2, s1);
}