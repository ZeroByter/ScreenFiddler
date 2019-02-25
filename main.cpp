#include "payloads.h"
#define concat(first, second) first second

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void ShowHelp() {
	std::cout << " -h or -help = shows this message" << std::endl;
	std::cout << "list of possible effects" << std::endl;

	for (int i = 0; i < nPayloads; i++) {
		PAYLOAD &payload = payloads[i];

		std::cout << " -" << payload.name << " = " << payload.desc << std::endl;
	}
}

int main(int argc, char **argv) {
	//check if user wants help
	for (int i = 1; i < argc; i++) {
		char* arg = argv[i];

		if (strcmp(arg, "-h") == 0 || strcmp(arg, "-help") == 0) {
			ShowHelp();
			return 0;
		}
	}

	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	std::vector<PAYLOAD> selectedPayloads = std::vector<PAYLOAD>();

	//user doesn't want help, time to add all his selected payloads
	for (int i = 1; i < argc; i++) {
		char* arg = argv[i];

		for (int j = 0; j < nPayloads; j++) {
			PAYLOAD &payload = payloads[j];

			if (strcmp(arg, ("-" + (std::string)payload.name).c_str()) == 0) selectedPayloads.push_back(payload);
		}
	}

	if (selectedPayloads.size() == 0) return 0;

	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);

	//setting up font stuff
	HGDIOBJ hFont = GetStockObject(DEFAULT_GUI_FONT);
	LOGFONT logfont;
	GetObject(hFont, sizeof(LOGFONT), &logfont);
	logfont.lfHeight = 60; //font size

	HFONT hNewFont = CreateFontIndirect(&logfont);

	SelectObject(hdc, hNewFont);

	SetTextColor(hdc, 0x000000FF);
	SetBkMode(hdc, TRANSPARENT);

	int width = 0;
	int height = 0;
	GetDesktopResolution(width, height);

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	while (true) {
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		for (std::vector<int>::size_type i = 0; i != selectedPayloads.size(); i++) {
			PAYLOAD &payload = selectedPayloads[i];
			
			if (payload.delaytime++ >= payload.delay) {
				payload.delay = ((PAYLOADFUNCTION((*)))payload.payloadFuncion)(hwnd, hdc, width, height, fElapsedTime);
				payload.delaytime = 0;
			}

			Sleep(1);
		}

		for (int button = 0x41; button < 0x5A; button++) {
			if (GetAsyncKeyState(button) & 0x8000) {
				return 0;
			}
		}
	}

	return 0;
}