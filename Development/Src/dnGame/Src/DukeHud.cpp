// DukeHud.cpp
//


#include "dnGame.h"

IMPLEMENT_CLASS(ADukeHUD)

void ADukeHUD::HudStartup() 
{

}

void ADukeHUD::DrawCrosshair()
{
	float XScale;
	float XLength;
	UTexture *T;

	T = CrosshairTextures[0];

	XScale = ::Max( 1, int(0.1 + Canvas->ClipX/640.0) );
	XLength = XScale * T->GetSurfaceWidth();

	Canvas->SetPos(0.5 * (Canvas->ClipX - XLength), 0.5 * (Canvas->ClipY - XLength));

	// UTexture* Tex, FLOAT X, FLOAT Y, FLOAT Z, FLOAT XL, FLOAT YL, FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, const FLinearColor& Color,EBlendMode BlendMode=BLEND_Translucent
	Canvas->DrawTile( T, 0.5 * (Canvas->ClipX - XLength), 0.5 * (Canvas->ClipY - XLength), 1, T->GetSurfaceWidth(), T->GetSurfaceHeight(), 0, 0, 32, 32, FColor(255,255,255), BLEND_Additive );
}

void ADukeHUD::RenderHud()
{	
	// Draw crosshair.
	Canvas->DrawColor = WhiteColor;
	DrawCrosshair();
}