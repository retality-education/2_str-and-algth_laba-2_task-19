#include "Binary_Tree.h"

void add(btree::ptrNODE& t, int elem)
{
	if (!t)
		t = new btree::NODE(elem);
	else
		if (elem < t->info)
			add(t->left, elem);
		else
			if (elem > t->info)
				add(t->right, elem);
}

btree::BTREE::BTREE(const char* file_name)
{
	std::ifstream file(file_name);
	TInfo x;
	root = nullptr;
	while (file >> x)
		add(root, x);
	file.close();
}

bool btree::BTREE::empty()
{
	return !root;
}

void clearr(btree::ptrNODE& t)
{
	if (t)
	{
		clearr(t->left);
		clearr(t->right);
		delete t;
		t = nullptr;
	}
}

btree::BTREE::~BTREE()
{
	clearr(root);
}

void printt(btree::ptrNODE t, int level, std::ostream& stream)
{
	if (t)
	{
		printt(t->right, level + 1, stream);
		for (int i = 1; i <= level; i++)
			stream << "  ";
		std::cout.width(2);
		stream << t->info << std::endl;
		printt(t->left, level + 1, stream);
	}
}
void btree::BTREE::print(std::ostream& stream)
{
	printt(root, 0, stream);
}

void btree::BTREE::clear(ptrNODE& ptr)
{
	clearr(ptr);
}
#include <stack>

// Метод для вычисления суммы и количества узлов (рекурсивный)
void btree::BTREE::calculate_sum_and_count_recursive(ptrNODE node, int& sum, int& count) {
    if (node) {
        sum += node->info;
        count++;
        calculate_sum_and_count_recursive(node->left, sum, count);
        calculate_sum_and_count_recursive(node->right, sum, count);
    }
}

// Метод для вычисления суммы и количества узлов (нерекурсивный)
void btree::BTREE::calculate_sum_and_count_iterative(int& sum, int& count) {
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

// Метод для удаления узлов меньше заданного значения (рекурсивный)
btree::ptrNODE btree::BTREE::remove_less_than_recursive(ptrNODE node, double threshold) {
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

// Метод для удаления узлов меньше заданного значения (нерекурсивный)
btree::ptrNODE btree::BTREE::remove_less_than_iterative(ptrNODE node, double threshold) {
    if (!node) return nullptr;

    std::stack<ptrNODE*> stack; // Стек указателей на узлы
    std::vector<ptrNODE> nodesToDelete; // Вектор для хранения узлов на удаление
    stack.push(&node); // Начинаем с корня

    while (!stack.empty()) {
        ptrNODE* currentPtr = stack.top();
        stack.pop();

        if (*currentPtr) {
            if ((*currentPtr)->info < threshold) {
                nodesToDelete.push_back(*currentPtr); // Запоминаем узел на удаление
                *currentPtr = nullptr; // Удаляем узел из дерева
            }
            else {
                // Добавляем правый и левый дочерние узлы в стек
                stack.push(&(*currentPtr)->right);
                stack.push(&(*currentPtr)->left);
            }
        }
    }

    // Теперь нужно пересоединить оставшиеся узлы
    for (auto node : nodesToDelete) {
        delete node; // Удаляем запомненные узлы
    }

    return node; // Возвращаем обновленный корень дерева
}

// Метод для удаления элементов меньше среднего арифметического
void btree::BTREE::remove_below_average() {
    int sum = 0;
    int count = 0;

    // Вычисляем сумму и количество узлов рекурсивно
    calculate_sum_and_count_recursive(root, sum, count);

    if (count == 0) return; // Если дерево пустое

    double average = static_cast<double>(sum) / count; // Вычисляем среднее арифметическое

    // Удаляем узлы меньше среднего арифметического рекурсивно или нерекурсивно
    root = remove_less_than_recursive(root, average); // Рекурсивный вариант
    // root = remove_less_than_iterative(root, average); // Нерекурсивный вариант
}