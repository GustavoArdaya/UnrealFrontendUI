// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendLoadingScreenSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendLoadingScreenSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadingReasonUpdatedDelegate, const FString&, CurrentLoadingReason);

	UPROPERTY(BlueprintAssignable)
	FOnLoadingReasonUpdatedDelegate OnLoadingReasonUpdated;
	
	// ~ Begin USubsystem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// ~ End USubsystem Interface

	// ~ Begin FTickableGameObject Interface
	virtual UWorld* GetTickableGameObjectWorld() const override;
	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// ~ End FTickableGameObject Interface

private:

	UFUNCTION()
	void OnMapPreloaded(const FWorldContext& WorldContext, const FString& MapName);

	UFUNCTION()
	void OnMapPostLoaded(UWorld*  LoadedWorld);

	void TryUpdateLoadingScreen();

	bool IsPreLoadScreenActive();

	bool ShouldDisplayLoadingScreen();

	bool CheckIfShowingLoadingScreenNeeded();

	void TryDisplayLoadingScreenIfNone();

	void TryRemoveLoadingScreen();

	void NotifyLoadingScreenVisibilityChanged(bool bIsVisible);

	bool bIsCurrentlyLoadingMap = false;

	float HoldLoadingScreenStartUpTime = -1.f;

	FString CurrentLoadingReason;

	TSharedPtr<SWidget> CachedCreatedLoadingScreenWidget;
};
