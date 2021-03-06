#include "funcoes.h"
#include <stdio.h>

int inicializa_estruturas(){

    int i = 0;

    for(i = 0; i < 10; i++){
        if(registroV[i].status != 1 && registroV[i].status != 2 && registroViagem[i].status != 3)
        registroV[i].status = 0;
    }

    for(i = 0; i < 10; i++){
        if(registroV[i].status != 1 && registroV[i].status != 2 && registroViagem[i].status != 3)
        registroV[i].quilometragem = 0;
    }

    for(i = 0; i < 10; i++){
        if(registroM[i].status != 1 && registroM[i].status != 2)
        registroM[i].status = 0;
    }

    for(i = 0; i < 30; i++){
        if(registroViagem[i].status != 1 && registroM[i].status != 2)
        registroViagem[i].status = 0;
    }

    return 1;
}


void cadastrar_motorista(){

    int i = 0;

    for(i = 0; i < 10; i++){
        if(registroM[i].status == 0)
            break;
    }
    printf("%d", i);
    if(i == 10){
        printf("Os cadastro já foram todos preenchidos");
    } else{
        system("cls");
        printf("\n\t\tCADASTRO DE MOTORISTAS");

        insere_informacao_motoristas(i);

        registroM[i].num_viagens = 0;

        registroM[i].status = 1;

        printf("\n\t-----Cadastro realizado com sucesso-----\n");
        printf("\n\n");
        system("pause");

        salvar_motorista();
    }
}


void cadastrar_veiculo(){

    int i = 0;

    for(i = 0; i < 10; i++){
        if(registroV[i].status == 0)
            break;
    }

    system("cls");
    printf("\n\t\tCADASTRO DE VEÍCULOS");

    insere_cadastro_veiculos(i);

    registroV[i].status = 1;

    printf("\n\t-----Cadastro realizado com sucesso-----\n");
    salvar_veiculo();
    system("pause");
}

void cadastrar_viagem(){

    int i = 0, opcao = 0;

    for(i = 0; i < 10; i++){
        if(registroViagem[i].status == 0)
            break;
    }

    system("cls");
    printf("\n\t\tCADASTRO DE VIAGENS");

    //--------------------------------------
    printf("\n\n\tMotoristas disponíveis: ");
    consultar_motorista_disponivel();

    printf("\n\tSelecionar *MOTORISTA: ");
    scanf("%d", &opcao);
    opcao--;

    registroM[opcao].status = 2;
    registroViagem[i].id_motorista = opcao;

    //--------------------------------------
    printf("\n\n\tVeículos disponíveis:");
    consultar_vDisponivel(i);

    printf("\n\tSelecionar *VEÍCULO: ");
    scanf("%d", &opcao);
    opcao--;

    registroV[opcao].status = 2;
    registroViagem[i].id_veiculo = opcao;

    //--------------------------------------
    printf("\n\tTamanho do percurso (Km): ");
    scanf("%f",&registroViagem[i].percorrido);

    printf("\n\t*ORIGEM: ");
    scanf(" %39[^\n]",registroViagem[i].origem);

    printf("\n\t*DESTINO: ");
    scanf(" %39[^\n]",registroViagem[i].destino);

    printf("\n\t*DATA INÍCIO (dd/mm/aa): ");
    fflush(stdin);
    scanf("%d/%d/%d", &registroViagem[i].data_inicio_dia, &registroViagem[i].data_inicio_mes, &registroViagem[i].data_inicio_ano);

    printf("\n\t*HORA INÍCIO (hh:mm): ");
    fflush(stdin);
    scanf("%d:%d", &registroViagem[i].hora_inicio_hh, &registroViagem[i].hora_inicio_mm);

    registroViagem[i].status = 1;

    printf("\n\t-----Cadastro realizado com sucesso-----\n");
    salvar_veiculo();
    salvar_motorista();
    salvar_viagem();
    system("pause");

}


void insere_informacao_motoristas(int i){

    if(i == 10){
        printf("\n\tO limite de cadastro excedido\n");
        system("pause");
    }else{
        printf("\n\n\t*NOME: ");
        scanf(" %39[^\n]",registroM[i].nome);

        printf("\n\t*CPF (Exemplo: 123.456.789-10): ");
        do{
            fflush(stdin);
            scanf(" %39[^\n]",registroM[i].cpf);
            if(registroM[i].cpf[3] != '.' || registroM[i].cpf[7] != '.' || registroM[i].cpf[11] != '-')
                printf("\n\tInsira corretamente: ");
        }while (registroM[i].cpf[3] != '.' || registroM[i].cpf[7] != '.' || registroM[i].cpf[11] != '-');

        printf("\n\t*TELEFONE (Exemplo: 0000-0000): ");
        do{
            fflush(stdin);
            scanf(" %39[^\n]", registroM[i].telefone);
            if(registroM[i].telefone[4] != '-')
                printf("\n\tInsira corretamente: ");
        }while (registroM[i].telefone[4] != '-');
    }
}

void insere_cadastro_veiculos(int i){

    if(i == 30){
        printf("\n\tO limite de cadastro excedido\n");
        system("pause");
        menu();
    } else{
        int tipo = 0;

        printf("\n\n\t*MARCA: ");
        scanf(" %39[^\n]",registroV[i].marca);

        printf("\n\t*MODELO: ");
        scanf(" %39[^\n]",registroV[i].modelo);

        printf("\n\t*PLACA (Exemplo: ABC-0000): ");
        do{
            scanf(" %39[^\n]",registroV[i].placa);
            if(registroV[i].placa[3] != '-')
                printf("\n\tInsira corretamente: ");
        }while (registroV[i].placa[3] != '-');

        printf("\n\t*ANO: ");
        scanf("%d",&registroV[i].ano);

        printf("\n\t*QUILOMETRAGEM (Km): ");
        scanf("%f",&registroV[i].quilometragem);

        printf("\n\t*TIPO: ");
        printf("\n\t\t1. Passeio");
        printf("\n\t\t2. Carga");
        printf("\n\t\t3. Transporte de passageiros");
        printf("\n\t\tOpção: ");
        scanf("%d",&tipo);

            switch(tipo){
                case PASSEIO:
                strcpy(registroV[i].tipo, "Passeio");
                break;

                case CARGA:
                strcpy(registroV[i].tipo, "Carga");
                break;

                case TRANSPORTE:
                strcpy(registroV[i].tipo, "Transporte de Passageiros");
                break;
            }
    }
}