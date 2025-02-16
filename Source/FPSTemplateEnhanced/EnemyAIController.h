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
	
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* EnemyBehaviorTree;
	
public:
	virtual void BeginPlay() override;
	void ChasePlayer(APawn* PlayerPawn);
};
