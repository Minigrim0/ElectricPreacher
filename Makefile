all: build check documentation

build:
	meson build
	ninja -C build

documentation:
	doxygen

checks:
	ninja cppcheck -C build
