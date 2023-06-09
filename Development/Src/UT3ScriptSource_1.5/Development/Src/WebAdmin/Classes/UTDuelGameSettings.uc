﻿/**
 * Settings class for the duel gametype.
 *
 * Copyright 2008 Epic Games, Inc. All Rights Reserved
 *
 * @author  Michiel 'elmuerte' Hendriks
 */
class UTDuelGameSettings extends UTTeamGameSettings;

`include(WebAdmin.uci)

var class<UTDuelGame> UTDuelGameClass;

function init()
{
	super.init();
	SetIntPropertyByName('NumRounds', UTDuelGameClass.default.NumRounds);
}

protected function saveInternal()
{
	GetIntPropertyByName('NumRounds', UTDuelGameClass.default.NumRounds);
	super.saveInternal();
}

defaultproperties
{
	UTGameClass=class'UTDuelGame'
	UTTeamGameClass=class'UTDuelGame'
	UTDuelGameClass=class'UTDuelGame'

	Properties[14]=(PropertyId=14,Data=(Type=SDT_Int32))
	PropertyMappings[14]=(Id=14,Name="NumRounds" `modloc(,ColumnHeaderText="Rounds"),MappingType=PVMT_Ranged,MinVal=1,MaxVal=999,RangeIncrement=1)
}
