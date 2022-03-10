# jsonlite

[![Release version](https://img.shields.io/github/v/release/makuke1234/jsonlite?display_name=release&include_prereleases)](https://github.com/makuke1234/jsonlite/releases/latest)
[![Total downloads](https://img.shields.io/github/downloads/makuke1234/jsonlite/total)](https://github.com/makuke1234/jsonlite/releases)
![C++ version](https://img.shields.io/badge/version-C++11-blue.svg)
[![wakatime](https://wakatime.com/badge/github/makuke1234/jsonlite.svg)](https://wakatime.com/badge/github/makuke1234/jsonlite)

A light-weight single-include C++ JSON library, relying on KISS (Keep It Stupid Simple)
convention and C++11 STL. Supports JSON string parsing and "beautiful" dumping.
"Easy" C++-like syntax is also supported.


# Overview

Yes, it`s just another JSON library that aims to achieve quick compilation times,
simplicity and ease of use, nothing more.
It implements its own universal string->integer and string->floating point
conversion bindings based on templates. Works on any signed or unsigned integer,
on any floating point type. Don't excpect to fully compliantly "edit" JSON strings
with this library, it only supports correctly parsing JSON strings to C++ objects
and not vice versa. That is because corners have been cut to save on code size
and thus compilation times. Writing this library a simplifying decision was made
to treat all JSON data types as strings only. To overcome this limitation, the
aforementioned conversion algorithms have been provided with this library as an extra.


This library also supports exceptions, they are designed to give hint about
obvious syntax errors and to be, yet again, simple.

Using the C++ library is pretty self-explanatory in its essence so no extra
documentation has been provided with it. The usage of the C bindings is a little
more tricky due to the language itself, thus more often than not the extra
documentation in the `C_bindings/src` subdirectory might be helpful.


# C bindings

In the folder `C_bindings` of my repository you can find the needed source files to
compile the C bindings of this C++ library yourself. If you think that would be unnecessary work,
you can just download the 64-bit `libjsonlite.a` file from the `bin` subdirectory (as long
as you GCC/G++ to link the final executable). If you want a 32-bit version then
you have to unfortunately compile it yourself.

The extra documentation necessary for the C bindings is also located in `src` subdirectory.


# Testing

In my opinion a comprehensive enough testing has been done, the jsonlite library
has been tested with hundreds of megabytes of TeliaTV's programme descriptions
and any bugs are yet to be found. If you find any scenario under which my library
breaks down while attempting to parse/use syntactically correct JSON files, feel free
to report those bugs under the *Issues* tab.


# Licensing

As stated on the *About* tab, this project follows the MIT License. Feel free to
do anything with my library under the circumstances of the MIT License.
