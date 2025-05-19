#include "stdafx.h"
#include "SetGameSpeed.h"

SetGameSpeed::SetGameSpeed()
{
}


SetGameSpeed::~SetGameSpeed()
{
}


void SetGameSpeed::ParseLine(const ArgScript::Line& line)
{
	//Get the argument.
	auto args = line.GetArguments(1);
	//Parse the argument as a float.
	float speed = mpFormatParser->ParseFloat(args[0]);

	//Using SetSpeedFactors(), set the last factor to be the specified speed,
	GameTimeManager.SetSpeedFactors(1.0, 2.0, 4.0, speed);
	//and then set the speed to be the last factor.
	GameTimeManager.SetSpeed(3);
	//Finally, set the factors back to vanilla.
	GameTimeManager.SetSpeedFactors(1.0, 2.0, 4.0, 8.0);
}

const char* SetGameSpeed::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Sets the current game speed. The default speed is 1.0.";
	}
	else {
		string str = "SetGameSpeed: Sets the active game speed to the value specified";
		str += "Usage: setGameSpeed speed";
		return str.c_str();
	}
}
