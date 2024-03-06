// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator CurrentRotation = GetComponentRotation();
	FString RotationString = CurrentRotation.ToCompactString();
	UE_LOG(LogTemp, Warning, TEXT("Rotation: %s"), *RotationString);

	UWorld* World = GetWorld();
	float time = World->TimeSeconds;
	UE_LOG(LogTemp, Warning, TEXT("Time: %f"), time);

}

