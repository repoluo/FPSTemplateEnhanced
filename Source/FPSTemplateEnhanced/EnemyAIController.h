// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEMPLATEENHANCED_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	void ChasePlayer(APawn* PlayerPawn);
	
	void SetRandomPatrolPoint();
	
	void Patrol(float DeltaTime);
	
	void SetSetPatrolPointFromExternal(FVector Point);
	
	void OnWaitTimerExpired();
	
	void CheckPosition();

private:
	bool bIsWaiting = false;
	FVector PatrolPoint;
	FVector LastPosition;
	FVector InitialLocation;
	FTimerHandle WaitTimerHandle; // for patrol
	FTimerHandle PositionCheckTimerHandle; // for prevent the enemy from being motionless
};
