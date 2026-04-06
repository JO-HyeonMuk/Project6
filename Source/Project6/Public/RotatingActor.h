#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogRotatingActor, Warning, All);

UCLASS()
class PROJECT6_API ARotatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ARotatingActor();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformSettings|Movement")
	FRotator RotationVelocity;



protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};