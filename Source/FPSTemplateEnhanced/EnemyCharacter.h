// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class FPSTEMPLATEENHANCED_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// lifespan
	int32 HitCount = 0;

	int32 Point = 60;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
    void OnSeePlayer(APawn* Pawn);
	
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensingComponent;

private:
	void KnockBack(const FVector& KnockBackDirection, float KnockBackStrength);

};
