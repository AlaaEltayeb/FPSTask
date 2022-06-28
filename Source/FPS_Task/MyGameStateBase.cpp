// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

AMyGameStateBase::AMyGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	SetReplicates(true);
}

void AMyGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority())
		return;

	if (fGameTimer > 0)
	{
		fGameTimer -= DeltaTime;
	}
}

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameStateBase, fGameTimer);
	DOREPLIFETIME(AMyGameStateBase, iRedTeamFlagCount);
	DOREPLIFETIME(AMyGameStateBase, iBlueTeamFlagCount);
}