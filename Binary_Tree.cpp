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

