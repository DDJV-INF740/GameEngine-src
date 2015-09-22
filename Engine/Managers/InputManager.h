#pragma once
#include "Components/InputComponent.h"
#include <vector>
#include <algorithm>
#include <assert.h>

class InputManager
{
private:
	InputManager() {}

public:
	static InputManager Instance;

	void onKeyDown(int iVirtualKey)
	{
		for (auto iter = _inputInterfaces.begin(); iter != _inputInterfaces.end(); ++iter)
		{
			IKeyboardInputInterface* keyboardInterface = dynamic_cast<IKeyboardInputInterface*>(*iter);
			if (keyboardInterface != nullptr)
			{
				keyboardInterface->onKeyDown(iVirtualKey);
			}
		}
	}

	void onKeyUp(int iVirtualKey)
	{
		for (auto iter = _inputInterfaces.begin(); iter != _inputInterfaces.end(); ++iter)
		{
			IKeyboardInputInterface* keyboardInterface = dynamic_cast<IKeyboardInputInterface*>(*iter);
			if (keyboardInterface != nullptr)
			{
				keyboardInterface->onKeyUp(iVirtualKey);
			}
		}
	}

	void addComponent(IInputInterface *iInputInterface)
	{
		_inputInterfaces.push_back(iInputInterface);
	}

	void removeComponent(IInputInterface *iInputInterface)
	{
		auto wFound = std::find(_inputInterfaces.begin(), _inputInterfaces.end(), iInputInterface);
		ASSERT(wFound != _inputInterfaces.end());
		_inputInterfaces.erase(wFound);
	}

	void update();

private:
	std::vector<IInputInterface*> _inputInterfaces;
};