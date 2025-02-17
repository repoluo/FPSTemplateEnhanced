// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSTemplateEnhancedGameMode2.h"
#include "CubeActor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

AFPSTemplateEnhancedGameMode2::AFPSTemplateEnhancedGameMode2()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	GameOverWidget = nullptr;
	LevelWidget = nullptr;
}

void AFPSTemplateEnhancedGameMode2::StartPlay()
{
	Super::StartPlay();
	check(GEngine != nullptr);

	StartGame();

	// show debug info
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode--2!"));
}

void AFPSTemplateEnhancedGameMode2::StartGame()
{
	// Randomly select important target cubes
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACubeActor::StaticClass(), FoundActors);

	for (int32 i = 0; i < NumberOfImportantTargets && FoundActors.Num() > 0; i++)
	{
		int32 Index = FMath::RandRange(0, FoundActors.Num() - 1);
		ACubeActor* Target = Cast<ACubeActor>(FoundActors[Index]);
		if (Target)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("SetImportantTarget！"));
			Target->bIsImportantTarget = true;
			Target->Points *= 3;
			Target->SetCubeColorLight(FVector(1.0f, 0.0f, 0.0f));
		}
		FoundActors.RemoveAt(Index);
	}

	if (UClass* LevelWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FirstPerson/Blueprints/WBP_LevelHint.WBP_LevelHint_C'")))
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			LevelWidget = CreateWidget<UUserWidget>(PlayerController, LevelWidgetClass);
			if (LevelWidget)
			{
				LevelWidget->AddToViewport();
				UTextBlock* ScoreText = Cast<UTextBlock>(LevelWidget->GetWidgetFromName(TEXT("LevelName")));
				if (ScoreText)
				{
					ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Level 2"))));
				}
			}
		}
	}

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		// 显示鼠标光标
		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	// Start game timer
	GetWorldTimerManager().SetTimer(TimerHandle_GameTimer, this, &AFPSTemplateEnhancedGameMode2::EndGame, GameDuration, false);
}

void AFPSTemplateEnhancedGameMode2::EndGame()
{
	// Print scores
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PlayerController = It->Get();
		if (PlayerController)
		{
			// Print player score (implement your own scoring system)
		}
	}

	// Print total score
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Total Score: %d"), TotalScore));
	
	if (UClass* GameOverWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FirstPerson/Blueprints/WBP_GameOverWidget.WBP_GameOverWidget_C'")))
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			GameOverWidget = CreateWidget<UUserWidget>(PlayerController, GameOverWidgetClass);
			if (GameOverWidget)
			{
				GameOverWidget->AddToViewport();
				UTextBlock* ScoreText = Cast<UTextBlock>(GameOverWidget->GetWidgetFromName(TEXT("TextBlock_TotalScore")));
				if (ScoreText)
				{
					ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Total Score: %d"), TotalScore)));
				}
			}
			// 禁用玩家控制器的输入
			PlayerController->SetIgnoreMoveInput(true);
			PlayerController->SetIgnoreLookInput(true);

			// 显示鼠标光标
			PlayerController->bShowMouseCursor = true;
			PlayerController->SetInputMode(FInputModeUIOnly());
		}
	}
	
	

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACubeActor::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		Actor->Destroy();
	}

}

void AFPSTemplateEnhancedGameMode2::AddScore(int32 Score)
{
	TotalScore += Score;
}
