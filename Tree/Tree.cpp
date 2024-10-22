#include <iostream>
#include "Tree.h"

tree::Tree::Node::Node(const int data) 
	: data{data}, parent{nullptr}, left{nullptr}, right{nullptr}
{
}

tree::Tree::Node::~Node()
{
	if (nullptr != this->parent)
	{
		if (this->parent->left == this)
		{
			this->parent->left = nullptr;
		}
		else
		{
			this->parent->right = nullptr;
		}
	}
	// можно не писать
	data = 0;
	this->left = nullptr;
	this->right = nullptr;
}

std::wstring tree::Tree::ToString(const Node& node)
{
	auto temp = node.ToString();
	return std::wstring{ temp.cbegin(), temp.cend() };
}

tree::Tree::Node* tree::Tree::Insert(Node* current, Node* inserted, Node* parent)
{
	return nullptr;
}

tree::Tree::Tree() : root{nullptr}, left{nullptr}, right {nullptr}, size{0}
{
}

tree::Tree::Tree(std::initializer_list<int> list) : Tree()
{
	for (auto& item : list)
	{
		this->Add(item);
	}
}

size_t tree::Tree::GetSize() const noexcept
{
	return this->size;
}

bool tree::Tree::IsEmpty() const noexcept
{
	return nullptr == this->root;
}

void tree::Tree::Add(const int data)
{
	auto node = new Node(data);
	if (this->IsEmpty())
	{
		this->root = node;
	}
	else
	{
		this->root = this->Insert(this->root, node, this->root->parent);
	}

	++this->size;
}
