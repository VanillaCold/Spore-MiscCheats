#include "stdafx.h"
#include "RemoveItem.h"

RemoveItem::RemoveItem()
{
}


RemoveItem::~RemoveItem()
{
}


void RemoveItem::ParseLine(const ArgScript::Line& line)
{
    auto args = line.GetArguments(1);
    uint32_t selected = id(args[0]);

    Simulator::cStarRecord* star = Simulator::GetActiveStarRecord();

    if (line.HasFlag("id"))
    {
        selected = mpFormatParser->ParseUInt(args[0]);
    }

    if (Simulator::IsScenarioMode())
    {
        Simulator::cStarRecord* star = StarManager.GetScenarioStar();
    }

    auto inventory = SimulatorSpaceGame.GetPlayerInventory();
    if (auto tool = inventory->GetTool(ResourceKey(selected,0,0)))
    {
        if (Simulator::IsSpaceGame() || (Simulator::IsScenarioMode() && star->mKey.internalValue != -1))
        {
            inventory->RemoveItem(tool);
        }
        else 
        { 
            App::ConsolePrintF("You need to be playing in the Space Stage (in/out of an adventure) to run this command.");
        }
    }
    else { App::ConsolePrintF("No valid tool specified."); }
}

const char* RemoveItem::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Removes the specified tool from your inventory in the space-stage";
	}
    else {
        return "RemoveItem: This cheat removes a tool based on the name, or hash, inputted.\n"
        "If the -id flag is specified, the input is interpreted as a hash. Otherwise, it is used as a filename.\n"
        "Usage: removeItem [toolName/toolHash] [-id]";
    }
}
