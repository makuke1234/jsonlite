# Documentation of the C bindings for the jsonlite C++ library

## List of library-dependent functions relevant to `jsonlite_freeobject()`

- ✔ `jsonlite_makeobject`
- ✔ `jsonlite_makekeyvalue`
- ✔ `jsonlite_makekeyvalues`
- ✔ `jsonlite_makekeyobject`
- ✔ `jsonlite_makekeyobjects`
- ✔ `jsonlite_parse`
- ❌ `jsonlite_at`
- ❌ `jsonlite_index`


Using `jsonlite_freeobject()` on any object returned by a function that does **NOT**
support it, is **undefined behaviour**.

### Explanation behind design philosophies

Functions like `jsonlite_makeobject()` support `jsonlite_freeobject()` because of
the implementation details. These type of functions will allocate their own memory
(note the `new` operator on line 3):

```Cpp
jsonliteS_t jsonlite_makeobject()
{
	return { new jsonlite::jsonL, nullptr };
}
```

And `jsonlite_freeobject()` will deallocate it:

```Cpp
void jsonlite_freeobject(jsonliteS_t obj)
{
	if (obj.jsonlite_jsonL_mem != nullptr)
	{
		delete static_cast<jsonlite::jsonL*>(obj.jsonlite_jsonL_mem);
		obj.jsonlite_jsonL_mem = nullptr;
	}
	if (obj.jsonlite_exceptioncode != nullptr)
	{
		std::free(obj.jsonlite_exceptioncode);
		obj.jsonlite_exceptioncode = nullptr;
	}
}
```


For maintaining reference-like behaviour on C objects, some functions like `jsonlite_at`
take the address of the underlying object that must have been allocated at some
point down the object dependency chain (note the `&` on line 6).

```Cpp
jsonliteS_t jsonlite_at(jsonliteS_t origobj, const char* key)
{
	jsonliteS_t obj{};
	try
	{
		obj.jsonlite_jsonL_mem = &static_cast<jsonlite::jsonL*>(
			origobj.jsonlite_jsonL_mem
		)->operator[](key);
	}
	catch (jsonlite::exception& e)
	{
		obj.jsonlite_exceptioncode = strdup(e.what());
	}
	return obj;
}
```
