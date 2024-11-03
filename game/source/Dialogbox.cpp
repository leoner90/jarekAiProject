#include "stdafx.h"
#include "DialogBox.h"

Dialogbox::Dialogbox()
{
	dialogBoxTimer = 0;
	isDialogBoxOpen = false;
	dialogboxSprite.LoadImage("dialogboxSprite.png");
	dialogboxSprite.SetImage("dialogboxSprite.png");
	dialogboxSprite.SetSize(150, 80);

	//dialogboxSprite.SetPosition(512, 80);
	
}

Dialogbox::~Dialogbox()
{
}

void Dialogbox::Update(float gametime)
{
}

void Dialogbox::Draw(CGraphics* g)
{
}

void Dialogbox::ShowDialogBox(CSprite& entity)
{

}
