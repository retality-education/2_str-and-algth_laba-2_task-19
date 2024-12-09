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
//ptrNODE remove_less_than_iterative(ptrNODE node, double threshold) {
//    if (!node) return nullptr;
//
//    std::stack<ptrNODE> stack; // Стек указателей на узлы
//    std::vector<ptrNODE> nodesToDelete; // Вектор для хранения узлов на удаление
//    stack.push(node); // Начинаем с корня
//
//    while (!stack.empty()) {
//        ptrNODE currentPtr = stack.top();
//        stack.pop();
//
//        if (currentPtr) {
//            if (currentPtr->info < threshold) {
//                nodesToDelete.push_back(currentPtr); // Запоминаем узел на удаление
//                currentPtr = nullptr; // Удаляем узел из дерева
//            }
//            else {
//                // Добавляем правый и левый дочерние узлы в стек
//                stack.push(currentPtr->right);
//                stack.push(currentPtr->left);
//            }
//        }
//    }
//    for (auto x : nodesToDelete)
//        delete x;
//    /*while (!nodesToDelete.empty()) {
//        delete nodesToDelete.top();
//    }*/
//
//    return node; // Возвращаем обновленный корень дерева
//}
#include <queue>
//void remove_less_than_iterative(ptrNODE& root, int threshold) {
//    std::stack<ptrNODE> s;
//    std::queue<ptrNODE> q;
//    btree::BTREE btree_temp;
//    ptrNODE ptr = root;
//    s.push(root);
//    while (!s.empty()) {
//        ptrNODE temp = s.top();
//        s.pop();
//        q.push(temp);
//        if (temp->left)
//            s.push(temp->left);
//        if (temp->right)
//            s.push(temp->right);
//    }
//    root = nullptr;
//    while (!q.empty()) {
//        ptrNODE temp = q.front();
//        q.pop();
//        if (temp->info < threshold)
//            delete temp;
//        else {
//            if (!root)
//                root = temp;
//            temp->
//        }
//    }
//    root = btree_temp.get_root();
//}
//void remove_less_than_iterative(ptrNODE root, int avg)
//{
//    //Обход в глубину
//    std::stack<ptrNODE> s;
//    int result{};
//    ptrNODE t = root;
//    while (t)
//    {
//        
//        if (t->left)
//        {
//            if (t->right)
//                s.push(t->right);
//            t = t->left;
//        }
//        else if (t->right)
//            t = t->right;
//        else if (s.empty())
//            t = nullptr;
//        else if (t->left == nullptr && t->right == nullptr && t->info < avg)
//            delete t;
//        else
//        {
//            t = s.top();
//            s.pop();
//        }
//    }
//}
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
                root = (root->left != nullptr) ? root->left : root->right;
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
ptrNODE remove_less_than_recursive(ptrNODE node, double threshold) {
    if (!node) return nullptr;

    node->left = remove_less_than_recursive(node->left, threshold);
    node->right = remove_less_than_recursive(node->right, threshold);

    if (node->info < threshold) {
        ptrNODE temp = node;
        if (node->right) {
            node = node->right;
            ptrNODE leftMost = node;
            while (leftMost->left) {
                leftMost = leftMost->left;
            }
            leftMost->left = temp->left;
        }
        else {
            node = node->left;
        }
        delete temp;
    }
    return node;
}
ptrNODE remove_below_average(ptrNODE& root) {
    int sum = 0;
    int count = 0;
    
    //calculate_sum_and_count_recursive(root, sum, count);
    calculate_sum_and_count_iterative(root, sum, count);

    if (count == 0) return nullptr; // Если дерево пустое

    double avg_sum = static_cast<double>(sum) / count; // Вычисляем среднее арифметическое

    //root = remove_less_than_recursive(root, avg_sum); // Рекурсивный вариант
    remove_less_than_iterative(root, avg_sum); // Нерекурсивный вариант
    return root;
}
int main() {
    btree::BTREE tree("test.txt"); // Предполагается, что данные находятся в файле data.txt

    std::cout << "Дерево до удаления:" << std::endl;
    tree.print();
    ptrNODE root = (tree.get_root());
    tree.set_root(remove_below_average(root)); // Удаляем элементы ниже среднего арифметического

    std::cout << "Дерево после удаления:" << std::endl;
    tree.print();

    return 0;
}
