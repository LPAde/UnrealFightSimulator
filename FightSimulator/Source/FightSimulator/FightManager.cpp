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

}

void AFightManager::BeginPlay()
{
	Super::BeginPlay();

	// Setting up with the creature delegates.
	_playerCreature->OnCreatureDiedSignal.AddDynamic(this, &AFightManager::EndFight);
	_enemyCreature->OnCreatureDiedSignal.AddDynamic(this, &AFightManager::EndFight);
	_playerCreature->OnCreatureTookDamageSignal.AddDynamic(this, &AFightManager::EndTurn);
	_enemyCreature->OnCreatureTookDamageSignal.AddDynamic(this, &AFightManager::EndTurn);
	_playerCreature->OnFinishedAttackAnimationSignal.AddDynamic(this, &AFightManager::Attack);
	_enemyCreature->OnFinishedAttackAnimationSignal.AddDynamic(this, &AFightManager::Attack);

	Cast<UFightingSimulatorGameInstance>(GetGameInstance())->_fightManager = this;

	// Temp code before the creature selection is implemented.
	DELAY(3.0f,
	{
			ChangeFightState(Beginn);
	})
}

void AFightManager::EndFight(ACreature* DeadCreature)
{
	ChangeFightState(End);
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

/// <summary>
/// Changes the current fight state and acts accordingly. 
/// </summary>
/// <param name="NewFightState"> The fight state the manager should switch to. </param>
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

		case None:
		default:
			break;
	}
}