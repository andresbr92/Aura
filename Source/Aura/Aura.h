// AndresD3v

#pragma once

#include "CoreMinimal.h"

#define CUSTOM_DEPTH_RED 250
#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel1;
#define CONSOLE_LOG(Format, ...) UE_LOG(LogTemp, Log, TEXT("%s: " Format), *FString(__FUNCTION__), ##__VA_ARGS__)