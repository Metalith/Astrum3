#ifndef LUNA_ENGINE_HPP
#define LUNA_ENGINE_HPP

#include "components/component.hpp"
#include "systems/system.hpp"
#include <vector>
#include <typeinfo>
#include <iostream>
//TODO: DOCUMENT THIS.

class Engine {
	public:
		Engine();
		void update();

		void addSystem(System* sys);
		void addComponent(int id, Component* c);
		int createEntity();
		void deleteEntity();

		template<class T>
		T* getComponent(int e) {
			T* tmp;
			for (auto* c : entities[e]) {
				if ((tmp = dynamic_cast<T*>(c)) != nullptr) {
					return tmp;
				}
			}
			std::cout << "Could not find component " << typeid(tmp).name() << std::endl;
			return nullptr;
		};
	private:
		std::vector<System*> systemList;
		std::vector<std::vector<Component*>> entities; //A vector of entities with their corresponding components
		std::vector<int> added;
};
#endif
