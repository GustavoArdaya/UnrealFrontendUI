// Vince Petrelli


#include "Widgets/Components/FrontendTabListWidgetBase.h"
#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"

void UFrontendTabListWidgetBase::RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName)
{
	
}

#if WITH_EDITOR
void UFrontendTabListWidgetBase::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!TabButtonEntryWidgetClass)
	{
		CompileLog.Error(FText::FromString(TEXT("No valid TabButtonEntryWidgetClass specified. ") +
			GetClass()->GetName() +
			TEXT(" needs a valid entry widget class to function properly")
		));
		
	}
}
#endif
