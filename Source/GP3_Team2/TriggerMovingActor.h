// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerMovingActor.generated.h"

/**
 * 
 */
UCLASS()
class GP3_TEAM2_API ATriggerMovingActor : public ATriggerBox
{
	GENERATED_BODY()

public:
	ATriggerMovingActor();

private:
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	void MoveActor();

	UFUNCTION()
	void DestroyMovingActor();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToMoveClass = nullptr;

	UPROPERTY(EditAnywhere)
	bool bShouldSpawnActor = true;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition = "!bShouldSpawnActor"))
	AActor* ExistingActor = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> Points;

	UPROPERTY(EditAnywhere, Blueprintable)
	float MoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, Blueprintable)
	float DestructionDelay = 5.0f;

	FTimerHandle MovementTimerHandle;
	FTimerHandle DestructionTimerHandle;

	AActor* MovingActor = nullptr;
	bool bIsMoving = false;
	int32 CurrentTargetIndex = 0;
	bool bHasBeenTriggered = false;
};
