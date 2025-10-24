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
	End = 4,
	None = 5
};



UCLASS()
class FIGHTSIMULATOR_API AFightManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AFightManager();

protected:
	virtual void BeginPlay() override;
	FightState _fightState;
	UFUNCTION()
	void EndFight(class ACreature* DeadCreature);

public:	

	UFUNCTION()
	void StartAttack(class ACreature* AttackingCreature);
	UFUNCTION()
	void Attack(class ACreature* AttackingCreature, float DamageMultiplier);

	UFUNCTION(BlueprintCallable)
	void DoPlayerAttack();

	UFUNCTION()
	void EndTurn(class ACreature* HitCreature);

	UFUNCTION(BlueprintCallable)
	void SetCreature(int CreatureID);

	void ChangeFightState(FightState NewFightState);

	UPROPERTY(EditAnywhere)
	class ACreature* _playerCreature;
	UPROPERTY(EditAnywhere)
	class ACreature* _enemyCreature;

	UPROPERTY(EditAnywhere)
	class AActor* _playerCreaturePosition;
	
	UPROPERTY(EditAnywhere)
	class AActor* _enemyCreaturePosition;

	UPROPERTY(EditAnywhere)
	TArray<class ACreature*> _allCreatures;

	UPROPERTY(EditAnywhere)
	float _baseDamage;
};


