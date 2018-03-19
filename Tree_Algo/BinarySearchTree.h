#pragma once

#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include <iostream>

using namespace std;

template <class T>
class BinarySearchTree {

private:

	// Описание структуры узла со ссылками на детей
	struct Node {
		T  key_;              // значение ключа, содержащееся в узле
		Node *left_;     // указатель на левое поддерево
		Node *right_;   // указатель на правое поддерево
		Node *p_;        // указатель на на родителя !!! не используется
						 // Конструктор узла
		Node(const T& key, Node *left = NULL, Node *right = NULL, Node *p = NULL) :
			key_(key), left_(left), right_(right), p_(p)
		{  }
	};

	// Дерево реализовано в виде указателя на корневой узел.
	Node *root_;

public:

	// Конструктор "по умолчанию" создает пустое дерево
	BinarySearchTree() : root_(NULL) {}

	// Деструктор освобождает память, занятую узлами дерева
	~BinarySearchTree() { deleteSubtree(root_); }

	// Печать строкового изображения дерева в выходной поток out
	void print(ostream & out) const { printNode(out, root_); out << endl; }

	// Функция поиска по ключу в бинарном дереве поиска
	bool iterativeSearch(const T & key)  const {
		return (iterativeSearchNode(key) != NULL);
	}

	void insert(T& key) { insert(new Node(key)); }

	// Удаление элемента из дерева, не нарушающее порядка элементов
	void deleteKey(const T & key)
	{
		Node * temp = iterativeSearchNode(key);

		if (temp == root_) {
			cout << "Error, you can't delete root\n";
			return;
		}

		if (temp == NULL)
		{
			cout << "We don't have this key " << key << " in tree" << '\n';
			return;
		}

		Node *parent = temp->p_;
		//Node is leaf
		if (temp->left_ == NULL && temp->right_ == NULL)
		{
			if (parent->right_ == temp)
				parent->right_ = NULL;
			else if (parent->left_ == temp)
				parent->left_ = NULL;
		}
		//one son
		else if (temp->left_ == NULL)
		{
			if (parent->left_ == temp)
				parent->left_ = temp->right_;
			else
				parent->right_ = temp->right_;

			(temp->right_)->p_ = parent;
		}
		else if (temp->right_ == NULL)
		{
			if (parent->left_ == temp)
				parent->left_ = temp->left_;
			else
				parent->right_ = temp->left_;

			(temp->left_)->p_ = parent;
		}
		//two sons
		else
		{
			(temp->right_)->p_ = temp->p_;

			Node* minSubtrElement = minSubtreeElement(temp->right_);
			minSubtrElement->left_ = temp->left_;
			(temp->left_)->p_ = minSubtrElement;

			if (temp->key_ > (temp->p_)->key_)
				(temp->p_)->right_ = temp->right_;
			else
				(temp->p_)->left_ = temp->right_;
		}

		delete temp;

		return;
	}

	// Определение количества узлов дерева
	int count() const {
		return countSubTree(this->root_);
	}
	// Определение высоты дерева
	int height() const {
		return heightSubTree(this->root_);
	}


private:
	// Вставка нового элемента в дерево, не нарушающая порядка
	// элементов. Вставка производится в лист дерева
	void insert(Node* key) {

		if (root_ == nullptr) {
			root_ = key;
			return;
		}

		Node *temp;
		temp = root_;
		while (temp != NULL)
		{
			if (temp->key_ < key->key_) {
				if (temp->right_ != NULL)
					temp = temp->right_;
				else {
					key->p_ = temp;
					temp->right_ = key;
					return;
				}
			}

			else {
				if (temp->left_ != NULL)
					temp = temp->left_;
				else {
					key->p_ = temp;
					temp->left_ = key;
					return;
				}
			}
		}
	}

	// Функция поиска адреса узла по ключу в бинарном дереве поиска
	Node * iterativeSearchNode(const T & key) const {
		Node* temp = root_;

		while (temp != NULL && temp->key_ != key)
			if (temp->key_ > key)
				temp = temp->left_;
			else
				temp = temp->right_;

		return temp;

	}

	//
	// Рекурсивные функции, представляющие  
	// рекурсивные тела основных интерфейсных методов
	//

	// Рекурсивная функция для освобождения памяти
	void deleteSubtree(Node *node) {
		if (node->left_) 
			deleteSubtree(node->left_);

		if (node->right_) 
			deleteSubtree(node->right_);

		delete node;
	}

	// Рекурсивная функция определения количества узлов дерева
	int countSubTree(Node *node) const {
		if (node == NULL)
			return 0;
		return (1 + countSubTree(node->left_) +
			countSubTree(node->right_));
	}

	// Рекурсивная функция определения высоты дерева
	int heightSubTree(Node *node) const {
		int leftHeight, rightHeight;
		int sumHeight = 0;

		if (node != NULL)
		{
			leftHeight = heightSubTree(node->left_);
			rightHeight = heightSubTree(node->right_);

			if (leftHeight > rightHeight)
				sumHeight = leftHeight + 1;
			else 
				sumHeight = rightHeight + 1;
		}

		return sumHeight;
	}

	// Рекурсивная функция для вывода изображения дерева в выходной поток
	void printNode(ostream & out, Node *root) const {
		// Изображение дерева заключается в круглые скобки.
		out << '(';
		if (root) {
			// Для узлов дерева должна быть определена (или переопределена)
			// операция вывода в выходной поток <<
			out << root->key_;
			printNode(out, root->left_);
			printNode(out, root->right_);
		}
		out << ')';
	}

	// Рекурсивная функция для организации обхода узлов дерева.
	void inorderWalk(Node *node) const {
		cout << '(';
		while (node != NULL)
		{
			inorderWalk(node->left_);
			cout << node->key_;
			inorderWalk(node->right_);
		}
		cout << ')';

		return;
	}

	void preorderWalk(Node *node) const {
		cout << '(';
		while (node != NULL)
		{
			inorderWalk(node->right_);
			cout << node->key_;
			inorderWalk(node->left_);
		}
		cout << ')';

		return;
	}

	Node* minSubtreeElement(Node *node)
	{
		if (node == NULL) {
			cout << "Error";
			return NULL;
		}

		Node* temp = node;

		while (temp->left_ != NULL)
			temp = temp->left_;

		return temp;
	}
}; // конец шаблона класса TreeBinarySearchTree


#endif
