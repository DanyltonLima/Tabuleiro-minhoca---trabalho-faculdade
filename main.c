//Materia Construcao de Algotritmo
//Professor: Eugenio
//Aluno: Danylton Lima 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 10
#define COLUNAS 10
void comecar_tabuleiro(char tabuleiro[LINHAS][COLUNAS]);
void construir_tabuleiro(char tabuleiro[LINHAS][COLUNAS]);
void inserir_obstaculos(char tabuleiro[LINHAS][COLUNAS], int n_obstaculos);
void inicio_minhoca(char tabuleiro[LINHAS][COLUNAS], int minhoca[5][2], int linha_cabeca, int coluna_cabeca, int mapa[LINHAS][COLUNAS]);
int movimento_valido(char tabuleiro[LINHAS][COLUNAS], int prox_linha, int prox_coluna);
void execucao_movimento(char tabuleiro[LINHAS][COLUNAS],int minhoca[5][2], int prox_linha_cabeca, int prox_coluna_cabeca, int mapa[LINHAS][COLUNAS]);
void inicio_mapa_casas_passadas(int mapa[LINHAS][COLUNAS]);
void posicao_e_registro(char tabuleiro[LINHAS][COLUNAS], int minhoca[5][2], int mapa[LINHAS][COLUNAS], int direcao);
void relatorio_final(int mapa[LINHAS][COLUNAS]);

int main()
{
    srand(time(NULL));
    char tabuleiro[LINHAS][COLUNAS];
    int minhoca[5][2];
    int casas_passadas[LINHAS][COLUNAS];

    int num_obstaculos; //numero de obstaculos
    int num_movimentos; //numero de movimentos
    int num_executados = 0; //numero de execu�oes
    int num_linha_cabeca_inicial; //variavel para guardar o valor inicial da linha
    int num_coluna_cabeca_inicial; //variavel para guardar o valor inicial da coluna
    int sorteio_direcao;
    int prox_num_linha_cabeca, prox_num_coluna_cabeca;

    comecar_tabuleiro(tabuleiro); //chamada do void
    inicio_mapa_casas_passadas(casas_passadas); //chamada de void
    construir_tabuleiro(tabuleiro); //chamada do segundo void

    printf("Quantos obstaculos voce quer no seu tabuleiro?\n");
    scanf("%d",&num_obstaculos);
    printf("Quantos movimentos a minhoca ira fazer?\n");
    scanf("%d", &num_movimentos);
    printf("Qual sera a linha da cabeca inicial? (0-9)\n");
    scanf("%d", &num_linha_cabeca_inicial);
    printf("Qual sera a coluna da cabeca incial? (0-9)\n");
    scanf("%d", &num_coluna_cabeca_inicial);

    inserir_obstaculos(tabuleiro, num_obstaculos); //chamada do void
    inicio_minhoca(tabuleiro, minhoca, num_linha_cabeca_inicial, num_coluna_cabeca_inicial, casas_passadas); //chamada de void

    printf("\n--pressione enter para iniciar o programa...\n");
    construir_tabuleiro(tabuleiro);
    getchar(); //isso � um pause
    getchar();
    for (int i = 0; i < num_movimentos; i++) {
        int direcoes_possiveis[4]; //aqui diz as dire��es v�lidas (0,1,2,3)
        int contador_de_opcoes = 0; //verifica as boas opcoes
        int linha_atual = minhoca[0][0]; //posic�o atual da linha da cabeca
        int coluna_atual = minhoca[0][1]; //posicao atual da coluna da cabeca
        //verificao das direcoes

        if (movimento_valido(tabuleiro, linha_atual - 1, coluna_atual) == 1){ //verifica pra cima
            direcoes_possiveis[contador_de_opcoes] = 0; // 0=cima
            contador_de_opcoes++;
        }

        if (movimento_valido(tabuleiro, linha_atual, coluna_atual + 1) == 1){ //verifica pra direita
            direcoes_possiveis[contador_de_opcoes] = 1; // 1=direita
            contador_de_opcoes++;
        }

        if (movimento_valido(tabuleiro, linha_atual + 1, coluna_atual) == 1){ //verifica pra baixo
            direcoes_possiveis[contador_de_opcoes] = 2; // 2=baixo
            contador_de_opcoes++;
        }

        if (movimento_valido(tabuleiro, linha_atual, coluna_atual - 1) == 1){ //verifica pra esquerda
            direcoes_possiveis[contador_de_opcoes] = 3; // 3=esquerda
            contador_de_opcoes++;
        }
        if (contador_de_opcoes > 0){
            int indice_sorteio = rand() % contador_de_opcoes;
            int direcao_final = direcoes_possiveis[indice_sorteio];
            int prox_linha_cabeca = linha_atual;
            int prox_coluna_cabeca = coluna_atual;

            if (direcao_final == 0){ //cima
                prox_linha_cabeca--;
            } else if (direcao_final == 1) { //direita
                prox_coluna_cabeca++;
            } else if (direcao_final == 2) { //baixo
                prox_linha_cabeca++;
            } else { //esquerda
                prox_coluna_cabeca--;}
            execucao_movimento(tabuleiro, minhoca, prox_linha_cabeca, prox_coluna_cabeca, casas_passadas);
        } else {
            printf("ALERTA: A minhoca nao esta se movendo, esta presa!\n");
        }
    construir_tabuleiro(tabuleiro);
    printf("\n-- Movimento de %d de %d --\n", i + 1, num_movimentos);
    printf("pressione enter para continuar...");
    getchar();
}
relatorio_final(casas_passadas);
printf("\n-- O passeio terminou! --\n");
return 0;
}

void comecar_tabuleiro(char tabuleiro[LINHAS][COLUNAS]){
    for(int i = 0; i < LINHAS; i++) { //i=linhas
        for(int j = 0; j < COLUNAS; j++) { //j=colunas
            tabuleiro[i][j] = '.'; // aqui � para colocar um ponto em determinado lugar como: linha 1, coluna 2
        }
    }
}
void construir_tabuleiro(char tabuleiro[LINHAS][COLUNAS]){
    system("cls");
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            printf("%c ", tabuleiro[i][j]);
        }
         printf("\n");
    }
}
void inserir_obstaculos(char tabuleiro[LINHAS][COLUNAS], int n_obstaculos){
        for (int i = 0; i < n_obstaculos; i++){
            int linha_aleatoria;
            int coluna_aleatoria;
            // "do" vai ficar sorteando at� encontrar uma casa vazia
            do{
                linha_aleatoria = rand() % LINHAS;
                coluna_aleatoria = rand() % COLUNAS;
            } while (tabuleiro[linha_aleatoria][coluna_aleatoria] != '.'); //repetir o sorteio se a casa n�o estiver sem nada
            tabuleiro[linha_aleatoria][coluna_aleatoria] = '#';
        }
}
void inicio_minhoca(char tabuleiro[LINHAS][COLUNAS], int minhoca[5][2], int linha_cabeca, int coluna_cabeca, int mapa[LINHAS][COLUNAS]) {
    printf("\n-DEBUG: Entrando na funcao inicio_minhoca\n");
    printf("DEBUG: recebendo as coordenadas: Linha %d, Coluna %d\n", linha_cabeca, coluna_cabeca);
    printf("DEBUG: antes de mudar, a casa [%d][%d] tem: '%c'\n", linha_cabeca, coluna_cabeca, tabuleiro[linha_cabeca][coluna_cabeca]);

    if (tabuleiro[linha_cabeca][coluna_cabeca] != '.'){
        printf("ALERTA: N�o foi possivel criar a minhoca. A posicao da cabeca esta ocupada!\n");
        return;
    }
    minhoca[0][0] = linha_cabeca;
    minhoca[0][1] = coluna_cabeca;
    tabuleiro[linha_cabeca][coluna_cabeca] = 'C';


    if (coluna_cabeca - 4 >= 0 && tabuleiro[linha_cabeca][coluna_cabeca - 1] == '.' && tabuleiro[linha_cabeca][coluna_cabeca - 2] == '.' && tabuleiro[linha_cabeca][coluna_cabeca - 3] == '.' && tabuleiro[linha_cabeca][coluna_cabeca - 4] == '.'){
        posicao_e_registro(tabuleiro, minhoca, mapa, 3);
    }
    else if (coluna_cabeca + 4 < COLUNAS && tabuleiro[linha_cabeca][coluna_cabeca + 1] == '.' && tabuleiro[linha_cabeca][coluna_cabeca + 2] == '.' && tabuleiro[linha_cabeca][coluna_cabeca + 3] == '.' && tabuleiro[linha_cabeca][coluna_cabeca + 4] == '.'){
        posicao_e_registro(tabuleiro, minhoca, mapa, 1);
    }
    else if (linha_cabeca - 4 >= 0 && tabuleiro[linha_cabeca - 1][coluna_cabeca] == '.' && tabuleiro[linha_cabeca - 2][coluna_cabeca] == '.' && tabuleiro[linha_cabeca - 3][coluna_cabeca] == '.' && tabuleiro[linha_cabeca - 4][coluna_cabeca] == '.'){
        posicao_e_registro(tabuleiro, minhoca, mapa, 0);
    }
    else if (linha_cabeca + 4 < LINHAS && tabuleiro[linha_cabeca + 1][coluna_cabeca] == '.' && tabuleiro[linha_cabeca + 2][coluna_cabeca] == '.' && tabuleiro[linha_cabeca + 3][coluna_cabeca] == '.' && tabuleiro[linha_cabeca + 4][coluna_cabeca] == '.'){
        posicao_e_registro(tabuleiro, minhoca, mapa, 2);
    }
    else{
        printf("ALERTA: Impossivel posicionar o corpo da minhoca! Nenhuma direcao e valida a partir de (%d, %d).\n", linha_cabeca, coluna_cabeca);
    }
}
int movimento_valido(char tabuleiro[LINHAS][COLUNAS], int prox_linha, int prox_coluna) {
    if (prox_linha < 0 || prox_linha >= LINHAS || prox_coluna < 0 || prox_coluna >= COLUNAS){
       return 0; //esse "return" e para saber se a posi�ao esta dentro do tabuleiro
    }
    if (tabuleiro[prox_linha][prox_coluna] != '.'){
        return 0; //esse "return" e para verificar se a posicao nao esta ocupada
    }
    return 1; //esse return � caso a posicao esteja vazia
}
void execucao_movimento(char tabuleiro[LINHAS][COLUNAS], int minhoca[5][2], int prox_linha_cabeca, int prox_coluna_cabeca, int mapa[LINHAS][COLUNAS]) {
    int cauda_antiga_linha = minhoca[4][0];
    int cauda_antiga_coluna = minhoca[4][1];

    for (int i = 4; i > 0; i--) {
        minhoca[i][0] = minhoca[i-1][0]; //aqui acontece a troca de linha, ela receba da parte da frente
        minhoca[i][1] = minhoca[i-1][1]; //aqui acontece a troca de coluna
    }

    minhoca[0][0] = prox_linha_cabeca;
    minhoca[0][1] = prox_coluna_cabeca;

    mapa[minhoca[0][0]][minhoca[0][1]] = 1;

    tabuleiro[cauda_antiga_linha][cauda_antiga_coluna] = '.';
    tabuleiro[minhoca[0][0]][minhoca[0][1]] = 'C';
    for (int i = 1; i < 4; i++){
        tabuleiro[minhoca[i][0]][minhoca[i][1]] = '*';
    }
    tabuleiro[minhoca[4][0]][minhoca[4][1]] = 250;
}
void inicio_mapa_casas_passadas(int mapa[LINHAS][COLUNAS]){
     for(int i = 0; i < LINHAS; i++) { //i=linhas
        for(int j = 0; j < COLUNAS; j++) { //j=colunas
            mapa[i][j] = 0; // aqui � para colocar um ponto em determinado lugar como: linha 1, coluna 2
        }
    }
}
void posicao_e_registro(char tabuleiro[LINHAS][COLUNAS], int minhoca[5][2], int mapa[LINHAS][COLUNAS], int direcao){
    int linha_cabeca = minhoca[0][0];
    int coluna_cabeca = minhoca[0][1];

    for (int i = 1; i < 5; i++){
        switch (direcao){
            case 0: //cima
                minhoca[i][0] = linha_cabeca - i;
                minhoca[i][1] = coluna_cabeca;
                break;
            case 1: //direita
                minhoca[i][0] = linha_cabeca;
                minhoca[i][1] = coluna_cabeca + i;
                break;
            case 2: //baixo
                minhoca[i][0] = linha_cabeca + i;
                minhoca[i][1] = coluna_cabeca;
                break;
            case 3: //esquerda
                minhoca[i][0] = linha_cabeca;
                minhoca[i][1] = coluna_cabeca - i;
                break;
        }
        if (i == 4){
            tabuleiro[minhoca[i][0]][minhoca[i][1]] = 250; //cauda
        } else {
            tabuleiro[minhoca[i][0]][minhoca[i][1]] = '*'; //corpo
        }
    }
    for (int k = 0; k < 5; k++){
        mapa[minhoca[k][0]][minhoca[k][1]] = 1;
    }
    printf("DEBUG: minhoca posicionada e registrada na direcao %d.\n", direcao);
}
void relatorio_final(int mapa[LINHAS][COLUNAS]){
    int casas_visitadas = 0;
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            if (mapa[i][j] == 1){
                casas_visitadas++;
            }
        }
    }
    int casas_nao_visitadas = (LINHAS * COLUNAS) - casas_visitadas;
    printf("\n--RELATORIO FINAL--\n");
    printf("Casas passadas pela minhoca: %d\n", casas_visitadas);
    printf("Casas nao passadas: %d\n", casas_nao_visitadas);
    printf("\n-----------------------------------------\n");
}
