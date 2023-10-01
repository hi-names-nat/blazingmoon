// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueData.h"


bool UDialogueData::GetParagraph(FString& Chunk, int32 Index)
{
	if (DialogueEntry.Num() == Index) return false;
	auto Str = DialogueEntry[Index];
	Chunk = Str;
	return true;
}
