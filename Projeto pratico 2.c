//Nome: Vinicius Resende Caldeira
//Matricula: UC21100402
//Curso: Ciências da Computação

#include<stdio.h> //Tratamento de entrada/saída
#include<string.h> //Manipulação de strings
#include<stdlib.h> //Implementa funções para diversas operações
#include<locale.h> //Localização de programas
#include<ctype.h> //Manipulação de caracteres

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define BLU "\e[0;34m"
#define reset "\e[0m"

int numAssentos = 0;
char destino[50];
float passagem, rendaTotal = 0;

int reservar(void), idadeCliente(void), idAssento(void);
void defVoo(void), mapaAviao(void), cancelarReserva(void), confirmarVenda(void), mapaIds(char);

typedef struct {
    char status;
    float preco;
}assento;

assento assentos[205];

int main(){
    setlocale(LC_ALL, "Portuguese");
    int i,id,idade,numReservas=0,numVendas=0;
    char opcaoMenu,entrarMenu = 's';

    defVoo();
    for(i=0;i<numAssentos;i++){//inicializando assentos
        assentos[i].status = 'D';
    }

    while(toupper(entrarMenu) != 'N'){
        system("cls");
        printf("\n");
        printf("MENU\n");
        printf("\n----------CUIDADO----------\n");
        printf("UMA VEZ INICIADAS, AS OPERAÇÕES ABAIXO NÃO PODEM SER CANCELADAS!");
        printf("\n---------------------------\n");
        printf("1- MAPA DE OCUPAÇÃO DO VOO\n");
        printf("2- EFETUAR RESERVA\n");
        printf("3- CANCELAR UMA RESERVA\n");
        printf("4- CONFIRMAR UMA VENDA\n");
        printf("5- CONSULTAR TABELA COM VALOR DE VENDAS E QUANTIDADE DE ASSENTOS\n");
        printf("PRESSIONE QUALQUER OUTRA TECLA PARA SAIR DO MENU E ENCERRAR O PROGRAMA.\n");
        scanf("%c",&opcaoMenu);
        fflush(stdin);

        if(toupper(opcaoMenu) == '1'){//mostra o mapa do aviao
            system("cls");
            mapaAviao();
            printf("\nDESEJA VOLTAR PARA O MENU? (S / N)\n");
            printf("(NÃO VOLTAR PARA O MENU SIGNIFICA ENCERRAR O PROGRAMA)\n");
            scanf("%c",&entrarMenu);
            fflush(stdin);
        }
        else if(toupper(opcaoMenu) == '2'){//efetua uma reserva
            system("cls");
            if(numReservas < numAssentos){// roda apenas se existem assentos para serem reservados
                idade = idadeCliente();
                printf("\n\n------------------------------------------------\n");
                printf("ASSENTOS DISPONÍVEIS:\n");
                mapaIds('D');
                printf("\n------------------------------------------------\n\n");

                id = reservar();
                if(idade>5){assentos[id-1].preco = passagem;}
                else{assentos[id-1].preco = passagem/2.0;}
                system("cls");
                printf("ESSE SERÁ O PREÇO DA PASSAGEM PARA ESSE CLIENTE: R$ %.2f\n", assentos[id-1].preco);
                printf("O ASSENTO AINDA NÃO FOI COMPRADO, PARA CONCLUIR A VENDA, VÁ PARA O MENU E PRESSIONE V\n");
                numReservas++;
            }
            else{
                printf("TODOS OS ASSENTOS JÁ FORAM RESERVADOS OU VENDIDOS.\n");
            }
            printf("\nDESEJA VOLTAR PARA O MENU? (S / N)\n");
            printf("(NÃO VOLTAR PARA O MENU SIGNIFICA ENCERRAR O PROGRAMA)\n");
            scanf("%c",&entrarMenu);
            fflush(stdin);
        }
        else if(toupper(opcaoMenu) == '3'){//cancela uma reserva
            system("cls");
            if(numReservas>0){// roda apenas se existem reservas para serem canceladas
                printf("\n\n------------------------------------------------\n");
                printf("ASSENTOS RESERVADOS:\n");
                mapaIds('R');
                printf("\n------------------------------------------------\n\n");
                
                cancelarReserva();
                numReservas--;
            }
            else{printf("NÃO EXISTEM ASSENTOS RESERVADOS PARA SEREM CANCELADOS");}
            printf("\nDESEJA VOLTAR PARA O MENU? (S / N)\n");
            printf("(NÃO VOLTAR PARA O MENU SIGNIFICA ENCERRAR O PROGRAMA)\n");
            scanf("%c",&entrarMenu);
            fflush(stdin);
        }
        else if(toupper(opcaoMenu) == '4'){// confirma a venda de reservas
            system("cls");
            if(numReservas>0 && numVendas<numAssentos){//roda apenas se uma venda for possivel
                printf("\n\n------------------------------------------------\n");
                printf("ASSENTOS RESERVADOS:\n");
                mapaIds('R');
                printf("\n------------------------------------------------\n\n");
                confirmarVenda();
                numReservas--;
                numVendas++;
            }
            else{printf("NÃO EXISTEM ASSENTOS RESERVADOS PARA SEREM VENDIDOS");}
            printf("\nDESEJA VOLTAR PARA O MENU? (S / N)\n");
            printf("(NÃO VOLTAR PARA O MENU SIGNIFICA ENCERRAR O PROGRAMA)\n");
            scanf("%c",&entrarMenu);
            fflush(stdin);
        }
        else if(toupper(opcaoMenu) == '5'){//printa tabelas para assentos disponiveis reservados e vendidos
            system("cls");
            if(numReservas>0){
                printf("\n------------------------------------------------\n" RED);
                printf("ASSENTOS RESERVADOS:\n");
                for(i=0;i<numAssentos;i++){
                    if(assentos[i].status == 'R'){printf("RESERVA %d, VALOR A PAGAR: R$ %.2f\n", i+1, assentos[i].preco);}
                }
                printf(reset "\n------------------------------------------------\n");
            }
            else{printf(RED "NENHUM ASSENTO RESERVADO\n" reset);}

            if(numVendas<numAssentos && numReservas<numAssentos){
                printf("\n------------------------------------------------\n" GRN);
                printf("ASSENTOS DISPONÍVEIS:\n");
                for(i=0;i<numAssentos;i++){
                    if(assentos[i].status == 'D'){
                        printf("%d; ", i+1, assentos[i].preco);
                    }
                    if((i+1)%6==0){
                        printf("\n");
                    }
                }
                printf(reset "\n------------------------------------------------\n");
            }
            else{printf(GRN "NENHUM ASSENTO DISPONÍVEL\n" reset);}

            if(numVendas>0){
                printf("\n------------------------------------------------\n" BLU);
                printf("VENDAS CONFIRMADAS:\n");
                for(i=0;i<numAssentos;i++){
                    if(assentos[i].status == 'C'){printf("RESERVA %d VENDIDA: R$ %.2f\n", i+1, assentos[i].preco);}
                }
                printf("\n-----RENDA TOTAL: R$ %.2f-----", rendaTotal);
                printf(reset "\n------------------------------------------------\n");
            }
            else{printf(BLU "NENHUMA VENDA CONFIRMADA\n" reset);}
            printf("PARA O DESTINO DE %s\n",destino);
            printf("\nDESEJA VOLTAR PARA O MENU? (S / N)\n");
            printf("(NÃO VOLTAR PARA O MENU SIGNIFICA ENCERRAR O PROGRAMA)\n");
            scanf("%c",&entrarMenu);
            fflush(stdin);
        }
        else{// ve se o cara qr sair do menu e muda a variavel entrarMenu
            printf("VOCÊ DESEJA CONTINUAR NO MENU? \n(DIGITE N PARA SAIR, QUALQUER OUTRA TECLA TE LEVARÁ DE VOLTA AO MENU)\n");
            scanf("%c",&entrarMenu);
            fflush(stdin);
        }
    }
}

void defVoo(){//define quantos assentos o aviao possui, preco da passagem e o destino de voo

    while(destino[0] == '\0' ||destino[0] == '\n' || destino[0] == ' '){//definindo o destino
        printf("O VOO PRECISA DE UM DESTINO, INFORME-O: ");
        fgets(destino,50,stdin);
        fflush(stdin);
    }
    while(passagem <= 0.0){//definindo o preco da passagem
        printf("A PASSAGEM PRECISA DE UM PREÇO VÁLIDO\n");
        printf("QUAL É O PREÇO DA PASSAGEM?\n");
        scanf("%f",&passagem);
        fflush(stdin);
    }    
    while(numAssentos < 89 || numAssentos > 200){//definindo o numero de assentos
        printf("O AVIÃO DEVE POSSUIR DE 90 A 200 ASSENTOS\n");
        printf("QUANTOS ASSENTOS O AVIÃO POSSUI?\n");
        scanf("%d",&numAssentos);
        fflush(stdin);
    }
}

void cancelarReserva(){//cancela uma reserva valida
    int id = 0;
    while(id<1 || id>numAssentos || assentos[id-1].status != 'R'){
        printf("CANCELAMENTO DE RESERVA\n");
        printf("ESCOLHA UM ASSENTO RESERVADO (VERMELHO)\nE QUE EXISTA NA AERONAVE\n");
        printf("DIGITE O NÚMERO DA RESERVA (EQUIVALE AO NÚMERO DO ASSENTO RESERVADO): ");
        scanf("%d",&id);
        fflush(stdin);
    }
    assentos[id-1].status = 'D';
    assentos[id-1].preco = 0;
    printf("CANCELAMENTO DA RESERVA %d REALIZADO COM SUCESSO\n", id);
}

void confirmarVenda(){//confirma uma venda valida
    int id = 0;
    while(id<1 || id>numAssentos || assentos[id-1].status != 'R'){
        printf("CONFIRMAÇÃO DE VENDA\n");
        printf("ESCOLHA UM ASSENTO RESERVADO (VERMELHO)\nE QUE EXISTA NA AERONAVE\n");
        printf("DIGITE O NÚMERO DA RESERVA (EQUIVALE AO NÚMERO DO ASSENTO RESERVADO): ");
        scanf("%d",&id);
        fflush(stdin);
    }
    assentos[id-1].status = 'C';
    rendaTotal += assentos[id-1].preco;
    printf("VENDA DA RESERVA %d CONFIRMADA COM SUCESSO\n", id);
}

int reservar(){//efetua uma reserva caso as condicoes sejam satisfeitas
    int id = 0;
    while(id<1 || id>numAssentos || assentos[id-1].status != 'D'){
        printf("ESCOLHA UM ASSENTO DISPONÍVEL (VERDE)\nE QUE EXISTA NA AERONAVE\n");
        printf("DIGITE O NÚMERO DO ASSENTO REQUERIDO: ");
        scanf("%d",&id);
        fflush(stdin);
    }
    assentos[id-1].status = 'R';
    printf("ASSENTO %d RESERVADO COM SUCESSO\n", id);
    return id;
}

void mapaAviao(){//mostra mapa do aviao com assentos reservados disponiveis e vendidos
    int i;
    printf("---- MAPA DE OCUPAÇÃO DO VOO ----\n\n");
    for(i=0;i<numAssentos;i++){//para cada assento no aviao
        //color coding
        if(assentos[i].status == 'D'){
            printf(GRN "D " reset);
        }
        else if(assentos[i].status == 'R'){
            printf(RED "R " reset);
        }
        else{printf(BLU "C " reset);}

        if((i+1)%3==0){//se o numero e divisivel por 3
            if((i+1)%2==0){//se o numero e divisivel por 6
                printf("\n");// acaba uma fileira
                continue;
            }
            printf("||   || ");//acaba o conjunto de cadeiras e comeca o corredor do aviao
        }
    }
    printf("\n-------------------------------\n\n");
}

void mapaIds(char status){//mostra mapa de ids
    int i;
    char cor[10];
    if(status == 'D'){strcpy(cor, GRN);}
    else if(status == 'R'){strcpy(cor, RED);}
    else if(status == 'C'){strcpy(cor, BLU);}
    for(i=0;i<numAssentos;i++){//mostra assentos disponiveis em uma lista com 6 assentos por linha
        if(assentos[i].status == status){
            printf(cor);
        }
        printf("%d; ", i+1);
        if((i+1)%6==0){printf("\n");}
        printf(reset);
    }
}

int idadeCliente()//pega a idade de cada cliente e retorna o valor
{
    int idade;
    printf("INFORME IDADE DO CLIENTE: ");
    scanf("%d", &idade);
    fflush(stdin);
    while(idade<=0 || idade>110)//loop pra corrigir input
    {
        printf("VALOR INVÁLIDO PARA IDADE, APENAS VALORES DE 0 A 110 SERÃO ACEITOS\n");
        scanf("%d", &idade);
        fflush(stdin);
    }
    return idade;
}
