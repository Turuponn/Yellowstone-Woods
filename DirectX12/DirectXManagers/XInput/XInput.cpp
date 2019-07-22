#include "XInput.h"
#include <Xinput.h>
#include <Windows.h>
#include <iostream>


#pragma comment (lib, "xinput.lib")

using namespace std;


XInput::XInput() {

}
XInput::~XInput() {

}

void XInput::Init() {
	// get port
	int playerID = -1;
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	for (DWORD i = 0; i < XUSER_MAX_COUNT && playerID == -1; i++)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
			playerID = i;
	}

	if (playerID != -1)
	{
		// create gamepad
		cout << "use xinput controller" << endl;
	}
	else {
		cout<< "not controller" <<endl;
	}
}
