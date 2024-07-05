#pragma once

#include <Spore\BasicIncludes.h>

class SkipSpaceTutorial 
	: public ArgScript::ICommand
{
public:
	SkipSpaceTutorial();
	~SkipSpaceTutorial();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;

private:
	void GiveSpaceItem(uint32_t id);
};

