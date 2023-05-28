// AIPawn.cpp
//

#include "dnGame.h"

IMPLEMENT_CLASS(UAnimNotify_WeaponState)

void UAnimNotify_WeaponState::Notify(class UAnimNodeSequence* NodeSeq)
{

}

FString UAnimNotify_WeaponState::GetEditorComment() {
	switch (weaponState) {
		case DUKE_WEAPONSTATE_IDLE:
			return TEXT("Switch to Idle");

		case DUKE_WEAPONSTATE_FIRE:
			return TEXT("Switch to Fire State");
	}

	return TEXT("Unknown State");
} 