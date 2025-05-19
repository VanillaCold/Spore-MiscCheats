#include "stdafx.h"
#include "GiveItem.h"
#include <Spore\Simulator.h>
#include <Spore\Properties.h>

GiveItem::GiveItem()
{
}


GiveItem::~GiveItem()
{
}


void GiveItem::ParseLine(const ArgScript::Line& line)
{
    cSpaceToolDataPtr tool;
    size_t numArgs;
    auto args = line.GetArguments(2);
    uint32_t selected = id(args[0]);

    if (line.HasFlag("id"))
    {
        selected = mpFormatParser->ParseUInt(args[0]);
    }

    if (!PropManager.HasPropertyList(selected, GroupIDs::SpaceTools))
    {
        App::ConsolePrintF("No valid tool specified.");
        return;
    }

    ToolManager.LoadTool({ selected, 0, 0 }, tool);

    auto ammo = clamp(mpFormatParser->ParseInt(args[1]), 0, tool->mMaxAmmoCount);

    Simulator::cStarRecord* star = Simulator::GetActiveStarRecord();

    if (Simulator::IsScenarioMode())
    {
        Simulator::cStarRecord* star = StarManager.GetScenarioStar();
    }

    if (tool != nullptr) 
    {
        if (Simulator::IsSpaceGame() || (Simulator::IsScenarioMode() && star->mKey.internalValue != -1) )
        {
            tool->mCurrentAmmoCount = ammo;
            auto inventory = SimulatorSpaceGame.GetPlayerInventory();
            inventory->AddItem(tool.get());
        }
        else 
        { 
            App::ConsolePrintF("You need to be playing in the Space Stage (in/out of an adventure) to run this command."); 
        }
    }
    else 
    { 
        App::ConsolePrintF("No valid tool specified."); 
    }
}

const char* GiveItem::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Gives you the space-stage tool, based on its tool ID.";
	}
	else {
		string str = "GiveItem: This cheat gives you a tool based on the name, or hash, inputted.\n";
        str += "If the -id flag is specified, the input is interpreted as a hash. Otherwise, it is used as a filename.";
        str += "Usage: giveitem [toolName/toolHash] [-id]";
        return str.c_str();
	}
}
