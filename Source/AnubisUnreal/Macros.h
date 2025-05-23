#pragma once
#include "DrawDebugHelpers.h"

#define PRINT_SCREEN(DebugMessage, ...) {  GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, FString::Printf(TEXT(DebugMessage), ##__VA_ARGS__));}
#define SPHERE(Center) if (GetWorld()) DrawDebugSphere(GetWorld(),Center,20.f,16,FColor::Blue, true)
#define SPHERE_TICK(Center, Radius) if (GetWorld()) DrawDebugSphere(GetWorld(),Center,Radius,16,FColor::Green, false)
#define SPHERE_TICK_COLOR(Center, Radius, Color) if (GetWorld()) DrawDebugSphere(GetWorld(),Center,Radius,16,Color, false)
#define LINE(LineStart, LineEnd) if (GetWorld()) DrawDebugLine(GetWorld(),LineStart,LineEnd,FColor::Blue, true)
#define LINE_TICK(LineStart, LineEnd) if (GetWorld()) DrawDebugLine(GetWorld(),LineStart,LineEnd,FColor::Green, false)
#define LINE_TICK_COLOR(LineStart, LineEnd, Color) if (GetWorld()) DrawDebugLine(GetWorld(),LineStart,LineEnd,Color, false)