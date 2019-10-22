## BINARY SEARCH TREE

### Binary search tree implementation ( bst.hpp );
### Testing unit ( bst_utest.hpp );
### The main function, which calls testing unit for different source files (main.cpp).

### Source files for generating BST with integer, double and char data types ( source_int.txt, source_double.txt, source_char.txt ).

### makefile
      command make:
		Run make file for generate dependency(*.dep) and objects(*.o) units, and as a final result execution 
		file(main.out), which represent tests results.
      command make debug:
		Make compilation and linking with "-g" flag.
      command make profile:
		Make compilation and linking with "-pg" flag, which give as an oportunity to see proper time analysis
		for each project unit.
      command make gcov:
		Make compilation and linking with "--coverage" flag, which give as an oportunity to see covearge analysis
		for each source unit. LCOV options are also demonstrated.
      command make memcheck:
		Running with Valgrind (a memory error detector).
		


