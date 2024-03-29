// Tree_Algo.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "BinarySearchTree.h"

using namespace std;

int main()
{
	{
		cout << "Create an empty tree, push values and put it out and delete some elements\n";

		BinarySearchTree<int> tree;

		for (int i = 0; i < 10; i++)
			tree.insert(i);

		tree.print(cout);

		for (int i = -1; i > -10; i--)
			tree.insert(i);

		tree.print(cout);

		tree.deleteKey(-2);

		tree.deleteKey(0);

		tree.print(cout);

		cout << "In this tree " << tree.count() << " counts\n";
		cout << "In this tree " << tree.height() << " heigth\n";
	}

    return 0;
}

