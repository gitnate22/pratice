cube2.o : cube2.hpp cube2.cpp
	clang++ -c cube2.cpp cube2.hpp

rub2 : rubricks2x2.cpp cube2.o
	clang++ rubricks2x2.cpp cube2.o -o rub2
