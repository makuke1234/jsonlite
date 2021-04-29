# C bindings for the jsonlite C++ libary

This folder contains the binary static libary suited for Windows, compiled with MinGW-32.
Keep in mind that you can compile the C code using the bindings with gcc, but linking needs to be done with g++
because the original C++ library itself must be linked against libstdc++ as it depends on the STL.

To use the binary just grab the 'libjsonlite.a' file to link against and you are good to go!

Have fun enjoying my library! :)
