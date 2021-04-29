#include "jsonlite.h"
#include "jsonlite.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>

extern "C"
{
	// jsonlite libary's string to int conversions for signed integers
	char jsonlite_stoi_c(const char* str)
	{
		return jsonlite::stoi<char>(str);
	}
	short jsonlite_stoi_s(const char* str)
	{
		return jsonlite::stoi<short>(str);
	}
	int jsonlite_stoi(const char* str)
	{
		return jsonlite::stoi<int>(str);
	}
	long jsonlite_stoi_l(const char* str)
	{
		return jsonlite::stoi<long>(str);
	}
	long long jsonlite_stoi_ll(const char* str)
	{
		return jsonlite::stoi<long long>(str);
	}
	intptr_t jsonlite_stoi_z(const char* str)
	{
		return jsonlite::stoi<intptr_t>(str);
	}

	// jsonlite libary's string to int conversions for unsigned integers
	unsigned char jsonlite_stou_c(const char* str)
	{
		return jsonlite::stou<unsigned char>(str);
	}
	unsigned short jsonlite_stou_s(const char* str)
	{
		return jsonlite::stou<unsigned short>(str);
	}
	unsigned int jsonlite_stou(const char* str)
	{
		return jsonlite::stou<unsigned int>(str);
	}
	unsigned long jsonlite_stou_l(const char* str)
	{
		return jsonlite::stou<unsigned long>(str);
	}
	unsigned long long jsonlite_stou_ll(const char* str)
	{
		return jsonlite::stou<unsigned long long>(str);
	}
	size_t jsonlite_stou_zu(const char* str)
	{
		return jsonlite::stou<size_t>(str);
	}

	// jsonlite libary's string to floating point conversions
	float jsonlite_stof(const char* str)
	{
		return jsonlite::stof<float>(str);
	}
	double jsonlite_stof_d(const char* str)
	{
		return jsonlite::stof<double>(str);
	}
	long double jsonlite_stof_ld(const char* str)
	{
		return jsonlite::stof<long double>(str);
	}


	jsonliteS_t jsonlite_makeobject()
	{
		return { new jsonlite::jsonL, nullptr };
	}
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

	jsonliteS_t jsonlite_makekeyvalue(const char* key, const char* value)
	{
		return {
			new jsonlite::jsonL(key, { value }),
			nullptr
		};
	}
	jsonliteS_t jsonlite_makekeyvalues(const char* key, const char** values, size_t sz)
	{
		std::vector<std::string> valuesvec(sz);
		for (size_t i = 0; i < sz; i++)
		{
			valuesvec[i] = values[i];
		}
		return {
			new jsonlite::jsonL(key, valuesvec),
			nullptr
		};
	}
	jsonliteS_t jsonlite_makekeyobject(const char* key, const jsonliteS_t object)
	{
		return {
			new jsonlite::jsonL(key, { *static_cast<jsonlite::jsonL*>(object.jsonlite_jsonL_mem) }),
			nullptr
		};
	}
	jsonliteS_t jsonlite_makekeyobjects(const char* key, const jsonliteS_t* objects, size_t sz)
	{
		std::vector<jsonlite::jsonL> objvec(sz);
		for (size_t i = 0; i < sz; i++)
		{
			objvec[i] = *static_cast<jsonlite::jsonL*>(objects[i].jsonlite_jsonL_mem);
		}
		return {
			new jsonlite::jsonL(key, objvec),
			nullptr
		};
	}

	jsonliteS_t jsonlite_parse(const char* str, size_t size)
	{
		jsonliteS_t obj{};
		try
		{
			obj.jsonlite_jsonL_mem = new jsonlite::jsonL(
				jsonlite::jsonL::parse(str, size)
			);
		}
		catch (jsonlite::exception& e)
		{
			obj.jsonlite_exceptioncode = strdup(e.what());
		}
		return obj;
	}
	char* dump(jsonliteS_t obj)
	{
		auto const& str = static_cast<jsonlite::jsonL*>(obj.jsonlite_jsonL_mem)->dump();
		auto sz = (str.length() + 1) * sizeof(char);
		auto ret = static_cast<char*>(std::malloc(sz));
		return static_cast<char*>(std::memcpy(ret, str.c_str(), sz));
	}
	char* jsonlite_getexception(jsonliteS_t obj)
	{
		return obj.jsonlite_exceptioncode;
	}
	bool jsonlite_clearexception(jsonliteS_t obj)
	{
		if (obj.jsonlite_exceptioncode != nullptr)
		{
			std::free(obj.jsonlite_exceptioncode);
			obj.jsonlite_exceptioncode = nullptr;
			return true;
		}
		else
			return false;
	}

	jsonliteS_t jsonlite_at(jsonliteS_t origobj, const char* key)
	{
		jsonliteS_t obj{};
		try
		{
			obj.jsonlite_jsonL_mem = new jsonlite::jsonL(
				static_cast<jsonlite::jsonL*>(origobj.jsonlite_jsonL_mem)->operator[](key)
			);
		}
		catch (jsonlite::exception& e)
		{
			obj.jsonlite_exceptioncode = strdup(e.what());
		}
		return obj;
	}
	jsonliteS_t jsonlite_index(jsonliteS_t origobj, int index)
	{
		jsonliteS_t obj{};
		try
		{
			obj.jsonlite_jsonL_mem = new jsonlite::jsonL(
				static_cast<jsonlite::jsonL*>(origobj.jsonlite_jsonL_mem)->operator[](index)
			);
		}
		catch (jsonlite::exception& e)
		{
			obj.jsonlite_exceptioncode = strdup(e.what());
		}
		return obj;
	}
	const char* jsonlite_key(const jsonliteS_t obj)
	{
		return static_cast<jsonlite::jsonL*>(obj.jsonlite_jsonL_mem)->key().c_str();
	}
	const char* jsonlite_get(jsonliteS_t obj)
	{
		try
		{
			return const_cast<std::string const&>(
				static_cast<jsonlite::jsonL*>(
					obj.jsonlite_jsonL_mem
				)->get()
			).c_str();
		}
		catch (jsonlite::exception& e)
		{
			if (obj.jsonlite_exceptioncode)
				jsonlite_clearexception(obj);
			obj.jsonlite_exceptioncode = strdup(e.what());
		}
		return nullptr;
	}
	void jsonlite_equate(jsonliteS_t baseobj, const jsonliteS_t otherobj)
	{
		static_cast<jsonlite::jsonL*>(baseobj.jsonlite_jsonL_mem)->equate(
			*static_cast<jsonlite::jsonL*>(otherobj.jsonlite_jsonL_mem)
		);
	}
	size_t jsonlite_size(const jsonliteS_t obj)
	{
		return static_cast<jsonlite::jsonL*>(obj.jsonlite_jsonL_mem)->size();
	}
}
