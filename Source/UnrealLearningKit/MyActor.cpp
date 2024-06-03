// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RotationSpeed = FRotator(0,90,0);

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	 
	StartLocation = GetActorLocation();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{   
	Super::Tick(DeltaTime);
	ToFroMotion(DeltaTime);
	Rotator(DeltaTime);
}
 void AMyActor::Rotator(float DeltaTime)
 {
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation += (RotationSpeed*DeltaTime);
	SetActorRotation(CurrentRotation);
	if(CurrentRotation.Euler().Z - StartRotation.Euler().Z> MaxRotation || CurrentRotation.Euler().Z -StartRotation.Euler().z< -MaxRotation){
		RotationSpeed = FRotator(0,-RotationSpeed.Euler().Z,0); 
	}
 }


	void AMyActor::ToFroMotion(float DeltaTime)
{	
	FVector CurrentLocation;
	CurrentLocation =GetActorLocation();
    CurrentLocation += MovementSpeed*DeltaTime;
	SetActorLocation(CurrentLocation);
	DistanceMoved = FVector::Dist(StartLocation,CurrentLocation);
	if(DistanceMoved>=MoveDistance){
		FVector MoveDirection = MovementSpeed.GetSafeNormal();
		StartLocation+=MoveDistance*MoveDirection;
		float offset =FVector::Dist(StartLocation,GetActorLocation());
		SetActorLocation (StartLocation);
		//FString s = "OK";
		//UE_LOG(LogTemp,Warning,TEXT("Log printing %s"),s);
		
		MovementSpeed*=-1;
		
	}
}

bool AMyActor :: DestinationReached(FVector CurrentLocation) const 
{
  return FVector::Dist(CurrentLocation,StartLocation)>=MoveDistance;
}
