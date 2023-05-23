﻿/**
 * Copyright 1998-2008 Epic Games, Inc. All Rights Reserved.
 */
class SeqAct_SetBlockRigidBody extends SequenceAction
	native(Sequence);

defaultproperties
{
	ObjName="Set BlockRigidBody"
	ObjCategory="Physics"

	InputLinks(0)=(LinkDesc="Turn On")
	InputLinks(1)=(LinkDesc="Turn Off")
}
