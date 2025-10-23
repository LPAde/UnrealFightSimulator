// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FightingSimulatorGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTSIMULATOR_API UFightingSimulatorGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AFightManager* _fightManager;
};
