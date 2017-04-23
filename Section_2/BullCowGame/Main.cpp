/*    this is the console executable, that makes use of the bullcow class
this acts as the view in a mvc pattern, and is responsible for

*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//  To make Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
bool BPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

// the entry pont for our game

int main()
{
	std::cout << BCGame.GetMaxTries();
	bool  BPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		PrintGameSummary(); // TODO add a game summary
		BPlayAgain = AskToPlayAgain();
	} 
	while (BPlayAgain);
	
	return 0; // exit Game
}

// introduction to the game
void PrintIntro()
{
	
	std::cout << "\n Welcome to Bulls and Cows, A fun word Game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I'm thinking off?\n";
	return;
}

// Plays a sinagle game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;

	// Loop asking for guess while the game is NOT won
	//and there are still trys remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 
	
		// submit valid guess, and recive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl << "\n\n";
	}

	
	return;
}

// get a guess from the player
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invlaid_Status;
	do {

		// ask for guess
		int32 CurruntTry = BCGame.GetCurrentTry();
		std::cout << "Try: " << CurruntTry << " of " << BCGame.GetMaxTries() << " Enter your guess? ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGiessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Too_Short:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " Letter word\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a isogram\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "please only use lower case\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping tilll we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done, You Won\n";
	}
	else
	{
		std::cout << "Sorry Better Luck Next Time\n";
	}
	return;
}
