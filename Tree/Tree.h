#pragma once
#include <initializer_list>
namespace tree
{
	class Tree
	{
	private:
		struct Node
		{
			int data;
			Node* parent;
			Node* left;
			Node* right;
			Node(const int data);
			Node(const Node&) = delete;
			Node(Node&& other) = default;
			Node& operator=(const Node&) = delete;
			Node& operator=(Node&& other) = default;
			~Node();
			friend bool operator==(const Node& lha, const Node& rha)
			{
				return lha.data == rha.data;
			}
			friend int operator<=>(const Node& lha, const Node& rha)
			{
				if (lha.data > rha.data)
				{
					return -1;
				}
				if (lha.data < rha.data)
				{
					return 1;
				}
				return 0;
			}
		};
		Node* root;
		Node* left;
		Node* right;
		size_t size;
		Node* Insert(Node* current, Node* inserted, Node* parent);
	public:
		Tree();
		Tree(std::initializer_list<int> list);
		size_t GetSize() const noexcept;
		bool IsEmpty() const noexcept;
		void Add(const int data);
	};
}