#include <iostream>
#include "Binary_Tree.h"

int main() {
    btree::BTREE tree("test.txt"); // Предполагается, что данные находятся в файле data.txt

    std::cout << "Дерево до удаления:" << std::endl;
    tree.print();

    tree.remove_below_average(); // Удаляем элементы ниже среднего арифметического

    std::cout << "Дерево после удаления:" << std::endl;
    tree.print();

    return 0;
}
