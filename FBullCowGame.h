/* Class structure for the game object. No code here. 
Drives the game based on Mastermind. */

#pragma once
#include <string>
using FSTRING = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class ETryStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Word_Has_Space,
	Wrong_Length,
	Not_Lowercase,
	Word_Contains_Nums
};

class FBullCowGame {
public:  //This is called the interface
	FBullCowGame(); // Constructor

	int32 GetMaxTries();
	int32 GetCurrentTry() const;
	int32 IncrementCurrentTry(int32);
	int32 GetHiddenWordLength() const;
	
	bool IsGameWon() const;
	ETryStatus IsTryValid(FSTRING); 
	
	//Count Bulls and Cows and increases Try #. Assumes a valid guess
	FBullCowCount SubmitValidTry(FSTRING);

	void SelectWordByLength(int32);
	
	void Reset();

private:
	//See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FSTRING MyHiddenWord;
	bool bGameIsWon;

	//Support Methods
	bool IsIsogram(FSTRING) const;
	bool IsLowercase(FSTRING) const;
};