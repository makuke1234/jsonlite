#include "../jsonlite.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	// Try opening JSON
	if (argc <= 1)
	{
		return -1;
	}
	FILE * jsonFile = fopen(argv[1], "rb");
	if (jsonFile == NULL)
	{
		return -2;
	}
	fseek(jsonFile, 0, SEEK_END);
	size_t jsonStringLen = ftell(jsonFile);
	fseek(jsonFile, 0, SEEK_SET);

	char * jsonString = malloc(jsonStringLen);
	fread(jsonString, 1, jsonStringLen, jsonFile);

	// Close file
	fclose(jsonFile);

	// Allocate json object
	jsonliteS_t obj = jsonlite_parse(jsonString, jsonStringLen - 1);

	char * emsg = jsonlite_getexception(obj);
	if (emsg)
	{
		printf("jsonlite library throwed an exception message: \"%s\"\n", emsg);
		return -3;
	}

	// json object is OK, dump the contents
	char * jsonContents = jsonlite_dump(obj);
	puts(jsonContents);
	// Free them afterwards
	free(jsonContents);

	// For fun get the contents of ["object"]["also numbers"][1]
	jsonliteS_t obj_object = jsonlite_at(obj, "object");
	emsg = jsonlite_getexception(obj_object);
	if (emsg)
		return -4;
	jsonliteS_t object_also_numbers = jsonlite_at(obj_object, "also numbers");
	emsg = jsonlite_getexception(object_also_numbers);
	if (emsg)
		return -5;
	jsonliteS_t also_numbers_1 = jsonlite_index(object_also_numbers, 1);
	emsg = jsonlite_getexception(also_numbers_1);
	if (emsg)
		return -6;
	// So far, no errors
	// Get value
	const char * svalue = jsonlite_get(also_numbers_1);
	// Convert to double
	double value = jsonlite_stof_d(svalue);
	// Print value
	printf("Value at [\"object\"][\"also numbers\"][1]: \"%f\"\n", value);

	// Convert to string
	{
		jsonlite_at(object_also_numbers, "45");
		jsonlite_at(object_also_numbers, "44");
	}

	// Dump new tree
	jsonContents = jsonlite_dump(obj);
	puts(jsonContents);
	// Free them afterwards
	free(jsonContents);

	// Free the object afterwards
	jsonlite_freeobject(obj);


	return 0;
}