#include <iostream>
#include "..\Tree\Tree.h"

using namespace tree;
int main()
{
    Tree tree{ 1, 2, 3, 4 };
    auto result = tree.HasValue(1);
    tree.Add(0);
    std::cout << result << "\n";
    auto tree1 = Tree();
    tree1.Add(1);
    std::cout << tree.ToString() << std::endl;
}
