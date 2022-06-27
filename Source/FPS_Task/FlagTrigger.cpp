// Fill out your copyright notice in the Description page of Project Settings.


#include "FlagTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include <FPS_Task/FPS_TaskCharacter.h>
#include <FPS_Task/MyGameStateBase.h>
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

// Sets default values
AFlagTrigger::AFlagTrigger()
{
	FlagMeshComp = CreateAbstractDefaultSubobject<UStaticMeshComponent>(FName("Flag"));
	BaseMeshComp = CreateAbstractDefaultSubobject<UStaticMeshComponent>(FName("Base"));

	FlagMeshComp->SetCollisionProfileName("NoCollision");
	BaseMeshComp->SetCollisionProfileName("NoCollision");

	BaseMeshComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	BaseMeshComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	FlagTriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("FlagTriggerVolume"));
	FlagTriggerVolume->SetBoxExtent(FVector(100.0f, 100.0f, 50.0f));

	FlagTriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FlagTriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	FlagTriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	if (FlagTriggerVolume == nullptr)
		return;

	RootComponent = FlagTriggerVolume;
}

// Called when the game starts or when spawned
void AFlagTrigger::BeginPlay()
{
	Super::BeginPlay();

	SetReplicates(true);
	FlagMeshComp->SetIsReplicated(true);
}

void AFlagTrigger::PlayEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

void AFlagTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (GetLocalRole() != ROLE_Authority)
		return;

	AFPS_TaskCharacter* MyCharacter = Cast<AFPS_TaskCharacter>(OtherActor);

	if (!MyCharacter)
		return;

	if (MyCharacter->bIsRed != bIsRedFlag && bHasFlag)
	{
		PlayEffect();

		MyCharacter->bIsCarryingFlag = true;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Flag Carried");

		FlagMeshComp->DestroyComponent(true);

		bHasFlag = false;
	}
	else if (MyCharacter->bIsRed == bIsRedFlag && MyCharacter->bIsCarryingFlag)
	{
		MyCharacter->bIsCarryingFlag = false;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Flag Captured");

		AMyGameStateBase* gameState = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
		if (MyCharacter->bIsRed)
		{
			gameState->iRedTeamFlagCount++;
		}
		else
		{
			gameState->iBlueTeamFlagCount++;
		}
	}
}