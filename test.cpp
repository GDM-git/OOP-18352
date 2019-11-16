#include "pch.h"
#include "gtest/gtest.h"
#include "RNA.h"

TEST(TestInit, TestRnkConstructor) {
	Nucleotide Nucle = C;
	RNA RNA_test(Nucle, 1000);
	RNA RNA_test_2;
	bool tmp = true;
	for (size_t i = 0; i < RNA_test.RNA_length(); i++) {
		if ((Nucleotide)RNA_test[i] != Nucle) {
			tmp = false;
			break;
		}
	}

	EXPECT_EQ(1000, RNA_test.RNA_length());
	EXPECT_EQ(0, RNA_test_2.RNA_length());
	EXPECT_TRUE(tmp);
}
TEST(TestCopy, TestCopyRNK) {
	Nucleotide n = C;
	const RNA RNA_test(n, 1000);
	const RNA RNA_test_2(RNA_test);
	EXPECT_EQ(RNA_test.RNA_length(), RNA_test_2.RNA_length());
	EXPECT_EQ(RNA_test.RNA_capacity(), RNA_test_2.RNA_capacity());
	bool tmp = true;
	bool IsEqual = (RNA_test == RNA_test_2);
	for (size_t i = 0; i < RNA_test.RNA_length(); i++) {
		if (RNA_test[i] != RNA_test_2[i]) {
			tmp = false;
			break;
		}
	}
	EXPECT_TRUE(tmp);
	EXPECT_TRUE(IsEqual);
}
TEST(TestAssigning, TestOperatorAssigningRNK) {
	Nucleotide n = C;
	RNA rn1(n, 1000);
	RNA rn2;
	rn2 = rn1;
	EXPECT_EQ(rn1.RNA_length(), rn2.RNA_length());
	EXPECT_EQ(rn1.RNA_capacity(), rn2.RNA_capacity());
	bool tmp = true;
	bool IsEqual = (rn1 == rn2);
	for (size_t i = 0; i < rn1.RNA_length(); i++) {
		if (rn1[i] != rn2[i]) {
			tmp = false;
			break;
		}
	}
	EXPECT_TRUE(tmp);
	EXPECT_TRUE(IsEqual);
}
TEST(TestAssigning, TestAssigningThisToThis) {
	Nucleotide n = C;
	RNA rn1(n, 1000);
	RNA rn2(rn1);
	rn1 = rn1;
	bool tmp = true;
	for (size_t i = 0; i < rn1.RNA_length(); i++) {
		if (rn1[i] != rn2[i]) {
			tmp = false;
			break;
		}
	}
	EXPECT_TRUE(rn1.RNA_length() == rn2.RNA_length());
	EXPECT_TRUE(tmp);
}
TEST(TestNot, TestNotRnk) {
	Nucleotide n = C;
	RNA rn1(n, 1000);
	RNA rn2;
	rn2 = !rn1;
	EXPECT_EQ(rn1.RNA_length(), rn2.RNA_length());
	EXPECT_EQ(rn1.RNA_capacity(), rn2.RNA_capacity());
	bool tmp = true;
	for (size_t i = 0; i < rn1.RNA_length(); i++) {
		switch ((Nucleotide)rn1[i])
		{
		case A:
			if (rn2[i] != T) tmp = false;
			break;
		case C:
			if (rn2[i] != G) tmp = false;
			break;
		case G:
			if (rn2[i] != C) tmp = false;
			break;
		case T:
			if (rn2[i] != A) tmp = false;
			break;
		default:
			break;
		}
		if (tmp == false) break;
	}
	EXPECT_TRUE(tmp);
}
TEST(TrimTest, TestTrimRNK) {
	RNA rn2(G, 1000);
	rn2.RNA_trim(0);
	EXPECT_EQ(rn2.RNA_length(), 0);
	EXPECT_EQ(rn2.RNA_capacity(), 0);
}
TEST(TestTime, RunTimeSmall) {
	RNA rn;
	int size = 10000;
	for (int i = 0; i < size; i++) {
		rn[i] = G;
	}
	EXPECT_TRUE(true);
}
TEST(TestTime, RunTimeBig) {
	RNA rn;
	int size = 1000000;
	for (int i = 0; i < size; i++) {
		rn[i] = G;
	}
	EXPECT_TRUE(true);
}

TEST(TestOperatorSum, TestCorrect) {
	size_t size1 = 1000;
	size_t size2 = 1000;
	Nucleotide n1 = C;
	Nucleotide n2 = G;

	RNA rn1(n1, size1);
	RNA rn2(n2, size2);
	const RNA rn3 = rn1 + rn2;
	bool isEqual = true;
	for (size_t i = 0; i < size1; i++) {
		if (rn3[i] != n1) {
			isEqual = false;
			break;
		}
	}
	if (isEqual == true) {
		for (size_t i = size1; i < rn3.RNA_length(); i++) {
			if (rn3[i] != n2) {
				isEqual = false;
				break;
			}
		}
	}

	EXPECT_TRUE(isEqual);
}
TEST(TestOperatorSum, TestBoundaryCauseSizeOf) {
	size_t size1 = sizeof(size_t);
	size_t size2 = 3 * sizeof(size_t);
	Nucleotide n1 = C;
	Nucleotide n2 = G;

	RNA rn1(n1, size1);
	RNA rn2(n2, size2);
	const RNA rn3 = rn1 + rn2;
	bool isEqual = true;
	for (size_t i = 0; i < size1; i++) {
		if (rn3[i] != n1) {
			isEqual = false;
			break;
		}
	}
	if (isEqual == true) {
		for (size_t i = size1; i < rn3.RNA_length(); i++) {
			if (rn3[i] != n2) {
				isEqual = false;
				break;
			}
		}
	}
	EXPECT_TRUE(isEqual);
}
TEST(TestOperatorSum, TestBoundaryCauseSizeOfMinusOne) {
	size_t size1 = (2 * sizeof(size_t)) - 1;
	size_t size2 = 3 * sizeof(size_t);
	Nucleotide n1 = C;
	Nucleotide n2 = G;

	RNA rn1(n1, size1);
	RNA rn2(n2, size2);
	const RNA rn3 = rn1 + rn2;
	bool isEqual = true;
	for (size_t i = 0; i < size1; i++) {
		if (rn3[i] != n1) {
			isEqual = false;
			break;
		}
	}
	if (isEqual == true) {
		for (size_t i = size1; i < rn3.RNA_length(); i++) {
			if (rn3[i] != n2) {
				isEqual = false;
				break;
			}
		}
	}
	EXPECT_TRUE(isEqual);
}
TEST(TestNotEqual, TestNotEqualRnk) {
	Nucleotide n = C;
	Nucleotide N = G;
	RNA rn1(n, 1000);
	RNA rn2(N, 1000);
	RNA rn3;
	bool IsEqual = (rn1 == rn2);
	EXPECT_FALSE(IsEqual);
	IsEqual = (rn1 == rn3);
	EXPECT_FALSE(IsEqual);
	IsEqual = (rn2 == rn3);
	EXPECT_FALSE(IsEqual);
}

TEST(TestIsCompl, TestIsComplRnk) {
	size_t size = 10000;
	Nucleotide n = C;
	RNA rn1(n, size);
	RNA rn2 = !rn1;
	EXPECT_TRUE(rn1.RNA_complementarity(rn2));
}

TEST(TestSplit, TestSplitRunTime) {
	size_t size = 10000;
	size_t splitNum = 100;
	Nucleotide n = C;
	RNA rn1(n, size);
	const RNA rn2 = rn1.RNA_split(splitNum);
	rn1 = !rn1;
	size_t tmpSize = rn1.RNA_length();
	bool tmp = true;
	for (size_t i = 0; i < tmpSize; i++) {
		if (((Nucleotide)rn1[i]) != G) {
			tmp = false;
			break;
		}
		if (i >= tmpSize && rn2[i - tmpSize] != C) {
			tmp = false;
			break;
		}
	}
	EXPECT_TRUE(tmp);
}
