#ifndef SDDS_STATION_H
#define SDDS_STATION_H

namespace sdds {
	class Station {
		int m_id = 0;
		std::string m_name{ "" };
		std::string m_desc{ "" };
		unsigned int m_serial = 0;
		unsigned int m_numberOfItems = 0;
		static size_t m_widthField;
		static int id_generator;
	public:
		Station();
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif
