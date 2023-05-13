all: build check documentation

build:
	meson build
	ninja -C build

run: build
	./build/ElectricPreacher

documentation:
	doxygen

checks:
	ninja cppcheck -C build
