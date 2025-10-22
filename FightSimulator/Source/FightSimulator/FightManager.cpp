// Fill out your copyright notice in the Description page of Project Settings.


#include "FightManager.h"
#include "Creature.h"

#define DELAY(time, block)\
{\
FTimerHandle TimerHandle;\
GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()block, time, false);\
}

AFightManager::AFightManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFightManager::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Start"));
	Super::BeginPlay();
	_leftCreature->OnCreatureDiedSignal.AddDynamic(this, &AFightManager::EndFight);
	_rightCreature->OnCreatureDiedSignal.AddDynamic(this, &AFightManager::EndFight);
	_leftCreature->OnFinishedAttackAnimationSignal.AddDynamic(this, &AFightManager::Attack);
	_rightCreature->OnFinishedAttackAnimationSignal.AddDynamic(this, &AFightManager::Attack);

	DELAY(3.0f, 
	{
		StartAttack(_leftCreature);
	UE_LOG(LogTemp, Warning, TEXT("StartAttack"));
	})
}

void AFightManager::EndFight(ACreature* DeadCreature)
{
	ChangeFightState(End);
}

void AFightManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFightManager::StartAttack(ACreature* AttackingCreature)
{
	if (AttackingCreature == _leftCreature)
	{
		_leftCreature->PlayAttackAnimation();
	}
	else
	{
		_rightCreature->PlayAttackAnimation();
	}
}

void AFightManager::Attack(ACreature* AttackingCreature, float DamageMultiplier)
{
	UE_LOG(LogTemp, Warning, TEXT("Attack"));
	if (AttackingCreature == _leftCreature) 
	{
		_rightCreature->GetDamaged(_baseDamage * DamageMultiplier);
	}
	else
	{
		_leftCreature->GetDamaged(_baseDamage * DamageMultiplier);
	}
}

void AFightManager::ChangeFightState(FightState NewFightState)
{
	_fightState = NewFightState;
}