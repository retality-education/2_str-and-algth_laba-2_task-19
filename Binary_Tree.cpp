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

// ����� ��� ���������� ����� � ���������� ����� (�����������)
void btree::BTREE::calculate_sum_and_count_recursive(ptrNODE node, int& sum, int& count) {
    if (node) {
        sum += node->info;
        count++;
        calculate_sum_and_count_recursive(node->left, sum, count);
        calculate_sum_and_count_recursive(node->right, sum, count);
    }
}

// ����� ��� ���������� ����� � ���������� ����� (�������������)
void btree::BTREE::calculate_sum_and_count_iterative(int& sum, int& count) {
    std::stack<ptrNODE> stack;
    ptrNODE current = root;

    while (current || !stack.empty()) {
        // ��������� �� ����� �����
        while (current) {
            stack.push(current);
            current = current->left;
        }

        // ������������ ������� ����
        current = stack.top();
        stack.pop();

        sum += current->info;
        count++;

        // ��������� � ������� ���������
        current = current->right;
    }
}

// ����� ��� �������� ����� ������ ��������� �������� (�����������)
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

// ����� ��� �������� ����� ������ ��������� �������� (�������������)
btree::ptrNODE btree::BTREE::remove_less_than_iterative(ptrNODE node, double threshold) {
    if (!node) return nullptr;

    std::stack<ptrNODE*> stack; // ���� ���������� �� ����
    std::vector<ptrNODE> nodesToDelete; // ������ ��� �������� ����� �� ��������
    stack.push(&node); // �������� � �����

    while (!stack.empty()) {
        ptrNODE* currentPtr = stack.top();
        stack.pop();

        if (*currentPtr) {
            if ((*currentPtr)->info < threshold) {
                nodesToDelete.push_back(*currentPtr); // ���������� ���� �� ��������
                *currentPtr = nullptr; // ������� ���� �� ������
            }
            else {
                // ��������� ������ � ����� �������� ���� � ����
                stack.push(&(*currentPtr)->right);
                stack.push(&(*currentPtr)->left);
            }
        }
    }

    // ������ ����� ������������� ���������� ����
    for (auto node : nodesToDelete) {
        delete node; // ������� ����������� ����
    }

    return node; // ���������� ����������� ������ ������
}

// ����� ��� �������� ��������� ������ �������� ���������������
void btree::BTREE::remove_below_average() {
    int sum = 0;
    int count = 0;

    // ��������� ����� � ���������� ����� ����������
    calculate_sum_and_count_recursive(root, sum, count);

    if (count == 0) return; // ���� ������ ������

    double average = static_cast<double>(sum) / count; // ��������� ������� ��������������

    // ������� ���� ������ �������� ��������������� ���������� ��� ������������
    root = remove_less_than_recursive(root, average); // ����������� �������
    // root = remove_less_than_iterative(root, average); // ������������� �������
}