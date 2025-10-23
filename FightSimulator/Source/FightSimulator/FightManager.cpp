// Fill out your copyright notice in the Description page of Project Settings.


#include "FightManager.h"
#include "Creature.h"
#include "FightingSimulatorGameInstance.h"
#include "UIManager.h"

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
	Super::BeginPlay();
	_playerCreature->OnCreatureDiedSignal.AddDynamic(this, &AFightManager::EndFight);
	_enemyCreature->OnCreatureDiedSignal.AddDynamic(this, &AFightManager::EndFight);
	_playerCreature->OnCreatureTookDamageSignal.AddDynamic(this, &AFightManager::EndTurn);
	_enemyCreature->OnCreatureTookDamageSignal.AddDynamic(this, &AFightManager::EndTurn);
	_playerCreature->OnFinishedAttackAnimationSignal.AddDynamic(this, &AFightManager::Attack);
	_enemyCreature->OnFinishedAttackAnimationSignal.AddDynamic(this, &AFightManager::Attack);

	Cast<UFightingSimulatorGameInstance>(GetGameInstance())->_fightManager = this;

	DELAY(3.0f,
	{
			ChangeFightState(Beginn);
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
	if (AttackingCreature == _playerCreature)
	{
		_playerCreature->PlayAttackAnimation();
	}
	else
	{
		_enemyCreature->PlayAttackAnimation();
	}
}

void AFightManager::Attack(ACreature* AttackingCreature, float DamageMultiplier)
{
	if (AttackingCreature == _playerCreature) 
	{
		_enemyCreature->GetDamaged(_baseDamage * DamageMultiplier);
	}
	else
	{
		_playerCreature->GetDamaged(_baseDamage * DamageMultiplier);
	}
}

void AFightManager::DoPlayerAttack()
{
	StartAttack(_playerCreature);
}

void AFightManager::EndTurn(ACreature* HitCreature)
{
	if (HitCreature == _playerCreature) 
	{
		ChangeFightState(PlayerAction);
	}
	else
	{
		ChangeFightState(EnemyAttack);
	}
}

void AFightManager::ChangeFightState(FightState NewFightState)
{
	_fightState = NewFightState;
	AUIManager* uiManager = Cast<UFightingSimulatorGameInstance>(GetGameInstance())->_uiManager;

	switch (_fightState)
	{
		case Beginn:
			UE_LOG(LogTemp, Warning, TEXT("Beginn"));
			if (_playerCreature->_speed >= _enemyCreature->_speed) 
			{
				ChangeFightState(PlayerAction);
			}
			else 
			{
				ChangeFightState(EnemyAttack);
			}
			break;
		case PlayerAction:
			UE_LOG(LogTemp, Warning, TEXT("PlayerAction"));
			if (uiManager)
			{
				uiManager->OpenAttackUI();
			}

			break;
		case PlayerAttack:
			UE_LOG(LogTemp, Warning, TEXT("PlayerAttack"));
			StartAttack(_playerCreature);
			break;
		case EnemyAttack:
			UE_LOG(LogTemp, Warning, TEXT("EnemyAttack"));
			StartAttack(_enemyCreature);
			break;
		case End:
			UE_LOG(LogTemp, Warning, TEXT("End"));
			if (uiManager)
			{
				uiManager->OpenEndUI();
			}
			break;
		default:
			break;
	}
}