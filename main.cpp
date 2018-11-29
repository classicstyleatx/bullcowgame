/*
This is the console exe that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction
For game logic see the FBullCowGame class.


*/
#pragma once
#include <iostream>
#include <string>
#include <istream>
#include "FBullCowGame.h"

//USING NAMESPACES to make UE4 friendly
using FTEXT = std::string;
using int32 = int;

//PROTOTYPES
void PrintIntro(); //Begins here
void PlayGame(); //This is the main game loop
void AddLine(); //Just an easier way to add line breaks wherever I need them
void PrintGameSummary(int32 numTries);
void IsLastTry();

bool WillPlayAgain(); //This is the affirmation method

char AskToPlayAgain(); //This is the evaluation method

FTEXT GetValidatedTry();

int32 AskForWordLength();

//Instantiate a new game
FBullCowGame BCGame; 

int main()
{
	
	bool bPlayAgain = true;
	do 
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = WillPlayAgain();
		
	} while (bPlayAgain == true);

	return 0;
}

void PrintIntro() 
{

	// Intro the game, and setup the word length constant
	
	std::cout << "===================================================\n";
	std::cout << "===============Instructions=======================\n";
	std::cout << "=================================================\n\n";
	std::cout << "Welcome to Bulls and Cows, a fun word game!" << std::endl;
	std::cout << "In this game, you will guess an isogram (word with no repeating letters) chosen by the system." << std::endl;
	std::cout << "The game will tell you how many letters are in the correct position - Bulls" << std::endl;
	std::cout << "and how many letters are correct but in the wrong position - Cows" << std::endl;
	std::cout << "=================================================\n";
	std::cout << "==================================================\n";
	std::cout << "===================================================\n";
}

void PlayGame()
{
	BCGame.Reset();//This is also our constructor.

	/*Prompt the user for the length of word they want to use, and derive the word to choose from that selection.*/
	BCGame.SelectWordByLength(AskForWordLength());

	AddLine(); //Just formatting

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?";

	AddLine();
	AddLine();
	
	int32 MaxTries = BCGame.GetMaxTries();

	//Loop asking for guesses while the game has not yet been won and tries are remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FTEXT PlayerTry = GetValidatedTry(); 
		FBullCowCount BullCowCount = BCGame.SubmitValidTry(PlayerTry);
		std::cout << "\t\tBulls =  " << BullCowCount.Bulls << " / Cows = " << BullCowCount.Cows << std::endl;
		AddLine();
		
		//PrintTry(PlayerTry);
	}

	PrintGameSummary(BCGame.GetCurrentTry());
}

FTEXT GetValidatedTry()
{	
	
	//Declarations
	int32 currentTry = BCGame.GetCurrentTry();
	ETryStatus TryStatus = ETryStatus::Invalid; //Result of error checking
	FTEXT PlayerTry = ""; //The actual input by the user
	bool ValidTry = false;

	//Loop asking for guesses
	do
	{	
		IsLastTry();
		std::cout << "Try " << currentTry << "/" << BCGame.GetMaxTries() << " - Please enter your guess: ";
		

		getline(std::cin, PlayerTry);

		//Error checking
		TryStatus = BCGame.IsTryValid(PlayerTry);
		switch (TryStatus)
		{
		case ETryStatus::Invalid:
			break;
		case ETryStatus::Not_Isogram:
			std::cout << "Please enter an isogram (word with no repeating letters)\n\n";
			break;
		case ETryStatus::Word_Has_Space:
			std::cout << "Please enter a word with no spaces\n\n";
			break;
		case ETryStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word\n\n";
			break;
		case ETryStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters\n\n";
			break;
		case ETryStatus::Word_Contains_Nums:
			std::cout << "Sorry, this isn't a word (no special characters or numbers please)\n\n";
			break;
		default:
			//assuming the guess is valid
			return PlayerTry;
			break;
		}

	} while (TryStatus != ETryStatus::OK);
	return PlayerTry;
}

int32 AskForWordLength()
{
	int32 WordLengthChoice = 0;
	std::cout << "How long (in letters) should the word be (3 to 6)?";
	std::cin >> WordLengthChoice;
	return WordLengthChoice;
}

void IsLastTry()
{
	if ((BCGame.GetMaxTries() - BCGame.GetCurrentTry()) == 0)
	{
		std::cout << "\n\tBe careful, this is your last chance!" << std::endl;
	}
	//return;
}

bool WillPlayAgain()
{
	char YesOrNo = AskToPlayAgain();

	//Evaluate Action Based On Response
	if (YesOrNo == 'y' || YesOrNo == 'Y')
	{
		return true;
	}
	else if (YesOrNo == 'n' || YesOrNo == 'N')
	{
		std::cout << "Your loss...";
		AddLine();
		return false;
	}
	else {
		std::cout << "Assuming you wanted to play again\n\n";
		return true;
	}
}

char AskToPlayAgain()
{
	AddLine();
	AddLine();
	std::cout << "Do you want to play again? y/n";
	AddLine();
	FTEXT response = "";
	getline(std::cin, response);
	char yesOrNo = response[0];
	return yesOrNo;
}

void AddLine() 
{
	std::cout << std::endl;
}

void PrintGameSummary(int32 numTries)
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\n\n\t\tCongratulations!\n\t\tThanks for playing, you succeeded after " << numTries - 1 << " tries.";
	}
	else
	{
		std::cout << "\n\t\tSorry, you lost. You can play again with the same word.\n";
	}
	

}
