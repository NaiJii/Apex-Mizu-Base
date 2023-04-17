#pragma once

#include "type/ClientClass.h"

struct CHLClient {
	VCALL(ClientClass_t*, GetAllClasses, 12, (), (this));
};