#include "../jsonlite.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	jsonliteS_t obj = jsonlite_parse("{\"lite\":\"not lite\"}", 0);

	const char* exception = jsonlite_getexception(obj);
	if (exception != NULL)
	{
		printf("Failed to parse json. Exception message:\"%s\"\n", exception);
		return 1;
	}
	jsonliteS_t liteobj = jsonlite_at(obj, "lite");
	exception = jsonlite_getexception(liteobj);
	if (exception != NULL)
	{
		printf("Failed to get index! Exception message:\"%s\"\n", exception);
		return 1;
	}

	const char* value = jsonlite_get(liteobj);
	if (value == NULL)
	{
		printf("Fail to get value! Exception message:\"%s\"\n", jsonlite_getexception(liteobj));
		return 1;
	}
	printf("obj value: \"%s\"\n", value);
	return 0;
}
