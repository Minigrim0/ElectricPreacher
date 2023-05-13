ALL_CPP_FILES=$(wildcard src/*/*.cpp)
ALL_H_FILES=$(wildcard includes/*/*.hpp)

all: compile doc

compile:
	meson setup build
	ninja -C build

run: compile
	./build/ElectricPreacher

doc:
	doxygen

check:
	ninja cppcheck -C build

clean:
	ninja -C build clean
