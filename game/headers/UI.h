#pragma once
class UI
{
public:
	UI();
	~UI();
	//update Bars
	void SetHpBar(float remainingHpPerc);
	void SetMpBar(float remainingHpPerc);
	void DrawUI(CGraphics* g);
private:

private:
	CSprite underLayerSprite;
	CSprite actionBarSprite;
	CSprite hpBarSprite;
	CSprite mpBarSprite;
	CSprite endTurnBtn;
};

 