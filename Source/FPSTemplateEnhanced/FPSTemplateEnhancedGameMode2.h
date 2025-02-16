// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSTemplateEnhancedGameMode2.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEMPLATEENHANCED_API AFPSTemplateEnhancedGameMode2 : public AGameModeBase
{
	GENERATED_BODY()

	AFPSTemplateEnhancedGameMode2();

protected:
	virtual void StartPlay() override;

private:
	void StartGame();
	void EndGame();

	// Number of important target cubes
	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 NumberOfImportantTargets = 2;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	float GameDuration = 30.0f;

	FTimerHandle TimerHandle_GameTimer;

	int32 TotalScore = 0;
	
	UUserWidget* GameOverWidget;
	UUserWidget* LevelWidget;

public:
	UFUNCTION()
	void AddScore(int32 Score);
	
};
