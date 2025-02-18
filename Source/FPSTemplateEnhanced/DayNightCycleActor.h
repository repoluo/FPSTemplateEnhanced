// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"
#include "Misc/OutputDeviceNull.h"
#include "GameFramework/Actor.h"
#include "DayNightCycleActor.generated.h"

UCLASS()
class FPSTEMPLATEENHANCED_API ADayNightCycleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNightCycleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "DayNightCycle") 
        AActor* Sun;
	
	// Directional light for the sun
	UPROPERTY(EditAnywhere, Category = "DayNightCycle")
		ADirectionalLight* LightSource;

	UPROPERTY(EditAnywhere, Category = "DayNightCycle")
		float TurnRate;
	

};
