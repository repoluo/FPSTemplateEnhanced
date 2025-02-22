// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (EnemyCharacter)
	{
		InitialLocation = EnemyCharacter->GetActorLocation();
	}

	SetRandomPatrolPoint();

	// 启动计时器，每2秒检查一次位置
	GetWorld()->GetTimerManager().SetTimer(PositionCheckTimerHandle, this, &AEnemyAIController::CheckPosition, 2.0f, true);
}

void AEnemyAIController::ChasePlayer(APawn* PlayerPawn)
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (EnemyCharacter)
	{
		EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = 520.0f; // 设置为所需的速度值
	}
	if (PlayerPawn)
	{
		MoveToActor(PlayerPawn, 20.0f);  
	}
}

void AEnemyAIController::SetRandomPatrolPoint()
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (EnemyCharacter)
	{
		EnemyCharacter->SetbPlayerSeen(false);
		FVector OriginLocation = InitialLocation;
		FVector NextRandomPoint = OriginLocation + FMath::VRand() * 1000.0f; // 随机1000个单位范围内
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()); // 获取导航系统
		if (NavSystem)
		{
			FNavLocation ResultLocation;
			if (NavSystem->ProjectPointToNavigation(NextRandomPoint, ResultLocation))
			{
				PatrolPoint = ResultLocation.Location;
			}
			else
			{
				// 如果点不在可导航区域内，递归调用函数重新设置巡逻点
				SetRandomPatrolPoint();
			}
		}
	}
}

void AEnemyAIController::Patrol(float DeltaTime)
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (EnemyCharacter)
	{
		if (bIsWaiting)
		{
			return; // 如果正在等待，则不执行巡逻逻辑
		}
		if (FVector::Dist(EnemyCharacter->GetActorLocation(), PatrolPoint) < 100.0f)
		{
			// 到达巡逻点后设置等待
			bIsWaiting = true;
			GetWorld()->GetTimerManager().SetTimer(WaitTimerHandle, this, &AEnemyAIController::OnWaitTimerExpired, 2.0f, false);
		}
		else
		{
			// EnemyCharacter->GetActorLocation()
			
			EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = 150.0f; // 设置为所需的速度值
			MoveToLocation(PatrolPoint, -1.0f, true, true, false, true, 0, true);

			// 计算旋转到巡逻点
			FVector Direction = PatrolPoint - EnemyCharacter->GetActorLocation();
			Direction.Z = 0;
			Direction.Normalize();
			FRotator TargetRotation = Direction.Rotation();
			FRotator CurrentRotation = EnemyCharacter->GetActorRotation();
			FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.0f); // 根据需要调整插值速度
			EnemyCharacter->SetActorRotation(NewRotation);
		}
	}
}

void AEnemyAIController::SetSetPatrolPointFromExternal(FVector Point)
{
	PatrolPoint = Point;
}

void AEnemyAIController::OnWaitTimerExpired()
{
	bIsWaiting = false;
	SetRandomPatrolPoint();
}

void AEnemyAIController::CheckPosition()
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (EnemyCharacter)
	{
		FVector CurrentPosition = EnemyCharacter->GetActorLocation();
		if (CurrentPosition.Equals(LastPosition, 1.0f)) // 如果位置无变化
		{
			SetRandomPatrolPoint();
		}
		LastPosition = CurrentPosition;
	}
}
