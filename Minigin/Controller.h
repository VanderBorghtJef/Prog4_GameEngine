#pragma once
#include "InputDevice.h"
#include <memory>

class Controller final : public InputDevice
{
public:

	// Old school enum so they are automatically converted to int when applicable
	enum ControllerButton {
		DPAD_UP = 0x0001,
		DPAD_DOWN = 0x0002,
		DPAD_LEFT = 0x0004,
		DPAD_RIGHT = 0x0008,
		BUTTON_START = 0x0010,
		BUTTON_BACK = 0x0020,
		LEFT_THUMB = 0x0040,
		RIGHT_THUMB = 0x0080,
		LEFT_SHOULDER = 0x0100,
		RIGHT_SHOULDER = 0x0200,
		BUTTON_A = 0x1000,
		BUTTON_B = 0x2000,
		BUTTON_X = 0x4000,
		BUTTON_Y = 0x8000,
	};

	Controller(int deviceID, int controllerIndex);
	~Controller();

	Controller(const Controller& other) = delete;
	Controller(Controller&& other) = delete;
	Controller& operator=(const Controller& other) = delete;
	Controller& operator=(Controller&& other) = delete;

	void Update() override;
	bool IsPressed(unsigned int key) const override;
	bool IsPressedThisFrame(unsigned int key) const override;
	bool IsReleasedThisFrame(unsigned int key) const override;

private:

	class ControllerImpl;
	std::unique_ptr<ControllerImpl> pImpl;
};

