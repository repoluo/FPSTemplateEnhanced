// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "GameOverUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEMPLATEENHANCED_API UGameOverUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void ButtonClick();

	UFUNCTION()
	void LoadNextLevel();

};
