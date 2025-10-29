#include "FightManager.h"
#include "Creature.h"
#include "FightingSimulatorGameInstance.h"
#include "UIManager.h"

AFightManager::AFightManager()
{

}

void AFightManager::BeginPlay()
{
	Super::BeginPlay();


	Cast<UFightingSimulatorGameInstance>(GetGameInstance())->_fightManager = this;
}

void AFightManager::EndFight(ACreature* DeadCreature)
{
	ChangeFightState(End);
}

void AFightManager::StartAttack(ACreature* AttackingCreature, bool IsSpecial)
{
	_currentAttackType = IsSpecial ? AttackType::Special : AttackType::Normal;

	if (AttackingCreature == _playerCreature)
	{
		if (IsSpecial) 
			_playerCreature->PlaySpecialAttackAnimation();
		else
			_playerCreature->PlayAttackAnimation();
	}
	else
	{
		if (IsSpecial)
			_enemyCreature->PlaySpecialAttackAnimation();
		else
			_enemyCreature->PlayAttackAnimation();
	}
}

void AFightManager::Attack(ACreature* AttackingCreature, float Damage)
{
	if (AttackingCreature == _playerCreature) 
	{
		if (_currentAttackType == AttackType::Normal)
			_enemyCreature->GetDamaged(Damage);
		else
			_enemyCreature->GetDamaged(Damage, _playerCreature->_specialUsesMaxHP);
	}
	else
	{
		if (_currentAttackType == AttackType::Normal)
			_playerCreature->GetDamaged(Damage);
		else
			_playerCreature->GetDamaged(Damage, _enemyCreature->_specialUsesMaxHP);
	}
}

void AFightManager::DoPlayerAttack(bool IsSpecial)
{
	StartAttack(_playerCreature, IsSpecial);
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

void AFightManager::SetCreature(int CreatureID)
{
	if (!_playerCreature) 
	{
		_playerCreature = _allCreatures[CreatureID];
		_playerCreature->SetActorLocationAndRotation(_playerCreaturePosition->GetTargetLocation(), _playerCreaturePosition->GetActorRotation());

		// Setting up with the enemy creature delegates.
		_playerCreature->OnCreatureDiedSignal.AddDynamic(this, &AFightManager::EndFight);
		_playerCreature->OnCreatureTookDamageSignal.AddDynamic(this, &AFightManager::EndTurn);
		_playerCreature->OnFinishedAttackAnimationSignal.AddDynamic(this, &AFightManager::Attack);

		_playerCreature->SetupHealthBar();
	}
	else 
	{
		_enemyCreature = _allCreatures[CreatureID];
		_enemyCreature->SetActorLocationAndRotation(_enemyCreaturePosition->GetTargetLocation(), _enemyCreaturePosition->GetActorRotation());

		// Setting up with the enemy creature delegates.
		_enemyCreature->OnCreatureDiedSignal.AddDynamic(this, &AFightManager::EndFight);
		_enemyCreature->OnCreatureTookDamageSignal.AddDynamic(this, &AFightManager::EndTurn);
		_enemyCreature->OnFinishedAttackAnimationSignal.AddDynamic(this, &AFightManager::Attack);
		
		_enemyCreature->SetupHealthBar();

		_playerCreature->PlayEnterAnimation();
		_enemyCreature->PlayEnterAnimation();

		ChangeFightState(Beginn);
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

			Cast<UFightingSimulatorGameInstance>(GetGameInstance())->_uiManager->CloseCreatureSelectionScreen();

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
			break;

		case EnemyAttack:
			UE_LOG(LogTemp, Warning, TEXT("EnemyAttack"));
			// Randomly decide if enemy attack is special or not. Currently a 25% chance.
			StartAttack(_enemyCreature, FMath::RandRange(0, 3) == 0);
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