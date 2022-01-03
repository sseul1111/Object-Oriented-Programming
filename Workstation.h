#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

extern std::deque<sdds::CustomerOrder> pending;
extern std::deque<sdds::CustomerOrder> completed;
extern std::deque<sdds::CustomerOrder> incomplete;

namespace sdds {
	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation;
	public:
		Workstation();
		Workstation(const std::string str);
		Workstation(const Workstation& ws) = delete;
		Workstation& operator=(const Workstation& ws) = delete;
		Workstation(Workstation&& ws) noexcept = delete;
		Workstation& operator=(Workstation&& ws) noexcept = delete;
		~Workstation() {} 
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif
