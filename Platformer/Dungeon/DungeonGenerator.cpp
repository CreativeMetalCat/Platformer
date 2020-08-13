// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "DungeonLevelScriptActorBase.h"
#include "Engine.h"

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
 	//it's one time shot actor, no need to tick
	PrimaryActorTick.bCanEverTick = false;
	EditorBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorBillboard"));
	SetRootComponent(EditorBillboard);
	EditorBillboard->bHiddenInGame = true;
}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonGenerator::Generate()
{
	if (StartingPointActor != nullptr) { StartingPoint = StartingPointActor->GetActorLocation(); }

	if (RoomLevelNames.Num() > 0)
	{
		TArray<int>RoomIds;
		int prevId = -1;
		for (int i = 0; i < RoomsYAmount; i++)
		{
			for (int u = 0; u < RoomsXAmount; u++)
			{
				int id = FMath::RandRange(0, RoomLevelNames.Num() - 1);
				/*while (id == prevId || bNotUseRandomnessCheck)
				{
					id = FMath::RandRange(0, RoomLevelNames.Num() - 1);
				}*/
				prevId = id;
				RoomIds.Add(id);//for now we just generate array of this things

				//bool success = false;
				//ULevelStreamingKismet::LoadLevelInstance(GetWorld(), RoomLevelNames[id], FVector(StartingPoint.X, StartingPoint.Y + u * MinDistanceBetweenRooms * -1, StartingPoint.Z + i * MinHeightBetweenRooms * -1), FRotator::ZeroRotator, success);
			}
		}

	}
	if (RoomLevelNames.Num() > 0)
	{
		TArray<FCellData>Cells;
		for (int i = 0; i < RoomsYAmount; i++)
		{
			for (int u = 0; u < RoomsXAmount; u++)
			{
				Cells.Add(FCellData::CreateCellData(FVector2D(u, i)));//filling up dungeon info
			}
		}

		//using that info
		int rInt = FMath::RandRange(0, 1);//0 is for right, 1 is for down,2 is for up, 4 is for left(we always start in the same place - top left corner)
		FVector2D CurrentPos = FVector2D(0, 0);
		TArray<FCellData>VisitedCells;
		TArray<FCellData>Path;
		bool notMadeMove = true;
		Path.Add(FCellData::CreateCellData(FVector2D(0, 0)));
		if (rInt == 1)
		{
			int checkId = FCellData::GetCellIdInArray(Cells, FVector2D(CurrentPos.X + 1, CurrentPos.Y));
			if (!Cells[checkId].Visited)
			{
				int id = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it started
				Cells[id].HasRightWall = false;
				Cells[id].Visited = true;

				CurrentPos.X += 1;
				id = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it's now
				Cells[id].HasLeftWall = false;
				Cells[id].Visited = true;

				Path.Add(FCellData::CreateCellData(CurrentPos));
				notMadeMove = false;
			}
		}
		else if (rInt == 0)
		{
			int checkId = FCellData::GetCellIdInArray(Cells, FVector2D(CurrentPos.X, CurrentPos.Y + 1));
			if (!Cells[checkId].Visited)
			{
				int startId = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it started
				Cells[startId].HasDownWall = false;
				Cells[startId].Visited = true;



				CurrentPos.Y += 1;
				int id = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it's now
				Cells[id].HasUpWall = false;
				Cells[id].Visited = true;

				Cells[startId].idOfDropChild = id;
				Cells[id].idOfUpperParent = startId;

				Path.Add(FCellData::CreateCellData(CurrentPos));
				notMadeMove = false;
			}
		}

		int testInt = 10;
		while (CurrentPos != FVector2D(0, 0)/* && testInt > 0*/)
		{
			UE_LOG(LogTemp, Warning, TEXT("New loop loop"));
			notMadeMove = true;
			while (notMadeMove)
			{

				rInt = FMath::RandRange(0, 3);


				if (FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X + 1, CurrentPos.Y)) && FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X - 1, CurrentPos.Y)) && FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X, CurrentPos.Y + 1)) && FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X, CurrentPos.Y - 1)))
				{
					//for debug
					bool RightCellVisitedOrBlocked = FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X + 1, CurrentPos.Y));
					bool DownCellVisitedOrBlocked = FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X, CurrentPos.Y + 1));
					bool LeftCellVisitedOrBlocked = FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X - 1, CurrentPos.Y));
					bool UpperCellVisitedOrBlocked = FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X, CurrentPos.Y - 1));

					int RightId = FCellData::GetCellIdInArray(Cells, FVector2D(CurrentPos.X + 1, CurrentPos.Y));
					int LefttId = FCellData::GetCellIdInArray(Cells, FVector2D(CurrentPos.X - 1, CurrentPos.Y));
					int UpId = FCellData::GetCellIdInArray(Cells, FVector2D(CurrentPos.X, CurrentPos.Y + 1));
					int DownId = FCellData::GetCellIdInArray(Cells, FVector2D(CurrentPos.X, CurrentPos.Y - 1));
					//for debug end

					Cells[FCellData::GetCellIdInArray(Cells, CurrentPos)].DeadEnd = true;

					notMadeMove = false;
					CurrentPos = Path[Path.Num() - 2].Location;//can not move anywhere, moving one pos back
					Path.RemoveAt(Path.Num() - 1);
					break;
				}

				if (rInt == 1)
				{
					if (!FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X + 1, CurrentPos.Y)))
					{
						int id = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it started
						Cells[id].HasRightWall = false;
						Cells[id].Visited = true;

						CurrentPos.X += 1;
						id = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it's now
						Cells[id].HasLeftWall = false;
						Cells[id].Visited = true;

						Path.Add(FCellData::CreateCellData(CurrentPos));
						notMadeMove = false;
						break;
					}
				}
				else if (rInt == 0)
				{
					if (!FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X, CurrentPos.Y + 1)))
					{
						int startId = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it started
						Cells[startId].HasDownWall = false;
						Cells[startId].Visited = true;



						CurrentPos.Y += 1;
						int id = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it's now
						Cells[id].HasUpWall = false;
						Cells[id].Visited = true;

						Cells[startId].idOfDropChild = id;
						Cells[id].idOfUpperParent = startId;

						Path.Add(FCellData::CreateCellData(CurrentPos));
						notMadeMove = false;
						break;
					}
				}
				else if (rInt == 2)
				{
					if (!FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X, CurrentPos.Y - 1)))
					{
						int startId = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it started
						Cells[startId].HasUpWall = false;
						Cells[startId].Visited = true;

						CurrentPos.Y -= 1;
						int id = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it's now
						Cells[id].HasDownWall = false;
						Cells[id].Visited = true;

						Cells[id].idOfDropChild = startId;
						Cells[startId].idOfUpperParent = id;

						Path.Add(FCellData::CreateCellData(CurrentPos));
						notMadeMove = false;
						break;
					}
				}
				else if (rInt == 3)
				{
					if (!FCellData::IsCellVisited(Cells, FVector2D(CurrentPos.X - 1, CurrentPos.Y)))
					{
						int id = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it started
						Cells[id].HasLeftWall = false;
						Cells[id].Visited = true;

						CurrentPos.X -= 1;
						id = FCellData::GetCellIdInArray(Cells, CurrentPos);//currenty it's the one where it's now
						Cells[id].HasRightWall = false;
						Cells[id].Visited = true;

						Path.Add(FCellData::CreateCellData(CurrentPos));
						notMadeMove = false;
						break;
					}
				}
			}
			testInt--;
		}

		for (int i = 0; i < Cells.Num(); i++)
		{
			//FVector(StartingPoint.X, StartingPoint.Y + u * MinDistanceBetweenRooms * -1, StartingPoint.Z + i * MinHeightBetweenRooms * -1)
			if (CorridorClasses.Num() > 0)
			{
				ADungeonRoomBase* room = GetWorld()->SpawnActor<ADungeonRoomBase>(CorridorClasses[0], FVector(StartingPoint.X, StartingPoint.Y + Cells[i].Location.X * (CorridorLenght + RoomLenght) * -1, StartingPoint.Z + Cells[i].Location.Y * MinHeightBetweenRooms * -1), FRotator::ZeroRotator);
				if (room != nullptr)
				{
					GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, "X for " + FString::FromInt(i) + " is " + FString::FromInt(Cells[i].Location.X));
					//GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, "Y for " + FString::FromInt(i) + " is " + FString::FromInt(Cells[i].Location.Y));
					room->HasDownWall = Cells[i].HasDownWall;
					room->HasUpWall = Cells[i].HasUpWall;
					room->HasRightWall = Cells[i].HasRightWall;
					room->HasLeftWall = (i != 0) ? Cells[i].HasLeftWall : false;//the first one always doesn't have left wall because it's entrance
					room->bIsDeadEnd = Cells[i].DeadEnd;
					room->IdOfDropEnd = Cells[i].idOfDropChild;
					room->IdOfDropStart = Cells[i].idOfUpperParent;
					room->bIsDrop = (Cells[i].idOfDropChild != -1 || Cells[i].idOfUpperParent != -1);
					if (Corridors.IsValidIndex(Cells[i].idOfUpperParent))
					{
						room->DropStart = (Cells[i].idOfUpperParent == -1) ? nullptr : Corridors[Cells[i].idOfUpperParent];
					}
					room->GenerateWalls();

					Corridors.Add(room);
				}

				if (RoomLevelNames.Num() > 0)
				{
					int id = FMath::RandRange(0, RoomLevelNames.Num() - 1);

					bool success = false;
					ULevelStreamingDynamic* level = ULevelStreamingKismet::LoadLevelInstance(GetWorld(), RoomLevelNames[id], FVector(StartingPoint.X, StartingPoint.Y + (Cells[i].Location.X * (CorridorLenght + RoomLenght) * -1) - CorridorLenght - RoomSpawnOffset, StartingPoint.Z + Cells[i].Location.Y * MinHeightBetweenRooms * -1), FRotator::ZeroRotator, success);

					ADungeonLevelScriptActorBase* levelScript = Cast<ADungeonLevelScriptActorBase>(level->GetLevelScriptActor());//the reason why i love Unreal Engine
					
					if (levelScript != nullptr)
					{
						levelScript->RoomId = i;//level itself will deal with setting and checking everything else
					}
	
					StreamedLevels.Add(level);
				}

			}
		}
	}
}