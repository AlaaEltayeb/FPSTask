// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 *
 */
UCLASS()
class FPS_TASK_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Gameplay")
		int iPlayersCount = 0;

public:
	AMyGameStateBase();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Gameplay")
		int iRedTeamFlagCount;
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Gameplay")
		int iBlueTeamFlagCount;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "GamePlay")
		float fGameTimer = 60.0f;
};
