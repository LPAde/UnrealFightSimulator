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

UENUM(BlueprintType)
enum class AttackType : uint8 {
	Normal = 0 UMETA(DisplayName = "Normal"),
	Special = 1  UMETA(DisplayName = "Special")
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

	UPROPERTY(VisibleAnywhere)
	AttackType _currentAttackType;

	UFUNCTION()
	void EndFight(class ACreature* DeadCreature);

public:	

	UFUNCTION()
	void StartAttack(class ACreature* AttackingCreature, bool IsSpecial);

	UFUNCTION()
	void Attack(class ACreature* AttackingCreature, float Damage);

	UFUNCTION(BlueprintCallable)
	void DoPlayerAttack(bool IsSpecial);

	UFUNCTION()
	void EndTurn(class ACreature* HitCreature);

	UFUNCTION(BlueprintCallable)
	void SetCreature(int CreatureID);

	void ChangeFightState(FightState NewFightState);

#pragma region Outliner Values

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

#pragma endregion
};