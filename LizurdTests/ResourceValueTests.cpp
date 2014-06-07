#include "stdafx.h"
#include "CppUnitTest.h"
#include "Defines.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Lizurd;

namespace LizurdTests
{		
	TEST_CLASS(ResourceValueTestClass)
	{
	public:
		
		TEST_METHOD(TestGreaterThanOrEqualShouldPass)
		{
			ResourceValue value(100, 0, 1, 10);
			ResourceValue cost(50, 0, 1);

			Assert::IsTrue(value >= cost);
		}

		TEST_METHOD(TestGreaterThanOrEqualVespyneOverShouldFail)
		{
			ResourceValue value(100, 0, 1, 10);
			ResourceValue cost(50, 10, 1);

			Assert::IsFalse(value >= cost);
		}

		TEST_METHOD(TestGreaterShouldPass)
		{
			ResourceValue value(100, 0, 1, 10);
			ResourceValue cost(100, 0, 1);

			Assert::IsTrue(value == cost);
		}

		TEST_METHOD(TestGreaterThanOrEqualWithVespyneShouldPass)
		{
			ResourceValue value(100, 100, 1, 10);
			ResourceValue cost(50, 50, 1);

			Assert::IsTrue(value >= cost);
		}

		TEST_METHOD(TestGreaterThanOrEqualWithSupplyShouldPass)
		{
			ResourceValue value(100, 100, 1, 10);
			ResourceValue cost(50, 50, 9);

			Assert::IsTrue(value >= cost);
		}

		TEST_METHOD(TestGreaterThanOrEqualShouldFail)
		{
			ResourceValue value(100, 0, 1, 10);
			ResourceValue cost(500, 0, 1);

			Assert::IsFalse(value >= cost);
		}

		TEST_METHOD(TestGreaterThanOrEqualWithVespyneShouldFail)
		{
			ResourceValue value(100, 100, 1, 10);
			ResourceValue cost(500, 500, 1);

			Assert::IsFalse(value >= cost);
		}
		TEST_METHOD(TestGreaterThanOrEqualWithSupplyShouldFail)
		{
			ResourceValue value(100, 100, 5, 10);
			ResourceValue cost(50, 50, 6);

			Assert::IsFalse(value >= cost);
		}

		TEST_METHOD(TestPlus)
		{
			ResourceValue value(100, 100, 1, 10);
			ResourceValue cost(50, 50, 90);
			ResourceValue result(150, 150, 91, 10);
			Assert::IsTrue((value + cost) == result);
		}
		TEST_METHOD(TestPlusEqual)
		{
			ResourceValue value(100, 100, 1, 10);
			ResourceValue cost(50, 50, 90);
			ResourceValue result(150, 150, 91, 10);
			value += cost;
			Assert::IsTrue(value == result);
		}
	};
}