#pragma once
#include "FBullCowGame.h"
#include <map>
#include <cctype>

#define TMap std::map //to make UE4 friendly
using int32 = int;


//Constructor, and it calls Reset()
FBullCowGame::FBullCowGame() { Reset(); } 

//Getters

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	MyHiddenWord = ""; //This must be an isogram.
	bGameIsWon = false;

	return;
}

int32 FBullCowGame::GetMaxTries()
{
	TMap <int32, int32> WordLengthToMaxTries{ {3, 3}, {4, 6}, {5, 9}, {6, 11}, {7,13}, {8, 15} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
	//return 15;
}

void FBullCowGame::SelectWordByLength(int32 PlayerChoice)
{
	TMap <int32, FSTRING> WordLenghGetsWord{ { 3, "hat"}, { 4, "plum" }, { 5, "spain" }, {6, "danger"} };
	MyHiddenWord = WordLenghGetsWord[PlayerChoice];
	//MyHiddenWord = "spain";
	//return;
}



ETryStatus FBullCowGame::IsTryValid(FSTRING PlayerTry) //The course calls this CheckGuessValidity()q
{
	if (PlayerTry.length() != GetHiddenWordLength())
	{
		return ETryStatus::Wrong_Length;
	}
	else if (!IsIsogram(PlayerTry))
	{
		return ETryStatus::Not_Isogram;
	}
	else if (!IsLowercase(PlayerTry))
	{
		return ETryStatus::Not_Lowercase;
	}
	else if (false)
	{
		return ETryStatus::Invalid;
	}
	else 
	{
		return ETryStatus::OK;
	}
}
//Receives a valid guess and increments the try count, then returns it
FBullCowCount FBullCowGame::SubmitValidTry(FSTRING PlayerTry)
{
	//increment turn number
	MyCurrentTry++;
	
	//set a return variable
	FBullCowCount BullCowCount;


	//loop through all letters in the try
		//for each letter do a comparison
			//compare against the hidden word
	//if they match, increment bulls if they are in the same place, increment cows if they're not
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength && i < PlayerTry.length(); i++)
	{
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (MyHiddenWord[i] == PlayerTry[j])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
		
	}
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	
	return BullCowCount;
}



int32 FBullCowGame::IncrementCurrentTry(int32)
{
	return MyCurrentTry++;
}


bool FBullCowGame::IsIsogram(FSTRING PlayerTry) const
{
	if (PlayerTry.length() <= 1) {return true; }

	TMap<char, bool> LetterSeen; //setup our map
	for (auto Letter : PlayerTry) //For all letters of the word (determined automatically)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) //if the letter is in the map
		{
			return false; //We do not have an isogram at this point
		}
		else
		{
			LetterSeen[Letter] = true;
		}
		//detect if one of the letters is already true or counted
		//return false if the count is more than 1, otherwise true
	}
	
	
	
	return true;
}

bool FBullCowGame::IsLowercase(FSTRING PlayerTry) const
{
	for (auto Letter : PlayerTry)
	{
		if (!islower(Letter)) //if it's not a lowercase letter, return false
		{
			return false;
		}
	}
	return true;
}
