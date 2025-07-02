// Vince Petrelli


#include "Controllers/FrontendPlayerController.h"

#include "Camera/CameraActor.h"
#include "FrontendSettings/FrontendGameUserSettings.h"
#include "Kismet/GameplayStatics.h"

void AFrontendPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	TArray<AActor*> FoundCameras; 
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), FoundCameras);
	if (!FoundCameras.IsEmpty())
	{
		SetViewTarget(FoundCameras[0]);
	}

	if (UFrontendGameUserSettings* GameUserSettings = UFrontendGameUserSettings::Get())
	{
		if (GameUserSettings->GetLastCPUBenchmarkResult() == -1.f || GameUserSettings->GetLastGPUBenchmarkResult() == -1.f)
		{
			GameUserSettings->RunHardwareBenchmark();
			GameUserSettings->ApplyHardwareBenchmarkResults();
		}
	}

	
}
