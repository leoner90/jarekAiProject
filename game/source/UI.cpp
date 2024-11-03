#include "stdafx.h"
#include "UI.h"

UI::UI()
{
	actionBarSprite.LoadImage("actionBar.png");
	actionBarSprite.SetImage("actionBar.png");
	actionBarSprite.SetSize(1024, 160);
	actionBarSprite.SetPosition(512, 80);


	//hpBar 130/65 origin
	hpBarSprite.LoadImage("hpBar.png");
	hpBarSprite.SetImage("hpBar.png");
	hpBarSprite.SetSize(160, 80);
	hpBarSprite.SetPosition(80, 40);

	//mpBar
	mpBarSprite.LoadImage("mpBar.png");
	mpBarSprite.SetImage("mpBar.png");
	mpBarSprite.SetSize(160, 80);
	mpBarSprite.SetPosition(950, 40);

	//under  Layer
	underLayerSprite.LoadImage("underLayer.png");
	underLayerSprite.SetImage("underLayer.png");
	underLayerSprite.SetSize(1024, 120);
	underLayerSprite.SetPosition(512, 60);
}


UI::~UI()
{
}

void UI::SetHpBar(float remainingHpPerc)
{
	float currentSize = 80.f * remainingHpPerc;
	hpBarSprite.SetSize(160, currentSize);
	hpBarSprite.SetPos(80, currentSize / 2);
}

void UI::SetMpBar(float remainingMpPerc)
{
	float currentSize = 80.f * remainingMpPerc;
	mpBarSprite.SetSize(160, currentSize);
	mpBarSprite.SetPos(950, currentSize / 2);
}

void UI::DrawUI(CGraphics* g)
{
	underLayerSprite.Draw(g);
	hpBarSprite.Draw(g);
	mpBarSprite.Draw(g);
	actionBarSprite.Draw(g);
	endTurnBtn.Draw(g);
}
