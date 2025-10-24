#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Creature.generated.h"

#pragma region Delegates

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreatureDiedSignal, ACreature*, DeadCreature);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreatureTookDamageSignal, ACreature*, HitCreature);

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFinishedAttackAnimationSignal, ACreature*, AttackingCreature, float, DamageMultiplier);

#pragma endregion

UCLASS()
class FIGHTSIMULATOR_API ACreature : public APawn
{
	GENERATED_BODY()
	
public:	
	ACreature();

protected:
	virtual void BeginPlay() override;
	void Die();

public:	
    void GetDamaged(float Damage);
	void GetDamaged(float DamagePercent, bool UsesMaxHP);
	void PlayAttackAnimation();
	void PlayEnterAnimation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetupHealthBar();

	void SetupHealthBar_Implementation();

#pragma region Broadcast Functions

	UFUNCTION(BlueprintCallable)
	void BroadcastTookDamageSignal();

	UFUNCTION(BlueprintCallable)
	void BroadcastDiedSignal();

	UFUNCTION(BlueprintCallable)
	void BroadcastFinishedAttackSignal();

#pragma endregion

#pragma region Signals

	FCreatureTookDamageSignal OnCreatureTookDamageSignal;
	FCreatureDiedSignal OnCreatureDiedSignal;
	FFinishedAttackAnimationSignal OnFinishedAttackAnimationSignal;

#pragma endregion

#pragma region Stats

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _maxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _currentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _damageMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _speed;

#pragma endregion

#pragma region AnimationBools

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _didDie;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _didAttack;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _didGetHit;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool _didEnter;

#pragma endregion
};