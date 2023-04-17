#include "../include.h"
#include "../sdk/sdk.h"
#include "../deps/imgui/imgui.h"

import memory;
import render;
import util;
import visuals;
import mizu;

void Visuals::Run()
{
	Players();
}

void Visuals::Players() {
	ImDrawList* draw = ImGui::GetBackgroundDrawList();
	if (!draw)
		return;

	for (int i = 1; i < NUM_ENT_ENTRIES; i++) {
		CEntInfo& info = SDK::m_cl_entity_list->m_entInfos[i];
		if (!info.m_entity)
			continue;

		CEntity* entity = info.m_entity;
		if (!entity || entity == Mizu::m_localPlayer)
			continue;

		const char* signifier = entity->GetSignifier();
		if (!signifier)
			continue;

		bool isPlayer = strstr(signifier, _("player")) == 0;
		bool isNPC = strstr(signifier, _("npc_dummie")) == 0;
		if (!isPlayer && !isNPC)
			continue;

		bool playerChecks = isPlayer && entity->GetHealth() > 0;
		bool npcChecks = isNPC && entity->GetHealth() > 0;
		if (!playerChecks && !npcChecks)
			continue;

		const Vector_t& origin = entity->GetOrigin();
		const CollisionProperty_t& collision = entity->GetCollision();

		Point_t screenOrigin, screenMins, screenMaxs;
		if (!Render::WorldToScreen(origin, screenOrigin) || !Render::WorldToScreen(origin + collision.m_mins, screenMins) || !Render::WorldToScreen(origin + collision.m_maxs, screenMaxs))
			continue;

		Point_t bboxSize;
		bboxSize.y = std::abs(screenMins.y - screenMaxs.y);
		bboxSize.x = (int)(bboxSize.y * 0.5f);
		Point_t bboxPos = { screenOrigin.x - bboxSize.x / 2, screenMaxs.y };

		if (Config::box) {
			draw->AddRectFilled(bboxPos, bboxPos + bboxSize, IM_COL32(0, 0, 0, 60));
			draw->AddRect(bboxPos - 1, bboxPos + bboxSize + 1, IM_COL32(0, 0, 0, 255));
			draw->AddRect(bboxPos, bboxPos + bboxSize, IM_COL32(255, 255, 255, 255));
			draw->AddRect(bboxPos + 1, bboxPos + bboxSize - 1, IM_COL32(0, 0, 0, 255));
		}
	}
}