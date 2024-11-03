#pragma once

class Dialogbox
{
public:
	Dialogbox();
	~Dialogbox();
	void Update(float gametime);
	void Draw(CGraphics* g);
	void ShowDialogBox(CSprite& entity);
	CSprite dialogboxSprite;
	float dialogBoxTimer;
	bool isDialogBoxOpen;

private:

};