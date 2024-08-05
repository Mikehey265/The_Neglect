// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerMovingActor.h"

ATriggerMovingActor::ATriggerMovingActor()
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerMovingActor::OnOverlapBegin);
}

void ATriggerMovingActor::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (bHasBeenTriggered)
	{
		return;
	}
	
	if (OtherActor && OtherActor != this && ActorToMoveClass && Points.Num() > 0)
	{
		TArray<AActor*> ValidPoints;
		for(AActor* Point : Points)
		{
			if(Point)
			{
				ValidPoints.Add(Point);
			}
		}

		if(ValidPoints.Num() > 0)
		{
			UE_LOG(LogTemp, Display, TEXT("Overlap Begin. Overlapping actor: %s"), *OtherActor->GetName());
			
			if(!MovingActor)
			{
				if(bShouldSpawnActor)
				{
					FActorSpawnParameters SpawnParams;
					MovingActor = GetWorld()->SpawnActor<AActor>(ActorToMoveClass, ValidPoints[0]->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
					CurrentTargetIndex = 1;
				}
				else if(ExistingActor && ExistingActor->IsA(ActorToMoveClass))
				{
					MovingActor = ExistingActor;
					CurrentTargetIndex = 0;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("ExistingActor is not set or is not of class ActorToMoveClass"))
				}
				bIsMoving = true;
				Points = ValidPoints;
				GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &ATriggerMovingActor::MoveActor, 0.01f, true);
				
				bHasBeenTriggered = true;
			}
		}
	}
}

void ATriggerMovingActor::MoveActor()
{
	if(MovingActor && Points.IsValidIndex(CurrentTargetIndex))
	{
		AActor* CurrentTarget = Points[CurrentTargetIndex];
		if(!CurrentTarget)
		{
			CurrentTargetIndex++;
			return;
		}

		float DeltaTime = GetWorld()->GetDeltaSeconds();

		FVector CurrentLocation = MovingActor->GetActorLocation();
		FVector TargetLocation = CurrentTarget->GetActorLocation();
		FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		FVector NewLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;

		FRotator NewRotation = Direction.Rotation();
		MovingActor->SetActorRotation(NewRotation);

		if(FVector::Dist(NewLocation, TargetLocation) <= MoveSpeed * DeltaTime)
		{
			NewLocation = TargetLocation;
			MovingActor->SetActorLocation(NewLocation);

			if (CurrentTargetIndex == Points.Num() - 1)
			{
				GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);

				if (bShouldSpawnActor)
				{
					GetWorld()->GetTimerManager().SetTimer(DestructionTimerHandle, this, &ATriggerMovingActor::DestroyMovingActor, DestructionDelay, false);
				}
				
				return;
			}
			else
			{
				CurrentTargetIndex++;
			}
		}
		MovingActor->SetActorLocation(NewLocation);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
		bIsMoving = false;
	}
}

void ATriggerMovingActor::DestroyMovingActor()
{
	if (MovingActor)
	{
		MovingActor->Destroy();
		MovingActor = nullptr;
		bIsMoving = false;
	}
}
