#include <iostream>
#include <windows.h>
#include <string>

// Helper function to convert std::string to std::wstring
std::wstring stringToWString(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstrTo[0], size_needed);
    return wstrTo;
}

void refocusConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow(); // Get the handle to the console window
    if (!consoleWindow) {
        std::cerr << "Cannot get console window handle." << std::endl;
        return;
    }

    // Get the foreground window's thread
    HWND foregroundWindow = GetForegroundWindow();
    if (foregroundWindow == consoleWindow) {
        // If the console is already in the foreground, no need to do anything
        return;
    }

    DWORD windowThreadProcessId = GetWindowThreadProcessId(foregroundWindow, nullptr);
    DWORD currentThreadId = GetCurrentThreadId();

    // Attach input threads
    AttachThreadInput(windowThreadProcessId, currentThreadId, TRUE);

    // Bring console window to the top
    BringWindowToTop(consoleWindow);

    // Show the console window explicitly
    const int CONST_SW_SHOW = 5; // Constant for ShowWindow's SW_SHOW
    ShowWindow(consoleWindow, CONST_SW_SHOW);

    // Detach input threads
    AttachThreadInput(windowThreadProcessId, currentThreadId, FALSE);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: start-shim <command> [args...]" << std::endl;
        return 1;
    }

    // Combine all arguments (the command and any provided parameters)
    std::string commandLine;
    for (int i = 1; i < argc; ++i) {
        commandLine += argv[i];
        if (i < argc - 1) {
            commandLine += " ";
        }
    }

    // Convert std::string to std::wstring
    std::wstring commandLineW = stringToWString(commandLine);

    // Setup process startup information and process information
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi = { 0 };

    // Launch the process
    if (!CreateProcess(
        nullptr,                    // Application name
        &commandLineW[0],           // Command line (modifies this in-place)
        nullptr,                    // Process security attributes
        nullptr,                    // Thread security attributes
        FALSE,                      // Inherit handles
        CREATE_NEW_CONSOLE,         // Use a new console
        nullptr,                    // Environment block
        nullptr,                    // Current directory
        &si,                        // Startup info
        &pi                         // Process info
    )) {
        std::cerr << "Failed to start process: " << commandLine << ". Error: " << GetLastError() << std::endl;
        return 1;
    }

    // Wait for the process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close handles for the process
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Refocus the console window after the child process exits
    refocusConsoleWindow();

    return 0;
}