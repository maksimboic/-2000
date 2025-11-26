#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

wstring SystemTime() {
    ULONGLONG uptimeMs = GetTickCount64();
    ULONGLONG totalSeconds = uptimeMs / 1000;
    ULONGLONG totalMinutes = totalSeconds / 60;
    ULONGLONG totalHours = totalMinutes / 60;
    ULONGLONG totalDays = totalHours / 24;

    ULONGLONG seconds = totalSeconds % 60;
    ULONGLONG minutes = totalMinutes % 60;
    ULONGLONG hours = totalHours % 24;

    return to_wstring(totalDays) + L" дней, " +
        to_wstring(hours) + L" часов, " +
        to_wstring(minutes) + L" минут, " +
        to_wstring(seconds) + L" секунд";
}

wstring GetCurrentDateTime() {
    SYSTEMTIME localTime;
    GetLocalTime(&localTime);

    wstringstream timeStream;
    timeStream << setw(4) << localTime.wYear << L"-"
        << setw(2) << setfill(L'0') << localTime.wMonth << L"-"
        << setw(2) << setfill(L'0') << localTime.wDay << L" "
        << setw(2) << setfill(L'0') << localTime.wHour << L":"
        << setw(2) << setfill(L'0') << localTime.wMinute << L":"
        << setw(2) << setfill(L'0') << localTime.wSecond;

    return timeStream.str();
}

int main() {
    // Получение информации о системе
    TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD computerNameLength = sizeof(computerName) / sizeof(TCHAR);
    GetComputerName(computerName, &computerNameLength);

    TCHAR userName[256];
    DWORD userNameLength = sizeof(userName) / sizeof(TCHAR);
    GetUserName(userName, &userNameLength);

    wstring infoMessage = L"Время работы системы: " + SystemTime() + L"\n" +
        L"Компьютер: " + computerName + L"\n" +
        L"Пользователь: " + userName + L"\n" +
        L"Текущая дата и время: " + GetCurrentDateTime();

    MessageBoxW(NULL, infoMessage.c_str(), L"Информация о системе", MB_OKCANCEL |	MB_ICONQUESTION);

    return 0;
}