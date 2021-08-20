# jsonlite
![Release version](https://img.shields.io/badge/beta-v0.9.0-green.svg)

A light-weight single-include C++ JSON library, relying on KISS (Keep It Stupid Simple)
convention and C++11 STL. Supports JSON string parsing and 'beautiful' dumping.
'Easy' C++-like syntax is also supported.


# Overview

Yes, it's just another JSON library that aims to achieve quick compilation times,
simplicity and ease of use, nothing more.
It implements its own universal string->integer and string->floating point
conversion bindings based on templates. Works on any signed or unsigned integer,
on any floating point type.

It also supports exceptions, they are designed to give hint about obvious syntax
errors and to be, yet again, simple.

Using the C++ library is pretty self-explanatory in its essence so no extra
documentation has been provided with it. The usage of the C bindings is a little
more tricky due to the language itself, thus more often than not the extra
documentation in the 'C_bindings/src' subdirectory might be helpful.


# C bindings

In the folder 'C_bindings' of my repository you can find the needed source files to
compile the C bindings of this C++ library yourself. If you think that would be unnecessary work,
you can just download the 'libjsonlite.a' file from the 'bin' subdirectory (as long
as you GCC/G++ to link the final executable).

The extra documentation neccessary for the C bindings is also located in 'src' subdirectory.


# Licensing

As stated, this project follows the MIT license.
