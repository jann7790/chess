﻿#pragma once
#include "Player.h"
#include <fstream>
#include "Viewer.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class GameManager
{
public:
	GameManager();
	int run();
	bool isGameOver();
	void ProcessInput();
	
	Position start;
	Position end;
private:
	int check;
	Player players[2];
	int current_player;
	Board board;
	Viewer viewer;
	


};

void GameManager::ProcessInput()
{
	sf::Event event;
	Position p;
	while (viewer.window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			viewer.window.close();
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			p.y = event.mouseButton.x / 112.5f;
			p.x = event.mouseButton.y / 112.5f;
			if (!check)
			{
				
				start = p;
				board.print(start);
				viewer.movePicture(board, start, players[current_player]);
			}
			else
			{
				end = p;
				if (players[current_player].OnMove(board, start, end))
				{
					current_player ^= 1;
				}
				viewer.movePicture(board);
			}
			cout<< p.x << " " << p.y << endl;
			check = check ^ 1;

		}
		if (players[current_player].isThreatened(board, players[current_player].findKing(board)))
		{
			cout << "checkcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheck\n";
		}
	}
	
}


int GameManager::run()
{
		
	bool check = 0;
	while (viewer.window.isOpen()) {

		ProcessInput();
		viewer.Display();
	}
	return 0;
}

GameManager::GameManager()
{
	check = 0;
	board = Board();
	//viewer = Viewer();
	players[0] = Player(0, board);
	players[1] = Player(1, board);
	current_player = 0;
	start.x = 0;
	start.y = 0;
	end.x = 0;
	end.y = 0;

	
}




bool GameManager::isGameOver()
{
	Board temp = board;
	for (int i = 0; i < 2; i++)
	{
		if (!players[i].isThreatened(board, players[i].findKing(board)))
			break;
		for (int j = 0; j < BOARDLEN; j++)
		{
			for (int k = 0; k < BOARDLEN; k++)
			{
				if (board.board[j][k].camp == players[i].camp)
				{
					for (auto element : board.board[j][k].availablemove)
					{
						if (players[current_player].OnMove(temp, temp.board[j][k]._position, element))
						{
							if (!players[i].isThreatened(temp, players[i].findKing(board)))
								return 0;
							temp = board;
						}
					}
				}
			}
		}
	}
	return 1;

}
 