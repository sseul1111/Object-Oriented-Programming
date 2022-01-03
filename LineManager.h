#ifndef LINEMANAGER_H
#define LINEMANAGER_H
namespace sdds {
	class LineManager {
		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder;
		Workstation* m_firstStation;
	public:
		LineManager();
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		LineManager(const LineManager& lm) = delete;
		LineManager& operator=(const LineManager& lm) = delete;
		LineManager(LineManager&& lm) noexcept = delete;
		LineManager& operator=(LineManager&& lm) noexcept = delete;
		~LineManager() {}
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif
