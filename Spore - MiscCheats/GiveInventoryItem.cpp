#include "stdafx.h"
#include "GiveInventoryItem.h"

GiveInventoryItem::GiveInventoryItem()
{
}


GiveInventoryItem::~GiveInventoryItem()
{
}


void GiveInventoryItem::ParseLine(const ArgScript::Line& line)
{
    cSpaceInventoryItemPtr item;
    size_t numArgs;
    auto args = line.GetArguments(2);
    uint32_t selected = id(args[0]);

    if (line.HasFlag("id"))
    {
        selected = mpFormatParser->ParseUInt(args[0]);
    }

    //ToolManager.LoadTool({ selected, 0, 0 }, tool);

    auto ammo = clamp(mpFormatParser->ParseInt(args[1]), 0, 99);

    Simulator::cStarRecord* star = Simulator::GetActiveStarRecord();

    if (Simulator::IsScenarioMode())
    {
        Simulator::cStarRecord* star = StarManager.GetScenarioStar();
    }

    if (Simulator::IsSpaceGame() || (Simulator::IsScenarioMode() && star->mKey.internalValue != -1))
    {
        SpaceTrading.ObtainTradingObject(ResourceKey(selected,TypeIDs::prop,GroupIDs::SpaceTrading_),ammo);
    }
    else
    {
        App::ConsolePrintF("You need to be playing in the Space Stage (in/out of an adventure) to run this command.");
    }
}

const char* GiveInventoryItem::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "GiveInventoryItem: Elaborate description of what this cheat does.";
	}
}
