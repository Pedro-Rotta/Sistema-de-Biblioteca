//BORDA COLORIDA
void Borda_Menu();
//LIMPADORES DE TELA
void Clear_Display();
void Clear_Fora();
void Clear_Mensagem();
void Clear_op();
void Clear_Quadro_Completo();
//ESCOLHA COM EXIBIÇÂO PARA AS CONSULTAS
void Escolha_Exibe_Consulta(char &op);
void Escolha_Exibe_Consulta_Color(char &op);
//AUXILIO NA EXCLUSAO
void Escolha_Excluir();
//MENSAGENS DE ERRO
void Mensagem1(char texto[]);
void Mensagem2(char texto[]);
//OPCOES DOS MENUS
void Menu_Alterar(char &op);
void Menu_Alterar_Color(char &op);
void Menu_Cadastrar(char &op);
void Menu_Cadastrar_Color(char &op);
void Menu_Consultar(char &op);
void Menu_Excluir(char &op);
void Menu_Excluir_Color(char &op);
void Menu_Principal(char &op);
void Menu_Relatorios(char &op);
//NOME DE TABELA/FINALIZAÇÃO DE INTERFACE
void Nome_Tabela(char texto[]);
void Preenchimento_Menu();
//TEXTOS PARA TODA A INTERFACE
void Texto_Display(int y, char texto[]);
void Texto_Menu_Color(int y, char texto[]);
void Texto_Menu_Principal(int y, char texto[]);
void Texto_Opcoes_Menu(int y, char texto[]);


void Borda_Menu(){
	int x, y;
	textcolor(YELLOW);
	for(x=21;x<100;x++){
		gotoxy(x, 5);
		printf("%c", '-');
		gotoxy(x, 27);
		printf("%c", '-');
	}
    textcolor(WHITE);
    textcolor(GREEN);
    gotoxy(20, 4);  printf("%c", 201);
    gotoxy(100, 4); printf("%c", 187);
    gotoxy(20, 28); printf("%c", 200);
    gotoxy(100, 28); printf("%c", 188);
    
    for (int i = 21; i < 100; i++) {
        gotoxy(i, 4);  printf("%c", 205);
        gotoxy(i, 28); printf("%c", 205);
    }
    
    for (int i = 5; i < 28; i++) {
        gotoxy(20, i);  printf("%c", 186);
        gotoxy(100, i); printf("%c", 186);
    }
    
    textcolor(RED);
    gotoxy(22, 6);  printf("%c", 201);
    gotoxy(98, 6);  printf("%c", 187);
    gotoxy(22, 26); printf("%c", 200);
    gotoxy(98, 26); printf("%c", 188);
    
    for (int i = 23; i < 98; i++) {
        gotoxy(i, 6);  printf("%c", 205);
        gotoxy(i, 26); printf("%c", 205); 
    }
    
    for (int i = 7; i < 26; i++) {
        gotoxy(22, i);  printf("%c", 186);
        gotoxy(98, i);  printf("%c", 186);
    }
}

void Clear_Display(){
	int x, y, xi, yi, xf, yf;
	xi = 51;
	yi = 7;
	xf = 97;
	yf = 20;
	for (y = yi; y <= yf; y++) {
        gotoxy(xi, y);
        for (x = xi; x <= xf; x++) {
            printf(" ");
        }
    }
}

void Clear_Fora(){
	int x, y, xi, yi, xf, yf;
		xi = 0;
		xf = 20;
		yi = 0;
		yf = 30;
		
		for(x=xi;x<xf;x++){
			for(y=yi;y<yf;y++){
				gotoxy(x,y);
				printf(" ");
			}
		}
		
		for(x=40,y=3;x<70;x++){
			gotoxy(x,y);
			printf(" ");
		}
}

void Clear_Mensagem(){
	int x, y, xi, yi, xf, yf;
	xi = 51;
	yi = 23;
	xf = 97;
	yf = 25;
	
	for (y = yi; y <= yf; y++) {
        gotoxy(xi, y);
        for (x = xi; x <= xf; x++) {
            printf(" ");
        }
    }
}

void Clear_op(){
	int x, y, xi, yi, xf, yf;
	xi = 23;
	yi = 7;
	xf = 49;
	yf = 25;
	for (y = yi; y <= yf; y++) {
        gotoxy(xi, y);
        for (x = xi; x <= xf; x++) {
            printf(" ");
        }
    }
}

void Clear_Quadro_Completo(){
	int x, y, xi, yi, xf, yf;
	xi = 23;
	yi = 7;
	xf = 96;
	yf = 25;
	for (y = yi; y <= yf; y++) {
        gotoxy(xi, y);
        for (x = xi; x <= xf; x++) {
            printf(" ");
        }
    }
}

void Escolha_Exibe_Consulta(char &op){
	Clear_op();
	Texto_Opcoes_Menu(7, "[A] CONSULTA POR ID");
	Texto_Opcoes_Menu(9, "[B] EXIBIR TODOS");
	Texto_Opcoes_Menu(25, "[ESC] MENU DE CONSULTAS");
	op=toupper(getch());
	while(op != 'A' && op != 'B' && op != 27){
		op=toupper(getch());
		Mensagem1("ESCOLHA UMA OPCAO VALIDA!");
	}
	Clear_Display();
}

void Escolha_Exibe_Consulta_Color(char &op){
	switch(op){
		case 'A':{Texto_Menu_Color(7, "[A] CONSULTA POR ID"); break;}
		case 'B':{Texto_Menu_Color(9, "[B] EXIBIR TODOS"); break;}
	}
}

void Escolha_Exibe_Consulta_Relacao(char &op){
	Clear_op();
	Texto_Opcoes_Menu(7, "[A] CONSULTA POR ID AUTOR");
	Texto_Opcoes_Menu(9, "[B] CONSULTA POR ID LIVRO");
	Texto_Opcoes_Menu(11, "[C] EXIBIR TODOS");
	Texto_Opcoes_Menu(25, "[ESC] MENU DE CONSULTAS");
	op=toupper(getch());
	while(op != 'A' && op != 'B' && op != 'C' && op != 27){
		op=toupper(getch());
		Mensagem1("ESCOLHA UMA OPCAO VALIDA!");
	}
	Clear_Display();
}

void Escolha_Exibe_Consulta_Color_Relacao(char &op){
	switch(op){
		case 'A':{Texto_Menu_Color(7, "[A] CONSULTA POR ID AUTOR"); break;}
		case 'B':{Texto_Menu_Color(9, "[B] CONSULTA POR ID LIVRO"); break;}
		case 'C':{Texto_Menu_Color(11, "[C] EXIBIR TODOS"); break;}
	}
}

void Escolha_Excluir(int y, char &op){
	textcolor(WHITE);
	gotoxy(52,y);
	printf("DESEJA REALMENTE REALIZAR A EXCLUSAO?");
	gotoxy(52,y+1);
	printf("[S] SIM");
	gotoxy(52,y+2);
	printf("[ESC] CANCELAR");
	op=toupper(getch());
	while(op != 'S' && op != 27){
		op=toupper(getch());
		Mensagem1("ESCOLHA UMA OPCAO VALIDA!");
	}
	Clear_Display();
	Clear_Mensagem();
}

void Mensagem1(char texto[]){
	textcolor(YELLOW);
	gotoxy(52,23);
	printf("Mensagem: %s", texto);
}

void Mensagem2(char texto[]){
	textcolor(YELLOW);
	gotoxy(52,25);
	printf("Mensagem: %s", texto);
}

void Menu_Alterar(char &op){
	Clear_Fora();
	Clear_op();
	Clear_Display();
	Borda_Menu();
	Preenchimento_Menu();
	textcolor(YELLOW);
	gotoxy(65,12);
	printf("ESCOLHA UMA OPCAO:");
	Nome_Tabela("MENU - ALTERAR");
	Texto_Opcoes_Menu(7, "[A] LIVRO");
	Texto_Opcoes_Menu(9, "[B] AUTOR");
	Texto_Opcoes_Menu(11, "[C] PESSOA");
	Texto_Opcoes_Menu(13, "[D] EMPRESTIMO");
	Texto_Opcoes_Menu(25, "[ESC] MENU PRINCIPAL");
	do{
		op=toupper(getch());
		Mensagem1("Escolha uma opcao valida!");
	}while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 27);
	Clear_Mensagem();
	Borda_Menu();
	Preenchimento_Menu();
	Clear_Display();
	Menu_Alterar_Color(op);
}

void Menu_Alterar_Color(char &op){
	textcolor(YELLOW);
	switch(op){
		case 'A':{Texto_Menu_Color(7, "[A] LIVRO"); break;}
		case 'B':{Texto_Menu_Color(9, "[B] AUTOR");break;}
		case 'C':{Texto_Menu_Color(11, "[C] PESSOA");break;}
		case 'D':{Texto_Menu_Color(13, "[D] EMPRESTIMO");break;}
	}
}

void Menu_Cadastrar(char &op) {
	
	Clear_Fora();
	Clear_op();
	Clear_Display();
	Borda_Menu();
	Preenchimento_Menu();
	textcolor(YELLOW);
	gotoxy(65,12);
	printf("ESCOLHA UMA OPCAO");
	Nome_Tabela("MENU - CADASTRAR");
	Texto_Opcoes_Menu(7,"[A] LIVRO");
	Texto_Opcoes_Menu(9,"[B] AUTOR");
	Texto_Opcoes_Menu(11,"[C] PESSOA");
	Texto_Opcoes_Menu(13,"[D] EMPRESTIMO");
	Texto_Opcoes_Menu(15,"[E] ASSOCIAR LIVRO/AUTOR");
	Texto_Opcoes_Menu(25,"[ESC] MENU PRINCIPAL");
	do{
		op=toupper(getch());
		Mensagem1("Escolha uma opcao valida!");
	}while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'E' && op != 27);
	Clear_Mensagem();
	Borda_Menu();
	Preenchimento_Menu();
	Clear_Display();
	Menu_Cadastrar_Color(op);
}

void Menu_Cadastrar_Color(char &op){
	textcolor(YELLOW);
	switch(op){
		case 'A':{Texto_Menu_Color(7, "[A] LIVRO");break;}
		case 'B':{Texto_Menu_Color(9, "[B] AUTOR");break;}
		case 'C':{Texto_Menu_Color(11, "[C] PESSOA");break;}
		case 'D':{Texto_Menu_Color(13, "[D] EMPRESTIMO");break;}
		case 'E':{Texto_Menu_Color(15, "[E] ASSOCIAR LIVRO/AUTOR");break;}
	}
}

void Menu_Consultar(char &op){
	Clear_Fora();
	Clear_Display();
	Clear_op();
	Borda_Menu();
	Preenchimento_Menu();
	textcolor(YELLOW);
	gotoxy(65,12);
	printf("ESCOLHA UMA OPCAO:");
	Nome_Tabela("MENU - CONSULTAR");
	Texto_Opcoes_Menu(7,"[A] LIVRO");
	Texto_Opcoes_Menu(9,"[B] AUTOR");
	Texto_Opcoes_Menu(11,"[C] PESSOA");
	Texto_Opcoes_Menu(13,"[D] EMPRESTIMO");
	Texto_Opcoes_Menu(15,"[E] ASSOCIACAO LIVRO/AUTOR");
	Texto_Opcoes_Menu(25,"[ESC] MENU PRINCIPAL");
	do{
		op=toupper(getch());
		Mensagem1("Escolha uma opcao valida!");
	}while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'E' && op != 27);
	Borda_Menu();
	Clear_Mensagem();
	Clear_Display();
}

void Menu_Excluir(char &op){
	Clear_Fora();
	Clear_Display();
	Clear_op();
	Borda_Menu();
	Preenchimento_Menu();
	textcolor(YELLOW);
	gotoxy(65,12);
	printf("ESCOLHA UMA OPCAO");
	Nome_Tabela("MENU - EXCLUIR");
	Texto_Opcoes_Menu(7,"[A] LIVRO");
	Texto_Opcoes_Menu(9,"[B] AUTOR");
	Texto_Opcoes_Menu(11,"[C] PESSOA");
	Texto_Opcoes_Menu(13,"[D] EMPRESTIMO");
	Texto_Opcoes_Menu(15,"[E] ASSOCIACAO LIVRO/AUTOR");
	Texto_Opcoes_Menu(25,"[ESC] MENU PRINCIPAL");
	do{
		op=toupper(getch());
		Mensagem1("Escolha uma opcao valida!");
	}while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'E' && op != 27);
	Clear_Mensagem();
	Clear_Display();
	Menu_Excluir_Color(op);
}

void Menu_Excluir_Color(char &op){
	textcolor(YELLOW);
	switch(op){
		case 'A':{Texto_Menu_Color(7, "[A] LIVRO");break;}
		case 'B':{Texto_Menu_Color(9, "[B] AUTOR");break;}
		case 'C':{Texto_Menu_Color(11, "[C] PESSOA");break;}
		case 'D':{Texto_Menu_Color(13, "[D] EMPRESTIMO");break;}
		case 'E':{Texto_Menu_Color(15, "[E] ASSOCIACAO LIVRO/AUTOR");break;}
	}
}

void Menu_Principal(char &op){
	Clear_Fora();
	system("CLS");
	Borda_Menu();
	textcolor(GREEN);
	gotoxy(53, 8);
	printf("BIBLIOTECA RNL");
	textcolor(RED);
	gotoxy(25, 8);
	printf("+-------------------+\n"); gotoxy(25, 9); 
	printf("|  ______   ______  |\n"); gotoxy(25, 10);
	printf("| |      | |      | |\n"); gotoxy(25, 11);
	printf("| | ATP1 | | ATP2 | |\n"); gotoxy(25, 12);
	printf("| |______| |______| |\n"); gotoxy(25, 13);
	printf("|  ______   ______  |\n"); gotoxy(25, 14);
	printf("| |      | |      | |\n"); gotoxy(25, 15);
	printf("| | ED1  | |  ED2 | |\n"); gotoxy(25, 16);
	printf("| |______| |______| |\n"); gotoxy(25, 17);
	printf("|  ______   ______  |\n"); gotoxy(25, 18);
	printf("| |      | |      | |\n"); gotoxy(25, 19);
	printf("| | SO1  | |  SO2 | |\n"); gotoxy(25, 20);
	printf("| |______| |______| |\n"); gotoxy(25, 21);
	printf("|                   |\n"); gotoxy(25, 22);
	printf("+-------------------+\n"); gotoxy(25, 23);
	
	gotoxy(75, 8);
	printf("+-------------------+\n"); gotoxy(75, 9); 
	printf("|  ______   ______  |\n"); gotoxy(75, 10);
	printf("| |      | |      | |\n"); gotoxy(75, 11);
	printf("| | FSI  | | GISI | |\n"); gotoxy(75, 12);
	printf("| |______| |______| |\n"); gotoxy(75, 13);
	printf("|  ______   ______  |\n"); gotoxy(75, 14);
	printf("| |      | |      | |\n"); gotoxy(75, 15);
	printf("| | CIEN | |  LGC | |\n"); gotoxy(75, 16);
	printf("| |______| |______| |\n"); gotoxy(75, 17);
	printf("|  ______   ______  |\n"); gotoxy(75, 18);
	printf("| |      | |      | |\n"); gotoxy(75, 19);
	printf("| | MAT  | | AMBP | |\n"); gotoxy(75, 20);
	printf("| |______| |______| |\n"); gotoxy(75, 21);
	printf("|                   |\n"); gotoxy(75, 22);
	printf("+-------------------+\n"); gotoxy(75, 23);
	
	
	
	Nome_Tabela("MENU PRINCIPAL");
	Texto_Menu_Principal(10, "[A] CADASTRO DE DADOS");
    Texto_Menu_Principal(12, "[B] ALTERAR REGISTROS");
    Texto_Menu_Principal(14, "[C] EXCLUIR REGISTROS");
    Texto_Menu_Principal(16, "[D] CONSULTAR DADOS");
    Texto_Menu_Principal(18, "[ESC] RELATORIOS");
	textcolor(YELLOW);
	gotoxy(50, 24);
    printf("BOM PROVEITO!");
    gotoxy(45,24);
    printf("AUTORES: LEANDRO, NICOLY, PEDRO");
	op=toupper(getch());
	while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 27){
		gotoxy(48, 21);
		printf("Escolha uma opcao valida!");
		op=toupper(getch());
	}
	Clear_Mensagem();
	Clear_Quadro_Completo();
}

void Menu_Relatorios(char &op){
	Clear_Fora();
	Clear_op();
	Clear_Display();
	Borda_Menu();
	Preenchimento_Menu();
	Nome_Tabela("MENU - RELATORIOS");
	Texto_Opcoes_Menu(7, "[A] COMPLETO");
	Texto_Opcoes_Menu(9, "[B] AUTOR POR LETRA");
	Texto_Opcoes_Menu(11, "[C] LIVRO POR PALAVRA");
	Texto_Opcoes_Menu(13, "[D] EMPRESTIMO POR PESSOA");
	Texto_Opcoes_Menu(15, "[E] LIVROS DE UM AUTOR");
	Texto_Opcoes_Menu(17, "[F] TODOS OS EMPRESTIMOS");
	Texto_Opcoes_Menu(25, "[ESC] ENCERRAR PROGRAMA");
	do{
		op=toupper(getch());
		Mensagem1("Escolha uma opcao valida!");
	}while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'E' && op != 'F' && op != 27);
	Clear_Mensagem();
	Borda_Menu();
	Preenchimento_Menu();
}

void Nome_Tabela(char texto[]){
	textcolor(YELLOW);
	gotoxy(55,5);
	printf("%s", texto);
}

void Preenchimento_Menu(){
	int i, x, y;
	textcolor(RED);
	gotoxy(50,6);
	printf("%c", 203);
	gotoxy(50,26);
	printf("%c", 202);
	
	for(i=0, y= 7;i<19;i++, y++){
		gotoxy(50,y);
		printf("%c", 186);
	}
	for(i=0, x=51;i<47;i++, x++){
		gotoxy(x,21); 
		printf("%c", 205);
	}
	gotoxy(50,21);
	printf("%c", 204);
	gotoxy(98, 21);
	printf("%c", 185);
	gotoxy(70, 22);
	printf("MENSAGENS");
}

void Texto_Display(int y, char texto[]){
	textcolor(WHITE);
	gotoxy(52,y);
	printf("%s", texto);
}

void Texto_Menu_Color(int y, char texto[]){
	textcolor(YELLOW);
	gotoxy(24,y);
	printf("%s", texto);
}

void Texto_Menu_Principal(int y, char texto[]){
	textcolor(WHITE);
	gotoxy(50, y);
	printf("%s", texto);
}

void Texto_Opcoes_Menu(int y, char texto[]){
	textcolor(WHITE);
	gotoxy(24,y);
	printf("%s", texto);
}
