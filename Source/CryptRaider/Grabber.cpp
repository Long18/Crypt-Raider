// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle Component found on %s"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Physics Handle Component found on %s"), *PhysicsHandle->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::ReleaseObject()
{
	UE_LOG(LogTemp, Display, TEXT("Released"));
}

void UGrabber::GrabObject()
{
	FVector ReachLineStart = GetComponentLocation();
	FVector ReachLineEnd = ReachLineStart + (GetForwardVector() * MaxGrabDistance);

	DrawDebugLine(GetWorld(), ReachLineStart, ReachLineEnd, FColor::Red);
	DrawDebugSphere(GetWorld(), ReachLineEnd, 10, 10, FColor::Emerald, true, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		ReachLineStart,
		ReachLineEnd,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);

	if (!HasHit) return;
	DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, true, 5);
	DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Blue, true, 5);
	UE_LOG(LogTemp, Display, TEXT("Hit: %s"), *HitResult.GetActor()->GetActorNameOrLabel());
}

