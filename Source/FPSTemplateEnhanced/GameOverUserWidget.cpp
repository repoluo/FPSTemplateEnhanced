// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

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
	FString LevelName = "/Game/FirstPerson/Maps/FirstPersonMap2.FirstPersonMap2'";
	UGameplayStatics::OpenLevel(this, FName(LevelName));
	// FString LevelName = "/Game/FirstPerson/Maps/FirstPersonMap2.umap";
	// UWorld* World = GetWorld();
	// if (!World) return;
	//
	// // 获取当前World关联的FWorldContext
	// FWorldContext* WorldContext = GEngine->GetWorldContextFromWorld(World);
	// if (!WorldContext) return;
	// FString option = "Error";
	// // 调用LoadMap加载新关卡
	// FURL URL(nullptr, *LevelName, TRAVEL_Absolute);
	// World->GetGameInstance()->GetEngine()->LoadMap(*WorldContext, URL, nullptr, option);
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