#ifndef BST_HPP
#define BST_HPP


#include <cassert>
#include <limits>
#include <cstddef>
#include <fstream>
#include <utility>
#include <iostream>

template <class DATATYPE>
class BST;

template <class DATATYPE>
class BSTNode
{
	public:
		DATATYPE getData() const
		{
			return m_data;
		}
		
	private:
		friend class BST<DATATYPE>;
		
		BSTNode(const DATATYPE &data)
			: m_data(data)
			, m_leftChild(nullptr)
			, m_rightChild(nullptr)
		{
		}

		DATATYPE m_data;
		BSTNode<DATATYPE> *m_leftChild;
		BSTNode<DATATYPE> *m_rightChild;
};

template <class DATATYPE>
class BST
{
	public:
		BST() : m_size(0), m_root(nullptr)
		{
		}

		~BST()
		{
			clearAssistant(m_root);
		}

		bool insert(const DATATYPE &d)
		{
			return insertAssistant(m_root, d);
		}

		bool remove(const DATATYPE &d)
		{
			return removeAssistant(m_root, d);
		}

		void clear()
		{
			clearAssistant(m_root);
		}

		void printByLevels() const
		{
			if ( nullptr == m_root ) { return; } 	//empty case
			BSTNode<DATATYPE>** q = new BSTNode<DATATYPE>*[m_size + 1];
			q[0] = m_root;
			std::size_t mark = 1;
			std::size_t begin = 0;
			std::size_t temp = mark;
		
			while(begin != mark) {
				std::cout << q[begin]->m_data << "  ";
				if (q[begin]->m_leftChild) {
					q[temp] = q[begin]->m_leftChild;
					++temp;
				}
				if (q[begin]->m_rightChild) {
					q[temp] = q[begin]->m_rightChild;
					++temp;
				}
				++begin;
				if (begin == mark) {
					std::cout << std::endl;
					mark = temp;
				}
			}
			delete[] q;
		}
		
		bool find(const DATATYPE &d) const
		{
			BSTNode<DATATYPE> * node = m_root;
			while(nullptr != node) {
				if (d == node->m_data) {
					return true;
				}
				else if (d < node->m_data) {
					node = node->m_leftChild;
				}
				else {
					node = node->m_rightChild;
				}
			}
			return false;
		}

		DATATYPE findMax() const
		{
			if (nullptr == m_root) {
				return std::numeric_limits<DATATYPE>::lowest();
			}
			BSTNode<DATATYPE> * node = m_root;
			while (nullptr != node->m_rightChild) {
				node = node->m_rightChild;
			}
			return node->m_data;
		}

		const BSTNode<DATATYPE>* findMax(const BSTNode<DATATYPE>* topNode) const
		{
			if (nullptr == topNode) {
				return nullptr;
			}
			while (nullptr != topNode->m_rightChild) {
				topNode = topNode->m_rightChild;
			}
			return topNode;
		}
		
		DATATYPE findMin() const
		{
			if (nullptr == m_root) {
				return std::numeric_limits<DATATYPE>::max();
			}
			BSTNode<DATATYPE> * node = m_root;
			while (nullptr != node->m_leftChild) {
				node = node->m_leftChild;
			}
			return node->m_data;
		}

		const BSTNode<DATATYPE>* findMin(const BSTNode<DATATYPE>* topNode) const 
		{
			if (nullptr == topNode) {
				return nullptr;
			}
			while (nullptr != topNode->m_leftChild) {
				topNode = topNode->m_leftChild;
			}
			return topNode;
		}

		const BSTNode<DATATYPE>* getRoot() const  
		{
			return m_root;
		}

		std::size_t getSize() const
		{
			return m_size;
		}

	private:
		//'insertAssistant' private member_function called by 'insert' public member_function
		bool insertAssistant (BSTNode<DATATYPE>*& node, const DATATYPE &d)
		{
			if (nullptr == node) {		//empty case
				node = new BSTNode<DATATYPE>(d);
				++m_size;
				return true;
			}
			else {
				if (d < node->m_data) {
					return insertAssistant(node->m_leftChild, d);
				}
				else if (d > node->m_data) {
					return insertAssistant(node->m_rightChild, d);
				}
				else {
					return false;	//a node with value 'd' exists
				}
			}	
		}

		//'removeAssistant' private member_function called by 'remove' public member_function
		bool removeAssistant (BSTNode<DATATYPE>*& node, const DATATYPE& d)
		{
			if (nullptr == node) { return false; }	//empty case or there are no nodes with the value 'd'

			if (d == node->m_data) {
				BSTNode<DATATYPE> * temp = node;
				if (nullptr != node->m_rightChild) {
					node = node->m_rightChild;

					findMin(node)->m_leftChild = temp->m_leftChild;
				}
				else if (nullptr != node->m_leftChild) {
					node = node->m_leftChild;
				}
				else {
					node = nullptr;
				}

				delete temp;
				--m_size;
				return true;
			}
			else if (d < node->m_data) {
				return removeAssistant(node->m_leftChild, d);
			}
			else {
				return removeAssistant(node->m_rightChild, d);
			}
		}

		//'clearAssistant' private member_function called by 'clear' public member_function
		void clearAssistant(BSTNode<DATATYPE>*& node)
		{
			if (nullptr == node) {
				return;
			}
			if (node->m_leftChild) { 
				clearAssistant(node->m_leftChild);
			}	
			if (node->m_rightChild) { 
				clearAssistant(node->m_rightChild);
			}	
			delete node;
			node = nullptr;
			--m_size;
		}
		
		// non const version of findMin(BSTNode) is intended for internal use
		// (to prevent integrity changes)
		BSTNode<DATATYPE>* findMin(BSTNode<DATATYPE>* topNode) 
		{
			if (nullptr == topNode) {
				return nullptr;
			}
			while (nullptr != topNode->m_leftChild) {
				topNode = topNode->m_leftChild;
			}
			return topNode;
		}
		
		//private members
		std::size_t m_size;
		BSTNode<DATATYPE> *m_root;
};


template <typename DATATYPE>
BST<DATATYPE> BSTGenerator(const char *sourceFile)
{
	std::ifstream fin(sourceFile, std::ios::in);
	assert(fin.is_open() && "File openning failed!");
	DATATYPE d;
	char c;
	BST<DATATYPE> bst;
	while (fin >> d) {
		bst.insert(d);
		if ( !(fin >> c) ) { break; }
		assert(',' == c && "Inaccurate file content!");
	}
	fin.close();
	return bst;
}


#endif
