#include "stdafx.h"
#include "SkipSpaceTutorial.h"
#include <Spore/Simulator/cMissionManager.h>

SkipSpaceTutorial::SkipSpaceTutorial()
{
}


SkipSpaceTutorial::~SkipSpaceTutorial()
{
}


void SkipSpaceTutorial::ParseLine(const ArgScript::Line& line)
{
	//Skip if not in space-stage.
	if (!Simulator::IsSpaceGame())
	{
		App::ConsolePrintF("Cheat must be used in the space-stage.");
	}

	//Constant array to iterate through, with all tutorial missions.
	const vector<string> b = { "TutorialFlight101","TutorialFlight101_VisitCities","TutorialFlight101_Scan","tutorialflight101_fetchanimal","TutorialFlight101_EradicateAnimals", "TutorialStory201"};

	//Initialize a flag to determine whether or not to give the tools.
	bool hasDoneAnything = false;
	
	//For each of the missions,
	for each (string str in b)
	{
		//Get the mission if it is loaded.
		auto mission = MissionManager.GetMissionByID(id(str.c_str()));
		if (mission)
		{
			//Set the flag to true; this makes sure all tools will be given.
			hasDoneAnything = true;
			//Print the message if compiled as debug.
			SporeDebugPrint("%x", mission);
			//End the mission by calling the same method as the devMission cheat,
			mission->FailMission();
			//and then call the method that makes the mission disappear from the log.
			//This also is done by devMission, so it's repeated here.
			mission->SetState(Simulator::MissionState::Completed);

			//CALL(Address(0x00c48740), void, Args(int*), Args((int*)mission));
		}
	}

	//If the cheat has finished any missions,
	if (hasDoneAnything)
	{
		//simply give all of the tools to the user.
		GiveSpaceItem(id("scan"));
		GiveSpaceItem(id("dropcargo"));
		GiveSpaceItem(id("abduct"));
		GiveSpaceItem(id("laserlevel1"));
		GiveSpaceItem(id("interplanetarydrive"));
		GiveSpaceItem(id("seti"));
		GiveSpaceItem(id("protonmissilelevel1"));
		GiveSpaceItem(id("interstellardrive"));
	}
	else
	{
		//If not, then tell the user that no tutorial missions were found.
		App::ConsolePrintF("No initial tutorial missions are currently active.\nThese missions are TutorialFlight101 (including its sub-missions) and TutorialStory201.");
	}
}

const char* SkipSpaceTutorial::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Skips the space-stage tutoral.";
	}
	else {
		return "SkipSpaceTutorial: Skips all currently-active space stage tutorial missions that are mandatory.";
	}
}

void SkipSpaceTutorial::GiveSpaceItem(uint32_t id)
{
	cSpaceToolDataPtr pTool;
	ToolManager.LoadTool(ResourceKey(id, 0, 0), pTool);
	SimulatorSpaceGame.GetPlayerInventory()->AddItem(pTool.get());
}
