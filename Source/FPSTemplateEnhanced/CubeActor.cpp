// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/PointLightComponent.h"
#include "FPSTemplateEnhancedProjectile.h"
#include "FPSTemplateEnhancedGameMode.h"
#include "FPSTemplateEnhancedGameMode2.h"

// Sets default values
ACubeActor::ACubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = CubeMeshComponent;
	CubeMeshComponent->SetSimulatePhysics(true);
	CubeMeshComponent->OnComponentHit.AddDynamic(this, &ACubeActor::OnHit);
	LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("CubeActorLight"));
	LightComponent->SetupAttachment(CubeMeshComponent);
	LightComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 45.0f)); // 设置光源位置为物体中心
	LightComponent->SetIntensity(0.0f);
	LightComponent->SetAttenuationRadius(90.0f);
}

// Called when the game starts or when spawned
void ACubeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// OnHit function
void ACubeActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(AFPSTemplateEnhancedProjectile::StaticClass()))
	{
		HitCount++;
		if (HitCount == 1)
		{
			SetActorScale3D(GetActorScale3D() * Y); // 缩放为Y倍
		}
		else if (HitCount == 2)
		{
			// score operation
			FString CurrentLevelName = GetWorld()->GetMapName();

			if (CurrentLevelName.Equals(L"UEDPIE_0_FirstPersonMap"))
			{
				AFPSTemplateEnhancedGameMode* GameMode = Cast<AFPSTemplateEnhancedGameMode>(GetWorld()->GetAuthGameMode());
				if (GameMode)
				{
					int32 Score =  Points;
					GameMode->AddScore(Score);
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("TotalScore += %d"), Score));
				}
			}
			else if (CurrentLevelName.Equals(L"UEDPIE_0_FirstPersonMap2"))
			{
				AFPSTemplateEnhancedGameMode2* GameMode = Cast<AFPSTemplateEnhancedGameMode2>(GetWorld()->GetAuthGameMode());
				if (GameMode)
				{
					int32 Score =  Points;
					GameMode->AddScore(Score);
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("TotalScore += %d"), Score));
				}
			}
			
			Destroy(); // 销毁方块
		}
		// OtherActor->Destroy(); // 销毁子弹

		
	}
}

void ACubeActor::SetCubeColorLight(const FVector& ColorVector)
{
	if (LightComponent)
	{
		LightComponent->SetLightColor(FLinearColor::Red);
		LightComponent->SetIntensity(999999.0f);
	}
}