#include "Controller.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>

class Controller::ControllerImpl {

	int m_ControllerIndex;

	XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

public:
	ControllerImpl(int controllerIndex);
	~ControllerImpl() = default;

	ControllerImpl(const ControllerImpl& other) = delete;
	ControllerImpl(ControllerImpl&& other) = delete;
	ControllerImpl& operator=(const ControllerImpl& other) = delete;
	ControllerImpl& operator=(ControllerImpl&& other) = delete;

	void Update();
	bool IsPressed(unsigned int key) const;
	bool IsPressedThisFrame(unsigned int key) const;
	bool IsReleasedThisFrame(unsigned int key) const;
};



// XBoxController

Controller::Controller(int deviceID, int controllerIndex)
	: InputDevice(deviceID)
{
	pImpl = std::make_unique<ControllerImpl>(controllerIndex);
}

Controller::~Controller() = default;

void Controller::Update() {
	pImpl->Update();
}

bool Controller::IsPressed(unsigned int key) const {
	return pImpl->IsPressed(key);
}

bool Controller::IsPressedThisFrame(unsigned int key) const {
	return pImpl->IsPressedThisFrame(key);
}

bool Controller::IsReleasedThisFrame(unsigned int key) const {
	return pImpl->IsReleasedThisFrame(key);
}



// XboxControllerImpl

Controller::ControllerImpl::ControllerImpl(int controllerIndex)
	: m_ControllerIndex{ controllerIndex }
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
}

void Controller::ControllerImpl::Update() {
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & ~(m_CurrentState.Gamepad.wButtons);
}

bool Controller::ControllerImpl::IsPressed(unsigned int key) const {
	return m_CurrentState.Gamepad.wButtons & key;
}

bool Controller::ControllerImpl::IsPressedThisFrame(unsigned int key) const {
	return m_ButtonsPressedThisFrame & key;
}

bool Controller::ControllerImpl::IsReleasedThisFrame(unsigned int key) const {
	return m_ButtonsReleasedThisFrame & key;
}