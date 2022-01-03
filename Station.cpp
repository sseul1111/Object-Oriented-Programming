#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {

	size_t Station::m_widthField = 0u;
	int Station::id_generator = 0;

	Station::Station() {}

	Station::Station(const std::string& str)
	{
		Utilities utility;
		size_t next_pos = 0;
		bool more = true;

		m_id = ++id_generator;
		try {
			m_name = utility.extractToken(str, next_pos, more);
			m_serial = stoi(utility.extractToken(str, next_pos, more));
			m_numberOfItems = stoi(utility.extractToken(str, next_pos, more));
			m_widthField = (m_widthField < utility.getFieldWidth()) ? utility.getFieldWidth() : m_widthField;
			m_desc = utility.extractToken(str, next_pos, more);
		}
		catch (std::string& err) {
			std::cout << err;
		}
	}

	const std::string& Station::getItemName() const
	{
		return m_name;
	}

	size_t Station::getNextSerialNumber()
	{
		m_serial++;
		return m_serial - 1;
	}

	size_t Station::getQuantity() const
	{
		return m_numberOfItems;
	}

	void Station::updateQuantity()
	{
		m_numberOfItems--;
		if (m_numberOfItems < 0)
			m_numberOfItems = 0;
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os << "[" << std::right << std::setw(3) << std::setfill('0') << m_id << "]";
		os << " Item: " << std::setw(m_widthField) << std::left << std::setfill(' ') << m_name;
		os << " [" << std::setw(6) << std::right << std::setfill('0') << m_serial << "]";

		if (full) {
			os << " Quantity: " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_numberOfItems;
			os << " Description: " << m_desc << std::endl;
		}
		else {
			os << std::endl;
		}


	}
}