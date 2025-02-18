// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "StartUserWidget.h"
#include "FPSTemplateEnhancedGameMode.generated.h"

UCLASS(minimalapi)
class AFPSTemplateEnhancedGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSTemplateEnhancedGameMode();
protected:
	virtual void StartPlay() override;

private:
	void StartGame();
	void EndGame();

	// Number of important target cubes
	UPROPERTY(EditAnywhere, Category="Gameplay")
	int32 NumberOfImportantTargets = 3;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	float GameDuration = 20.0f;

	FTimerHandle TimerHandle_GameTimer;
	FTimerHandle TimerHandle_DynamicHintTimer;

	int32 TotalScore = 0;
	
	UUserWidget* GameOverWidget;
	UUserWidget* LevelWidget;
	UStartUserWidget* StartWidget;
	UUserWidget* DynamicHintWidget;

public:
	UFUNCTION()
	void AddScore(int32 Score);

	UFUNCTION()
	void OnLoginSuccess();

	UFUNCTION()
	void HideDynamicHintWidget();
	
};



