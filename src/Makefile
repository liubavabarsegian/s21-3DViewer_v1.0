NAME = 3d-viewer
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror -std=c11
SRCS = 3d-viewer/*.c
TEST_SRCS = tests/*.c

# Используемые папки
SOURCE_DIR =3d-viewer
TSOURCES_DIR =tests
INSTALL_DIR =build
DIST_DIR =3DViewer_v1.0

TEST_FLAGS = -lcheck -lm -lpthread
GCOV_FLAGS = -ftest-coverage -fprofile-arcs
UNAME_S = $(shell uname -s)

ifeq ($(shell uname), Linux)
	TEST_FLAGS += -lrt -lsubunit
endif

LIBSOURCES = $(wildcard 3d-viewer/parser.c 3d-viewer/s21_affine_transform.c)
TESTSOURSES = $(wildcard tests/*.c)
SOURCES = $(LIBSOURCES) $(TESTSOURSES)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

ifeq ($(shell uname -s),Linux)
	OPEN_CMD = xdg-open
	OFLAGS =  -lcheck -lsubunit -lm -lrt -lpthread -lgcov -o 
endif

ifeq ($(shell uname -s),Darwin) # MacOS
	OPEN_CMD = open
	OFLAGS = -lcheck -lm -lpthread -lgcov -o
endif

TESTSOURSES =  tests/tests.c
SOURCES = $(TESTSOURSES) $(LIBSOURCES)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LC = lcov
EXECUTABLE = test
LCOVFLAGS = -c -d . -o
.c.o:
	$(CC) $(CFLAGS) $< $(GCOVFLAGS) -o $@

test: clean $(OBJECTS)
	$(CC) $(OBJECTS) $(OFLAGS) $@
	./$(EXECUTABLE)
	@rm -rf *.o

gcov_report: test
	$(LC) $(LCOVFLAGS) report.info
	genhtml report.info
	# $(OPEN_CMD) ./index.html

install: 
	make clean
	make uninstall
	mkdir $(INSTALL_DIR)
	make $(NAME)
	cd $(SOURCE_DIR) && qmake ../$(SOURCE_DIR)/$(NAME).pro && make && make clean && rm Makefile && cd ../ && mv $(SOURCE_DIR)/$(NAME) $(INSTALL_DIR)
uninstall:
	rm -rf $(INSTALL_DIR)

dvi:
	@doxygen conf && mv html documentation
	@open documentation/index.html

dist:
	rm -rf $(DIST_DIR)/
	mkdir $(DIST_DIR)/
	mkdir $(DIST_DIR)/src
	mkdir $(DIST_DIR)/src/$(SOURCE_DIR)
	mkdir $(DIST_DIR)/src/$(SOURCE_DIR)/imgs
	mkdir $(DIST_DIR)/src/$(TSOURCES_DIR)
	cp Makefile dvi.html $(DIST_DIR)/src/
	cp $(SOURCE_DIR)/*.h $(SOURCE_DIR)/*.pro $(SOURCE_DIR)/*.cpp $(SOURCE_DIR)/*.ui $(SOURCE_DIR)/*.user $(DIST_DIR)/src/$(SOURCE_DIR)/ 
	cp $(SOURCE_DIR)/imgs/* $(DIST_DIR)/src/$(SOURCE_DIR)/imgs/
	cp $(TSOURCES_DIR)/*.c $(DIST_DIR)/src/$(TSOURCES_DIR)
	tar cvzf $(DIST_DIR).tgz $(DIST_DIR)/
	mv $(DIST_DIR).tgz $(HOME)/Desktop/
	rm -rf $(DIST_DIR)/


rebuild: clean $(NAME)

clean:
	rm -rf test *.gcov *.css gcov*.html
	rm -rf *.o *.a *.out  $(SOURCE_DIR)/.qmake.stash  $(SOURCE_DIR)/*.user
	rm -rf *.gcda *.gcno *.info *.gch *.html
	rm -rf test report
	rm -rf documentation/
	rm -rf 3d-viewer/*.o
	rm -rf 3d-viewer/*.gcda 3d-viewer/*.gcno 3d-viewer/*.info 3d-viewer/*.gch 3d-viewer/*.html
	rm -rf tests/*.gcda tests/*.gcno tests/*.info tests/*.gch tests/*.html tests/*.o

clean_all: 
	make clean
	rm -rf build

style: 
	clang-format --style=google $(SRCS)  $(SOURCE_DIR)/*.cpp $(SOURCE_DIR)/*.h $(TEST_SRCS) -n

correct_style: 
	clang-format --style=google $(SRCS) $(SOURCE_DIR)/*.cpp $(SOURCE_DIR)/*.h $(TEST_SRCS) -i

installqt:
	sudo apt update
	sudo apt install clang-format
	sudo apt install qtcreator -y
	sudo apt install qtbase5-dev qtwayland5-dev-tools qtwayland5 -y
	sudo apt install qt5-qmake -y
	sudo apt install doxygen
