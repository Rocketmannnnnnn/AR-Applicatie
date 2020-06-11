#include <iostream>
#include "GameLogic.h"
using namespace std;

GameLogic::GameLogic()
{
}

GameLogic::GameLogic(GraphicMain* graphicMain)
{
	gamestate = GameState::STATE_NOT_STARTED;
	gm = graphicMain;
}

GameLogic::~GameLogic()
{
}

void GameLogic::GameLogic_Init() {
	Boat boat0 = Boat(3, { {8,7},{8,8},{8,9} });
	Boat boat1 = Boat(3, { {0,0},{0,1},{0,2} });
	Boat boat2 = Boat(4, { {5,4},{5,5},{5,6},{5,7} });
	Boat boat3 = Boat(5, { {9,0},{9,1},{9,2},{9,3} });
	
	bordSpeler.addBoat(boat0);
	bordSpeler.addBoat(boat1);
	bordSpeler.addBoat(boat2);
	bordSpeler.addBoat(boat3);

	/*bordAI.addBoat(boat0);
	bordAI.addBoat(boat1);
	bordAI.addBoat(boat2);
	bordAI.addBoat(boat3);*/
}

Bord* GameLogic::getBordSpeler() {
    return &bordSpeler;
}

Bord* GameLogic::getBordAI() {
    return &bordAI;
}

void GameLogic::printBords() {
    cout << "Speler bord:" << endl;
    bordSpeler.printBord();
    cout << "AI bord:" << endl;
    bordAI.printBord();
}

void GameLogic::initBordAI() {
	vector<int> boats = { 5,4,3,3,2 };
	Boat tempBoat = Boat(1, { 0,0 });
	int tempBoatLength = 0;
	int x, y;
	while (!boats.empty()) {
		tempBoatLength = boats.back();
		boats.pop_back();
		while (1) {
			x = rand() % 10;
			y = rand() % 10;

			tempBoat = Boat(tempBoatLength, { x,y });
			if (!bordSpeler.checkIfBoatOverlap(tempBoat) && bordSpeler.checkIfBoatIsInBounds(tempBoat)) {
				bordSpeler.addBoat(tempBoat);
			}
		}
	}
}

void GameLogic::update(float elapsedTime) {
	
};