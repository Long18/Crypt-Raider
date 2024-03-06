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
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) return;

	FVector TargetLocattion = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocattion, GetComponentRotation());
}


void UGrabber::ReleaseObject()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle != nullptr) PhysicsHandle->ReleaseComponent();
}

void UGrabber::GrabObject()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) return;

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

	PhysicsHandle->GrabComponentAtLocationWithRotation
	(
		HitResult.GetComponent(),
		NAME_None,
		HitResult.ImpactPoint,
		GetComponentRotation()
	);
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}
	return Result;
}

