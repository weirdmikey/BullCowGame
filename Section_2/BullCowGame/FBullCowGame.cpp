#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame()  // default constructor
{
	Reset();

}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGamewon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTrys{ {3, 5}, {4, 7}, {5, 8}, {6, 10} };
	return WordLengthToMaxTrys[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLenght() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGamewon;
}

EGuessStatus FBullCowGame::CheckGiessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLopwercase(Guess)) // if guess is all lower case, return error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght())
	{
		return EGuessStatus::Too_Short;
	}
	else
	{
		return EGuessStatus::OK;
	}
	// if guess lenght is wrong
	   //return error

	//otherwise 
	//return ok
}

// recives a valid guess, incruments turns and retunrs count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{	
	
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32  WordLenghth = MyHiddenWord.length(); // assumning the same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLenghth; MHWChar++)
	{
		// compair letters agans the guess
		for (int32 GChar = 0; GChar < WordLenghth; GChar++)
		{
			// if they match theen 
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {  // if ther in the sdameplace
					BullCowCount.Bulls++;// increment bulls
				}
				else
				{
					BullCowCount.Cows++;// incremment cows if not 

				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLenghth)
	{
		bGamewon = true;
	}
	else
	{
		bGamewon = false;
	}
	return BullCowCount;

}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms 
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // set up map
	for (auto Letter : Word)  // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { return false; }
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	// loop throug all thye leetres of the word
	    // if the letter is n the map 
	  // we do not have a iusogram
	//otherwise
	    // add the letter to the map as seen

	return true; // for example in case /0 is entered
}

bool FBullCowGame::IsLopwercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}

	}

	return true;
}
