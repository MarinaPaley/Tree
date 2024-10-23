﻿#include "pch.h"
#include "CppUnitTest.h"
#include "..\Tree\Tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tree;
namespace TreeTests
{
	TEST_CLASS(TreeTests)
	{
	public:
		
		TEST_METHOD(Add_ValidData_Success)
		{
			// arrange
			Tree tree;
			const size_t expected = 1;

			// act
			tree.Add(1);

			// assert
			Assert::AreEqual(expected, tree.GetSize());
		}

		TEST_METHOD(HasValue_Exists_True)
		{
			// arrange
			Tree tree{ 1 };
			// act
			auto actual = tree.HasValue(1);
			// assert
			Assert::IsTrue(actual);
		}

		TEST_METHOD(HasValue_NotExist_False)
		{
			// arrange
			Tree tree{ 1 };
			// act
			auto actual = tree.HasValue(2);
			// assert
			Assert::IsFalse(actual);
		}
	};
}
