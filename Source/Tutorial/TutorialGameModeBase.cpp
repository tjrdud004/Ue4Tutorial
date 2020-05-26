// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialGameModeBase.h"
#include "ConstructorHelpers.h"
#include "Player/CPlayer.h"

ATutorialGameModeBase::ATutorialGameModeBase()
{
	FString path = L"Blueprint'/Game/Player/BpCPlayer.BpCPlayer_C'";
	static ConstructorHelpers::FClassFinder<ACPlayer> player(*path);

	if (player.Succeeded())
		DefaultPawnClass = player.Class;

}