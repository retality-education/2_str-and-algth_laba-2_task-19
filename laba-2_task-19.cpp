#include "Binary_Tree.h"
#include <Windows.h>
// Внешние функции
double calculate_average_recursive(btree::ptrNODE node, double& sum, int& count);
double calculate_average(btree::BTREE tree);
void remove_nodes_recursive(btree::ptrNODE node, double average);
void remove_nodes_iterative(btree::ptrNODE root, double average);
void remove_less_than(btree::BTREE tree, double average);
// Рекурсивная функция для вычисления среднего арифметического
double calculate_average_recursive(btree::ptrNODE node, double& sum, int& count) {
    if (!node) return 0.0;

    sum += node->info;
    count++;

    calculate_average_recursive(node->left, sum, count);
    calculate_average_recursive(node->right, sum, count);

    return sum / count;
}

// Функция для вычисления среднего арифметического (внешняя)
double calculate_average(btree::BTREE tree) {
    if (tree.empty()) return 0.0;

    double sum = 0.0;
    int count = 0;

    calculate_average_recursive(tree.get_root(), sum, count);

    return sum / count;
}

// Рекурсивная функция для удаления узлов меньше среднего
void remove_nodes_recursive(btree::ptrNODE node, double average) {
    if (!node) return;

    if (node->info < average) {
        // Удаляем текущий узел и заменяем его на правого потомка
        btree::ptrNODE temp = node;

        // Если у узла есть левый потомок, то берем его правого потомка
        node = node->right;

        delete temp; // Освобождаем память

        // Рекурсивно удаляем узлы в левом поддереве
        remove_nodes_recursive(node->left, average);

        // Удаляем узлы в правом поддереве
        remove_nodes_recursive(node->right, average);

        return;
    }

    // Рекурсивно обходим левое и правое поддеревья
    remove_nodes_recursive(node->left, average);
    remove_nodes_recursive(node->right, average);
}

// Нерекурсивная функция для удаления узлов меньше среднего
void remove_nodes_iterative(btree::ptrNODE root, double average) {
    if (!root) return;

    std::stack<btree::ptrNODE*> stack;
    stack.push(&root);

    while (!stack.empty()) {
        btree::ptrNODE* current = stack.top();
        stack.pop();

        if (*current) {
            if ((*current)->info < average) {
                btree::ptrNODE temp = *current;
                *current = (*current)->right; // Заменяем на правого потомка
                delete temp; // Освобождаем память
            }
            else {
                stack.push(&(*current)->left);
                stack.push(&(*current)->right);
            }
        }
    }
}

// Функция для удаления узлов меньше среднего значения (внешняя)
void remove_less_than(btree::BTREE tree, double average) {
    remove_nodes_recursive(tree.get_root(), average); // Для рекурсивного подхода
    //remove_nodes_iterative(tree.get_root(), average); // Для нерекурсивного подхода
}

int main() {
    SetConsoleOutputCP(1251);
    btree::BTREE tree("data.txt");

    if (!tree.empty()) {
        double average = calculate_average(tree);
        std::cout << "Среднее арифметическое: " << average << std::endl;

        remove_less_than(tree, average); // Используется рекурсивный подход

        std::cout << "Дерево после удаления элементов меньше среднего:" << std::endl;
        tree.print();
    }
    else {
        std::cout << "Дерево пустое." << std::endl;
    }

    return 0;
}