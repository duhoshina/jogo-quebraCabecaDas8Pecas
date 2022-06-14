#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define STR_MAX 25
#define M_SIZE 3

/* ----------------------------------------- cores e formato de texto ---------------------------------------- */
#define ANSI_RESET            "\x1b[0m"  // desativa os efeitos anteriores
#define ANSI_BOLD             "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

/* --------------------------------- macros para facilitar o uso --------------------------------------------- */
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

/* ------------------------------------ caracteres uteis para tabelas -------------------------------------------------- */
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL  "\u250F" // ┏ (top-left)
#define TAB_ML  "\u2523" // ┣ (middle-left)
#define TAB_BL  "\u2517" // ┗ (bottom-left)
#define TAB_TJ  "\u2533" // ┳ (top-join)
#define TAB_MJ  "\u254B" // ╋ (middle-join)
#define TAB_BJ  "\u253B" // ┻ (bottom-join)
#define TAB_TR  "\u2513" // ┓ (top-right)
#define TAB_MR  "\u252B" // ┫ (middle-right)
#define TAB_BR  "\u251B" // ┛ (bottom-right)

/* ------------------------------------------ menus do jogo ----------------------------------------------------------- */
void menuInicial();
void menuInstrucoes();
void cmd(char*);

/* ----------------------------------------- Funcoes do jogo ---------------------------------------------------------- */
void jogo(int**, int*);
void embaralha(int**, int);
void salvar(int**, int*, char*);
void carregar(int**, int*);
bool verificaJogo(int**, int*);

/* ----------------------------------------- Funcoes da matriz -------------------------------------------------------- */
int **alocaMatriz();
void desalocaMatriz(int**);
void matrizInicial(int**, int*);
void imprimeMatriz(int **);

int main(){
    char *comando;
    comando = (char *) malloc(sizeof(char)*STR_MAX);

    char *comandoNivel;
    comandoNivel = (char *) malloc(sizeof(char)*STR_MAX);

    int **matriz;
    matriz = alocaMatriz();

    int *jogadas;
    jogadas = (int *) malloc(sizeof(int));
    printf("%s \n\n", "Bem vindo ao Quebra-Cabeças");

    bool jogoAnterior = false;

    do {
        menuInicial();
        cmd(comando);
        switch(*comando){
            case '0':
                free(jogadas);
                free(comando);
                free(comandoNivel);
                desalocaMatriz(matriz);
                exit(0);
            break;
            case '1':
                matrizInicial(matriz, jogadas);
                imprimeMatriz(matriz);
                printf("%s\n\n", "Tabuleiro ordenado!");
                
                printf("%s:", "Digite o nivel de dificuldade para embaralhar, fácil (1), médio (2) ou dificil (3)");
                
                scanf("%s", comandoNivel);

                if(strcmp(comandoNivel, "sair") == 0){
                        free(jogadas);
                        free(comando);
                        free(comandoNivel);
                        desalocaMatriz(matriz);
                        exit(0);
                }
                
                if(strcmp(comandoNivel, "voltar") == 0){
                    strcpy(comando, "voltar");
                    break;
                }
                

                switch(*comandoNivel){
                    case '1':
                        embaralha(matriz, 20);
                    break;
                    case '2':
                        embaralha(matriz, 40);
                    break;
                    case '3':
                        embaralha(matriz, 80);
                    break;
                }

                imprimeMatriz(matriz);
                printf("Tabuleiro embaralhado. Vamos começar o jogo!\n");

                jogo(matriz, jogadas);

            break;
            case '2':
                if(jogoAnterior){
                    jogo(matriz, jogadas);
                }else{
                    printf(BG_MAGENTA(BLACK("\n%s")), "Você não tem um jogo atual, comece um novo jogo!!");
                    printf("\n");
                }
            break;
            case '3':
                carregar(matriz, jogadas);
                jogo(matriz, jogadas);
            break;
            case '4':
                menuInstrucoes();
            break;
            default:
                if(strcmp(comando, "sair") != 0 && strcmp(comando, "salvar")!= 0 && strcmp(comando, "voltar")!= 0){
                    printf("%s\n", "Entrada inválida!");
                }
            break;
        }
    }while(strcmp(comando, "sair")!=0);

    free(jogadas);
    free(comando);
    free(comandoNivel);
    desalocaMatriz(matriz);
    return 0;
}

void menuInicial(){
    printf("\n%s \n", "0. Sair do Jogo");
    printf("%s \n", "1. Começar um novo jogo");
    printf("%s \n", "2. Continuar o jogo atual");
    printf("%s \n", "3. Continuar um jogo salvo");
    printf("%s \n\n", "4. Instruções do jogo");
}

void menuInstrucoes(){
    printf("\n%s \n\n", "INSTRUCOES");
    printf("%s \n", "O jogo quebra-cabeça das 8 pastilhas é bem fácil de jogar!");
    printf("%s \n", "Você deve mover as pastilhas para o espaço vazio.");
    printf("%s \n", "Contudo apenas as pastilhas adjacentes a esse espaço que podem ser movidas para ele.");
    printf("%s \n", "O jogo se encerra assim que você colocar as peças na ordem de 1 a 8.");
    printf("\n%s\n", "Você também tem a possibilidade de deixar o jogo a qualquer momento digitando 'sair'.");
    printf("%s\n", "Você também pode salvar o jogo que se encontra atualmente.");
    printf("%s\n", "Para isso basta você digira 'salvar nomedoaquivo.txt' para salvar em um");
    printf("%s\n","no arquivo arquivo.txt, que será criado ou então caso exista");
    printf("%s\n", "sobrescreverá o arquivo antigo.");
    printf("%s\n", "Em todas as telas com opções você pode digitar voltar para ir para o MENU INICIAL.");
}

void cmd(char *comando){
    char entrada[STR_MAX];
    printf("Escolha a opção (digite “sair” em qualquer lugar para sair do jogo): ");
    scanf("%s", entrada);
    strcpy(comando, entrada);
}

int **alocaMatriz(){
    int **m;
    m = (int **) malloc(sizeof(int*)*M_SIZE);

    for(int i = 0; i < M_SIZE; i++){
        m[i] = (int *) malloc(sizeof(int));
    }
    
    return m;
}

void desalocaMatriz(int **m){
    for(int i = 0; i < M_SIZE; i++){
        free(m[i]);
    }
    free(m);
}

void matrizInicial(int **m, int *j){
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    m[2][0] = 7;
    m[2][1] = 8;
    m[2][2] = 0;

    j = 0;
}

void imprimeMatriz(int **m){
    printf("\n\t\t" TAB_TL TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_HOR TAB_TR "\n");
	for(int i = 0; i < M_SIZE ; i++){
		printf("\t\t"TAB_VER);
		for(int j = 0; j < M_SIZE; j++){
			if(m[i][j] != 0){
				printf(" %d " TAB_VER, m[i][j]);
			}else{
				printf(" %s " TAB_VER, " ");
			}
		}
		if(i < M_SIZE-1){
			printf("\n\t\t" TAB_ML TAB_HOR TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_HOR TAB_MR "\n");
		}
	}
	printf("\n\t\t" TAB_BL TAB_HOR TAB_HOR TAB_HOR TAB_BJ TAB_HOR TAB_HOR TAB_HOR TAB_BJ TAB_HOR TAB_HOR TAB_HOR TAB_BR "\n");
	printf("\n\n");
}

void jogo(int **m, int *j){
    char *comandoJogo;
    comandoJogo = (char *) malloc(sizeof(char)*STR_MAX);

    do{
        printf("Digite um comando ou número da peça que quer mover: ");
        fflush(stdin); //limpar possiveis characteres no buffer de entrada
	    fgets(comandoJogo, STR_MAX-5, stdin); //string com espaços

        if(strcmp(comandoJogo, "sair") == 0){
            break;
        }

        if(strstr(comandoJogo,"salvar")){ //verifica se a palavra esta dentro do texto
			char *nomeArquivo = strtok(comandoJogo," "); //divide o texto separados por espaco
			nomeArquivo = strtok(NULL, " "); //pula pra proxima palavra
			salvar(m,j, nomeArquivo);
		}

        int p = strtol(comandoJogo, NULL, 10);
        if(p >= 1 || p <= 8){
            int linP = 0, colP = 0, linZero = 0, colZero = 0;
            bool achou = false; //verifica se encontrou a peca
            for(int i = 0; i < M_SIZE; i++){
                for(int j = 0; j < M_SIZE; j++){
                    if(m[i][j] == 0){ //procura o 0 no tabuleiro
                        linZero = i;
                        colZero = j;
                    }
                    if(m[i][j] == p){  //procura a peça no tabuleiro
                        linP = i;
                        colP = j;
                        achou = true;
                    }
                }
            }

            if(achou && ((linZero == linP && (colZero == colP+1 || colZero == colP-1)) ||
            (colZero == colP && (linZero == linP+1 || linZero == linP-1)))){
                m[linZero][colZero] = p;
                m[linP][colP] = 0;
                *j+= 1;
                printf("Quantidade de jogadas até agora: %d\n", *j);
            }else if(!achou){
                printf(BG_RED("%s"), "Essa peça não existe!");
                printf("\n");
            }
            else{
                printf("Não é possível mover a peça " BOLD("%d") ".\n\n", p);
            }
            if(verificaJogo(m,j))
                break;
        }
        imprimeMatriz(m);
    }while(strcmp(comandoJogo, "voltar"));

    free(comandoJogo);
}

void embaralha(int **matriz, int x){
    srand(time(NULL));
    int linZero = 2, colZero = 2, movimento = 0, movimentoAnterior = 1;
    for(int i = 0; i < x; i++){
        // printf("embaralha %d vzs\n", i);
        movimento = rand() % 4;
        while(((movimento == 0 && linZero == 0) || 
               (movimento == 1 && colZero == 2) || 
               (movimento == 2 && linZero == 2) || 
               (movimento == 3 && colZero == 0)) ||
               (movimento == 0 && movimentoAnterior == 2) ||
               (movimento == 2 && movimentoAnterior == 0) ||
               (movimento == 1 && movimentoAnterior == 3) ||
               (movimento == 3 && movimentoAnterior == 1))
            movimento = rand() % 4;

        printf("movimento: %d\n", movimento);
        if(movimento == 0){
            matriz[linZero][colZero] = matriz[(linZero-1)][colZero];
            matriz[(linZero-1)][colZero] = 0;
            linZero--;
        }
        if(movimento == 1){
            matriz[linZero][colZero] = matriz[linZero][(colZero+1)];
            matriz[linZero][(colZero+1)] = 0;
            colZero++;
        }
        if(movimento == 2){
            matriz[linZero][colZero] = matriz[(linZero+1)][colZero];
            matriz[(linZero+1)][colZero] = 0;
            linZero++;
        }
        if(movimento == 3){
            matriz[linZero][colZero] = matriz[linZero][(colZero-1)];
            matriz[linZero][(colZero-1)] = 0;
            colZero--;
        }
        // imprimeMatriz(matriz);
        movimentoAnterior = movimento;
    }
    printf("\n");
}

void salvar(int **m, int *j, char *f){
    FILE *pArq = NULL;
	pArq = fopen(f,"w");
	if( pArq == NULL ){
		printf(RED("\n%s\n"),"Erro ao abrir aquivo para salvar!!");
	}
	fprintf(pArq, "%s\n", "3");  
	for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++){
       		fprintf( pArq,"%d\t", m[i][j]);
   		}
		fprintf(pArq, "\n");
    }
	fprintf(pArq, "%d", *j);

	fclose(pArq);
}

void carregar(int **m, int *j){
	char *nomeArquivo;
    nomeArquivo = (char *) malloc(sizeof(char)*STR_MAX);

    int dimensao; //apenas para salvar a dimensao da matriz (como sera sempre 3 ela nao é usada para nada)
	FILE *pArq = NULL;
	
    printf("Digite o nome do arquivo: ");
	fflush(stdin);
	fgets(nomeArquivo, 20, stdin);
	
    pArq = fopen(nomeArquivo,"r");
	
    if(nomeArquivo == NULL){
		printf(BG_RED("\n%s\n"), "Erro ao tentar abrir arquivo para leitura!");
	}
	fscanf(pArq,"%d",&dimensao);

	for(int i = 0; i < M_SIZE; i++){
	    for(int j = 0; j < M_SIZE; j++){
	   		fscanf(pArq, "%d", &m[i][j]);
	    }
	}

	fscanf(pArq,"%d",j);
	fclose(pArq);
}

bool verificaJogo(int **m, int *j){
	if(m[0][0] == 1 && 
       m[0][1] == 2 && 
       m[0][2] == 3 &&
	   m[1][0] == 4 && 
       m[1][1] == 5 && 
       m[1][2] == 6 &&
	   m[2][0] == 7 && 
       m[2][1] == 8 && 
       m[2][2] == 0
	){
		printf(BG_GREEN("Parabéns! Você completou o quebra-cabeças com %d movimentos."), *j);
        printf("\n\n");
        return true;
	}
    return false;
}
