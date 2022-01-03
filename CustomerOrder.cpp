#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

	size_t CustomerOrder::m_widthField = 0u;

	CustomerOrder::CustomerOrder() : m_name{ "" }, m_product{ "" }, m_cntItem{ 0 }, m_listItem{ nullptr } {}

	CustomerOrder::CustomerOrder(const std::string str)
	{
		Utilities token;
		bool more = true;
		size_t pos = 0u;
		m_cntItem = 0;

		m_name = token.extractToken(str, pos, more);
		m_product = token.extractToken(str, pos, more);

		size_t pos_2 = pos;

		while (more) {
			token.extractToken(str, pos, more);
			m_cntItem++;
		}

		m_listItem = new Item * [m_cntItem];
		more = true;

		for (size_t i = 0u; i < m_cntItem; i++) {
			m_listItem[i] = new Item(token.extractToken(str, pos_2, more));
		}

		if (token.getFieldWidth() > m_widthField)
			m_widthField = token.getFieldWidth();

	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		*this = std::move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
	{
		if (this != &src) {
			if (m_listItem) {
				for (size_t i = 0u; i < m_cntItem; i++) {
					delete m_listItem[i];
				}
				delete[] m_listItem;
			}

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_listItem = src.m_listItem;

			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0;
			src.m_listItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		if (m_listItem) {
			for (size_t i = 0u; i < m_cntItem; i++) {
				delete m_listItem[i];
			}
		}
		delete[] m_listItem;
		m_listItem = nullptr;
	}

	bool CustomerOrder::isFilled() const
	{
		bool fill = true;
		for (size_t i = 0u; i < m_cntItem && fill; i++) {
			if (m_listItem[i]->m_isFilled == false)
				fill = false;
		}
		return fill;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool fill = true;
		std::for_each(m_listItem, (m_listItem + m_cntItem), [itemName, &fill](const Item* item) {
			if (item->m_itemName == itemName && !item->m_isFilled)
				fill = false;
			});

		return fill;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0u; i < m_cntItem; i++) {
			if (m_listItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_listItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_listItem[i]->m_isFilled = true;

					os << right << "    Filled ";
					os << m_name << ", " << m_product << " [" << m_listItem[i]->m_itemName << "]" << endl;
				}
				else {
					os << right << "    Unable to fill ";
					os << m_name << ", " << m_product << " [" << m_listItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << setw(6) << right << setfill('0') << m_listItem[i]->m_serialNumber << "] ";
			os << setw(m_widthField) << left << setfill(' ') << m_listItem[i]->m_itemName << " - ";
			os << (m_listItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	}

}