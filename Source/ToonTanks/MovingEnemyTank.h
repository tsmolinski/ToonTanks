// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "MovingEnemyTank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AMovingEnemyTank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetSpeed(float value);

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 300.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 350.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;

	void CheckFireCondition();

	bool InFireRange();

	void Move(float Value);
	
};
