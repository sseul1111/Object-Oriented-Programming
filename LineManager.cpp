#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include "Workstation.h"
#include "LineManager.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	LineManager::LineManager()
	{
		m_cntCustomerOrder = 0;
		m_firstStation = nullptr;
	}

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		try {
			m_cntCustomerOrder = pending.size();
			m_firstStation = nullptr;

			std::fstream readFile(file);
			if (!readFile) throw("");

			std::string temp;
			Utilities util;
			while (std::getline(readFile, temp)) {
				size_t next_pos = 0;
				bool more;
				std::string first, next;

				first = util.extractToken(temp, next_pos, more);
				if (more) next = util.extractToken(temp, next_pos, more);

				std::for_each(stations.begin(), stations.end(), [&](Workstation* station) {
					if (station->getItemName() == first) {
						std::for_each(stations.begin(), stations.end(), [&](Workstation* nextStation) {
							if (nextStation->getItemName() == next) {
								station->setNextStation(nextStation);
							}
							});
						activeLine.push_back(station);
					}
					});

				m_firstStation = activeLine.front();
			}
		}
		catch (...) {
			throw std::string("Error loading LineManager.");
		}
	}

	void LineManager::linkStations()
	{
		std::vector<Workstation*> reorder{ m_firstStation };
		size_t i = 0;

		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* current) {
			std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* next) {
				if (reorder[i]->getNextStation())
					if (reorder[i]->getNextStation()->getItemName() == next->getItemName()) {
						reorder.push_back(next);
						i++;
					}
				});
			});

		activeLine = reorder;
	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t iterNum = 0;
		size_t prevOrdersFinished = completed.size() + incomplete.size();

		os << "Line Manager Iteration: " << ++iterNum << std::endl;
		if (!pending.empty()) {
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}

		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws) {
			ws->fill(os);
			});

		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws) {
			ws->attemptToMoveOrder();
			});

		m_cntCustomerOrder -= ((completed.size() + incomplete.size()) - prevOrdersFinished);
		return m_cntCustomerOrder <= 0;
	}

	void LineManager::display(std::ostream& os) const
	{
		std::for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* ws) { ws->display(os); });
	}
}