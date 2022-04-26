#include "BetterWindow.h"

IMod* BMLEntry(IBML* bml) {
	return new BetterWindow(bml);
}

void BetterWindow::OnLoad() {
	// Get window's handle
	m_window = (HWND)m_bml->GetRenderContext()->GetWindowHandle();
	m_im = m_bml->GetInputManager();

	GetConfig()->SetCategoryComment("Mode", "Mod Settings.");
	auto_mode = GetConfig()->GetProperty("Mode", "AutoEnable");
	auto_mode->SetComment("Auto block input when out of focus.");
	auto_mode->SetDefaultBoolean(true);

	disable_ime = GetConfig()->GetProperty("Mode", "DisableIME");
	disable_ime->SetComment("Disable ingame IME. Restart game to apply it.");
	disable_ime->SetDefaultBoolean(true);

	hot_key = GetConfig()->GetProperty("Mode", "HotKey");
	hot_key->SetComment("Hot key to block input forcibly.");
	hot_key->SetDefaultKey(CKKEY_F4);

	tip_lable = std::make_unique<BGui::Label>("L_key_to_block");
	tip_lable->SetFont(ExecuteBB::GAMEFONT_01);
	tip_lable->SetPosition(Vx2DVector(0.0f, 0.05f));
	tip_lable->SetSize(Vx2DVector(1.0f, 0.0353f));
	tip_lable->SetAlignment(ALIGN_CENTER);
	tip_lable->SetText("INPUT BLOCKED");

	if (disable_ime->GetBoolean()) {
		// Get input context for backup. 
		HIMC m_hImc = ImmGetContext(m_window);
		// Remove association the testing 
		if (m_hImc)
			ImmAssociateContext(m_window, NULL);
		// Release input context
		ImmReleaseContext(m_window, m_hImc);
	}
}

void BetterWindow::OnProcess() {
	if (m_window == GetFocus() && GetKeyState(18) < 0 && GetKeyState(115) < 0) m_bml->ExitGame(); // Alt + F4

	if (m_im->oIsKeyPressed(hot_key->GetKey())) key_to_block ^= true; // Switch

	if (m_im->oIsKeyPressed(CKKEY_SLASH)) m_cmdTyping = true;
	if (m_cmdTyping && (m_im->oIsKeyPressed(CKKEY_RETURN) || m_im->oIsKeyPressed(CKKEY_ESCAPE))) m_cmdTyping = false;

	tip_lable->SetVisible(key_to_block);
	tip_lable->Process();

	InputHook::SetBlock(key_to_block || m_cmdTyping || (auto_mode->GetBoolean() && m_window != GetFocus()));
}
