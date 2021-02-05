// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
  Super::BeginPlay();

  Isogram = GetValidWords(Words);

  InitGame();

  // PrintLine(TEXT("The number of possible words is %i"), Words.Num());
  // PrintLine(TEXT("The number of valid words is: %i"), GetValidWords(Words).Num());
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
  //if game is over then clearscree() and initgame()
  //else check player guess

  if (bGameOver)
  {
    ClearScreen();
    InitGame();
  }
  else
  {
    ProcessGuess(Input);
  }
}

void UBullCowCartridge::InitGame()
{

  PrintLine(TEXT("Welcome to BullCows Guessing Game!"));

  HiddenWord = Isogram[FMath::RandRange(0, Isogram.Num() - 1)];
  Lives = HiddenWord.Len() * 2;
  bGameOver = false;

  //PrintLine(TEXT("The HiddenWord is: %s. \nIt is %i characters long"), *HiddenWord, HiddenWord.Len());

  PrintLine(TEXT("You Have %i Lives"), HiddenWord.Len() * 2);
  PrintLine(TEXT("Please Enter a guess:"));
  //setting up game

  // const char HW[];
}

void UBullCowCartridge::EndGame()
{
  bGameOver = true;
  PrintLine(TEXT("\nPress enter to play again"));
}

//Check if isogram
//check if right num of char

//remove life

//check if lives > 0
//if yes game over
//if no play again

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
  PrintLine(Guess);
  if (Guess == HiddenWord)
  {
    PrintLine(TEXT("You Guessed it!"));
    EndGame();
    return;
  }

  if (!IsIsogram(Guess))
  {
    PrintLine(TEXT("No repeating letters, guess again"));
    return;
  }

  if (Guess.Len() != HiddenWord.Len())
  {
    PrintLine(TEXT("Incorrect: The Hidden word is %i characters long."), HiddenWord.Len());
    return;
  }

  PrintLine(TEXT("Lost a life"));
  PrintLine(TEXT("You have %i left"), --Lives);

  if (Lives <= 0)
  {
    ClearScreen();
    PrintLine(TEXT("You have no lives left"));
    PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
    EndGame();
    return;
  }

  FBullCowCount Score = GetBullCows(Guess);

  PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.BullCount, Score.CowCount);

  PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{

  for (int32 Index = 0; Index < Word.Len(); Index++)
  {
    for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
    {
      if (Word[Index] == Word[Comparison])
      {
        return false;
      }
    }
  }
  return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{

  TArray<FString> ValidWords;

  for (FString Word : WordList)
  {
    if (Word.Len() >= 4 && Word.Len() <= 8)
    {
      if(IsIsogram(Word))
      {
        ValidWords.Emplace(Word);
      }
    }
  }
  return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
  FBullCowCount Count;

  for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
  {
    if (Guess[GuessIndex] == HiddenWord[GuessIndex])
    {
      Count.BullCount++;
      continue;
    }

    for (int32 CowIndex = 0; CowIndex < HiddenWord.Len(); CowIndex++)
    {
      if (Guess[GuessIndex] == HiddenWord[CowIndex])
      {
        Count.CowCount++;
        break;
      }
    }
  }
  return Count;
}
