// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::ChasePlayer(APawn* PlayerPawn)
{
	if (PlayerPawn)
	{
		MoveToActor(PlayerPawn, 20.0f);  
	}
}
