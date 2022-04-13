#pragma once

#include <memory>
#include <BML/BMLAll.h>

extern "C" {
	__declspec(dllexport) IMod* BMLEntry(IBML* bml);
}

class BetterWindow : public IMod {
public:
	BetterWindow(IBML* bml) : IMod(bml) {}

	virtual CKSTRING GetID() override { return "BetterWindow"; }
	virtual CKSTRING GetVersion() override { return BML_VERSION; }
	virtual CKSTRING GetName() override { return "Better Window"; }
	virtual CKSTRING GetAuthor() override { return "Ghomist"; }
	virtual CKSTRING GetDescription() override { return "Better Window for Ballance.\nBlock input when Ballance is not focused."; }
	DECLARE_BML_VERSION;
	virtual void OnLoad();
	virtual void OnProcess();

private:
	HWND m_window = NULL;
	bool m_cmdTyping = false;
	InputHook* m_im = nullptr;
	IProperty* auto_mode = nullptr;
	IProperty* hot_key = nullptr;
	bool key_to_block = false;
	std::unique_ptr<BGui::Label> tip_lable = nullptr;
};