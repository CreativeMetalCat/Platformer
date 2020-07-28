// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpNavLinkProxy.h"


bool AJumpNavLinkProxy::ShouldJump(AActor* agent)
{
	TArray<FNavigationLink> NavLinks;
	TArray<FNavigationSegmentLink> NavSegmentLinks;
	if (GetNavigationLinksArray(NavLinks, NavSegmentLinks))
	{
		for (int i = 0; i < NavLinks.Num(); i++)
		{
			
			NavLinks[i].Left;
			NavLinks[i].Right;
		}
	}
	return false;
}
