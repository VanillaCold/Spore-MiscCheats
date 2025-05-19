#include "stdafx.h"
#include "ChangeEditorModel.h"

ChangeEditorModel::ChangeEditorModel()
{
}


ChangeEditorModel::~ChangeEditorModel()
{
}


void ChangeEditorModel::ParseLine(const ArgScript::Line& line)
{
	if (GameModeManager.GetActiveModeID() == GameModeIDs::kEditorMode)
	{
		// Only send the "is cheater" message when you're in the editor.
		// since it only works in the editor.
		MessageManager.MessageSend(CheatManager.kMsgCheatInvoked, nullptr);
		auto request = Sporepedia::ShopperRequest(this);
		request.Show(request);
	}

	// This method is called when your cheat is invoked.
	// Put your cheat code here.
}

const char* ChangeEditorModel::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "ChangeEditorModel: Elaborate description of what this cheat does.";
	}
}

void ChangeEditorModel::OnShopperAccept(const ResourceKey& selection)
{
	if (selection == ResourceKey(0, 0, 0))
	{
		return;
	}
	ResourceObjectPtr resource;
	ResourceManager.GetResource(selection, &resource);
	if (resource)
	{
		auto editorRes = (Editors::cEditorResource*)(resource.get()); // it's always gonna be an editor resource.
		Editors::EditorModel* model = new Editors::EditorModel();
		model->Load(editorRes);
		Editor.SetEditorModel(model);
	}
}
