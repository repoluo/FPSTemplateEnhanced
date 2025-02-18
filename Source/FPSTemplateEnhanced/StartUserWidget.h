// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "StartUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoginSuccess);

/**
 * 
 */
UCLASS()
class FPSTEMPLATEENHANCED_API UStartUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UEditableTextBox* UsernameTextBox;
	UEditableTextBox* PasswordTextBox;
	FString Username;
	FString Password;
	UButton* SignInButton;
	UButton* SignUpButton;
	
	bool AccountState; // true means sign in successfully, false means sign in failed, default is false
	bool RegisterState; // true means sign up successfully, false means sign up failed, default is false

protected:
	virtual void NativeConstruct() override;

	bool CheckAccountFile(FString FileName);
	bool SaveAccountFile(FString FileName);
	bool LoadAccountFile(FString FileName);
	
public:
	UStartUserWidget(const FObjectInitializer& ObjectInitializer);

	// function to bind to the sign in button
	UFUNCTION()
	void SignInButtonClicked();

	// function to bind to the sign up button
	UFUNCTION()
	void SignUpButtonClicked();

	UFUNCTION()
	bool GetAccountState() const;
	
	UFUNCTION()
	bool GetRegisterState() const;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLoginSuccess OnLoginSuccess;
	
};
