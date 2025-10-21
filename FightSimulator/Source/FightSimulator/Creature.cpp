// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"

// Sets default values
ACreature::ACreature()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeleton"));
	SkeletonMesh->AddToRoot();
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACreature::Die()
{
	_didDie = true;
	OnCreatureDiedSignal.Broadcast(this);
}

// Called every frame
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
		Damage = _maxHP * DamagePercent / 100;
	}
	else 
	{
		Damage = _currentHP * DamagePercent / 100;
	}
	
	GetDamaged(Damage);
}
