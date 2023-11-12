// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingEnemyTank.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AMovingEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void AMovingEnemyTank::SetSpeed(float value)
{
	Speed = value;
}

void AMovingEnemyTank::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void AMovingEnemyTank::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AMovingEnemyTank::CheckFireCondition, FireRate, true);
}

void AMovingEnemyTank::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}

	if (InFireRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool AMovingEnemyTank::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}

void AMovingEnemyTank::Move(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);

	// X = Value * Speed * DeltaTime
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}
