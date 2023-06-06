#include <iostream>
#include <list>
#include <string>
#include <locale.h>
#include <queue>//lista
//#include <winsock2.h>//socket chat
//#include <WS2tcpip.h>//tcp chat
//#include <iconv.h>//tratar string chat
//#include <cstdlib>//limpar tela
#include <stdio.h>
#include <sqlite3.h>


#pragma comment(lib, "ws2_32.lib")
using namespace std;

class Usuario {
public:
    int id[5] = { 999,999,999,999,999 };
    string nome[5];
    string senha[5];
    string cidade[5];
    string bairro[5];
    string funcao[5];
    string servico[5];
    string texto[5];
    string login[5];
    int cont = 0;
};

class Prestador {
public:
    int id[5] = { 999,999,999,999,999 };
    string nome[5];
    string senha[5];
    string funcao[5];
    string cidade[5];
    string bairro[5];
    string servico[5];
    string solicitante[5];
    string texto[5];
    string login[5];
    int cont = 0;
};


//cout <<"Fale um pouco do problema que está ocorrendo\n:";
    //  cin >> user.texto[id];
    //  cout << user.texto[id]; 