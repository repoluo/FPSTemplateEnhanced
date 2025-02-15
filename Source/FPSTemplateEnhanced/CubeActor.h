// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "CubeActor.generated.h"

UCLASS()
class FPSTEMPLATEENHANCED_API ACubeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// lifespan
	int32 HitCount = 0;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void SetCubeColorLight(const FVector& Color);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cube")
	float ScaleFactor = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cube")
	int32 Points = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cube")
	bool bIsImportantTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cube")
	UStaticMeshComponent* CubeMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cube")
	UPointLightComponent* LightComponent;
	
	float Y = 0.5f;
};
