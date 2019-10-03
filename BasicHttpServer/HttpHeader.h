#pragma once
#include <string>

namespace HttpServerNS {
	class HttpHeader
	{
	private:
		std::string name;
		std::string value;
	public:
		HttpHeader(std::string name, std::string value);
		~HttpHeader();

		std::string getName() const { return name; }
		std::string getValue() const { return value; }
		std::string addValue(std::string value) { this->value += "," + value; return value; }
	};

}
