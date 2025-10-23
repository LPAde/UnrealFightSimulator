#include "UIManager.h"
#include "FightingSimulatorGameInstance.h"

AUIManager::AUIManager()
{

}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();

	Cast<UFightingSimulatorGameInstance>(GetGameInstance())->_uiManager = this;
}

void AUIManager::OpenAttackUI_Implementation()
{
}

void AUIManager::OpenEndUI_Implementation()
{
}

