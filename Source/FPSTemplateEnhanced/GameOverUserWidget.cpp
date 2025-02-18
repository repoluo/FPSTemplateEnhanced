// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/WidgetAnimation.h"

void UGameOverUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UButton* NextLevelButton = Cast<UButton>(GetWidgetFromName(TEXT("Button_NextLevel"))))
	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, "ButtonClick");
		NextLevelButton->OnClicked.Add(ScriptDelegate);
	}
	
}

void UGameOverUserWidget::ButtonClick()
{
	LoadNextLevel();
}

void UGameOverUserWidget::LoadNextLevel()
{
	FString LevelName = "/Game/FirstPerson/Maps/FirstPersonMap2.umap";
	UGameplayStatics::OpenLevel(this, FName(LevelName));
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());

		// 设置玩家角色的位置
		if (APawn* PlayerPawn = PlayerController->GetPawn())
		{
			FVector NewLocation = FVector(-30.f, 0.f, -150.f); // 设置玩家角色的位置
			PlayerPawn->SetActorLocation(NewLocation);
		}
	}
	
}