# Documentation of the C bindings for the jsonlite C++ library

# List of library-dependent functions

| Function name           | Supports 'jsonlite_freeobject()'? |
| ----------------------- | --------------------------------- |
| jsonlite_makeobject     | yes                               |
| jsonlite_makekeyvalue   | yes                               |
| jsonlite_makekeyvalues  | yes                               |
| jsonlite_makekeyobject  | yes                               |
| jsonlite_makekeyobjects | yes                               |
| jsonlite_parse          | yes                               |
| jsonlite_at             | no                                |
| jsonlite_index          | no                                |

Using 'jsonlite_freeobject()' on any object returned by a function that does NOT
support it is undefined behaviour.
