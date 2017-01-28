# Project ABIM
Project ABIM is, or rather, will be a 2d game engine used by its developers in future video game projects. It is written in C++, though it uses some plain C features, and is based on OpenGL and GLFW.

## Dependencies
* OpenGL version 3.2 or newer
* libglfw <= 3.0.0

## Building
The build environment is based on autotools, so the usual procedure for projects based on it applies:
```bash
autoreconf
./configure
make
sudo make install
```

## Documentation
A lot of header files feature doxygen-style comments. Actual doxygen support is to-be implemented.
