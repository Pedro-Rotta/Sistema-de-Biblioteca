#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "interface.h"
#include <direct.h>
#include <unistd.h>

struct _Livro{
	int ID_Livro;
	int Vet_Ano_Livro[3];
	char Titulo[20];
	bool Status;
	bool Status_Emprestado; //true == disponivel |||| false == indisponivel
};
struct _Autor{
	int ID_Autor;
	bool Status;
	char Nome_Autor[20];
	char Nacionalidade[20];
};
struct _Pessoa{
	int ID_Pessoa;
	bool Status;
	char Nome_Pessoa[20];
	char Telefone_Pessoa[15]; //Formato: +18 99805-1878
	char Endereco_Pessoa[30];
};
struct _Emprestimo{ 
	int ID_Emprestimo;
	int ID_Livro;
	int ID_Pessoa;
	int Vet_Data_Emprestimo[3];
	int Vet_Data_Devolucao[3];
	bool Status;
};
struct _Relacao{
	int ID_Livro;
	int ID_Autor;
	bool Status;
};





//EXECUTAVEIS PRINCIPAIS
int main(void);
void Executar(void);
void Exclusao_Fisica(void);
void Relatorios(void);


//ALTERAC?ES
void Alterar_Autor();
void Alterar_Emprestimo();
void Alterar_Livro();
void Alterar_Pessoa();

//BUSCAS
int Busca_Autor(int ID, FILE *f);
int Busca_Autor_Na_Relacao(int ID, FILE *f);
int Busca_Emprestimo(int ID, FILE *f);
int Busca_Livro(int ID, FILE *f);
int Busca_Livro_Autor_Relacionamento(int ID_Livro, int ID_Autor, FILE *f);
int Busca_Livro_Na_Relacao(int ID, FILE *f);
int Busca_Livro_No_Emprestimo(int ID, FILE *f);
int Busca_Pessoa(int ID, FILE *f);
int Busca_Pessoa_No_Emprestimo(int ID, FILE *f);

//CADASTROS
void Cadastro_Autor();	//INCLUIR VERIFICA??ES
void Cadastro_Emprestimo();	//INCLUIR VERIFICA??ES
void Cadastro_Livro();	//INCLUIR VERIFICA??ES
void Cadastro_Pessoa();	//INCLUIR VERIFICA??ES
void Cadastro_Relacionamento();	//INCLUIR VERIFICA??ES


//CONSULTAS
void Autor_Por_Letra();	//COMPLETO
void Consulta_Autor();	//COMPLETO
void Consulta_Emprestimo();	//COMPLETO
void Consulta_Completa();	//COMPLETO
void Consulta_Livro();	//COMPLETO
void Consulta_Pessoa();	//COMPLETO
void Consulta_Relacionamento();	//COMPLETO
void Emprestimos_Por_Pessoa();	//COMPLETO
void Livro_Por_Palavra();	//??
void Relatorio_Emprestimo_Completo();	//COMPLETO
void Livros_De_Autor();	//COMPLETO

//EXCLUS?ES
void Exclusao_Autor();	//COMPLETO
void Exclusao_Emprestimo();	//COMPLETO
	void Exclusao_Livro();	//COMPLETO
void Exclusao_Pessoa();	//COMPLETO
void Exclusao_Relacionamento();	//COMPLETO

//PARTE DE INSERCAO DO CADASTRO
void Insere_Autor(int ID, FILE *f);
void Insere_Emprestimo(int ID, FILE *f_Empresimo, FILE *f_Livro, FILE *f_Pessoa);
void Insere_Livro(int ID, FILE *f);
void Insere_Pessoa(int ID, FILE *f);
void Insere_Relacionamento(int ID_Livro, FILE *f_Relacao, FILE *f_Autor);


//ORDENA??O
void Ordenar_Autor(FILE *f);
void Ordenar_Autor_Por_Nacionalidade(FILE *f);
void Ordenar_Emprestimo(FILE *f);
void Ordenar_Livro(FILE *f);
void Ordenar_Livros_Por_Data(FILE *f);
void Ordenar_Pessoa(FILE *f);
void Ordenar_Relacao(FILE *f);


//VERIFICA SE TEM DADOS
bool Verifica_Presenca_Dados_Autor(FILE *f);
bool Verifica_Presenca_Dados_Emprestimo(FILE *f);
bool Verifica_Presenca_Dados_Livro(FILE *f);
bool Verifica_Presenca_Dados_Pessoa(FILE *f);
bool Verifica_Presenca_Dados_Relacao(FILE *f);
bool Verifica_Data_Emprestimo(_Emprestimo Emprestimo);
bool Verifica_Todos_Dados();

//EXECUTAVEIS PRINCIPAIS
int main(void){
	char *diretorio = "arquivos.dat";
	_mkdir(diretorio);
	FILE *f;
	f = fopen("arquivos.dat/Livros_Cadastrados.dat", "ab");
	fclose(f);
	f = fopen("arquivos.dat/Autores_Cadastrados.dat", "ab");
	fclose(f);
	f = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "ab");
	fclose(f);
	f = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "ab");
	fclose(f);
	f = fopen("arquivos.dat/Relacao_Cadastrados.dat", "ab");
	fclose(f);


	Executar();
	Exclusao_Fisica();
	Relatorios();
    return 0;
}
void Executar(void){
	char op;
	bool ContinuarMenu = true;
	Menu_Principal(op);
	while(ContinuarMenu){
		switch(op){
			case 'A':{
				Menu_Cadastrar(op);
				while(op != 27){
						switch(op){
						case 'A':{ Cadastro_Livro(); break; //Cadastro Ordenado Completo
						}
						case 'B':{ Cadastro_Autor(); break; //Cadastro Ordenado Completo
						}
						case 'C':{ Cadastro_Pessoa(); break; //Cadastro Ordenado Completo
						}
						case 'D':{ Cadastro_Emprestimo(); break; //Cadastro Nao Ordenado Completo
						}
						case 'E':{ Cadastro_Relacionamento(); break; //Cadastro Nao Ordenado CompletoMenu_Excluir_Color
						}
					}
					Menu_Cadastrar(op);
				}
				break;
			}
			case 'B':{
				Menu_Alterar(op);
				while(op != 27){
					switch(op){
						case 'A':{ Alterar_Livro(); break;
						}
						case 'B':{ Alterar_Autor(); break;
						}
						case 'C':{ Alterar_Pessoa(); break;
						}
						case 'D':{ Alterar_Emprestimo(); break;
						}
					}
					Menu_Alterar(op);
				}
				break;
			}
			case 'C':{
				Menu_Excluir(op);
				while(op != 27){
					switch(op){
						case 'A':{ Exclusao_Livro(); break;
						}
						case 'B':{ Exclusao_Autor(); break;
						}
						case 'C':{ Exclusao_Pessoa();break;
						}
						case 'D':{ Exclusao_Emprestimo(); break;
						}
						case 'E':{ Exclusao_Relacionamento(); break;
						}
					}
					Menu_Excluir(op);
				}
				break;
			}
			case 'D':{
				Menu_Consultar(op);
				while(op != 27){
					switch(op){
						case 'A':{ Consulta_Livro(); break;
						}
						case 'B':{ Consulta_Autor(); break;
						}
						case 'C':{ Consulta_Pessoa(); break;
						}
						case 'D':{ Consulta_Emprestimo(); break;
						}
						case 'E':{ Consulta_Relacionamento(); break;
						}
					}
					Menu_Consultar(op);
				}
				break;
			}
			case 27:{
				Exclusao_Fisica();
				if(Verifica_Todos_Dados()){
					Clear_Quadro_Completo();
					Preenchimento_Menu();
					textcolor(GREEN);
					Preenchimento_Menu();
					Borda_Menu();
					gotoxy(30, 11);
					printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 191); gotoxy(30, 12);
					printf("|              |"); gotoxy(30, 13);
					printf("|  RELATORIOS  |"); gotoxy(30, 14);
					printf("|______________|"); gotoxy(30, 15);
					printf("|   ________   |"); gotoxy(30, 16);
					printf("|  |TYPE 'S'|  |"); gotoxy(30, 17);
					printf("|  |_OR ESC_|  |"); gotoxy(30, 18);
					printf("|______________|"); gotoxy(30, 19);
					printf("   |        |"); gotoxy(30, 20);
					printf("   |________|"); gotoxy(30, 21);
					printf("  /_-_-_-_-_-\\"); 
					gotoxy(52, 7);
					printf("Ir para relatorios?");
					gotoxy(52, 9);
					printf("[S] Sim");
					gotoxy(52, 11);
					printf("[ESC] Cancelar");
					gotoxy(52, 13);
					printf("OBS: Nao podera retornar ao menu principal");
					op = toupper(getch());
					while(op != 'S' && op != 27){
						op = toupper(getch());
						Mensagem1("Escolha uma opcao valida!");
					}
					if(op == 'S'){
						ContinuarMenu = false;
					}
					system("CLS");
				}
				else{
					gotoxy(45, 21);
					printf("Nao ha dados para gerar os relatorios");
				}
			}
		}
		if(ContinuarMenu){
			Menu_Principal(op);
		}
	}
}
void Relatorios(void){
	char op;
	Menu_Relatorios(op);
	while(op != 27){
		switch(op){
			case 'A':{
				Consulta_Completa(); //CONSULTA MAIS DETALHADA
				break;
			}
			case 'B':{
				Autor_Por_Letra();	//DEVE SER ORDENADO PELA NACIONALIDADE
				break;
			}
			case 'C':{
				Livro_Por_Palavra(); //DEVE SER ORDENADO POR ANO DE PUBLICAÇÃO
				break;
			}
			case 'D':{
				Emprestimos_Por_Pessoa(); //TODOS OS EMPRESTIMOS DA PESSOA
				break;
			}
			case 'E':{
				Livros_De_Autor();
				break;
			}
			case 'F':{
				Relatorio_Emprestimo_Completo(); //TODOS OS EMPRESTIMOS DETALHADOS SEPARADOS POR PESSOA ORDEM DA EXIBIÇÃO: ID_PESSOA (O NOME DA PESSOA E TODOS OD EMPRESTIMOS REALIZADOS POR ELA)
				break;
			}
		}
		Menu_Relatorios(op);
	}
}
void Exclusao_Fisica(void){
	long int pos;
	long int tamanhoAtual;	
	_Autor	auxAutor, Exclui_Pos_Autor;
	_Emprestimo auxEmprestimo, Exclui_Pos_Emprestimo;
	_Livro	auxLivro, Exclui_Pos_Livro;
	_Pessoa auxPessoa, Exclui_Pos_Pessoa;
	_Relacao auxRelacao, Exclui_Pos_Relacao;
	FILE *f_Autor, *f_Emprestimo, *f_Livro, *f_Pessoa, *f_Relacao;
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat", "rb+");
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb+");
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb+");
	f_Pessoa = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "rb+");
	f_Relacao = fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb+");
	rewind(f_Autor);
	rewind(f_Emprestimo);
	rewind(f_Livro);
	rewind(f_Pessoa);
	rewind(f_Relacao);
	//EXCLUI AUTORES
	while(fread(&auxAutor, sizeof(_Autor), 1, f_Autor) == 1){
		if (!auxAutor.Status) {
			pos = ftell(f_Autor) - sizeof(_Autor);
			while(fread(&Exclui_Pos_Autor, sizeof(_Autor), 1, f_Autor) == 1){
				fseek(f_Autor, -2 * sizeof(_Autor), 1);
				fwrite(&Exclui_Pos_Autor, sizeof(_Autor), 1, f_Autor);
				fseek(f_Autor, sizeof(_Autor), 1);
			}
			fseek(f_Autor, 0, 2);
			tamanhoAtual = ftell(f_Autor);
			ftruncate(fileno(f_Autor), tamanhoAtual - sizeof(_Autor));
			fseek(f_Autor, pos, 0);
		}
	}
	//EXCLUI EMPRESTIMOS
	while(fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo) == 1){
		if (!auxEmprestimo.Status) {
			pos = ftell(f_Emprestimo) - sizeof(_Emprestimo);
			while(fread(&Exclui_Pos_Emprestimo, sizeof(_Emprestimo), 1, f_Emprestimo) == 1){
				fseek(f_Emprestimo, -2 * sizeof(_Emprestimo), 1);
				fwrite(&Exclui_Pos_Emprestimo, sizeof(_Emprestimo), 1, f_Emprestimo);
				fseek(f_Emprestimo, sizeof(_Emprestimo), 1);
			}
			fseek(f_Emprestimo, 0, 2);
			tamanhoAtual = ftell(f_Emprestimo);
			ftruncate(fileno(f_Emprestimo), tamanhoAtual - sizeof(_Emprestimo));
			fseek(f_Emprestimo, pos, 0);
		}
	}
	//EXCLUI LIVROS
	while(fread(&auxLivro, sizeof(_Livro), 1, f_Livro) == 1){
		if (!auxLivro.Status) {
			pos = ftell(f_Livro) - sizeof(_Livro);
			while(fread(&Exclui_Pos_Livro, sizeof(_Livro), 1, f_Livro) == 1){
				fseek(f_Livro, -2 * sizeof(_Livro), 1);
				fwrite(&Exclui_Pos_Livro, sizeof(_Livro), 1, f_Livro);
				fseek(f_Livro, sizeof(_Livro), 1);
			}
			fseek(f_Livro, 0, 2);
			tamanhoAtual = ftell(f_Livro);
			ftruncate(fileno(f_Livro), tamanhoAtual - sizeof(_Livro));
			fseek(f_Livro, pos, 0);
		}
	}
	//EXCLUI PESSOAS
	while(fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa) == 1){
		if (!auxPessoa.Status) {
			pos = ftell(f_Pessoa) - sizeof(_Pessoa);
			while(fread(&Exclui_Pos_Pessoa, sizeof(_Pessoa), 1, f_Pessoa) == 1){
				fseek(f_Pessoa, -2 * sizeof(_Pessoa), 1);
				fwrite(&Exclui_Pos_Pessoa, sizeof(_Pessoa), 1, f_Pessoa);
				fseek(f_Pessoa, sizeof(_Pessoa), 1);
			}
			fseek(f_Pessoa, 0, 2);
			tamanhoAtual = ftell(f_Pessoa);
			ftruncate(fileno(f_Pessoa), tamanhoAtual - sizeof(_Pessoa));
			fseek(f_Pessoa, pos, 0);
		}
	}
	//EXCLUI RELACAO
	while(fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao) == 1){
		if (!auxRelacao.Status) {
			pos = ftell(f_Relacao) - sizeof(_Relacao);
			while(fread(&Exclui_Pos_Relacao, sizeof(_Relacao), 1, f_Relacao) == 1){
				fseek(f_Relacao, -2 * sizeof(_Relacao), 1);
				fwrite(&Exclui_Pos_Relacao, sizeof(_Relacao), 1, f_Relacao);
				fseek(f_Relacao, sizeof(_Relacao), 1);
			}
			fseek(f_Relacao, 0, 2);
			tamanhoAtual = ftell(f_Relacao);
			ftruncate(fileno(f_Relacao), tamanhoAtual - sizeof(_Relacao));
			fseek(f_Relacao, pos, 0);
		}
	}
	fclose(f_Autor);
	fclose(f_Emprestimo);
	fclose(f_Livro);
	fclose(f_Pessoa);
	fclose(f_Relacao);
}

//ALTERA??ES
void Alterar_Autor(){	//COMPLETO
	int  IDaux, y = 7, NovoID;
	char op, auxString[20];
	_Autor auxAutor;
	_Relacao auxRelacao;
	FILE *f_Autor, *f_Relacao;
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat", "rb+");
	f_Relacao = fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb+");
	if(Verifica_Presenca_Dados_Autor(f_Autor)){
		Texto_Display(y, "ID autor: ");
		y+=2;
		if(scanf("%d", &IDaux) == 1){
			if(IDaux / 100 > 0 && IDaux / 100 < 10){
				if(Busca_Autor(IDaux, f_Autor) != -1){
					do{
						Clear_Display();
						Texto_Display(7, "[A] Alterar ID");
						Texto_Display(9, "[B] Alterar Nome");
						Texto_Display(11, "[C] Alterar Nacionalidade");
						Texto_Display(13, "[ESC] Sair");
						op = toupper(getch());
					}while(op != 'A' && op != 'B' && op != 'C' && op != 27);
					switch(op){
						case 'A':{
							Clear_Display();
							Texto_Display(7, "Novo ID: ");
							if(scanf("%d", &NovoID) == 1){
								if(NovoID / 100 > 0 && NovoID / 100 < 10){
									if(Busca_Autor(NovoID, f_Autor) == -1){
										//TROCA AUTOR
										Busca_Autor(IDaux, f_Autor);
										fseek(f_Autor, -sizeof(_Autor), 1);
										fread(&auxAutor, sizeof(_Autor), 1, f_Autor);
										auxAutor.ID_Autor = NovoID;
										fseek(f_Autor, -sizeof(_Autor), 1);
										fwrite(&auxAutor, sizeof(_Autor), 1, f_Autor);
										//TROCA RELACAO
										rewind(f_Relacao);
										while(fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao) == 1){
											if(Busca_Autor_Na_Relacao(IDaux, f_Relacao) != -1){
												fseek(f_Relacao, -sizeof(_Relacao), 1);
												fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao);
												auxRelacao.ID_Autor = NovoID;
												fseek(f_Relacao, -sizeof(_Relacao), 1);
												fwrite(&auxRelacao, sizeof(_Relacao), 1, f_Relacao);
											}
										}
										Ordenar_Autor(f_Autor);
										Mensagem1("Alteracao feita com sucesso");
										Mensagem2("Alteracao encerrada");
									}
									else{
										Mensagem1("ID ja cadastrado");
										Mensagem2("Alteracao cancelada");
									}
								}
								else{
									Mensagem1("ID de 3 digitos");
									Mensagem2("Alteracao cancelada");
								}
							}
							else{
								fflush(stdin);
								Mensagem1("Apenas numeros inteiros!");
								Mensagem2("Alteracao cancelada!");
							}
							break;
						}
						case 'B':{
							fflush(stdin);
							Clear_Display();
							Texto_Display(7, "Novo nome: ");
							fseek(f_Autor, - sizeof(_Autor), 1);
							fread(&auxAutor, sizeof(_Autor), 1, f_Autor);
							gets(auxString);
							auxString[0] = toupper(auxString[0]);
							if(strlen(auxString) < 20 && strlen(auxString) > 2){
								strcpy(auxAutor.Nome_Autor, auxString);
								fseek(f_Autor, -sizeof(_Autor), 1);
								fwrite(&auxAutor, sizeof(_Autor), 1, f_Autor);
								Mensagem1("Alteracao concluida!");
								Mensagem2("Alteracao finalizada!");
							}
							else{
								Mensagem1("Limite excedido!");
								Mensagem2("Alteracao cancelada!");
							}
							break;
						}
						case 'C':{
							fflush(stdin);
							Clear_Display();
							Texto_Display(7, "Nova nacionalidade: ");
							fseek(f_Autor, -sizeof(_Autor), 1);
							fread(&auxAutor, sizeof(_Autor), 1, f_Autor);
							gets(auxString);
							auxString[0] = toupper(auxString[0]);
							if(strlen(auxString) < 20 && strlen(auxString) > 1){
								strcpy(auxAutor.Nacionalidade, auxString);
								fseek(f_Autor, -sizeof(_Autor), 1);
								fwrite(&auxAutor, sizeof(_Autor), 1, f_Autor);
								Mensagem1("Alteracao realizada com sucesso");
								Mensagem2("Alteracao finalizada");
							}
							else{
								Mensagem1("Limite excedido!");
								Mensagem2("Alteracao cancelada!");
							}
								break;
						}
						default: {
							Mensagem1("Alteracao cancelada!");
							Mensagem2("Operacao abortada!");
							break;
						}
					}
				}
				else{
					Mensagem1("Autor nao encontrado!");
					Mensagem2("Alteracao cancelada!");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Alteracao cancelada");
			}
		}
		else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros!");
			Mensagem2("Alteracao cancelada");
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Alteracao cancelada");
	}

	fclose(f_Autor);
	fclose(f_Relacao);
}
void Alterar_Emprestimo(){	//COMPLETO
	int IDaux, Diaux, Mesaux, Anoaux;
	char op;
	bool flag_Passou_Verificacao_Lancamento_Livro;
	FILE *f_Emprestimo;
	_Emprestimo aux;
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb+");
	if(Verifica_Presenca_Dados_Emprestimo(f_Emprestimo)){
		Texto_Display(7, "ID emprestimo: ");
		if(scanf("%d", &IDaux) == 1){
			if(IDaux / 100 > 0 && IDaux / 100 < 10){
				if(Busca_Emprestimo(IDaux, f_Emprestimo) != -1){
					fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
					fread(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
					do{
						Clear_Display();
						Texto_Display(7, "[A] Alterar ID");
						Texto_Display(9, "[B] Alterar data emprestimo");
						Texto_Display(11, "[C] Alterar data devolucao");
						Texto_Display(13, "[ESC] Cancelar");
						op = toupper(getch());
					}while(op != 'A' && op != 'B' && op != 'C' && op != 27);
					switch(op){
						case 'A':{
							Clear_Display();
							Texto_Display(7, "ID novo: ");
							if(scanf("%d", &IDaux) == 1){
								if(IDaux / 100 > 0 && IDaux / 100 < 10){
									aux.ID_Emprestimo = IDaux;
									fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
									fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
								}
								else{
									Mensagem1("ID de 3 digitos");
									Mensagem2("Alteracao cancelada");
								}
							}
							else{
								fflush(stdin);
								Mensagem1("Apenas numeros inteiros");
								Mensagem2("Alteracao cancelada");
							}
							break;
						}
						case 'B':{
							do{
								Clear_Display();
								Texto_Display(7, "[A] Dia");
								Texto_Display(9, "[B] Mes");
								Texto_Display(11, "[C] Ano");
								Texto_Display(13, "[D] Data completa");
								Texto_Display(15, "[ESC] Cancelar");
								op = toupper(getch());
							}while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 27);
							switch(op){
								case 'A':{
									Clear_Display();
									Texto_Display(7, "Novo dia: ");
									if(scanf("%d", &Diaux) == 1){
										if(Diaux >= 1 && Diaux <= 30){
											aux.Vet_Data_Emprestimo[0] = Diaux;
											if(Verifica_Data_Emprestimo(aux)){
												fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
												fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
												Mensagem1("Alteracao realizada com sucesso");
												Mensagem2("Alteracao encerrada");
											}
										}
										else{
											Mensagem1("Dia invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 'B':{
									Clear_Display();
									Texto_Display(7, "Novo Mes: ");
									if(scanf("%d", &Mesaux) == 1){
										if(Mesaux >= 1 && Mesaux <= 12){
											aux.Vet_Data_Emprestimo[1] = Mesaux;
											if(Verifica_Data_Emprestimo(aux)){
												fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
												fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
												Mensagem1("Alteracao realizada com sucesso");
												Mensagem2("Alteracao encerrada");
											}
										}
										else{
											Mensagem1("Mes invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 'C':{
									Clear_Display();
									Texto_Display(7, "Novo Ano: ");
									if(scanf("%d", &Anoaux) == 1){
										if(Anoaux >= 1900 && Anoaux <= 2024){
											aux.Vet_Data_Emprestimo[2] = Anoaux;
											if(Verifica_Data_Emprestimo(aux)){
												fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
												fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
												Mensagem1("Alteracao realizada com sucesso");
												Mensagem2("Alteracao encerrada");
											}
										}
										else{
											Mensagem1("Ano invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 'D':{
									Clear_Display();
									Texto_Display(7, "Novo dia: ");
									if(scanf("%d", &Diaux) == 1){
										if(Diaux >= 1 && Diaux <= 30){
											Texto_Display(9, "Novo mes: ");
											if(scanf("%d", &Mesaux) == 1){
												if(Mesaux >= 1 && Mesaux <= 12){
													Texto_Display(9, "Novo ano: ");
													if(scanf("%d", &Anoaux) == 1){
														if(Anoaux >= 1900 && Anoaux <= 2024){
															aux.Vet_Data_Emprestimo[0] = Diaux;
															aux.Vet_Data_Emprestimo[1] = Mesaux;
															aux.Vet_Data_Emprestimo[2] = Anoaux;
															if(Verifica_Data_Emprestimo(aux)){
																fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
																fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
																Mensagem1("Alteracao realizada com sucesso");
																Mensagem2("Alteracao encerrada");
															}
														}
														else{
															Mensagem1("Ano invalido");
															Mensagem2("Alteracao encerrada");
														}
													}
													else{
														fflush(stdin);
														Mensagem1("Apenas numeros inteiros");
														Mensagem2("Alteracao encerrada");
													}
												}
												else{
													Mensagem1("Mes invalido");
													Mensagem2("Alteracao encerrada");
												}
											}
											else{
												fflush(stdin);
												Mensagem1("Apenas numeros inteiros");
												Mensagem2("Alteracao encerrada");
											}
										}
										else{
											Mensagem1("Ano invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 27:{
									Mensagem1("Operacao abortada");
									Mensagem2("Alteracao cancelada");
									break;
								}
							}
							break;
						}
						case 'C':{
							do{
								Clear_Display();
								Texto_Display(7, "[A] Dia");
								Texto_Display(9, "[B] Mes");
								Texto_Display(11, "[C] Ano");
								Texto_Display(13, "[D] Data completa");
								Texto_Display(15, "[ESC] Cancelar");
								op = toupper(getch());
							}while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 27);
							switch(op){
								case 'A':{
									Clear_Display();
									Texto_Display(7, "Novo dia: ");
									if(scanf("%d", &Diaux) == 1){
										if(Diaux >= 1 && Diaux <= 30){
											aux.Vet_Data_Devolucao[0] = Diaux;
											if(Verifica_Data_Emprestimo(aux)){
												fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
												fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
												Mensagem1("Alteracao realizada com sucesso");
												Mensagem2("Alteracao encerrada");
											}
										}
										else{
											Mensagem1("Dia invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 'B':{
									Clear_Display();
									Texto_Display(7, "Novo Mes: ");
									if(scanf("%d", &Mesaux) == 1){
										if(Mesaux >= 1 && Mesaux <= 12){
											aux.Vet_Data_Devolucao[1] = Mesaux;
											if(Verifica_Data_Emprestimo(aux)){
												fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
												fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
												Mensagem1("Alteracao realizada com sucesso");
												Mensagem2("Alteracao encerrada");
											}
										}
										else{
											Mensagem1("Mes invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 'C':{
									Clear_Display();
									Texto_Display(7, "Novo Ano: ");
									if(scanf("%d", &Anoaux) == 1){
										if(Anoaux >= 1900 && Anoaux <= 2024){
											aux.Vet_Data_Devolucao[2] = Anoaux;
											if(Verifica_Data_Emprestimo(aux)){
												fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
												fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
												Mensagem1("Alteracao realizada com sucesso");
												Mensagem2("Alteracao encerrada");
											}
										}
										else{
											Mensagem1("Ano invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 'D':{
									Clear_Display();
									Texto_Display(7, "Novo dia: ");
									if(scanf("%d", &Diaux) == 1){
										if(Diaux >= 1 && Diaux <= 30){
											Texto_Display(9, "Novo mes: ");
											if(scanf("%d", &Mesaux) == 1){
												if(Mesaux >= 1 && Mesaux <= 12){
													Texto_Display(9, "Novo ano: ");
													if(scanf("%d", &Anoaux) == 1){
														if(Anoaux >= 1900 && Anoaux <= 2024){
															aux.Vet_Data_Devolucao[0] = Diaux;
															aux.Vet_Data_Devolucao[1] = Mesaux;
															aux.Vet_Data_Devolucao[2] = Anoaux;
															if(Verifica_Data_Emprestimo(aux)){
																fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
																fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
																Mensagem1("Alteracao realizada com sucesso");
																Mensagem2("Alteracao encerrada");
															}
														}
														else{
															Mensagem1("Ano invalido");
															Mensagem2("Alteracao encerrada");
														}
													}
													else{
														fflush(stdin);
														Mensagem1("Apenas numeros inteiros");
														Mensagem2("Alteracao encerrada");
													}
												}
												else{
													Mensagem1("Mes invalido");
													Mensagem2("Alteracao encerrada");
												}
											}
											else{
												fflush(stdin);
												Mensagem1("Apenas numeros inteiros");
												Mensagem2("Alteracao encerrada");
											}
										}
										else{
											Mensagem1("Ano invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 27:{
									Mensagem1("Operacao abortada");
									Mensagem2("Alteracao cancelada");
									break;
								}
							}
							break;
						}
						default: {
							Mensagem1("Operacao abortada");
							Mensagem2("Alterar cancelada");
							break;
						}
					}
				}
				else{
					Mensagem1("Emprestimo nao achado");
					Mensagem2("Alteracao cancelada");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Alteracao cancelada");
			}
		}
		else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros");
			Mensagem2("Alteracao cancelada");
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Alteracao cancelada");
	}
	fclose(f_Emprestimo);
}
void Alterar_Livro(){	//COMPLETO
	int Diaux, Mesaux, Anoaux, IDaux, IDnovo;
	char op, Tituloaux[20];
	_Livro auxLivro;
	_Emprestimo auxEmprestimo;
	_Relacao auxRelacao;
	FILE *f_Livro, *f_Emprestimo, *f_Relacao;
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb+");
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb+");
	f_Relacao = fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb+");
	if(Verifica_Presenca_Dados_Livro(f_Livro)){
		Texto_Display(7, "ID livro: ");
		if(scanf("%d", &IDaux) == 1){
			if(IDaux / 100 > 0 && IDaux / 100 < 10){
				if(Busca_Livro(IDaux, f_Livro) != -1){
					do{
						Clear_Display();
						Texto_Display(7, "[A] Alterar ID");
						Texto_Display(9, "[B] Alterar data");
						Texto_Display(11, "[C] Alterar titulo");
						Texto_Display(13, "[ESC] Cancelar");
						op = toupper(getch());
					}while(op != 'A' && op != 'B' && op != 'C' && op != 27);
					switch(op){
						case 'A':{
							Clear_Display();
							Texto_Display(7, "Novo ID: ");
							if(scanf("%d", &IDnovo) == 1){
								if(IDnovo / 100 > 0 && IDnovo / 100 < 10){
									if(Busca_Livro(IDnovo, f_Livro) == -1){
										Busca_Livro(IDaux, f_Livro);
										fseek(f_Livro, -sizeof(_Livro), 1);
										fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
										auxLivro.ID_Livro = IDnovo;
										fseek(f_Livro, -sizeof(_Livro), 1);
										fwrite(&auxLivro, sizeof(_Livro), 1, f_Livro);
										rewind(f_Emprestimo);
										if(Busca_Livro_No_Emprestimo(IDaux, f_Emprestimo) != -1){
											fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
											fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo);
											auxEmprestimo.ID_Livro = IDnovo;
											fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
											fwrite(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo);
										}
										rewind(f_Relacao);
										while(fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao) == 1){
											if(Busca_Livro_Na_Relacao(IDaux, f_Relacao) != -1){
												fseek(f_Relacao, -sizeof(_Relacao), 1);
												fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao);
												auxRelacao.ID_Livro = IDnovo;
												fseek(f_Relacao, -sizeof(_Relacao), 1);
												fwrite(&auxRelacao, sizeof(_Relacao), 1, f_Relacao);
											}
										}
										Mensagem1("Alteracao realizada com sucesso");
										Mensagem2("Alteracao encerrada");
									}
									else{
										Mensagem1("ID ja cadastrado");
										Mensagem2("Alteracao encerrada");
									}
								}
								else{
									Mensagem1("ID de 3 digitos");
									Mensagem2("Alteracao cancelada");
								}
							}
							else{
								fflush(stdin);
								Mensagem1("Apenas numeros inteiros");
								Mensagem2("Alteracao cancelada");
							}
							break;
						}
						case 'B':{
							do{
								Clear_Display();
								Texto_Display(7, "[A] Dia");
								Texto_Display(9, "[B] Mes");
								Texto_Display(11, "[C] Ano");
								Texto_Display(13, "[D] Data completa");
								Texto_Display(15, "[ESC] Cancelar");
								op = toupper(getch());
							}while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 27);
							switch(op){
								case 'A':{
									Clear_Display();
									Texto_Display(7, "Novo dia: ");
									if(scanf("%d", &Diaux) == 1){
										if(Diaux >= 1 && Diaux <= 30){
											fseek(f_Livro, -sizeof(_Livro), 1);
											fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
											auxLivro.Vet_Ano_Livro[0] = Diaux;
											fseek(f_Livro, -sizeof(_Livro), 1);
											fwrite(&auxLivro, sizeof(_Livro), 1, f_Livro);
											Mensagem1("Alteracao realizada com sucesso");
											Mensagem2("Alteracao encerrada");
										}
										else{
											Mensagem1("Dia invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 'B':{
									Clear_Display();
									Texto_Display(7, "Novo Mes: ");
									if(scanf("%d", &Mesaux) == 1){
										if(Mesaux >= 1 && Mesaux <= 12){
											fseek(f_Livro, -sizeof(_Livro), 1);
											fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
											auxLivro.Vet_Ano_Livro[1] = Mesaux;
											fseek(f_Livro, -sizeof(_Livro), 1);
											fwrite(&auxLivro, sizeof(_Livro), 1, f_Livro);
											Mensagem1("Alteracao realizada com sucesso");
											Mensagem2("Alteracao encerrada");
										}
										else{
											Mensagem1("Mes invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 'C':{
									Clear_Display();
									Texto_Display(7, "Novo Ano: ");
									if(scanf("%d", &Anoaux) == 1){
										if(Anoaux >= 1900 && Anoaux <= 2024){
											fseek(f_Livro, -sizeof(_Livro), 1);
											fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
											auxLivro.Vet_Ano_Livro[2] = Anoaux;
											fseek(f_Livro, -sizeof(_Livro), 1);
											fwrite(&auxLivro, sizeof(_Livro), 1, f_Livro);
											Mensagem1("Alteracao realizada com sucesso");
											Mensagem2("Alteracao encerrada");
										}
										else{
											Mensagem1("Ano invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 'D':{
									Clear_Display();
									Texto_Display(7, "Novo dia: ");
									if(scanf("%d", &Diaux) == 1){
										if(Diaux >= 1 && Diaux <= 30){
											Texto_Display(9, "Novo mes: ");
											if(scanf("%d", &Mesaux) == 1){
												if(Mesaux >= 1 && Mesaux <= 12){
													Texto_Display(9, "Novo ano: ");
													if(scanf("%d", &Anoaux) == 1){
														if(Anoaux >= 1900 && Anoaux <= 2024){
															fseek(f_Livro, -sizeof(_Livro), 1);
															fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
															auxLivro.Vet_Ano_Livro[0] = Diaux;
															auxLivro.Vet_Ano_Livro[1] = Mesaux;
															auxLivro.Vet_Ano_Livro[2] = Anoaux;
															fseek(f_Livro, -sizeof(_Livro), 1);
															fwrite(&auxLivro, sizeof(_Livro), 1, f_Livro);
															Mensagem1("Alteracao realizada com sucesso");
															Mensagem2("Alteracao encerrada");
														}
														else{
															Mensagem1("Ano invalido");
															Mensagem2("Alteracao encerrada");
														}
													}
													else{
														fflush(stdin);
														Mensagem1("Apenas numeros inteiros");
														Mensagem2("Alteracao encerrada");
													}
												}
												else{
													Mensagem1("Mes invalido");
													Mensagem2("Alteracao encerrada");
												}
											}
											else{
												fflush(stdin);
												Mensagem1("Apenas numeros inteiros");
												Mensagem2("Alteracao encerrada");
											}
										}
										else{
											Mensagem1("Ano invalido");
											Mensagem2("Alteracao encerrada");
										}
									}
									else{
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros");
										Mensagem2("Alteracao cancelada");
									}
									break;
								}
								case 27:{
									Mensagem1("Operacao abortada");
									Mensagem2("Alteracao cancelada");
									break;
								}
							}
						}
						case 'C':{
							Clear_Display();
							Texto_Display(7, "Novo titulo: ");
							fflush(stdin);
							gets(Tituloaux);
							if(strlen(Tituloaux) <= 20 && strlen(Tituloaux) > 2){
								fseek(f_Livro, -sizeof(_Livro), 1);
								fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
								strcpy(auxLivro.Titulo, Tituloaux);
								fseek(f_Livro, -sizeof(_Livro), 1);
								fwrite(&auxLivro, sizeof(_Livro), 1, f_Livro);
								Mensagem1("Alteracao realizada com sucesso");
								Mensagem2("Alteracao cancelada");
							}
							else{
								Mensagem1("Titulo 	excedeu o limite");
								Mensagem2("Alteracao cancelada");
							}
								break;
							}
						default:{
							Mensagem1("Operacao abortada");
							Mensagem2("Alteracao cancelada");
							break;
						}
					}
				}
				else{
					Mensagem1("Livro nao encontrado");
					Mensagem2("Alteracao cancelada");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Alteracao cancelada");
			}
		}
		else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros");
			Mensagem2("Alteracao cancelada");
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Alteracao cancelada");
	}
	Ordenar_Livro(f_Livro);
	fclose(f_Livro);
	fclose(f_Emprestimo);
	fclose(f_Relacao);
}
void Alterar_Pessoa(){	//COMPLETO
	int IDaux, y = 7, NovoID;
	char op, auxString[30];
	_Pessoa auxPessoa;
	_Emprestimo auxEmprestimo;
	FILE *f_Pessoa, *f_Emprestimo;
	f_Pessoa = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "rb+");
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb+");
	if(Verifica_Presenca_Dados_Pessoa(f_Pessoa)){
		Texto_Display(y, "ID pessoa: ");
		y+=2;
		if(scanf("%d", &IDaux) == 1){
			if(IDaux / 100 > 0 && IDaux / 100 < 10){
				if(Busca_Pessoa(IDaux, f_Pessoa) != -1){
					do{
						Clear_Display();
						Texto_Display(7, "[A] Alterar ID");
						Texto_Display(9, "[B] Alterar Nome");
						Texto_Display(11, "[C] Alterar Telefone");
						Texto_Display(13, "[D] Alterar Endereco");
						Texto_Display(15, "[ESC] Sair");
						op = toupper(getch());
					}while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 27);
					switch(op){
						case 'A':{
							Clear_Display();
							Texto_Display(7, "Novo ID: ");
							if(scanf("%d", &NovoID) == 1){
								if(NovoID / 100 > 0 && NovoID / 100 < 10){
									if(Busca_Pessoa(NovoID, f_Pessoa) == -1){
										//TROCA PESSOA
										Busca_Pessoa(IDaux, f_Pessoa);
										fseek(f_Pessoa, -sizeof(_Pessoa), 1);
										fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
										auxPessoa.ID_Pessoa = NovoID;
										fseek(f_Pessoa, -sizeof(_Pessoa), 1);
										fwrite(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
										//TROCA EMPRESTIMO
										rewind(f_Emprestimo);
										if(Busca_Pessoa_No_Emprestimo(IDaux, f_Emprestimo) != -1){
											fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
											fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo);
											auxEmprestimo.ID_Pessoa = NovoID;
											fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
											fwrite(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo);
										}
										Mensagem1("Alteracao feita com sucesso");
										Mensagem2("Alteracao encerrada");
									}
									else{
										Mensagem1("ID ja cadastrado");
										Mensagem2("Alteracao cancelada");
									}
								}
								else{
									Mensagem1("ID de 3 digitos");
									Mensagem2("Alteracao cancelada");
								}
							}
							else{
								fflush(stdin);
								Mensagem1("Apenas numeros inteiros");
								Mensagem2("Alteracao cancelada");
							}
							break;
						}
						case 'B':{
							fflush(stdin);
							Clear_Display();
							Texto_Display(7, "Novo nome: ");
							fseek(f_Pessoa, -sizeof(_Pessoa), 1);
							fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
							gets(auxString);
							auxString[0] = toupper(auxString[0]);
							if(strlen(auxString) < 20){
								strcpy(auxPessoa.Nome_Pessoa, auxString);
								fseek(f_Pessoa, -sizeof(_Pessoa), 1);
								fwrite(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
								Mensagem1("Alteracao realizada com sucesso");
								Mensagem2("Alteracao finalizada");
							}
							else{
								Mensagem1("Nome excedeu o limite");
								Mensagem2("Alteracao cancelada");
							}
							break;
						}
						case 'C':{
							fflush(stdin);
							Clear_Display();
							Texto_Display(7, "Novo telefone: ");
							fseek(f_Pessoa, -sizeof(_Pessoa), 1);
							fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
							gets(auxString);
							auxString[0] = toupper(auxString[0]);
							if(strlen(auxString) == 14){
								strcpy(auxPessoa.Telefone_Pessoa, auxString);
								fseek(f_Pessoa, -sizeof(_Pessoa), 1);
								fwrite(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
								Mensagem1("Alteracao realizada com sucesso");
								Mensagem2("Alteracao finalizada");
							}
							else{
								Mensagem1("Telefone no formato errado");
								Mensagem2("Alteracao cancelada");
							}
							break;
						}
						case 'D':{
							fflush(stdin);
							Clear_Display();
							Texto_Display(7, "Novo endereco: ");
							fseek(f_Pessoa, -sizeof(_Pessoa), 1);
							fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
							gets(auxString);
							auxString[0] = toupper(auxString[0]);
							if(strlen(auxString) < 30 && strlen(auxString) > 4){
								strcpy(auxPessoa.Endereco_Pessoa, auxString);
								fseek(f_Pessoa, -sizeof(_Pessoa), 1);
								fwrite(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
								Mensagem1("Alteracao realizada com sucesso");
								Mensagem2("Alteracao finalizada");
							}
							else{
								Mensagem1("Endereco excedeu o limite de espaco");
								Mensagem2("Alteracao cancelada");
							}
							break;
						}
						default:{
							Mensagem1("Operacao abortada");
							Mensagem2("Alteracao cancelada");
							break;
						}
					}
				}
				else{
					Mensagem1("Pessoa nao encontrado");
					Mensagem2("Alteracao cancelada");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Alteracao cancelada");
			}
		}
		else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros");
			Mensagem2("Alteracao cancelada");
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Alteracao cancelada");
	}

	fclose(f_Pessoa);
	fclose(f_Emprestimo);
}


//BUSCAS
int Busca_Autor(int ID, FILE *f){	//COMPLETO
	int Qnt_Reg;
	_Autor aux;
	fseek(f, 0, 2);
	Qnt_Reg = ftell(f) / sizeof(_Autor);
	if(Qnt_Reg > 0){
		rewind(f);
		fread(&aux, sizeof(_Autor), 1, f);
		while(!feof(f) && (ID != aux.ID_Autor || !aux.Status)){
			fread(&aux, sizeof(_Autor), 1, f);
		}
		if(ID == aux.ID_Autor && aux.Status){
			return ftell(f) - sizeof(_Autor);
		}
		else{
			return -1;
		}
	}
	else{
		return -1;
	}
}
int Busca_Autor_Na_Relacao(int ID, FILE *f){	//COMPLETO
	_Relacao aux;
	fseek(f, -sizeof(_Relacao), 1);
	fread(&aux, sizeof(_Relacao), 1, f);
	while(!feof(f) && (ID != aux.ID_Autor || !aux.Status)){
		fread(&aux, sizeof(_Relacao), 1, f);
	}
	if(ID == aux.ID_Autor && aux.Status){
		return ftell(f) - sizeof(_Relacao);
	}
	else{
		return -1;
	}
}
int Busca_Emprestimo(int ID, FILE *f){	//COMPLETO
	int Qnt_Reg;
	_Emprestimo aux;
	fseek(f, 0, 2);
	Qnt_Reg = ftell(f) / sizeof(_Emprestimo);
	if(Qnt_Reg > 0){
		rewind(f);
		fread(&aux, sizeof(_Emprestimo), 1, f);
		while(!feof(f) && (ID != aux.ID_Emprestimo || !aux.Status)){
			fread(&aux, sizeof(_Emprestimo), 1, f);
		}

		if(ID == aux.ID_Emprestimo && aux.Status){
			return ftell(f) - sizeof(_Emprestimo);
		}
		else{
			return -1;
		}
	}
	else{
		return -1;
	}
}
int Busca_Livro(int ID, FILE *f){	//COMPLETO
	int Qnt_Reg;
	_Livro aux;
	fseek(f, 0, 2);
	Qnt_Reg = ftell(f) / sizeof(_Livro);
	if(Qnt_Reg > 0){
		rewind(f);
		fread(&aux, sizeof(_Livro), 1, f);
		while (!feof(f) && (ID != aux.ID_Livro || !aux.Status)){
			fread(&aux, sizeof(_Livro), 1, f);
		}
		if (ID == aux.ID_Livro && aux.Status)
			return ftell(f)-sizeof(_Livro);
		else
			return -1;
	}
	else{
		return -1;
	}
}
int Busca_Livro_Autor_Relacionamento(int ID_Livro, int ID_Autor, FILE *f){	//COMPLETO
	_Relacao aux;
	rewind(f);
	fread(&aux, sizeof(_Relacao), 1, f);
	while(!feof(f) && ((ID_Autor != aux.ID_Autor || ID_Livro != aux.ID_Livro) || !aux.Status)){
		fread(&aux, sizeof(_Relacao), 1, f);
	}
	if (ID_Livro == aux.ID_Livro && ID_Autor == aux.ID_Autor && aux.Status)
		return ftell(f) -sizeof(_Relacao);
	else
		return -1;
}
int Busca_Livro_Na_Relacao(int ID, FILE *f){	//COMPLETO
	_Relacao aux;
	fseek(f, -sizeof(_Relacao), 1);
	fread(&aux, sizeof(_Relacao), 1, f);
	while(!feof(f) && (ID != aux.ID_Livro || !aux.Status)){
		fread(&aux, sizeof(_Relacao), 1, f);
	}
	if(ID == aux.ID_Livro && aux.Status){
		return ftell(f) - sizeof(_Relacao);
	}
	else{
		return -1;
	}
}
int Busca_Livro_No_Emprestimo(int ID, FILE *f){	//COMPLETO
	_Emprestimo aux;
	fread(&aux, sizeof(_Emprestimo), 1, f);
	while(!feof(f) && (ID != aux.ID_Livro || !aux.Status)){
		fread(&aux, sizeof(_Emprestimo), 1, f);
	}
	if(ID == aux.ID_Livro && aux.Status){
		return ftell(f) - sizeof(_Emprestimo);
	}
	else{
		return -1;
	}
}
int Busca_Pessoa(int ID, FILE *f){	//COMPLETO
	int Qnt_Reg;
	_Pessoa aux;
	fseek(f, 0, 2);
	Qnt_Reg = ftell(f) / sizeof(_Autor);
	if(Qnt_Reg > 0){
		rewind(f);
		fread(&aux, sizeof(_Pessoa), 1, f);
		while(!feof(f) && (ID != aux.ID_Pessoa || !aux.Status)){
			fread(&aux, sizeof(_Pessoa), 1, f);
		}
		if(ID == aux.ID_Pessoa && aux.Status){
			return ftell(f) - sizeof(_Pessoa);
		} 
		else{
			return -1;
		}
	}
	else{
		return -1;
	}
}
int Busca_Pessoa_No_Emprestimo(int ID, FILE *f){	//COMPLETO
	_Emprestimo aux;
	fread(&aux, sizeof(_Emprestimo), 1, f);
	while(!feof(f) && (ID != aux.ID_Pessoa || !aux.Status)){
		fread(&aux, sizeof(_Emprestimo), 1, f);
	}
	if(ID == aux.ID_Pessoa && aux.Status){
		return ftell(f) - sizeof(_Emprestimo);
	}
	else{
		return -1;
	}
}


//CADASTROS
void Cadastro_Autor(){	//COMPLETO
	FILE *f_Autor;
	int IDaux;
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat", "rb+");
	Nome_Tabela("CADASTRO AUTOR");
	Texto_Display(7, "ID: ");
	if(scanf("%d", &IDaux) == 1){
		if(IDaux / 100 > 0 && IDaux / 100 < 10){
			if(Busca_Autor(IDaux, f_Autor) == -1){
				Insere_Autor(IDaux, f_Autor);
			}
			else{
				Mensagem1("Autor ja cadastrado");
			}
		}
		else{
			Mensagem1("ID de 3 digitos");
			Mensagem2("Cadastro cancelado");
		}
	}
	else{
		fflush(stdin);
		Mensagem1("Apenas numeros inteiros");
	}
	fclose(f_Autor);
}
void Cadastro_Emprestimo(){	//COMPLETO
	FILE *f_Emprestimo, *f_Livro, *f_Pessoa;
	int IDaux;
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb+");
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb+");
	f_Pessoa = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "rb");
	Nome_Tabela("CADASTRO EMPRESTIMO");
	Texto_Display(7, "ID: ");
	if(Verifica_Presenca_Dados_Livro(f_Livro) && Verifica_Presenca_Dados_Pessoa(f_Pessoa)){
		if(scanf("%d", &IDaux) == 1){
			if(IDaux / 100 > 0 && IDaux / 100 < 10){
				if(Busca_Emprestimo(IDaux, f_Emprestimo) == -1){
					Insere_Emprestimo(IDaux, f_Emprestimo, f_Livro, f_Pessoa);
				}
				else{
					Mensagem1("Emprestimo ja cadastrado");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Cadastro cancelado");
			}
		}
		else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros");
		}
	}
	else{
		Mensagem1("Nao ha dados para suficientes");
		Mensagem2("Cadastro cancelado");
	}
	fclose(f_Livro);
	fclose(f_Pessoa);
	fclose(f_Emprestimo);
}
void Cadastro_Livro(){	//COMPLETO
	FILE *f_Livro;
	int IDaux;
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb+");
	Nome_Tabela("CADASTRO LIVRO");
	Texto_Display(7, "ID: ");
	if(scanf("%d", &IDaux) == 1){
		if(IDaux / 100 > 0 && IDaux / 100 < 10){
			if(Busca_Livro(IDaux, f_Livro) == -1){
				Insere_Livro(IDaux, f_Livro);
			}
			else{
				Mensagem1("Livro ja cadastrado");
			}
		}
		else{
			Mensagem1("ID de 3 digitos");
			Mensagem2("Cadastro cancelado");
		}
	}
	else{
		fflush(stdin);
		Mensagem1("Apenas numeros inteiros");
	}
	fclose(f_Livro);
}
void Cadastro_Pessoa(){	//COMPLETO
	FILE *f_Pessoa;
	int IDaux;
	f_Pessoa = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "rb+");
	Nome_Tabela("CADASTRO PESSOA");
	Texto_Display(7,"ID: ");
	if(scanf("%d", &IDaux) == 1){
		if(IDaux / 100 > 0 && IDaux / 100 < 10){
			if(Busca_Pessoa(IDaux, f_Pessoa) == -1){
				Insere_Pessoa(IDaux, f_Pessoa);
			}
			else{
				Mensagem1("Pessoa ja cadastrado");
			}
		}
		else{
			Mensagem1("ID de 3 digitos");
			Mensagem2("Cadastro cancelado");
		}
	}
	else{
		fflush(stdin);
		Mensagem1("Apenas numeros inteiros");
	}
	fclose(f_Pessoa);
}
void Cadastro_Relacionamento(){	//COMPLETO
	FILE *f_Relacao, *f_Livro, *f_Autor;
	int IDaux;
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat","rb");
	f_Relacao = fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb+");
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb");
	if(Verifica_Presenca_Dados_Livro(f_Livro) && Verifica_Presenca_Dados_Autor(f_Autor)){
		Nome_Tabela("CADASTRO RELACAO");
		Texto_Display(7, "ID Livro: ");
		if(scanf("%d", &IDaux) == 1){
			if(IDaux / 100 > 0 && IDaux / 100 < 10){
				if(Busca_Livro(IDaux, f_Livro) != -1){
					Insere_Relacionamento(IDaux, f_Relacao, f_Autor);
				}
				else{
					Mensagem1("Livro nao encontrado");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Cadastro cancelado");
			}
		}
		else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros");
		}
	}
	else{
		Mensagem1("Nao ha dados suficientes");
		Mensagem2("Cadastro cancelado");
	}
	fclose(f_Relacao);
	fclose(f_Livro);
	fclose(f_Autor);
}


//CONSULTAS
void Autor_Por_Letra(){	//COMPLETO
	int x, y;
	char Inicial, cont = 0;
	FILE *f_Autor;
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat", "rb+");
	_Autor auxAutor;
	Ordenar_Autor_Por_Nacionalidade(f_Autor);
	Texto_Display(7, "Letra inicial: ");
	fflush(stdin);
	scanf("%c", &Inicial);
	Clear_Display();
	Inicial = toupper(Inicial);
	rewind(f_Autor);
	y = 7;
	while(fread(&auxAutor, sizeof(_Autor), 1, f_Autor)){
		textcolor(WHITE);
		if(auxAutor.Nome_Autor[0] == Inicial){
			gotoxy(52,y++);
			printf("ID autor: %d", auxAutor.ID_Autor);
			gotoxy(52, y++);
			printf("Nome: %s", auxAutor.Nome_Autor);
			gotoxy(52, y++);
			printf("Nacionalidade: %s", auxAutor.Nacionalidade);
			gotoxy(52, y++);
			for(x = 52; x < 97; x++){
				printf("%c", 196);
			}
			Mensagem1("Pressione qualquer tecla");
			Mensagem2("Para continuar");
			if(y == 19){
				getch();
				y = 7;
				Clear_Display();
			}
			cont++;
		}
	}
	getch();
	if(cont == 0){
		Mensagem1("Nao encontrado");
		Mensagem2("Consulta encerrada");
	}
	Ordenar_Autor(f_Autor);
	fclose(f_Autor);
}
void Consulta_Autor(){	//COMPLETO
	int IDaux, pos, x, y;
	char op;
	FILE *f_Autor;
	_Autor aux;
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat", "rb");
	if(Verifica_Presenca_Dados_Autor(f_Autor)){
		Escolha_Exibe_Consulta(op);
		Escolha_Exibe_Consulta_Color(op);
		if(op == 'A'){
			Nome_Tabela("CONSULTA AUTOR");
			Texto_Display(7, "ID: ");
			if(scanf("%d", &IDaux) == 1){
				if(IDaux / 100 > 0 && IDaux / 100 < 10){
					if((pos = Busca_Autor(IDaux, f_Autor)) != -1){
						y = 7;
						Clear_Display();
						textcolor(WHITE);
						fseek(f_Autor, pos, 0);
						fread(&aux, sizeof(_Autor), 1, f_Autor);
						gotoxy(52,y++);
						printf("ID: %d", aux.ID_Autor);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						gotoxy(52,y++);
						printf("Nome: %s", aux.Nome_Autor);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						gotoxy(52,y++);
						printf("Nacionalidade: %s", aux.Nacionalidade);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						Mensagem1("Pressione qualquer tecla");
						Mensagem2("Para voltar ao Menu");
						getch();
						Clear_Mensagem();
					}
					else{
						Mensagem1("Autor nao encontrado");
						Mensagem2("Consulta cancelada");
					}
				}
				else{
					Mensagem1("ID de 3 digitos");
					Mensagem2("Consulta cancelada");
				}
			}
			else{
				fflush(stdin);
				Mensagem1("Apenas numeros inteiros");
				Mensagem2("Consulta cancelada");
			}
		}
		else if(op == 'B'){
			y = 7;
			rewind(f_Autor);
			while(fread(&aux, sizeof(_Autor), 1, f_Autor) == 1){
				if(aux.Status){
					textcolor(WHITE);
					gotoxy(52,y++);
					printf("ID: %d", aux.ID_Autor);
					gotoxy(52,y++);
					printf("Nome: %s", aux.Nome_Autor);
					gotoxy(52,y++);
					printf("Nacionalidade: %s", aux.Nacionalidade);
					gotoxy(52, y);
					for(x = 52; x < 97; x++) {
						printf("%c", 196);
					}
					y += 2;
					if(y == 22){
						fseek(f_Autor, -sizeof(_Autor), 1);
						if(fread(&aux, sizeof(_Autor), 1, f_Autor) == 1){
							fseek(f_Autor, -sizeof(_Autor), 1);
							Mensagem1("Pressione qualquer tecla");
							Mensagem2("Para continuar");
							y = 7;
							getch();
							Clear_Display();
							Clear_Mensagem();
						}
						else{
							fseek(f_Autor, -sizeof(_Autor), 1);
						}
					}
				}
			}
			Mensagem1("Pressione qualquer tecla");
			Mensagem2("Para voltar ao Menu");
			getch();
			Clear_Mensagem();
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Consulta cancelada");
	}
	fclose(f_Autor);
}
void Consulta_Emprestimo(){	//COMPLETO
	int IDaux, pos, x, y;
	char op;
	Nome_Tabela("CONSULTA EMPRESTIMO");
	FILE *f_Emprestimo;
	_Emprestimo aux;
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb");
	if(Verifica_Presenca_Dados_Emprestimo(f_Emprestimo)){
		Escolha_Exibe_Consulta(op);
		Escolha_Exibe_Consulta_Color(op);
		if(op == 'A'){
			Texto_Display(7, "ID: ");
			if(scanf("%d", &IDaux) == 1){
				if(IDaux / 100 > 0 && IDaux / 100 < 10){
					if((pos = Busca_Emprestimo(IDaux, f_Emprestimo)) != -1){
						if(aux.Status){
							y = 7;
							Clear_Display();
							textcolor(WHITE);
							fseek(f_Emprestimo, pos, 0);
							fread(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
							gotoxy(52,y++);
							printf("ID emprestimo: %d", aux.ID_Emprestimo);
							gotoxy(52, y++);
							for(x = 52; x < 97; x++) {
								printf("%c", 196);
							}
							gotoxy(52,y++);
							printf("ID livro: %d", aux.ID_Livro);
							gotoxy(52, y++);
							for(x = 52; x < 97; x++) {
								printf("%c", 196);
							}
							gotoxy(52,y++);
							printf("ID pessoa: %d", aux.ID_Pessoa);
							gotoxy(52, y++);
							for(x = 52; x < 97; x++) {
								printf("%c", 196);
							}
							gotoxy(52,y++);
							printf("Data emprestimo: %d/%d/%d", aux.Vet_Data_Emprestimo[0], aux.Vet_Data_Emprestimo[1], aux.Vet_Data_Emprestimo[2]);
							gotoxy(52, y++);
							for(x = 52; x < 97; x++) {
								printf("%c", 196);
							}
							gotoxy(52,y++);
							printf("Data devolucao: %d/%d/%d", aux.Vet_Data_Devolucao[0], aux.Vet_Data_Devolucao[1], aux.Vet_Data_Devolucao[2]);
							gotoxy(52, y++);
							for(x = 52; x < 97; x++) {
								printf("%c", 196);
							}
							Mensagem1("Pressione qualquer tecla");
							Mensagem2("Para voltar ao Menu");
							getch();
							Clear_Mensagem();
						}
					}
					else{
						Mensagem1("Livro nao encontrado");
					}
				}
				else{
					Mensagem1("ID de 3 digitos");
					Mensagem2("Consulta cancelada");
				}
			}
			else{
				fflush(stdin);
				Mensagem1("Apenas numeros inteiros");
			}
		}
		else if(op == 'B'){
			y = 7;
			rewind(f_Emprestimo);
			while((fread(&aux, sizeof(_Emprestimo), 1, f_Emprestimo)) == 1){
				if(aux.Status){
					textcolor(WHITE);
					gotoxy(52,y++);
					printf("ID emprestimo: %d", aux.ID_Emprestimo);
					gotoxy(52,y++);
					printf("ID livro: %d", aux.ID_Livro);
					gotoxy(52,y++);
					printf("ID pessoa: %d", aux.ID_Pessoa);
					gotoxy(52,y++);
					printf("Data emprestimo: %d/%d/%d", aux.Vet_Data_Emprestimo[0], aux.Vet_Data_Emprestimo[1], aux.Vet_Data_Emprestimo[2]);
					gotoxy(52,y++);
					printf("Data devolucao: %d/%d/%d", aux.Vet_Data_Devolucao[0], aux.Vet_Data_Devolucao[1], aux.Vet_Data_Devolucao[2]);
					gotoxy(52, y);
					for(x = 52; x < 97; x++) {
						printf("%c", 196);
					}
					y += 2;
					if(y == 21){
						fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
						if((fread(&aux, sizeof(_Emprestimo), 1, f_Emprestimo)) == 1){
							fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
							Mensagem1("Pressione qualquer tecla");
							Mensagem2("Para continuar");
							y = 7;
							getch();
							Clear_Display();
							Clear_Mensagem();
						}
						else{
							fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
						}
					}
				}
			}
			Mensagem1("Pressione qualquer tecla");
			Mensagem2("Para voltar ao Menu");
			getch();
			Clear_Mensagem();
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrado");
		Mensagem2("Consulta cancelada");
	}
	fclose(f_Emprestimo);
}
void Consulta_Completa(){	//COMPLETO
	int pos_Emprestimo, pos_Livro, pos_Pessoa, IDaux, y, x;
	char op;
	FILE *f_Autor, *f_Emprestimo, *f_Livro, *f_Pessoa, *f_Relacao;
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat", "rb");
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb");
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb");
	f_Pessoa = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "rb");
	f_Relacao = fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb");
	_Autor auxAutor;
	_Livro auxLivro;
	_Pessoa auxPessoa;
	_Emprestimo auxEmprestimo;
	_Relacao auxRelacao;
	do{
		Clear_Fora();
		Clear_Display();
		Clear_op();
		Borda_Menu();
		Preenchimento_Menu();
		Nome_Tabela("RELATORIO - CONSULTA DETALHADA");
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
			switch(op){
				case 'A':{
					Consulta_Livro();
					break;
				}
				case 'B':{
					Consulta_Autor();
					break;
				}
				case 'C':{
					Consulta_Pessoa();
					break;
				}
				case 'D':{
					Escolha_Exibe_Consulta(op);
					Escolha_Exibe_Consulta_Color(op);
					if(op == 'A'){
						Texto_Display(7, "ID: ");
						if(scanf("%d", &IDaux) == 1){
							if(IDaux / 100 > 0 && IDaux / 100 < 10){
								if((pos_Emprestimo = Busca_Emprestimo(IDaux, f_Emprestimo)) != -1){
									if(auxEmprestimo.Status){
										y = 7;
										Clear_Display();
										textcolor(WHITE);
										fseek(f_Emprestimo, pos_Emprestimo, 0);
										fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo);
										pos_Livro = Busca_Livro(auxEmprestimo.ID_Livro, f_Livro);
										fseek(f_Livro, pos_Livro, 0);
										fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
										pos_Pessoa = Busca_Pessoa(auxEmprestimo.ID_Pessoa, f_Pessoa);
										fseek(f_Pessoa, pos_Pessoa, 0);
										fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
										gotoxy(52,y++);
										printf("ID emprestimo: %d", auxEmprestimo.ID_Emprestimo);
										gotoxy(52, y++);
										for(x = 52; x < 97; x++){
											printf("%c", 196);
										}
										gotoxy(52,y++);
										printf("ID livro: %d", auxLivro.ID_Livro);
										gotoxy(52,y++);
										printf("Ano: %d", auxLivro.Vet_Ano_Livro[2]);
										gotoxy(52,y++);
										printf("Titulo: %s", auxLivro.Titulo);
										gotoxy(52, y++);
										for(x = 52; x < 97; x++) {
											printf("%c", 196);
										}
										gotoxy(52,y++);
										printf("ID pessoa: %d", auxPessoa.ID_Pessoa);
										gotoxy(52,y++);
										printf("Nome: %s", auxPessoa.Nome_Pessoa);
										gotoxy(52,y++);
										printf("Telefone: %s", auxPessoa.Telefone_Pessoa);
										gotoxy(52,y++);
										printf("Endereco: %s", auxPessoa.Endereco_Pessoa);
										gotoxy(52,y++);
										for(x = 52; x < 97; x++) {
											printf("%c", 196);
										}
										gotoxy(52, y++);
										printf("Data emprestimo: %d/%d/%d", auxEmprestimo.Vet_Data_Emprestimo[0], auxEmprestimo.Vet_Data_Emprestimo[1], auxEmprestimo.Vet_Data_Emprestimo[2]);
										gotoxy(52,y++);
										printf("Data devolucao: %d/%d/%d", auxEmprestimo.Vet_Data_Devolucao[0], auxEmprestimo.Vet_Data_Devolucao[1], auxEmprestimo.Vet_Data_Devolucao[2]);
										gotoxy(52, y++);
										gotoxy(52, y++);
										for(x = 52; x < 97; x++) {
											printf("%c", 196);
										}
										Mensagem1("Pressione qualquer tecla");
										Mensagem2("Para voltar ao Menu");
										getch();
										Clear_Mensagem();
									}
								}
								else{
									Mensagem1("Livro nao encontrado");
								}
							}
							else{
								Mensagem1("ID de 3 digitos");
								Mensagem2("Consulta cancelada");
							}
						}
						else{
							fflush(stdin);
							Mensagem1("Apenas numeros inteiros");
						}
					}
					else if(op == 'B'){
						rewind(f_Emprestimo);
						while(fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo) == 1){
							if(auxEmprestimo.Status){
								y = 7;
								Clear_Display();
								textcolor(WHITE);
								pos_Livro = Busca_Livro(auxEmprestimo.ID_Livro, f_Livro);
								fseek(f_Livro, pos_Livro, 0);
								fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
								pos_Pessoa = Busca_Pessoa(auxEmprestimo.ID_Pessoa, f_Pessoa);
								fseek(f_Pessoa, pos_Pessoa, 0);
								fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
								gotoxy(52,y++);
								printf("ID emprestimo: %d", auxEmprestimo.ID_Emprestimo);
								gotoxy(52, y++);
								for(x = 52; x < 97; x++){
									printf("%c", 196);
								}
								gotoxy(52,y++);
								printf("ID livro: %d", auxLivro.ID_Livro);
								gotoxy(52,y++);
								printf("Ano: %d", auxLivro.Vet_Ano_Livro[2]);
								gotoxy(52,y++);
								printf("Titulo: %s", auxLivro.Titulo);
								gotoxy(52, y++);
								for(x = 52; x < 97; x++) {
									printf("%c", 196);
								}
								gotoxy(52,y++);
								printf("ID pessoa: %d", auxPessoa.ID_Pessoa);
								gotoxy(52,y++);
								printf("Nome: %s", auxPessoa.Nome_Pessoa);
								gotoxy(52,y++);
								printf("Telefone: %s", auxPessoa.Telefone_Pessoa);
								gotoxy(52,y++);
								printf("Endereco: %s", auxPessoa.Endereco_Pessoa);
								gotoxy(52,y++);
								for(x = 52; x < 97; x++) {
									printf("%c", 196);
								}
								gotoxy(52, y++);
								printf("Data emprestimo: %d/%d/%d", auxEmprestimo.Vet_Data_Emprestimo[0], auxEmprestimo.Vet_Data_Emprestimo[1], auxEmprestimo.Vet_Data_Emprestimo[2]);
								gotoxy(52,y++);
								printf("Data devolucao: %d/%d/%d", auxEmprestimo.Vet_Data_Devolucao[0], auxEmprestimo.Vet_Data_Devolucao[1], auxEmprestimo.Vet_Data_Devolucao[2]);
								gotoxy(52, y++);
								if(fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo) == 1){
									fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
									Mensagem1("Pressione qualquer tecla");
									Mensagem2("Para continuar");
								}
								else{
									Mensagem1("Pressione qualquer tecla");
									Mensagem2("Para voltar ao menu");
								}
								getch();
								Clear_Mensagem();
							}
						}
					}
					break;
				}
				case 'E':{
					Escolha_Exibe_Consulta_Relacao(op);
					Escolha_Exibe_Consulta_Color_Relacao(op);
					if(op == 'A'){
						Texto_Display(7, "ID autor: ");
						if(scanf("%d", &IDaux) == 1){
							if(IDaux / 100 > 0 && IDaux / 100 < 10){
								rewind(f_Relacao);
								if(Busca_Autor_Na_Relacao(IDaux, f_Relacao) != -1){
									rewind(f_Relacao);
									Clear_Display();
									while(fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao) == 1){
										y = 7;
										if(IDaux == auxRelacao.ID_Autor && auxRelacao.Status){
											Busca_Livro(auxRelacao.ID_Livro, f_Livro);
											fseek(f_Livro, -sizeof(_Livro), 1);
											fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
											Busca_Autor(auxRelacao.ID_Autor, f_Autor);
											fseek(f_Autor, -sizeof(_Autor), 1);
											fread(&auxAutor, sizeof(_Autor), 1, f_Autor);
											textcolor(WHITE);
											gotoxy(52,y++);
											printf("ID livro: %d", auxLivro.ID_Livro);
											gotoxy(52,y++);
											printf("Ano: %d", auxLivro.Vet_Ano_Livro[2]);
											gotoxy(52,y++);
											printf("Titulo: %s", auxLivro.Titulo);
											gotoxy(52, y++);
											for(x = 52; x < 97; x++){
												printf("%c", 196);
											}
											gotoxy(52,y++);
											printf("ID autor: %d", auxAutor.ID_Autor);
											gotoxy(52, y++);
											printf("Nome: %s", auxAutor.Nome_Autor);
											gotoxy(52, y++);
											printf("Nacionalidade: %s", auxAutor.Nacionalidade);
											gotoxy(52, y++);
											for(x = 52; x < 97; x++){
												printf("%c", 196);
											}
										}
										if(fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao) == 1){
											fseek(f_Relacao, -sizeof(_Relacao), 1);
											Mensagem1("Pressione qualquer tecla");
											Mensagem2("Para continuar");
										}
										else{
											Mensagem1("Pressione qualquer tecla");
											Mensagem2("Para voltar ao menu");
										}
										getch();
										Clear_Display();
									}
									Clear_Mensagem();
								}
								else{
									Mensagem1("Nao encontrado");
									Mensagem2("Relatorio cancelado");
								}
							}
							else{
								Mensagem1("ID de 3 digitos");
								Mensagem2("Consulta cancelada");
							}
						}
						else{
							fflush(stdin);
							Mensagem1("Apenas numeros inteiros");
							Mensagem2("Consulta cancelada");
						}
					}
					else if(op == 'B'){
						Texto_Display(7, "ID livro: ");
						if(scanf("%d", &IDaux) == 1){
							if(IDaux / 100 > 0 && IDaux / 100 < 10){
								rewind(f_Relacao);
								if(Busca_Livro_Na_Relacao(IDaux, f_Relacao) != -1){
									rewind(f_Relacao);
									Clear_Display();
									while(fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao) == 1){
										y = 7;
										if(IDaux == auxRelacao.ID_Livro && auxRelacao.Status){
											Busca_Autor(auxRelacao.ID_Autor, f_Autor);
											fseek(f_Autor, -sizeof(_Autor), 1);
											fread(&auxAutor, sizeof(_Autor), 1, f_Autor);
											Busca_Livro(auxRelacao.ID_Livro, f_Livro);
											fseek(f_Livro, -sizeof(_Livro), 1);
											fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
											textcolor(WHITE);
											gotoxy(52,y++);
											printf("ID Autor: %d", auxAutor.ID_Autor);
											gotoxy(52,y++);
											printf("Nome: %s", auxAutor.Nome_Autor);
											gotoxy(52,y++);
											printf("Nacionalidade: %s", auxAutor.Nacionalidade);
											gotoxy(52, y++);
											for(x = 52; x < 97; x++){
												printf("%c", 196);
											}
											gotoxy(52,y++);
											printf("ID Livro: %d", auxLivro.ID_Livro);
											gotoxy(52, y++);
											printf("Ano: %d", auxLivro.Vet_Ano_Livro[2]);
											gotoxy(52, y++);
											printf("Titulo: %s", auxLivro.Titulo);
											gotoxy(52, y++);
											for(x = 52; x < 97; x++){
												printf("%c", 196);
											}
										}
										if(y==15){
											if(fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao) == 1){
												fseek(f_Relacao, -sizeof(_Relacao), 1);
												Mensagem1("Pressione qualquer tecla");
												Mensagem2("Para continuar");
											}
											else{
												Mensagem1("Pressione qualquer tecla");
												Mensagem2("Para voltar ao menu");
											}
											getch();
											Clear_Display();
										}
									}
									Clear_Mensagem();
								}
								else{
									Mensagem1("Nao encontrado");
									Mensagem2("Relatorio cancelado");
								}
							}
							else{
								Mensagem1("ID de 3 digitos");
								Mensagem2("Consulta cancelada");
							}
						}
						else{
							fflush(stdin);
							Mensagem1("Apenas numeros inteiros");
							Mensagem2("Consulta cancelada");
						}
					}
					else if(op == 'C'){
						y = 7;
						rewind(f_Relacao);
						while(fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao) == 1){
							if(auxRelacao.Status){
								Busca_Autor(auxRelacao.ID_Autor, f_Autor);
								fseek(f_Autor, -sizeof(_Autor), 1);
								fread(&auxAutor, sizeof(_Autor), 1, f_Autor);
								Busca_Livro(auxRelacao.ID_Livro, f_Livro);
								fseek(f_Livro, -sizeof(_Livro), 1);
								fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
								textcolor(WHITE);
								gotoxy(52,y++);
								printf("ID livro: %d", auxLivro.ID_Livro);
								gotoxy(52,y++);
								printf("Ano: %d", auxLivro.Vet_Ano_Livro[2]);
								gotoxy(52,y++);
								printf("Titulo: %s", auxLivro.Titulo);
								gotoxy(52, y++);
								for(x = 52; x < 97; x++) {
									printf("%c", 196);
								}
								gotoxy(52,y++);
								printf("ID autor: %d", auxAutor.ID_Autor);
								gotoxy(52,y++);
								printf("Nome: %s", auxAutor.Nome_Autor);
								gotoxy(52,y++);
								printf("Nacionalidade: %s", auxAutor.Nacionalidade);
								gotoxy(52, y);
								for(x = 52; x < 97; x++) {
									printf("%c", 196);
								}
								if(fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao) == 1){
									fseek(f_Relacao, -sizeof(_Relacao), 1);
									Mensagem1("Pressione qualquer tecla");
									Mensagem2("Para continuar");
									y = 7;
									getch();
									Clear_Display();
									Clear_Mensagem();
								}
							}
						}
						Mensagem1("Pressione qualquer tecla");
						Mensagem2("Para voltar ao Menu");
						getch();
						Clear_Mensagem();
					}
					break;
				}
			}
		Clear_Display();
	}while(op != 27);
	fclose(f_Autor);
	fclose(f_Emprestimo);
	fclose(f_Livro);
	fclose(f_Pessoa);
	fclose(f_Relacao);
}
void Consulta_Livro(){	//COMPLETO
	int IDaux, pos, x, y;
	char op;
	Nome_Tabela("CONSULTA LIVRO");
	FILE *f_Livro;
	_Livro aux;
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb");
	if(Verifica_Presenca_Dados_Livro(f_Livro)){
		Escolha_Exibe_Consulta(op);
		Escolha_Exibe_Consulta_Color(op);
		if(op == 'A'){
			Texto_Display(7, "ID: ");
			if(scanf("%d", &IDaux) == 1){
				if(IDaux / 100 > 0 && IDaux / 100 < 10){
					if((pos = Busca_Livro(IDaux, f_Livro)) != -1){
						y = 7;
						Clear_Display();
						textcolor(WHITE);
						fseek(f_Livro, pos, 0);
						fread(&aux, sizeof(_Livro), 1, f_Livro);
						gotoxy(52,y++);
						printf("ID: %d", aux.ID_Livro);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						gotoxy(52,y++);
						printf("Titulo: %s", aux.Titulo);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						gotoxy(52,y++);
						printf("Ano: %d", aux.Vet_Ano_Livro[2]);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						if(aux.Status_Emprestado){
							Texto_Display(y++, "Disponivel para emprestimo?: Sim");
						}
						else{
							Texto_Display(y++, "Disponivel para emprestimo?: Nao");
						}
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						Mensagem1("Pressione qualquer tecla");
						Mensagem2("Para voltar ao Menu");
						getch();
						Clear_Mensagem();
					}
					else{
						Mensagem1("Livro nao encontrado");
					}
				}
				else{
					Mensagem1("ID de 3 digitos");
					Mensagem2("Consulta cancelada");
				}
			}
			else{
				fflush(stdin);
				Mensagem1("Apenas numeros inteiros");
			}
		}
		else if(op == 'B'){
			y = 7;
			rewind(f_Livro);
			while(fread(&aux, sizeof(_Livro), 1, f_Livro) == 1){
				if(aux.Status){
					textcolor(WHITE);
					gotoxy(52,y);
					printf("ID: %d", aux.ID_Livro);
					y++;
					gotoxy(52,y);
					printf("Titulo: %s", aux.Titulo);
					y++;
					gotoxy(52,y);
					printf("Ano: %d", aux.Vet_Ano_Livro[2]);
					y++;
					if(aux.Status_Emprestado){
						Texto_Display(y, "Disponivel para emprestimo?: Sim");
					}
					else{
						Texto_Display(y, "Disponivel para emprestimo?: Nao");
					}
					y++;
					gotoxy(52, y);
					for(x = 52; x < 97; x++) {
						printf("%c", 196);
					}
					y += 2;
					if(y == 19){
						fseek(f_Livro, -sizeof(_Livro), 1);
						if(fread(&aux, sizeof(_Livro), 1, f_Livro) == 1){
							fseek(f_Livro, -sizeof(_Livro), 1);
							Mensagem1("Pressione qualquer tecla");
							Mensagem2("Para continuar");
							y = 7;
							getch();
							Clear_Display();
							Clear_Mensagem();
						}
						else{
							fseek(f_Livro, -sizeof(_Livro), 1);
						}
						
					}
				}
			}
			Mensagem1("Pressione qualquer tecla");
			Mensagem2("Para voltar ao Menu");
			getch();
			Clear_Mensagem();

		}
	}
	else{
		Mensagem1("Nao ha dados cadastrado");
		Mensagem2("Consulta cancelada");
	}
	fclose(f_Livro);
}
void Consulta_Pessoa(){	//COMPLETO
	int IDaux, pos, x, y;
	char op;
	FILE *f_Pessoa;
	_Pessoa aux;
	Nome_Tabela("CONSULTA PESSOA");
	f_Pessoa = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "rb");
	if(Verifica_Presenca_Dados_Pessoa(f_Pessoa)){
		Escolha_Exibe_Consulta(op);
		Escolha_Exibe_Consulta_Color(op);
		if(op == 'A'){
			Texto_Display(7, "ID: ");
			if(scanf("%d", &IDaux) == 1){
				if(IDaux / 100 > 0 && IDaux / 100 < 10){
					if((pos = Busca_Pessoa(IDaux, f_Pessoa)) != -1){
						y = 7;
						Clear_Display();
						textcolor(WHITE);
						fseek(f_Pessoa, pos, 0);
						fread(&aux, sizeof(_Pessoa), 1, f_Pessoa);
						gotoxy(52,y++);
						printf("ID: %d", aux.ID_Pessoa);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						gotoxy(52,y++);
						printf("Nome: %s", aux.Nome_Pessoa);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						gotoxy(52,y++);
						printf("Endereco: %s", aux.Endereco_Pessoa);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						gotoxy(52,y++);
						printf("Fone: %s", aux.Telefone_Pessoa);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++) {
							printf("%c", 196);
						}
						Mensagem1("Pressione qualquer tecla");
						Mensagem2("Para voltar ao Menu");
						getch();
						Clear_Mensagem();
					}
					else{
						Mensagem1("Livro nao encontrado");
					}
				}
				else{
					Mensagem1("ID de 3 digitos");
					Mensagem2("Consulta cancelada");
				}
			}
			else{
				fflush(stdin);
				Mensagem1("Apenas numeros inteiros");
			}
		}
		else if(op == 'B'){
			y = 7;
			rewind(f_Pessoa);
			while(fread(&aux, sizeof(_Pessoa), 1, f_Pessoa) == 1){
				if(aux.Status){
					textcolor(WHITE);
					gotoxy(52,y++);
					printf("ID: %d", aux.ID_Pessoa);
					gotoxy(52,y++);
					printf("Nome: %s", aux.Nome_Pessoa);
					gotoxy(52,y++);
					printf("Endereco: %s", aux.Endereco_Pessoa);
					gotoxy(52,y++);
					printf("Fone: %s", aux.Telefone_Pessoa);
					gotoxy(52, y);
					for(x = 52; x < 97; x++) {
						printf("%c", 196);
					}
					y += 2;
					if(y == 19){
						fseek(f_Pessoa, -sizeof(_Pessoa), 1);
						if(fread(&aux, sizeof(_Pessoa), 1, f_Pessoa) == 1){
							fseek(f_Pessoa, -sizeof(_Pessoa), 1);
							Mensagem1("Pressione qualquer tecla");
							Mensagem2("Para continuar");
							y = 7;
							getch();
							Clear_Display();
							Clear_Mensagem();
						}
						else{
							fseek(f_Pessoa, -sizeof(_Pessoa), 1);
						}
						
					}
				}
			}
			Mensagem1("Pressione qualquer tecla");
			Mensagem2("Para voltar ao Menu");
			getch();
			Clear_Mensagem();
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrado");
		Mensagem2("Consulta cancelada");
	}
	fclose(f_Pessoa);
}
void Consulta_Relacionamento(){	//COMPLETO
	int IDaux, x, y;
	char op;
	FILE *f_Relacao;
	_Relacao aux;

	Nome_Tabela("CONSULTA RELACAO");
	f_Relacao = fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb");

	if(Verifica_Presenca_Dados_Relacao(f_Relacao)){
		Escolha_Exibe_Consulta_Relacao(op);
		Escolha_Exibe_Consulta_Color_Relacao(op);
		if(op == 'A'){
			Texto_Display(7, "ID autor: ");
			if(scanf("%d", &IDaux) == 1){
				if(IDaux / 100 > 0 && IDaux / 100 < 10){
					y = 7;
					rewind(f_Relacao);
					Clear_Display();
					while(fread(&aux, sizeof(_Relacao), 1, f_Relacao) == 1){
						if(IDaux == aux.ID_Autor && aux.Status){
							textcolor(WHITE);
							gotoxy(52,y++);
							printf("ID livro: %d", aux.ID_Livro);
							gotoxy(52,y++);
							printf("ID autor: %d", aux.ID_Autor);
							gotoxy(52, y);
							for(x = 52; x < 97; x++) {
								printf("%c", 196);
							}
							y += 2;
							if(y == 19){
								fseek(f_Relacao, -sizeof(_Relacao), 1);
								if(fread(&aux, sizeof(_Relacao), 1, f_Relacao) == 1){
									fseek(f_Relacao, -sizeof(_Relacao), 1);
									Mensagem1("Pressione qualquer tecla");
									Mensagem2("Para continuar");
									y = 7;
									getch();
									Clear_Display();
									Clear_Mensagem();
								}
								else{
									fseek(f_Relacao, -sizeof(_Relacao), 1);
								}
							}
						}
					}
					Mensagem1("Pressione qualquer tecla");
					Mensagem2("Para voltar ao Menu");
					getch();
					Clear_Mensagem();
				}
				else{
					Mensagem1("ID de 3 digitos");
					Mensagem2("Consulta cancelada");
				}
			}
			else{
				fflush(stdin);
				Mensagem1("Apenas numeros inteiros");
				Mensagem2("Consulta cancelada");
			}
		}
		else if(op == 'B'){
			Texto_Display(7, "ID livro: ");
			if(scanf("%d", &IDaux) == 1){
				if(IDaux / 100 > 0 && IDaux / 100 < 10){
					y = 7;
					rewind(f_Relacao);
					Clear_Display();
					while(fread(&aux, sizeof(_Relacao), 1, f_Relacao) == 1){
						if(IDaux == aux.ID_Livro && aux.Status){
							textcolor(WHITE);
							gotoxy(52,y++);
							printf("ID livro: %d", aux.ID_Livro);
							gotoxy(52,y++);
							printf("ID autor: %d", aux.ID_Autor);
							gotoxy(52, y);
							for(x = 52; x < 97; x++) {
								printf("%c", 196);
							}
							y += 2;
							if(y == 19){
								if(fread(&aux, sizeof(_Relacao), 1, f_Relacao) == 1){
									fseek(f_Relacao, -sizeof(_Relacao), 1);
									Mensagem1("Pressione qualquer tecla");
									Mensagem2("Para continuar");
									y = 7;
									getch();
									Clear_Display();
									Clear_Mensagem();
								}
								else{
									fseek(f_Relacao, -sizeof(_Relacao), 1);
								}
							}
						}
					}
					Mensagem1("Pressione qualquer tecla");
					Mensagem2("Para voltar ao Menu");
					getch();
					Clear_Mensagem();
				}
				else{
					Mensagem1("ID de 3 digitos");
					Mensagem2("Consulta cancelada");
				}
			}
			else{
				fflush(stdin);
				Mensagem1("Apenas numeros inteiros");
				Mensagem2("Consulta cancelada");
			}
		}
		else if(op == 'C'){
			y = 7;
			rewind(f_Relacao);
			while(fread(&aux, sizeof(_Relacao), 1, f_Relacao) == 1){
				if(aux.Status){
					textcolor(WHITE);
					gotoxy(52,y++);
					printf("ID livro: %d", aux.ID_Livro);
					gotoxy(52,y++);
					printf("ID autor: %d", aux.ID_Autor);
					gotoxy(52, y);
					for(x = 52; x < 97; x++) {
						printf("%c", 196);
					}
					y += 2;
					if(y == 19){ 
						if(fread(&aux, sizeof(_Relacao), 1, f_Relacao) == 1){
							fseek(f_Relacao, -sizeof(_Relacao), 1);
							Mensagem1("Pressione qualquer tecla");
							Mensagem2("Para continuar");
							y = 7;
							getch();
							Clear_Display();
							Clear_Mensagem();
						}
						else{
							fseek(f_Relacao, -sizeof(_Relacao), 1);
						}
						
					}
				}
			}
			Mensagem1("Pressione qualquer tecla");
			Mensagem2("Para voltar ao Menu");
			getch();
			Clear_Mensagem();
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Consulta cancelada");
	}
	fclose(f_Relacao);
}
void Emprestimos_Por_Pessoa(){	//COMPLETO
	int cont = 0, IDaux, y, x, pos, pos2;
	FILE *f_Livro, *f_Pessoa, *f_Emprestimo;
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb");
	f_Pessoa = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "rb");
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb");
	_Emprestimo auxEmprestimo;
	_Livro auxLivro;
	_Pessoa auxPessoa;
	Texto_Display(7, "ID pessoa: ");
	if(scanf("%d", &IDaux) == 1){
		if(IDaux / 100 > 0 && IDaux/100 < 10){
			rewind(f_Emprestimo);
			while(fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo) == 1){
				fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
				y = 7;
				if(Busca_Pessoa_No_Emprestimo(IDaux, f_Emprestimo) != -1){
					textcolor(WHITE);
					Busca_Livro(auxEmprestimo.ID_Livro, f_Livro);
					fseek(f_Livro, -sizeof(_Livro), 1);
					fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
					pos = Busca_Pessoa(auxEmprestimo.ID_Pessoa, f_Pessoa);
					fseek(f_Pessoa, -sizeof(_Pessoa), 1);
					fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
					gotoxy(52, y++);
					printf("ID emprestimo: %d", auxEmprestimo.ID_Emprestimo);
					gotoxy(52, y++);
					for(x = 52; x < 97; x++){
						printf("%c", 196);
					}
					gotoxy(52, y++);
					printf("ID livro: %d", auxLivro.ID_Livro);
					gotoxy(52, y++);
					printf("Ano: %d", auxLivro.Vet_Ano_Livro[2]);
					gotoxy(52, y++);
					printf("Titulo: %s", auxLivro.Titulo);
					gotoxy(52, y++);
					for(x = 52; x < 97; x++){
						printf("%c", 196);
					}
					gotoxy(52, y++);
					printf("ID pessoa: %d", auxPessoa.ID_Pessoa);
					gotoxy(52, y++);
					printf("Nome: %s", auxPessoa.Nome_Pessoa);
					gotoxy(52, y++);
					printf("Telefone: %s", auxPessoa.Telefone_Pessoa);
					gotoxy(52, y++);
					printf("Endereco: %s", auxPessoa.Endereco_Pessoa);
					gotoxy(52, y++);
					for(x = 52; x < 97; x++){
						printf("%c", 196);
					}
					cont ++;
					if(fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo) == 1){
						fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
						Mensagem1("Pressione qualquer tecla");
						Mensagem2("Para continuar");
						getch();
						Clear_Display();
					}
				}
			}
			if(cont == 0){
				Mensagem1("Nao ha emprestimo dessa pessoa");
				Mensagem2("Relatorio cancelado");
			}
			else{
				Mensagem1("Pressione qualquer tecla");
				Mensagem2("Para voltar ao menu");
				getch();
			}
		}
		else{
			Mensagem1("ID de 3 digitos");
			Mensagem2("Relatorio cancelado");
		}
	}
	else{
		fflush(stdin);
		Mensagem1("Apenas numeros inteiros");
		Mensagem2("Relatorio cancelado");
	}
	Clear_Mensagem();
	fclose(f_Livro);
	fclose(f_Pessoa);
	fclose(f_Emprestimo);
}
void Livro_Por_Palavra(){
	int y, x, t, j, i, pos;
	char Termo[20], auxTermo[20];
	_Livro auxLivro;
	FILE *f_Livro;
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb+");
	fflush(stdin);
    y = 7; // Linha inicial para exibição
    Texto_Display(y++, "Palavra: ");
    fgets(Termo, sizeof(Termo), stdin);
    Termo[strcspn(Termo, "\n")] = '\0'; // Remover a nova linha da string

    if (strlen(Termo) > 0) {
        strupr(Termo);
        Ordenar_Livros_Por_Data(f_Livro);
        rewind(f_Livro);

        // Iterar sobre todos os livros
        while (fread(&auxLivro, sizeof(_Livro), 1, f_Livro) == 1) {
			textcolor(WHITE);
            strcpy(auxTermo, auxLivro.Titulo);
            strupr(auxTermo);

            // Buscar o termo dentro do título
            for (i = 0; i <= strlen(auxTermo) - strlen(Termo); i++) {
                pos = 0;
                // Comparar caractere por caractere
                while (pos < strlen(Termo) && auxTermo[i + pos] == Termo[pos]) {
                    pos++;
                }

                // Se encontrou o termo, exibe os dados do livro
                if (pos == strlen(Termo) && auxLivro.Status) {
                    gotoxy(52, y++);
                    printf("ID livro: %d", auxLivro.ID_Livro);
                    gotoxy(52, y++);
                    printf("Titulo: %s", auxLivro.Titulo);
                    gotoxy(52, y++);
                    printf("Ano: %d", auxLivro.Vet_Ano_Livro[2]);
                    gotoxy(52, y++);
                    for (x = 52; x < 97; x++) {
                        printf("%c", 196); // Linha de separação
                    }
                }
            }
			if(y == 19){
				if(fread(&auxLivro, sizeof(_Livro), 1, f_Livro) == 1){
					fseek(f_Livro, -sizeof(_Livro), 1);
				}
				Mensagem1("Pressione qualquer tecla");
				Mensagem2("Para continuar");
				getch();
			}
        }
		Mensagem1("Pressione qualquer tecla");
		Mensagem2("Para voltar ao menu");
		getch();

        // Caso não tenha encontrado nenhum livro
        if (ftell(f_Livro) == 0) {
            Mensagem1("Nenhum livro encontrado");
            Mensagem2("Relatorio cancelado");
        }

    } else {
        Mensagem1("Formato invalido");
        Mensagem2("Relatorio cancelado");
    }
    fclose(f_Livro);
}
void Livros_De_Autor(){	//COMPLETO
	int cont = 0, IDaux, y, x;
	FILE *f_Autor, *f_Livro, *f_Relacao;
	_Autor auxAutor;
	_Relacao auxRelacao;
	_Livro auxLivro;
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat", "rb");
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb");
	f_Relacao = fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb");
	Texto_Display(7, "ID autor: ");
	if(scanf("%d", &IDaux) == 1){
		if(IDaux/100 > 0 && IDaux/100 < 10){
			if(Busca_Autor(IDaux, f_Autor) != -1){
				rewind(f_Autor);
				while(fread((&auxRelacao), sizeof(_Relacao), 1, f_Relacao) == 1){
					Clear_Display();
					y = 7;
					if(auxRelacao.ID_Autor == IDaux){
						textcolor(WHITE);
						Busca_Autor(auxRelacao.ID_Autor, f_Autor);
						fseek(f_Autor, -sizeof(_Autor), 1);
						fread(&auxAutor, sizeof(_Autor), 1, f_Autor);
						gotoxy(52, y++);
						printf("ID autor: %d", auxAutor.ID_Autor);
						gotoxy(52, y++);
						printf("Nome: %s", auxAutor.Nome_Autor);
						gotoxy(52, y++);
						printf("Nacionalidade: %s", auxAutor.Nacionalidade);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++){
							printf("%c", 196);
						}
						Busca_Livro(auxRelacao.ID_Livro, f_Livro);
						fseek(f_Livro, -sizeof(_Livro), 1);
						fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
						gotoxy(52, y++);
						printf("ID livro: %d", auxLivro.ID_Livro);
						gotoxy(52, y++);
						printf("Ano: %d", auxLivro.Vet_Ano_Livro[2]);
						gotoxy(52, y++);
						printf("Titulo: %s", auxLivro.Titulo);
						gotoxy(52, y++);
						for(x = 52; x < 97; x++){
							printf("%c", 196);
						}
						if(fread((&auxRelacao), sizeof(_Relacao), 1, f_Relacao) == 1){
							fseek(f_Relacao, -sizeof(_Relacao), 1);
							Mensagem1("Pressione qualquer tecla");
							Mensagem2("Para continuar");
							getch();
						}
						cont++;
					}
				}
				if(cont == 0){
					Mensagem1("Nao ha livros desse autor");
					Mensagem2("Relatorio cancelado");
				}
				else{
					Mensagem1("Pressione qualquer tecla");
					Mensagem2("Para voltar ao menu");
					getch();
					Clear_Mensagem();
				}
			}
			else{
				Mensagem1("Autor nao encontrado");
				Mensagem2("Relatorio cancelado");
			}
		}
		else{
			Mensagem1("Formato do ID invalido");
			Mensagem2("Relatorio cancelado");
		}
	}
	else{
		fflush(stdin);
		Mensagem1("Apenas numeros inteiros");
		Mensagem2("Relatorio cancelado");
	}
	Clear_Mensagem();
	fclose(f_Autor);
	fclose(f_Livro);
	fclose(f_Relacao);
}
void Relatorio_Emprestimo_Completo(){	//COMPLETO
	int cont = 0, y, x;
	FILE *f_Livro, *f_Pessoa, *f_Emprestimo;
	_Livro auxLivro;
	_Emprestimo auxEmprestimo;
	_Pessoa auxPessoa;
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb");
	f_Pessoa = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "rb");
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb");

	while(fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa) == 1){
		rewind(f_Emprestimo);
		while(fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo) == 1){
			Clear_Display();
			y = 7;
			if(auxPessoa.ID_Pessoa == auxEmprestimo.ID_Pessoa){
				textcolor(WHITE);
				fseek(f_Pessoa, -sizeof(_Pessoa), 1);
				fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
				Busca_Livro(auxEmprestimo.ID_Livro, f_Livro);
				fseek(f_Livro, -sizeof(_Livro), 1);
				fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
				gotoxy(52, y++);
				printf("ID pessoa: %d", auxPessoa.ID_Pessoa);
				gotoxy(52, y++);
				printf("Nome: %s", auxPessoa.Nome_Pessoa);
				gotoxy(52, y++);
				for(x = 52; x < 97; x++){
					printf("%c", 196);
				}
				gotoxy(52, y++);
				printf("ID livro: %d", auxLivro.ID_Livro);
				gotoxy(52, y++);
				printf("Ano: %d", auxLivro.Vet_Ano_Livro[2]);
				gotoxy(52, y++);
				printf("Titulo: %s", auxLivro.Titulo);
				gotoxy(52, y++);
				for(x = 52; x < 97; x++){
					printf("%c", 196);
				}
				gotoxy(52, y++);
				printf("Ano emprestimo: %d", auxEmprestimo.Vet_Data_Emprestimo[2]);
				gotoxy(52, y++);
				printf("Ano devolucao: %d", auxEmprestimo.Vet_Data_Devolucao[2]);
				gotoxy(52, y++);
				printf("ID livro: %d", auxLivro.ID_Livro);
				cont++;
				if(fread((&auxEmprestimo), sizeof(_Emprestimo), 1, f_Emprestimo) == 1){
					Mensagem1("Pressione qualquer tecla");
					Mensagem2("Para continuar");
					getch();
				}
			}
		}
	}
	Mensagem1("Pressione qualquer tecla");
	Mensagem2("Para voltar ao menu");
	getch();
	Clear_Mensagem();
	fclose(f_Livro);
	fclose(f_Pessoa);
	fclose(f_Emprestimo);
}

//EXCLUS?ES
void Exclusao_Autor(){	//COMPLETO
	int IDaux, y =9;
	char op;
	_Autor auxAutor;
	_Relacao auxRelacao;
	FILE *f_Autor, *f_Relacao;
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat", "rb+");
	f_Relacao = fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb+");
	if(Verifica_Presenca_Dados_Autor(f_Autor)){
		Nome_Tabela("EXCLUSAO AUTOR");
		Texto_Display(7,"ID autor: ");
		if(scanf("%d", &IDaux) == 1){
			if(IDaux / 100 > 0 && IDaux / 100 < 10){
				if(Busca_Autor(IDaux, f_Autor) != -1){
					Escolha_Excluir(y, op);
					if(op == 'S'){
						fseek(f_Autor, -sizeof(_Autor), 1);
						fread(&auxAutor, sizeof(_Autor), 1, f_Autor);
						auxAutor.Status = false;
						fseek(f_Autor, -sizeof(_Autor), 1);
						fwrite(&auxAutor, sizeof(_Autor), 1, f_Autor);
						rewind(f_Relacao);
						while(!feof(f_Relacao)){
							if((Busca_Autor_Na_Relacao(IDaux, f_Relacao)) != -1){
								fseek(f_Relacao, -sizeof(_Relacao), 1);
								fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao);
								auxRelacao.Status = false;
								fseek(f_Relacao, -sizeof(_Relacao), 1);
								fwrite(&auxRelacao, sizeof(_Relacao), 1, f_Relacao);
							}
						}
						Mensagem1("Excluido com sucesso");
						Mensagem2("Exclusao finalizada");
					}
					else{
						Mensagem1("Operacao abortada");
						Mensagem2("Exclusao cancelada");
					}
					
				}
				else{
					Mensagem1("Autor nao encontrado");
					Mensagem2("Exclusao cancelada");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Exclusao cancelada");
			}
		}
		else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros");
			Mensagem2("Exclusao cancelada");
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Exclusao cancelada");
	}
	fclose(f_Autor);
	fclose(f_Relacao);
}
void Exclusao_Emprestimo(){	//COMPLETO
	int y = 7, IDaux;
	char op;
	_Livro auxLivro;
	_Emprestimo aux;
	FILE *f_Emprestimo, *f_Livro;
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb+");
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb+");
	if(Verifica_Presenca_Dados_Emprestimo(f_Emprestimo)){
		Texto_Display(y, "ID emprestimo: ");
		y+=2;
		if(scanf("%d", &IDaux) == 1){
			if(IDaux / 100 > 0 && IDaux / 100 < 10){
				if(Busca_Emprestimo(IDaux, f_Emprestimo) != -1){
					Escolha_Excluir(y, op);
					if(op == 'S'){
						fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
						fread(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
						aux.Status = false;
						fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
						fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
						auxLivro.ID_Livro = aux.ID_Livro;
						Busca_Livro(auxLivro.ID_Livro, f_Livro);
						fseek(f_Livro, -sizeof(_Livro), 1);
						fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
						auxLivro.Status_Emprestado = true;
						fseek(f_Livro, -sizeof(_Livro), 1);
						fwrite(&auxLivro, sizeof(_Livro), 1, f_Livro);
						Mensagem1("Excluido com sucesso");
						Mensagem2("Exclusao finalizada");
					}
					else{
						Mensagem1("Operacao abortada");
						Mensagem2("Exclusao cancelada");
					}
				}
				else{
					Mensagem1("Emprestimo nao encontrado");
					Mensagem2("Exclusao cancelada");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Exclusao cancelada");
			}
		}
		else{
			Mensagem1("Apenas numeros inteiro");
			Mensagem2("Exclusao cancelada");
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Exclusao cancelada");
	}
	fclose(f_Livro);
	fclose(f_Emprestimo);
}
void Exclusao_Livro(){	//COMPLETO
	int IDaux, y = 9;
	char op;
	_Livro auxLivro;
	_Emprestimo auxEmprestimo;
	_Relacao auxRelacao;
	FILE *f_Livro, *f_Emprestimo, *f_Relacao;
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb+");
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb+");
	f_Relacao = fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb+");
	if(Verifica_Presenca_Dados_Livro(f_Livro)){
		Nome_Tabela("EXCLUSAO LIVRO");
		Texto_Display(7,"ID livro: ");
		if(scanf("%d", &IDaux) == 1){
			if(IDaux / 100 > 0 && IDaux / 100 < 10){
				if(Busca_Livro(IDaux, f_Livro) != -1){
					Escolha_Excluir(y, op);
					if(op == 'S'){
						fseek(f_Livro, -sizeof(_Livro), 1);
						fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
						auxLivro.Status = false;
						fseek(f_Livro, -sizeof(_Livro), 1);
						fwrite(&auxLivro, sizeof(_Livro), 1, f_Livro);
						rewind(f_Emprestimo);
						if((Busca_Livro_No_Emprestimo(IDaux, f_Emprestimo)) != -1){
							fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
							fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo);
							auxEmprestimo.Status = false;
							fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
							fwrite(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo);
						}
						rewind(f_Relacao);
						while(fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao)){
							if((Busca_Livro_Na_Relacao(IDaux, f_Relacao)) != -1){
								fseek(f_Relacao, -sizeof(_Relacao), 1);
								fread(&auxRelacao, sizeof(_Relacao), 1, f_Relacao);
								auxRelacao.Status = false;
								fseek(f_Relacao, -sizeof(_Relacao), 1);
								fwrite(&auxRelacao, sizeof(_Relacao), 1, f_Relacao);
							}
						}
						Mensagem1("Excluido com sucesso");
						Mensagem2("Exclusao finalizada");
					}
					else{
						Mensagem1("Operacao abortada");
						Mensagem2("Exclusao cancelada");
					}
					
				}
				else{
					Mensagem1("Autor nao encontrado");
					Mensagem2("Exclusao cancelada");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Exclusao cancelada");
			}
		}
		else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros");
			Mensagem2("Exclusao cancelada");
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Exclusao cancelada");
	}
	fclose(f_Livro);
	fclose(f_Emprestimo);
	fclose(f_Relacao);
}
void Exclusao_Pessoa(){	//COMPLETO
	int IDaux, y = 9, pos;
	char op;
	_Livro auxLivro;
	_Pessoa auxPessoa;
	_Emprestimo auxEmprestimo;
	FILE *f_Pessoa, *f_Emprestimo, *f_Livro;
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb+");
	f_Pessoa = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "rb+");
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb+");
	if(Verifica_Presenca_Dados_Pessoa(f_Pessoa)){
		Nome_Tabela("EXCLUSAO PESSOA");
		Texto_Display(7,"ID pessoa: ");
		if(scanf("%d", &IDaux) == 1){
			if(IDaux / 100 > 0 && IDaux / 100 < 10){
				if(Busca_Pessoa(IDaux, f_Pessoa) != -1){
					Escolha_Excluir(y, op);
					if(op == 'S'){
						fseek(f_Pessoa, -sizeof(_Pessoa), 1);
						fread(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
						auxPessoa.Status = false;
						fseek(f_Pessoa, -sizeof(_Pessoa), 1);
						fwrite(&auxPessoa, sizeof(_Pessoa), 1, f_Pessoa);
						rewind(f_Emprestimo);
						while(fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo) == 1){
							fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
							if((Busca_Pessoa_No_Emprestimo(IDaux, f_Emprestimo)) != -1){
								fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
								fread(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo);
								auxEmprestimo.Status = false;
								fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
								fwrite(&auxEmprestimo, sizeof(_Emprestimo), 1, f_Emprestimo);
								fseek(f_Emprestimo, -sizeof(_Emprestimo), 1);
								auxLivro.ID_Livro = auxEmprestimo.ID_Livro;
								Busca_Livro(auxLivro.ID_Livro, f_Livro);
								fseek(f_Livro, -sizeof(_Livro), 1);
								fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
								auxLivro.Status_Emprestado = true;
								fseek(f_Livro, -sizeof(_Livro), 1);
								fwrite(&auxLivro, sizeof(_Livro), 1, f_Livro);
							}
						}
						Mensagem1("Excluido com sucesso");
						Mensagem2("Exclusao finalizada");
					}
					else{
						Mensagem1("Operacao abortada");
						Mensagem2("Exclusao cancelada");
					}
				}
				else{
					Mensagem1("Autor nao encontrado");
					Mensagem2("Exclusao cancelada");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Exclusao cancelada");
			}
		}
		else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros");
			Mensagem2("Exclusao cancelada");
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Exclusao cancelada");
	}
	fclose(f_Pessoa);
	fclose(f_Emprestimo);
	fclose(f_Livro);
}
void Exclusao_Relacionamento(){	//COMPLETO
	int ID_Livro, ID_Autor, y;
	char op;
	_Relacao aux;
	FILE *f_Livro, *f_Autor, *f_Relacao;
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb");
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat", "rb");
	f_Relacao = fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb+");
	y = 7;
	if(Verifica_Presenca_Dados_Relacao(f_Relacao)){
		Texto_Display(y,"ID livro: ");
		y+=2;
		if(scanf("%d", &ID_Livro) == 1){
			if(ID_Livro / 100 > 0 && ID_Livro / 100 < 10){
				if(Busca_Livro(ID_Livro, f_Livro) != -1){
					Texto_Display(y,"ID autor: ");
					y+=2;
					if(scanf("%d", &ID_Autor) == 1){
						if(Busca_Autor(ID_Autor, f_Autor) != -1){
							Escolha_Excluir(y, op);
							if(op == 'S'){
								if(Busca_Livro_Autor_Relacionamento(ID_Livro, ID_Autor, f_Relacao) != -1){
									fseek(f_Relacao, -sizeof(_Relacao), 1);
									fread(&aux, sizeof(_Relacao), 1, f_Relacao);
									aux.Status = false;
									fseek(f_Relacao, -sizeof(_Relacao), 1);
									fwrite(&aux, sizeof(_Relacao), 1, f_Relacao);
									Mensagem1("Excluido com sucesso");
									Mensagem2("Exclusao finalizada");
								}
								else{
									Mensagem1("Relacao nao encontrada");
									Mensagem2("Exclusao cancelada");
								}
							}
							else{
								Mensagem1("Operacao abortada");
								Mensagem2("Exclusao cancelada");
							}
						}
						else{
							Mensagem1("Autor nao encontrado");
							Mensagem2("Exclusao cancelada");
						}
					}
					else{
						fflush(stdin);
						Mensagem1("Apenas numeros inteiros");
						Mensagem2("Exclusao cancelada");
					}
				}
				else{
					Mensagem1("Livro nao encontrado");
					Mensagem2("Exclusao cancelada");
				}
			}
			else{
				Mensagem1("ID de 3 digitos");
				Mensagem2("Exclusao cancelada");
			}
		}
		else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros");
			Mensagem2("Exclusao cancelada");
		}
	}
	else{
		Mensagem1("Nao ha dados cadastrados");
		Mensagem2("Exclusao cancelada");
	}
	fclose(f_Livro);
	fclose(f_Autor);
	fclose(f_Relacao);
}


//CADASTROS
void Insere_Autor(int ID, FILE *f){	//COMPLETO
	int i, j, flag = 0, QuantReg;
	_Autor aux, Le_Reg;
	aux.ID_Autor = ID;
	Texto_Display(9, "Nome: ");
	fflush(stdin);
	if(strlen(gets(aux.Nome_Autor)) <= 19 && strlen(aux.Nome_Autor) > 2){
		aux.Nome_Autor[0] = toupper(aux.Nome_Autor[0]);
		Texto_Display(11, "Nacionalidade: ");
		fflush(stdin);
		if(strlen(gets(aux.Nacionalidade)) <= 19 && strlen(aux.Nacionalidade) >= 2){
			aux.Nacionalidade[0] = toupper(aux.Nacionalidade[0]);
			aux.Status = true;
			fseek(f, 0, 2);
			QuantReg = ftell(f) / sizeof(_Autor);
			i = QuantReg;
			for(j = 0; j < QuantReg && flag == 0; j++){
				fseek(f, j * sizeof(_Autor), 0);
				fread(&Le_Reg, sizeof(_Autor), 1, f);
				if (aux.ID_Autor < Le_Reg.ID_Autor) {
					i = j;
					flag = 1;
				}
			}
			for(j = QuantReg; j > i; j--){
				fseek(f, (j - 1) * sizeof(_Autor), 0);
				fread(&Le_Reg, sizeof(_Autor), 1, f);
				fseek(f, j * sizeof(_Autor), 0);
				fwrite(&Le_Reg, sizeof(_Autor), 1, f);
			}
			fseek(f, i * sizeof(_Autor), 0);
			fwrite(&aux, sizeof(_Autor), 1, f);
			Mensagem1("Cadastro realizado com sucesso");
		}
		else{
			Mensagem1("Nacionalidade alem do tamanho");
			Mensagem2("Cadastro nao concluido");
		}
	}
	else{
		Mensagem1("Nome alem do tamanho permitido");
		Mensagem2("Cadastro nao concluido");
	}
}
void Insere_Emprestimo(int ID, FILE *f_Emprestimo, FILE *f_Livro, FILE *f_Pessoa){	//COMPLETO
	int i, j, flag = 0, QuantReg, Posicao_Livro;
	bool flag_Passou_Verificacao_Lancamento_Livro = false;
	_Emprestimo aux, Le_Reg;
	_Livro auxLivro;
	aux.ID_Emprestimo = ID;
	Texto_Display(9, "ID do Livro: ");
	scanf("%d", &ID);
	if(ID / 100 > 0 && ID / 100 < 10){
		if((Posicao_Livro = Busca_Livro(ID, f_Livro)) != -1){
			fseek(f_Livro, Posicao_Livro, 0);
			fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
			if(auxLivro.Status_Emprestado){
				aux.ID_Livro = ID;
				Texto_Display(11, "ID da Pessoa: ");
				scanf("%d", &ID);
				if(ID / 100 > 0 && ID / 100 < 10){
					if(Busca_Pessoa(ID, f_Pessoa) != -1){
						aux.ID_Pessoa = ID;
						Texto_Display(13, "Formato data: 'DD MM AAAA'");
						Texto_Display(15, "Data do emprestimo: ");
						for(i=0;i<3;){
							if(scanf("%d", &aux.Vet_Data_Emprestimo[i]) != 1){
								fflush(stdin);
								Mensagem1("Apenas numeros inteiros e espaco");
								Clear_Display();
								Texto_Display(7, "Data do emprestimo: ");
							}
							else{
								i++;
							}
						}
						if((aux.Vet_Data_Emprestimo[0] >= 1 && aux.Vet_Data_Emprestimo[0] <= 31) && (aux.Vet_Data_Emprestimo[1] >= 1 && aux.Vet_Data_Emprestimo[1] <= 12) && (aux.Vet_Data_Emprestimo[2] >= 1900 && aux.Vet_Data_Emprestimo[2] <= 2024)){
							fseek(f_Livro, Posicao_Livro, 0);
							fread(&auxLivro, sizeof(_Livro), 1, f_Livro);
							//VERIFICAÇÃO DATA DE LANÇAMENTO DO LIVRO
							if(aux.Vet_Data_Emprestimo[2] >= auxLivro.Vet_Ano_Livro[2]){
								if(aux.Vet_Data_Emprestimo[1] != auxLivro.Vet_Ano_Livro[1]){
									flag_Passou_Verificacao_Lancamento_Livro = true;
								}
								else if(aux.Vet_Data_Emprestimo[1] >= auxLivro.Vet_Ano_Livro[1]){
									if(aux.Vet_Data_Emprestimo[1] != auxLivro.Vet_Ano_Livro[1]){
										flag_Passou_Verificacao_Lancamento_Livro = true;
									}
									else if(aux.Vet_Data_Emprestimo[0] >= auxLivro.Vet_Ano_Livro[0]){
										flag_Passou_Verificacao_Lancamento_Livro = true;
									}
									else{
										Mensagem1("Emprestimo antes do lancamento livro");
										Mensagem2("Cadastro cancelado");
									}
								}
								else{
									Mensagem1("Emprestimo antes do lancamento livro");
									Mensagem2("Cadastro cancelado");
								}
							}
							else{
								Mensagem1("Emprestimo antes do lancamento livro");
								Mensagem2("Cadastro cancelado");
							}
							if(flag_Passou_Verificacao_Lancamento_Livro){
								Texto_Display(17, "Data da devolucao: ");
								for(i=0;i<3;){
									if(scanf("%d", &aux.Vet_Data_Devolucao[i]) != 1){
										fflush(stdin);
										Mensagem1("Apenas numeros inteiros e espaco");
										Clear_Display();
										Texto_Display(7, "Formato data: 'DD MM AAAA'");
										Texto_Display(9, "Data da devolucao: ");
									}
									else{
										i++;
									}
								}
								if((aux.Vet_Data_Devolucao[0] >= 1 && aux.Vet_Data_Devolucao[0] <= 31) && (aux.Vet_Data_Devolucao[1] >= 1 && aux.Vet_Data_Devolucao[1] <= 12) && (aux.Vet_Data_Devolucao[2] >= 1900 && aux.Vet_Data_Devolucao[2] <= 2024)){
									//VERIFICAÇÃO ANO
									if(Verifica_Data_Emprestimo(aux)){
										aux.Status = true;
										fseek(f_Emprestimo, 0, 2);
										QuantReg = ftell(f_Emprestimo) / sizeof(_Emprestimo);
										i = QuantReg;
										for(j = 0; j < QuantReg && flag == 0; j++){
											fseek(f_Emprestimo, j * sizeof(_Emprestimo), 0);
											fread(&Le_Reg, sizeof(_Emprestimo), 1, f_Emprestimo);
											if (aux.ID_Emprestimo < Le_Reg.ID_Emprestimo){
												i = j;
												flag = 1;
											}
										}
										for(j = QuantReg; j > i; j--) {
											fseek(f_Emprestimo, (j - 1) * sizeof(_Emprestimo), 0);
											fread(&Le_Reg, sizeof(_Emprestimo), 1, f_Emprestimo);
											fseek(f_Emprestimo, j * sizeof(_Emprestimo), 0);
											fwrite(&Le_Reg, sizeof(_Emprestimo), 1, f_Emprestimo);
										}
										fseek(f_Emprestimo, i * sizeof(_Emprestimo), 0);
										fwrite(&aux, sizeof(_Emprestimo), 1, f_Emprestimo);
										auxLivro.Status_Emprestado = false;
										fseek(f_Livro, Posicao_Livro, 0);
										fwrite(&auxLivro, sizeof(_Livro), 1, f_Livro);
										Mensagem1("Cadastro realizado com sucesso");
									}
								}
								else{
									Mensagem1("Datas invalidas, insira uma valida");
									Mensagem2("Cadastro nao concluido");
								}
							}
						}
						else{
							Mensagem1("Datas invalidas, insira uma valida");
							Mensagem2("Cadastro nao concluido");
						}
					}
					else{
						Mensagem1("Pessoa nao encontrada");
						Mensagem2("Cadastro nao concluido");
					}
				}
				else{
					Mensagem1("ID de 3 digitos");
					Mensagem2("Cadastro cancelado");
				}
			}
			else{
				Mensagem1("Ja emprestado a outra pessoa");
				Mensagem2("Cadastro nao concluido");
			}
		}
		else{
			Mensagem1("Livro nao encontrado");
			Mensagem2("Cadastro nao concluido");
		}
	}
	else{
		Mensagem1("ID de 3 digitos");
		Mensagem2("Cadastro cancelado");
	}
}
void Insere_Livro(int ID, FILE *f){	//COMPLETO
	int i, j, flag = 0, QuantReg;
	_Livro aux, Le_Reg;
	aux.ID_Livro = ID;
	Texto_Display(9, "Titulo: ");
	fflush(stdin);
	if(strlen(gets(aux.Titulo)) <= 19 && strlen(aux.Titulo) > 2){
		Texto_Display(11, "Formato data: 'DD MM AAAA'");
		Texto_Display(13, "Data: ");
		for(i=0;i<3;){
			if(scanf("%d", &aux.Vet_Ano_Livro[i]) != 1){
				fflush(stdin);
				Mensagem1("Apenas numeros inteiros e espaco");
				Clear_Display();
				Texto_Display(7, "Formato data: 'DD MM AAAA'");
				Texto_Display(9, "Data: ");
			}
			else{
				i++;
			}
		}
		if((aux.Vet_Ano_Livro[0] >= 1 && aux.Vet_Ano_Livro[0] <= 31) && (aux.Vet_Ano_Livro[1] >= 1 && aux.Vet_Ano_Livro[1] <= 12) && (aux.Vet_Ano_Livro[2] >= 1900 && aux.Vet_Ano_Livro[2] <= 2024)){
			aux.Status_Emprestado = true;
			aux.Status = true;
			fseek(f, 0, 2);
			QuantReg = ftell(f) / sizeof(_Livro);
			i = QuantReg;
			for(j = 0; j < QuantReg && flag == 0; j++){
				fseek(f, j * sizeof(_Livro), 0);
				fread(&Le_Reg, sizeof(_Livro), 1, f);
				if (aux.ID_Livro < Le_Reg.ID_Livro){
					i = j;
					flag = 1;
				}
			}
			for(j = QuantReg; j > i; j--) {
				fseek(f, (j - 1) * sizeof(_Livro), 0);
				fread(&Le_Reg, sizeof(_Livro), 1, f);
				fseek(f, j * sizeof(_Livro), 0);
				fwrite(&Le_Reg, sizeof(_Livro), 1, f);
			}
			fseek(f, i * sizeof(_Livro), 0);
			fwrite(&aux, sizeof(_Livro), 1, f);
			Mensagem1("Cadastro realizado com sucesso");
		}
		else{
			Mensagem1("Datas invalidas, insira uma valida");
			Mensagem2("Cadastro nao concluido");
		}
	}
	else{
		Mensagem1("Titulo alem do tamanho permitido");
		Mensagem2("Cadastro nao concluido");
	}
}
void Insere_Pessoa(int ID, FILE *f){	//COMPLETO
	int i, j, flag = 0, QuantReg;
	_Pessoa aux, Le_Reg;
	aux.ID_Pessoa = ID;
	Texto_Display(9,"Nome: ");
	fflush(stdin);
	if(strlen(gets(aux.Nome_Pessoa)) <= 19){
		aux.Nome_Pessoa[0] = toupper(aux.Nome_Pessoa[0]);
		Texto_Display(11, "Formato fone: +XX XXXXX-XXXX");
		Texto_Display(13, "Telefone: ");
		fflush(stdin);
		if(strlen(gets(aux.Telefone_Pessoa)) == 14){
			Texto_Display(15, "Formato endereco: Rua, Numero");
			Texto_Display(17, "Endereco: ");
			fflush(stdin);
			if(strlen(gets(aux.Endereco_Pessoa)) <= 29 && strlen(aux.Endereco_Pessoa) > 4){
				aux.Status = true;
				fseek(f, 0, 2);
				QuantReg = ftell(f) / sizeof(_Pessoa);
				i = QuantReg;
				for(j = 0; j < QuantReg && flag == 0; j++){
					fseek(f, j * sizeof(_Pessoa), 0);
					fread(&Le_Reg, sizeof(_Pessoa), 1, f);
					if (aux.ID_Pessoa < Le_Reg.ID_Pessoa) {
						i = j;
						flag = 1;
					}
				}
				for(j = QuantReg; j > i; j--){
					fseek(f, (j - 1) * sizeof(_Pessoa), 0);
					fread(&Le_Reg, sizeof(_Pessoa), 1, f);
					fseek(f, j * sizeof(_Pessoa), 0);
					fwrite(&Le_Reg, sizeof(_Pessoa), 1, f);
				}
				fseek(f, i * sizeof(_Pessoa), 0);
				fwrite(&aux, sizeof(_Pessoa), 1, f);
				Mensagem1("Cadastro realizado com sucesso");
			}
			else{
				Mensagem1("Endereco alem do tamanho permitido");
				Mensagem2("Cadastro nao concluido");
			}
		}
		else{
			Mensagem1("Fora do formato");
			Mensagem2("Cadastro nao concluido");
		}
	}
	else{
		Mensagem1("Nome alem do tamanho permitido");
		Mensagem2("Cadastro nao concluido");
	}
}
void Insere_Relacionamento(int ID_Livro, FILE *f_Relacao, FILE *f_Autor){	//COMPLETO
	char op = 'A';
	int i, j, flag = 0, QuantReg, ID_Autor, y = 9;
	_Relacao aux, Le_Reg;
	while(op != 27){
		if(op == 'A'){
			Texto_Display(y, "ID autor: ");
			fflush(stdin);
			if(scanf("%d", &ID_Autor) == 1){
				if(ID_Autor / 100 > 0 && ID_Autor / 100 < 10){
					Clear_Mensagem();
						if(Busca_Autor(ID_Autor, f_Autor) != -1){
							if(Busca_Livro_Autor_Relacionamento(ID_Livro, ID_Autor, f_Relacao) == -1){
								aux.ID_Livro = ID_Livro;
								aux.ID_Autor = ID_Autor;
								aux.Status = true;
								fseek(f_Relacao,0,2);
								QuantReg = ftell(f_Relacao) / sizeof(_Relacao);
								i = QuantReg;
								for(j = 0; j < QuantReg && flag == 0; j++){
									fseek(f_Relacao, j * sizeof(_Relacao), 0);
									fread(&Le_Reg, sizeof(_Relacao), 1, f_Relacao);
									if (aux.ID_Livro < Le_Reg.ID_Livro){
										i = j;
										flag = 1;
									}
								}
								for(j = QuantReg; j > i; j--) {
									fseek(f_Relacao, (j - 1) * sizeof(_Relacao), 0);
									fread(&Le_Reg, sizeof(_Relacao), 1, f_Relacao);
									fseek(f_Relacao, j * sizeof(_Relacao), 0);
									fwrite(&Le_Reg, sizeof(_Relacao), 1, f_Relacao);
								}
								fseek(f_Relacao, i * sizeof(_Relacao), 0);
								fwrite(&aux, sizeof(_Relacao), 1, f_Relacao);
								Mensagem1("Cadastro realizado com sucesso");
							}
							else{
								Mensagem1("Autor ja relacionado");
							}
						}
						else{
							fflush(stdin);
							Mensagem1("Autor nao encontrado");
						}
				}
				else{
					Mensagem1("ID de 3 digitos");
					Mensagem2("Cadastro cancelado");
				}
			}
			else{
			fflush(stdin);
			Mensagem1("Apenas numeros inteiros");
			}
		}
		else{
			Mensagem1("Escolha uma opcao valida");
		}
		if(op != 27){
			Clear_Display();
			Texto_Display(7, "[A] Autor do livro");
			Texto_Display(9, "[ESC] MENU CONSULTAS");
			op = toupper(getch());
			Clear_Display();
			Clear_Mensagem();
			y = 7;
		}
	}
}


//ORDENA??ES
void Ordenar_Autor(FILE *f){	//COMPLETO
	int a, b, Qnt_Reg;
	_Autor aux1, aux2;

	fseek(f,0,2);
	Qnt_Reg = ftell(f)/sizeof(_Autor);
	for(a=0; a<Qnt_Reg-1; a++){
		for(b=a+1; b<Qnt_Reg; b++)
		{
			fseek(f,a*sizeof(_Autor),0);
			fread(&aux1,sizeof(_Autor),1,f);
			
			fseek(f,b*sizeof(_Autor),0);
			fread(&aux2,sizeof(_Autor),1,f);
			
			if (aux1.ID_Autor > aux2.ID_Autor)
			{
				fseek(f,a*sizeof(_Autor),0);
				fwrite(&aux2,sizeof(_Autor),1,f);
				
				fseek(f,b*sizeof(_Autor),0);
				fwrite(&aux1,sizeof(_Autor),1,f);
			}
		}
	}
}
void Ordenar_Autor_Por_Nacionalidade(FILE *f){	//COMPLETO
	int a, b, Qnt_Reg;
	_Autor aux1, aux2;

	fseek(f,0,2);
	Qnt_Reg = ftell(f)/sizeof(_Autor);
	for(a=0; a<Qnt_Reg-1; a++){
		for(b=a+1; b<Qnt_Reg; b++)
		{
			fseek(f,a*sizeof(_Autor),0);
			fread(&aux1,sizeof(_Autor),1,f);
			
			fseek(f,b*sizeof(_Autor),0);
			fread(&aux2,sizeof(_Autor),1,f);
			
			if(stricmp(aux1.Nacionalidade, aux2.Nacionalidade) > 0){
				fseek(f,a*sizeof(_Autor),0);
				fwrite(&aux2,sizeof(_Autor),1,f);
				
				fseek(f,b*sizeof(_Autor),0);
				fwrite(&aux1,sizeof(_Autor),1,f);
			}
		}
	}
}
void Ordenar_Emprestimo(FILE *f){	//COMPLETO
	int a, b, Qnt_Reg;
	_Emprestimo aux1, aux2;

	fseek(f,0,2);
	Qnt_Reg = ftell(f)/sizeof(_Emprestimo);
	for(a=0; a<Qnt_Reg-1; a++){
		for(b=a+1; b<Qnt_Reg; b++)
		{
			fseek(f,a*sizeof(_Emprestimo),0);
			fread(&aux1,sizeof(_Emprestimo),1,f);
			
			fseek(f,b*sizeof(_Emprestimo),0);
			fread(&aux2,sizeof(_Emprestimo),1,f);
			
			if (aux1.ID_Emprestimo > aux2.ID_Emprestimo)
			{
				fseek(f,a*sizeof(_Emprestimo),0);
				fwrite(&aux2,sizeof(_Emprestimo),1,f);
				
				fseek(f,b*sizeof(_Emprestimo),0);
				fwrite(&aux1,sizeof(_Emprestimo),1,f);
			}
		}
	}
}
void Ordenar_Livro(FILE *f){	//COMPLETO
	int a, b, Qnt_Reg;
	_Livro aux1, aux2;

	fseek(f,0,2);
	Qnt_Reg = ftell(f)/sizeof(_Livro);
	for(a=0; a<Qnt_Reg-1; a++){
		for(b=a+1; b<Qnt_Reg; b++)
		{
			fseek(f,a*sizeof(_Livro),0);
			fread(&aux1,sizeof(_Livro),1,f);
			
			fseek(f,b*sizeof(_Livro),0);
			fread(&aux2,sizeof(_Livro),1,f);
			
			if (aux1.ID_Livro > aux2.ID_Livro)
			{
				fseek(f,a*sizeof(_Livro),0);
				fwrite(&aux2,sizeof(_Livro),1,f);
				
				fseek(f,b*sizeof(_Livro),0);
				fwrite(&aux1,sizeof(_Livro),1,f);
			}
		}
	}
}
void Ordenar_Livros_Por_Data(FILE *f){
	int a, b, Qnt_Reg;
	_Livro aux1, aux2;

	fseek(f,0,2);
	Qnt_Reg = ftell(f)/sizeof(_Livro);
	for(a=0; a<Qnt_Reg-1; a++){
		for(b=a+1; b<Qnt_Reg; b++)
		{
			fseek(f,a*sizeof(_Livro),0);
			fread(&aux1,sizeof(_Livro),1,f);
			
			fseek(f,b*sizeof(_Livro),0);
			fread(&aux2,sizeof(_Livro),1,f);
			
			if (aux1.Vet_Ano_Livro[2] > aux2.Vet_Ano_Livro[2])
			{
				Clear_Mensagem();
				fseek(f,a*sizeof(_Livro),0);
				fwrite(&aux2,sizeof(_Livro),1,f);
				
				fseek(f,b*sizeof(_Livro),0);
				fwrite(&aux1,sizeof(_Livro),1,f);
			}
		}
	}
}
void Ordenar_Pessoa(FILE *f){	//COMPLETO
	int a, b, Qnt_Reg;
	_Pessoa aux1, aux2;

	fseek(f,0,2);
	Qnt_Reg = ftell(f)/sizeof(_Pessoa);
	for(a=0; a<Qnt_Reg-1; a++){
		for(b=a+1; b<Qnt_Reg; b++)
		{
			fseek(f,a*sizeof(_Pessoa),0);
			fread(&aux1,sizeof(_Pessoa),1,f);
			
			fseek(f,b*sizeof(_Pessoa),0);
			fread(&aux2,sizeof(_Pessoa),1,f);
			
			if (aux1.ID_Pessoa > aux2.ID_Pessoa)
			{
				fseek(f,a*sizeof(_Pessoa),0);
				fwrite(&aux2,sizeof(_Pessoa),1,f);
				
				fseek(f,b*sizeof(_Pessoa),0);
				fwrite(&aux1,sizeof(_Pessoa),1,f);
			}
		}
	}
}
void Ordenar_Relacao(FILE *f){	//COMPLETO
	int a, b, Qnt_Reg;
	_Relacao aux1, aux2;

	fseek(f,0,2);
	Qnt_Reg = ftell(f)/sizeof(_Relacao);
	for(a=0; a<Qnt_Reg-1; a++){
		for(b=a+1; b<Qnt_Reg; b++)
		{
			fseek(f,a*sizeof(_Relacao),0);
			fread(&aux1,sizeof(_Relacao),1,f);
			
			fseek(f,b*sizeof(_Relacao),0);
			fread(&aux2,sizeof(_Relacao),1,f);
			
			if (aux1.ID_Livro > aux2.ID_Livro)
			{
				fseek(f,a*sizeof(_Relacao),0);
				fwrite(&aux2,sizeof(_Relacao),1,f);
				
				fseek(f,b*sizeof(_Relacao),0);
				fwrite(&aux1,sizeof(_Relacao),1,f);
			}
		}
	}
}


//VERIFICACOES
bool Verifica_Presenca_Dados_Autor(FILE *f){	//COMPLETO
    _Autor aux;
    rewind(f);
    while(fread(&aux, sizeof(_Autor), 1, f) == 1){
        if(aux.Status){
            return true;
        }
    }
    return false;
}
bool Verifica_Presenca_Dados_Emprestimo(FILE *f){	//COMPLETO
    _Emprestimo aux;
    rewind(f);
    while(fread(&aux, sizeof(_Emprestimo), 1, f) == 1){
        if(aux.Status){
            return true;
        }
    }
    return false;
}
bool Verifica_Presenca_Dados_Livro(FILE *f){	//COMPLETO
    _Livro aux;
    rewind(f);
    while(fread(&aux, sizeof(_Livro), 1, f) == 1){
        if(aux.Status){
            return true;
        }
    }
    return false;
}
bool Verifica_Presenca_Dados_Pessoa(FILE *f){	//COMPLETO
    _Pessoa aux;
    rewind(f);
    while(fread(&aux, sizeof(_Pessoa), 1, f) == 1){
        if(aux.Status){
            return true;
        }
    }
    return false;
}
bool Verifica_Presenca_Dados_Relacao(FILE *f){	//COMPLETO
    _Relacao aux;
    rewind(f);
    while(fread(&aux, sizeof(_Relacao), 1, f) == 1){
        if(aux.Status){
            return true;
        }
    }
    return false;
}
bool Verifica_Data_Emprestimo(_Emprestimo Emprestimo){	//COMPLETO
		//VERIFICAÇÃO ANO
	if(Emprestimo.Vet_Data_Emprestimo[2] < Emprestimo.Vet_Data_Devolucao[2]){
		return true; //TRUE = PODE FAZER A INSERCAO
	}
	//VERIFICAÇÃO ANO
	else if(Emprestimo.Vet_Data_Emprestimo[2] == Emprestimo.Vet_Data_Devolucao[2]){
		//VERIFICAÇÃO MES
		if(Emprestimo.Vet_Data_Emprestimo[1] < Emprestimo.Vet_Data_Devolucao[1]){
			return true;
		}	//VERIFICAÇÃO MES
		else if(Emprestimo.Vet_Data_Emprestimo[1] == Emprestimo.Vet_Data_Devolucao[1]){
			//VERIFICAÇÃO DIA
			if(Emprestimo.Vet_Data_Emprestimo[0] < Emprestimo.Vet_Data_Devolucao[0]){
				return true;
			}
			else if(Emprestimo.Vet_Data_Emprestimo[0] == Emprestimo.Vet_Data_Devolucao[0]){
				Mensagem1("Devolucao com apenas 1 dia de '!='");
				Mensagem2("Cadastro cancelado");
				return false;
			}
			else{
				Mensagem1("Emprestimo depois da devolucao");
				Mensagem2("Cadastro cancelado");
				return false;
			}
		}
		else{
			Mensagem1("Emprestimo depois da devolucao");
			Mensagem2("Cadastro cancelado");
			return false;
		}

	}
	else{
		Mensagem1("Emprestimo depois da devolucao");
		Mensagem2("Cadastro cancelado");
		return false;
	}
}
bool Verifica_Todos_Dados(){	//COMPLETO
	FILE *f_Autor, *f_Emprestimo, *f_Livro, *f_Pessoa, *f_Relacao;
	f_Autor = fopen("arquivos.dat/Autores_Cadastrados.dat", "rb");
	f_Emprestimo = fopen("arquivos.dat/Emprestimos_Cadastrados.dat", "rb");
	f_Livro = fopen("arquivos.dat/Livros_Cadastrados.dat", "rb");
	f_Pessoa = fopen("arquivos.dat/Pessoas_Cadastradas.dat", "rb");
	f_Relacao =  fopen("arquivos.dat/Relacao_Cadastrados.dat", "rb");
	if(Verifica_Presenca_Dados_Autor(f_Autor) && Verifica_Presenca_Dados_Emprestimo(f_Emprestimo) && Verifica_Presenca_Dados_Livro(f_Livro) && Verifica_Presenca_Dados_Pessoa(f_Pessoa) && Verifica_Presenca_Dados_Relacao(f_Relacao)){
		return true;
	}
	else{
		return false;
	}
	fclose(f_Autor);
	fclose(f_Emprestimo);
	fclose(f_Livro);
	fclose(f_Pessoa);
	fclose(f_Relacao);
}
