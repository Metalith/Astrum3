#ifndef LUNA_SYSTEM_HPP
#define LUNA_SYSTEM_HPP

#include <vector>

class Engine;

class System {
	public:
		virtual void update() = 0; //TODO: Set to take float delta time;
		virtual void addEntity(int e) { entities.push_back(e); }
		template<class T> void setComponent() { T tmp = T(); componentIDs.push_back(tmp.getID()); }
		static void setEngine(Engine* engine) { System::engine = engine; }
		std::vector<int> getIDs() { return componentIDs; }
	protected:
		static Engine* engine;
		std::vector<int> componentIDs;
		std::vector<int> entities;

		virtual ~System() {}
};

#endif
