#include "SpawnManager.h"
#include "MovingPlatform.h"
#include "RotatingActor.h"

ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
    if (ActorClassesToSpawn.Num() == 0) return;

    for (int32 i = 0; i < SpawnCount; i++)
    {
        // 1. 랜덤 위치 계산
        FVector RandomLocation(
            FMath::RandRange(SpawnRangeMin.X, SpawnRangeMax.X),
            FMath::RandRange(SpawnRangeMin.Y, SpawnRangeMax.Y),
            FMath::RandRange(SpawnRangeMin.Z, SpawnRangeMax.Z)
        );

        // 2. 배열에서 랜덤하게 클래스 하나 선택
        int32 RandomIndex = FMath::RandRange(0, ActorClassesToSpawn.Num() - 1);
        TSubclassOf<AActor> SelectedClass = ActorClassesToSpawn[RandomIndex];

        if (SelectedClass)
        {
            // 3. 액터 스폰
            AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SelectedClass, RandomLocation, FRotator::ZeroRotator);

            if (SpawnedActor)
            {
                // 4. [중요] 어떤 클래스인지 확인 후 랜덤 속성 부여

                // 만약 이동 플랫폼이라면?
                if (AMovingPlatform* MovingActor = Cast<AMovingPlatform>(SpawnedActor))
                {
                    MovingActor->MoveVelocity = FVector(FMath::RandRange(-300.f, 300.f), FMath::RandRange(-300.f, 300.f), 0.f);
                    MovingActor->MaxRange = FMath::RandRange(200.f, 800.f);
                }
                // 만약 회전 액터라면?
                else if (ARotatingActor* RotatingActor = Cast<ARotatingActor>(SpawnedActor))
                {
                    float RandomYaw = FMath::RandRange(45.f, 360.f);
                    RotatingActor->RotationVelocity = FRotator(0.f, RandomYaw, 0.f);
                }
            }
        }
    }
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

