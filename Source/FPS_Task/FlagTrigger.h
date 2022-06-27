// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlagTrigger.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class FPS_TASK_API AFlagTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlagTrigger();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "StaticMeshObject")
		UStaticMeshComponent* FlagMeshComp;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "StaticMeshObject")
		UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		UBoxComponent* FlagTriggerVolume;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* PickupFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffect();

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsRedFlag;

	bool bHasFlag = true;
};
