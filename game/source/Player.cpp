#include "stdafx.h"
#include "player.h"
#include "Map/Map.h"




Player::Player(Map& map) : pathFinder(*this, map)
{
 
	//JUST FOR TESTING
	playerSprite = new CSprite;
	playerSprite->AddImage("playerSprite.png", "WalkRight", 5, 4, 0, 0, 4, 0, CColor::Black());
	playerSprite->AddImage("playerSprite.png", "WalkLeft", 5, 4, 0, 1, 4, 1, CColor::Black());
	playerSprite->AddImage("playerSprite.png", "WalkUp", 5, 4, 0, 3, 4, 3, CColor::Black());
	playerSprite->AddImage("playerSprite.png", "WalkDown", 5, 4, 0, 1, 4, 1, CColor::Black());

	playerSprite->SetAnimation("WalkRight", 8);
	playerSprite->SetPosition(350, 250);
	playerSprite->SetSpeed(0);
	playerSprite->SetDirection(90);
	playerSprite->SetStatus(WALK_RIGHT);
	playerSprite->SetSpeed(0);



}

Player::~Player()
{
}

void Player::Draw(CGraphics* g)
{
}

void Player::Update(float time)
{
	Animation();
	MoveToWaypoint(time);
}

void Player::MoveToWaypoint(float t)
{
	if (!pathFinder.m_waypoints.empty()) {

		pathFinder.PathSmoothing();
		CVector destinationToFisrtWP = pathFinder.m_waypoints.front() -  playerSprite->GetPosition();
		// Start moving toward the first waypoint if player isn't moving
		if (playerSprite->GetSpeed() < 1)
		{
			 playerSprite->SetSpeed(100);
			//player.playerSprite->SetAnimation("walk");

			playerSprite->SetDirection(destinationToFisrtWP);
			playerSprite->SetRotation(playerSprite->GetDirection() - 90);
		}

		// Stop on the arriving to dest
		if (Dot(playerSprite->GetVelocity(), destinationToFisrtWP) < 0)
		{
			//removes first so next becomes first
			pathFinder.m_waypoints.erase(pathFinder.m_waypoints.begin()); // Remove the reached waypoint
			playerSprite->SetVelocity(0, 0);
			playerSprite->SetRotation(0);

		}


	}

	if (pathFinder.m_waypoints.empty())
		 playerSprite->SetVelocity(0, 0);



	 playerSprite->Update(t);
}

void Player::Animation()
{
	int currentState;
	if (playerSprite->GetSpeed() > 0)
	{
		currentState = WALK_RIGHT;
	}
	else 
		currentState = WALK_LEFT;


	if (currentState == playerSprite->GetStatus())
		return;

	if (playerSprite->GetStatus() == IDLE) 
	{
		playerSprite->SetAnimation("WalkRight", 12);
	}
	else if (playerSprite->GetStatus() == WALK_LEFT) {
		playerSprite->SetAnimation("WalkLeft", 12);
	}
	else if (playerSprite->GetStatus() == WALK_RIGHT) {
		playerSprite->SetAnimation("WalkRight", 12);
	}
	else if (playerSprite->GetStatus() == WALK_UP) {
		playerSprite->SetAnimation("WalkUp", 12);
	}
	else if (playerSprite->GetStatus() == WALK_DOWN) {
		playerSprite->SetAnimation("WalkDown", 12);
	}

}

 
 
void Player::OnLButtonDown(Uint16 x, Uint16 y)
{
	pathFinder.Move(x,y);
}