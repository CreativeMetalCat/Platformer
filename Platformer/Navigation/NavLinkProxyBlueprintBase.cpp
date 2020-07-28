// Fill out your copyright notice in the Description page of Project Settings.


#include "NavLinkProxyBlueprintBase.h"
#include "NavLinkCustomComponent.h"

FVector ANavLinkProxyBlueprintBase::GetRightPoint(bool& Exists)
{
	return GetRightPointForSpecificLink(0, Exists);
}

FVector ANavLinkProxyBlueprintBase::GetLeftPoint(bool& Exists)
{
	return GetLeftPointForSpecificLink(0, Exists);
}

FVector ANavLinkProxyBlueprintBase::GetLeftPointForSpecificLink(int id, bool& Exists)
{
	TArray<FNavigationLink> NavLinks;
	TArray<FNavigationSegmentLink> NavSegmentLinks;
	if (GetNavigationLinksArray(NavLinks, NavSegmentLinks))
	{
		if (NavLinks.IsValidIndex(id))
		{
			Exists = true;
			return NavLinks[id].Left;
		}
	}

	Exists = false;
	return FVector(0, 0, 0);
}

FVector ANavLinkProxyBlueprintBase::GetRightPointForSpecificLink(int id, bool& Exists)
{
	TArray<FNavigationLink> NavLinks;
	TArray<FNavigationSegmentLink> NavSegmentLinks;
	if (GetNavigationLinksArray(NavLinks, NavSegmentLinks))
	{
		if (NavLinks.IsValidIndex(id))
		{
			Exists = true;
			return NavLinks[id].Right;
		}
	}

	Exists = false;
	return FVector(0,0,0);
}
