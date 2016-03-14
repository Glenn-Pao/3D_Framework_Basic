#pragma once

//sound engine
#include <irrKlang.h>
#include <iostream>
#include <vector>

#pragma comment (lib, "irrKlang.lib")
using namespace irrklang; 

class CSound
{
	enum SOUND_TYPE
	{
		LOBBY,
		MAIN_MENU,
		MAZE,
		PUZZLE,
		MCQ,
		STRESS,
		NUM_SOUND
	};
public:
	CSound();
	~CSound();

	void Init();
	void UpdateSound(double &dt);

	void Exit();

	void PlayMainMenu();				//plays the main menu
	void StopMainMenu();				//stop the main menu

	void PlayMazeEscaper();			//plays the maze escaper
	void StopMazeEscaper();			//stop the maze escaper

	void PlayPuzzleParty();			//plays the puzzle party
	void StopPuzzleParty();			//stop the puzzle party

	void PlayMCQPower();			//plays the mcq power
	void StopMCQPower();			//stop the mcq power

	void PlayStress();					//plays the stress
	void StopStress();					//stop the stress

	void PlayLobby();					//plays the game hub lobby sound
	void StopLobby();					//stop the game hub lobby sound

	void AdjustVol();						//adjust the volume in options

	void setSoundType(int);
	int getSoundType(void);

	void PlaySong();

	void setActive(bool);
	bool getActive(void);

private:
	//Handles to play different sounds
	ISoundEngine *TheSound;	//main sound system

	ISound *MainMenu;		//background music for main menu
	ISound *MazeEscaper;	//background music for maze, game 1 by Gregory
	ISound *PuzzleParty;	//background music for puzzle party, game 2 by Job
	ISound *MCQPower;	//background music for MCQ, game 3 by Glenn
	ISound *Stress;	//background music for Stress, game by Rayson
	ISound *Lobby;			//background for game hub

	SOUND_TYPE m_Sound_Type;

	float volMM;				//current volume of main menu
	float volME;				//current volume of maze escaper
	float volPP;				//current volume of puzzle party
	float volMP;				//current volume of mcq power
	float volS;					//current volume of stress
	float volLob;				//current volume of lobby
	float maxVol;				//volume defined by lua script

	bool active;				//play sound if active
};

