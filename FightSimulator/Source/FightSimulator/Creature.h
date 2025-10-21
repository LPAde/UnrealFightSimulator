// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Creature.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreatureDiedSignal, ACreature*, DeadCreature);

UCLASS()
class FIGHTSIMULATOR_API ACreature : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACreature();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Die();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    void GetDamaged(float Damage);
	void GetDamaged(float DamagePercent, bool UsesMaxHP);

	FCreatureDiedSignal OnCreatureDiedSignal;
	USkeletalMeshComponent* SkeletonMesh;

#pragma region CreatureStats
	UPROPERTY(VisibleAnywhere)
	float _maxHP;

	UPROPERTY(VisibleAnywhere)
	float _currentHP;

	UPROPERTY(VisibleAnywhere)
	float _damageMultiplier;

	UPROPERTY(VisibleAnywhere)
	float _armor;

	UPROPERTY(VisibleAnywhere)
	int _speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _didDie;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _didAttack;
#pragma endregion
};