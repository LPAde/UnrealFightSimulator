#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

UCLASS()
class FIGHTSIMULATOR_API AUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AUIManager();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenCreatureSelectionScreen();

	void OpenCreatureSelectionScreen_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CloseCreatureSelectionScreen();

	void CloseCreatureSelectionScreen_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenAttackUI();

	void OpenAttackUI_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenEndUI();

	void OpenEndUI_Implementation();

};
