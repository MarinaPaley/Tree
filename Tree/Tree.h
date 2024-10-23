#pragma once
#include <initializer_list>
#include <vector>

namespace tree
{
	class Tree;

	/**
	* @brief Метод представления дерева в виде строки "широких" символов.
	* @param tree Дерево.
	* @return Дерево в виде строки "широких" символов.
	*/
	std::wstring ToString(const Tree& tree);

	/**
	* @brief Оператор равенства двух деревьев.
	* @return \c true, если равны. Иначе \c - false.
	*/
	bool operator==(const Tree& lha, const Tree& rha);

	/**
	* @brief Класс дерево.
	*/
	class Tree
	{
	private:
		struct Node;

		/**
		 * @brief Метод представления узла в виде строки "широких" символов.
		 * @param node Узел.
		 * @return Узел в виде строки "широких" символов.
		*/
		std::wstring ToString(const Node& node);

		/**
		* @brief Структура узел бинарного дерева.
		*/
		struct Node
		{
			/**
			* @brief Данные.
			*/
			int data;

			/**
			* @brief Указатель на родителя.
			*/
			Node* parent;

			/**
			* @brief Указатель на левого потомка.
			*/
			Node* left;

			/**
			* @brief Указатель на правого потомка.
			*/
			Node* right;

			/**
			* @brief Инициализирует новый экземпляр класса \c Tree::Node.
			* @param data Значение узла.
			*/
			Node(const int data);

			/**
			* @brief Контруктор копирования.
			*/
			Node(const Node&) = delete;

			/**
			* @brief Перемещающий конструктор.
			* @param other Другой узел.
			*/
			Node(Node&& other) = default;

			/**
			* @brief Оператор копирования.
			* @return Скопированный объект.
			*/
			Node& operator=(const Node&) = delete;

			/**
			* @brief Оператор перемещения.
			* @param other Другой узел.
			* @return Перемещенный объект.
			*/
			Node& operator=(Node&& other) = default;

			/**
			* @brief Деструктор.
			*/
			~Node();

			/**
			* @brief Оператор сравнения с другим узлом.
			* @param lha Левый операнд.
			* @param rha Правый операнд.
			* @return \c true в случае тождества, \c false в противном случае.
			*/
			friend bool operator==(const Node& lha, const Node& rha)
			{
				return lha.data == rha.data;
			}

			/**
			* @brief Оператор сравнения с другим узлом.
			* @param lha Левый операнд.
			* @param rha Правый операнд.
			* @return \c 1 – значение узла больше, \c -1 – значение узла меньше, иначе – \c 0.
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
			 * @brief Является ли текущий узел дерева его корнем.
			 * @return \c true - является, \c false - нет.
			*/
			bool IsRoot() const noexcept;

			/**
			 * @brief Является ли текущий узел дерева его листом.
			 * @return \c true - является, \c false - нет.
			*/
			bool IsLeaf() const noexcept;

			/**
			* @brief Представление узда в строковом виде.
			*/
			std::string ToString() const noexcept;
		};

		/**
		 * @brief Указатель на корень.
		*/
		Node* root;
		/**
		 * @brief Указатель на левое поддерево.
		*/
		Node* left;
		/**
		 * @brief Указатель на правое поддерево.
		*/
		Node* right;
		/**
		 * @brief Количество узлов в дерево.
		*/
		size_t size;
		/**
		 * @brief Вставка узла.
		 * @param current Текущий узел.
		 * @param node Вставляемый узел.
		 * @param parent Родительский узел.
		 * @return Обновленный узел.
		*/
		Node* Insert(Node* current, Node* inserted, Node* parent);

		/**
		 * @brief Удаляет узел из дерева.
		 * @param deleted Удаляемый узел.
		*/
		void Delete(Node* deleted);

		/**
		* @brief Находит элемент в дереве.
		* @param current Текущий узел.
		* @param target Искомый элемент.
		* @return Найденный узел.
		*/
		Node* Find(Node* current, const int target) const noexcept;

		/**
		 * @brief Процедура, в которой заменяется одно поддерево 
		 в качестве дочернего элемента своего родителя другим поддеревом.
		 * @param parent Родительский узел.
		 * @param son Дочерний узел.
		*/
		void Transplant(Node* parent, Node* son);

		/**
		 * @brief Процедура нахождения минимального узла.
		 * @param node Узел, с которого идет поиск.
		 * @return Указатель на минималный узел.
		*/
		Node* TreeMin(Node* node) const noexcept;

		/**
		 * @brief Процедура нахождения максимального узла.
		 * @param node Узел, с которого идет поиск.
		 * @return Указатель на максимальный узел.
		 */
		Node* TreeMax(Node* node) const noexcept;

		/**
		* @brief Расчет глубины дерева до заданного узла.
		* @param current Заданный узел.
		* @return Глубина дерева.
		*/
		int GetHeight(Node* current) const noexcept;

		/**
		 * @brief Обмен содержимым с другим деревом.
		 * @param other Другое дерево.
		*/
		void Swap(const Tree& other) noexcept;

		/**
		 * @brief Удаление элементов рекурсивно.
		 * @param current Текущий узел.
		*/
		void InOrderRemoveTree(Node* current);

		/**
		* @brief Вектор узлов в порядке обхода дерева InOrder.
		*/
		std::vector<int> values;

		/**
		* @brief Создание вектора в порядке обхода дерева InOrder.
		*/
		void MakeValues();

		/**
		* @brief Обхода дерева.
		* @param current Текущий узел дерева.
		*/
		void InOrder(Node* current);

	public:
		/**
		 * @brief Инициализирует объект класса \c tree::Tree.
		*/
		Tree();

		/**
		 * @brief Инициализирует объект класса \c tree::Tree.
		 * @param list Список инициплизирующих параметров.
		*/
		Tree(std::initializer_list<int> list);

		/**
		 * @brief Деструктор. Разрушает объект типа ::BaseBinaryTree<T> .
		*/
		~Tree();

		/**
		 * @brief Определяет количесто узлов в дереве.
		 * @return Количество узлов в дереве.
		*/
		size_t GetSize() const noexcept;

		/**
		 * @brief Определяет, путое ли дерево.
		 * @return \c true, если пустое, иначе \c false.
		*/
		bool IsEmpty() const noexcept;

		/**
		 * @brief Добавляет новый узел в дерево.
		 * @param value Значение нового узла.
		 * @return \c true, если узел добавлен, иначе \c false.
		*/
		void Add(const int data);

		/**
		* @brief Удаляет узел из дерева.
		* @param value Значение удаляемого узла.
		* @return \c true, если узел удален, иначе \c false.
		*/
		bool Remove(const int value);

		/**
		 * @brief Проверет содержится ли в дереве узел с таки значением.
		 * @param value Значение искомого узла.
		 * @return \c true, если содержится, иначе \c false.
		*/
		bool HasValue(const int value) const noexcept;

		/**
		* @brief Строковое представление делева.
		*/
		std::string ToString() const noexcept;
	};
}