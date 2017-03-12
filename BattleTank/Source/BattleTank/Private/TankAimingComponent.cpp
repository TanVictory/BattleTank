// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UTankAimingComponent::AimAt(FVector & HitLocation,float LaunchSpeed)
{
	ProjectileLaunchSpeed = LaunchSpeed;
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FirePoint"));
	
	//Calculate the OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
		this, 
		OutLaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		)
		)
	{
		auto AimAtSpeed = OutLaunchVelocity.GetSafeNormal();
		
		MoveBarrelTowards(AimAtSpeed);
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f AimSolution found"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f AimSolution not found"), Time);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Work-out different between current barrel rotation,and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("%s AimDirection  is : %s"), *GetOwner()->GetName(), *AimAsRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("%s DeltaRotator.Pitch  is : %f"), *GetOwner()->GetName(), DeltaRotator.Pitch);

	Barrel->Elevate(DeltaRotator.Pitch); //TODO remove magic number
}