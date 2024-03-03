#include <windows.h>
#include <stdbool.h>
#define MUTEX_NAME "HiddenWavPlayerMutex"


bool isAnotherInstanceRunning() {
  HANDLE hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
  if (hMutex == NULL) {
    return true;
  }

  DWORD dwLastError = GetLastError();
  if (dwLastError == ERROR_ALREADY_EXISTS) {
    CloseHandle(hMutex);
    return true;
  }

  return false;
}

void playWav(const char *filename) {
  PlaySound(filename, NULL, SND_FILENAME | SND_SYNC);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  if (isAnotherInstanceRunning()) {
    return 1;
  }

  if (__argc < 2 || __argc > 3) {
    MessageBox(NULL, "Usage: <wav_file> [wait_time_in_seconds]", "Error", MB_OK | MB_ICONERROR);
    return -1;
  }

  const char *wav_file = __argv[1];

  if (__argc == 3) {
    int wait_time = atoi(__argv[2]);
    Sleep(wait_time * 1000);
  }

  playWav(wav_file);

  return 0;
}