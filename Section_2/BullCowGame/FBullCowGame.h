/*
the game logic (no view code or direct user ineration
*/

#pragma once
#include <string>

// to mmake syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EGuessStatus
{
	Invlaid_Status,
	OK,
	Not_Isogram,
	Too_Short,
	Not_Lowercase


};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;

	void Reset(); // todo a more rich return value

	EGuessStatus CheckGiessValidity(FString) const;

	// counts bulls and cows and increasses try number
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGamewon;

	bool IsIsogram(FString) const;
	bool IsLopwercase(FString) const ;
	

};