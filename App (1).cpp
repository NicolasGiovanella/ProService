#include "App.h"

int createDb(const char* s);//cria banco
int createTable(const char* s);//criar tabela no banco
int updateData(const char* s);//att valor no banco
int deleteData(const char* s);//deleta valor no banco
int insertData(const char* s);//inserir dados
int selectData(const char* s);//imprimi dados
int callbackCheckNome(void* data, int argc, char** argv, char** azColName);
int callback(void* NotUsed, int argc, char** argv, char** azColName);
int callbackGetID(void* data, int argc, char** argv, char** azColName);

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

int createTablePrestador(const char* s) {
    sqlite3* DB;

    string sql = "CREATE TABLE IF NOT EXISTS prest("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nome  TEXT NOT NULL,"
        "login  TEXT NOT NULL,"
        "senha  TEXT NOT NULL,"
        "cidade  TEXT NOT NULL,"
        "bairro  TEXT NOT NULL,"
        "funcao  TEXT NOT NULL,"
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

int insertData(const char* s,const char* nome, const char* login, const char* senha, const char* cidade, const char* bairro, const char* servico) {
    sqlite3* DB;
    char* messaggeError;
    bool teste = true;
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

int insertPrestador(const char* s, const char* nome, const char* login, const char* senha, const char* cidade, const char* bairro, const char* funcao,const char* servico) {
    sqlite3* DB;
    char* messaggeError;
    bool teste = true;
    int exit = sqlite3_open(s, &DB);


    string sql = "INSERT INTO prest (nome, login, senha, cidade, bairro, funcao, servico) VALUES ('" +
        string(nome) + "', '" +
        string(login) + "', '" +
        string(senha) + "', '" +
        string(cidade) + "', '" +
        string(bairro) + "', '" +
        string(funcao) + "', '" +
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

bool verificaNome(const char* s, const char* user, const char* table)
{
    sqlite3* DB;
    char* messageError;
    int count = 0;

    string sql = "SELECT COUNT(*) FROM "+ string(table) +" WHERE login = '" + string(user) + "'; ";

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
    exit = sqlite3_exec(DB, sql.c_str(), callbackCheckNome, &count, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in selectData function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records selected Successfully!" << endl;

    if (count > 0) {
       // cout << "O nome de usuário já existe." << endl;
        return true;
    }
    else {
       // cout << "nome não existe" << endl;
        return false;
    }
    
}

enum TipoLogin {
    INVALIDO,
    USER,
    PREST
};

TipoLogin verificarCredenciais(const char* s, const string& login, const string& senha) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);
    string sql;

    // Consulta na tabela 'user'
    sql = "SELECT COUNT(*) FROM user WHERE login = '" + login + "' AND senha = '" + senha + "'";
    int countUser = 0;
    exit = sqlite3_exec(DB, sql.c_str(), callbackCheckNome, &countUser, nullptr);
    if (exit != SQLITE_OK) {
        cerr << "Erro na consulta da tabela 'user'." << endl;
        sqlite3_close(DB);
        return INVALIDO;
    }

    // Consulta na tabela 'prest'
    sql = "SELECT COUNT(*) FROM prest WHERE login = '" + login + "' AND senha = '" + senha + "'";
    int countPrest = 0;
    exit = sqlite3_exec(DB, sql.c_str(), callbackCheckNome, &countPrest, nullptr);
    if (exit != SQLITE_OK) {
        cerr << "Erro na consulta da tabela 'prest'." << endl;
        sqlite3_close(DB);
        return INVALIDO;
    }

    sqlite3_close(DB);

    // Verifica se há registros correspondentes nas tabelas 'user' ou 'prest'
    if (countUser > 0) {
        return USER;  // Credenciais válidas como 'user'
    }
    else if (countPrest > 0) {
        return PREST;  // Credenciais válidas como 'prestador'
    }
    else {
        return INVALIDO; // Credenciais inválidas
    }
}

int getUserID(const char* s, const string& table , const string& login, const string& senha) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);
    string sql = "SELECT id FROM "+ table +" WHERE login = '" + login + "' AND senha = '" + senha + "'";
    int id = 0;
    exit = sqlite3_exec(DB, sql.c_str(), callbackGetID, &id, nullptr);
    sqlite3_close(DB);
    return id;
}

int callbackGetID(void* data, int argc, char** argv, char** azColName) {
    int* id = static_cast<int*>(data);
    *id = atoi(argv[0]);
    return 0;
}

int callbackCheckNome(void* data, int argc, char** argv, char** azColName) {
    int* count = static_cast<int*>(data);
    *count = atoi(argv[0]);
    return 0;
}

int deleteData(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string id;
    cout << "Digite o id do user a ser excluido: ";
    cin >> id;

    string sql = "DELETE FROM user WHERE ID = '" + id + "';";

    int exit = sqlite3_open(s, &DB);
    exit = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in deleteData function." << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Record deleted successfully!" << endl;
    }

    return 0;
}

int updateData(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string id;
    string nomeAlterado;

    cout << "Qual o ID do user que voce quer alterar? " << endl;
    cin >> id;
    cout << "Digite o novo nome: " << endl;
    cin >> nomeAlterado;

    string sql("UPDATE user SET nome = '" + nomeAlterado + "' WHERE ID = '" + id + "'");

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error in updateData function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records updated Successfully!" << endl;

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

int selectPrest(const char* s)
{
    sqlite3* DB;
    char* messageError;
    string sql = "SELECT * FROM prest;";

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
}*/

/*void iniciaServer() {
    string serverCommand = "start cmd /k node server.js";
    system(serverCommand.c_str());
    // Aguardar alguns segundos para o servidor iniciar completamente
    Sleep(2000);
}*/

void cadastroUser(Usuario& user, Prestador& prest) {
    string cinNome;
    string cinLogin;
    string cinSenha;
    const char* dir = "C:\\prest\\prest.db";//onde vai ser salvo DB

    system("cls"); // Limpa a tela;
    cout << "*****CADASTRO USUARIO*****" << endl;
    cout << "Nome para cadastro: ";
    cin >> cinNome;
    
    bool nomeExistente = true;
    while (nomeExistente) {
        cout << "Escreva um nome de usuário: ";
        cin >> cinLogin;
        // Verificar se o nome de usuário já existe
        if (verificaNome(dir, cinLogin.c_str(), "user")) {
            cout << "O nome de usuário já existe. Por favor, escolha outro nome." << endl;
        }
        else {
            nomeExistente = false;
        }
    }
    
    cout << "Senha: ";
    cin >> cinSenha;

    insertData(dir, cinNome.c_str(), cinLogin.c_str(), cinSenha.c_str(), "Nulo", "Nulo", "Nulo");

    system("cls"); // Limpa a tela
};

void cadastroPrestador(Prestador& prest, Usuario& user) {
    string cinNome;
    int opc;
    string cinLogin;
    string funcao;
    string cidade;
    string senha;
    bool loop = true;
    const char* dir = "C:\\prest\\prest.db";//onde vai ser salvo DB

    system("cls"); // Limpa a tela
    cout << "*****CADASTRO PRESTADOR DE SERVICO*****" << endl;
    cout << "Nome para cadastro: ";
    cin >> cinNome;
   
    bool nomeExistente = true;
    while (nomeExistente) {
        cout << "Escreva um nome de usuário: ";
        cin >> cinLogin;
        // Verificar se o nome de usuário já existe
        if (verificaNome(dir, cinLogin.c_str(), "prest")) {
            cout << "O nome de usuário já existe. Por favor, escolha outro nome." << endl;
        }
        else {
            nomeExistente = false;
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
            funcao = "Eletricista";
            loop = false;
            break;
        case 2:
            funcao = "Mecânico";
            loop = false;
            break;
        case 3:
            funcao = "Encanador";
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
        cidade = "Porto Alegre";
        break;
    case 2:
        cidade = "Viamão";
        break;
    case 3:
        cidade = "Alvorada";
        break;
    default:
        cout << "Comando invalido!";
    }
    cout << "Senha: ";
    cin >> senha;
    insertPrestador(dir, cinNome.c_str(), cinLogin.c_str(), senha.c_str(), cidade.c_str(), "Nulo", funcao.c_str(), "Nulo");
    
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
    int n1 = -1; // Inicializa 'n1' com -1

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

    if (n1 != -1) {
        return prest.nome[n1];
    }
    else {
        // Trate o caso em que nenhum prestador aceitou o serviço
        return "Nenhum prestador aceitou o serviço";
    }
}

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
            
        }
        loop = true;
    }
}

void login(Usuario& user, Prestador& prest) {
    string login;
    string senha;
    bool logado = false;
    int id;
    const char* dir = "C:\\prest\\prest.db";
    system("cls"); // Limpa a tela
    cout << "Login: ";
    cin >> login;
    cout << "Senha: ";
    cin >> senha;
   // system("cls"); // Limpa a tela
    TipoLogin tipo = verificarCredenciais(dir, login, senha);
    
    if (tipo == USER) {
        cout << "********TELA DO USUARIO********" << endl;
        id = getUserID(dir, "user", login, senha);
        if (id != 0) { // Verifica se o ID é válido
            cout << id << endl;
            TelaUser(user, prest, 1);
        }
        else {
            cout << "Erro ao obter o ID do usuário." << endl;
        }
    }
    else if (tipo == PREST) {
        cout << "********TELA DO TRABALHADOR********" << endl;
        id = getUserID(dir, "prest", login, senha);
        if (id != 0) { // Verifica se o ID é válido
            cout << id << endl;
            TelaTrabalhador(prest, 1);
        }
        else {
            cout << "Erro ao obter o ID do trabalhador." << endl;
        }
    }
    else {
        cout << "Usuário ou senha incorretos!" << endl;
    }
            
};

void App::start() { // em c++ precisar construir o metod fora da classe
    SetConsoleOutputCP(CP_UTF8);
    
    Usuario user;
    Prestador prest;
    int opcao = 0;
    int opcaoUser = 0;

    

    const char* dir = "C:\\prest\\prest.db";//onde vai ser salvo DB
    sqlite3* DB;// ponteiro usado para compartilhar o mesmo objeto sqlite3(DB)

    createDb(dir);
    createTable(dir);
    createTablePrestador(dir);

    while (opcao != 8) {
        cout << "******** Bem Vindo A Tela De Inicio ********\n"
            << "1-Cadastro:\n"
            << "2-Login:\n"
            << "3-Listar Usuario:\n"
            << "4-Listar Prestador:\n"
            << "5-Chat:\n"
            << "6-Delete user:\n"
            << "7-Edita user:\n"
            << "8-Sair:\n";
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

            selectData(dir);
            break;
        case 4:
            cout << "*********PRESTADORES*********";
            selectPrest(dir);
            break;
        case 5:
           // iniciaServer();
           // chat("Nicolas");
            break;
        case 6:
            deleteData(dir);
            break;
        case 7:
            updateData(dir);
            break;
        case 8: // opção para sair do sistema.
            break;
        default:
            cout << "Comando invalido!" << endl;
        }
    }
}

void App::Finish() { cout << "FIM DO SISTEMA"; };
