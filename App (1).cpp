#include "App.h"

int createDb(const char* s);//cria banco
int createTable(const char* s);//criar tabela no banco
int insertData(const char* s);//inserir dados
int selectData(const char* s);//imprimi dados
int callback(void* NotUsed, int argc, char** argv, char** azColName);

int createDb(const char* s) {
    sqlite3* DB;
    int exit = 0;

    exit = sqlite3_open(s, &DB);

    sqlite3_close(DB);

    return 0;
}

int createTable(const char* s) {
    sqlite3* DB;

    string sql = "CREATE TABLE IF NOT EXISTS user("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nome  TEXT NOT NULL,"
        "login  TEXT NOT NULL,"
        "senha  TEXT NOT NULL,"
        "cidade  TEXT NOT NULL,"
        "bairro  TEXT NOT NULL,"
        "servico  TEXT NOT NULL);";

    try {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char* messaggeError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK) {
            cerr << "ERROR CREATE TABLE" << endl;
            sqlite3_free(messaggeError);
        }
        else {
            cout << "TABLE CREATE SUCCESSFULLY" << endl;
            sqlite3_close(DB);
        }

    }
    catch (const exception& e) {
        cerr << e.what();
    }

    return 0;
}

int insertData(const char* s, const char* nome, const char* login, const char* senha, const char* cidade, const char* bairro, const char* servico) {
    sqlite3* DB;
    char* messaggeError;

    int exit = sqlite3_open(s, &DB);

    string sql = "INSERT INTO user (nome, login, senha, cidade, bairro, servico) VALUES ('" +
        string(nome) + "', '" +
        string(login) + "', '" +
        string(senha) + "', '" +
        string(cidade) + "', '" +
        string(bairro) + "', '" +
        string(servico) + "');";

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        cerr << "ERROR INSERT: " << messaggeError << endl;
        sqlite3_free(messaggeError);
    }
    else {
        cout << "INSERT SUCCESSFULLY" << endl;
        sqlite3_close(DB);
    }

    return 0;
}

int selectData(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "SELECT * FROM user;";

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
    exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in selectData function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records selected Successfully!" << endl;

    return 0;
}

// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) {
        // column name and value
        cout << azColName[i] << ": " << argv[i] << endl;
    }

    cout << endl;

    return 0;
}

/*int chat(const std::string& clientName) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Falha ao inicializar o Winsock" << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Falha ao criar o socket" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(3000); // Porta do servidor de chat
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Falha na conexão com o servidor" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::string message;

    while (true) {
        cout << "Digite uma mensagem: ";
        std::getline(std::cin, message);

        // Adiciona o nome do cliente à mensagem
        std::string fullMessage = clientName + ": " + message;

        // Enviar a mensagem para o servidor
        send(clientSocket, fullMessage.c_str(), fullMessage.size() + 1, 0);

        if (message == "exit") {
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}

void iniciaServer() {
    string serverCommand = "start cmd /k node server.js";
    system(serverCommand.c_str());
    // Aguardar alguns segundos para o servidor iniciar completamente
    Sleep(2000);
}
*/
void cadastroUser(Usuario& user, Prestador& prest) {
    string cinNome;
    string cinLogin = "teste";
    const char* dir = "C:\\prest\\prest.db";//onde vai ser salvo DB

    system("cls"); // Limpa a tela;
    cout << "*****CADASTRO USUARIO*****" << endl;
    cout << "Nome para cadastro: ";
    cin >> cinNome;
    for (int i = 0; i < 5; i++) {
        if (cinNome == user.nome[i]) {
            while (cinNome == user.nome[i]) {
                cout << "Usuário já existe\n";
                cout << "Nome para cadastro:";
                cin >> cinNome;
            }
        }
        else {
            user.nome[user.cont] = cinNome;
            insertData(dir, cinNome.c_str(), cinLogin.c_str(), "senha", "cidade", "bairro", "servico");
            break;
        }
    }
    cout << "escreva um nome de usuario: ";
    cin >> cinLogin;
    for (int i = 0; i < 5; i++) {
        if (cinLogin == user.login[i] || cinLogin == prest.login[i]) {
            while (cinLogin == user.login[i] || cinLogin == prest.login[i]) {
                cout << "Nome de Usuario já existe\n";
                cout << "Nome para cadastro:";
                cin >> cinLogin;
            }
        }
        else {
            user.login[user.cont] = cinLogin;
            break;
        }
    }
    cout << "Senha: ";
    cin >> user.senha[user.cont];

    user.id[user.cont] = user.cont;
    user.cont++;

    system("cls"); // Limpa a tela
};

void cadastroPrestador(Prestador& prest, Usuario& user) {

    string cinNome;
    int opc;
    string cinLogin;
    bool loop = true;

    system("cls"); // Limpa a tela
    cout << "*****CADASTRO PRESTADOR DE SERVICO*****" << endl;
    cout << "Nome para cadastro: ";
    cin >> cinNome;
    for (int i = 0; i < 5; i++) {
        if (cinNome == prest.nome[i]) {
            while (cinNome == prest.nome[i]) {
                cout << "Usuário já existe" << endl;
                cout << "Nome para cadastro: " << endl;
                cin >> cinNome;
            }
        }
        else {
            prest.nome[prest.cont] = cinNome;
            break;
        }
    }
    cout << "Escreva um nome de usuario: ";
    cin >> cinLogin;
    for (int i = 0; i < 5; i++) {
        if (cinLogin == prest.login[i] || cinLogin == user.login[i]) {
            while (cinLogin == prest.login[i] || cinLogin ==
                user.login[i]) {
                cout << "Nome de Usuario já existe" << endl;
                cout << "Nome para cadastro:";
                cin >> cinLogin;
            }
        }
        else {
            prest.login[prest.cont] = cinLogin;
            break;
        }
    }
    while (loop) {
        cout << "Qual a sua função:\n";
        cout << "1-Eletricista\n"
            << "2-Mecânico\n"
            << "3-Encanador\n";
        cin >> opc;
        switch (opc) {
        case 1:
            prest.funcao[prest.cont] = "Eletricista";
            loop = false;
            break;
        case 2:
            prest.funcao[prest.cont] = "Mecânico";
            loop = false;
            break;
        case 3:
            prest.funcao[prest.cont] = "Encanador";
            loop = false;
            break;
        default:
            cout << "Função invalida" << endl;
        }
    }
    cout << "Qual sua Cidade:" << endl;
    cout << "1-Porto Alegre" << endl;
    cout << "2-Viamão" << endl;
    cout << "3-Alvorada" << endl;
    cin >> opc;
    switch (opc)
    {
    case 1:
        prest.cidade[prest.cont] = "Porto Alegre";
        break;
    case 2:
        prest.cidade[prest.cont] = "Viamão";
        break;
    case 3:
        prest.cidade[prest.cont] = "Alvorada";
        break;
    default:
        cout << "Comando invalido!";
    }
    cout << "Senha: ";
    cin >> prest.senha[prest.cont];

    prest.id[prest.cont] = prest.cont;
    prest.cont++;
    system("cls"); // Limpa a tela
};

void TelaTrabalhador(Prestador& prest, int id) {
    int opc = 0;
    while (opc != 5) {
        cout << "Nome: " << prest.nome[id] << endl;
        cout << "Função: " << prest.funcao[id] << endl;
        cout << "Sua cidade : " << prest.cidade[id] << endl;
        cout << "\n=== Lista de Serviços ===" << endl;
        if (!prest.solicitante[id].empty()) {
            cout << "Solicitante: " << prest.solicitante[id] << endl;
            cout << "serviço: " << prest.funcao[id] << endl;
            cout << "Descrição do serviço: \n" << prest.texto[id] << endl;
        }
        else {
            cout << "Sem serviços solicitados :(" << endl;
        }
        cout << "\n=========================" << std::endl;
        cout << "5-Voltar\n";
        cin >> opc;
    }
};

void CidadeUsuario(Usuario& user, int id) {
    int opc[4];
    while (opc[0] != 1 && opc[0] != 2 && opc[0] != 3) {
        cout << "Qual a sua região:\n";
        cout << "1 - Porto Alegre\n"
            << "2 - Viamão\n"
            << "3 - Alvorada\n";
        cin >> opc[0];
    }

    switch (opc[0]) {
    case 1:
        user.cidade[id] = "Porto Alegre";
        while (opc[1] != 1 && opc[1] != 2 && opc[1] != 3) {
            cout << "Qual a seu bairro:\n"
                << "1 - Moinhos de vento\n"
                << "2 - auxiliadora\n"
                << "3 - cidade baixa\n";
            cin >> opc[1];
        }
        switch (opc[1])
        {
        case 1: user.bairro[id] = "Moinhos de Vento";
            break;
        case 2: user.bairro[id] = "Auxiliadora";
            break;
        case 3: user.bairro[id] = "Cidade Baixa";
            break;
        }
        break;
    case 2:
        user.cidade[id] = "Viamão";
        while (opc[2] != 1 && opc[2] != 2 && opc[2] != 3) {
            cout << "Qual a seu bairro:\n"
                << "1 - Planalto\n"
                << "2 - Santa Isabel\n"
                << "3 - Monte Alegre\n";
            cin >> opc[2];
        }
        switch (opc[2]) {
        case 1: user.bairro[id] = "Planalto";
            break;
        case 2: user.bairro[id] = "Santa Isabel";
            break;
        case 3: user.bairro[id] = "Monte Alegre";
        }
        break;
    case 3:
        user.cidade[id] = "Alvorada";
        while (opc[3] != 1 && opc[3] != 2 && opc[3] != 3) {
            cout << "Qual a seu bairro:\n"
                << "1 - Jardim Aparecida\n"
                << "2 - Salome\n"
                << "3 - Bela Vista\n";
            cin >> opc[3];
        }
        switch (opc[3]) {
        case 1: user.bairro[id] = "Jardim Aparecida";
            break;
        case 2: user.bairro[id] = "Salome";
            break;
        case 3: user.bairro[id] = "Bela Vista";

        }
        break;

    };
};

string Servico(Usuario& user, Prestador& prest, int id) {
    bool servicoAceito = false;
    int n1;
    for (int i = 0; i < 5; i++) {
        if (user.funcao[id] == prest.funcao[i] && user.cidade[id] ==
            prest.cidade[i]) {
            servicoAceito = true;
            user.servico[id] = "serviço";
            prest.servico[i] = "servico";
            prest.solicitante[i] = user.nome[id];
            prest.texto[i] = user.texto[id];
            cout << "Prestador " << prest.nome[i] << " aceitou seu serviço\n";
            n1 = i;
            break;
        }
    }
    if (!servicoAceito) {
        cout << "Nenhum prestador encontrado :(" << endl;
    }
    return prest.nome[n1];
};

void TelaUser(Usuario& user, Prestador& prest, int id) {
    int opc = 0;
    int opc2 = 0;
    bool loop = true;
    string prestador;
    while (opc != 4) {
        cout << "1-Solicitar Serviço na sua região" << endl;
        cout << "2-Serviços solicitados" << endl;
        cout << "3-chat" << endl;
        cout << "4-Voltar\n";
        cin >> opc;

        if (opc == 1) {
            CidadeUsuario(user, id);

            while (loop) {
                cout << "Qual o serviço que voce quer solicitar?\n";
                cout << "1-Eletricista\n"
                    << "2-Mecânico\n"
                    << "3-Encanador\n";
                cin >> opc2;
                if (opc2 == 1) {
                    user.funcao[id] = "Eletricista";
                    loop = false;
                }
                else if (opc2 == 2) {
                    user.funcao[id] = "Mecânico";
                    loop = false;
                }
                else if (opc2 == 3) {
                    user.funcao[id] = "Encanador";
                    loop = false;
                }
                else {
                    cout << "Função invalida" << endl;
                }
            }
            cout << "Escreva uma breve descrição do serviço:\n" << endl;
            cin.ignore();  // Limpa o buffer do teclado
            getline(cin, user.texto[id]); //permite escreve texto com espaço

            prestador = Servico(user, prest, id);
        }
        else if (opc == 2) {
            if (!user.servico[id].empty()) {
                system("cls"); // Limpa a tela
                cout << "\n=== Lista de Serviços ===" << endl;
                cout << "Prestador: " << prestador << endl;
                cout << "serviço: " << user.funcao[id] << endl;
                cout << "cidade: " << user.cidade[id] << endl;
                cout << "Descrição do serviço: \n" << user.texto[id] << endl << endl;
            }
            else {
                system("cls"); // Limpa a tela
                cout << "Sem serviços solicitados :(" << endl;
            }
        }
        else if (opc == 3) {
            //iniciaServer();
            //chat(user.nome[id]);
        }
        loop = true;
    }
}

void login(Usuario& user, Prestador& prest) {
    string login;
    string senha;
    bool logado = false;
    system("cls"); // Limpa a tela
    cout << "Login: ";
    cin >> login;
    cout << "Senha: ";
    cin >> senha;
    system("cls"); // Limpa a tela
    for (int i = 0; i < 5; i++) {
        if (login == user.login[i] && senha == user.senha[i]) {

            logado = true;
            TelaUser(user, prest, i);
            break;
        }
        else if (login == prest.login[i] && senha == prest.login[i]) {

            logado = true;
            TelaTrabalhador(prest, i);
            break;
        };
    };
    if (!logado) {
        cout << "Usuario ou senha incorreto!!!\n";
    }
};

void ListarUser(Usuario& user) {
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << "-nome: " << user.nome[i] << endl;
        cout << i + 1 << "-senha: " << user.senha[i] << endl;
        cout << i + 1 << "-ID : " << user.id[i] << endl;
        cout << i + 1 << "-login: " << user.login[i] << endl;
        cout << "-----------------------" << endl;
    }
};

void ListarPrest(Prestador& prest) {
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << "-nome: " << prest.nome[i] << endl;
        cout << i + 1 << "-senha: " << prest.senha[i] << endl;
        cout << i + 1 << "-função: " << prest.funcao[i] << endl;
        cout << i + 1 << "-ID =: " << prest.id[i] << endl;
        cout << i + 1 << "-login: " << prest.login[i] << endl;
        cout << "-----------------------" << endl;
    }
};

void App::start() { // em c++ precisar construir o metod fora da classe
    Usuario user;
    Prestador prest;
    int opcao = 0;
    int opcaoUser = 0;

    const char* dir = "C:\\prest\\prest.db";//onde vai ser salvo DB
    sqlite3* DB;// ponteiro usado para compartilhar o mesmo objeto sqlite3(DB)

    createDb(dir);
    createTable(dir);

    while (opcao != 6) {
        cout << "******** Bem Vindo A Tela De Inicio ********\n"
            << "1-Cadastro:\n"
            << "2-Login:\n"
            << "3-Listar Usuario:\n"
            << "4-Listar Prestador:\n"
            << "5-Banco de dados:\n"
            << "6-Sair:\n";
        cin >> opcao;
        switch (opcao) {
        case 1:
            cout << "1-Usuario\n"
                << "2-Trabalhador\n";
            cin >> opcaoUser;
            if (opcaoUser == 1) {
                cadastroUser(user, prest);
            }
            else if (opcaoUser == 2) {
                cadastroPrestador(prest, user);
            }
            else {
                cout << "Opção inválida" << endl;
            }
            break;
        case 2:
            login(user, prest);
            break;
        case 3:
            ListarUser(user);
            break;
        case 4:
            ListarPrest(prest);
            break;
        case 5:
            selectData(dir);
            break;
        case 6: // opção para sair do sistema.
            break;
        default:
            cout << "Comando invalido!" << endl;
        }
    }
}

void App::Finish() { cout << "FIM DO SISTEMA"; };