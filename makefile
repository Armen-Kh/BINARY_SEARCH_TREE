TARGET = main.out
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,%.o, $(SOURCES))
DEPENDS = $(patsubst %.cpp,%.dep, $(SOURCES)) 
FLAGS ?= -O3

$(TARGET) : $(OBJECTS)
	g++ $(FLAGS) $^ -o $@

%.o : %.cpp
	g++ -c $(FLAGS) $< -I./ -o $@

%.dep : %.cpp
	g++ -MM $< -MT "$@ $(basename $@).o" -I./ -o $@
	@#the same as above  g++ -MM $< _MT "@ $(subst .dep,.o,$@)" -I./ -o $@

.PHONY : run
run : 
	./main.out

.PHONY : clean
clean :
	rm -rf *.dep *.o main.out *.gcno *.gcda GcovResults Report gmon.out profile_data.txt coverage.info

.PHONY : debug 
debug : clean
	$(MAKE) FLAGS="-g"
	@echo "Running GDB"
	gdb ./$(TARGET)

.PHONY : profile
profile : clean
	$(MAKE) FLAGS="-pg"
	./$(TARGET)
	@echo "Running GPROF"
	gprof -q -b $(TARGET) gmon.out profile_data.txt

.PHONY : gcov
gcov : clean
	$(MAKE) FLAGS="--coverage"
	./$(TARGET)
	@echo "Running GCOV"
	#@mkdir GcovResults
	@gcov -r bst 
	@gcov -r bst_utest 
	#@mv *gcov GcovResults
	@echo "Running LCOV"
	@lcov -t "$(TARGET)" -o coverage.info -c -d .
	@genhtml -o Report coverage.info
	@xdg-open Report/index.html

.PHONY : memcheck
memcheck : clean
	$(MAKE) FLAGS="-g -O0"
	valgrind --leak-check=full ./$(TARGET)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPENDS)
endif
	
