#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);

	MoveVelocity = FVector(200.0f, 0.0f, 0.0f);
	MaxRange = 500.0f;

}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s: StartLocation: %s"), *GetName(), *StartLocation.ToString());
	
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += (MoveVelocity * DeltaTime);
	SetActorLocation(CurrentLocation);

	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);

	if (DistanceMoved >= MaxRange)
	{
		UE_LOG(LogTemp, Log, TEXT("%s: Reached MaxRange. Reversing!"), *GetName());

		MoveVelocity = -MoveVelocity;

		FVector MoveDirection = MoveVelocity.GetSafeNormal();
		SetActorLocation(CurrentLocation + (MoveVelocity * DeltaTime));
	}

	if (DistanceMoved >= MaxRange)
	{
		GetWorld()->GetTimerManager().SetTimer(DisappearTimerHandle, this, &AMovingPlatform::Disappear, 2.0f, false);
	}
}

void AMovingPlatform::Disappear()
{
	if (MeshComp)
	{
		MeshComp->SetVisibility(false);
		SetActorEnableCollision(false);
	}

	GetWorld()->GetTimerManager().SetTimer(DisappearTimerHandle, this, &AMovingPlatform::Appear, 3.0f, false);

	UE_LOG(LogTemp, Warning, TEXT("%s has disappeared!"), *GetName());
}

void AMovingPlatform::Appear()
{
	if (MeshComp)
	{
		MeshComp->SetVisibility(true);
		SetActorEnableCollision(true);
	}

	UE_LOG(LogTemp, Warning, TEXT("%s has appeared!"), *GetName());
}