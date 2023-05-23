// DukeHud.UC
//

class DukeHUD extends HUD
	native;

// Crosshair.
var int CrosshairCount;
var texture CrosshairTextures[20];

native function HudStartup();
native function RenderHud();

cpptext
{
	void DrawCrosshair();
}

simulated function PostBeginPlay()
{
	super.PostBeginPlay();

	HudStartup();
}

simulated event PostRender()
{
	super.PostRender();

	RenderHud();
}

defaultproperties
{
	CrosshairCount=9
    CrosshairTextures(0)=Texture'hud_effects.crosshair1BC'
    CrosshairTextures(1)=Texture'hud_effects.crosshair2BC'
    CrosshairTextures(2)=Texture'hud_effects.crosshair3BC'
    CrosshairTextures(3)=Texture'hud_effects.crosshair4BC'
    CrosshairTextures(4)=Texture'hud_effects.crosshair5BC'
    CrosshairTextures(5)=Texture'hud_effects.crosshair6BC'
    CrosshairTextures(6)=Texture'hud_effects.crosshair7BC'
    CrosshairTextures(7)=Texture'hud_effects.crosshair8BC'
    CrosshairTextures(8)=Texture'hud_effects.crosshair9BC'
    CrosshairTextures(9)=Texture'hud_effects.crosshair10BC'
    CrosshairTextures(10)=Texture'hud_effects.crosshair11BC'
    CrosshairTextures(11)=Texture'hud_effects.crosshair12BC'
    CrosshairTextures(12)=Texture'hud_effects.crosshair13BC'
    CrosshairTextures(13)=Texture'hud_effects.crosshair14BC'
}