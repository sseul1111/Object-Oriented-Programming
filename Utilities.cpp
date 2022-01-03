#include <iostream>
#include <string>
#include <algorithm>
#include "Utilities.h"

namespace sdds {

	char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token = "";

		if (str[next_pos] == m_delimiter) {
			more = false;
			throw("Found Delimiter!");
		}
		else if (str.find(m_delimiter, next_pos) == std::string::npos) {
			token = str.substr(next_pos);
			more = false;
			next_pos = 0;
		}
		else {
			token = str.substr(next_pos, str.find_first_of(m_delimiter, next_pos) - next_pos);
			next_pos = str.find(m_delimiter, next_pos) + 1;
			more = true;
		}

		if (m_widthField < token.length())
			m_widthField = token.length();

		return token;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}