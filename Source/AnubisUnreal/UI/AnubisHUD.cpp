// Made by sir Wok for AnubisUnreal project


#include "AnubisHUD.h"
#include "AttributesWidget.h"

void AAnubisHUD::Init()
{
	AttributesWidget = CreateWidget<UAttributesWidget>(GetOwningPlayerController(), AttributesWidgetClass);
	AttributesWidget->BindToAttributes();
	AttributesWidget->AddToViewport();
}
