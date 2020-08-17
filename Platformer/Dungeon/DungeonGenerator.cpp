// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "DungeonLevelScriptActorBase.h"
#include "Kismet/GameplayStatics.h"

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
	gameInstance = Cast<UPlatformerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonGenerator::Generate()
{
	if (StartingPointActor != nullptr) { StartingPoint = StartingPointActor->GetActorLocation(); }
	if (gameInstance != nullptr)
	{
		gameInstance->CurrentSpawnedLevelId = 0;

		RoomsXAmount = gameInstance->DungeonData.SizeX;
		RoomsYAmount = gameInstance->DungeonData.SizeY;
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

			if (CorridorClasses.Num() > 0)
			{
				ADungeonRoomBase* room = GetWorld()->SpawnActor<ADungeonRoomBase>(CorridorClasses[0], FVector(StartingPoint.X, StartingPoint.Y + Cells[i].Location.X * (CorridorLenght + RoomLenght) * -1, StartingPoint.Z + Cells[i].Location.Y * MinHeightBetweenRooms * -1), FRotator::ZeroRotator);
				if (room != nullptr)
				{

					Cells[i].Id = i;
					room->HasDownWall = Cells[i].HasDownWall;
					room->HasUpWall = Cells[i].HasUpWall;
					/*we do that because we want rooms to be always accesable. it's a test,so probably will be changed*/
					room->HasRightWall = false; //Cells[i].HasRightWall;
					room->HasLeftWall = (i != 0) ? Cells[i].HasLeftWall : false;//the first one always doesn't have left wall because it's entrance
					if (i == 0) { Cells[i].HasLeftWall = false; }
					room->bIsDeadEnd = Cells[i].DeadEnd;
					room->IdOfDropEnd = Cells[i].idOfDropChild;
					room->IdOfDropStart = Cells[i].idOfUpperParent;
					room->bIsDrop = (Cells[i].idOfDropChild != -1 || Cells[i].idOfUpperParent != -1);
					if (Corridors.IsValidIndex(Cells[i].idOfUpperParent))
					{
						room->DropStart = (Cells[i].idOfUpperParent == -1) ? nullptr : Corridors[Cells[i].idOfUpperParent];
					}
					room->RoomId = i;
					room->GenerateWalls();

					Corridors.Add(room);
				}

				if ((i == Cells.Num() - 1) && EndRoomLevelNames.Num() > 0)
				{
					SpawnRoom(EndRoomLevelNames, Cells[i].Location.X, Cells[i].Location.Y, ERoomType::ERT_Default,i);
				}

				else if (SpawnedShops < MaxShopsPerDungeon && ItemLevelNames.Num()  > 0 && FMath::RandRange(0, 100) < ChanceOfItemRoomSpawn + 10)//30% percent chance of getting it
				{

					if (SpawnRoom(ItemLevelNames, Cells[i].Location.X, Cells[i].Location.Y, ERoomType::ERT_Store,i))
					{
						SpawnedShops++;
					}
				}
				else if (SpawnedChests < MaxChestsPerDungeon && ItemLevelNames.Num()  > 0 && FMath::RandRange(0, 100) < ChanceOfItemRoomSpawn + 5)//40% percent chance of getting it
				{

					if (SpawnRoom(ItemLevelNames, Cells[i].Location.X, Cells[i].Location.Y, ERoomType::ERT_Chest,i))
					{
						SpawnedChests++;
					}
				}


				else if (RoomLevelNames.Num() > 0)
				{
					SpawnRoom(RoomLevelNames, Cells[i].Location.X, Cells[i].Location.Y, ERoomType::ERT_Default,i);
				}

				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "WorldGen Error: No rooms to spawn!");
				}
			}

		}
		if (gameInstance != nullptr)
		{
			gameInstance->Corridors = Cells;//for mini-map generation

			//save important data abount dungeon -- start

			

			//save important data abount dungeon -- end
		}
		GetWorldTimerManager().SetTimer(StreamedLevelInitTimer, this, &ADungeonGenerator::InitStreamedLevels, 3.f, false);
	}
}


void ADungeonGenerator::InitStreamedLevels()
{
	if (StreamedLevels.Num() > 0)
	{
		
		ADungeonLevelScriptActorBase* levelScript;
		if (gameInstance != nullptr)
		{
			for (int i = 0; i < StreamedLevels.Num(); i++)
			{
				levelScript = nullptr;
				if (StreamedLevels[i]->GetLevelScriptActor() != nullptr)
				{
					levelScript = Cast<ADungeonLevelScriptActorBase>(StreamedLevels[i]->GetLevelScriptActor());

					if (levelScript != nullptr)
					{
						levelScript->RoomId = i;//level itself will deal with setting and checking everything else
						
						if (i != 0)//first one is too close to properly react so we load it from the beggining
						{
							levelScript->DisableAllActorsInLevel();//disabling from the beggining
						}
						if (gameInstance != nullptr)
						{
							levelScript->RoomType = gameInstance->Rooms[i].RoomType;

						}
						levelScript->SetLevelsOrderId(i);
						levelScript->Init();
					}
					else
					{
						
					}
					//we add this struct for keeping data			
				}
				else
				{
					
				}
			}
		}
	}
}

bool ADungeonGenerator::SpawnRoom(TArray<FString> LevelNames,int LocationX,int LocationY,ERoomType roomType, int id)
{
	if (LevelNames.Num() > 0)
	{
		int id = FMath::RandRange(0, LevelNames.Num() - 1);

		bool success = false;
		FVector SpawnLocation = FVector(StartingPoint.X, StartingPoint.Y + (LocationX * (CorridorLenght + RoomLenght) * -1) - CorridorLenght - RoomSpawnOffset, StartingPoint.Z + LocationY * MinHeightBetweenRooms * -1);
		ULevelStreamingDynamic* level = ULevelStreamingKismet::LoadLevelInstance(GetWorld(), LevelNames[id], SpawnLocation, FRotator::ZeroRotator, success);

		if (success)
		{
			if (gameInstance != nullptr)
			{
				FDungeonRoomData data = FDungeonRoomData::CreateRoomData();
				data.RoomType = roomType;
				data.Location = SpawnLocation;
				data.Id = id;
				gameInstance->Rooms.Add(data);
			}
			StreamedLevels.Add(level);
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "WorldGen Error: Failed to load level: " + LevelNames[id]);
			return false;
		}
	}
	return false;
}

