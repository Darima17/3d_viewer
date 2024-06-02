CC = gcc
CFLAGS = -std=c++17 -Wall -pedantic -Wextra -Werror
TEST_FLAGS = -lgtest -lgtest_main -lm -lstdc++ -pthread
SOURCE = models/edges.cc models/faces.cc models/figure.cc models/point.cc models/points.cc
TESTS = tests/tests.cc

.PHONY: all clean fclean test install uninstall dvi dist gcov_report style_change style_check

all: clean install\

install:
	mkdir build
	cd build && qmake ../viewer/3DViewer.pro && make
	open build/3DViewer.app

open:
	open build/3DViewer.app

uninstall:
	rm -rf build

dvi:
	doxygen ./doxy/Doxyfile
	open ./docs/html/index.html

dist:
	@mkdir -p dist
	@cp -R build/$(3DV) dist
	@cp ../README_RUS.md dist && cp ../README.md dist
	@cd dist && tar cvzf 3DViewer.tgz *
	@cd dist && rm -rf $(3DV) README.md README_RUS.md

test :
	$(CC) $(CFLAGS) $(SOURCE) $(TESTS) $(TEST_FLAGS) -fprofile-arcs -ftest-coverage -o test.out
	./test.out

gcov_report: test
	mkdir report
	gcovr -r . --html-details -o ./report/coverage_details.html --filter "models/.*" --filter "tests/.*"
	open ./report/coverage_details.html


style_check:
	@cp ../materials/linters/.clang-format .
	@clang-format -n */*.cc */*.h tests/*.cc
	@rm ./.clang-format

style_change:
	@cp ../materials/linters/.clang-format .
	@clang-format -i */*.cc */*.h tests/*.cc 
	@rm ./.clang-format

clean:
	@rm -rf test/testing *.gcno *.gcov *.o *.gcda *.info gcov_report
	@rm -rf .qmake.stash *.user moc_*
	@rm -rf test/*.gcno test/*.o test/*gcda
	@rm -rf test.out test.gcda test.gcno
	@rm -rf out
	@rm -rf *.out
	@rm -rf report
	@rm -rf models/*.gch
	@rm -rf docs
	@rm -rf test_figure.txt


fclean: clean
	@rm -rf dist ~/Desktop/$(3DV) build* test_html