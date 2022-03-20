#include "BetterWindow.h"

IMod* BMLEntry(IBML* bml) {
	return new BetterWindow(bml);
}

void BetterWindow::OnLoad() {
	// Get window's handle
	m_window = (HWND)m_bml->GetRenderContext()->GetWindowHandle();
	m_im = m_bml->GetInputManager();
}

void BetterWindow::OnProcess() {
	if (GetKeyState(18) < 0 && GetKeyState(115) < 0) m_bml->ExitGame(); // Alt + F4

	if (m_im->oIsKeyPressed(CKKEY_SLASH)) m_cmdTyping = true;
	if (m_cmdTyping && (m_im->oIsKeyPressed(CKKEY_RETURN) || m_im->oIsKeyPressed(CKKEY_ESCAPE))) m_cmdTyping = false;

	InputHook::SetBlock(m_cmdTyping || m_window != GetFocus());
}
