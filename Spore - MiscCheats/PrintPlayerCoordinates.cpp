#include "stdafx.h"
#include "PrintPlayerCoordinates.h"

PrintPlayerCoordinates::PrintPlayerCoordinates()
{
}


PrintPlayerCoordinates::~PrintPlayerCoordinates()
{
}


void PrintPlayerCoordinates::ParseLine(const ArgScript::Line& line)
{
	if (GameNounManager.GetAvatar())
	{
		App::ConsolePrintF("Player creature coordinates: %f, %f, %f", GameNounManager.GetAvatar()->GetPosition());
	}

	else if (Simulator::GetPlayerUFO())
	{
		App::ConsolePrintF("Player UFO coordinates: %f, %f, %f", Simulator::GetPlayerUFO()->GetPosition());
	}

	else
	{
		App::ConsolePrintF("No coordinates found!");
	}
}

const char* PrintPlayerCoordinates::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Returns the current position of the player";
	}
	else {
		return "getPlayerCoordinates: This cheat returns the position of the player, either a creature or the player UFO in space-stage, to the cheat console.\n"
			"Usage: getPlayerCoordinates";
	}
}
