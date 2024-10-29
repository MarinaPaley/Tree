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
	if (deleted->IsLeaf())// case 1
	{
		delete deleted;
		deleted = nullptr;
	}
	else if (nullptr == deleted->left) // case 2
	{
		this->Transplant(deleted, deleted->right);
	}
	else if (nullptr == deleted->right) // case 2
	{
		this->Transplant(deleted, deleted->left);

	}
	else { // Case 3
		auto successor = this->TreeMin(deleted->right);
		if (successor->parent != deleted) 
		{
			this->Transplant(successor, successor->right);
			successor->right = deleted->right;
			successor->right->parent = successor;
		}

		this->Transplant(deleted, successor);
		successor->left = deleted->left;
		successor->left->parent = successor;
	}
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
	if (nullptr == parent->parent) {
		this->root = son;
	}
	else if (parent == parent->parent->left) {
		parent->parent->left = son;
	}
	else {
		parent->parent->right = son;
	}
	if (nullptr != son) {
		son->parent = parent->parent;
	}
}


tree::Tree::Node* tree::Tree::TreeMin(Node* node) const noexcept
{
	while (nullptr != node->left)
	{
		node = node->left;
	}

	return node;
}

tree::Tree::Node* tree::Tree::TreeMax(Node* node) const noexcept
{
	while (nullptr != node->right)
	{
		node = node->right;
	}

	return node;
}

int tree::Tree::GetHeight(Node* current) const noexcept
{
	if (nullptr == current)
	{
		return 0;
	}

	auto left = this->GetHeight(current->left);
	auto right = this->GetHeight(current->right);

	return std::max(left, right) + 1;
}

void tree::Tree::Swap(Tree& other) noexcept
{
	std::swap(this->root, other.root);
	std::swap(this->left, other.left);
	std::swap(this->right, other.right);
	std::swap(this->size, other.size);
}

void tree::Tree::InOrderRemoveTree(Node* current)
{
	if (nullptr == current)
	{
		return;
	}

	--this->size;
	this->InOrderRemoveTree(current->left);
	this->InOrderRemoveTree(current->right);

	delete current;
	current = nullptr;
}

void tree::Tree::MakeValues()
{
	this->values.clear();
	this->InOrder(this->root);
}

void tree::Tree::InOrder(Node* current)
{
	if (nullptr == current)
	{
		return;
	}

	this->InOrder(current->left);
	this->values.push_back(current->data);
	this->InOrder(current->right);
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
	this->InOrderRemoveTree(this->root);
}

size_t tree::Tree::GetSize() const noexcept
{
	return this->size;
}

bool tree::Tree::IsEmpty() const noexcept
{
	return nullptr == this->root;
}

bool tree::Tree::Add(const int data)
{
	if (this->HasValue(data))
	{
		return false;
	}

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
	this->MakeValues();
	return true;
}

bool tree::Tree::Remove(const int value)
{
	if (this->IsEmpty())
	{
		return false;
	}

	auto deleted = this->Find(this->root, value);
	if (nullptr == deleted)
	{
		return false;
	}

	this->Delete(deleted);
	--this->size;
	this->MakeValues();

	return true;
}

bool tree::Tree::HasValue(const int value) const noexcept
{
	return nullptr != this->Find(this->root, value);
}

std::string tree::Tree::ToString() const noexcept
{
	std::ostringstream buffer{};
	buffer << "{ ";
	for (auto it = this->values.cbegin(); it != this->values.cend(); ++it)
	{
		buffer << (*it) << " ";
	}
	buffer << "}";

	return buffer.str();
}

std::wstring tree::ToString(const Tree& tree)
{
	auto temp = tree.ToString();
	return std::wstring{ temp.cbegin(), temp.cend() };
}

bool tree::operator==(const Tree& lha, const Tree& rha)
{
	return lha.ToString() == rha.ToString();
}

std::ostream& tree::operator<<(std::ostream& out, const Tree& tree)
{
	out << tree.ToString();
	return out;
}
