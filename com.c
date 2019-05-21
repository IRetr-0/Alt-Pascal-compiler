//MARLON MELO - 41610547
//CARLITO TORIBIO - 4143774
//ANDRE NEUBERT - 41639537
//RAFAEL ROMERO - 31608914

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ID 11

#define NUMBER 21
#define TRUE 22
#define FALSE 23

#define ADDITION 31
#define SUBTRACTION 32
#define MULTIPLICATION 33
#define DIVISION 34
#define MORETHAN 35
#define MOREEQUALTHAN 36
#define LESSTHAN 37
#define LESSEQUALTHAN 38
#define EQUALS 39
#define ATTRIBUTION 30

#define AND 41
#define OR 42
#define NOT 43

#define DOT 51
#define COMMA 52
#define COLON 53
#define SEMICOLON 54
#define OPARENTHESES 55
#define CPARENTHESES 56

#define PROGRAM 61
#define BEGIN 62
#define END 63
#define PROCEDURE 64
#define IF 65
#define THEN 66
#define ELSE 67
#define WHILE 68
#define DO 69
#define VAR 60
#define WRITE 70  

#define INT 71
#define BOOL 72

#define COMMENT 666

#define ERROR 0

//Declarando:
int PROGRAMA(char tokbuffer[], int *pos);
int BLOCO(char tokbuffer[], int *pos);
int PARTE_DECLARACOES_VARIAVEIS(char tokbuffer[], int *pos);
int DECLARACAO_VARIAVEIS(char tokbuffer[], int *pos);
int LISTA_IDENTIFICADORES(char tokbuffer[], int *pos);
int PARTE_DECLARACOES_SUBROTINAS(char tokbuffer[], int *pos);
int DECLARACAO_PROCEDIMENTO(char tokbuffer[], int *pos);
int PARAMETROS_FORMAIS(char tokbuffer[], int *pos);
int PARAMETRO_FORMAL(char tokbuffer[], int *pos);
int TIPO(char tokbuffer[], int *pos);
int COMANDO_COMPOSTO(char tokbuffer[], int *pos);
int COMANDO(char tokbuffer[], int *pos);
int ATRIBUICAO(char tokbuffer[], int *pos);
int CHAMADA_PROCEDIMENTO(char tokbuffer[], int *pos);
int LISTA_PARAMETROS(char tokbuffer[], int *pos);
int COMANDO_CONDICIONAL(char tokbuffer[], int *pos);
int COMANDO_REPETITIVO(char tokbuffer[], int *pos);
int EXPRESSAO(char tokbuffer[], int *pos);
int RELACAO(char tokbuffer[], int *pos);
int EXPRESSAO_SIMPLES(char tokbuffer[], int *pos);
int TERMO(char tokbuffer[], int *pos);
int FATOR(char tokbuffer[], int *pos);
int VARIAVEL(char tokbuffer[], int *pos);
int BOOLEANO(char tokbuffer[], int *pos);
int IDENTIFICADOR(char tokbuffer[], int *pos);
int NUMERO(char tokbuffer[], int *pos);

char toktranslate(int inttok);
void append(char* s, char c);
void trataErro();
int match(char t, char tokbuffer[], int *pos);
int scanner(char tokbuffer[]);
char * abreLeArquivo(char *arquivo);

//global
char lookahead;
int gambi;
int arra;
//Token como um int
int inttok;
//Lexema atual
char *palavra;
//Separador de palavras
char delimit[] = " \t\r\n\v\f"; //Ignorados para separar a string

//_____________________________________MAIN_____________________________________
int main(){

	//Buffer com todos os tokens, adicionados cada vez que o scanner faz um pedido
	char tokbuffer[500];
	
	//Buffer com todos os lexemas do arquivo de entrada
	char *input;
	input = abreLeArquivo("entrada.txt");
	
	//Palavra = Lexema atual, nesse caso o primeiro lexema
	palavra = strtok(input, delimit);// Separando o buffer em tokens
	
	//Adicionando um espaco no fim da palavra -> palavra$
	char c = ' ';
	size_t len = strlen(palavra);
	char *palavra$ = malloc(len + 1 + 1 );
	strcpy(palavra$, palavra);
	palavra$[len] = c;
	palavra$[len + 1] = '\0';
	
	//ANALISE SINTATICA PEDINDO TOKEN PARA ANALISE LEXICA
	//Analise lexica do token e traducao desse token int para char adiciona no vetor de tokens
	inttok = scanner(palavra$);
	append(tokbuffer, toktranslate(inttok));
	
	//lookahead recebendo primeiro token
	int pos = 0;
	lookahead = tokbuffer[pos];
	//printf(">>>%c\n",lookahead);
	
	//Se o lookahead for comentario pegar prox token
	while (lookahead == 'c'){
		palavra = strtok(NULL, delimit);
		printf(">>>%s",palavra);
		len = strlen(palavra);
		palavra$ = malloc(len + 1 + 1 );
		strcpy(palavra$, palavra);
		palavra$[len] = c;
		palavra$[len + 1] = '\0';
		inttok = scanner(palavra$);
		append(tokbuffer, toktranslate(inttok));
		lookahead = tokbuffer[++(pos)];

	}
	
	if (PROGRAMA(tokbuffer, &pos)){
	    printf("\nSequencia de tokens %s reconhecidos\n", tokbuffer);
		printf("\nFIM DA ANALISE SINTATICA\n");
	}
	else 
	    trataErro();
	
	return 0;
}

char toktranslate(int inttok){
	switch(inttok){
		case ID:
			return '_';
			
		case NUMBER:
			return 'n';
		
		case TRUE:
			return 't';
		
		case FALSE:
			return 'f';			
	
		case ADDITION:
			return '+';
		
		case SUBTRACTION:
			return '-';
			
		case MULTIPLICATION:
			return '*';
		
		case DIVISION:
			return '/';			
		
		case MORETHAN:
			return '>';
			
		case MOREEQUALTHAN:
			return ']';			
		
		case LESSTHAN:
			return '<';
	
		case LESSEQUALTHAN:
			return '[';		
		
		case EQUALS:
			return '=';			
		
		case ATTRIBUTION:
			return 'a';

		case AND:
			return '&';			
		
		case OR:
			return '|';

		case NOT:
			return '!';		
		
		case DOT:
			return '.';
		
		case COMMA:
			return ',';		
		
		case COLON:
			return ':';		
		
		case SEMICOLON:
			return ';';
		
		case OPARENTHESES:
			return '(';			
		
		case CPARENTHESES:
			return ')';
		
		case PROGRAM:
			return 'p';
		
		case BEGIN:
			return 'b';			
		
		case END:
			return 'E';

		case PROCEDURE:
			return 'P';
	
		case IF:
			return 'i';
	
		case THEN:
			return '-';
	
		case ELSE:
			return 'e';
		
		case WHILE:
			return 'w';
		
		case DO:
			return 'd';
	
		case VAR:
			return 'v';
		
		case WRITE:
			return 'W';
		
		case INT:
			return 'I';
			
		case BOOL:
			return 'B';
		
		case COMMENT:
			return 'c';

		default:
			printf("How did this happen?");

	}
}

void append(char* s, char c)
{
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

char * abreLeArquivo(char *arquivo){
    char *bufferEntrada;
    int size;
    // declara um ponteiro para arquivo
    // do tipo FILE
    FILE *fp;

    // abre um arquivo em modo texto
    fp = fopen(arquivo,"r");

    //testa se o arquivo foi aberto corretamente
    if( fp == NULL ){
        printf("nao achei o arquivo.\n");
        exit(0);
    }
    //printf("abri corretamente o arquivo.\n");
    // calcula em bytes o tamanho do arquivo de entrada
    // para isso usamos a funcao fseek() e ftell()
    // 1o passo = desloca o ponteiro do arquivo para o final
    fseek(fp, 0, SEEK_END);
    // 2o passo - calcula o numero de bytes da posicao corrente no arquivo
    size = ftell(fp);
    //3o passo - move o ponteiro do arquivo para inicio do arquivo
    rewind (fp);

    // aloca o buffer de entrada
    bufferEntrada = (char*)calloc(size+1, sizeof(int));

    // copia o conteudo do arquivo para um vetor de caracter *buffer
    fread (bufferEntrada,1,size,fp);

    return bufferEntrada;
}

void trataErro(){
	printf("\n\nERRO DE SINTAXE\n\n");
	/* Faca um tratamento melhor */
}

int scanner(char tokbuffer[]) {
    int c = 0;
	//Inicio
    q0:
		if(tokbuffer[c]== '/'){ c++; goto q1; }
		else if(isdigit(tokbuffer[c])) {c++; goto q9;}
		else if(tokbuffer[c] == '-') {c++; goto q77;}
		else if(tokbuffer[c] == '*') {c++; goto q78;}
		else if(tokbuffer[c] == '>') {c++; goto q79;}
		else if(tokbuffer[c] == '+') {c++; goto q76;}
		else if(tokbuffer[c] == '.') {c++; goto q91;}
		else if(tokbuffer[c] == '<') {c++; goto q83;}
		else if(tokbuffer[c] == ' ') {c++; goto q132;}
		else if(tokbuffer[c] == '(') {c++; goto q86;}
		else if(tokbuffer[c] == ':') {c++; goto q93;}
		else if(tokbuffer[c] == ',') {c++; goto q90;}
		else if(tokbuffer[c] == ')') {c++; goto q88;}
		else if(tokbuffer[c] == ';') {c++; goto q92;}
		//reservadas
		else if(tokbuffer[c] == 'a') {c++; goto q54;}
		else if(tokbuffer[c] == 'b') {c++; goto q13;}
		else if(tokbuffer[c] == 'd') {c++; goto q40;}
		else if(tokbuffer[c] == 'e') {c++; goto q35;}
		else if(tokbuffer[c] == 'f') {c++; goto q45;}
		else if(tokbuffer[c] == 'n') {c++; goto q68;}
		else if(tokbuffer[c] == 'v') {c++; goto q42;}
		else if(tokbuffer[c] == 'w') {c++; goto q57;}
		else if(tokbuffer[c] == 't') {c++; goto q50;}
		else if(tokbuffer[c] == 'o') {c++; goto q66;}
		else if(tokbuffer[c] == 'p') {c++; goto q17;}
		else if(tokbuffer[c] == 'i') {c++; goto q10;}
		//identificador
		else if (tokbuffer[c] == 'c') { c++; goto q6; }
		else if (tokbuffer[c] == 'g') { c++; goto q6; }
		else if (tokbuffer[c] == 'h') { c++; goto q6; }
		else if (tokbuffer[c] == 'j') { c++; goto q6; }
		else if (tokbuffer[c] == 'k') { c++; goto q6; }
		else if (tokbuffer[c] == 'l') { c++; goto q6; }
		else if (tokbuffer[c] == 'm') { c++; goto q6; }
		else if (tokbuffer[c] == 'q') { c++; goto q6; }
		else if (tokbuffer[c] == 'r') { c++; goto q6; }
		else if (tokbuffer[c] == 's') { c++; goto q6; }
		else if (tokbuffer[c] == 'u') { c++; goto q6; }
		else if (tokbuffer[c] == 'x') { c++; goto q6; }
		else if (tokbuffer[c] == 'y') { c++; goto q6; }
		else if (tokbuffer[c] == 'z') { c++; goto q6; }
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == 'A') { c++; goto q6; }
		else if (tokbuffer[c] == 'B') { c++; goto q6; }
		else if (tokbuffer[c] == 'C') { c++; goto q6; }
		else if (tokbuffer[c] == 'D') { c++; goto q6; }
		else if (tokbuffer[c] == 'E') { c++; goto q6; }
		else if (tokbuffer[c] == 'F') { c++; goto q6; }
		else if (tokbuffer[c] == 'G') { c++; goto q6; }
		else if (tokbuffer[c] == 'H') { c++; goto q6; }
		else if (tokbuffer[c] == 'I') { c++; goto q6; }
		else if (tokbuffer[c] == 'J') { c++; goto q6; }
		else if (tokbuffer[c] == 'K') { c++; goto q6; }
		else if (tokbuffer[c] == 'L') { c++; goto q6; }
		else if (tokbuffer[c] == 'M') { c++; goto q6; }
		else if (tokbuffer[c] == 'N') { c++; goto q6; }
		else if (tokbuffer[c] == 'O') { c++; goto q6; }
		else if (tokbuffer[c] == 'P') { c++; goto q6; }
		else if (tokbuffer[c] == 'Q') { c++; goto q6; }
		else if (tokbuffer[c] == 'R') { c++; goto q6; }
		else if (tokbuffer[c] == 'S') { c++; goto q6; }
		else if (tokbuffer[c] == 'T') { c++; goto q6; }
		else if (tokbuffer[c] == 'U') { c++; goto q6; }
		else if (tokbuffer[c] == 'V') { c++; goto q6; }
		else if (tokbuffer[c] == 'X') { c++; goto q6; }
		else if (tokbuffer[c] == 'W') { c++; goto q6; }
		else if (tokbuffer[c] == 'Y') { c++; goto q6; }
		else if (tokbuffer[c] == 'Z') { c++; goto q6; }
		return ERROR;

	// COMENTARIO e DIVISAO FIM
	q1:
		if(tokbuffer[c]== ' ') { c++; goto q75; }
		else if (tokbuffer[c] == '*') { c++; goto q2; }
		return ERROR;

    q2:
		if(isascii(tokbuffer[c])) { c++; goto q114; }
		else if (tokbuffer[c]== ' ') { c++; goto q114; }
		return ERROR;

    q3:
		if (tokbuffer[c] == '/') { c++; goto q4; }
		return ERROR;

    q4:
		if (tokbuffer[c] == ' ') { c++; goto q137; }
		return ERROR;

    q5:
		//RETORNAR  MENOR-MAIOR <>
		return EQUALS;

    q6:
		if(tokbuffer[c] == ' '){ c++; goto q133; }
		else if(isalnum(tokbuffer[c])) {c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q8:

		return ERROR;

    q9:
		if(isdigit(tokbuffer[c])){ c++; goto q9; }
		else if(tokbuffer[c] == ' ' ) {c++; goto q135;}
		return ERROR;

    q10:
		if(tokbuffer[c] == 'n') {c++; goto q11;}
		else if(tokbuffer[c] == 'f') {c++; goto q30;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'n' && tokbuffer[c] != 'f') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q11:
        if(tokbuffer[c] == 't') {c++; goto q12;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 't') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q12:
        if(tokbuffer[c] == ' ') {c++; goto q96;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q13:
		if(tokbuffer[c] == 'e') {c++; goto q31;}
		else if(tokbuffer[c] == 'o') {c++; goto q14;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'e' && tokbuffer[c] != 'o') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q14:
        if(tokbuffer[c] == 'o') {c++; goto q15;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'o') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q15:
        if(tokbuffer[c] == 'l') {c++; goto q16;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'l') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q16:
        if(tokbuffer[c] == ' ') {c++; goto q98;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q17:
        if(tokbuffer[c] == 'r') {c++; goto q18;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'r') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q18:
        if(tokbuffer[c] == 'o') {c++; goto q19;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'o') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q19:
        if(tokbuffer[c] == 'c') {c++; goto q24;}
        else if(tokbuffer[c] == 'g') {c++; goto q20;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'c' && tokbuffer[c] != 'g') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

	q20:
        if(tokbuffer[c] == 'r') {c++; goto q21;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'r') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q21:
        if(tokbuffer[c] == 'a') {c++; goto q22;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'a') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q22:
        if(tokbuffer[c] == 'm') {c++; goto q23;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'm') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q23:
        if(tokbuffer[c] == ' ') {c++; goto q100;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q24:
		if(tokbuffer[c] == 'e') {c++; goto q25;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'e') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q25:
        if(tokbuffer[c] == 'd') {c++; goto q26;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'd') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q26:
        if(tokbuffer[c] == 'u') {c++; goto q27;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'u') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q27:
        if(tokbuffer[c] == 'r') {c++; goto q28;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'r') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q28:
		if(tokbuffer[c] == 'e') {c++; goto q29;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'e') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q29:
        if(tokbuffer[c] == ' ') {c++; goto q101;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

	q30:
        if(tokbuffer[c] == ' ') {c++; goto q97;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q31:
        if(tokbuffer[c] == 'g') {c++; goto q32;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'g') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q32:
        if(tokbuffer[c] == 'i') {c++; goto q33;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'i') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q33:
        if(tokbuffer[c] == 'n') {c++; goto q99;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'n') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q34:
        if(tokbuffer[c] == 's') {c++; goto q38;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 's') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q35:
		if(tokbuffer[c] == 'l') {c++; goto q34;}
		else if(tokbuffer[c] == 'n') {c++; goto q36;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'l' && tokbuffer[c] != 'n') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q36:
        if(tokbuffer[c] == 'd') {c++; goto q37;}
		return ERROR;

	q37:
		if(tokbuffer[c] == ' ') {c++; goto q102;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q38:
		if(tokbuffer[c] == 'e') {c++; goto q39;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'e') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q39:
		if(tokbuffer[c] == ' ') {c++; goto q103;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q40:
		if(tokbuffer[c] == 'o') {c++; goto q41;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'o') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q41:
		if(tokbuffer[c] == ' ') {c++; goto q104;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q42:
		if(tokbuffer[c] == 'a') {c++; goto q43;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'a') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q43:
		if(tokbuffer[c] == 'r') {c++; goto q44;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'r') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q44:
        if(tokbuffer[c] == ' ') {c++; goto q105;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q45:
		if(tokbuffer[c] == 'a') {c++; goto q46;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'a') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q46:
        if(tokbuffer[c] == 'l') {c++; goto q47;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'l') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q47:
        if(tokbuffer[c] == 's') {c++; goto q48;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 's') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q48:
        if(tokbuffer[c] == 'e') {c++; goto q49;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'e') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q49:
        if(tokbuffer[c] == ' ') {c++; goto q106;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q50:
		if(tokbuffer[c] == 'h') {c++; goto q51;}
		else if(tokbuffer[c] == 'r') {c++; goto q72;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'h' && tokbuffer[c] != 'r') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q51:
        if(tokbuffer[c] == 'e') {c++; goto q52;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'e') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q52:
        if(tokbuffer[c] == 'n') {c++; goto q53;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'n') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q53:
		if(tokbuffer[c] == ' ') {c++; goto q107;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q54:
        if(tokbuffer[c] == 'n') {c++; goto q55;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'n') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q55:
		if(tokbuffer[c] == 'd') {c++; goto q56;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'd') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q56:
        if(tokbuffer[c] == ' ') {c++; goto q108;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q57:
		if(tokbuffer[c] == 'r') {c++; goto q58;}
		else if(tokbuffer[c] == 'h') {c++; goto q62;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'h' && tokbuffer[c] != 'r') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q58:
        if(tokbuffer[c] == 'i') {c++; goto q59;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'i') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q59:
        if(tokbuffer[c] == 't') {c++; goto q60;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 't') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q60:
        if(tokbuffer[c] == 'e') {c++; goto q61;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'e') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q61:
        if(tokbuffer[c] == ' ') {c++; goto q109;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q62:
        if(tokbuffer[c] == 'i') {c++; goto q63;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'i') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q63:
        if(tokbuffer[c] == 'l') {c++; goto q64;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'l') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q64:
        if(tokbuffer[c] == 'e') {c++; goto q65;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'e') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q65:
        if(tokbuffer[c] == ' ') {c++; goto q110;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q66:
        if(tokbuffer[c] == 'r') {c++; goto q67;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'r') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q67:
        if(tokbuffer[c] == ' ') {c++; goto q111;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q68:
        if(tokbuffer[c] == 'o') {c++; goto q69;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'o') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q69:
        if(tokbuffer[c] == 't') {c++; goto q70;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 't') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q70:
        if(tokbuffer[c] == ' ') {c++; goto q112;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q72:
        if(tokbuffer[c] == 'u') {c++; goto q73;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'u') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q73:
        if(tokbuffer[c] == 'e') {c++; goto q74;}
		else if (isalnum(tokbuffer[c]) && tokbuffer[c] != 'e') { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

   q74:
        if(tokbuffer[c] == ' ') {c++; goto q113;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

	//RETORNA DIVISAO
    q75:
		return DIVISION;

    q76:
		if(tokbuffer[c] == ' ' ) {c++; goto q117;}
		return ERROR;

	q77:
		if(tokbuffer[c] == ' ' ) {c++; goto q116;}
		return ERROR;

    q78:
		if(tokbuffer[c] == ' ' ) {c++; goto q115;}
		return ERROR;

    q79:
		if(tokbuffer[c] == ' ' ) {c++; goto q131;}
		else if(tokbuffer[c] == '=') {c++; goto q82;}
		return ERROR;

	q82:
		if(tokbuffer[c] == ' ' ) {c++; goto q120;}
		return ERROR;


	q83:
		if(tokbuffer[c]== ' ' ) {c++; goto q130;}
		else if(tokbuffer[c] == '=') {c++; goto q85;}
		else if(tokbuffer[c] == '>') {c++; goto q5;}
		return ERROR;

    /*
	q84:
		if(tokbuffer[c]== ' ' ) {c++; goto q123;}
		return ERROR;
	*/
		
    q85:
		//RETORNA <=
		return LESSEQUALTHAN;

	q86:
		if(tokbuffer[c]== ' ' ) {c++; goto q124;}
		return ERROR;

	q88:
		if(tokbuffer[c]== ' ' ) {c++; goto q125;}
		return ERROR;

	q89:
		//RETORNA BEGIN
		return BEGIN;

     q90:
		if(tokbuffer[c]== ' ' ) {c++; goto q126;}
		return ERROR;

    q91:
		if(tokbuffer[c]== ' ' ) {c++; goto q127;}
		return ERROR;

	q92:
		if(tokbuffer[c]== ' ' ) {c++; goto q128;}
		return ERROR;

    q93:
		if(tokbuffer[c]== ' ' ) {c++; goto q94;}
		else if(tokbuffer[c] == '=') {c++; goto q95;}
		return ERROR;

    q94:
        //RETORNA : DOIS PONTOS
		return COLON;

	q95:
		// RETORNA :=
		return ATTRIBUTION;

    q96:
        //RETORNA INT
		return INT;

    q97:
		//RETORNA IF
		return IF;

	q98:
        //RETORNA BOOL
		return BOOL;

    q99:
        if(tokbuffer[c] == ' ') {c++; goto q89;}
		else if (isalnum(tokbuffer[c])) { c++; goto q6;}
		else if (tokbuffer[c] == '_') { c++; goto q6; }
		else if (tokbuffer[c] == ' ') { c++; goto q133; }
		return ERROR;

    q100:
        //RETORNA PROGRAM
		return PROGRAM;

	q101:
        //RETORNA PROCEDURE
		return PROCEDURE;

    q102:
		//RETORNA END
		return END;

    q103:
        //RETORNA ELSE
		return ELSE;

	q104:
        //RETORNA DO
		return DO;

    q105:
        //RETORNA VAR
		return VAR;

    q106:
		//RETORNA FALSE
		return FALSE;

	q107:
        //RETORNA THEN
		return THEN;

    q108:
         //RETORNA AND
		return AND;

    q109:
        //RETORNA WRITE
		return WRITE;

	q110:
        //RETORNA WHILE
		return WHILE;

    q111:
        //RETORNA OR
		return OR;

    q112:
        //RETORNA NOT
		return NOT;

	q113:
        //RETORNA TRUE
		return TRUE;

    q114:
		if(isascii(tokbuffer[c]) && tokbuffer[c] != '*') { c++; goto q114; }
		else if (tokbuffer[c]== ' ') { c++; goto q114; }
		else if (tokbuffer[c] == '*') { c++; goto q3; }
		return ERROR;

	q115:
        //RETORNAR SINAL MULTIP *
		return MULTIPLICATION;

	q116:
       //RETORNAR SINAL MENOS -
		return SUBTRACTION;

    q117:
        //RETORNAR SINAL MAIS +
		return ADDITION;

	q120:
        //RETORNAR SINAL >= MAIOR-IGUAL
		return MOREEQUALTHAN;
    
	/*
	q123:
        //RETORNAR IGUAL =
		return OPERATOR;
	*/
		
    q124:
		//RETORNAR PARENTESES (
		return OPARENTHESES;

	q125:
        //RETORNA PARENTESES )
		return CPARENTHESES;

    q126:
        //RETORNA VIRGULA ,
		return COMMA;

    q127:
        //RETORNAR PONTO .
		return DOT;

	q128:
        //RETORNA PONTO-VIRGULA ;
		return SEMICOLON;

    q130:
        //RETORNAR < MENOR
		return LESSTHAN;

	q131:
        //RETORNAR > MAIOR
		return MORETHAN;

	//delete me plz?
    q132:
        //VAZIO
		return ERROR;

    q133:
        //RETORNAR VARIAVEL/IDENTIFICADOR
		return ID;

    q135:
        //RETORNAR NUMERO
		return NUMBER;

	q137:
		//RETORNA COMENTARIO
		return COMMENT;
}

int match(char t, char tokbuffer[], int *pos){
	char c = ' ';
	size_t len;
	char *palavra$;
	
	//Se o lookahead for comentario pegar prox token
	while (lookahead == 'c'){
		
		palavra = strtok(NULL, delimit);
		len = strlen(palavra);
		palavra$ = malloc(len + 1 + 1 );
		strcpy(palavra$, palavra);
		palavra$[len] = c;
		palavra$[len + 1] = '\0';
		inttok = scanner(palavra$);
		append(tokbuffer, toktranslate(inttok));
		lookahead = tokbuffer[++(*pos)];

	}
	
	if (lookahead == t){
		printf("Lookahead: %c ",lookahead);
		palavra = strtok(NULL, delimit);
		if (palavra != NULL)
		{
			len = strlen(palavra);
			palavra$ = malloc(len + 1 + 1 );
			strcpy(palavra$, palavra);
			palavra$[len] = c;
			palavra$[len + 1] = '\0';
			inttok = scanner(palavra$);
			append(tokbuffer, toktranslate(inttok));
			lookahead = tokbuffer[++(*pos)];
			printf("Matched: %c\n",t);
		}
		return(1);
	}
	//printf("Erro token esperado: %c | Lookahead: %c\n", t, lookahead);
	return(0);  
}

int PROGRAMA(char tokbuffer[], int *pos){
	if (match('p', tokbuffer, pos) &&
		IDENTIFICADOR(tokbuffer,pos) &&
		match(';', tokbuffer, pos) &&
		BLOCO(tokbuffer, pos) &&
		match('.', tokbuffer, pos))
	{
		return(1);
	}
	printf("Erro na leitura PROGRAMA\n");
	return(0);
}

int IDENTIFICADOR(char tokbuffer[], int *pos){
	//solicitar TOKEN
	if (match('_', tokbuffer, pos))
		return(1);
	
	printf("Erro na leitura IDENTIFICADOR\n");
	return(0);	
}

//erro aqui
int BLOCO(char tokbuffer[], int *pos){
	
	if(PARTE_DECLARACOES_VARIAVEIS(tokbuffer,pos)){
		if (PARTE_DECLARACOES_SUBROTINAS(tokbuffer,pos)){
			return(1);
		} 
	}
	if (PARTE_DECLARACOES_SUBROTINAS(tokbuffer,pos)){
		return(1);
	} 
	printf("Erro na leitura BLOCO\n");
	return(0);
}

int PARTE_DECLARACOES_VARIAVEIS(char tokbuffer[], int *pos){
	int temp;
	if ( DECLARACAO_VARIAVEIS(tokbuffer,pos) )
	{
		while (match(';',tokbuffer, pos)) { 
			gambi++;
			printf("gambi: %d\n",gambi);
			DECLARACAO_VARIAVEIS(tokbuffer,pos);
		}
		if (gambi == arra){
			return (1);
		}
		
	}
	printf("Erro na leitura PARTE_DECLARACOES_VARIAVEIS\n");
	return(0);
}

int DECLARACAO_VARIAVEIS(char tokbuffer[], int *pos){
	if(match('v', tokbuffer, pos)){
		arra++;
		printf("arra: %d\n",arra);
		if (
			LISTA_IDENTIFICADORES(tokbuffer,pos) && 
			match(':',tokbuffer,pos) &&
			TIPO(tokbuffer,pos)
			)
		{
			return(1);
		}
	}
	printf("Erro na leitura DECLARACAO_VARIAVEIS\n");
	return(0);
}

int LISTA_IDENTIFICADORES(char tokbuffer[], int *pos){ 
	if( IDENTIFICADOR(tokbuffer,pos)){
		while(match(',',tokbuffer, pos)) { IDENTIFICADOR(tokbuffer,pos);}
		return(1);
	}
	printf("Erro na leitura LISTA_IDENTIFICADORES\n");
	return(0);
}

int TIPO(char tokbuffer[], int *pos){
	if (match('I',tokbuffer,pos) || 
		match('B',tokbuffer,pos))
		{
			return(1);
		}
		printf("Erro na leitura TIPO\n");
	return(0);
}

int PARTE_DECLARACOES_SUBROTINAS(char palavra[], int *pos){
	while (DECLARACAO_PROCEDIMENTO(palavra,pos)) {match(';',palavra,pos);}
	return(1);
	//printf("Erro na leitura PARTE_DECLARACOES_SUBROTINAS");
	//return(0);
}

int DECLARACAO_PROCEDIMENTO(char palavra[], int *pos){ 
	if( match('P',palavra,pos) && IDENTIFICADOR(palavra,pos) ){
		
		if (PARAMETROS_FORMAIS(palavra,pos)){
			if(match(';',palavra,pos) && BLOCO(palavra,pos)){
				return (1);
			}
			return (0);
		}
		if(match(';',palavra,pos) && BLOCO(palavra,pos)){
			return (1);
		}
	} 
	printf("Erro na leitura DECLARACAO_PROCEDIMENTO\n");
	return(0);
}

int PARAMETROS_FORMAIS(char palavra[], int *pos){
	if( match('(',palavra,pos) && PARAMETRO_FORMAL(palavra,pos)){
		while (match(';', palavra,pos)) { PARAMETRO_FORMAL(palavra,pos);}
		match(')', palavra, pos);
		return(1);
	} 	
	printf("Erro na leitura PARAMETROS_FORMAIS\n");
	return(0);
}

int PARAMETRO_FORMAL(char palavra[], int *pos){
	if (match('v',palavra,pos)){
		if (IDENTIFICADOR(palavra,pos) && match(':',palavra,pos) && TIPO(palavra,pos)){
			return(1);
		}
		return (0);
	}
	if (IDENTIFICADOR(palavra,pos) && match(':',palavra,pos) && TIPO(palavra,pos)){
		return(1);
	}
	printf("Erro na leitura PARAMETRO_FORMAL\n");
	return(0);
}