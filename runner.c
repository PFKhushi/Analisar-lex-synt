#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD start, end, exitCode;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    start = GetTickCount64();

    // cria o processo do analisador
    if (!CreateProcess(
            "analisador.exe",   // programa
            NULL,               // argumentos
            NULL, NULL, FALSE,  // herança
            0,                  // flags
            NULL, NULL,         // ambiente e diretório
            &si, &pi)) {
        printf("Erro ao iniciar analisador.exe\n");
        return 1;
    }

    // espera terminar
    WaitForSingleObject(pi.hProcess, INFINITE);

    end = GetTickCount64();

    // pega código de saída
    GetExitCodeProcess(pi.hProcess, &exitCode);

    // fecha handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    double elapsed = (end - start) / 1000.0;

    printf("\nProcess returned %lu (0x%lX)   execution time : %.3f s\n",
           exitCode, exitCode, elapsed);

    printf("Press any key to continue . . .");
    system("pause >nul");
    return 0;
}
