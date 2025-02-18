// Fill out your copyright notice in the Description page of Project Settings.


#include "StartUserWidget.h"
#include "HAL/PlatformFileManager.h"


void UStartUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct()"));

	if (UButton* TempButton = Cast<UButton>(GetWidgetFromName(TEXT("SignInButton"))))
	{
		SignInButton = TempButton;
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, "SignInButtonClicked");
		SignInButton->OnClicked.Add(ScriptDelegate);
	}
	if (UButton* TempButton = Cast<UButton>(GetWidgetFromName(TEXT("SignUpButton"))))
	{
		SignUpButton = TempButton;
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, "SignUpButtonClicked");
		SignUpButton->OnClicked.Add(ScriptDelegate);
	}
	if (UEditableTextBox* TempTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Username"))))
	{
		UsernameTextBox = TempTextBox;
	}
	if (UEditableTextBox* TempTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Password"))))
	{
		PasswordTextBox = TempTextBox;
	}
}

bool UStartUserWidget::CheckAccountFile(FString FileName)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.FileExists(*FileName);
}

bool UStartUserWidget::SaveAccountFile(FString FileName)
{
	TArray<FString> AccountData;
	AccountData.Add(Username);
	AccountData.Add(Password);
	if (!FFileHelper::SaveStringArrayToFile(AccountData, *FileName, FFileHelper::EEncodingOptions::ForceUTF8))
	{
		UE_LOG(LogTemp, Warning, TEXT("[File: %s] Failed to save account file!"), *FileName);
		return false;
	}
	return true;
}

bool UStartUserWidget::LoadAccountFile(FString FileName)
{
	TArray<FString> AccountData;
	if (!FFileHelper::LoadFileToStringArray(AccountData, *FileName))
	{
		UE_LOG(LogTemp, Warning, TEXT("[File: %s] Failed to load account file!"), *FileName);
		return false;
	}
	if (AccountData.Num() < 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("[File: %s] Account file is corrupted!"), *FileName);
		return false;
	}
	Username = AccountData[0];
	Password = AccountData[1];
	
	return true;
}

UStartUserWidget::UStartUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SignInButton = nullptr;
	SignUpButton = nullptr;
	UsernameTextBox = nullptr;
	PasswordTextBox = nullptr;

	AccountState = false;
	RegisterState = false;
}

void UStartUserWidget::SignInButtonClicked()
{
	if (!UsernameTextBox || !PasswordTextBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("Get UsernameTextBox or PasswordTextBox failed!"));
		return;
	}

	// get the username and password from the text boxes
	FString UsernameGottenFromTextBox = UsernameTextBox->GetText().ToString();
	FString PasswordGottenFromTextBox = PasswordTextBox->GetText().ToString();

	if (UsernameGottenFromTextBox.IsEmpty() || PasswordGottenFromTextBox.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Username or Password is empty!"));
		return;
	}

	// file path
	FString Filename = FPaths::ProjectContentDir() + TEXT("Account/") + UsernameGottenFromTextBox + TEXT(".txt");

	// check if the account file exists
	if (!CheckAccountFile(Filename))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s's account does not exist!"), *UsernameGottenFromTextBox);
		return;
	}

	// load the account file
	if (!LoadAccountFile(Filename))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load %s's account file!"), *UsernameGottenFromTextBox);
		return;
	}

	// check if the password is correct
	if (Password != PasswordGottenFromTextBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s's Password is incorrect!"), *UsernameGottenFromTextBox);
		return;
	}

	// sign in successfully
	AccountState = true;
	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Red, TEXT("Sign in Successfully"), false);

	OnLoginSuccess.Broadcast();

	RemoveFromParent();
}

void UStartUserWidget::SignUpButtonClicked()
{
	if (!UsernameTextBox || !PasswordTextBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("Get UsernameTextBox or PasswordTextBox failed!"));
		return;
	}

	// get the username and password from the text boxes
	FString UsernameGottenFromTextBox = UsernameTextBox->GetText().ToString();
	FString PasswordGottenFromTextBox = PasswordTextBox->GetText().ToString();

	if (UsernameGottenFromTextBox.IsEmpty() || PasswordGottenFromTextBox.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Username or Password is empty!"));
		return;
	}

	// file path
	FString Filename = FPaths::ProjectContentDir() + TEXT("Account/") + UsernameGottenFromTextBox + TEXT(".txt");

	// check if the account file exists
	if (CheckAccountFile(Filename))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s's account already exists!"), *UsernameGottenFromTextBox);
		return;
	}

	this->Username = UsernameGottenFromTextBox;
	this->Password = PasswordGottenFromTextBox;

	// save the account file
	if (!SaveAccountFile(Filename))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to save %s's account file!"), *UsernameGottenFromTextBox);
		return;
	}

	// sign up successfully
	RegisterState = true;
	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Red, TEXT("Sign up Successfully"), false);
}

bool UStartUserWidget::GetAccountState() const
{
	return AccountState;
}

bool UStartUserWidget::GetRegisterState() const
{
	return RegisterState;
}
