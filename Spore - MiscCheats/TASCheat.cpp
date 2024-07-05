#include "stdafx.h"
#include "TASCheat.h"

TASCheat::TASCheat()
{
	mbIsPaused = false;
	mbDelayPause = false;
	App::AddUpdateFunction(this);
}


TASCheat::~TASCheat()
{
}


void TASCheat::ParseLine(const ArgScript::Line& line)
{
	if (line.HasFlag("pause"))
	{
		mbIsPaused = true;
		return;
	}
	if (line.HasFlag("unpause"))
	{
		Unpause();
		return;
	}
	if (line.HasFlag("nextframe"))
	{
		NextFrame();
		return;
	}
	if (line.HasFlag("nextInputFrame"))
	{
		NextFrame();
		mbDelayPause = true;
		return;
	}
	App::ConsolePrintF("Invalid option.");
}

void TASCheat::Unpause()
{
	mbIsPaused = false;
	int length = GameTimeManager.GetPauseCount(Simulator::TimeManagerPause::Gameplay);
	for (int i = 0; i < length; i++)
	{
		GameTimeManager.Resume(Simulator::TimeManagerPause::Gameplay);
	}
}

void TASCheat::NextFrame()
{
	int length = GameTimeManager.GetPauseCount(Simulator::TimeManagerPause::Gameplay);
	for (int i = 0; i < length; i++)
	{
		GameTimeManager.Resume(Simulator::TimeManagerPause::Gameplay);
	}
}

void TASCheat::Update()
{

	if (mbIsPaused)
	{
		if (mbDelayPause)
		{
			mbDelayPause = false;
			return;
		}
		if (!GameTimeManager.IsPaused())
		{
			GameTimeManager.Pause(Simulator::TimeManagerPause::Gameplay);
		}
	}
}

const char* TASCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "TASCheat: Elaborate description of what this cheat does.";
	}
}


int TASCheat::AddRef()
{
	return DefaultRefCounted::AddRef();
}

int TASCheat::Release()
{
	return DefaultRefCounted::Release();
}

int TASCheat::GetReferenceCount()
{
	return DefaultRefCounted::GetReferenceCount();
}