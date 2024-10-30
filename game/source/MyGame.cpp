#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) : mainMap(), player(mainMap)
{
	
}

CMyGame::~CMyGame(void)
{
}

/*********** UPDATE ***********/
void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();
	player.Update(t);

}

/***********  DRAW ***********/
void CMyGame::OnDraw(CGraphics* g)
{
	//pos += CVector(g->GetScrollPos());
	mainMap.Draw(g, player.playerSprite->GetPosition());
	player.playerSprite->Draw(g);
//	for (auto obj : testNodes) obj->Draw(g);

	//if(!m_waypoints.empty())
	//	g->DrawLine(CVector(player.playerSprite->GetPos() + CVector(-0, -50)), m_waypoints[0], 4, CColor::Red());
 
	
}


/***********  INIT ***********/
void CMyGame::OnInitialize()
{
}

/***********  TO CLEAN ***********/
void CMyGame::OnDisplayMenu()
{
	StartGame();
}

void CMyGame::OnStartGame()
{
}

void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

void CMyGame::OnGameOver()
{
}

void CMyGame::OnTerminate()
{
}

/***********  KEYBOARD EVENTS ***********/

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)

	{
		player.playerSprite->SetVelocity(1,1);
		player.playerSprite->SetSpeed(120);
	}
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}



/***********  MOUSE EVENTS ***********/

void CMyGame::OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight, bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x, Uint16 y)
{
	player.OnLButtonDown(x, y);
}

void CMyGame::OnLButtonUp(Uint16 x, Uint16 y)
{
}


void CMyGame::OnRButtonDown(Uint16 x, Uint16 y)
{
 
	
}

void CMyGame::OnRButtonUp(Uint16 x, Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x, Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x, Uint16 y)
{
}