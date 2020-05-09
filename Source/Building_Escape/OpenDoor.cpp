// Copyright Kevin Erik Iin 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = GetOwner() -> GetActorRotation();
	InitialYaw = InitialRotation.Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += CurrentYaw;
	OpenRotation = InitialRotation;
	
	if (!DoorTrigger)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s has the open door component on it, but no DoorTrigger set!"), *GetOwner()->GetName());
	}

	ActorDoorOpen = GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(DoorTrigger && DoorTrigger -> IsOverlappingActor(ActorDoorOpen))
	{
		OpenDoor(DeltaTime);
	}

	else if (InitialYaw != CurrentYaw)
	{
		CloseDoor(DeltaTime);
	}
	
	


	// ...
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Door opening"));
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2.0f);
	OpenRotation.Yaw = CurrentYaw;
	GetOwner() -> SetActorRotation(OpenRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Door closing"));
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, 2.0f);
	OpenRotation.Yaw = CurrentYaw;
	GetOwner() -> SetActorRotation(OpenRotation);
}
