class AnimNotify_WeaponState extends AnimNotify
	native;

enum EWeaponState
{
	DUKE_WEAPONSTATE_IDLE,
	DUKE_WEAPONSTATE_FIRE
};

var() EWeaponState weaponState; 

cpptext
{
	// AnimNotify interface.
	virtual void Notify( class UAnimNodeSequence* NodeSeq );
	virtual FString GetEditorComment();
}

defaultproperties
{
	 weaponState=DUKE_WEAPONSTATE_IDLE
}
