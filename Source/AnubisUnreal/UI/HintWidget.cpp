// Made by sir Wok for AnubisUnreal project


#include "HintWidget.h"

void UHintWidget::SetHintText(const FText& InText)
{
	if (HintTextBlock)
	{
		HintTextBlock->SetText(InText);
	}
}