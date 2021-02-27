/*
Shakra Driver component for Windows
This .cpp file contains the required code to run the driver under Windows 8.1 and later.

This file is useful only if you want to compile the driver under Windows, it's not needed for Linux/macOS porting.
*/

#ifdef _WIN32

#include "WinError.hpp"

void ErrorSystem::WinErr::Log(const wchar_t* Message, const wchar_t* Position, const wchar_t* File, const wchar_t* Line) {
	wchar_t* Buf = new wchar_t[SZBufSize];

	swprintf_s(Buf, BufSize, L"DEBUG MSG FROM %s.\n\nFile: %s\nLine: %s\n\nMessage: %s", Position, File, Line, Message);

	OutputDebugString(Buf);

#ifdef _DEBUG
	MessageBox(NULL, Buf, L"Shakra - Debug message", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif

	delete[] Buf;
}

void ErrorSystem::WinErr::ThrowError(const wchar_t* Error, const wchar_t* Position, const wchar_t* File, const wchar_t* Line, bool IsSeriousError) {
	wchar_t* Buf = new wchar_t[SZBufSize];

#ifdef _DEBUG
	swprintf_s(Buf, BufSize, L"An error has occured in the \"%s\" function!\n\nFile: %s\nLine: %s\n\nError: %s", Position, File, Line, Error);
#else
	swprintf_s(Buf, BufSize, L"An error has occured in the \"%s\" function!\n\nError: %s", Position, Error);
#endif

	MessageBox(NULL, Buf, L"Shakra - Error", IsSeriousError ? MB_ICONERROR : MB_ICONWARNING | MB_OK | MB_SYSTEMMODAL);

	delete[] Buf;
}

void ErrorSystem::WinErr::ThrowFatalError(const wchar_t* Error) {
	wchar_t* Buf = new wchar_t[SZBufSize];

	swprintf_s(Buf, BufSize, L"A fatal error has occured from which the driver is unable to recover!\n\nError: %s", Error);

	MessageBox(NULL, Buf, L"Shakra - FATAL ERROR", MB_ICONERROR | MB_OK | MB_SYSTEMMODAL);

	delete[] Buf;

	throw (int)(-1);
}

#endif