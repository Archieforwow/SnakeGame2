// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SnakeGame2Target : TargetRules
{
	public SnakeGame2Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

        ExtraModuleNames.AddRange( new string[] { "SnakeGame2" } );
	}
}
