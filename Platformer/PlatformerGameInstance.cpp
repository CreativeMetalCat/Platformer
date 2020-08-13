// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerGameInstance.h"

bool UPlatformerGameInstance::IsRoomCompleted(int RoomId)
{
	if (Rooms.Num() > 0)
	{
		return Rooms[RoomId].bCompleted;
	}
	return false;
}

void UPlatformerGameInstance::MarkRoomAsCompleted(int RoomId)
{
	if (Rooms.Num() > 0)
	{
		Rooms[RoomId].bCompleted = true;
	}
}
