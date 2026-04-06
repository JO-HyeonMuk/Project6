#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class PROJECT6_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnManager();

    UPROPERTY(EditAnywhere, Category = "Spawning")
    TArray<TSubclassOf<AActor>> ActorClassesToSpawn;

    UPROPERTY(EditAnywhere, Category = "Spawning")
    int32 SpawnCount = 20;

    UPROPERTY(EditAnywhere, Category = "Spawning")
    FVector SpawnRangeMin;

    UPROPERTY(EditAnywhere, Category = "Spawning")
    FVector SpawnRangeMax;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
