#ifndef BST_UTEST_HPP
#define BST_UTEST_HPP


#include "bst.hpp"

#include <cstddef>
#include <iostream>
#include <typeinfo>

template <typename DATATYPE>
bool BST_UTest(const char* sourceFile)
{
	std::cout << "The test for BST< " << typeid(DATATYPE).name() << " > is started!" 
		  << "\n***************************************************" << std::endl;

	std::cout << "Generating Binary Search Tree from " << sourceFile << std::endl;
	BST<DATATYPE> bst = BSTGenerator<DATATYPE>(sourceFile);
	std::size_t s = bst.getSize();
	std::cout << "\nPrinting by levels of generated BST." << std::endl;
	bst.printByLevels();

	DATATYPE max = bst.findMax();
	DATATYPE min = bst.findMin();
	std::cout << "\nMaximum value: " << max << std::endl;
	std::cout << "Minimum value: " << min << std::endl;
	bool b0 = ( *(bst.findMax(bst.getRoot())) ).getData() == max;
	bool b1 = ( *(bst.findMin(bst.getRoot())) ).getData() == min;
	
	bst.insert( (DATATYPE)65 );
	bool b2 = (bst.find( (DATATYPE)65 ) == true);
	bool b3 = (bst.insert( (DATATYPE)65 ) == false);
	bool b4 = (bst.getSize() == s + 1);
	
	bst.remove( (DATATYPE)7.2 );
	bst.remove( (DATATYPE)20.7 );
	bst.find( (DATATYPE)20.7 );
	bst.remove( (DATATYPE)116 );
	bst.remove( (DATATYPE)101 );
	bool b5 = (bst.getSize() == s - 1);
	
	bst.clear();
	bool b6 = ( 0 == bst.getSize() );
	bool b7 = ( nullptr == bst.getRoot() );

	return b0 && b1 && b2 && b3 && b4 && b5 && b6 && b7;
}


#endif
