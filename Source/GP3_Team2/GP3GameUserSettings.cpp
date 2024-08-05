// Fill out your copyright notice in the Description page of Project Settings.


#include "GP3GameUserSettings.h"

UGP3GameUserSettings::UGP3GameUserSettings(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	GammaValue = 2.2f;
	bHeadbob = true;
	bCameraLag = true;
	ResolutionValue = 1;
}

UGP3GameUserSettings* UGP3GameUserSettings::GetGameSettings()
{
	return Cast<UGP3GameUserSettings>(GetGameUserSettings());
}

void UGP3GameUserSettings::SetGammaValue(float NewGammaValue)
{
	GammaValue = NewGammaValue;
}

float UGP3GameUserSettings::GetGammaValue() const
{
	return GammaValue;
}

void UGP3GameUserSettings::SetHeadbobBool(bool NewBoolValue)
{
	bHeadbob = NewBoolValue;
}

bool UGP3GameUserSettings::GetHeadbobValue() const
{
	return bHeadbob;
}

void UGP3GameUserSettings::SetCameraLagBool(bool NewBoolValue)
{
	bCameraLag = NewBoolValue;
}

bool UGP3GameUserSettings::GetCameraLagValue() const
{
	return bCameraLag;
}

void UGP3GameUserSettings::SetResolution(int NewResolution)
{
	ResolutionValue = NewResolution;
}

int UGP3GameUserSettings::GetResolution() const
{
	return ResolutionValue;
}


