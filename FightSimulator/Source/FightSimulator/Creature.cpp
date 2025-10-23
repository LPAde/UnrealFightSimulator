#include "Creature.h"

ACreature::ACreature()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACreature::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACreature::Die()
{
	_didDie = true;
}

void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACreature::GetDamaged(float Damage)
{
	_currentHP -= (Damage - _armor);

	if (_currentHP <= 0) 
	{
		_currentHP = 0;
		Die();
	}
	else 
	{
		// Only does the animation when it survived the attack.
		_didGetHit = true;
	}
}

/// <summary>
/// Damages the creature with a percentage based attack.
/// </summary>
/// <param name="DamagePercent"> The percent of relative health the damage deals. As a whole number 0-100. </param>
/// <param name="UsesMaxHP"> Is this damage based on max health or current health? </param>
void ACreature::GetDamaged(float DamagePercent, bool UsesMaxHP)
{
	float Damage;

	if (UsesMaxHP) 
	{
		Damage = _maxHP * DamagePercent * 0.01f;
	}
	else 
	{
		Damage = _currentHP * DamagePercent * 0.01f;
	}
	
	GetDamaged(Damage);
}

void ACreature::PlayAttackAnimation()
{
	_didAttack = true;
}


void ACreature::BroadcastTookDamageSignal()
{
	OnCreatureTookDamageSignal.Broadcast(this);
}

void ACreature::BroadcastDiedSignal()
{
	OnCreatureDiedSignal.Broadcast(this);
}

void ACreature::BroadcastFinishedAttackSignal()
{
	OnFinishedAttackAnimationSignal.Broadcast(this, _damageMultiplier);
}
