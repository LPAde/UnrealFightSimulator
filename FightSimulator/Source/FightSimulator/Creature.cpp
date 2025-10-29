#include "Creature.h"

ACreature::ACreature()
{
}

void ACreature::BeginPlay()
{
	Super::BeginPlay();
	
	_currentHP = _maxHP;
}

void ACreature::GetDamaged(float Damage)
{
	UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);
	UE_LOG(LogTemp, Warning, TEXT("Armor: %f"), _armor);
	float RealDamage = Damage - _armor;

	// Making sure you always deal at least one damage.
	if (RealDamage < 0)
		RealDamage = 1;

	_currentHP -= RealDamage;

	if (_currentHP <= 0) 
	{
		_currentHP = 0;
		PlayDeathAnimation();
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
	UE_LOG(LogTemp, Warning, TEXT("SpecialAttackStrength: %f"), DamagePercent);
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

void ACreature::SetupHealthBar_Implementation()
{

}

#pragma region Animation Methods

void ACreature::PlayAttackAnimation()
{
	_didAttack = true;
}

void ACreature::PlaySpecialAttackAnimation()
{
	_didSpecialAttack = true;
}

void ACreature::PlayEnterAnimation()
{
	_didEnter = true;
	SetupHealthBar();
}

void ACreature::PlayDeathAnimation()
{
	_didDie = true;
}

#pragma endregion

#pragma region Broadcast Methods

void ACreature::BroadcastTookDamageSignal()
{
	OnCreatureTookDamageSignal.Broadcast(this);
}

void ACreature::BroadcastDiedSignal()
{
	OnCreatureDiedSignal.Broadcast(this);
}

void ACreature::BroadcastFinishedAttackSignal(bool IsSpecial)
{
		OnFinishedAttackAnimationSignal.Broadcast(this, IsSpecial ? _damageMultiplier : _damage);
}

#pragma endregion