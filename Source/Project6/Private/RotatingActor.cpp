#include "RotatingActor.h"

DEFINE_LOG_CATEGORY(LogRotatingActor);
ARotatingActor::ARotatingActor()
{
 
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);

	RotationVelocity = FRotator(0.f, 90.f, 0.f);
}


void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogRotatingActor, Warning, TEXT("%s: BeginPlay - Initial Speed: %s"),
		*GetName(), *RotationVelocity.ToString());
	
}

void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

