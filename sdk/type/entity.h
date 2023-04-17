#pragma once

#include "../../memory/virtual.h"

#include "angle.h"
#include "CHighlight.h"
#include "ClientClass.h"
#include "color.h"
#include "collideable.h"
#include "matrix.h"
#include "netvars.h"
#include "studio.h"
#include "vector.h"

#include "../CEntityList.h"

import memory;

struct IClientRenderable {
	VCALL(bool, SetupBones, 16, (Matrix3x4_t* matrix, uint32_t maxBones, uint32_t mask, float time), (this, matrix, maxBones, mask, time))
};

struct IClientNetworkable {
	VCALL(void, Release, 1, (), (this));
	VCALL(ClientClass_t*, GetClientClass, 3, (), (this));
};

struct IClientUnknown {
};

struct CEntity {
	VCALL(void*, GetPredDescMap, 14, (), (this));

	EHandle GetHandle() {
		return *(EHandle*)((uintptr_t)this + 0x8);
	}

	IClientRenderable* GetRenderable() {
		return (IClientRenderable*)((uintptr_t)this + 0x10);
	}

	IClientNetworkable* GetNetworkable() {
		return (IClientNetworkable*)((uintptr_t)this + 0x18);
	}

	const char* GetModelName() {
		return *(const char**)((uintptr_t)this + 0x30);
	}

	int GetIndex() {
		return *(int*)((uintptr_t)this + 0x38);
	}

	Vector_t GetOrigin() {
		return *(Vector_t*)((uintptr_t)this + 0x14c);
	}

	float GetLastVisibleTime() {
		return *(float*)((uintptr_t)this + 0x1a78);
	}

	CStudioHdr* GetModelPtr();

	// netvars
#pragma region DT_BaseEntity
	NETVAR(int, GetTeam, "DT_BaseEntity", "m_iTeamNum");
	NETVAR(int, GetModelIndex, "DT_BaseEntity", "m_nModelIndex");
	NETVAR(int, GetEffects, "DT_BaseEntity", "m_fEffects");
	NETVAR(int, GetRenderMode, "DT_BaseEntity", "m_nRenderMode");
	NETVAR(int, GetRenderFX, "DT_BaseEntity", "m_nRenderFX");
	NETVAR(const char*, GetSignifier, "DT_BaseEntity", "m_iSignifierName");
	NETVAR(int, GetScriptNameIndex, "DT_BaseEntity", "m_scriptNameIndex");
	NETVAR(int, GetInstanceNameIndex, "DT_BaseEntity", "m_instanceNameIndex");
	NETVAR(int, GetShieldHealth, "DT_BaseEntity", "m_shieldHealth");
	NETVAR(int, GetShieldHealthMax, "DT_BaseEntity", "m_shieldHealthMax");
	NETVAR(CollisionProperty_t, GetCollision, "DT_BaseEntity", "m_Collision");
#pragma endregion

	NETVAR(HighlightSettings_t, GetHighlightSettings, "DT_HighlightSettings", "m_highlightParams");

#pragma region DT_BaseAnimating
	NETVAR(int, GetSkin, "DT_BaseAnimating", "m_nSkin");
	NETVAR(int, GetSkinMod, "DT_BaseAnimating", "m_skinMod");
	NETVAR(int, GetBody, "DT_BaseAnimating", "m_nBody");
	NETVAR(int, GetCamoIndex, "DT_BaseAnimating", "m_camoIndex");
	NETVAR(float, GetModelScale, "DT_BaseAnimating", "m_flModelScale");
	NETVAR_OFFSET(Matrix3x4_t*, GetBoneMatrix, "DT_BaseAnimating", "m_nForceBone", 0x48);
#pragma endregion

#pragma region DT_BaseCombatCharacter
	NETVAR(EHandle, GetSelectedWeapons, "DT_BaseCombatCharacter", "m_selectedWeapons"); // 2 weapons here
	NETVAR(EHandle, GetLatestPrimaryWeapon, "DT_BaseCombatCharacter", "m_latestPrimaryWeapons"); // active weapon here (m_selectedWeapons+0x4)
	NETVAR(EHandle, GetLatestPrimaryWeaponIndexZeroOrOne, "DT_BaseCombatCharacter", "m_latestPrimaryWeaponsIndexZeroOrOne"); // 2 weapons here (m_latestPrimaryWeapons+0x8)
	NETVAR(float, GetTimeBase, "DT_BaseCombatCharacter", "m_currentFramePlayer.timeBase"); // 0x2100
	NETVAR(Angle_t, GetWeaponPunch, "DT_BaseCombatCharacter", "m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle");
	NETVAR(float, GetCurrentTraversalAnimProgress, "DT_BaseCombatCharacter", "m_currentFrameLocalPlayer.m_traversalAnimProgress");
	NETVAR(int, GetDuckTransitionRemainderMsec, "DT_BaseCombatCharacter", "m_currentFrameLocalPlayer.m_duckTransitionRemainderMsec");
	NETVAR_OFFSET(float, GetNetworkYaw, "DT_BaseCombatCharacter", "m_currentFramePlayer.m_ammoPoolCount", -0x8);
#pragma endregion

#pragma region DT_Player
	NETVAR(int, GetFlags, "DT_Player", "m_fFlags");
	NETVAR(int, GetHealth, "DT_Player", "m_iHealth");
	NETVAR(int, GetLifeState, "DT_Player", "m_lifeState");
	NETVAR(int, GetBleedOutState, "DT_Player", "m_bleedoutState");
	NETVAR_PTR(EHandle, GetWeaponHandles, "DT_Player", "weapons");
	NETVAR_PTR(EHandle, GetOffhandWeaponHandles, "DT_Player", "offhandWeapons");
	NETVAR(bool, IsZooming, "DT_Player", "m_bZooming");
	NETVAR(int, GetArmorType, "DT_Player", "m_armorType");
	NETVAR(int, GetHelmetType, "DT_Player", "m_helmetType");
	NETVAR(float, GetSkydiveSpeed, "DT_Player", "m_skydiveSpeed");
	NETVAR(int, GetSkydiveState, "DT_Player", "m_skydiveState");
	NETVAR(int, GetTraversalState, "DT_Player", "m_traversalState");
	NETVAR(int, GetTraversalType, "DT_Player", "m_traversalType");
	NETVAR(float, GetTraversalAnimProgress, "DT_Player", "m_traversalAnimProgress");
	NETVAR_PTR(uint32_t, GetAmmoPoolCountTable, "DT_Player", "m_ammoPoolCount");
	NETVAR(EHandle, GetGroundEntityHanlde, "DT_Player", "m_hGroundEntity");
	NETVAR(float, GetTimeLastTouchedGround, "DT_Player", "m_flTimeLastTouchedGround");
	NETVAR(EHandle, GetGlobalScriptNetData, "DT_Player", "m_playerScriptNetDataGlobal");
	NETVAR_PTR(EHandle, GetViewmodelHandles, "DT_Player", "m_hViewModels");

	NETVAR_OFFSET(Angle_t, GetViewAngles, "DT_Player", "m_ammoPoolCapacity", -0x14);
	NETVAR_OFFSET(Angle_t, GetSwayAngles, "DT_Player", "m_ammoPoolCapacity", -0x24);
	NETVAR_OFFSET(EHandle, GetCurrentWeaponHandle, "DT_Player", "activeWeapons", -0xC);

	NETVAR(void*, GetConsumableInventory, "DT_Player", "m_consumableInventory"); // size: 0x40, sizeofelem = 0x4, count = 0x10
	NETVAR(int, GetLastUCmdSimulationTicks, "DT_Player", "m_lastUCmdSimulationTicks");
	NETVAR(float, GetLastUCmdSimulationRemainderTime, "DT_Player", "m_lastUCmdSimulationRemainderTime");
	NETVAR(float, GetLastKillTime, "DT_Player", "m_lastKillTime");
	NETVAR(float, GetLaggedMovementValue, "DT_Player", "m_flLaggedMovementValue"); // 0x3aec
	NETVAR(float, GetLastMoveInputTime, "DT_Player", "m_lastMoveInputTime"); // 0x3af0

	NETVAR(Vector_t, GetTraversalBegin, "DT_Player", "m_traversalBegin"); // 0x2b04
	NETVAR(Vector_t, GetTraversalMid, "DT_Player", "m_traversalMid"); // 0x2b10
	NETVAR(Vector_t, GetTraversalEnd, "DT_Player", "m_traversalEnd"); // 0x2b1c
	NETVAR(float, GetTraversalMidFrac, "DT_Player", "m_traversalMidFrac"); // 0x2b28
	NETVAR(Vector_t, GetTraversalForwardDir, "DT_Player", "m_traversalForwardDir"); // 0x2b2c
	NETVAR(float, GetTraversalStartTime, "DT_Player", "m_traversalStartTime"); // 0x2b48
	NETVAR(float, GetTraversalHandAppearTime, "DT_Player", "m_traversalHandAppearTime"); // 0x2b4c
	NETVAR(float, GetTraversalProgress, "DT_Player", "m_traversalProgress"); // 0x2b44
	NETVAR(float, GetTraversalReleaseTime, "DT_Player", "m_traversalReleaseTime"); // 0x2b50
	NETVAR(float, GetTraversalBlendOutStartTime, "DT_Player", "m_traversalBlendOutStartTime"); // 0x2b54
	NETVAR(Vector_t, GetTraversalBlendOutStartOffset, "DT_Player", "m_traversalBlendOutStartOffset"); // 0x2b58
	NETVAR(float, GetWallDangleJumpOffTime, "DT_Player", "m_wallDangleJumpOffTime"); // 0x2b70
	NETVAR(int, GetWallDangleMayHangHere, "DT_Player", "m_wallDangleMayHangHere"); // 0x2b74
	NETVAR(int, GetWallDangleForceFallOff, "DT_Player", "m_wallDangleForceFallOff"); // 0x2b75
	NETVAR(int, GetWallDangleLastPushedForward, "DT_Player", "m_wallDangleLastPushedForward"); // 0x2b76
	NETVAR(int, GetWallDangleDisableWeapon, "DT_Player", "m_wallDangleDisableWeapon"); // 0x2b78
	NETVAR(int, GetGravityLiftActive, "DT_Player", "m_gravityLiftActive"); // 0x2b82
	NETVAR(float, GetGravityLiftEnterTime, "DT_Player", "m_gravityLiftEnterTime"); // 0x2b84
	NETVAR(float, GetGravityLiftEjectTime, "DT_Player", "m_gravityLiftEjectTime"); // 0x2b88
	NETVAR(float, GetGravityLiftHoverTime, "DT_Player", "m_gravityLiftHoverTime"); // 0x2b8c
	NETVAR(int, GetBlackholeActive, "DT_Player", "m_blackholeActive"); // 0x2ba8
	NETVAR(int, GetJetDriveWasActive, "DT_Player", "m_jetDriveWasActive"); // 0x2ba9
	NETVAR(int, GetJetDriveActive, "DT_Player", "m_jetDriveActive"); // 0x2baa
	NETVAR(Vector_t, GetJetDriveTargetPos, "DT_Player", "m_jetDriveTargetPos"); // 0x2bac
	NETVAR(int, GetJetDriveTargetEnt, "DT_Player", "m_jetDriveTargetEnt"); // 0x2bb8
	NETVAR(Vector_t, GetJetDriveTargetEntOffset, "DT_Player", "m_jetDriveTargetEntOffset"); // 0x2bbc
	NETVAR(Vector_t, GetJetDriveStartPos, "DT_Player", "m_jetDriveStartPos"); // 0x2bc8
	NETVAR(float, GetJetDriveStartTime, "DT_Player", "m_jetDriveStartTime"); // 0x2bd4
	NETVAR(float, GetJetDriveSpeed, "DT_Player", "m_jetDriveSpeed"); // 0x2bd8
	NETVAR(float, GetJetDriveAccel, "DT_Player", "m_jetDriveAccel"); // 0x2bdc
	NETVAR(float, GetJetDriveDecelWindowTimeOutTime, "DT_Player", "m_jetDriveDecelWindowTimeOutTime"); // 0x2be0
	NETVAR(int, GetJetDriveInDecelWindow, "DT_Player", "m_jetDriveInDecelWindow"); // 0x2be4
	NETVAR(float, GetJetDriveTimeout, "DT_Player", "m_jetDriveTimeout"); // 0x2be8
	NETVAR(Vector_t, GetJetDriveDoubleJumpVelocity, "DT_Player", "m_jetDriveDoubleJumpVelocity"); // 0x2bec
	NETVAR(bool, IsGliding, "DT_Player", "m_gliding"); //
	NETVAR(bool, IsDodging, "DT_Player", "m_dodging"); //
	NETVAR(bool, IsSliding, "DT_Player", "m_sliding"); //
	NETVAR(int, GetDuckState, "DT_Player", "m_duckState"); //
	NETVAR(EHandle, GetLocalScriptNetData, "DT_Player", "m_playerScriptNetDataExclusive");
	NETVAR(float, GetZoomBaseFrac, "DT_Player", "m_zoomBaseFrac");
	NETVAR(float, GetFriction, "DT_Player", "m_flFriction"); // 0x4a0
	NETVAR(Vector_t, GetVecVelocity, "DT_Player", "m_vecVelocity.x"); // 0x488
#pragma endregion
};

struct CWeaponX : CEntity {
#pragma region DT_WeaponX_LocalWeaponData
	NETVAR(float, GetLastPrimaryAttackTime, "DT_WeaponX_LocalWeaponData", "m_lastPrimaryAttackTime");
	NETVAR(float, GetNextReadyTime, "DT_WeaponX_LocalWeaponData", "m_nextReadyTime");
	NETVAR(float, GetNextPrimaryAttackTime, "DT_WeaponX_LocalWeaponData", "m_nextPrimaryAttackTime");
	NETVAR(float, GetAttackTimeThisFrame, "DT_WeaponX_LocalWeaponData", "m_attackTimeThisFrame");
	NETVAR(int, GetAmmoInClip, "DT_WeaponX_LocalWeaponData", "m_ammoInClip");
	NETVAR(int, GetAmmoInStockpile, "DT_WeaponX_LocalWeaponData", "m_ammoInStockpile");
	NETVAR(bool, IsInReload, "DT_WeaponX_LocalWeaponData", "m_bInReload");
	NETVAR(float, GetTimeWeaponIdle, "DT_WeaponX_LocalWeaponData", "m_flTimeWeaponIdle");
#pragma endregion

#pragma region DT_WeaponX
	NETVAR(int, GetWorldModelIndex, "DT_WeaponX", "m_iWorldModelIndex");
	NETVAR(int, GetWorldModelIndexOverride, "DT_WeaponX", "m_worldModelIndexOverride");
	NETVAR(int, GetHolsterModelIndex, "DT_WeaponX", "m_holsterModelIndex");
	NETVAR(int, GetDroppedModelIndex, "DT_WeaponX", "m_droppedModelIndex");
	NETVAR(int, GetWeaponNameIndex, "DT_WeaponX", "m_weaponNameIndex");
	NETVAR(EHandle, GetWeaponOwner, "DT_WeaponX", "m_weaponOwner");
	NETVAR(int, GetModBitfieldCurrent, "DT_WeaponX", "m_modBitfieldCurrent");
	NETVAR(float, GetMoveSpread, "DT_WeaponX", "m_moveSpread"); // 0x16c0
	NETVAR(float, GetSpreadStartTime, "DT_WeaponX", "m_spreadStartTime"); // 0x16c4
	NETVAR(float, GetSpreadStartFracHip, "DT_WeaponX", "m_spreadStartFracHip"); // 0x16c8
	NETVAR(float, GetSpreadStartFracADS, "DT_WeaponX", "m_spreadStartFracADS"); // 0x16cc
	NETVAR(float, GetKickSpreadHipfire, "DT_WeaponX", "m_kickSpreadHipfire"); // 0x16d0
	NETVAR(float, GetKickSpreadADS, "DT_WeaponX", "m_kickSpreadADS"); // 0x16d4
	NETVAR(float, GetTargetZoomFOV, "DT_WeaponX", "m_targetZoomFOV"); // 0x1770
	NETVAR(float, GetCurZoomFOV, "DT_WeaponX", "m_curZoomFOV"); // 0x1774
	NETVAR(int, GetTossRelease, "DT_WeaponX", "m_tossRelease"); // 0x168c
	NETVAR(EHandle, GetLastTossedGrenade, "DT_WeaponX", "m_lastTossedGrenade"); //
	NETVAR(int, NeedsReloadCheck, "DT_WeaponX", "m_needsReloadCheck"); // 0x17ad
	NETVAR(int, NeedsEmptyCycleCheck, "DT_WeaponX", "m_needsEmptyCycleCheck"); // 0x17ae
#pragma endregion
};