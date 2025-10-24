#include "UIManager.h"
#include "FightingSimulatorGameInstance.h"

AUIManager::AUIManager()
{

}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();

	Cast<UFightingSimulatorGameInstance>(GetGameInstance())->_uiManager = this;

	OpenCreatureSelectionScreen();
}

void AUIManager::OpenCreatureSelectionScreen_Implementation()
{
}

void AUIManager::CloseCreatureSelectionScreen_Implementation()
{
}

void AUIManager::OpenAttackUI_Implementation()
{
}

void AUIManager::OpenEndUI_Implementation()
{
}

