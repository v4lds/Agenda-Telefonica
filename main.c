#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define Class struct

Class Agenda {
    int id;
    char nome[50];
    char n_tel[11];
};

Class Agenda lista_contatos[20];
int tam_lista = 0;
int sequencial_id = 1;


FILE* carregandoArquivo(){

    FILE *agenda;
    agenda = fopen(".agenda.txt", "r");

    if (agenda == NULL){
        agenda = fopen(".agenda.txt","w");
    }
    return agenda;
}

void carregandoDados(FILE* arq){

    int result;

    while (!feof(arq)){
        Class Agenda c;
        result = fscanf(arq,"%d %s %s",&c.id,&c.nome,&c.n_tel);
        if (result != EOF){
            addList(c);
            sequencial_id++;
        }
    }
    fclose(arq);
}

void addList(Class Agenda c){
    lista_contatos[tam_lista] = c;
    tam_lista++;
}

void salva_contato(Class Agenda c){
    FILE* arq;
    arq = fopen(".agenda.txt", "a");
    fprintf(arq,"%d %s %s\n",c.id,c.nome,c.n_tel);
    fclose(arq);
}

void adicionar_contato(){
    titulo_generico("ADICIONAR CONTATO");
    Class Agenda c;
    c.id = sequencial_id++;

    printf("Digite o nome do contato: ");
    scanf("%s",&c.nome);

    printf("Digite o número de telefone: ");
    scanf("%s",&c.n_tel);

    addList(c);

    salva_contato(c);

    system("cls");
}

void imprimir_contato(Class Agenda c){
    printf("ID: %d.\n",c.id);
    printf("Nome: %s.\n",c.nome);
    printf("Número: %s\n",c.n_tel);
}

void imprimir_lista(){
    titulo_generico("LISTA DE CONTATOS:");
    for(int i =0;i<tam_lista;i++){
        Class Agenda c = lista_contatos[i];

        printf("ID: %d.\n",c.id);
        printf("Nome: %s.\n",c.nome);
        printf("Número: %s.\n\n",c.n_tel);
    }
}

int menuGenerico(char* menu[], int qtde){
    int index = 0;
    int escolha = 0;
    while (index <qtde){
        printf("%s\n",menu[index]);
        index++;
    }
    printf("Selecione uma opção: ");
    scanf("%d",&escolha);
    return escolha;

}

void remover_contato(c){
    int id_remove = 0;
    int id_busca = 0;
    printf("\n\nDigite o ID do contato que você deseja remover: ");
    scanf("%d",&id_remove);
    id_busca = id_remove;
    find_by_id(id_busca);
}

int find_by_id(id_busca){

    int id_buscado = 0;

    id_buscado = id_busca;
    for (int index = 0; index <= tam_lista; index++){

        Class Agenda c = lista_contatos[index];

        if (c.id == id_buscado){
            system("cls");
            imprimir_contato(c);
            system("pause");
            return c.id;
        }
    }
    printf("Contato não encontrado.\n");
    system("pause");
}

void find_by_name(){

    char nome_buscado[50];

    printf("Digite o nome do contato que deseja encontrar: ");
    scanf("%s",&nome_buscado);

    for (int index = 0; index <= tam_lista; index++){

        Class Agenda c = lista_contatos[index];
        int comp_nome = strcmp(c.nome, nome_buscado);
        if (comp_nome == 0){
                system("cls");
            imprimir_contato(c);
            system("pause");
            return;
        }
    }
    printf("Contato não encontrado.\n");
    system("pause");
}

void find_by_n_tel(){

    char tel_buscado[11];

    printf("Digite o número de telefone do contato que deseja encontrar: ");
    scanf("%s",&tel_buscado);

    for (int index = 0; index <= tam_lista; index++){

        Class Agenda c = lista_contatos[index];
        int comp_nome = strcmp(c.n_tel, tel_buscado);
        if (comp_nome == 0){
            system("cls");
            imprimir_contato(c);
            system("pause");
            return;
        }
    }
    printf("Contato não encontrado.\n");
    system("pause");
}

void titulo_generico(char* titulo[]){

    printf("------------------\n");
    printf("%s\n",titulo);
    printf("------------------\n");
}

int main() {
    setlocale(LC_ALL,"Portuguese");

    FILE* arq = carregandoArquivo();
    carregandoDados(arq);

    char* escolhas[] = {"[1] Adicionar um contato na lista.",
                        "[2] Remover um contato da lista.",
                        "[3] Listar todos os contatos.",
                        "[4] Buscar por item.",
                        "[5] Finalizar programa."};

    //Esse menu é chamado na opcao 4 do menu escolhas.
    char* menu_busca[] = {"[1] Buscar por ID.",
                          "[2] Buscar por nome.",
                          "[3] Buscar pelo número.",
                          "[4] Voltar."};

    int choice = 0;
    int opcao_selecionada = 0;
    int opcao_busca = 0;

    while (choice < 5){

        titulo_generico("AGENDA DE CONTATOS");

        opcao_selecionada = menuGenerico(escolhas, 5);

        choice = opcao_selecionada;

        system("cls");
        switch (opcao_selecionada) {

            case 1:
                system("cls");
                adicionar_contato();
                break;
            case 2:
                system("cls");
                titulo_generico("REMOVER CONTATO");
                imprimir_lista();
                remover_contato();
                break;
            case 3:
                system("cls");
                imprimir_lista();
                system("pause");
                system("cls");
                break;
            case 4:
                while (opcao_busca != 4){
                    titulo_generico("MENU DE BUSCA");
                    opcao_busca = menuGenerico(menu_busca,4);
                    if (opcao_busca == 1){
                        system("cls");
                        titulo_generico("FILTRO DE BUSCA: ID");
                        int id_busca = 0;
                        printf("Digite o ID do contato que deseja encontrar: ");
                        scanf("%d",&id_busca);
                        find_by_id(id_busca);
                        system("cls");
                    } else if (opcao_busca == 2){
                        system("cls");
                        titulo_generico("FILTRO DE BUSCA: NOME");
                        find_by_name();
                        system("cls");
                    } else if (opcao_busca == 3){
                        system("cls");
                        titulo_generico("FILTRO DE BUSCA: NÚMERO DE TELEFONE");
                        find_by_n_tel();
                        system("cls");
                    } else if (opcao_busca == 4){
                        opcao_busca = 0;
                        break;
                    } else {
                        system("cls");
                        printf("Opção inválida.");
                        system("pause");
                    }
                }
                system("cls");
                break;
            case 5:
                break;
            default:
                printf("Opção inválida.");
                break;
        }
    }
}
