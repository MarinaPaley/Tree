#include <iostream>
#include <sstream>
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

bool tree::Tree::Node::IsRoot() const noexcept
{
	return nullptr == this->parent;
}

bool tree::Tree::Node::IsLeaf() const noexcept
{
	return nullptr == this->left && nullptr == this->right;
}

std::string tree::Tree::Node::ToString() const noexcept
{
	std::ostringstream buffer{};
	buffer << this->data;
	return buffer.str();
}

std::wstring tree::Tree::ToString(const Node& node)
{
	auto temp = node.ToString();
	return std::wstring{ temp.cbegin(), temp.cend() };
}

tree::Tree::Node* tree::Tree::Insert(Node* current, Node* inserted, Node* parent)
{
	if (nullptr == current)
	{
		current = inserted;
		current->parent = parent;
		return current;
	}

	if (*inserted < *current) // Не адреса узлов, а значения! Оператор *
	{
		current->left = this->Insert(current->left, inserted, current);
	}
	else if (*inserted > *current) {
		current->right = this->Insert(current->right, inserted, current);
	}

	return current;
}

void tree::Tree::Delete(Node* deleted)
{
}

tree::Tree::Node* tree::Tree::Find(Node* current, const int target) const noexcept
{
	if (nullptr == current)
	{
		return nullptr;
	}

	if (target < current->data)
	{
		return this->Find(current->left, target);
	}
	else if (target > current->data)
	{
		return this->Find(current->right, target);
	}
	else
	{
		return current;
	}

}

void tree::Tree::Transplant(Node* parent, Node* son)
{
}

tree::Tree::Node* tree::Tree::TreeMin(Node* node) const noexcept
{
	return nullptr;
}

tree::Tree::Node* tree::Tree::TreeMax(Node* node) const noexcept
{
	return nullptr;
}

int tree::Tree::GetHeight(Node* current) const noexcept
{
	return 0;
}

void tree::Tree::Swap(const Tree& other) noexcept
{
}

void tree::Tree::InOrderRemoveTree(Node* current)
{
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

tree::Tree::~Tree()
{
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

bool tree::Tree::Remove(const int value)
{
	return false;
}

bool tree::Tree::HasValue(const int value) const noexcept
{
	return nullptr != this->Find(this->root, value);
}

std::string tree::Tree::ToString()
{
	return std::string();
}
