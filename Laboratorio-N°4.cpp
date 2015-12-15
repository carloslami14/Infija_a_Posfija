/*    Laboratorio de Sintaxis y Semantica de los Lenguajes
  
  Comision: 2K2

  Año: 2015

  Integrantes:
    Belmonte, Agustin
    Castro, Emanuel
    Lami, Carlos
    Martinez, Daniel
*/

#include<stdio.h>
#include<string.h>
#include<string.h>
#include<math.h>
#define max 50

//Estructura de la pila
struct nodo {     
       char info;
       struct nodo *sig;
};

struct nodo2 {     
       int info;
       struct nodo2 *sig;
};


//pilas
typedef struct nodo *pila;
typedef struct nodo *lista;
typedef struct nodo2 *num;
typedef struct nodo *fija;

//Funciones
void push( pila &p, char a);
char pop( pila &p);
int pop2(num &p);
char pop3( lista &p);
void agregar( lista &, char a);
void eliminar( pila &M);
int  prioridadInfija( char a);
int  prioridadpila( char a);
void mostrar( lista &list);
void controlador( pila &p, char cad[]);
int resul( lista l);
int numero(char cad[50],int j);

//push = Carga en la pila
//pop  = Descarga de la pila

main(void)
{   
    pila p = NULL;
    pila M = NULL;
    lista list = NULL;
    char cad[max], c;
    int tam;
	int f;
    do
    {
        printf("\n\nIngrese la Expresion Algebraica:   ");
        scanf("%50s",cad);

        if( M != NULL)
        { 
          eliminar(M); 
        }
        controlador(M,cad);
        
    } while(M != NULL);

    printf("\nExpresion Algebraica Infija:  %s\n",cad);

    tam=strlen(cad);

    for(int i = 0; i < tam; i++)
    {
        if( (cad[i]>='0' && cad[i]<='9') || (cad[i]>='a' && cad[i]<='z') || cad[i]==' ' )
        {
          agregar(list,cad[i]);
        }

        if(cad[i]=='+' || cad[i]=='-' || cad[i]=='*' || cad[i] =='/' || cad[i]=='(')
        {
          agregar(list,' ');

          if(p==NULL)
          {
            push(p,cad[i]);
          }
          else
          {
            if(prioridadInfija(cad[i])>prioridadpila(p->info))
            {
              push(p,cad[i]);
            }
            else
            {   
              if(prioridadInfija(cad[i])==prioridadpila(p->info))
            {
              c=pop(p);
              agregar(list,c);
              push(p,cad[i]);
            }
            else
            {
              c=pop(p);
              agregar(list,c);
            }
            }
          }
        }
        
        if(cad[i] == ')')
        {
            while( p->info != '(' && p != NULL )
            {
              c=pop(p);
              agregar(list,c);
            }

            if( p->info == '(')
            {
              c=pop(p);
            }
        }
    }
    
    while( p!=NULL )
    {
      c=pop(p);
      agregar(list,c);
    }

    mostrar(list);
    
    f=resul(list);
	
	printf("\n\nEl resultado es: %d",f);
	
    printf("\n\n");
    return 0;
}

//Controlar la apertura y cierre de parentesis
void controlador( pila &p, char cad[])
{
  pila aux;
  int i = 0;

  while( cad[i] != '\0')
  {
    if( cad[i]=='(' )
    {
      push(p,cad[i]);
    }
    else if( cad[i]==')' )
    {
      aux = p;

      if( aux!=NULL )
      {
        if( cad[i]==')' )
        {
          if( aux->info=='(')
          {
            pop(p);
          }
        }
      }
      else
      {
        push(p,cad[i]);
      }
    }

    i++;
  }

  if(p==NULL)
  {
    printf("\nLa Expresion Algebraica esta Correcta!!!\n");
  }
  else
  {
    printf("\nLa Expresion Algebraica esta Incorrecta!!!\n");
  }
}

//agregar elementos a la pila
void push(pila &p,char a)
{
    pila q=new struct nodo;
    q->info=a;
    q->sig=p;
    p=q;
}

void push2(num &p,int a)
{
    num q=new struct nodo2;
    q->info=a;
    q->sig=p;
    p=q;
}


//Descargar elementos de la pila 
char pop(pila &p)
{
    int n;
    pila aux;

    n=p->info;
    aux=p;
    p=p->sig;
    delete(aux);

    return n;
}

int pop2(num &p)
{
    int n;
    num aux;

    n=p->info;
    aux=p;
    p=p->sig;
    delete(aux);

    return n;
}

char pop3(lista &p)
{
	char n;
    lista aux;

    n=p->info;
    aux=p;
    p=p->sig;
    delete(aux);

    return n;
}

//eliminar pila
void eliminar(pila &M)
{
  pila aux;

  if(M != NULL)
  {
    while(M!=NULL)
    {
      aux=M;
      M=M->sig;
      delete(aux);
    }
  }
}

//agregar elemntos a la lista
void agregar(lista &list,char a)
{
    lista t, q = new(struct nodo);

    q->info  = a;
    q->sig = NULL;

    if( list==NULL )
    {
      list = q;
    }
    else
    {
      t = list;

      while( t->sig!=NULL )
      {
        t = t->sig;
      }

      t->sig = q;
    }
}

//Mostrar lista
void mostrar( lista &list)
{
  pila aux;
  aux=list;

  if(list!=NULL)
  {
    printf("\nExpresion Algebraica Posfija:   ");
  
    while(aux!=NULL)
    {
      printf("%c",aux->info);
      aux = aux->sig;
    }
  }
}

//Prioridad de los operadores de la Cadena
int prioridadInfija(char a)
{
  if( a=='*')
  {
    return 2;
  }
  if( a=='/')
  {
    return 2;
  }
  if( a=='+')
  {
    return 1;
  }
  if( a=='-')
  {
    return 1;
  }
  if( a=='(')
  {
    return 5;
  }
}

//Prioridad de los operadores de la pila
int prioridadpila(char a)
{
  if( a=='*')
  {
    return 2;
  }
  if( a=='/')
  {
    return 2;
  }
  if( a=='+')
  {
    return 1;
  }
  if( a=='-')
  {
    return 1;
  }
  if( a=='(')
  {
    return 0;
  }
}

int operacion(char a,int b,int c)
{
  if( a=='*')
  {
  	return b*c;
  }
  if( a=='/')
  {
    return c/ b;
  }
  if( a=='+')
  {
    return b + c;
  }
  if( a=='-')
  {
    return c - b;
  }
}

//Calcula el resultado de la pila
int resul(lista l)
{
  int resultad=0;
  int i = 0;
  int a;
  char c;
  int t;
  int num1,num2;
  int n=0;
  char nom[50];
  num numeros=NULL;
  
  while(l != NULL)
  {
  	c = pop3(l);
  	
  	if( c>=48 && c<=57)
  	{
  		while( (c>=48 && c<=57) )
    	{
		   	nom[i]=c;
			c= pop3(l);
    		i++;
		}
		
		n=numero(nom,i);
		
		i=0;
		push2(numeros,n);
	}
    
	if((c=='+') || (c =='-') || (c=='*') || (c=='/'))
   	{
   		num1=pop2(numeros);
		num2=pop2(numeros);    
		
		int num3=operacion(c,num1,num2);	
   		push2(numeros,num3);
   	}
  }
 
  return pop2(numeros);
}


int numero (char cad[50],int j)
{
	int n=0;
    int i=0;
    int a=0;
    int g;
    char c;
    j=j-1;
   
    c=cad[i];

	while(j>=0)
	{
		if(j==0)
		{
			g=1;
		}
		else
		{
			g=pow(10,j);
	    }
	
		n = (c -'0') * g;
	
   		i++;
		j=j-1;
		c=cad[i];
	
		a=a+n;
	}
    
    return a;
}
