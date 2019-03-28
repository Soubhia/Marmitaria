/*	Trabalho FPD - Marmitaria Saí de Casa 
	2016 - Informatica 71A
	leonardo Dias Vono Fernandes n°18
	Yasmin G. Miranda da Cunha n°35
	Victor Rodrigues Russo n°32
	Carlos A. P. M. Soubhia nº04  
	
	senha do gerente: admin
*/
#include<stdio.h>                
#include<string.h>
#include <conio.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>
#include <unistd.h>
#include <locale.h>
#include <stdlib.h>
#include<time.h>
//************************
FILE *fclientes;
FILE *fpratos;
//************************
int main()
{	
	void tela_inicial(int,int,int,int);
	void menu_principal();
	void carregamento();
	
	//abrindo os arquivos para ver se nao estão com nenhum erro
	if((fclientes=fopen("clientes.bin","ab")) == 0) //aberto no modo "ab" pois no "wb" é excluido oq já esta no arquivo e no "rb" ele teria que existir
	{
		printf ("Erro na Abertura do arquivo do cliente");
		exit (1);
	}
	fclose (fclientes);
	
	if((fpratos=fopen("pratos.bin","ab"))==0)
	{
		printf ("Erro na Abertura do arquivo do prato");
		exit (1);
	}
	fclose (fpratos);
	
	tela_inicial(3,26,5,80); //tela que fica parada com o logotipo da marmitaria e informações de contato
	carregamento(); //carregamento criado apenas para distração
	menu_principal(); //menu com: inclusão, consulta, alteração, sobre, etc.
}
//************************
void menu_principal()
{
	
	void HideCursor(int);
	void tela_inicial(int,int,int,int);
	void tela_menu(int,int);
	void tela(int);
	int cursor(int,int,int,int); 
	void inclusao();
	void consulta ();
	void alteracao();
	void exclusao();
	void sobre();
	void encerrar();
	
	HideCursor(0); //tirando o cursor da tela
	int opcao; // opcao selecionada entre o menu (ex: inclusao, consulta, sobre). Ela é igual a linha onde esta localizada a escolha
	do
	{
		tela(1); //limpa a tela, coloca bordas. 1 = desenho de garfo e faca
		tela_menu(13,10);  //mostrando dados na tela do menu inicial 
		opcao = cursor(12,10,6,1);	//setas para escolha. Enviando a coluna, a linha, qtd de opcoes e qual tela mostrara 
		switch (opcao) //começa do 10 pois é a linha inicial (depois aumenta de 2 em 2)
		{
			case 10: inclusao (); 
					 break;
			case 12: consulta();
					 break;
			case 14: alteracao();
					 break;
			case 16: exclusao ();
					 break; 
			case 18: sobre();
					 break; 
			case 20: encerrar();	
					 break;	 
		}
	}while (true); //repete sem parar
}
//************************
struct CLIENTES
{
	int chave;
	char nome[25];
	char cartao; //sim ou nao        
	char cel_1 [2];
	char cel_2 [10];
	char tel_1 [2];
	char tel_2 [10];      
	struct end_do_cliente
	{
		char rua[50];
		char numero[5];
		char cep_1[5];
		char cep_2[4];
		char complemento[3];
	}endereco;
	int prato_preferido;
	struct nascimento
	{
		char dia[2];
		char mes[2];
		char ano[5];
	}data;
	int exclusao;
} cliente;
//***************************
struct PRATOS
{
	int chave;
	char nome[15];
	char ingredientes[40];
	char preco1[3]; //numeros antes da virgula
	char preco2[3]; //numeros depois da virgula
	char cal[5];
	int exclusao;
}prato;
//***************************
void HideCursor(int mostra=0)
{
	CONSOLE_CURSOR_INFO cursor;
	if(mostra == 1)
		cursor = {20, TRUE,};
	else
		cursor = {20, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
//***********************************
#ifdef __cplusplus
extern "C" {
#endif

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 25, 80, 1, 1};
void textcolor(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}
//********************************
void textbackground(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}
//***************************
#ifdef __cplusplus
}
#endif
void gotoxy(int x, int y)
{
   COORD c;
   c.X=x-1;
   c.Y=y-1;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//***************************
void borda(int li, int lf, int ci, int cf)  //recebendo: linha inicial, linha final, coluna inicial, coluna final 
{
	setlocale(LC_ALL,"C"); 
	textbackground (14); //amarelo claro
	textcolor (BLACK);
	gotoxy (ci+1, li+1); printf ("                          MARMITARIA SAI D'CASA                           ");
	textbackground (15);
	textcolor(4);
	for (int i=li; i<=lf;i++)    //imprimindo coluna inicial
	{
		gotoxy (ci,i); printf("%c",186);
	}
	for (int i=li;i<=lf;i++)    //imprimindo   coluna final
	{ 
		gotoxy (cf,i);printf ("%c",186);
	}
	for (int i = ci+1 ; i < cf ; i++)
	{
		gotoxy (i, li); printf ("%c",205);   //imprimindo linha inicial e titulo
		gotoxy (i, li+2); printf ("%c",205);
	}
	for (int i = ci+1 ; i < cf ;i++ )
	{
		gotoxy (i ,lf); printf ("%c",205); //imprimindo linha final   
	}
	gotoxy (cf,li) ; printf ("%c", 187);     //colocando cantos 
	gotoxy (cf,lf) ; printf ("%c", 188);
	gotoxy (ci,li) ; printf ("%c", 201);
	gotoxy (ci,lf) ; printf ("%c", 200); 
	gotoxy (cf, li+2) ; printf ("%c", 185);
	gotoxy (ci, li+2) ; printf ("%c", 204); 
	
	textcolor (BLACK);
	setlocale (LC_ALL,"Portuguese");
	
}
//***************************
void pepsi (int c, int li)
{
	setlocale (LC_ALL,"C");
	
	
	textbackground(RED);
	gotoxy (c+5, li+4);printf("%c            %c",219,219);
	gotoxy (c+2, li+5);printf("%c                  %c",219,219);
	gotoxy (c+1, li+6);printf("%c                    %c",219,219);
	gotoxy (c, li+7);printf("%c                      %c",219,219);
	textbackground(15);
	textcolor (BLUE);
	gotoxy (c+3, li+8);printf("  _   _  _   (_'  |   ");
	gotoxy (c+3, li+9);printf(" |_) |_  |_) ._)  |   ");
	gotoxy (c+3, li+10);printf(" |   |_  |            ");
	textcolor (BLACK);
	textbackground(1);
	gotoxy (c, li+11);printf("%c                      %c",219,219);
	gotoxy (c+1, li+12);printf("%c                    %c",219,219);
	gotoxy (c+2, li+13);printf("%c                  %c",219,219);
	gotoxy (c+5, li+14);printf("%c            %c",219,219);
	textbackground(15);
	textcolor(BLACK);
	gotoxy (c+5,li+3);printf ("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",220,220,220,220,220,220,220,220,220,220,220,220,220,220);
	gotoxy (c+5,li+15);printf ("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",223,223,223,223,223,223,223,223,223,223,223,223,223,223);
	gotoxy (c,li+8);printf ("%c",219);
	gotoxy (c,li+9);printf ("%c",219);
	gotoxy (c,li+10);printf ("%c",219);
	gotoxy (c+23,li+8);printf ("%c",219);
	gotoxy (c+23,li+9);printf ("%c",219);
	gotoxy (c+23,li+10);printf ("%c",219);
	setlocale (LC_ALL,"Portuguese");
}
//***************************
void desenho (int c, int li)  //desenhando garfo e faca //recebendo a coluna e a linha do desenho
{
	setlocale (LC_ALL,"C");
	textcolor (8); //cinza
	textbackground(15);	//branco
	// desenhando um garfo:
	gotoxy (c, li);printf("%c  %c  %c  %c",219,219,219,219);	
	gotoxy (c, li+1);printf("%c  %c  %c  %c",219,219,219,219);			
	gotoxy (c, li+2);printf("%c  %c  %c  %c",219,219,219,219);
	gotoxy (c, li+3);printf("%c  %c  %c  %c",219,219,219,219);
    gotoxy (c, li+4);printf("%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219);    
	gotoxy (c+1, li+5);printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
	gotoxy (c+2, li+6);printf("%c%c%c%c%c%c",219,219,219,219,219,219);  
	gotoxy (c+3, li+7);printf("%c%c%c%c",219,219,219,219);   
	c+=4;
    gotoxy (c, li+8);printf("%c%c",219,219);	    
    gotoxy (c, li+9);printf("%c%c",219,219);        
	gotoxy (c, li+10);printf("%c%c",219,219);    
	gotoxy (c, li+11);printf("%c%c",219,219);    
	gotoxy (c, li+12);printf("%c%c",219,219);    
	gotoxy (c, li+13);printf("%c%c",219,219);    
	gotoxy (c, li+14);printf("%c%c",219,219);    
	gotoxy (c, li+15);printf("%c%c",219,219);    
	gotoxy (c, li+16);printf("%c%c",219,219);    
	gotoxy (c, li+17);printf("%c%c",219,219);
	//desenhando uma faca:
	c=47;	
	gotoxy (c, li  );printf ("%c",219);
	gotoxy (c, li+1);printf ("%c%c",219,219);		
	gotoxy (c, li+2);printf ("%c%c%c",219,219,219);		
	gotoxy (c, li+3);printf ("%c%c%c%c",219,219,219,219);		
	gotoxy (c, li+4);printf ("%c%c%c%c%c",219,219,219,219,219);		
	gotoxy (c, li+5);printf ("%c%c%c%c%c%c",219,219,219,219,219,219);		
	gotoxy (c, li+6);printf ("%c%c%c%c%c",219,219,219,219,219);		
	gotoxy (c, li+7);printf ("%c%c%c%c",219,219,219,219);	
			
	for (int i=8;i<18;i++)
	{
		gotoxy (c, li+i);printf ("%c%c%c",219,219,219);
	}		

}
//***************************
void carregamento()	 //carregamento criado apos a tela inicial	
{
	void tela (int);
	tela(0);
	gotoxy(39,11);printf("LOADING...");
	setlocale(LC_ALL,"C");
	gotoxy (32,18);
	srand(time(NULL));
	int sorteio; 
	for(int i=0; i<45; i++)
	{
		sorteio = rand ()%80;
		if (i%2 == 0)
			textcolor (4); //vermelho
		else 
			textcolor (0); //preto
		gotoxy(i+20,15);printf("%c",219);
		gotoxy(i+20,16);printf("%c",219);
		Sleep (sorteio);
	}
}
//***************************
char consist_sn(int x, int y)
{
	HideCursor(1); //colocando o cursor da tela
	int i=0;
	char op;
	gotoxy(x,y); printf("(n/s): ");
	op=getchar();
	fflush (stdin);
	do
	{
	if(op != 's' && op != 'S' && op != 'n' && op != 'N')
	{
		gotoxy(x,y);
		for(int j=0;j<38;j++)
			printf(" ");
		gotoxy(x,y);printf("Inválido! Redigite: ");
		op=getchar();
	fflush (stdin);
	}
	else
		i=1;
	}while(i!=1);
	return op;
}
//***************************
void anulando (int ci, int li)  //falta colocar os gotoxy (x,y) e alterar cores
{
	setlocale(LC_ALL, "C");
	textcolor(RED);
	for(int i=li; i<(li+8); i++)
	{
		for(int j=ci; j<(ci+14); j++)
		{
			gotoxy(j,i); printf("%c", 219);
		}	
	}
	textbackground (RED);
	textcolor(WHITE); 
	ci+=3;
	gotoxy (ci,li+1); printf("__"); gotoxy(ci+6, li+1); printf("__");
	gotoxy (ci,li+2); printf("\\ \\"); gotoxy(ci+5,li+2); printf("/ /"); 	//mudar a cor da letra pra preto e o fundo interior pra vermelho
 	gotoxy (ci+1,li+3); printf("\\ \\/ /");
  	gotoxy (ci+2,li+4); printf("}  {");
 	gotoxy (ci+1,li+5); printf("/ /\\ \\");
	gotoxy (ci,li+6); printf("/_/"); gotoxy(ci+5, li+6); printf("\\_\\");
    textbackground (WHITE);
}	
//***************************
void coca(int ci, int li)
{
	textcolor(12);	
	textbackground(12);
	gotoxy(ci+2,li);printf("ttttttt");
	gotoxy(ci+2,li+1);printf("ttttttt");
	textcolor(BLACK);
	textbackground(BLACK);
	gotoxy(ci+3,li+2);printf("aaaaa");
	gotoxy(ci+3,li+3);printf("aaaaa");
	gotoxy(ci+2,li+4);printf("aaaaaaa");
	gotoxy(ci+1,li+5);printf("aaaaaaaaa");
	gotoxy(ci,li+6);printf("aaaaaaaaaaa");
	textcolor(12);	
	textbackground(12);
	gotoxy(ci,li+7);printf("ttttttttttt");
	gotoxy(ci,li+8);printf("ttttttttttt");
	gotoxy(ci,li+9);printf("ttttttttttt");
	gotoxy(ci,li+10);printf("ttttttttttt");
	textcolor(BLACK);	
	textbackground(BLACK);
	gotoxy(ci,li+11);printf("aaaaaaaaaaa");
	gotoxy(ci,li+12);printf("aaaaaaaaaaa");
	gotoxy(ci+1,li+13);printf("aaaaaaaaa");
	gotoxy(ci+1,li+14);printf("aaaaaaaaa");
	gotoxy(ci,li+15);printf("aaaaaaaaaaa");
	gotoxy(ci,li+16);printf("aaaaaaaaaaa");
	gotoxy(ci,li+17);printf("aaaaaaaaaaa");
	gotoxy(ci,li+18);printf("aa  aaa  aa");
	textcolor(WHITE);	
	textbackground(12);
	gotoxy(ci+1,li+8);printf("Coca-cola");
    textbackground(WHITE);
}
//*********************************************
void hamburguer(int ci,int li) 
{
	for(int a=ci;a<=(ci+14);a++)
	{
		for(int b=li ; b<=(li+2);b++)
		{
			textbackground(6);
			gotoxy(a,b);printf(" ");
			gotoxy(a,b+7);printf(" ");
		}
	}
	for(int c=(ci-1);c<=(ci+15);c++)
	{
		textbackground(10);
		gotoxy(c,li+3);printf(" ");
		textbackground(12);
		gotoxy(c,li+4);printf(" ");
		textbackground(16);
		gotoxy(c,li+6);printf(" ");
		textbackground(14);
		gotoxy(c,li+5);printf(" ");
	}
	textbackground(WHITE);
	gotoxy(ci,li);printf(" ");
	gotoxy(ci,li+9);printf(" ");
	gotoxy(ci+14,li);printf(" ");
	gotoxy(ci+14,li+9);printf(" ");
}
//***************************
void ferramentas (int ci, int li)
{
	textcolor (8);
	//alicate
	gotoxy(ci+27,li+4); printf("___");
	gotoxy(ci+15,li+5); printf("_  _...--'''   ``-._");
	gotoxy(ci+14,li+6); printf("/\\`                 `._");
	gotoxy(ci+1,li+7); printf("__..--''\\___/  \\     _.-'```''-._   `;");
	gotoxy(ci,li+8); printf("/       .'       \\_.-'            ````");
	gotoxy(ci-1,li+9); printf("|_.-.___|  .-.   .'~");
	gotoxy(ci-1,li+10); printf("| `-'      `-'  ;`._");
	gotoxy(ci,li+11); printf("\\__       ___.'  //`-._          _,,,");
	gotoxy(ci+2,li+12); printf("``--../   \\  //     `-.,,,..-'    `;");
	gotoxy(ci+13,li+13); printf("\\//,_               _.-'");
	gotoxy(ci+17,li+14); printf("```--...___..-'");
	
	//chave
	gotoxy(ci+1,li);printf("_.---.                     .---.");				
	gotoxy(ci,li+1);      printf("'---,  `._________________.'  _  `.");
	gotoxy(ci+5,li+2);      printf(")   _________________   <_>  :");
	gotoxy(ci,li+3);      printf(".---'  .'                 `.     .'");
	gotoxy(ci,li+4);      printf("``----'                     `---'");
	textcolor (BLACK);	
}
//*********************************
void pc(int ci, int li)
{
	setlocale (LC_ALL, "C");
	textbackground (BLACK);
	textcolor (WHITE);
	//tela:
	for (int i=3; i<=11;i++)
	{
		gotoxy(ci+5, li+i);  printf("                                 "); 
	}              
    gotoxy(ci+5, li+12); printf("\\_______________________________/");    
	gotoxy (ci+5,li+3); printf ("%c", 223);
	gotoxy (ci+37,li+3); printf ("%c", 223);
	//teclado:
	textbackground(BLACK);
	gotoxy(ci+4, li+13); printf(",----------------------------------,"); 
	gotoxy(ci+4, li+14); printf("|  [][][][][][][][][][][][_]  [][] |"); 
	gotoxy(ci+4, li+15); printf("|  [_][][][][][][][][][][][]  [][] |"); 
	gotoxy(ci+4, li+16); printf("| [][_][][][][][][][][][][]   [][] |"); 
	gotoxy(ci+4, li+17); printf("| [__][][][][][][][][][][__]  [][] |"); 
	gotoxy(ci+4, li+18); printf("|   [__][________________][__]     |"); 
	gotoxy(ci+4, li+19); printf("`----------------------------------'");
	
	textcolor (GREEN);
	//tela verde:
	for (int i=4;i<=11;i++)
	{
		for (int j=8;j<35;j++)
		{
			gotoxy (ci+j,li+i); printf ("%c", 219);

		}
	}
	
	textbackground(GREEN);textcolor (WHITE);gotoxy (ci+12,li+5); printf("C:\> Exclusão_Pesto");
	textbackground(WHITE);
	setlocale (LC_ALL, "Portuguese");
	textcolor (BLACK);
	

}
//**************************
void tela(int desenhar)
{
	system("cls");
	system ("color F0"); //cor de fundo branco
	borda (3,26,5,80); //80 após o 5
	if (desenhar==1)
		desenho (58,7);
	else if (desenhar == 2)
		pepsi (50,7);
	else if (desenhar == 3)
		pc (37,6);
	else if(desenhar == 4)
		coca (60,6);
	else if(desenhar == 5)	
		hamburguer(55,13);
	else if(desenhar == 6)	
		anulando (60,11);
	else if (desenhar == 7)
	    ferramentas (40,10);
}
//******************************
void encerrar()
{
	HideCursor(1); //colocando o cursor da tela
	void gotoxy(int,int);
	char fim=0;
	gotoxy(6,22); printf("Você deseja mesmo encerrar o programa?"); 
	fflush(stdin);
	fim=consist_sn(6,23);
	if(fim=='S' || fim=='s')
	{
		tela(0);
		gotoxy(15,15); printf("Obrigado por utilizar nosso programa...Volte sempre!");
	}
	else
	{
		return;
	}
	gotoxy(1,27);
	exit(0);
}
//***************************
int tabela_pratos (int li, int ci, int cf, int prato_preferido, int alt=0) //se prato_preferido, faz a pergunta do prato
{
	int pega2(int, char [9]);
	void alteracao_prato();
	void alteracao();
	int pega_alt(int, char [40], int = 0);
	int pega2_alt(int, char [9]);
	setlocale (LC_ALL,"Portuguese");
	int tam=1;
	HideCursor (0); //tirando o cursor da tela
	
	fpratos=fopen("pratos.bin","rb+"); //nao estava funcionando vendo por NULL
	do		//contando quantos pratos existem cadastrados
	{
		fread(&prato, sizeof(prato),1,fpratos);
		if (prato.exclusao != 1)
			tam++;
	}while(!feof (fpratos));
	tam-=2;
	if(tam == 0)  //nenhum prato cadastrado
	{
		gotoxy(28,12); printf("Não há pratos disponíveis\n");
		gotoxy(22,24); system("pause");
		return 0;
	}	

	rewind (fpratos);
	int cont=0, //quando cont=tam (tamanho do arquivo), para de mostrar pratos na tela
		num=0; //num vai indicar quantas telas de prato ja foi mostrada
		    
	li+=1;
	int posicao; //posicao é usada na alteracao e determina onde ficara a seta 
	int lp = li; //lp é a linha em que começa a mostrar os pratos
	do
	{
		tela(0);
		setlocale (LC_ALL,"Portuguese");
		gotoxy (35,7); printf ("TABELA DE PRATOS");		
		gotoxy (ci+1,9); printf ("Nº");			//colocando titulos da tabela
		gotoxy (ci+7,9); printf ("Nome");
		gotoxy (ci+34,9); printf ("Ingredientes");
		gotoxy (cf-4,9); printf ("kcal");
		gotoxy (cf-11,9); printf ("Preço");
			
		num++;
		li = lp;
        do
        {
			fread(&prato,sizeof(prato),1,fpratos);
			if(prato.exclusao!=1)
			{
				gotoxy (ci+1,li); printf ("%d",prato.chave);			//imprimindo sobre o prato
				gotoxy (ci+4,li); printf ("%s",prato.nome);
				gotoxy (ci+20,li); printf ("%s",prato.ingredientes);
				gotoxy (cf-11,li); printf ("%s,%s",prato.preco1, prato.preco2);
				gotoxy (cf-4,li); puts(prato.cal);
				li++;
				cont++;
			}
			
		} while (cont!=tam && li < 21); //repetir enquanto ainda tiver prato E ainda nao tenha imprimido 10 pratos
		
		textcolor (12); 
		setlocale (LC_ALL, "C");
		if (alt == 0)
		{
			gotoxy (7,25); printf ("%c%c", 174, 205); //imprimindo seta pra esquerda <<
			gotoxy (77,25); printf ("%c%c",205, 175); //imprimindo seta pra direita >>
		}		
		else 
		{
			textcolor (8); gotoxy (7,24); printf ("ESC para sair"); textcolor (4);
			gotoxy (77,24); printf ("/\\"); //imprimindo seta pra cima ^
			gotoxy (77,25); printf ("\\/"); //imprimindo seta pra baixo (sem símbolo)
		}
		textcolor (BLACK);
		li-=11;	
			
		fflush (stdin);
		char dig;
		if (alt == 0) //alt vale 0 quando nao está em alteração
		{
			do 
			{
				fflush (stdin);
				gotoxy (1,1);dig = getch();
				if(dig == 27)
				{
					return 0;
				}
				else if(dig == 75) //seta pra esquerda (voltar tabela)
				{
					if (num == 1) //se tiver na primeira tela e a pessoa voltar
					{
						if  (prato_preferido == 1 ) //laço de repetição deve continar
							dig = '0';
						 
						else
							return 0; //pessoa volta pra funcao anterior	 
					}
					else
					{
						rewind (fpratos);   //colocando ponteiro no inicio do arquivo
						for (int i=0;i<(10*(num-2)) ;i++)	//lendo o tanto necessario 
							fread(&prato,sizeof(prato),1,fpratos);
						cont = num*10 - 20;
						num-=2;
					}
						
				}	
			} while (dig != 75 && dig != 77); //enquanto nao for digitado nem seta pra esquerda nem pra direita
		}
		else if(dig == 27) //se digitado esc, volta
				return 0;
			
		else
		{
			HideCursor (0); //tirando o cursor da tela
			int lf = lp+cont-10*(num-1)-1; //linha final onde esta o ultimo prato
				
			if (posicao == 0) //posicao é a linha onde o cursor devera ser posicionado, lp é a linha onde começou a mostrar os pratos
				posicao = lf;
			else
				posicao = lp; 
					
			do 
			{
				gotoxy (ci,posicao); printf ("%c", 175);
				fflush (stdin);
				dig = getch();
				if(dig == 27) //se digitado esc, volta
					return 0;
				
				else if (dig == 72 && posicao == lp && cont>10) //se digitado seta pra cima, e estiver no inicio da linha e ja tiver mostrado os pratos inicias
				{
					rewind (fpratos);   //colocando ponteiro no inicio do arquivo
					for (int i=0;i<(10*(num-2)) ;i++)	//lendo o tanto necessario 
						fread(&prato,sizeof(prato),1,fpratos);
					cont = num*10 - 20;
					num-=2;
					posicao = 0; //posicao = 0 indica que tem que iniciar na linha final o seta
					break;
				}
				
				else if (dig == 80 && posicao == lf && cont !=tam) //se digitado seta pra baixo no ultimo prato e ainda nao estiver no final
				{
					break; //saia do laço de repetição e continue a mostrar os pratos
				}
					
				else if(dig == 72 && posicao>11) //seta pra cima
				{
					gotoxy (ci,posicao);printf (" "); //apagando flecha
					gotoxy (ci, --posicao); printf ("%c", 175);
				}
					
				else if (dig == 80 && posicao < lf) //Se digitado seta para baixo E posicao for menor que a ultima linha 
				{
					gotoxy (ci,posicao);printf (" "); //apagando flecha
					gotoxy (ci, ++posicao); printf ("%c", 175);
				}
					
			} while (dig != '\r'); //enquanto nao for digitado enter OU for digitado para baixo e precisar mudar de tela
		
			if (dig == '\r') //se a pessoa digitou enter, ela alterara o prato
			{
				HideCursor(1); //mostrando o cursor da tela
				int codigo_prato = (posicao-lp+1) + num*10 - 10, //Guardando o codigo do prato
					fposicao;
		        rewind (fpratos);
				do
	            { 
		            fread (&prato, sizeof (prato),1,fpratos);
		            if (prato.chave == codigo_prato && prato.exclusao != 1) //se achou o codigo e o prato nao foi excluido
		           	{
		           		fposicao = ftell(fpratos); //guardando a posição do registro atual do arquivo 
			                 break;
					}
			                  
		        }while (!feof (fpratos));
					
				PRATOS prato_aux; //criando uma struct auxiliar 
				prato_aux = prato;// 
				fflush (stdin);
				setlocale (LC_ALL,"C");
			
				gotoxy (ci+4,posicao); 
				if(pega_alt(15,prato.nome) == 1)  //é igual a 1 quando a pessoa digitou esc
					alteracao_prato();
				fflush (stdin);
					
				gotoxy (ci+20,posicao); 
				if(pega_alt(40, prato.ingredientes, 1) == 1)
					alteracao();
				fflush (stdin);
					
				gotoxy (cf-11,posicao); 
				if(pega2_alt (2, prato.preco1) == 1)
					alteracao();
				fflush (stdin);
				
				gotoxy (cf-8,posicao); 
				if(pega2_alt (2, prato.preco2) == 1)
					alteracao();
				fflush (stdin);
					
				gotoxy (cf-4,posicao); 
				if(pega2_alt(0,prato.cal) == 1)
					alteracao();
		
		
				if (prato.nome[0] == '\0')
					strcpy (prato.nome, prato_aux.nome);
	
				if (prato.ingredientes[0] == '\0')
					strcpy (prato.ingredientes, prato_aux.ingredientes);
				
				if (prato.preco1[0] == '\0')
				{
					strcpy (prato.preco1, prato_aux.preco1);
					strcpy (prato.preco2, prato_aux.preco2);
				}
				if (prato.cal[0] == '\0')
					strcpy (prato.cal, prato_aux.cal);
				return fposicao;
				
			}
					
		}	
		
		if (prato_preferido == 1 && cont == tam)
		{
			int c=0;
			char pp[5];
			setlocale (LC_ALL, "Portuguese");
			HideCursor(1); //mostrando o cursor da tela
			
			textcolor (8);gotoxy (ci,25); printf ("Digite 0 caso deseja rever a tabela"); textcolor (BLACK);
			gotoxy (ci,24); printf ("Digite o número do seu prato preferido: ");
				
			do
			{
				fflush (stdin);
				if (pega2 (0,pp) == 1) //se digitado esc retorna
					return 0; 
				
				fflush(stdin);
				cliente.prato_preferido = atoi (pp);
				if (cliente.prato_preferido == 0) //se a pessoa digitou 0, ela reve a tabela
				{
					cont=0,
					num=0;
					c=0;
					rewind (fpratos);   //colocando ponteiro no inicio do arquivo
				}
				else if (cliente.prato_preferido > 0 && cliente.prato_preferido <= tam)
				{
					return 2;
				}
				else
				{
					gotoxy (ci,25); textcolor(RED); printf ("Prato não existente, redigite:                    "); gotoxy (ci+31,25);
					c++;
	 			} 
			}while (c>0);
		}
	}while (cont!=tam);
	fclose (fpratos);
	return 2; //retornando valor aleatorio (pois a funcao é int)
}
//***************************
int pega(int x, char string[40], int virgula = 0) //faz a consisitencia para strings apenas com letras
{
	char aux;
	fflush (stdin);
	
	strcpy (string, "                                       ");
    for (int i=39; i>0;i--)		//apagando caracteres da string
				string [i-1] = string [i];
	int i=0, //i conta quantos caracteres ja foram digitados
	espaco, //espaço serve para a pessoa nao conseguir digitar varios espacos
	enter,  //enter serve para a pessoa nao apertar apenas enter e ir 
	cont=0, //auxiliar para conseguir apagar ate certo ponto
	p=0, 	//auxiliar para conseguir apagar ate certo ponto
	I,		//auxiliar de i
	dig=0;  //dig aumenta de valor quando a pessoa digita uma letra
	
	
	do
	{
		fflush(stdin);
		enter = 0;
		aux=getch();
		if (aux == 8) //se digitado backspace
		{
			if (p==0)
			{
				I = i; //auxiliar de i
				p++;
			}
			
			for (int z=i-1; z<=25;z++)		//apagando caracter da string
				string [z] = string [z+1];
				
			if (cont<I)
			{
				printf ("\b \b"); //apagando na tela 
				cont++;
				i--;
			}
			dig--;
		}
		else if(aux == 27)
		{
			return 1;
		}
		else if((aux>= 65 && aux<=122) || (aux == ',' && virgula ==1)) //se digitado uma letra (independente se for maiuscula ou minuscula) OU 
		{																//digitado virgula e a pessoa estiver em ingredientes
			string[i]=aux;
			printf("%c",string[i]);
			i++;
			espaco = 0, p=0,cont=0;
			dig++;
		}
		else if (aux == '\r' && dig>0) //se for digitado enter 
		{
			enter++;
			i++;
			espaco = 0;
		}
		else if (aux == ' ' && espaco == 0)
		{
			
			string[i]=aux;
			printf("%c",string[i]);
			i++;
			espaco++;
			p=0,cont=0;
			dig++;

		}
		
	}while(enter == 0 && i<x);
	i--; //i é igual o tanto de caracteres digitados
	
}
//***************************
int pega2 (int x, char string[9]) //x = quantidade de numeros string = onde na struct vai salvar (ex: tel, cep)
								   //se x for igual a 0, quer dizer que nao há uma quantidade determinada de digitos (ex.: calorias, numero da casa)
{ 
	strcpy (string, "        ");
	for (int i=8; i>0;i--)		//apagando caracteres da string
				string [i-1] = string [i];
	char aux; 
	int i=0, //conta quantos numeros já foram digitados
	cont=0, //auxiliar para conseguir apagar ate certo ponto
	p=0, 	//auxiliar para conseguir apagar ate certo ponto
	I;		//auxiliar de i
	
	do
	{
		fflush(stdin);
		aux=getch();
		
		if (aux == 8) //se digitado backspace
		{
			if (p==0) //pode apagar na tela
			{
				I = i; //auxiliar de i (numero de caracteres digitados)
				p++;
			}
				
			for (int z=i-1; z<=25;z++)		//apagando caracter da string
				string [z] = string [z+1];
	
			if (cont<I)
			{
				printf ("\b \b"); //apagando na tela 
				cont++;
				i--;
			}
		
		}
		else if(aux == 27) //se digitado esc
		{
			return 1;
		}
		else if((aux>=48 && aux<= 57)) //se digitado um numero (0 a 9)
		{
			p=0,cont=0;
			string[i]=aux;
			printf("%c",string[i]);
			i++;
		}
	}while((i<x && x>0) || (x==0 && (aux != '\r' || i == 0))); //para de repetir quando:
											 				  //digitado o numero limite de caracteres OU 
															   //digitado enter e pelo menos um caracter ja foi digitado
																   //nao há limite de caracteres e digitado enter
	string [i] = '\0';
	fflush (stdin);
}
//***************************
void cadastro_cliente()
{
	void consulta_prato();
	void consulta_gerente();
	void inclusao();
	void escrever_arquivo(int);
	int x;
	char cadastrar;
	
	tela(0);
	int tam=0;
	if((fclientes=fopen("clientes.bin","rb")))
	{
		do
		{
			fread(&cliente, sizeof(cliente),1,fclientes);
			tam++;
		}while(!feof (fclientes));
		fclose(fclientes);
	} 
	cliente.chave=tam;
	
	gotoxy (30,7); printf ("Cadastro do cliente: %d", cliente.chave);
	fflush (stdin);
	int ci = 9, li = 9;
	setlocale (LC_ALL,"Portuguese");
	gotoxy (ci,li); printf ("Nome       :");
	gotoxy (ci,li+2); printf ("Cartão(s/n):");
	gotoxy (ci,li+4); printf ("Celular    : (  ) ");
	gotoxy (ci,li+6); printf ("Telefone    : (  ) ");
	gotoxy (ci,li+8); printf ("Rua        :");
	gotoxy (ci,li+10); printf ("Número     :");
	gotoxy (ci,li+12); printf ("CEP        :      -");
	gotoxy (ci,li+14); printf ("Apartamento:");
	gotoxy (ci+25,li+14); textcolor (8); printf ("Digite '0' caso não more em apartamento"); textcolor (BLACK);
	gotoxy (ci,li+16); printf ("Nascimento :   /  /                                     (DD/MM/AAAA)");
	int a=13;
	gotoxy (ci+13,li);
	if(pega(25,cliente.nome) == 1)
	{
		inclusao();
	}
	
	fflush (stdin);
	gotoxy (ci+a,li+2); cliente.cartao=getche();
	if(cliente.cartao == 27) //se digitado esc, retorna para a função anterior
		inclusao();
	while(cliente.cartao != 's' && cliente.cartao != 'S' && cliente.cartao != 'n' && cliente.cartao != 'N')
	{
		fflush (stdin);
		gotoxy(35,li+2); textcolor(8); printf("Redigite"); textcolor(BLACK);
		gotoxy (ci+a,li+2); cliente.cartao=getche();
	}
		
	gotoxy(35,li+2); printf("        ");
		 
	gotoxy (ci+14,li+4);
	if(pega2 (2, cliente.cel_1) == 1)
	{
		inclusao();
	} 
	fflush (stdin);	
	gotoxy (ci+18,li+4);
	if(pega2 (9, cliente.cel_2) == 1)
	{
		inclusao();
	}
	fflush (stdin);			
	gotoxy (ci+15,li+6);
	if(pega2 (2, cliente.tel_1) == 1)
	{
		inclusao();
	}
	fflush (stdin);		
	gotoxy (ci+19,li+6);
	if(pega2 (8, cliente.tel_2) == 1)
	{
		inclusao();
	}
	fflush (stdin);								
								
	gotoxy (ci+13,li+8); 
	if(pega(50, cliente.endereco.rua) == 1)
	{
	   	inclusao();
	}
	fflush (stdin);
		
	gotoxy (ci+13,li+10); 
	if(pega2 (0, cliente.endereco.numero) == 1)
	{
		inclusao();
	}
	fflush (stdin);
		
	gotoxy (ci+13,li+12); 
	if(pega2 (5, cliente.endereco.cep_1) == 1)
	{
		inclusao();
	} 
	fflush (stdin);
	gotoxy (ci+19,li+12); 
	if(pega2 (3, cliente.endereco.cep_2) == 1)
	{
		inclusao();
	}
	fflush (stdin);
		
	gotoxy (ci+13,li+14); 
	if(pega2 (0, cliente.endereco.complemento) == 1)
	{
		inclusao();
	}
	fflush (stdin);
	do
	{
		fflush (stdin);
		a=13;
		for (int i=0;i<2;i++)
		{
			gotoxy (ci+a,li+16);              //lendo dia
			fflush (stdin);	
			cliente.data.dia[i] = getche ();
			a++;
			if(cliente.data.dia[i] == 27)
			{
				inclusao();
			}
		}
		a=16;
		for (int i=0;i<2;i++)
		{
			gotoxy (ci+a,li+16); 
			fflush (stdin);
			cliente.data.mes[i] = getche ();
			a++;	
			if(cliente.data.mes[i] == 27)
			{
				inclusao();
			}
		} 	
		a=19;
		for (int i=0;i<5;i++)
		{
			gotoxy (ci+a,li+16); 
			fflush (stdin);
			cliente.data.ano[i] = getche ();
			a++;
			if(cliente.data.ano[i] == 27)
			{
				inclusao();
			}	
		}
			
		int dia = (cliente.data.dia[0]-48)*10 + cliente.data.dia[1]-48;
		int mes = (cliente.data.mes[0]-48)*10 + cliente.data.mes[1]-48;
		int ano = (cliente.data.ano[0]-48)*1000 + (cliente.data.ano[1]-48)*100 + (cliente.data.ano[2]-48)*10 + cliente.data.ano[3]-48;
		if((mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12) && dia>0 && dia<32)   //meses com 31 dias
			x=0;
			
		else if((mes==4 || mes==6 || mes==9 ||mes==11) && dia>0 && dia<31) //meses com 30 dias 
			x=0;
				
		else if(mes==2 && dia>0 && dia<29) //fevereiro, sem ser bissexto
			x=0;
			
		if (x==0 && ano>1920 && ano<2017 )
			x=0;
			
		else
		{
			x=1;
			gotoxy(35,25); textcolor(8); printf("Redigite"); textcolor (BLACK);
			gotoxy (ci,li+16); printf ("Nascimento :   /  /     ");		
		}		
			
	}while(x!=0);
		
	tela(0);
	gotoxy (30,7); printf ("Cadastro do cliente");		//arrumar a borda, está aparecendo 80 no canto superior direito
	fclose (fpratos);
	if(tabela_pratos (10,7,79,1) == 0)  //escolhendo prato preferido
	{
		inclusao();
	}
		
	tela (0);
	char salvar;
	gotoxy (ci,li-1); printf ("Deseja salvar o cadastro? ");gotoxy(ci,li);
	fflush(stdin);
	salvar=consist_sn(ci,li);
	if (salvar == 's'||salvar=='S')
	{
		cliente.exclusao=0;
		escrever_arquivo(2);	
	}
			
	fflush (stdin);
	gotoxy (ci,li+3); printf ("Deseja cadastrar mais alguma pessoa?");gotoxy (ci,li+4);
	cadastrar=consist_sn(ci,li+4);
	if (cadastrar == 'S' || cadastrar == 's')
		cadastro_cliente ();
	else
		inclusao();
		
}
//***************************
void inclusao()
{
	HideCursor(1); //colocando o cursor da tela
	void tela_menu(int,int);
	void cadastro_gerente ();
	char senha[10], escolha;
	int y=0,c; //c serve para consistencia do "Voce é gerente ou cliente"
	tela(4);
	do
	{
		c=0;
		fflush (stdin);
		setlocale (LC_ALL,"Portuguese");
		gotoxy(50,25); textcolor (8); printf("Aperte ESC caso deseje voltar"); textcolor (BLACK);
		gotoxy(7,8); printf("Você é -> GERENTE(1) ou CLIENTE (2):       "); 
		setlocale (LC_ALL,"C");
		gotoxy (44, 8); escolha = getche();
		
		if (escolha == 27) //ESC digitado
		{
			menu_principal();      //volta pro menu inicial
		}
		else 
		{
			getche();	//se nao for ESC, é necessario que se pressione enter 
			if (escolha !='1' && escolha != '2')
			{
				gotoxy(50,8); textcolor(8); printf("Redigite"); textcolor(BLACK);
				c=1;
			}
		}		
	}while(c==1);
	
	if(escolha=='1')
    {
    	gotoxy(50,8); printf("        ");
		gotoxy(7,10); printf("Digite a senha: ");
    	int a; //a tem  a função de repetir enquanto nao digitar a senha correta
   		do
   		{
    		a = 0;
    		fflush(stdin);
			gets(senha);
   			if(strcmp(senha,"admin")!=0)
   			{
    			gotoxy(7,10); textcolor (4); printf("Senha incorreta, redigite:                       "); gotoxy (34,10);
    			a++; 
    		}
		}while (a == 1);
		textcolor (BLACK);
    	cadastro_gerente(); 
    	tela(0);
	}
	else if(escolha=='2')
	{ 
		gotoxy(50,8); printf("        ");
		cadastro_cliente(); 
	}
}
//***************************
void tela_menu (int c,int li) //recebendo a coluna e a linha inicial  //c=13 l=10
{
	c--; 
	setlocale (LC_ALL,"Portuguese");
	textcolor (BLACK);
	textbackground (15);
	gotoxy (c, li); printf (" Inclusão");
	gotoxy (c, li+2); printf (" Consultas");
	gotoxy (c, li+4); printf (" Alteração");
	gotoxy (c, li+6); printf (" Exclusão");
	gotoxy (c, li+8); printf (" Sobre");
	gotoxy (c, li+10); printf (" Encerrar");
	gotoxy (8,25); printf ("Telefone: (14) 4002-8922");
	
}
//***************************
void tela_consulta(int ci,int li)
{
	gotoxy (ci,li);printf (" Pratos");
	gotoxy (ci,li+2);	printf (" Clientes");
	gotoxy (ci,li+4);	printf (" Voltar");
}
//***************************
void tela_tipo_consulta(int ci,int li)
{
	setlocale (LC_ALL,"Portuguese");
	textcolor(BLACK);
	gotoxy (30,10);printf("O que deseja fazer?");
	gotoxy(ci,li);printf(" Consulta geral");
	gotoxy(ci,li+2);printf(" Consulta por código");
	gotoxy(ci,li+4);printf(" Pesquisar texto");
	gotoxy(ci,li+6);printf(" Voltar");
}
//************************
void tela_alteracao(int ci, int li)
{
	setlocale (LC_ALL,"Portuguese");
	textcolor(BLACK);
	gotoxy (13,10);printf("Como você deseja alterar?");
	gotoxy(ci,li);printf(" Escolher na tabela");
	gotoxy(ci,li+2);printf(" Por código específico");
	gotoxy(ci,li+4);printf(" Voltar");
}
//************************
void tela_exclusao (int c, int l) //coluna e linha
{
	setlocale(LC_ALL,"Portuguese");
	gotoxy(c,l); printf("  Excluir prato");
	gotoxy(c,l+2); printf("  Excluir cliente");
	gotoxy(c,l+4); printf("  Voltar");
	setlocale(LC_ALL,"C");
}
void tela_exclusao_prato (int c, int l) //coluna e linha
{
	setlocale(LC_ALL,"Portuguese");
	gotoxy(c,l); printf("  Excluir por Código");
	gotoxy(c,l+2); printf("  Excluir por Tabela");
	gotoxy(c,l+4); printf("  Voltar");
	setlocale(LC_ALL,"C");
}
int cursor(int coluna, int linha, int opcoes, int tela) //c=12  l=10
{
	int li, lf; //linha inicial e linha final
	li = linha;
	lf = linha + (2*opcoes) - 2;
	char ch;
	borda (3,26,5,80);

	do 
	{
		if (tela == 1)
			tela_menu(13,10);
		else if (tela==2)
		    tela_consulta(coluna,li);
		else if (tela == 3)
		    tela_tipo_consulta(coluna, li);
		else if (tela == 4)
			tela_alteracao(coluna, li);
		else if (tela == 5)
		    tela_exclusao(coluna, li);
		else if(tela==6)
		 	tela_exclusao_prato(coluna,li);   
		HideCursor (0); //tirando cursor da tela
		setlocale (LC_ALL, "C");
		gotoxy (coluna,linha);printf ("%c",175); //imprimindo seta
		ch = getch();
		if (ch == 'w' || ch ==72) //se digitado "w" ou seta para cima
		{
			linha-=2;
		
		}
		else if (ch == 's' || ch ==80) //se digitado "w" ou seta para baixo
		{
			linha+=2;
		}

		if (linha > lf)
			linha = li;
		else if (linha < li)
			linha = lf;
		
		
	}while (ch != '\r');  //enquanto nao digitado enter
	setlocale (LC_ALL,"Portuguese");
	return linha;
}
//***************************
void tela_inicial (int li, int lf, int ci, int cf)  //recebendo: linha inicial, linha final, coluna inicial, coluna final 
{
	system ("color F0"); //cor de fundo branco
	
	// colocando cores e bordas chamativas:
	textbackground (4); //vermelho  
	for (int i=li; i<=lf;i++)    //imprimindo coluna inicial
	{
		gotoxy (ci,i); printf("  ");
	}
	for (int i=li;i<=lf;i++)    //imprimindo   coluna final
	{ 
		gotoxy (cf,i);printf ("  ");
	}
	for (int i = ci+1 ; i < cf ; i++)
	{
		gotoxy (i, li); printf (" ");   //imprimindo linha inicial e titulo
		
	}
	for (int i = ci+1 ; i < cf ;i++ )
	{
		gotoxy (i ,lf); printf (" "); //imprimindo linha final   
	}
	textbackground (14); //amarelo
	for (int i= (li+1); i<lf ; i++)
	{
		for (int j= (ci+1); j<cf ;j++)
			gotoxy (j,i); printf (" ");
	}	
	textbackground (14); //amarelo
	int colunas = cf-ci-2;
	for (int i= (li+1); i<lf ; i++)  //i=linha
	{
		gotoxy (ci+2,i);
		for (int j=1;j<=colunas;j++)
			printf (" ");
		
	}	
	//									3,26,5,80
	setlocale (LC_ALL,"C");
	int c; //c = coluna
																		//linha inicial 7 linha final =10
	//letra s:
	c=19;
	for (int i=1; i<=2 ; i++)
	{
		gotoxy (c,7);printf ("%c",219); printf ("%c%c%c",223,223,223);
		gotoxy (c,8);printf ("%c",219); printf ("%c%c%c",220,220,220);
		gotoxy (c+3,9); printf ("%c",219);
		gotoxy (c,10); printf ("%c%c%c%c",223,223,223,223);
		
		c=58;
	}
	
	
	//letra a
	for (int z = 1; z<=3 ; z++)
	{
		if (z == 1)
			c=24;
		else if (z == 2)
			c=52;
		else
			c=63;
		for (int i=7;i<=9;i++)
		{
			gotoxy (c,i);printf ("%c",219);
		}
		gotoxy (c,10); printf ("%c",223);  
		gotoxy (c+1,8); printf ("%c%c%c",220,220,220);  
		for (int i=7;i<=9;i++)
		{
			gotoxy (c+4,i);printf ("%c",219);
		}
		gotoxy (c+4,10); printf ("%c",223);
		gotoxy (c+1,7);printf ("%c%c%c",223,223,223);
	}

	//letra i
	c=30;
	for (int i=7;i<=9;i++)
	{
		gotoxy (c,i);printf ("%c",219);
	}
	gotoxy (c,10); printf ("%c",223);
	
	//acento
	gotoxy (c,6); printf ("%c",223);
	gotoxy (c+1,5); printf ("%c",220);  
	
	//letra d
	c=36;
	for (int i=7;i<=9;i++)
	{
		gotoxy (c,i);printf ("%c",219);
	}
	gotoxy (c,10); printf ("%c",223); 
	
	gotoxy (c+1,7); printf ("%c%c",223,223);
	gotoxy (c+6,7); printf ("%c",223);
	gotoxy (c+3,7); printf ("%c",220);
	gotoxy (c+3,8); printf ("%c",219);
	gotoxy (c+3,9); printf ("%c",219);
	gotoxy (c+2,10); printf ("%c",223);
	gotoxy (c+1,10); printf ("%c",223);
	
	//apostrofo
	c=42;
	gotoxy (c,7); printf ("%c",219);
	gotoxy (c-1,8); printf ("%c",223);
	
	//c
	c=47;
	for (int i=7; i<10 ; i++)
	{
			gotoxy (c,i); printf ("%c",219); 
	} 
	gotoxy (c,10); printf ("%c%c%c%c",223,223,223,223);
	gotoxy (c+1,7); printf ("%c%c%c",223,223,223);
	
	//***************************************
	HideCursor (0);
	textcolor (6);
	gotoxy (45,24); printf ("Aperte uma tecla para continuar...");
	textcolor (4);
	gotoxy (27,13); printf ("AQUI LHE DAREMOS UMA BOA COMIDA");
	gotoxy (27,15); printf ("www.saidecasa.com.br/marmitaria");
	gotoxy (32,17); printf ("Telefone: (14) 4002-8922");

	gotoxy (90,27);
	setlocale (LC_ALL,"Portuguese");
	getch();
}
//***************************
void escrever_arquivo(int opcao)
{
	
	if(opcao==1) //gerente, adicionando pratos
	{
		//fflush (fpratos);
		if((fpratos = fopen("pratos.bin", "ab"))==NULL)
		{ 
			printf("Problema na abertura do arquivo");
			exit(1);
		}
		if(fwrite(&prato, sizeof(prato),1,fpratos)==1)
				fflush (fpratos);
		fclose (fpratos);
	}
	else if(opcao==2) //cliente se cadastrando
	{
		
		if((fclientes = fopen("clientes.bin", "ab")))
		{ 
			if(fwrite(&cliente, sizeof(cliente),1,fclientes)==1)
				fflush (fclientes);
			fclose (fclientes);
		}
		else
		{
			printf("Problema na abertura do arquivo");
			exit(1);
		}
	}
		
}
//***************************
void sobre()
{
	setlocale (LC_ALL,"Portuguese");
	system ("cls");
	borda(3,26,5,80);
	textcolor (RED); 
	tela(5);
	gotoxy (40,7); printf ("SOBRE");
	
	int ci = 10, li = 12;    //definindo a linha e a coluna inicial
	textcolor (GREEN);
	gotoxy (ci,li);   printf("Nome Empresa: ");
	gotoxy (ci,li+2); printf("Integrantes : ");
	gotoxy (ci,li+7); printf("Turma       : ");
	gotoxy (ci,li+9); printf("Orientadora : ");
	gotoxy (ci,li+11);printf("Senha Gerente: ");
	textcolor (BLACK);
	ci+=14;
	gotoxy (13,10); printf("Empresa responsável pelo fornecimento de comida em larga escala");
	gotoxy (ci,li);printf("SAÍ D' CASA");
	gotoxy (ci,li+2);printf("Carlos Alberto   nº04");
	gotoxy (ci,li+3);printf("Leonardo Dias    nº18");
	gotoxy (ci,li+4);printf("Victor Russo     nº32");
	gotoxy (ci,li+5);printf("Yasmin Miranda   nº35");
	gotoxy (ci,li+7);printf("71A");
	gotoxy (24,li+9);printf("Ariane Scarelli");
	gotoxy (ci,li+11);printf("admin");
	gotoxy (45,25); textcolor (6); printf ("Aperte uma tecla para continuar...");
	getch();
}
//***********************
void cadastro_gerente()
{
	int continuar=0;
	do
	{
		fclose (fpratos);
		fflush (stdin);
		if ((fpratos=fopen("pratos.bin","rb")) == NULL)
		{
			printf ("Problema na abertura do arquivo para leitura");
			exit(1);
		}
		int lin=10,col=10;
		tela(0);
		int tam=0;
		/*strcpy (prato.ingredientes,"\0");
		strcpy (prato.nome, "\0");
		strcpy (prato.preco1, "\0");
		strcpy (prato.preco2, "\0");
		strcpy (prato.cal, "\0");
		*/
		do
		{
			tam++;
			fread(&prato, sizeof(prato),1,fpratos);
			
		}while(!feof (fpratos));
		
		prato.chave=tam;
		gotoxy(30,7);printf("Cadastro do prato: %d",prato.chave);
		gotoxy(col,lin);printf("Nome        :");
		gotoxy(col,lin+=2);printf("Ingredientes:");
		gotoxy(col,lin+=2);printf("Preço       : R$  ,");
		gotoxy(col,lin+=2);printf("Calorias    :       kCal");
		
		fflush(stdin);
		col=24;lin=10;
		gotoxy(col,lin); 
		if(pega(15,prato.nome) == 1)
		{
			inclusao();
		}
		gotoxy(col,lin+2); 
		if(pega(40,prato.ingredientes,1) == 1)
		{
			inclusao();
		}
		gotoxy(col+2,lin+4);  //colocando na posicao correta
		if(pega2 (2, prato.preco1) == 1)
		{
			inclusao();
		}
		 //consistencia para ver se foi digitado realmente um numero e salvando no preco_aux
		gotoxy(col+5,lin+4);  //colocando na posicao correta
		if(pega2 (2, prato.preco2) == 1)
		{
			inclusao();
		}
		getch(); 
		
		gotoxy(col,lin+6); 
		if(pega2(0,prato.cal) == 1)
		{
			inclusao();
		}
		tela(0);
		char salvar;
		fflush (stdin);
		gotoxy (10,12); printf ("Deseja salvar o cadastro?");gotoxy(10,13);
		fflush(stdin);
		salvar=consist_sn(10,13);
		if (salvar == 's'||salvar == 'S')
		{
			prato.exclusao=0;
			escrever_arquivo(1);
		}
		char cadastrar;
		gotoxy (10,15); printf ("Deseja cadastrar mais algum prato?");gotoxy (10,16);
		fflush(stdin);
		cadastrar=consist_sn(10,16);
		if (cadastrar == 'n' ||salvar == 'N')
				continuar++;	
	}while(continuar==0);
	fclose (fpratos);
	menu_principal();
}
//************************
int tabela_clientes(int li, int ci, int cf, int pergunta = 0)
{
	setlocale (LC_ALL,"Portuguese");
	char esc;
	int tam=1;
	fclose (fclientes);
	fclientes=fopen("pratos.bin","rb"); //nao estava funcionando vendo por NULL
	do		//contando quantos clientes existem cadastrados
	{
		fread(&cliente, sizeof(cliente),1,fclientes);
		tam++;
	}while(!feof (fclientes));
	tam-=2;
	
	if(tam == 0)  //nenhum prato cadastrado
	{
		gotoxy(28,12); printf("Não há clientes cadastrados\n");
		gotoxy(22,24); system("pause");
	}	
	else
	{
		rewind (fclientes);
		int cont=0, //quando cont=tam (tamanho do arquivo), para de mostrar pratos na tela
		    num=0; //num vai indicar quantas telas de prato ja foi mostrada
		do
		{
			tela(0);
			setlocale (LC_ALL,"Portuguese");
			//colocando titulos da tabela
			gotoxy (35,7); printf ("TABELA DE CLIENTES");
			gotoxy (ci+1,li); printf ("Nº");
			gotoxy (ci+5,li); printf ("Nome");
			gotoxy (ci+20,li); printf ("Telefone");
			gotoxy (cf-30,li); printf ("Prato Preferido");
			
			li+=1;
			num++;
			fflush (stdin);
			char dig;
            for (int i=0;i<10;i++)	
			{	
				fread(&cliente,sizeof(cliente),1,fclientes);
				gotoxy (ci+1,li+2); printf ("%d",cliente.chave);			//imprimindo sobre o prato
				gotoxy (ci+4,li+2); printf ("%s",cliente.nome);
				gotoxy (ci+20,li+2);puts(cliente.tel_1);gotoxy (ci+23,li+2);puts(cliente.tel_2);
				gotoxy (cf-30,li+2); printf ("%d",cliente.prato_preferido);
				li++;
				cont++;
				if (cont == tam)
					break;
			}	
		
			textcolor (12); 
			if(dig == 27)
			{
				return 1;
			}
			gotoxy (7,25); printf ("%c%c", 174, 205); //imprimindo seta pra esqueda <<
			gotoxy (77,25); printf ("%c%c",205, 175); //imprimindo seta pra direita >>
			textcolor (BLACK);
			li-=11;
				
			do 
			{
				fflush (stdin);
				gotoxy (1,1);dig = getch();
			
				if(dig == 75) //seta pra esquerda (voltar tabela)
				{
					rewind (fclientes);   //colocando ponteiro no inicio do arquivo
					for (int i=0;i<(10*(num-2)) ;i++)	//lendo o tanto necessario 
						fread(&cliente,sizeof(cliente),1,fclientes);
					cont = num*10 - 20;
					num-=2;
				}
			} while (dig != 75 && dig != 77); //enquanto nao for digitado nem seta pra esquerda nem pra direita
		}while (cont!=tam);
		fclose (fpratos);	
	}
}
//************************
void geral_gerente()
{
	void consulta_gerente();
	if((fclientes=fopen("clientes.bin","rb"))==NULL)
	{
		system("cls");
		tela(0);
		printf("Não há clientes cadastrados.");
	}
	else if(tabela_clientes(10,7,79) == 1)
	{
		consulta_gerente();
	}
	else
	{
		rewind (fclientes);
		system("cls");
		tela(0);
		gotoxy (33,7);printf ("Consulta Clientes - Geral");
		gotoxy (45,25); textcolor (6); printf ("Aperte uma tecla para voltar...");
		fclose(fclientes);
		getch();		
		
	}
	consulta_gerente();
}
//************************
void codigo_cliente()
{
	void consulta_gerente();
	tela(0);
	setlocale (LC_ALL,"Portuguese");
	gotoxy (30,7);printf ("Consulta Cliente - Código");
	char a[5],c=0;
	char esc;
	fflush (stdin);
	gotoxy (10,10);printf ("Digite o código que você deseja pesquisar: ");
	if(pega2(0, a) == 1)
	{
		consulta_gerente();
	}
	int aux = atoi (a);
	
	if ((fclientes=fopen("clientes.bin","rb")) == NULL)
	{
		printf ("Problema na abertura do arquivo para leitura");
		exit(1);
	}
	do
	{
		fread (&cliente, sizeof (cliente),1,fclientes);
		if (cliente.chave == aux && cliente.exclusao == 0) //achou
		{
			c=1;
			break;
		}		
	}while (!feof (fclientes));
	if (c==1)    //c vale 1 quando conseguiu achar um prato com aquele codigo
	{
		
		HideCursor(1);
		gotoxy(10,12);printf("Nome       :");gotoxy(22,12);printf("%s",cliente.nome);
		gotoxy(10,13);printf("Cartão(s/n):");gotoxy(22,13);printf("%c",cliente.cartao);
		gotoxy(10,14);printf("Celular    :");gotoxy(22,14);printf("(");gotoxy(23,14);puts(cliente.cel_1);gotoxy(25,14);printf(")");gotoxy(26,14);puts(cliente.cel_2);
		gotoxy(10,15);printf("Telefone   :");gotoxy(22,15);printf("(");gotoxy(23,15);puts(cliente.tel_1);gotoxy(25,15);printf(")");puts(cliente.tel_2);
		gotoxy(10,16);printf("Rua        :");gotoxy(22,16);puts(cliente.endereco.rua);
		gotoxy(10,17);printf("Número     :");gotoxy(22,17);puts(cliente.endereco.numero);
		gotoxy(10,18);printf("CEP        :");gotoxy(22,18);puts(cliente.endereco.cep_1);gotoxy(27,18);printf("-");puts(cliente.endereco.cep_2);
		gotoxy(10,19);printf("Apartamento:");gotoxy(22,19);puts(cliente.endereco.complemento);
		gotoxy(10,20);printf("Nascimento :");
		gotoxy(22,20);puts(cliente.data.dia);gotoxy(24,20);printf("/");puts(cliente.data.mes);gotoxy(27,20);printf("/");puts(cliente.data.ano);
	}
	else //nao achou 
	{
		gotoxy (10,12); printf ("Não foi possível achar nenhum código correspondente.");		
	}
	char continuar;
	gotoxy (10,23);printf ("Deseja procurar outro codigo? ");
	fflush (stdin);
	continuar=consist_sn(39,23);
	if (continuar == 's' || continuar == 'S')
		codigo_cliente();
	fclose(fclientes);	
}
//************************
void geral_prato()
{
	void consulta_prato();
	tela(0);
	gotoxy (33,7);printf ("Consulta Prato - Geral");
	if(tabela_pratos(10,7,79,0) == 0)
	{
		consulta_prato();
	}  //linha, coluna inicial, coluna final, 0 serve para nao fazer a pergunta de qual seu prato preferido
	
}
//************************
int codigo_prato()
{
	void consulta_prato();
	tela(0);
	int a=1;
	setlocale (LC_ALL,"Portuguese");
	gotoxy (37,7);printf ("Consulta Prato - Código");
	
	if ((fpratos=fopen("pratos.bin","rb")) == NULL)
	{
		printf ("Problema na abertura do arquivo para leitura");
		exit(1);
	}
	
	char b[5], //b serve pra ver qual o codigo que a pessoa deseja pesquisar
	c=0;
	fflush (stdin);
	gotoxy (10,10);printf ("Digite o código que você deseja pesquisar: ");
	if(pega2(0, b) == 1)
	{
		consulta_prato();
	}
	int aux = atoi (b);
	rewind (fpratos); //colocando ponteiro no inicio do arquivo
	do
	{
		fread (&prato, sizeof (prato),1,fpratos);
		if (prato.chave == aux && prato.exclusao != 1)
		{
			c=1;
			break;
		}
		c=0;
			
	}while (!feof (fpratos));
	if (c==1)    //c vale 1 quando conseguiu achar um prato com aquele codigo
	{

		gotoxy (10,12);printf ("Nome        : %s", prato.nome);
		gotoxy (10,13);printf ("Ingredientes: %s", prato.ingredientes);
		gotoxy (10,14);printf ("Preço       : %s,%s",prato.preco1, prato.preco2);
		gotoxy (10,15);printf ("Calorias    : ");puts(prato.cal);
	}
	else //nao achou 
	{
		gotoxy (10,12); printf ("Não foi possível achar nenhum código correspondente.");		
	}
	char continuar;
	gotoxy (10,23);printf ("Deseja procurar outro codigo? ");
	fflush (stdin);
	continuar=consist_sn(39,23);
	if (continuar == 's' || continuar == 'S')
		codigo_prato();
	
	a=0;	
	fclose (fpratos);
	return (a);
}
//************************
int pesquisa_prato()
{
	tela(0);
	int a=1, c;
	setlocale (LC_ALL,"Portuguese");
	gotoxy (30,7);printf ("Consulta Prato - Pesquisa");
	
	int ci=7, cf=79, li=12;
	li--;
	setlocale (LC_ALL,"Portuguese");		//colocando titulos 
	gotoxy (ci+1,li); printf ("Nº");
	gotoxy (ci+5,li); printf ("Nome");
	gotoxy (ci+30,li); printf ("Ingredientes");
	gotoxy (cf-4,li); printf ("kcal");
	gotoxy (cf-11,li); printf ("Preço");
	
	char pesquisa[20]; //pesquisa sera oq a pessoa deseja procurar
	fflush (stdin);
	gotoxy (8,9);printf ("Digite o nome do prato: ");
	gets (pesquisa);
	strupr (pesquisa); //deixando maiusculo

	int tam=0,qtd=0; //tam = tamanho do arquivo e qtd = repete ate chegar ao fim do arquivo	
	if ((fpratos=fopen("pratos.bin","rb")) == NULL)
	{
		printf ("Problema na abertura do arquivo para leitura");
		exit(1);
	}
	do
	{
		tam++;
		fread(&prato, sizeof(prato),1,fpratos);

	}while(!feof (fpratos));
	tam--;
	rewind (fpratos);
	do
	{
		int comp=0;  
		fread (&prato, sizeof (prato),1,fpratos);
		char prato_aux [50];
		strcpy (prato_aux, prato.nome);
		strupr(prato_aux);
		
		for (int i=0; i<strlen(prato.nome); i++)
		{
			int cont = 0; //cont conta quantas letras estão batendo 
			for (int j=0; j<strlen (pesquisa); j++)
			{
				if ( pesquisa[cont] == prato_aux[comp])
					cont++;
				comp++;
			}
			
			if (cont == strlen(pesquisa)) //achou um nome
			{
				gotoxy (ci+1,li+2); printf ("%d",prato.chave);			//imprimindo sobre o prato
				gotoxy (ci+4,li+2); printf ("%s",prato.nome);
				gotoxy (ci+15,li+2); printf ("%s",prato.ingredientes);
				gotoxy (cf-11,li+2); printf ("%s,%s",prato.preco1, prato.preco2);
				gotoxy (cf-4,li+2); puts(prato.cal);	//printf ("%d",prato.cal);
				li++;
				break;
			}
		}
		qtd++;		
	}while (qtd<tam);
	
	char continuar;
	gotoxy (10,23);printf ("Deseja pesquisar outro prato? ");
	fflush (stdin);
	continuar=consist_sn(39,23);
	if (continuar == 's' || continuar == 'S')
		pesquisa_prato();
	
	a=0;	
	fclose (fpratos);
	return (a);
}
//************************
void consulta_prato()
{
	void consulta();
	int a = 0,opcao;
	do
	{
		fflush (stdin);
		tela(2);
		gotoxy (30,7) ;printf ("Consultando pratos");
		opcao = cursor (23,14,4,3);
		
		if(opcao == 14) //consulta geral em tabela
		{
			geral_prato();
		}
		
		else if(opcao == 16) //consultando pela chave primaria
		{
			do
			{
				fflush (stdin);
				a = codigo_prato();
			}while (a==1);
		}
			
		else if (opcao == 18) //consulta por pesquisa de nome do prato
		{
			do
			{
				fflush (stdin);
				a = pesquisa_prato();
			}while (a==1);
		}
		
		else if (opcao == 20) //voltar 
		{
			consulta();
		}
	
	}while (a==0);
}
//************************
void pesquisa_cliente()
{
	tela(0);
	void consulta_gerente();
	int c;
	setlocale (LC_ALL,"Portuguese");
	gotoxy (30,6);printf ("Consulta Cliente - Pesquisa");
	int ci=7, cf=79, li=10;
	li--;
	setlocale (LC_ALL,"Portuguese");		//colocando titulos da tabela
	gotoxy (ci+1,li); printf ("Nº");
	gotoxy (ci+5,li); printf ("Nome");
	gotoxy (ci+20,li); printf ("Telefone");
	gotoxy (cf-30,li); printf ("Prato Preferido");
	char pesquisa[20]; //pesquisa sera oq a pessoa deseja procurar
	fflush (stdin);
	gotoxy (8,8);printf ("Digite o nome do cliente: ");
	gets (pesquisa);
	strupr (pesquisa); //deixando maiusculo
	int tam=0,qtd=0; //tam = tamanho do arquivo e qtd = repete ate chegar ao fim do arquivo
	if ((fclientes=fopen("clientes.bin","rb")) == NULL)
	{
		printf ("Problema na abertura do arquivo para leitura");
		exit(1);
	}
	
	do
	{
		tam++;
		fread(&cliente, sizeof(cliente),1,fclientes);

	}while(!feof (fclientes));
	tam--;
	getch();
}
//************************
void consulta_gerente()
{
	void consulta();
	int opcao;
	tela(2);
	gotoxy (30,7) ;printf ("Consultando clientes");
	opcao = cursor (23,14,4,3);
	if (opcao == 14) //geral
	{
		geral_gerente();
	}
	if (opcao == 16) //codigo
	{
		codigo_cliente();
	}
	if (opcao == 18) //pesquisa
	{
 	    pesquisa_cliente();
	}
	else if (opcao == 20)
	{
		consulta();
	}
}
//************************
void consulta ()
{
	void consulta_gerente();
	HideCursor(0); //tirando o cursor da tela
	tela (2); // 2 = desenho da pepsi
	gotoxy (37,7); printf ("CONSULTA");
	
	int opcao; 
	opcao = cursor (30,13,3,2); //enviando: coluna inicial, linha inicial, quantidade de opções do menu e qual tela sera exibida
		
	if (opcao == 13) //consulta pratos 
	{
		consulta_prato();
	}
	else if (opcao == 15) //consulta clientes
	{
		consulta_gerente();
	}
	
	else if (opcao == 17)
	{
		menu_principal();
	}
	
}
//************************

//************************
void alteracao_prato_geral()
{
	void alteracao_prato();
	tela(0);
	gotoxy (33,7) ;printf ("Alterando pratos - Tabela");
	
	/*enviando: coluna inicial, linha inicial, coluna final, sem pergunta de qual seu 
	prato preferido e 1 que serve para pessoa selecionar o prato que deseja alterar: */
	int fposicao = tabela_pratos (10,7,79,0,1);  //pegando o codigo do prato que quero alterar
	if(fposicao == 0) //vale 0 quando o usuario pressionou esc, deve voltar
	{
		alteracao_prato();
	}
	setlocale (LC_ALL, "Portuguese");
	char salvar;
	gotoxy (7,23); printf ("Deseja salvar as alterações? ");
	salvar = consist_sn (38, 23);
	fflush (stdin);
	if (salvar == 's')
	{
		
		fseek (fpratos,fposicao-(sizeof(prato)),SEEK_SET);
		fwrite (&prato, sizeof (prato),1,fpratos);
	}
	fclose (fpratos);
	
	char continuar;
	gotoxy (7,24);printf ("Deseja alterar outro prato pela tabela? ");
	continuar=consist_sn(47,24);
	if (continuar == 's' || continuar == 'S')
		alteracao_prato_geral();
	
}
//************************
int pega_alt(int x, char string [40], int virgula = 0) //consistencia de letras para alteracao (permite que seja digitado apenas enter na string)
{
	char aux;
	fflush (stdin);
	strcpy (string, "                                       ");
    for (int i=39; i>0;i--)		//apagando caracteres da string
				string [i-1] = string [i];
				
	int i=0, //i conta quantos caracteres ja foram digitados
	espaco, //espaço serve para a pessoa nao conseguir digitar varios espacos
	cont=0, //auxiliar para conseguir apagar ate certo ponto
	p=0, 	//auxiliar para conseguir apagar ate certo ponto
	I,		//auxiliar de i
	dig=0;  //dig aumenta de valor quando a pessoa digita uma letra
		
	do
	{
		fflush(stdin);
		aux=getch();
		
		if (aux == '\r' && i==0) //se a pessoa digitar enter no primeiro espaço
		{
			string[0] == '\0'; 
			return 0;
		}
		if (aux == 8) //se digitado backspace
		{
			if (p==0)
			{
				I = i; //auxiliar de i
				p++;
			}
			
			for (int z=i-1; z<=25;z++)		//apagando caracter da string
				string [z] = string [z+1];
				
			if (cont<I)
			{
				printf ("\b \b"); //apagando na tela 
				cont++;
				i--;
			}
			dig--;
		}
		else if(aux == 27) //se digitado esc
		{
			return 1;
		}
		else if((aux>= 65 && aux<=122) || (aux == ',' && virgula ==1)) //se digitado uma letra (independente se for maiuscula ou minuscula) OU 
		{																//digitado virgula e a pessoa estiver em ingredientes
			string[i]=aux;
			printf("%c",string[i]);
			i++;
			espaco = 0, p=0,cont=0;
			dig++;
		}
		else if (aux == ' ' && espaco == 0)
		{
			
			string[i]=aux;
			printf("%c",string[i]);
			i++;
			espaco++;
			p=0,cont=0;
			dig++;

		}
	
	}while(i<x && aux != '\r');
	i--; //i é igual o tanto de caracteres digitados
	
}
//************************
int pega2_alt(int x, char string[9]) //consistencia de numeros para alteracao (permite que seja digitado apenas enter na string)
{
	strcpy (string, "        ");
	for (int i=8; i>0;i--)		//apagando caracteres da string
				string [i-1] = string [i];
	char aux; 
	int i=0, //conta quantos numeros já foram digitados
	cont=0, //auxiliar para conseguir apagar ate certo ponto
	p=0, 	//auxiliar para conseguir apagar ate certo ponto
	I;		//auxiliar de i
	
	do
	{
		fflush(stdin);
		aux=getch();
		
		if (aux == '\r' && i==0) //se a pessoa digitar enter no primeiro espaço
		{
			string[0] == '\0'; 
			return 0;
		}
		else if (aux == 8) //se digitado backspace
		{
			if (p==0) //pode apagar na tela
			{
				I = i; //auxiliar de i (numero de caracteres digitados)
				p++;
			}
				
			for (int z=i-1; z<=25;z++)		//apagando caracter da string
				string [z] = string [z+1];
	
			if (cont<I)
			{
				printf ("\b \b"); //apagando na tela 
				cont++;
				i--;
			}
		
		}
		else if(aux == 27)
		{
			return 1;
		}
		else if(aux>=48 && aux<= 57) //se digitado um numero (0 a 9) ou enter
		{
			p=0,cont=0;
			string[i]=aux;
			printf("%c",string[i]);
			i++;
		}
	}while((i<x && x>0) || (x==0 && aux != '\r')); //para de repetir quando:
															   //digitado o numero limite de caracteres OU 
															   //nao há limite de caracteres e digitado enter 
	string [i] = '\0';
	
}
//************************
void alteracao_cliente_geral()
{
	tela(0);
}
//************************
void alteracao_cliente_codigo()
{
	tela(0);
	void alteracao_cliente();
	void alteracao();
	fflush (stdin);
	CLIENTES aux;
	gotoxy (30,7) ;printf ("Alterando clientes - Código");
	fclose(fclientes);
	if ((fclientes = fopen("clientes.bin", "rb+"))==NULL) //abrindo arquivo para ler e escrever
	{
		printf ("Problema na abertura do arquivo para leitura");
		exit(1);
	}
	rewind(fclientes);
	int cod_aux;
	int file_p;
	int c=0;
	char a[5];
	gotoxy(10,10);printf("Digite o código que você deseja pesquisar:");
	if(pega2(0, a) == 1)
	{
		alteracao_cliente();
	}  
	cod_aux=atoi(a);
	do
	{
		fread(&cliente,sizeof(cliente),1,fclientes);
		if(cod_aux==cliente.chave&&cliente.exclusao!=1)
		{
			c=1;
			file_p=ftell(fclientes);
			break;
		}
	}while(!feof(fclientes));
	if(c==1)
	{
		HideCursor(1);
		aux=cliente;
		gotoxy(10,12);printf("Nome       :");gotoxy(22,12);printf("%s",aux.nome);
		gotoxy(10,13);printf("Cartão(s/n):");gotoxy(22,13);printf("%c",aux.cartao);
		gotoxy(10,14);printf("Celular    :");gotoxy(22,14);printf("(");gotoxy(23,14);puts(aux.cel_1);gotoxy(25,14);printf(")");gotoxy(26,14);puts(aux.cel_2);
		gotoxy(10,15);printf("Telefone   :");gotoxy(22,15);printf("(");gotoxy(23,15);puts(aux.tel_1);gotoxy(25,15);printf(")");puts(aux.tel_2);
		gotoxy(10,16);printf("Rua        :");gotoxy(22,16);puts(aux.endereco.rua);
		gotoxy(10,17);printf("Número     :");gotoxy(22,17);puts(aux.endereco.numero);
		gotoxy(10,18);printf("CEP        :");gotoxy(22,18);puts(aux.endereco.cep_1);gotoxy(27,18);printf("-");puts(aux.endereco.cep_2);
		gotoxy(10,19);printf("Apartamento:");gotoxy(22,19);puts(aux.endereco.complemento);
		gotoxy(10,20);printf("Nascimento :");
		gotoxy(22,20);puts(aux.data.dia);gotoxy(24,20);printf("/");puts(aux.data.mes);gotoxy(27,20);printf("/");puts(aux.data.ano);
		gotoxy(22,12);
		if(pega_alt(25,cliente.nome)==1)
			alteracao_cliente();
			
		do
		{
			gotoxy(22,13);
			cliente.cartao=getche();
			if(cliente.cartao==27)
				alteracao_cliente();	
		}while(cliente.cartao!='s'&&cliente.cartao!='S'&&cliente.cartao!='n'&&cliente.cartao!='N'&&cliente.cartao!='\r');
		gotoxy(23,14);
		if(pega2_alt(2,cliente.cel_1)==1)
			alteracao_cliente();
		gotoxy(26,14);
		if(pega2_alt(8,cliente.cel_2)==1)
			alteracao_cliente();
		gotoxy(23,15);
		if(pega2_alt(2,cliente.tel_1)==1)
			alteracao_cliente();
		gotoxy(26,15);
		if(pega2_alt(9,cliente.tel_2)==1)
			alteracao_cliente();
		gotoxy(22,16);	
		if(pega_alt(50,cliente.endereco.rua)==1)
			alteracao_cliente();
		gotoxy(22,17);
		if(pega2_alt(0,cliente.endereco.numero)==1)
			alteracao_cliente();
		gotoxy(22,18);
		if(pega2_alt(5,cliente.endereco.cep_1)==1)
			alteracao_cliente();
		gotoxy(28,18);	
		if(pega2_alt(3,cliente.endereco.cep_2)==1)
			alteracao_cliente();	
		gotoxy(22,19);
		if(pega2_alt(0,cliente.endereco.complemento)==1)
			alteracao_cliente();
		int x=1;
		do
		{
			fflush (stdin);
			for (int i=0;i<2;i++)
			{
				char a[2];
				gotoxy (22+i,20);              //lendo dia
				fflush (stdin);
				strcpy(a,cliente.data.dia);
				cliente.data.dia[i] = getche ();
				if(cliente.data.dia[0]=='\r')
				{
					strcpy(cliente.data.dia,a);
					break;
				}
				if(cliente.data.dia[i] == 27)
				{
					inclusao();
				}
			}
			printf("/");
			for (int i=0;i<2;i++)
			{
				gotoxy (25+i,20); 
				fflush (stdin);
				char a[2];
				strcpy(a,cliente.data.mes);
				cliente.data.mes[i] = getche ();
				if(cliente.data.mes[0]=='\r')
				{
					strcpy(cliente.data.mes,a);
					break;
				}	
				if(cliente.data.mes[i] == 27)
				{
					inclusao();
				}
			} 	
			printf("/");
			for (int i=0;i<5;i++)
			{
				gotoxy (28+i,20); 
				fflush (stdin);
				char a[5];
				strcpy(a,cliente.data.ano);
				cliente.data.ano[i] = getche ();
				if(cliente.data.ano[0]=='\r')
				{
					strcpy(cliente.data.ano,a);
					break;
				}
				if(cliente.data.ano[i] == 27)
				{
					inclusao();
				}	
			}
			int dia = (cliente.data.dia[0]-48)*10 + cliente.data.dia[1]-48;
			int mes = (cliente.data.mes[0]-48)*10 + cliente.data.mes[1]-48;
			int ano = (cliente.data.ano[0]-48)*1000 + (cliente.data.ano[1]-48)*100 + (cliente.data.ano[2]-48)*10 + cliente.data.ano[3]-48;
			if((mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12) && dia>0 && dia<32)   //meses com 31 dias
				x=0;

			else if((mes==4 || mes==6 || mes==9 ||mes==11) && dia>0 && dia<31) //meses com 30 dias 
				x=0;
				
			else if(mes==2 && dia>0 && dia<29) //fevereiro, sem ser bissexto
				x=0;
			
			if (x==0 && ano>1920 && ano<2017 )
				x=0;
			
			else
			{
				x=1;
				gotoxy(35,25); textcolor(8); printf("Redigite"); textcolor (BLACK);
				gotoxy (10,20); printf ("Nascimento :   /  /     ");		
			}		
			
		}while(x!=0);			
		if(cliente.nome[0]=='\0')
			strcpy(cliente.nome,aux.nome);
		if(cliente.cartao=='\r')
			cliente.cartao=aux.cartao;
		if(cliente.cel_1[0]=='\0')
			strcpy(cliente.cel_1,aux.cel_1);
		if(cliente.cel_2[0]=='\0')
			strcpy(cliente.cel_2,aux.cel_2);
		if(cliente.tel_1[0]=='\0')
			strcpy(cliente.tel_1,aux.tel_1);
		if(cliente.tel_2[0]=='\0')
			strcpy(cliente.tel_2,aux.tel_2);	
		if(cliente.endereco.rua[0]=='\0')
			strcpy(cliente.endereco.rua,aux.endereco.rua);	
		if(cliente.endereco.numero[0]=='\0')
			strcpy(cliente.endereco.numero,aux.endereco.numero);
		if(cliente.endereco.cep_1[0]=='\0')
			strcpy(cliente.endereco.cep_1,aux.endereco.cep_1);
		if(cliente.endereco.cep_2[0]=='\0')
			strcpy(cliente.endereco.cep_2,aux.endereco.cep_2);
		if(cliente.endereco.complemento[0]=='\0')
			strcpy(cliente.endereco.complemento,aux.endereco.complemento);
		setlocale(LC_ALL,"Portuguese");
		char salvar;
		gotoxy(10,23);printf("Deseja salvar as alterações?");
		salvar=consist_sn(38,21);
		if(salvar='S'||'s')
		{
			fseek(fclientes,file_p-sizeof(cliente),SEEK_SET);
			fwrite(&cliente,sizeof(cliente),1,fclientes);
		}	
											
	}
	else
	{
		gotoxy(10,12);printf("Nao foi possível achar esse codigo");
		getch();
	}
	fclose(fclientes);
	char continuar;
	gotoxy (10,24);printf ("Deseja alterar outro cliente? ");
	continuar=consist_sn(39,23);
	if (continuar == 's' || continuar == 'S')
		alteracao_cliente_codigo();
	alteracao_cliente();
}
//************************
void alteracao_cliente() //alterando os clientes
{
	tela(0);
	void alteracao();
	int opcao;
	
	fflush (stdin);
	tela(3);
	gotoxy (33,7) ;printf ("Alterando clientes");
	opcao = cursor (13,14,3,4); //coluna, linha incial, qtd de opcoes e qual tela sera mostrada 
	
	if(opcao == 14) //alteração pela tabela
	{
		alteracao_cliente_geral();
	}
		
	else if(opcao == 16) //alteração por codigo
	{
		alteracao_cliente_codigo();
	}
			
	else if (opcao == 18) //voltar
	{
		alteracao();
	}

}
void alteracao_prato_codigo()
{
	void alteracao_prato();
	void alteracao();
	tela(0);
	fflush (stdin);
	gotoxy (30,7) ;printf ("Alterando pratos - Código");
	fclose (fpratos);
	if ((fpratos = fopen("pratos.bin", "rb+"))==NULL) //abrindo arquivo para ler e escrever
	{
		printf ("Problema na abertura do arquivo para leitura");
		exit(1);
	}
	  

	int fposicao; //posicao é uma posicao a mais do que a do prato que desejamos alterar
	int c;       //'c' vale um quando achou algum codigo
    char a[5];
	gotoxy (10,10);printf ("Digite o código que você deseja pesquisar: ");
	if(pega2(0, a) == 1)
	{
		alteracao_prato();
	}
	fflush (stdin);
	int codigo_aux = atoi (a); //transformando em numero
	
	do
	{
		fread (&prato, sizeof (prato),1,fpratos);
		if (prato.chave == codigo_aux && prato.exclusao != 1) //se achou o codigo e o prato nao foi excluido
		{
			c=1;
			fposicao = ftell(fpratos); //guardando a posição do registro atual do arquivo 
			break;
		}
		c=0;
			
	}while (!feof (fpratos));
	if (c==1)    //c vale 1 quando conseguiu achar um prato com aquele codigo
	{
		HideCursor(1); //mostrando o cursor da tela
		PRATOS prato_aux; //criando uma struct auxiliar 
		prato_aux = prato;// 
		gotoxy (10,12);printf ("Nome        : %s", prato.nome);
		gotoxy (10,13);printf ("Ingredientes: %s", prato.ingredientes);
		gotoxy (10,14);printf ("Preço       : %s,%s",prato.preco1, prato.preco2);
		gotoxy (10,15);printf ("Calorias    : %s", prato.cal);
		fflush (stdin);
		setlocale (LC_ALL,"C");
		gotoxy (24,12); 
		if(pega_alt(15,prato.nome) == 1)
		{
			alteracao();
		}
		fflush (stdin);
		gotoxy (24,13); 
		if(pega_alt(40,prato.ingredientes, 1) == 1)
		{
			alteracao();
		}
		fflush (stdin);
		gotoxy (24,14); 
		if(pega2_alt (2, prato.preco1) == 1)
		{
			alteracao();
		}
		fflush (stdin);
		gotoxy (27,14); 
		if(pega2_alt (2, prato.preco2) == 1)
		{
			alteracao();
		}
		fflush (stdin);
		gotoxy (24,15); 
		if(pega2_alt(0,prato.cal) == 1)
		{
			alteracao();
		}
		
		if (prato.nome[0] == '\0')
		{
			strcpy (prato.nome, prato_aux.nome);
		}
		if (prato.ingredientes[0] == '\0')
			strcpy (prato.ingredientes, prato_aux.ingredientes);
		if (prato.preco1[0] == '\0')
		{
			strcpy (prato.preco1, prato_aux.preco1);
			strcpy (prato.preco2, prato_aux.preco2);
		}
		if (prato.cal[0] == '\0')
		{
			strcpy (prato.cal, prato_aux.cal);
		}
		setlocale (LC_ALL, "Portuguese");
		char salvar;
		gotoxy (10,21); printf ("Deseja salvar as alterações? ");
		salvar = consist_sn (38, 21);
		if (salvar == 's'||salvar=='S')
		{
			fseek (fpratos,fposicao-(sizeof(prato)),SEEK_SET);
			fwrite (&prato, sizeof (prato),1,fpratos);
		}	
		
	}
	else //nao achou 
	{
		gotoxy (10,12); printf ("Não foi possível achar nenhum código correspondente.");		
	}
	fclose (fpratos);
	char continuar;
	gotoxy (10,23);printf ("Deseja alterar outro prato? ");
	continuar=consist_sn(39,23);
	if (continuar == 's' || continuar == 'S')
		alteracao_prato_codigo();

}
//************************
void alteracao_prato() //alterando os pratos
{
	setlocale (LC_ALL, "Portuguese");
	tela(0);
	void alteracao();
	int opcao;
	
	fflush (stdin);
	tela(3);
	gotoxy (30,7) ;printf ("Alterando pratos");
	opcao = cursor (13,14,3,4); //coluna, linha incial, qtd de opcoes e qual tela sera mostrada 
	
	if(opcao == 14) //alteração pela tabela
	{
		alteracao_prato_geral();
	}
		
	else if(opcao == 16) //alteração por codigo
	{
		alteracao_prato_codigo();
	}
			
	else if (opcao == 18) //voltar
	{
		alteracao();
	}
	getch();
}
//************************
void alteracao()
{
	tela (7); // 7 = desenho ferramentas
	gotoxy (35,7); printf ("ALTERAÇÃO");
	int opcao; 
	opcao = cursor (27,12,3,2); //enviando: coluna inicial, linha inicial, quantidade de opções do menu e qual tela sera exibida	
	if (opcao == 12) //altera pratos 
	{
		alteracao_prato();
	}
	else if (opcao == 14) //altera clientes
	{
		alteracao_cliente();
	}
	
	else if (opcao == 16)  //voltar
	{
		menu_principal();
	}
	
} 
//***********************
void excluir_prato_codigo()
{
	void exclusao();
	tela(0);
	fflush(stdin);
	gotoxy (30,7) ;printf ("Excluindo pratos - Código");
	fclose (fpratos);
	if ((fpratos = fopen("pratos.bin", "rb+"))==NULL) //abrindo arquivo para ler e escrever
	{
		printf ("Problema na abertura do arquivo para leitura");
		exit(1);
	}
	int fposicao; //posicao é uma posicao a mais do que a do prato que desejamos alterar
	int c;       //'c' vale um quando achou algum codigo
    char a[5];
	gotoxy (10,10);printf ("Digite o código que você deseja pesquisar: ");
	if(pega2(0, a) == 1)
	{
		alteracao_prato();
	}
	fflush (stdin);
	int codigo_aux = atoi (a); //transformando em numero
	
	do
	{
		fread (&prato, sizeof (prato),1,fpratos);
		if (prato.chave == codigo_aux && prato.exclusao != 1) //se achou o codigo e o prato nao foi excluido
		{
			c=1;
			fposicao = ftell(fpratos); //guardando a posição do registro atual do arquivo 
			break;
		}
		c=0;
			
	}while (!feof (fpratos));
	if (c==1)    //c vale 1 quando conseguiu achar um prato com aquele codigo
	{
		int comp [2]; 
		comp[0] = strlen (prato.nome);
		comp[1] = strlen (prato.ingredientes);
		
		gotoxy (10,12);printf ("Nome        : %s", prato.nome);
		gotoxy (10,13);printf ("Ingredientes: %s", prato.ingredientes);
		gotoxy (10,14);printf ("Preço       : %s,%s",prato.preco1, prato.preco2);
		gotoxy (10,15);printf ("Calorias    : %s", prato.cal);
		fflush (stdin);
		setlocale (LC_ALL,"Portuguese");
		gotoxy(10,17);textcolor(RED);printf("Deseja realmente excluir este prato?");
		char op;
		op=consist_sn(47,17);
		if(op=='S'||op=='s')
		{
			fflush (stdin);
			fseek (fpratos,fposicao-(sizeof(prato)),SEEK_SET);
			prato.exclusao=1;
			fwrite(&prato,sizeof(prato),1,fpratos);
			fclose(fpratos);
			textcolor(BLACK);
			
			gotoxy(24,12);          //excluindo nome do prato
			for(int i=0 ;i<comp[0] ;i++)
			{
				printf(" "); Sleep(100);
			}
			
			gotoxy(24,13);          //excluindo ingredientes
			for(int i=0;i<comp[1];i++)
			{
				printf(" "); Sleep(100);
			}
			
			gotoxy(24,14);          //excluindo preço
			for(int i=0;i<5;i++)
			{
				printf(" "); Sleep(100);
			}
			
			gotoxy(24,15);          //excluindo calorias
			for(int i=0;i<5;i++)
			{
				printf(" "); Sleep(100);
			}
			
			HideCursor (0);
			gotoxy(29,20); printf("Prato excluído com sucesso");
		}
	}
	else
	{
		gotoxy(29,15);
		printf("Código não encontrado");
	}
	textcolor (BLACK); gotoxy (10,22); printf ("Deseja excluir outro prato?"); textcolor (0);
	char cont;
	cont=consist_sn(37,22);
	if(cont=='s'||cont=='S')
		excluir_prato_codigo();
}
//***********************
void excluir_prato()
{
	tela(3);
	gotoxy(35,7); printf("EXCLUSÃO - Pratos"); 
	int opcao;
	void exclusao();
	opcao=cursor(20,12,3,6);
	if (opcao == 12) //excluir prato por código
	{
		excluir_prato_codigo();
	}
	else if (opcao == 14) //excluir na tabela
	{
		
	}
	
	else if (opcao == 16)  //voltar
	{
		exclusao();
	}
}
//************************
 void excluir_cliente_codigo()
 {
 	HideCursor(1);
	void exclusao();
 	void exclusao_cliente();
	tela(0);
	fflush(stdin);
	gotoxy (30,7) ;printf ("Excluindo clientes - Código");
	fclose(fclientes);
	if ((fclientes = fopen("clientes.bin", "rb+"))==NULL) //abrindo arquivo para ler e escrever
	{
		printf ("Problema na abertura do arquivo para leitura");
		exit(1);
	}
	int fposicao; //posicao é uma posicao a mais do que a do cliente que desejamos alterar
	int c;       //'c' vale um quando achou algum codigo
    char a[5];
	gotoxy (10,10);printf ("Digite o código que você deseja pesquisar: ");
	if(pega2(0, a) == 1)
	{
		alteracao_cliente();
	}
	fflush (stdin);
	int codigo_aux = atoi (a); //transformando em numero
	do
	{
		fread (&cliente, sizeof (cliente),1,fclientes);
		if (cliente.chave == codigo_aux && cliente.exclusao != 1) //se achou o codigo e o prato nao foi excluido
		{
			c=1;
			fposicao = ftell(fclientes); //guardando a posição do registro atual do arquivo 
			break;
		}
		c=0;
			
	}while (!feof (fclientes));
	if(c==1)
	{
		int comp[2];
		comp[0]=strlen(cliente.nome);
		comp[1]=strlen(cliente.endereco.rua);
		gotoxy(10,12);printf("Nome       :");gotoxy(22,12);printf("%s",cliente.nome);
		gotoxy(10,13);printf("Cartão(s/n):");gotoxy(22,13);printf("%c",cliente.cartao);
		gotoxy(10,14);printf("Celular    :");gotoxy(22,14);printf("(");gotoxy(23,14);puts(cliente.cel_1);gotoxy(25,14);printf(")");gotoxy(26,14);puts(cliente.cel_2);
		gotoxy(10,15);printf("Telefone   :");gotoxy(22,15);printf("(");gotoxy(23,15);puts(cliente.tel_1);gotoxy(25,15);printf(")");puts(cliente.tel_2);
		gotoxy(10,16);printf("Rua        :");gotoxy(22,16);puts(cliente.endereco.rua);
		gotoxy(10,17);printf("Número     :");gotoxy(22,17);puts(cliente.endereco.numero);
		gotoxy(10,18);printf("CEP        :");gotoxy(22,18);puts(cliente.endereco.cep_1);gotoxy(27,18);printf("-");puts(cliente.endereco.cep_2);
		gotoxy(10,19);printf("Apartamento:");gotoxy(22,19);puts(cliente.endereco.complemento);
		gotoxy(10,20);printf("Nascimento :");
		gotoxy(22,20);puts(cliente.data.dia);gotoxy(24,20);printf("/");puts(cliente.data.mes);gotoxy(27,20);printf("/");puts(cliente.data.ano);
		setlocale (LC_ALL,"Portuguese");
		gotoxy(10,22);textcolor(RED);printf("Deseja realmente excluir este cliente?");
		char op;
		op=consist_sn(47,22);
		if(op=='s'||op=='S')
		{
			fflush(stdin);
			fseek(fclientes,fposicao-sizeof(cliente),SEEK_SET);
			cliente.exclusao=1;
			fwrite(&cliente,sizeof(cliente),1,fclientes);
			fclose(fclientes);
			textcolor(BLACK);
			gotoxy(22,12);
			for(int i=0;i<comp[0];i++)
			{
				printf(" "); Sleep(100);
			}
			gotoxy(22,13);printf(" ");Sleep(100);
			gotoxy(22,14);
			for(int i=0;i<14;i++)
			{
				printf(" ");Sleep(100);
			}
			gotoxy(22,15);
			for(int i=0;i<13;i++)
			{
				printf(" ");Sleep(100);
			}
			gotoxy(22,16);
			for(int i=0;i<comp[1];i++)
			{
				printf(" "); Sleep(100);
			}
			gotoxy(22,17);
			for(int i=0;i<5;i++)
			{
				printf(" "); Sleep(100);
			}
			gotoxy(22,18);
			for(int i=0;i<9;i++)
			{
				printf(" "); Sleep(100);
			}
			gotoxy(22,19);
			for(int i=0;i<4;i++)
			{
				printf(" "); Sleep(100);
			}
			gotoxy(22,20);
			for(int i=0;i<10;i++)
			{
				printf(" "); Sleep(100);
			}
			HideCursor (0);
			gotoxy(29,23); printf("Prato excluído com sucesso");
			
		}
	}
	else
	{
		gotoxy(29,15);
		printf("Código não encontrado");
	}
	textcolor (BLACK); gotoxy (10,24); printf ("Deseja excluir outro cliente?"); textcolor (0);
	char cont;
	cont=consist_sn(38,24);
	if(cont=='s'||cont=='S')
		excluir_cliente_codigo();
 }
void excluir_cliente()
{
	tela(3);
	gotoxy(35,7); printf("EXCLUSÃO - Clientes"); 
	int opcao;
	void exclusao();
	opcao=cursor(20,12,3,6);
		if (opcao == 12) //excluir cliente por código
	{
		excluir_cliente_codigo();
	}
	else if (opcao == 14) //excluir na tabela
	{
		
	}
	
	else if (opcao == 16)  //voltar
	{
		exclusao();
	}
}
void exclusao()
{
	tela(3);  //desenhando pc
	int opcao;
	gotoxy(38,7); printf("EXCLUSÃO");  
	opcao = cursor (20,13,3,5); //enviando: coluna inicial, linha inicial, quantidade de opções do menu e qual tela sera exibida	
	if (opcao == 13) //excluir prato
	{
		excluir_prato();
	}
	else if (opcao == 15) //excluir cliente
	{
		excluir_cliente();
	}
	
	else if (opcao == 17)  //voltar
	{
		menu_principal();
	}
	getch();
}






