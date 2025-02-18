// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycleActor.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/SkyLight.h"
#include "Components/SkyLightComponent.h"

// Sets default values
ADayNightCycleActor::ADayNightCycleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ADayNightCycleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADayNightCycleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LightSource)
	{
		LightSource->AddActorLocalRotation(FRotator(DeltaTime * TurnRate), 0, 0);
	}
	// if (Sun)
	// {
	// 	FOutputDeviceNull AR;
	// 	Sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), AR, NULL, true);
	// }

}



