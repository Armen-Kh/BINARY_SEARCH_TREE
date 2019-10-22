#include "bst_utest.hpp"

#include <iostream>

int main()
{
	bool ib = BST_UTest<int>("source_int.txt");
	std::cout << (ib ? "************ Test for integer BSTree SUCCEEDED!\n\n"
		      	 : "************ Test for integer BSTree FAILED!\n\n") << std::endl;

	bool db = BST_UTest<double>("source_double.txt");
	std::cout << (db ? "************ Test for double BSTree SUCCEEDED!\n\n"
		      	 : "************ Test for double BSTree FAILED!\n\n") << std::endl;

	bool cb = BST_UTest<char>("source_char.txt");
	std::cout << (cb ? "************ Test for char BSTree SUCCEEDED!\n\n"
		      	 : "************ Test for char BSTree FAILED!\n\n") << std::endl;
	return 0;
}
