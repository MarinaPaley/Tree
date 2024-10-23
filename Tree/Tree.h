#pragma once
#include <initializer_list>
#include <vector>

namespace tree
{
	class Tree;

	/**
	* @brief ����� ������������� ������ � ���� ������ "�������" ��������.
	* @param tree ������.
	* @return ������ � ���� ������ "�������" ��������.
	*/
	std::wstring ToString(const Tree& tree);

	/**
	* @brief �������� ��������� ���� ��������.
	* @return \c true, ���� �����. ����� \c - false.
	*/
	bool operator==(const Tree& lha, const Tree& rha);

	/**
	* @brief ����� ������.
	*/
	class Tree
	{
	private:
		struct Node;

		/**
		 * @brief ����� ������������� ���� � ���� ������ "�������" ��������.
		 * @param node ����.
		 * @return ���� � ���� ������ "�������" ��������.
		*/
		std::wstring ToString(const Node& node);

		/**
		* @brief ��������� ���� ��������� ������.
		*/
		struct Node
		{
			/**
			* @brief ������.
			*/
			int data;

			/**
			* @brief ��������� �� ��������.
			*/
			Node* parent;

			/**
			* @brief ��������� �� ������ �������.
			*/
			Node* left;

			/**
			* @brief ��������� �� ������� �������.
			*/
			Node* right;

			/**
			* @brief �������������� ����� ��������� ������ \c Tree::Node.
			* @param data �������� ����.
			*/
			Node(const int data);

			/**
			* @brief ���������� �����������.
			*/
			Node(const Node&) = delete;

			/**
			* @brief ������������ �����������.
			* @param other ������ ����.
			*/
			Node(Node&& other) = default;

			/**
			* @brief �������� �����������.
			* @return ������������� ������.
			*/
			Node& operator=(const Node&) = delete;

			/**
			* @brief �������� �����������.
			* @param other ������ ����.
			* @return ������������ ������.
			*/
			Node& operator=(Node&& other) = default;

			/**
			* @brief ����������.
			*/
			~Node();

			/**
			* @brief �������� ��������� � ������ �����.
			* @param lha ����� �������.
			* @param rha ������ �������.
			* @return \c true � ������ ���������, \c false � ��������� ������.
			*/
			friend bool operator==(const Node& lha, const Node& rha)
			{
				return lha.data == rha.data;
			}

			/**
			* @brief �������� ��������� � ������ �����.
			* @param lha ����� �������.
			* @param rha ������ �������.
			* @return \c 1 � �������� ���� ������, \c -1 � �������� ���� ������, ����� � \c 0.
			*/
			friend int operator<=>(const Node& lha, const Node& rha)
			{
				if (lha.data < rha.data)
				{
					return -1;
				}
				if (lha.data > rha.data)
				{
					return 1;
				}
				return 0;
			}

			/**
			 * @brief �������� �� ������� ���� ������ ��� ������.
			 * @return \c true - ��������, \c false - ���.
			*/
			bool IsRoot() const noexcept;

			/**
			 * @brief �������� �� ������� ���� ������ ��� ������.
			 * @return \c true - ��������, \c false - ���.
			*/
			bool IsLeaf() const noexcept;

			/**
			* @brief ������������� ���� � ��������� ����.
			*/
			std::string ToString() const noexcept;
		};

		/**
		 * @brief ��������� �� ������.
		*/
		Node* root;
		/**
		 * @brief ��������� �� ����� ���������.
		*/
		Node* left;
		/**
		 * @brief ��������� �� ������ ���������.
		*/
		Node* right;
		/**
		 * @brief ���������� ����� � ������.
		*/
		size_t size;
		/**
		 * @brief ������� ����.
		 * @param current ������� ����.
		 * @param node ����������� ����.
		 * @param parent ������������ ����.
		 * @return ����������� ����.
		*/
		Node* Insert(Node* current, Node* inserted, Node* parent);

		/**
		 * @brief ������� ���� �� ������.
		 * @param deleted ��������� ����.
		*/
		void Delete(Node* deleted);

		/**
		* @brief ������� ������� � ������.
		* @param current ������� ����.
		* @param target ������� �������.
		* @return ��������� ����.
		*/
		Node* Find(Node* current, const int target) const noexcept;

		/**
		 * @brief ���������, � ������� ���������� ���� ��������� 
		 � �������� ��������� �������� ������ �������� ������ ����������.
		 * @param parent ������������ ����.
		 * @param son �������� ����.
		*/
		void Transplant(Node* parent, Node* son);

		/**
		 * @brief ��������� ���������� ������������ ����.
		 * @param node ����, � �������� ���� �����.
		 * @return ��������� �� ���������� ����.
		*/
		Node* TreeMin(Node* node) const noexcept;

		/**
		 * @brief ��������� ���������� ������������� ����.
		 * @param node ����, � �������� ���� �����.
		 * @return ��������� �� ������������ ����.
		 */
		Node* TreeMax(Node* node) const noexcept;

		/**
		* @brief ������ ������� ������ �� ��������� ����.
		* @param current �������� ����.
		* @return ������� ������.
		*/
		int GetHeight(Node* current) const noexcept;

		/**
		 * @brief ����� ���������� � ������ �������.
		 * @param other ������ ������.
		*/
		void Swap(const Tree& other) noexcept;

		/**
		 * @brief �������� ��������� ����������.
		 * @param current ������� ����.
		*/
		void InOrderRemoveTree(Node* current);

		/**
		* @brief ������ ����� � ������� ������ ������ InOrder.
		*/
		std::vector<int> values;

		/**
		* @brief �������� ������� � ������� ������ ������ InOrder.
		*/
		void MakeValues();

		/**
		* @brief ������ ������.
		* @param current ������� ���� ������.
		*/
		void InOrder(Node* current);

	public:
		/**
		 * @brief �������������� ������ ������ \c tree::Tree.
		*/
		Tree();

		/**
		 * @brief �������������� ������ ������ \c tree::Tree.
		 * @param list ������ ���������������� ����������.
		*/
		Tree(std::initializer_list<int> list);

		/**
		 * @brief ����������. ��������� ������ ���� ::BaseBinaryTree<T> .
		*/
		~Tree();

		/**
		 * @brief ���������� ��������� ����� � ������.
		 * @return ���������� ����� � ������.
		*/
		size_t GetSize() const noexcept;

		/**
		 * @brief ����������, ����� �� ������.
		 * @return \c true, ���� ������, ����� \c false.
		*/
		bool IsEmpty() const noexcept;

		/**
		 * @brief ��������� ����� ���� � ������.
		 * @param value �������� ������ ����.
		 * @return \c true, ���� ���� ��������, ����� \c false.
		*/
		void Add(const int data);

		/**
		* @brief ������� ���� �� ������.
		* @param value �������� ���������� ����.
		* @return \c true, ���� ���� ������, ����� \c false.
		*/
		bool Remove(const int value);

		/**
		 * @brief �������� ���������� �� � ������ ���� � ���� ���������.
		 * @param value �������� �������� ����.
		 * @return \c true, ���� ����������, ����� \c false.
		*/
		bool HasValue(const int value) const noexcept;

		/**
		* @brief ��������� ������������� ������.
		*/
		std::string ToString() const noexcept;
	};
}