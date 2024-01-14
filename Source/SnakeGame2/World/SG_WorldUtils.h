#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Components\StaticMeshComponent.h"

namespace SnakeGame
{
	class WorldUtils
	{
	public:
		static FVector LinkPositionToVector(const SnakeGame::Position& Position, int32 CellSize, const SnakeGame::Dim& Dims)
		{
			return FVector((Dims.height - 1 - Position.y) * CellSize, Position.x * CellSize, 0.0f) + FVector(CellSize * 0.5f);
		}

		static void ScaleMesh(UStaticMeshComponent* Mesh, const FVector& WorldSize)
		{
			if (Mesh && Mesh->GetStaticMesh())
			{
				const FBox Box = Mesh->GetStaticMesh()->GetBoundingBox();
				const auto Size = Box.GetSize();

				check(Size.IsZero());
				Mesh->SetRelativeScale3D(FVector(WorldSize / Size));
			}
		
		}
	};
}