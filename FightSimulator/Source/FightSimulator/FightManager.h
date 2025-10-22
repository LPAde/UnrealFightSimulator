// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FightManager.generated.h"

enum FightState
{
	Beginn = 0,
	PlayerAction = 1,
	PlayerAttack = 2,
	EnemyAttack = 3,
	End = 4
};

UCLASS()
class FIGHTSIMULATOR_API AFightManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFightManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FightState _fightState;
	UFUNCTION()
	void EndFight(class ACreature* DeadCreature);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void StartAttack(class ACreature* AttackingCreature);
	UFUNCTION()
	void Attack(class ACreature* AttackingCreature, float DamageMultiplier);
	void ChangeFightState(FightState NewFightState);
	UPROPERTY(EditAnywhere)
	class ACreature* _leftCreature;
	UPROPERTY(EditAnywhere)
	class ACreature* _rightCreature;
	UPROPERTY(EditAnywhere)
	float _baseDamage;
};


