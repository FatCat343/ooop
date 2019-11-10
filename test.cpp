#include "gtest/gtest.h"
#include "../Project1/RNA.cpp"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
TEST(SampleTest2, LargeTest) {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		RNA rna1;
		for (size_t i = 1; i < 1000000; i++) {
			rna1 = rna1 + 'C';
		}
		char nukl = rna1[23];
		EXPECT_EQ(nukl, 'C') << "wrong output";
	}
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2)) {
		EXPECT_EQ(1, 0) << "detected memory leaks";
	}
}

TEST(SampleTest2, EqualityTest) {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		RNA rna1(998, 'C');
		RNA rna2 = rna1;
		rna2 = rna2;
		if (rna1 == rna2);
		else EXPECT_EQ(1, 0) << "equality fails";
	}
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2)) {
		EXPECT_EQ(1, 0) << "detected memory leaks";
	}
}
TEST(SampleTest2, ConstructorTest) {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		RNA rna1, rna2(999, 'G');
		for (size_t i = 1; i <= 999; i++) {
			char nukl = rna2.get(i);
			EXPECT_EQ(nukl, 'G') << "constructor failed";
		}
		RNA rna3(rna2);
		for (size_t i = 1; i <= 999; i++) {
			char nukl = rna3.get(i);
			EXPECT_EQ(nukl, 'G') << "copyconstructor failed";
		}

	}
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2)) EXPECT_EQ(1, 0) << "detected memory leaks";
}
TEST(SampleTest2, BinaryOpsTest) {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		RNA rna1(1000, 'G'), rna2(999, 'G');
		if (rna1 == rna2) EXPECT_EQ(1, 0) << "equality fails";
	}
	{
		RNA rna1(999, 'G'), rna2(999, 'G');
		if (rna1 == rna2);
		else EXPECT_EQ(1, 0) << "equality fails";
	}
	{
		RNA rna1(999, 'G'), rna2(999, 'C');
		if (rna1 != rna2);
		else EXPECT_EQ(1, 0) << "unequality fails";
	}
	{
		RNA rna1(1001, 'U'), rna2(1001, 'U');
		if (rna1 != rna2) EXPECT_EQ(1, 0) << "unequality fails";
	}
	{
		RNA rna1(999, 'C'), rna2(998, 'C');
		if (rna1.iscomplementary(rna2)) EXPECT_EQ(1, 0) << "iscomplementary fails";
	}
	{
		RNA rna1(999, 'A'), rna2(999, 'C');
		if (rna1.iscomplementary(rna2)) EXPECT_EQ(1, 0) << "iscomplementary fails";
	}
	{
		RNA rna1(999, 'G'), rna2(999, 'C');
		if (rna1.iscomplementary(rna2));
		else EXPECT_EQ(1, 0) << "iscomplementary fails";
	}
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2)) EXPECT_EQ(1, 0) << "detected memory leaks";
}
TEST(SampleTest2, PlusTest) {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		RNA rna1(1001, 'C'), rna2(999, 'G');
		RNA rna3 = rna1 + rna2;
		for (size_t i = 1; i <= 2000 ; i++) {
			char nukl = rna3.get(i);
			if (i <= 1001) EXPECT_EQ(nukl, 'C') << "plus failed";
			else EXPECT_EQ(nukl, 'G') << "plus failed";
		}
	}
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2)) EXPECT_EQ(1, 0) << "detected memory leaks";
}
TEST(SampleTest2, SplitTest) {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		RNA rna1(2000 , 'G');
		char nukl;
		RNA rna2 = rna1.split(203);
		for (size_t i = 1; i <= 2000; i++) {
			if (i <= 203) nukl = rna1.get(i);
			else nukl = rna2.get(i - 203);
			EXPECT_EQ(nukl, 'G') << "split failed. wrong output on";
		}
	}
	{
		RNA rna1;
		RNA rna2 = rna1.split(0);
		EXPECT_EQ(rna2.RNAusedlen(), 0);
	}
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2)) EXPECT_EQ(1, 0) << "detected memory leaks";
}
TEST(SampleTest2, CreatigComplimentaryRnaTest) {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		RNA rna1(499, 'G');
		char nukl;
		RNA rna2 = !rna1;
		for (size_t i = 1; i <= 499; i++) {
			nukl = rna2.get(i);
			EXPECT_EQ(nukl, 'C') << "split failed";
		}
	}
	{
		RNA rna1(400, 'U');
		char nukl;
		RNA rna2 = !rna1;
		for (size_t i = 1; i <= 400; i++) {
			nukl = rna2.get(i);
			EXPECT_EQ(nukl, 'A') << "split failed";
		}
	}
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2)) EXPECT_EQ(1, 0) << "detected memory leaks";
}
TEST(SampleTest2, IndexTest) {
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		RNA rna1(1000, 'G');
		char nukl = rna1[50];
		EXPECT_EQ(nukl, 'G') << "reading from rna by index failed";
		
		RNA rna2(101, 'C');
		rna2[4] = 'A';
		for (size_t i = 1; i <= 101; i++) {
			nukl = rna2.get(i);
			if (i == 4) EXPECT_EQ(nukl, 'A') << "writting to rna by index failed";
			else EXPECT_EQ(nukl, 'C') << "writting to rna by index failed";
		}
		
		RNA rna3(102, 'U');
		rna3[10] = rna1[9];
		for (size_t i = 1; i <= 102; i++) {
			nukl = rna3.get(i);
			if (i == 10) EXPECT_EQ(nukl, 'G') << "writting to rna by index failed";
			else EXPECT_EQ(nukl, 'U') << "writting to rna by index failed";
		}
	}
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2)) EXPECT_EQ(1, 0) << "detected memory leaks";
}