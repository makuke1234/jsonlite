  #ifndef JSONLITE_H
#define JSONLITE_H

#ifdef __cplusplus
#include <cstdint>

extern "C"
{
#else
#include <stdint.h>
#include <stdbool.h>

#endif

typedef struct jsonliteS
{
	void* jsonlite_jsonL_mem;
	char* jsonlite_exceptioncode;
} jsonliteS_t;

// jsonlite libary's string to int conversions for signed integers
char jsonlite_stoi_c(const char* str);
short jsonlite_stoi_s(const char* str);
int jsonlite_stoi(const char* str);
long jsonlite_stoi_l(const char* str);
long long jsonlite_stoi_ll(const char* str);
intptr_t jsonlite_stoi_z(const char* str);

// jsonlite libary's string to int conversions for unsigned integers
unsigned char jsonlite_stou_c(const char* str);
unsigned short jsonlite_stou_s(const char* str);
unsigned int jsonlite_stou(const char* str);
unsigned long jsonlite_stou_l(const char* str);
unsigned long long jsonlite_stou_ll(const char* str);
size_t jsonlite_stou_zu(const char* str);

// jsonlite libary's string to floating point conversions
float jsonlite_stof(const char* str);
double jsonlite_stof_d(const char* str);
long double jsonlite_stof_ld(const char* str);


// Allocate memory for a json object
jsonliteS_t jsonlite_makeobject();
// Deallocate json object's memory
void jsonlite_freeobject(jsonliteS_t obj);

jsonliteS_t jsonlite_makekeyvalue(const char* key, const char* value);
jsonliteS_t jsonlite_makekeyvalues(const char* key, const char** values, size_t sz);
jsonliteS_t jsonlite_makekeyobject(const char* key, const jsonliteS_t object);
jsonliteS_t jsonlite_makekeyobjects(const char* key, const jsonliteS_t* objects, size_t sz);

jsonliteS_t jsonlite_parse(const char* str, size_t size);
char* dump(jsonliteS_t obj);
char* jsonlite_getexception(jsonliteS_t obj);
bool jsonlite_clearexception(jsonliteS_t obj);

jsonliteS_t jsonlite_at(jsonliteS_t origobj, const char* key);
jsonliteS_t jsonlite_index(jsonliteS_t origobj, int index);
const char* jsonlite_key(const jsonliteS_t obj);
const char* jsonlite_get(jsonliteS_t obj);
void jsonlite_equate(jsonliteS_t baseobj, const jsonliteS_t otherobj);
size_t jsonlite_size(const jsonliteS_t obj);

#ifdef __cplusplus
}
#endif

#endif
