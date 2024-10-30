#include "pch.h"
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

		TEST_METHOD(AreEquals_SameTrees_IsTrue)
		{
			// arrange
			Tree tree1{ 1, 2, 3, 4, 5, 6, 7 };
			Tree tree2{ 1, 2, 3, 4, 5, 6, 7 };

			// act & assert
			Assert::AreEqual(tree1, tree2);
		}

		TEST_METHOD(InitializerCtor_ValidData_Success)
		{
			// arrange
			const std::string expected{ "{ 1 2 3 4 5 }" };

			// act
			Tree tree{ 1, 2, 3, 4, 5 };
			auto actual = tree.ToString();

			// assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Add_ExistingValueNode_False)
		{
			// arrange
			Tree tree{ 1, 2, 3, 4, 5 };

			// act & assert
			Assert::IsFalse(tree.Add(1));
		}

		TEST_METHOD(Remove_ExistingValueNode_True)
		{
			// arrange
			Tree tree{ 1, 2, 3, 4, 5 };

			// act & assert
			Assert::IsTrue(tree.Remove(1));
		}

		TEST_METHOD(Remove_NotExistingValueNode_False)
		{
			// arrange
			Tree tree{ 1, 2, 3, 4, 5 };

			// act & assert
			Assert::IsFalse(tree.Remove(6));
		}

		TEST_METHOD(RemoveCase1_ValidData_True)
		{
			// arrange
			Tree tree{ 15, 10, 20, 8, 12, 18, 25};

			// act & assert
			Assert::IsTrue(tree.Remove(18));
		}

		TEST_METHOD(RemoveCase2_RemoveWithRightSon_True)
		{
			// arrange
			Tree tree{ 15, 10, 20, 8, 12, 18, 25, 16, 19, 30 };

			// act & assert
			Assert::IsTrue(tree.Remove(25));
		}

		TEST_METHOD(RemoveCase2_RemoveWithLeftSon_True)
		{
			// arrange
			Tree tree{ 15, 10, 20, 8, 12, 18, 25, 16, 19, 23 };

			// act & assert
			Assert::IsTrue(tree.Remove(25));
		}

		TEST_METHOD(RemoveCase3_ValidData_True)
		{
			// arrange
			Tree tree{ 15, 10, 20, 8, 12, 18, 25 };

			// act & assert
			Assert::IsTrue(tree.Remove(15));
		}

		TEST_METHOD(AddEmtyList_ValidData_True)
		{
			// arrange
			Tree tree;
			

			// act & assert
			Assert::IsTrue(tree.Add(1));
		}
	};
}
