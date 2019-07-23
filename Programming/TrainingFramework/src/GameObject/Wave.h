#pragma once
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <conio.h>

class Wave {

public:
	Wave(char* filename);
	~Wave();
	void play(bool async = true);
	bool isok();

private:
	char* buffer;
	bool ok;
	HINSTANCE HInstance;
};