# C bindings for the jsonlite C++ libary

This folder contains the binary static libary suited for Windows, compiled with MinGW-32.
Keep in mind that you can compile the C code using the bindings with gcc, but linking needs to be done with g++
because the original C++ library itself must be linked against libstdc++ as it depends on the STL.

To use the binary just grab the 'libjsonlite.a' file to link against and you are
good to go (when using GCC to link your executable)!
If you are using any other compiler than GCC to compile your C program, then you
either MUST link with G++'s C++ standard library OR compile these C-bindings yourself.
If you chose to recompile C-bindings, feel free to use any compiler supporting at
least C++11 (GCC, Clang, MSVC should be OK).

Have fun enjoying my library! :)
