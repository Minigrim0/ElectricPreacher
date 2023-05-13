ALL_CPP_FILES=$(wildcard src/*/*.cpp)
ALL_H_FILES=$(wildcard includes/*/*.hpp)

all: build check documentation

build: $(ALL_CPP_FILES) $(ALL_H_FILES) main.cpp constants.hpp
	meson build
	ninja -C build

run: build
	./build/ElectricPreacher

documentation:
	doxygen

check:
	ninja cppcheck -C build
