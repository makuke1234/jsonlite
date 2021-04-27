#pragma once

#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <exception>
#include <type_traits>
#include <functional>

namespace jsonlite
{
	template<class T, typename std::enable_if<std::is_signed<T>::value>::type* = nullptr>
	inline T stoi(std::string const& str)
	{
		return T(std::stoi(str));
	}
	template<> inline long stoi<long>(std::string const& str)
	{
		return std::stol(str);
	}
	template<> inline long long stoi<long long>(std::string const& str)
	{
		return std::stoll(str);
	}
	template<class T, typename std::enable_if<std::is_unsigned<T>::value>::type* = nullptr>
	inline T stou(std::string const& str)
	{
		return T(std::stoul(str));
	}
	template<> inline unsigned long long stou<unsigned long long>(std::string const& str)
	{
		return std::stoull(str);
	}
	
	template<class T> inline T stof(std::string const& str);
	template<> inline float stof<float>(std::string const& str)
	{
		return std::stof(str);
	}
	template<> inline double stof<double>(std::string const& str)
	{
		return std::stod(str);
	}
	template<> inline long double stof<long double>(std::string const& str)
	{
		return std::stold(str);
	}

	class jsonL;

	class exception : public std::exception
	{
	private:
		friend class jsonL;
		enum class type : char {
			Unknown,
			NotAnEndpoint,
			OutOfBounds,

			ParseNoTerminatingQuote,
			ParseNoTerminatingCurly,
			ParseNoTerminatingBracket,
			ParseIncorrectNull,
			ParseIncorrectTrue,
			ParseIncorrectFalse,
			ParseIncorrectNumber,
			ParseIncorrectValue,
			ParseNoKeyValue,
			
			enum_size
		};
		type Type{ type::Unknown };
		const char* exceptionMessages[std::underlying_type<type>::type(type::enum_size)]
		{
			"Unknown exception.",
			"This is not an end-point in the object structure!",
			"The array does not contain an item at this index!",

			"String's terminating '\"' not found!",
			"Object's terminating '}' not found!",
			"Array's terminating ']' not found!",
			"Incorrect 'null' representation!",
			"Incorrect boolean 'true' representation!",
			"Incorrect boolean 'false' representation!",
			"Incorrect number format!",
			"Object key's ':' not found!",
			"Object key's value not found!"
		};
		exception() noexcept = default;

	public:
		explicit exception(type Type_) noexcept
			: Type(Type_)
		{}

		const char* what() const throw() override
		{
			return exceptionMessages[long(std::underlying_type<type>::type(Type))];
		}
	};

	class jsonL
	{
	private:
		std::string Key;
		std::vector<jsonL> values;
		std::unordered_map<std::string, std::size_t> indexes;

		enum class objtype : char {
			EmptyObject,
			Object,
			PairObject,
			EndPoint,
		};
		objtype role{ objtype::EmptyObject };

		explicit jsonL(const char* key_)
			: Key(key_), role(objtype::EndPoint)
		{}
		explicit jsonL(std::string const& key_)
			: Key(key_), role(objtype::EndPoint)
		{}
		static inline std::string recurseValues(std::vector<jsonL> const& val, std::size_t depth);
		static inline jsonL recurseParse(const char* str, std::size_t len, char type);
	public:
		static inline jsonL parse(const char* str, std::size_t len = 0)
		{
			// If length not given, calculate string length
			if (len == 0)
				len = std::char_traits<char>::length(str);

			// Get starting position for the JSON structure
			auto sp = str, ep = str + len;
			for (; sp != ep; ++sp)
			{
				if (*sp == '{')
				{
					++sp;
					break;
				}
			}
			// Get ending position for the JSON structure
			for (--ep; ep != sp; --ep)
			{
				if (*ep == '}')
				{
					--ep;
					break;
				}
			}

			return jsonL::recurseParse(sp, ep - sp + 1, '{');
		}
		static inline jsonL parse(std::string const& str)
		{
			return jsonL::parse(str.c_str(), str.length());
		}
		inline std::string dump() const
		{
			return "{\n" + recurseValues(values, std::size_t(1)) + '}';
		}

		jsonL() noexcept = default;
		jsonL(jsonL const& other) = default;
		jsonL(jsonL&& other) noexcept = default;
		jsonL& operator=(jsonL const& other) = default;
		jsonL& operator=(jsonL&& other) noexcept = default;
		~jsonL() noexcept = default;

		jsonL& operator=(std::initializer_list<jsonL> objs_)
		{
			role = objtype::Object;
			for (auto&& i : objs_)
			{
				indexes[i.Key] = values.size();
				values.emplace_back(std::move(i));
			}
			return *this;
		}

		jsonL(const char* key_, std::initializer_list<jsonL> objs_)
			: Key(key_), role(objtype::Object)
		{
			for (auto const& i : objs_)
			{
				indexes[i.Key] = values.size();
				values.push_back(i);
			}
		}
		jsonL(std::string const& key_, std::initializer_list<jsonL> objs_)
			: Key(key_), role(objtype::Object)
		{
			for (auto const& i : objs_)
			{
				indexes[i.Key] = values.size();
				values.push_back(i);
			}
		}
		jsonL(const char* key_, std::initializer_list<const char*> values_)
			: Key(key_), role(objtype::Object)
		{
			for (auto i : values_)
			{
				indexes[i] = values.size();
				values.push_back(jsonL(i));
			}
		}
		jsonL(std::string const& key_, std::initializer_list<std::string> values_)
			: Key(key_), role(objtype::Object)
		{
			for (auto i : values_)
			{
				indexes[i] = values.size();
				values.push_back(jsonL(i));
			}
		}
		jsonL(const char* key_, const char* value_)
			: Key(key_), values{ jsonL(value_) }, indexes{ {value_, 0} }, role(objtype::PairObject)
		{}
		jsonL(std::string const& key_, std::string const& value_)
			: Key(key_), values{ jsonL(value_) }, indexes{ {value_, 0} }, role(objtype::PairObject)
		{}

		jsonL& operator[](const char* key_)
		{
			auto it = indexes.find(key_);
			if (it == indexes.end())
			{
				indexes[key_] = values.size();
				values.push_back(jsonL(key_));
				return values.back();
			}
			else
				return values[it->second];
		}
		jsonL& operator[](std::string const& key_)
		{
			auto it = indexes.find(key_);
			if (it == indexes.end())
			{
				indexes[key_] = values.size();
				values.push_back(jsonL(key_));
				return values.back();
			}
			else
				return values[it->second];
		}
		jsonL& operator[](int index)
		{
			if (std::size_t(index) >= values.size())
				throw jsonlite::exception(jsonlite::exception::type::OutOfBounds);
			return values[index];
		}
		std::string const& key() noexcept
		{
			return Key;
		}
		std::string& get()
		{
			if (role == objtype::PairObject)
				return values.front().Key;
			else if (role == objtype::EndPoint)
				return Key;
			else
				throw jsonlite::exception(jsonlite::exception::type::NotAnEndpoint);
		}
		std::string const& get() const
		{
			if (role == objtype::PairObject)
				return values.front().Key;
			else if (role == objtype::EndPoint)
				return Key;
			else
				throw jsonlite::exception(jsonlite::exception::type::NotAnEndpoint);
		}
		void equate(jsonL const& addable)
		{
			if (addable.role == objtype::EndPoint)
			{
				indexes = { { addable.Key, 0 } };
				values = { addable };
				role = objtype::PairObject;
			}
			else
			{
				values = addable.values;
				indexes = addable.indexes;
				role = objtype::Object;
			}
		}
		std::size_t size() const noexcept
		{
			return values.size();
		}

		template<class T, typename std::enable_if<std::is_unsigned<T>::value>::type* = nullptr,
			typename std::enable_if<!std::is_same<T, bool>::value>::type* = nullptr>
		T getas() const
		{
			return jsonlite::stou<T>(get());
		}
		template<class T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr,
			typename std::enable_if<std::is_signed<T>::value>::type* = nullptr>
		T getas() const
		{
			return jsonlite::stoi<T>(get());
		}
		template<class T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
		T getas() const
		{
			return jsonlite::stof<T>(get());
		}
		template<class T, typename std::enable_if<std::is_same<T, bool>::value>::type* = nullptr>
		T getas() const
		{
			return get().compare(0, 5, "true") == 0 ? true : false;
		}
		template<class T, typename std::enable_if<std::is_same<T, std::string::const_pointer>::value>::type* = nullptr>
		T getas() const
		{
			return get().c_str();
		}
		template<class T, typename std::enable_if<std::is_same<T, std::string>::value>::type* = nullptr>
		T getas() const
		{
			return get();
		}
	};

	// Parse JSON objects from string recursively
	inline jsonL jsonL::recurseParse(const char* str, std::size_t len, char type)
	{
		static std::function<bool(const char*, const char* (&), const char*)> findend;
		findend = [](const char* s, const char* (&e), const char* endp) -> bool
		{
			// Check also for endp
			switch (*s)
			{
				// Find the value
				case '"':
				{
					auto prev = '"';
					for (e = s + 1; e != endp; ++e)
					{
						if (*e == '"' && prev != '\\')
							return true;
						prev = *e;
					}
					break;
				}
				case '[':
				case '{':
				{
					std::vector<char> st{ *s };
					for (e = s + 1; e != endp; ++e)
					{
						if (*e == '"')
						{
							if (!findend(e, e, endp))
								return false;
						}
						else
						{
							if (*e == '[' || *e == '{')
								st.push_back(*e);
							else if ((*e == ']' && st.back() == '[') || (*e == '}' && st.back() == '{'))
								st.pop_back();

							if (st.empty())
								return true;
						}
					}
					break;
				}
			}
			return false;
		};

		jsonL obj;

		if (!len)
		{
			if (type == '[')
			{
				obj.values.push_back(jsonL("nullptr"));
			}
		}

		for (auto sp = str, ep = str + len; sp != ep; ++sp)
		{
			if (type == '[')
			{
				const char* strend = nullptr;
				switch (*sp)
				{
				case '"':
					if (!findend(sp, strend, ep))
						throw exception(exception::type::ParseNoTerminatingQuote);
					obj.values.push_back(jsonL(std::string(sp + 1, strend - sp - 1)));
					sp = strend;
					break;
				case '{':
					if (!findend(sp, strend, ep))
						throw exception(exception::type::ParseNoTerminatingCurly);
					obj.values.push_back(recurseParse(sp + 1, strend - sp - 1, '{'));
					sp = strend;
					break;
				case 'n':
					if (strncmp(sp, "null", 4) == 0)
						sp += 3;
					else if (strncmp(sp, "nullptr", 7) == 0)
						sp += 6;
					else
						throw exception(exception::type::ParseIncorrectNull);

					// No need to check, exception has been already thrown if something is wrong						
					obj.values.push_back(jsonL("nullptr"));
					break;
				case 't':
					if (strncmp(sp, "true", 4) == 0)
						sp += 3;
					else
						throw exception(exception::type::ParseIncorrectTrue);
					
					obj.values.push_back(jsonL("true"));
					break;
				case 'f':
					if (strncmp(sp, "false", 5) == 0)
						sp += 4;
					else
						throw exception(exception::type::ParseIncorrectFalse);
					
					obj.values.push_back(jsonL("false"));
					break;
				default:
					if (*sp >= '0' && *sp <= '9')
					{
						bool done{ false };
						// Find number end
						bool containsdot{ false };
						for (strend = sp + 1; strend != ep; ++strend)
						{
							if (*strend == '.')
							{
								if (containsdot)
									throw exception(exception::type::ParseIncorrectNumber);
								containsdot = true;
							}
							else if (!(*strend >= '0' && *strend <= '9'))
							{
								obj.values.push_back(jsonL(std::string(sp, strend - sp)));
								sp = strend - 1;
								done = true;
								break;
							}
						}
						if (!done)
						{
							obj.values.push_back(jsonL(std::string(sp, strend - sp)));
							sp = strend - 1;
						}
					}
				}
			}
			else if (type == '{')
			{
				// Found the starting position for the string
				if (*sp == '"')
				{
					// Find string end
					const char* strend = nullptr;
					if (!findend(sp, strend, sp))
						throw exception(exception::type::ParseNoTerminatingQuote);

					std::string tokenKey(sp + 1, strend - sp - 1);

					sp = strend;
					// Scan for the ':' character marking the start of the value
					while (*++sp != ':')
					{
						if (sp == ep)
							throw exception(exception::type::ParseIncorrectValue);
					}
					// Find for '"', '[', '{', 'n', 't', 'f' or a number to identify the value type
					do
					{
						++sp;
						if (sp == ep)
							throw exception(exception::type::ParseNoKeyValue);
					} while (*sp != '"' && *sp != '[' && *sp != '{' && *sp != 'n' && *sp != 't' && *sp != 'f' && !(*sp >= '0' && *sp <= '9'));
					
					switch (*sp)
					{
						// string : value pair
					case '"':
						// find value
						if (!findend(sp, strend, ep))
							throw exception(exception::type::ParseNoTerminatingQuote);
						obj[tokenKey].equate(jsonL(std::string(sp + 1, strend - sp - 1)));
						sp = strend;
						break;
						// array
					case '[':
						if (!findend(sp, strend, ep))
							throw exception(exception::type::ParseNoTerminatingBracket);
						obj[tokenKey].equate(recurseParse(sp + 1, strend - sp - 1, '['));
						sp = strend;
						break;
						// object
					case '{':
						if (!findend(sp, strend, ep))
							throw exception(exception::type::ParseNoTerminatingCurly);
						obj[tokenKey].equate(recurseParse(sp + 1, strend - sp - 1, '{'));
						sp = strend;
						break;
						// check for null or nullptr
					case 'n':
						if (strncmp(sp, "null", 4) == 0)
							sp += 3;
						else if (strncmp(sp, "nullptr", 7) == 0)
							sp += 6;
						else
							throw exception(exception::type::ParseIncorrectNull);

						// No need to check, exception has been already thrown if something is wrong						
						obj[tokenKey].equate(jsonL("nullptr"));
						break;
					case 't':
						if (strncmp(sp, "true", 4) == 0)
							sp += 3;
						else
							throw exception(exception::type::ParseIncorrectTrue);
						
						obj[tokenKey].equate(jsonL("true"));
						break;
					case 'f':
						if (strncmp(sp, "false", 5) == 0)
							sp += 4;
						else
							throw exception(exception::type::ParseIncorrectFalse);
						
						obj[tokenKey].equate(jsonL("false"));
						break;
					default:
						// if is a number
						if (*sp >= '0' && *sp <= '9')
						{
							// Find number end
							bool containsdot{ false };
							bool done{ false };
							for (strend = sp + 1; strend != ep; ++strend)
							{
								if (*strend == '.')
								{
									if (containsdot)
										throw exception(exception::type::ParseIncorrectNumber);
									containsdot = true;
								}
								else
								{
									if (!(*strend >= '0' && *strend <= '9'))
									{
										obj[tokenKey].equate(jsonL(std::string(sp, strend - sp)));
										sp = strend - 1;
										done = true;
										break;
									}
								}
							}
							if (!done)
							{
								obj[tokenKey].equate(jsonL(std::string(sp, strend - sp)));
								sp = strend - 1;
							}
						}
					}
				}
			}
		}

		return obj;
	}

	inline std::string jsonL::recurseValues(std::vector<jsonL> const& val, std::size_t depth)
	{
		std::ostringstream dumpstream;

		for (auto i = val.begin(); i != val.end(); ++i)
		{
			for (std::size_t j = 0; j < depth; ++j)
			{
				dumpstream << '\t';
			}

			if (i->role == objtype::PairObject)
			{
				dumpstream << '"' << i->Key << "\": \"" << i->values.front().Key << '"';
				if (std::next(i) != val.end())
					dumpstream << ',';
				dumpstream << '\n';
			}
			else if (i->role == objtype::EndPoint)
			{
				dumpstream << '"' << i->Key << '"';
				if (std::next(i) != val.end())
					dumpstream << ',';
				dumpstream << '\n';
			}
			else
			{
				dumpstream << '"' << i->Key << "\":\n";
				for (std::size_t j = 0; j < depth; ++j)
				{
					dumpstream << '\t';
				}
				bool endpoint = false;
				if (i->values.front().role == objtype::EndPoint)
					endpoint = true;
				dumpstream << (endpoint ? '[' : '{');
				dumpstream << '\n' << recurseValues(i->values, depth + 1);
				for (std::size_t j = 0; j < depth; ++j)
				{
					dumpstream << '\t';
				}
				dumpstream << (endpoint ? ']' : '}');

				if (std::next(i) != val.end())
					dumpstream << ',';
				dumpstream << '\n';
			}
		}

		return dumpstream.str();
	}
}
