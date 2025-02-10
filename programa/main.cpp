#include <iostream> // Permite a entrada e saída de dados
#include <iomanip> // Permite manipular os dados de entrada e saída (como formatação de números)
#include <string> // Adiciona a funcionalidade de strings, que são cadeias de caracteres
#include <map> // Adiciona maps, que possuem a estrutura de chave-valor
#include <vector> // Adiciona a estrutura de vector, que permite criar arrays dinâmicos
#include <ctime> // Permite que receba a data e hora em tempo real
#include <limits> // Para usar numeric_limits, que controla os limites de tipos numéricos
#include <locale> // Para configurar o locale e poder usar caracteres especiais (como acentos)

using namespace std;

// Estrutura para armazenar informações de vendas
struct Venda {
    string produto; // Nome do Produto
    int quantidade; // Quantidade de Produtos Comprados
    double total; // Total da Compra 
    time_t data; // Data e hora da compra
};

// Banco de dados de produtos e histórico de vendas
map<string, double> produtos; // Armazena os produtos e seus preços em um 'map'
vector<Venda> historicoVendas; // Armazena as vendas realizadas em um vetor que vai aumentando de acordo com o número de vendas realizadas

// Função para inicializar os produtos fictícios
void inicializarProdutos() {
    // Adiciona produtos fictícios ao mapa 'produtos' (nome e preço)
    produtos["Camiseta"] = 29.90;
    produtos["Calca Jeans"] = 89.90;
    produtos["Tenis Esportivo"] = 159.90;
    produtos["Jaqueta de Couro"] = 199.90;
    produtos["Bone"] = 19.90;
    produtos["Relogio"] = 120.50;
    produtos["Mochila"] = 69.90;
    produtos["Fone de Ouvido"] = 79.90;
    produtos["Caderno"] = 15.50;
    produtos["Caneta"] = 2.50;
}

// Função para exibir todos os produtos (Sem retorno de valores)
void listarProdutos() {
    if (produtos.empty()) { // Verifica se há produtos cadastrados
        cout << "Nenhum produto cadastrado.\n"; // Exibe mensagem caso não haja produtos
        return; // Sai da função
    }
    cout << "\n--- Produtos Disponíveis ---\n"; // Cabeçalho para listagem
    cout << left << setw(20) << "Produto" << "Preço (R$)" << endl; // Exibe os títulos das colunas
    cout << "-----------------------------\n"; // Linha separadora

    // Iteração sem decomposição estruturada
    for (map<string, double>::const_iterator it = produtos.begin(); it != produtos.end(); ++it) {
        string nome = it->first;      // Chave do mapa (nome do produto)
        double preco = it->second;    // Valor do mapa (preço do produto)
        cout << left << setw(20) << nome << fixed << setprecision(2) << preco << endl; // Exibe produto e preço formatado
    }
}

// Função para adicionar ou editar um produto
void editarProduto() {
    string nome;
    double preco;

    cout << "\nDigite o nome do produto: "; // Solicita o nome do produto
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada
    getline(cin, nome); // Lê o nome do produto com possíveis espaços

    if (nome.empty()) { // Verifica se o nome é vazio
        cout << "Nome do produto não pode ser vazio.\n"; // Exibe mensagem de erro
        return; // Sai da função
    }

    cout << "Digite o preço do produto: R$"; // Solicita o preço do produto
    cin >> preco; // Lê o preço

    if (cin.fail() || preco <= 0) { // Verifica se o preço é válido
        cin.clear(); // Limpa o estado de erro de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada
        cout << "Preço inválido. Deve ser um número positivo.\n"; // Exibe mensagem de erro
        return; // Sai da função
    }

    produtos[nome] = preco; // Atualiza ou adiciona o produto no mapa
    cout << "Produto atualizado/adicionado com sucesso!\n"; // Exibe confirmação
}

// Função para realizar uma compra
void realizarCompra() {
    string nome;
    int quantidade;
    double totalCompra = 0.0; // Armazena o total da compra
    map<string, int> carrinho; // Armazena os itens do carrinho de compras

    while (true) { // Laço para realizar compras até o usuário decidir parar
        listarProdutos(); // Exibe os produtos disponíveis
        cout << "\nDigite o nome do produto para adicionar ao carrinho (ou 'fim' para finalizar): "; // Solicita o nome do produto
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
        getline(cin, nome); // Lê o nome do produto

        if (nome == "fim") break; // Se o usuário digitar "fim", sai do laço

        if (produtos.find(nome) != produtos.end()) { // Verifica se o produto existe no mapa
            cout << "Digite a quantidade: "; // Solicita a quantidade do produto
            cin >> quantidade; // Lê a quantidade

            if (cin.fail() || quantidade <= 0) { // Verifica se a quantidade é válida
                cin.clear(); // Limpa o estado de erro de cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
                cout << "Quantidade inválida. Tente novamente.\n"; // Exibe mensagem de erro
                continue; // Continua o laço
            }

            carrinho[nome] += quantidade; // Adiciona a quantidade ao carrinho
            cout << quantidade << " unidade(s) de " << nome << " adicionada(s) ao carrinho.\n"; // Exibe confirmação
        } else {
            cout << "Produto não encontrado. Tente novamente.\n"; // Exibe erro se o produto não existir
        }
    }

    if (carrinho.empty()) { // Verifica se o carrinho está vazio
        cout << "Nenhum produto foi adicionado ao carrinho.\n"; // Exibe mensagem
        return; // Sai da função
    }

    cout << "\n--- Recibo da Compra ---\n"; // Cabeçalho do recibo

    // Iteração sem decomposição estruturada
    for (map<string, int>::const_iterator it = carrinho.begin(); it != carrinho.end(); ++it) {
        string produto = it->first; // Nome do produto
        int qtd = it->second; // Quantidade do produto
        double subtotal = qtd * produtos[produto]; // Calcula o subtotal para o produto
        totalCompra += subtotal; // Acumula o total da compra

        cout << left << setw(20) << produto << "Qtd: " << setw(3) << qtd << " Subtotal: R$" << fixed << setprecision(2) << subtotal << endl; // Exibe produto, quantidade e subtotal

        historicoVendas.push_back({produto, qtd, subtotal, time(nullptr)}); // Adiciona a venda ao histórico
    }
    cout << "Total da Compra: R$" << fixed << setprecision(2) << totalCompra << endl; // Exibe o total da compra
}

// Função para exibir o histórico de vendas
void gerarRelatorio() {
    if (historicoVendas.empty()) { // Verifica se há vendas registradas
        cout << "Nenhuma venda registrada.\n"; // Exibe mensagem de erro
        return; // Sai da função
    }

    cout << "\n--- Histórico de Vendas ---\n"; // Cabeçalho do relatório
    cout << left << setw(20) << "Produto" << setw(10) << "Qtd" << setw(15) << "Total (R$)" << "Data/Hora" << endl; // Títulos das colunas
    cout << "--------------------------------------------------\n"; // Linha separadora

    for (vector<Venda>::const_iterator it = historicoVendas.begin(); it != historicoVendas.end(); ++it) {
        const Venda& venda = *it; // Obtém a venda
        tm* dt = localtime(&venda.data); // Converte a data para formato local
        char buffer[80]; // Buffer para armazenar a data formatada
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", dt); // Formata a data

        cout << left << setw(20) << venda.produto << setw(10) << venda.quantidade << setw(15) << fixed << setprecision(2) << venda.total << buffer << endl; // Exibe os dados da venda
    }
}

int main() {
    // Inicializa os produtos fictícios
    inicializarProdutos(); // Chama a função para adicionar produtos fictícios

    setlocale(LC_ALL, "pt_BR.UTF-8"); // Configura o locale para UTF-8
    int opcao; // Variável para armazenar a opção escolhida pelo usuário

    while (true) { // Laço principal do menu
        cout << "\n--- Menu Principal ---\n"; // Cabeçalho do menu
        cout << "1. Listar produtos\n"; // Opção 1
        cout << "2. Adicionar/Editar produto\n"; // Opção 2
        cout << "3. Realizar compra\n"; // Opção 3
        cout << "4. Gerar relatório de vendas\n"; // Opção 4
        cout << "5. Sair\n"; // Opção 5
        cout << "Escolha uma opção: "; // Solicita a opção
        cin >> opcao; // Lê a opção

        if (cin.fail()) { // Verifica se a entrada é válida
            cin.clear(); // Limpa o estado de erro de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
            cout << "Entrada inválida. Tente novamente.\n"; // Exibe mensagem de erro
            continue; // Continua o laço
        }

        switch (opcao) { // Ação com base na opção escolhida
            case 1:
                listarProdutos(); // Chama a função de listar produtos
                break;
            case 2:
                editarProduto(); // Chama a função para editar produtos
                break;
            case 3:
                realizarCompra(); // Chama a função para realizar uma compra
                break;
            case 4:
                gerarRelatorio(); // Chama a função para gerar o relatório de vendas
                break;
            case 5:
                cout << "Saindo...\n"; // Exibe mensagem de saída
                return 0; // Sai do programa
            default:
                cout << "Opção inválida. Tente novamente.\n"; // Exibe erro para opção inválida
        }
    }
}
