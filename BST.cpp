// BST.cpp: Binary Search Tree

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

//����� ����������� ��������� ������� ������
class node
{
public:

	int key;

	node* parent;

	node* LC;//����� �������

	node* RC;//������ �������

	node()
	{
		parent = NULL;
		 LC = NULL;
		 RC = NULL;
	}

	~node()
	{
		if (this != NULL)
		{
			
			delete LC;
			delete RC;
		}
	}
};

class BST
{
private:	

	node* root;

/*
PushInBST - �������� ������� ���� �� ��������� key ��� ������� parent.

���� ��� �� ���������� (�.�. � parent  ��� ���� �������),�� ������� ���������� ��� ��� �������.

������ ������ ���������� � ������� �������� ��� ������� ������,��� ����� �������� ������������ ����� �������,

�� ����� � ��� ����� ���-�� �� ��������� �� ���� :)
	
*/
	void PushInBST(int key, node* parent)
	{
		if (key < parent->key)
		{
			if (parent->LC == NULL)
			{
				node* n = new node;

				n->key = key;

				n->LC = NULL;

				n->RC = NULL;

				parent->LC = n;

				n->parent = parent;

				num++;
			}
			else
				PushInBST(key, parent->LC);
		}
		else
		{
			if (parent->RC == NULL)
			{
				node* n = new node;

				n->key = key;

				n->LC = NULL;

				n->RC = NULL;

				parent->RC = n;

				n->parent = parent;

				num++;
			}
			else
				PushInBST(key, parent->RC);

		}
	
	}

	int num;//���������� ��������� � ������

//	GetAllNodes - ������ ������� "�����������" ��� ����� �� ������ � ���������� �� � ������ (������������ � ��������� �������� ���� ��������).
	int* GetAllNodes()
	{
		int* a = new int[this->num];

		BST* temp = new BST;

		*temp = *this;

		node* edit = temp->root;

		node* parent = NULL;

		int j = this->num;

		int k = 0;

		while (j > 0)
		{
			if (edit->LC != NULL)
			{
				parent = edit;
				edit = edit->LC;
			}
			else
			{
				if (edit->RC != NULL)
				{
					parent = edit;
					edit = edit->RC;
				}
				else
				{
					a[k] = edit->key;

					k++; j--;

					if (edit == parent->LC)
						parent->LC = NULL;
					else
						parent->RC = NULL;

					delete edit;

					edit = parent;

					if (edit->parent != NULL)
						parent = edit->parent;
					else
					{
						a[k] = edit->key;
						j--; k++;
						continue;
					}

				}
				
			}
		}
		delete temp;

		return a;
	}
		
		

	

//������� ������ �� ����� ������ ������ ������
	void WriteOneString(std::vector<node*> array, int tab)
	{
		std::string tabul = GetTabulation(tab);

		std::cout << tabul;

		std::vector<node*> NextString;

		int NeedNext = 0;

		int size_arr = array.size();

		for (int i = 0; i < size_arr - 1; i += 2)
		{
			if (array[i] != NULL)
				std::cout << array[i]->key << "\t\t";
			else std::cout << "NULL" << "\t\t";

			if (array[i + 1] != NULL)
				std::cout << array[i + 1]->key << "|";
			else std::cout << "NULL" << "|";

			if ( array[i] != NULL )
				if ( array[i]->LC != NULL || array[i]->RC != NULL  )
					NeedNext = 1;
			if ( array[i+1] != NULL ) 
				if (array[i + 1]->LC != NULL || array[i + 1]->RC != NULL)
					NeedNext = 1;


		}
		std::cout << std::endl;
		tab--;
		if (NeedNext != 0)
		{
			for (int i = 0; i < size_arr; i++)
			{
				if (array[i] != NULL)
				{
					NextString.push_back(array[i]->LC);

					NextString.push_back(array[i]->RC);
				}
				else
				{
					NextString.push_back(NULL);

					NextString.push_back(NULL);
				}
				
			}
			WriteOneString(NextString, tab);
		}
	}

	std::string GetTabulation(int tab)
	{
		std::string result = "";
		for (int i = 0; i < tab; i++)
			result = result + "\t";
		return result;
	}

public:
	
	BST()
	{
		root = NULL;

		num = 0;
	}

	BST(int value)
	{
		root = new node;

		root->key = value;

		root->LC = NULL;

		root->RC = NULL;

		root->parent = NULL;

		num = 1;
		
	}
	
//����������� �����������
	BST(const BST& s)
	{
		
		if (s.root != NULL)
		{
			root = new node;

			root->key = s.root->key;

			root->parent = NULL;

			if (s.root->LC != NULL)
				this->root->LC = CopyNodes(s.root->LC, root);
			else root->LC = NULL;

			if (s.root->RC != NULL)
				root->RC = CopyNodes(s.root->RC, root);
			else root->RC = NULL;
		}
		else root = NULL;
		this->num = s.num;
		
	}

/*

CopyNodes ������� ����� ����� s ��� ������� ����� parent1. ���� � s ���� �������,

�� ��� ����� ���������� � ����� ��� ������� (������� �������� ����������)

*/
	node* CopyNodes(node* s, node* parent1)
	{
		node* a = new node;

		a->key = s->key;

		a->parent = parent1;

		if (s->LC != NULL)
			a->LC = CopyNodes(s->LC, a);
		else a->LC = NULL;

		if (s->RC != NULL)
			a->RC = CopyNodes(s->RC, a);
		else a->RC = NULL;

		return a;

	}

//������� �������� � ������
	void push(int key)
	{
		if (root != NULL)
		{
			PushInBST(key, root);
			
		}
		else
		{
			root = new node;
			root->key = key;
			root->LC = NULL;
			root->RC = NULL;
			root->parent = NULL;
			num++;
		}

	}

	BST operator = (BST s)
	{
		if (s.root != NULL)
		{
			if (this->root != NULL)
				delete this->root;
			
			this->root = new node;
	
			this->root->key = s.root->key;
	
			if (s.root->LC != NULL)
				this->root->LC = CopyNodes(s.root->LC, this->root);
			else this->root->LC = NULL;

			if (s.root->RC != NULL)
				this->root->RC = CopyNodes(s.root->RC, this->root);
			else this->root->RC = NULL;
		}
		else this->root = NULL;

		this->num = s.num;

		return (*this);
	}

	BST operator + (BST s)
	{

		BST* edit;

		edit = new BST;

		*edit = *this;

		int* a = edit->GetAllNodes();

		num = edit->num;

		*edit = s;

		for (int j = 0; j < num; j++)
			edit->push(a[j]);

		return *edit;
	}

	

//����������� ������� ��� ������ ������ �� �����(������ ���������, ����� ������, ����� ����� )
	void WriteTree()
	{   
		int j = num - 1;

		std::string tab = GetTabulation(j);

		std::cout << tab << root->key << std::endl;

		std::vector<node*> NextString;

		if ((root->LC != NULL) || (root->RC != NULL))
		{
			NextString.push_back(root->LC);

			NextString.push_back(root->RC);

		}
		j--;
		WriteOneString(NextString, j);

	}

	~BST()
	{
		
		delete root;
	}

};


// ��������� ����������� ��� ���������
int main()
{
	BST* test = new BST(4);

	test->push(1);

	test->push(10);

	test->push(12);

	BST* test1 = new BST(9);

	test1->push(3);

	/*
	int i = 1;

	std::cout << "TEST" << std::endl;

	while (i > 0)
	{
		std::cin >> i;

		test->push(i);
	}

	i = 1;

	test->WriteTree();

	std::cout << "TEST1" << std::endl;

	while (i > 0)
	{
		std::cin >> i;

		test1->push(i);
	}
	*/

	BST* t = new BST;

	*t = *test + *test1;

	BST* r = new BST;

	*r = *t;

	t->WriteTree();
	
	delete test;

	delete test1;

	delete t;

	delete r;

	system("pause");

	return 0;
}

