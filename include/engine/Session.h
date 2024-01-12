#ifndef SESSION_H
#define SESSION_H

#include "engine/Component.h"
#include <vector>
#include <typeinfo>

class Component; // Pre-declaration

class Session
{
public:
	Session() = default;
	~Session();
	void add(Component *comp);
	void remove(Component *comp);
	void run();
	std::vector<Component *> getAllComponents() const;
	std::vector<Component *> getComponentsOfType(const std::type_info &targetType) const;

private:
	std::vector<Component *> comps;
	std::vector<Component *> added, removed;
	Session &operator=(Session &) = delete;
	Session(Session &) = delete;
};

extern Session ses;

#endif