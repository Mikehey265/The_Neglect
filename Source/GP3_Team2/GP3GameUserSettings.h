// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "GP3GameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class GP3_TEAM2_API UGP3GameUserSettings : public UGameUserSettings
{
	GENERATED_UCLASS_BODY()
	
private:
	UPROPERTY(Config)
	float GammaValue;

	UPROPERTY(Config)
	bool bHeadbob;

	UPROPERTY(Config)
	bool bCameraLag;

	UPROPERTY(Config)
	int ResolutionValue;

public:

	UFUNCTION(BlueprintCallable)
	static UGP3GameUserSettings* GetGameSettings();
	
	UFUNCTION(BlueprintCallable, Category="GameSettings")
	void SetGammaValue(float NewGammaValue);

	UFUNCTION(BlueprintPure, Category="GameSettings")
	float GetGammaValue() const;

	UFUNCTION(BlueprintCallable, Category="GameSettings")
	void SetHeadbobBool(bool NewBoolValue);
	
	UFUNCTION(BlueprintPure, Category="GameSettings")
	bool GetHeadbobValue() const;

	UFUNCTION(BlueprintCallable, Category="GameSettings")
	void SetCameraLagBool(bool NewBoolValue);
	
	UFUNCTION(BlueprintPure, Category="GameSettings")
	bool GetCameraLagValue() const;

	UFUNCTION(BlueprintCallable, Category="GameSettings")
	void SetResolution(int NewResolution);
	
	UFUNCTION(BlueprintPure, Category="GameSettings")
	int GetResolution() const;
};
