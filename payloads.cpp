#include "payloads.h"

PAYLOAD payloads[] = {
	Payload("bouncingError", "Bouncing error on the screen", (LPVOID)bouncingError),
	Payload("basicTunnel", "basic tunnel effect", (LPVOID)basicTunnel),
	Payload("fastTunnel", "like 'basicTunnel', but much faster", (LPVOID)fastTunnel),
	Payload("cursorErrors", "error icons on your cursor", (LPVOID)cursorErrors),
	Payload("cursorIcons", "like 'cursorErrors', but more random", (LPVOID)cursorIcons),
	Payload("pwnedText", "u have been pwned", (LPVOID)pwnedText),
	Payload("randomPwnedText", "like 'pwnedText', but more random", (LPVOID)randomPwnedText),
	Payload("randomIcons", "a bunch of random icons everywhere", (LPVOID)randomIcons),
	Payload("fastRandomIcons", "like 'randomIcons', but much faster (warning, this could lag your computer)", (LPVOID)fastRandomIcons),
	Payload("screenBleed", "bleeds your screen...", (LPVOID)screenBleed),
	Payload("swigglyScreenBleed", "bleeds your screen... but more swiggly...", (LPVOID)swigglyScreenBleed),
	Payload("inverseColors", "epilepsy madness", (LPVOID)inverseColors),
};
const size_t nPayloads = sizeof(payloads) / sizeof(PAYLOAD);

float bouncingErrorsX = -1;
float bouncingErrorsY = -1;
float bouncingErrorsVelX = 400;
float bouncingErrorsVelY = 0;

PAYLOADFUNCTION(bouncingError) {
	if (bouncingErrorsX == -1) {
		bouncingErrorsX = width / 2;
		bouncingErrorsY = height / 2;
	}

	int ix = GetSystemMetrics(SM_CXICON) / 2;
	int iy = GetSystemMetrics(SM_CYICON) / 2;

	DrawIcon(hdc, bouncingErrorsX - ix, bouncingErrorsY - iy, LoadIcon(NULL, IDI_ERROR));

	bouncingErrorsX += bouncingErrorsVelX * fElapsedTime;
	bouncingErrorsY += bouncingErrorsVelY * fElapsedTime;

	if (bouncingErrorsX < 0 || bouncingErrorsX > width) bouncingErrorsVelX *= -1.4;

	//too much power! we got to limit it's power!
	if (bouncingErrorsVelX > 600) bouncingErrorsVelX = 600;
	if (bouncingErrorsVelX < -600) bouncingErrorsVelX = -600;

	bouncingErrorsVelY += 6000 * fElapsedTime;
	if (bouncingErrorsY > height) {
		bouncingErrorsVelY *= -1.005f;
	}

	return 1;
}

PAYLOADFUNCTION(basicTunnel) {
	StretchBlt(hdc, 50, 50, width - 100, height - 100, hdc, 0, 0, width, height, SRCCOPY);

	return 300;
}

PAYLOADFUNCTION(fastTunnel) {
	StretchBlt(hdc, 50, 50, width - 100, height - 100, hdc, 0, 0, width, height, SRCCOPY);

	return 1;
}

PAYLOADFUNCTION(inverseColors) {
	BitBlt(hdc, 0, 0, width, height, hdc, 0, 0, NOTSRCCOPY);

	return 50;
}

PAYLOADFUNCTION(cursorErrors) {
	int ix = GetSystemMetrics(SM_CXICON) / 2;
	int iy = GetSystemMetrics(SM_CYICON) / 2;

	POINT cursor;
	GetCursorPos(&cursor);

	DrawIcon(hdc, cursor.x - ix, cursor.y - iy, LoadIcon(NULL, IDI_ERROR));

	return 1;
}

PAYLOADFUNCTION(cursorIcons) {
	int ix = GetSystemMetrics(SM_CXICON) / 2;
	int iy = GetSystemMetrics(SM_CYICON) / 2;

	POINT cursor;
	GetCursorPos(&cursor);

	int random = rand() % 4;
	int randomPos = 100;

	if (random == 0) {
		DrawIcon(hdc, cursor.x - ix + (rand() % randomPos + randomPos / 2) - randomPos, cursor.y - iy + (rand() % randomPos + randomPos / 2) - randomPos, LoadIcon(NULL, IDI_ERROR));
	}
	else if (random == 1) {
		DrawIcon(hdc, cursor.x - ix + (rand() % randomPos + randomPos / 2) - randomPos, cursor.y - iy + (rand() % randomPos + randomPos / 2) - randomPos, LoadIcon(NULL, IDI_ASTERISK));
	}
	else if (random == 2) {
		DrawIcon(hdc, cursor.x - ix + (rand() % randomPos + randomPos / 2) - randomPos, cursor.y - iy + (rand() % randomPos + randomPos / 2) - randomPos, LoadIcon(NULL, IDI_INFORMATION));
	}
	else if (random == 3) {
		DrawIcon(hdc, cursor.x - ix + (rand() % randomPos + randomPos / 2) - randomPos, cursor.y - iy + (rand() % randomPos + randomPos / 2) - randomPos, LoadIcon(NULL, IDI_WINLOGO));
	}

	return 25;
}

PAYLOADFUNCTION(pwnedText) {
	LPCSTR message = "you have been pwned!";

	RECT rect;
	rect.left = 0;
	rect.right = width;
	rect.top = 100;
	rect.bottom = 200;

	DrawText(hdc, message, -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_CENTER);

	return 1;
}

PAYLOADFUNCTION(randomPwnedText) {
	LPCSTR message = "you have been pwned!";

	int x = rand() & width;
	int y = rand() & height;

	RECT rect;
	rect.left = x - 10;
	rect.top = y - 10;
	rect.right = x + 10;
	rect.bottom = y + 10;

	DrawText(hdc, message, -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_VCENTER);

	return 1;
}

PAYLOADFUNCTION(randomIcons) {
	int ix = GetSystemMetrics(SM_CXICON) / 2;
	int iy = GetSystemMetrics(SM_CYICON) / 2;

	int x = rand() % width;
	int y = rand() % height;

	int random = rand() % 4;

	if (random == 0) {
		DrawIcon(hdc, x - ix, y - iy, LoadIcon(NULL, IDI_ERROR));
	}
	else if (random == 1) {
		DrawIcon(hdc, x - ix, y - iy, LoadIcon(NULL, IDI_ASTERISK));
	}
	else if (random == 2) {
		DrawIcon(hdc, x - ix, y - iy, LoadIcon(NULL, IDI_INFORMATION));
	}
	else if (random == 3) {
		DrawIcon(hdc, x - ix, y - iy, LoadIcon(NULL, IDI_WINLOGO));
	}

	return 150;
}

PAYLOADFUNCTION(fastRandomIcons) {
	int ix = GetSystemMetrics(SM_CXICON) / 2;
	int iy = GetSystemMetrics(SM_CYICON) / 2;

	int x = rand() % width;
	int y = rand() % height;

	int random = rand() % 4;

	if (random == 0) {
		DrawIcon(hdc, x - ix, y - iy, LoadIcon(NULL, IDI_ERROR));
	}
	else if (random == 1) {
		DrawIcon(hdc, x - ix, y - iy, LoadIcon(NULL, IDI_ASTERISK));
	}
	else if (random == 2) {
		DrawIcon(hdc, x - ix, y - iy, LoadIcon(NULL, IDI_INFORMATION));
	}
	else if (random == 3) {
		DrawIcon(hdc, x - ix, y - iy, LoadIcon(NULL, IDI_WINLOGO));
	}

	return 0;
}

PAYLOADFUNCTION(screenBleed) {
	StretchBlt(hdc, 0, 0, width, height, hdc, 0, 0, width, height - 20, SRCCOPY);

	return 1;
}

float i = 0;

PAYLOADFUNCTION(swigglyScreenBleed) {
	StretchBlt(hdc, -10 - sin(i) * 20 + 10, 0, width, height, hdc, 0, 0, width, height - 20, SRCCOPY);

	i += 500 * fElapsedTime;

	return 1;
}