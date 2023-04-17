#pragma once
// not a module because we actually want to import all of the #include of this file too
#include <cstdint>
#include <cstddef>
#include "../memory/virtual.h"

#include "type/angle.h"
#include "type/color.h"
#include "type/convar.h"
#include "type/collideable.h"
#include "type/CUserCmd.h"
#include "type/entity.h"
#include "type/matrix.h"
#include "type/recv.h"

#include "type/utl.h"
#include "type/vector.h"

#include "definitions.h"

#include "CClientState.h"
#include "CEngineClient.h"
#include "CEntityList.h"
#include "CGlobalBaseVars.h"
#include "CHLClient.h"
#include "CInput.h"
#include "CViewRender.h"

#include <d3d11.h>

namespace SDK {
	// interfaces
	inline CClientState* m_clientState;
	inline CEntityList* m_cl_entity_list;
	inline CHLClient* m_chlClient;
	inline CEngineClient* m_engineClient;
	inline void* m_engineTrace;
	inline CInput* m_input;
	inline void* m_gameMovement;
	inline CGlobalVars* m_globalVars;
	inline CViewRender* m_viewRender;
	inline CEntity** m_localPlayerPtr;
	inline char* m_levelName;

	// globals
	inline VMatrix* m_viewMatrixPtr;

	// setup once during the entire lifetime of the program
	bool Setup();

	// setup once in the beginning of a game
	bool Init();

	// setup once we enter a game for the first time
	bool Update();
	inline bool m_init = false;
	inline bool m_updated = false;

	// utilities relative to the sdk
	constexpr float HammerUnitToMeters(const float hammerUnits) {
		return hammerUnits * 0.01905f;
	}

	constexpr float MetersToHammerUnit(const float meters) {
		return meters * 52.49344f;
	}
}
