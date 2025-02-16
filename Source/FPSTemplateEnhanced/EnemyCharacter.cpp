// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EnemyAIController.h"
#include "FPSTemplateEnhancedProjectile.h"
#include "FPSTemplateEnhancedGameMode2.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// load the character mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Create a pawn sensing component
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SetPeripheralVisionAngle(120.0f);

	AIControllerClass = AEnemyAIController::StaticClass();

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Bind the function that will fire when the player is seen
	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePlayer);
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::OnSeePlayer(APawn* Pawn)
{
	// If the player is seen, print a message
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Player %s is seen!"), *Pawn->GetName()));
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->ChasePlayer(Pawn);
	}
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	HitCount++;
	if (DamageCauser && DamageCauser->IsA(AFPSTemplateEnhancedProjectile::StaticClass()))
	{
		FVector KnockBackDirection = GetActorLocation() - DamageCauser->GetActorLocation();
		KnockBackDirection.Z = 0; // 保持水平击退
		KnockBackDirection.Normalize();
		KnockBack(KnockBackDirection, 3000.0f); // 调整击退强度
	}
	if (HitCount == 3)
	{
		AFPSTemplateEnhancedGameMode2* GameMode = Cast<AFPSTemplateEnhancedGameMode2>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			int32 Score = Point;
			GameMode->AddScore(Score);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("TotalScore += %d"), Score));
		}
		Destroy();
	}

	return DamageAmount;
}

void AEnemyCharacter::KnockBack(const FVector& KnockBackDirection, float KnockBackStrength)
{
	LaunchCharacter(KnockBackDirection * KnockBackStrength, true, true);
}