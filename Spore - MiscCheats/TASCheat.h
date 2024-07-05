#pragma once

#include <Spore\BasicIncludes.h>

class TASCheat 
	: public ArgScript::ICommand
	, public App::IUpdatable
	, public DefaultRefCounted
{
public:
	TASCheat();
	~TASCheat();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;

	void Unpause();
	void NextFrame();

	bool mbIsPaused;
	bool mbDelayPause;

	void Update() override;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;

	virtual int AddRef() override;
	virtual int Release() override;
	virtual int GetReferenceCount() override;
};

