// Vince Petrelli


#include "Subsystems/FrontendLoadingScreenSubsystem.h"

#include "FrontendDebugHelper.h"
#include "PreLoadScreenManager.h"
#include "FrontendSettings/FrontendLoadingScreenSettings.h"

bool UFrontendLoadingScreenSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}
	return false;
}

void UFrontendLoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	FCoreUObjectDelegates::PreLoadMapWithContext.AddUObject(this, &UFrontendLoadingScreenSubsystem::OnMapPreloaded);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UFrontendLoadingScreenSubsystem::OnMapPostLoaded);
}

void UFrontendLoadingScreenSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PreLoadMapWithContext.RemoveAll(this);
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
}

UWorld* UFrontendLoadingScreenSubsystem::GetTickableGameObjectWorld() const
{
	if (UGameInstance* OwningGameInstance = GetGameInstance())
	{
		return OwningGameInstance->GetWorld();
	}
	return nullptr;
}

void UFrontendLoadingScreenSubsystem::Tick(float DeltaTime)
{
	TryUpdateLoadingScreen();
}

ETickableTickType UFrontendLoadingScreenSubsystem::GetTickableTickType() const
{
	if (IsTemplate())
	{
		return ETickableTickType::Never;
	}
	
	return ETickableTickType::Conditional;
}

bool UFrontendLoadingScreenSubsystem::IsTickable() const
{
	return GetGameInstance() && GetGameInstance()->GetGameViewportClient(); 
}

TStatId UFrontendLoadingScreenSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UFrontendLoadingScreenSubsystem, STATGROUP_Tickables);
}

void UFrontendLoadingScreenSubsystem::OnMapPreloaded(const FWorldContext& WorldContext, const FString& MapName)
{
	if (WorldContext.OwningGameInstance != GetGameInstance()) return;

	SetTickableTickType(ETickableTickType::Conditional);
	bIsCurrentlyLoadingMap = true;

	TryUpdateLoadingScreen();
}

void UFrontendLoadingScreenSubsystem::OnMapPostLoaded(UWorld* LoadedWorld)
{
	if (LoadedWorld && LoadedWorld->GetGameInstance() == GetGameInstance())
	{
		bIsCurrentlyLoadingMap = false;
	}
}

void UFrontendLoadingScreenSubsystem::TryUpdateLoadingScreen()
{
	// Check for active startup loading screen
	if (IsPreLoadScreenActive()) return;
	
	if (ShouldDisplayLoadingScreen())
	{
		// Check if loading screen should be displayed		
	}
	else
	{
		// Try to remove active loading screen

		// Notify loading complete

		// Disable ticking
		SetTickableTickType(ETickableTickType::Never);
	}	
}

bool UFrontendLoadingScreenSubsystem::IsPreLoadScreenActive()
{
	if (FPreLoadScreenManager* PreLoadScreenManager = FPreLoadScreenManager::Get())
	{
		return PreLoadScreenManager->HasValidActivePreLoadScreen();
	}
	return false;
}

bool UFrontendLoadingScreenSubsystem::ShouldDisplayLoadingScreen()
{
	const UFrontendLoadingScreenSettings* LoadingScreenSettings = GetDefault<UFrontendLoadingScreenSettings>();
	if (GIsEditor && !LoadingScreenSettings->bShouldShowLoadingScreenInEditor)
	{
		return false;
	}

	// Check if objects in the world need a loading screen
	if (CheckIfShowingLoadingScreenNeeded())
	{
		GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = true;
		return true;
	}
	// Allow the world to be rendered in viewport
	GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = false;

	const float CurrentTime = FPlatformTime::Seconds();

	if (HoldLoadingScreenStartUpTime < 0.f)
	{
		HoldLoadingScreenStartUpTime = CurrentTime;
	}

	const float ElapsedTime = CurrentTime - HoldLoadingScreenStartUpTime;

	if (ElapsedTime < LoadingScreenSettings->HoldLoadingScreenExtraSeconds)
	{
		return true;
	}

	return false;
}

bool UFrontendLoadingScreenSubsystem::CheckIfShowingLoadingScreenNeeded()
{
}
