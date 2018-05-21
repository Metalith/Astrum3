#ifndef COMPONENT_PLAYER
#define COMPONENT_PLAYER

#include "component.hpp"

class Player : public Component {
	public:
		int getID() { return 1; }
};

#endif
