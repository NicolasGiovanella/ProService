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

//cria bancdo de dados
int createDb(const char* s) {
    sqlite3* DB;
    int exit = 0;

    exit = sqlite3_open(s, &DB);

    sqlite3_close(DB);

    return 0;
}
//criar tabela tabela user
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
//cria tabela prestador
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
//cria tabela serviço
int createTableServico(const char* s) {
    sqlite3* DB;

    string sql = "CREATE TABLE IF NOT EXISTS servico("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "idUser   INTEGER NULL,"
        "idPrest  INTEGER NOT NULL,"
        "descricao  TEXT NOT NULL,"
        "cidade TEXT NOT NULL,"
        "tipoServico  TEXT NOT NULL);";

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
//inseri dados a tabela servico
int insertServico(const char* s, int idUser, int idPrest, const char* descricao, const char* cidade, const char* servico) {
    sqlite3* DB;
    char* messaggeError;
    bool teste = true;
    int exit = sqlite3_open(s, &DB);


    string sql = "INSERT INTO servico (idUser, idPrest, descricao, cidade ,tipoServico) VALUES ('" +
        to_string(idUser) + "', '" +
        to_string(idPrest) + "', '" +
        string(descricao) + "', '" +
        string(cidade) + "', '" +
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
//imprimi serviço
int selectServico(const char* s)
{
    sqlite3* DB;
    char* messageError;
    string sql = "SELECT * FROM servico;";

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
//insere dados a tabela user
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
//insere dados a tabela prestador
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

int getPrestadorID(const char* s, const string& cidade, const string& bairro, const string& funcao) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);
    string sql = "SELECT id FROM prest WHERE cidade = '" + cidade + "' AND bairro = '" + bairro + "' AND funcao = '" + funcao + "'";
    int id = 0;
    exit = sqlite3_exec(DB, sql.c_str(), callbackGetID, &id, nullptr);
    sqlite3_close(DB);
    return id;
}
//função struct 
struct InformacoesPrestador {
    string nome;
    string funcao;
    string cidade;
    string bairro;
};

InformacoesPrestador obterInformacoesPrestador(const char* s, int id) {
    InformacoesPrestador informacoes;

    sqlite3* DB;
    string sql = "SELECT nome, funcao, cidade, bairro FROM prest WHERE ID = " + to_string(id) + ";";

    try {
        int exit = sqlite3_open(s, &DB);

        if (exit != SQLITE_OK) {
            cerr << "ERROR OPENING DATABASE" << endl;
            return informacoes;
        }

        sqlite3_stmt* stmt;
        exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

        if (exit != SQLITE_OK) {
            cerr << "ERROR PREPARING STATEMENT" << endl;
            sqlite3_close(DB);
            return informacoes;
        }

        exit = sqlite3_step(stmt);

        if (exit == SQLITE_ROW) {
            const unsigned char* nome = sqlite3_column_text(stmt, 0);
            const unsigned char* funcao = sqlite3_column_text(stmt, 1);
            const unsigned char* cidade = sqlite3_column_text(stmt, 2);
            const unsigned char* bairro = sqlite3_column_text(stmt, 3);

            informacoes.nome = reinterpret_cast<const char*>(nome);
            informacoes.funcao = reinterpret_cast<const char*>(funcao);
            informacoes.cidade = reinterpret_cast<const char*>(cidade);
            informacoes.bairro = reinterpret_cast<const char*>(bairro);
        }
        else {
            cerr << "PRESTADOR NOT FOUND" << endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(DB);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return informacoes;
}

//deleta dados do banco
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
//editar dados do banco
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
//imprimir * do banco user
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
//imprimir * do banco prest
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
//callback para buscar id
int callbackGetID(void* data, int argc, char** argv, char** azColName) {
    int* id = static_cast<int*>(data);
    *id = atoi(argv[0]);
    return 0;
}
//callback para chamar nome
int callbackCheckNome(void* data, int argc, char** argv, char** azColName) {
    int* count = static_cast<int*>(data);
    *count = atoi(argv[0]);
    return 0;
}
//calback para imprimir *
int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) {
        // column name and value
        cout << azColName[i] << ": " << argv[i] << endl;
    }

    cout << endl;

    return 0;
}

// Função para verificar se um valor existe no banco de dados SQLite e imprimir os registros correspondentes
/*int verificarValorExistente(const char* s, int idUser) {
    sqlite3* DB;
    //int rc;
    int exit = sqlite3_open(s, &DB);
    // Abre a conexão com o banco de dados
   // rc = sqlite3_open("caminho_para_o_banco_de_dados.db", &DB);

    if (exit != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(DB) << endl;
        return 0;
    }

    sqlite3_stmt* stmt;
    string query = "SELECT * FROM servico WHERE idUser = " + to_string(idUser) + ";";

    // Prepara a consulta SQL
    exit = sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, nullptr);

    if (exit != SQLITE_OK) {
        cerr << "Erro ao preparar a consulta: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return 0;
    }

    // Vincula o valor do parâmetro
    sqlite3_bind_int(stmt, 1, idUser);

    // Executa a consulta
    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Imprime os valores dos campos correspondentes
        int id = sqlite3_column_int(stmt, 0);
        int userId = sqlite3_column_int(stmt, 1);
        int prestId = sqlite3_column_int(stmt, 2);
        const unsigned char* descricao = sqlite3_column_text(stmt, 3);
        const unsigned char* cidade = sqlite3_column_text(stmt, 4);
        const unsigned char* tipoServico = sqlite3_column_text(stmt, 5);

        cout << "Registro encontrado:" <<endl;
        cout << "ID: " << id << endl;
        cout << "idUser: " << userId << endl;
        cout << "idPrest: " << prestId << endl;
        cout << "descricao: " << descricao << endl;
        cout << "cidade: " << cidade << endl;
        cout << "tipoServico: " << tipoServico << endl;
        cout << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return 1;
    }

    if (exit != SQLITE_DONE) {
        // Erro ao executar a consulta
        cerr << "Erro ao executar a consulta: " << sqlite3_errmsg(DB) << endl;
        return 0;
    }

    // Libera os recursos
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}*/
/*void selectServicoPorIdUser(const char* s, int idUser) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);

    if (exit != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    sqlite3_stmt* stmt;
    string query = "SELECT * FROM servico WHERE idUser = "+to_string(idUser)+";";

    exit = sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        cerr << "Erro ao preparar a consulta: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    sqlite3_bind_int(stmt, 1, idUser);

    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int userId = sqlite3_column_int(stmt, 1);
        int prestId = sqlite3_column_int(stmt, 2);
        const unsigned char* descricao = sqlite3_column_text(stmt, 3);
        const unsigned char* cidade = sqlite3_column_text(stmt, 4);
        const unsigned char* tipoServico = sqlite3_column_text(stmt, 5);

        cout << "Registro encontrado:" << endl;
        cout << "ID: " << id << endl;
        //cout << "idUser: " << userId << endl;
       // cout << "idPrest: " << prestId << endl;
        cout << "descricao: " << descricao << endl;
        cout << "cidade: " << cidade << endl;
        cout << "tipoServico: " << tipoServico << endl;
        cout << endl;
    }

    if (exit != SQLITE_DONE) {
        cerr << "Erro ao executar a consulta: " << sqlite3_errmsg(DB) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}*/
void selectServicoPorIdUser(const char* s,  int idUser) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);

    if (exit != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    sqlite3_stmt* stmt;
    string query = "SELECT * FROM servico WHERE idUser = " + to_string(idUser) + "; ";

    exit = sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        cerr << "Erro ao preparar a consulta: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    bool found = false; // Variável para rastrear se algum item foi encontrado

    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
        found = true;

        int id = sqlite3_column_int(stmt, 0);
        int userId = sqlite3_column_int(stmt, 1);
        int prestId = sqlite3_column_int(stmt, 2);
        const unsigned char* descricao = sqlite3_column_text(stmt, 3);
        const unsigned char* cidade = sqlite3_column_text(stmt, 4);
        const unsigned char* tipoServico = sqlite3_column_text(stmt, 5);

        cout << "Registro encontrado:" << endl;
        cout << "ID: " << id << endl;
        // cout << "idUser: " << userId << endl;
        // cout << "idPrest: " << prestId << endl;
        cout << "descricao: " << descricao << endl;
        cout << "cidade: " << cidade << endl;
        cout << "tipoServico: " << tipoServico << endl;
        cout << endl;
    }

    if (exit != SQLITE_DONE) {
        cerr << "Erro ao executar a consulta: " << sqlite3_errmsg(DB) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    if (!found) {
        cout << "Nenhum item encontrado o Usúario " << endl;
    }
}

void selectServicoPorIdPrest(const char* s,  int idPrest) {
    sqlite3* DB;
    int exit = sqlite3_open(s, &DB);

    if (exit != SQLITE_OK) {
        cerr << "Não foi possível abrir o banco de dados: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    sqlite3_stmt* stmt;
    string query = "SELECT * FROM servico WHERE idPrest = " + to_string(idPrest) + "; ";

    exit = sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        cerr << "Erro ao preparar a consulta: " << sqlite3_errmsg(DB) << endl;
        sqlite3_close(DB);
        return;
    }

    bool found = false; // Variável para rastrear se algum item foi encontrado

    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
        found = true;

        int id = sqlite3_column_int(stmt, 0);
        int userId = sqlite3_column_int(stmt, 1);
        int prestId = sqlite3_column_int(stmt, 2);
        const unsigned char* descricao = sqlite3_column_text(stmt, 3);
        const unsigned char* cidade = sqlite3_column_text(stmt, 4);
        const unsigned char* tipoServico = sqlite3_column_text(stmt, 5);

        cout << "Registro encontrado:" << endl;
        cout << "ID: " << id << endl;
        // cout << "idUser: " << userId << endl;
        // cout << "idPrest: " << prestId << endl;
        cout << "descricao: " << descricao << endl;
        cout << "cidade: " << cidade << endl;
        cout << "tipoServico: " << tipoServico << endl;
        cout << endl;
    }

    if (exit != SQLITE_DONE) {
        cerr << "Erro ao executar a consulta: " << sqlite3_errmsg(DB) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    if (!found) {
        cout << "Nenhum item encontrado o Usúario " << endl;
    }
}


/*-------------funçoes-------------*/

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
    string bairro;
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
 
    int opcCidade[4];
    while (opcCidade[0] != 1 && opcCidade[0] != 2 && opcCidade[0] != 3) {
        cout << "Qual a sua região:\n";
        cout << "1 - Porto Alegre\n"
            << "2 - Viamão\n"
            << "3 - Alvorada\n";
        cin >> opcCidade[0];
    }

    switch (opcCidade[0]) {
    case 1:
        cidade = "Porto Alegre";
        while (opcCidade[1] != 1 && opcCidade[1] != 2 && opcCidade[1] != 3) {
            cout << "Qual a seu bairro:\n"
                << "1 - Moinhos de vento\n"
                << "2 - auxiliadora\n"
                << "3 - cidade baixa\n";
            cin >> opcCidade[1];
        }
        switch (opcCidade[1])
        {
        case 1: bairro = "Moinhos de Vento";
            break;
        case 2: bairro = "Auxiliadora";
            break;
        case 3: bairro = "Cidade Baixa";
            break;
        }
        break;
    case 2:
        cidade = "Viamão";
        while (opcCidade[2] != 1 && opcCidade[2] != 2 && opcCidade[2] != 3) {
            cout << "Qual a seu bairro:\n"
                << "1 - Planalto\n"
                << "2 - Santa Isabel\n"
                << "3 - Monte Alegre\n";
            cin >> opcCidade[2];
        }
        switch (opcCidade[2]) {
        case 1: bairro = "Planalto";
            break;
        case 2: bairro = "Santa Isabel";
            break;
        case 3: bairro = "Monte Alegre";
        }
        break;
    case 3:
        cidade = "Alvorada";
        while (opcCidade[3] != 1 && opcCidade[3] != 2 && opcCidade[3] != 3) {
            cout << "Qual a seu bairro:\n"
                << "1 - Jardim Aparecida\n"
                << "2 - Salome\n"
                << "3 - Bela Vista\n";
            cin >> opcCidade[3];
        }
        switch (opcCidade[3]) {
        case 1: bairro = "Jardim Aparecida";
            break;
        case 2: bairro = "Salome";
            break;
        case 3: bairro = "Bela Vista";

        }
        break;

    };
    cout << "Senha: ";
    cin >> senha;
    insertPrestador(dir, cinNome.c_str(), cinLogin.c_str(), senha.c_str(), cidade.c_str(), bairro.c_str(), funcao.c_str(), "Nulo");
    
    system("cls"); // Limpa a tela
};

void TelaTrabalhador(int idPrest, const InformacoesPrestador& informacoes) {
    int opc = 0;

    while (opc != 5) {
        system("cls"); // Limpa a tela
        const char* dir = "C:\\prest\\prest.db";
        cout << idPrest << endl;
        cout << "+--------------------------------------------+\n";
        cout << "|          ****TELA DO PRESTADOR****         |\n"
             << "+--------------------------------------------+\n";
        cout << "Nome: " << informacoes.nome << endl;
        cout << "Função: " << informacoes.funcao << endl;
        cout << "Sua cidade : " << informacoes.cidade << endl;
        cout << "\n============ Lista de Serviços ============" << endl;
        selectServicoPorIdPrest(dir, idPrest);
        cout << "\n===========================================" << endl;
        cout << "5-Voltar\n";
        cin >> opc;
    }
};

int Servico(string cidade, string bairro, string funcao) {
    bool servicoAceito = false;
    const char* dir = "C:\\prest\\prest.db";
    int id;

   id = getPrestadorID(dir, cidade, bairro, funcao);//vai verificar se tem aloguem prestador que atende os requisitos

   return id;
}

void TelaUser(InformacoesPrestador& informacoes, int idUser) {
    system("cls"); // Limpa a tela
    int opc = 0;
    int opc2 = 0;
    bool loop = true;
    const char* dir = "C:\\prest\\prest.db";
    int IDprestador = -1;
    string prestador;
    string funcao;
    string cidade;
    string bairro;
    string descricao;
    while (opc != 4) {
        cout << "+----------------------------------------+\n"
            << "|            Solicitações                |\n"
            << "|----------------------------------------|\n"
            << "|1-Solicitar Serviço na sua região:      |\n"
            << "|2-Serviços solicitados:                 |\n"
            << "|3-chat:                                 |\n"
            << "|4-Voltar                                |\n"
            << "+----------------------------------------+\n";
        cin >> opc;

        if (opc == 1) {
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
                cidade = "Porto Alegre";
                while (opc[1] != 1 && opc[1] != 2 && opc[1] != 3) {
                    cout << "Qual a seu bairro:\n"
                        << "1 - Moinhos de vento\n"
                        << "2 - auxiliadora\n"
                        << "3 - cidade baixa\n";
                    cin >> opc[1];
                }
                switch (opc[1])
                {
                case 1: bairro = "Moinhos de Vento";
                    break;
                case 2: bairro = "Auxiliadora";
                    break;
                case 3: bairro = "Cidade Baixa";
                    break;
                }
                break;
            case 2:
                cidade = "Viamão";
                while (opc[2] != 1 && opc[2] != 2 && opc[2] != 3) {
                    cout << "Qual a seu bairro:\n"
                        << "1 - Planalto\n"
                        << "2 - Santa Isabel\n"
                        << "3 - Monte Alegre\n";
                    cin >> opc[2];
                }
                switch (opc[2]) {
                case 1: bairro = "Planalto";
                    break;
                case 2: bairro = "Santa Isabel";
                    break;
                case 3: bairro = "Monte Alegre";
                }
                break;
            case 3:
                cidade = "Alvorada";
                while (opc[3] != 1 && opc[3] != 2 && opc[3] != 3) {
                    cout << "Qual a seu bairro:\n"
                        << "1 - Jardim Aparecida\n"
                        << "2 - Salome\n"
                        << "3 - Bela Vista\n";
                    cin >> opc[3];
                }
                switch (opc[3]) {
                case 1: bairro = "Jardim Aparecida";
                    break;
                case 2: bairro = "Salome";
                    break;
                case 3: bairro = "Bela Vista";

                }
                break;

            };

            while (loop) {
                system("cls"); // Limpa a tela
                cout << "Qual o serviço que voce quer solicitar?\n";
                cout << "1-Eletricista\n"
                    << "2-Mecânico\n"
                    << "3-Encanador\n";
                cin >> opc2;
                if (opc2 == 1) {
                    funcao = "Eletricista";
                    loop = false;
                }
                else if (opc2 == 2) {
                    funcao = "Mecânico";
                    loop = false;
                }
                else if (opc2 == 3) {
                    funcao = "Encanador";
                    loop = false;
                }
                else {
                    cout << "Função invalida" << endl;
                }
            }
            cout << "Escreva uma breve descrição do serviço:\n" << endl;
            cin.ignore();  // Limpa o buffer do teclado
            getline(cin, descricao); //permite escreve texto com espaço

            IDprestador = Servico(cidade, bairro, funcao);
            informacoes = obterInformacoesPrestador(dir, IDprestador);     
            if (IDprestador > 0) {
                insertServico(dir, idUser, IDprestador, descricao.c_str(), cidade.c_str(), funcao.c_str());
            }
            else {
                cout << "Nenhum prestador encontrado no momento" << endl;
            }

        }
        else if (opc == 2) {
            cout << "\n=== Lista de Serviços ===" << endl;        
            selectServicoPorIdUser(dir, idUser);
        }

        loop = true;
    }
}

void login(Usuario& user, Prestador& prest, InformacoesPrestador& informacoes) {
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
        id = getUserID(dir, "user", login, senha);
        if (id != 0) { // Verifica se o ID é válido
            //cout << id << endl;
            //obterInformacoesPrestador(dir, id);
            TelaUser(informacoes, id);
        }
        else {
            cout << "Erro ao obter o ID do usuário." << endl;
        }
    }
    else if (tipo == PREST) {
        id = getUserID(dir, "prest", login, senha);
        if (id != 0) { // Verifica se o ID é válido
            //cout << id << endl;
            informacoes = obterInformacoesPrestador(dir, id); // Armazena as informações do prestador
            TelaTrabalhador(id, informacoes);
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
    InformacoesPrestador informacoes;
    int opcao = 0;
    int opcaoUser = 0;

    const char* dir = "C:\\prest\\prest.db";//onde vai ser salvo DB
    sqlite3* DB;// ponteiro usado para compartilhar o mesmo objeto sqlite3(DB)

    createDb(dir);
    createTable(dir);
    createTablePrestador(dir);
    createTableServico(dir);
   // selectServico(dir);
   // insertServico(dir);
    
    

    while (opcao != 8) {
        cout <<"+--------------------------------------------+\n";
        cout <<"|******** Bem Vindo A Tela De Inicio ********|\n"
            << "+--------------------------------------------+\n"
            << "|1-Cadastro:                                 |\n"
            << "|2-Login:                                    |\n"
            << "|3-Listar Usuario:                           |\n"
            << "|4-Listar Prestador:                         |\n"
            << "|5-Chat:                                     |\n"
            << "|6-Delete user:                              |\n"
            << "|7-Edita user:                               |\n"
            << "|8-Sair:                                     |\n"
            << "+--------------------------------------------+\n";
        cin >> opcao;
        switch (opcao) {
        case 1:
            cout << "+---------------+\n"
                << "|1-Usuario      |\n"
                << "+ --------------+\n"
                << "|2-Trabalhador  |\n"
                << "+---------------+\n";
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
            login(user, prest, informacoes);
            break;
        case 3:
            system("cls");
            selectData(dir);
            break;
        case 4:
            system("cls");
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
