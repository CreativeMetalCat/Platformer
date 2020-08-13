// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "CellData.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FCellData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool HasUpWall = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool HasDownWall = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool HasRightWall = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool HasLeftWall = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Visited = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool DeadEnd = false;

	//Id of start of the drop
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int idOfUpperParent = -1;

	//Id of the end of the drop
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int idOfDropChild = -1;

	FCellData()
	{
		
	}

	static FCellData CreateCellData(FVector2D Location)		
	{
		FCellData result;
		result.Location = Location;
		return result;
	}

	static int GetCellIdInArray(TArray<FCellData>Cells, FVector2D loc)
	{
		if (Cells.Num() > 0)
		{
			for (int i = 0; i < Cells.Num(); i++)
			{
				if (Cells[i].Location == loc) { return i; }
			}
		}
		return -1;
	}

	//returns true if visited, border
	//return false if not visited or border or if arry is empty
	static bool IsCellVisited(TArray<FCellData>Cells, FVector2D loc)
	{
		if (Cells.Num() > 0)
		{
			int id = FCellData::GetCellIdInArray(Cells, loc);
			if (id == -1) { return true;/*it's out of bounds so we don't want to go there, so we mark it as visited for the generator*/ }
			else
			{
				return Cells[id].Visited;
			}

		}
		return false;
	}
};