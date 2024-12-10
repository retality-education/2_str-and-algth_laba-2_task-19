#include <iostream>
#include "Binary_Tree.h"
#include <stack>
using btree::ptrNODE;

void calculate_sum_and_count_iterative(ptrNODE root, int& sum, int& count) {
    std::stack<ptrNODE> stack;
    ptrNODE current = root;

    while (current || !stack.empty()) {
        // Двигаемся по левым узлам
        while (current) {
            stack.push(current);
            current = current->left;
        }

        // Обрабатываем текущий узел
        current = stack.top();
        stack.pop();

        sum += current->info;
        count++;

        // Переходим к правому поддереву
        current = current->right;
    }
}

#include <vector>

#include <queue>

void remove_less_than_iterative(ptrNODE& root, int threshold) {
    if (root == nullptr) return;

    std::stack<ptrNODE> stack1, stack2;
    stack1.push(root);

    // Сначала помещаем все узлы в первый стек
    while (!stack1.empty()) {
        ptrNODE current = stack1.top();
        stack1.pop();
        stack2.push(current);

        // Добавляем левых и правых потомков в стек
        if (current->left != nullptr) {
            stack1.push(current->left);
        }
        if (current->right != nullptr) {
            stack1.push(current->right);
        }
    }

    // Теперь обрабатываем узлы из второго стека
    while (!stack2.empty()) {
        ptrNODE current = stack2.top();
        stack2.pop();

        // Если значение меньше порога, удаляем узел
        if (current->info < threshold) {
            // Удаляем текущий узел
            if (current == root) {
                // Если корень нужно удалить
                ptrNODE temp = root;
                if (root->right)
                    root = root->right;
                else
                    root = nullptr;
                delete temp; // Освобождаем память
                current = root; // Обновляем текущий узел
            }
            else {
                // Найдем родителя текущего узла
                ptrNODE parent = root;
                while (parent != nullptr) {
                    if (current->info < parent->info) {
                        if (parent->left == current) {
                            parent->left = (current->left != nullptr) ? current->left : current->right;
                            break;
                        }
                        parent = parent->left;
                    }
                    else {
                        if (parent->right == current) {
                            parent->right = (current->left != nullptr) ? current->left : current->right;
                            break;
                        }
                        parent = parent->right;
                    }
                }
                delete current; // Освобождаем память
            }
        }
        
    }
}
void calculate_sum_and_count_recursive(ptrNODE node, int& sum, int& count) {
    if (node) {
        sum += node->info;
        count++;
        calculate_sum_and_count_recursive(node->left, sum, count);
        calculate_sum_and_count_recursive(node->right, sum, count);
    }
}
void remove_less_than_recursive(btree::BTREE& btree, ptrNODE& node, double avg) {
    if (!node) return;

    if (node->info < avg)
    {
        ptrNODE temp = node;
        node = node->right;
        btree.clear(temp->left);
        temp->left = nullptr;
        temp->right = nullptr;
        delete temp;
        remove_less_than_recursive(btree, node, avg);
    }
    else
        remove_less_than_recursive(btree, node->left, avg);
}
void remove_below_average(btree::BTREE& tree, ptrNODE& root) {
    int sum = 0;
    int count = 0;
    
    calculate_sum_and_count_recursive(root, sum, count);
    //calculate_sum_and_count_iterative(root, sum, count);

    if (count == 0) return; // Если дерево пустое

    double avg_sum = static_cast<double>(sum) / count; // Вычисляем среднее арифметическое

    remove_less_than_recursive(tree, root, avg_sum); // Рекурсивный вариант
    //remove_less_than_iterative(root, avg_sum); // Нерекурсивный вариант
}
int main() {
    btree::BTREE tree("test.txt"); // Предполагается, что данные находятся в файле data.txt

    std::cout << "Дерево до удаления:" << std::endl;
    tree.print();
    ptrNODE root = (tree.get_root());
    remove_below_average(tree, root); // Удаляем элементы ниже среднего арифметического

    std::cout << "Дерево после удаления:" << std::endl;
    tree.print();

    return 0;
}
