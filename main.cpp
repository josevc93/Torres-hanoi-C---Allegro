#include <allegro.h>
#include <stdlib.h>
#include "inicia.h"

class rectangulo{
 public:
  rectangulo(int a=0, int b=0, int c=0, int d=0, int e=0, int f=0);
  void pintar();
  void mover(int n, int lugar);
  void borrar(int n, int desplazamiento);
  int top(int origen);
 private:
  int x,y,x2,y2,color,actual;
};

rectangulo *r[6];

rectangulo::rectangulo(int a, int b, int c, int d, int e, int f){
 x = a;
 y = b;
 x2 = c;
 y2 = d;
 color = e;
 actual=f;
}

// Dibuja los rectangulos

void rectangulo::pintar()
{
 rectfill(screen,x,y,x2,y2,pallete_color[color]);
}

//Borramos un rectangulo

void rectangulo::borrar(int n, int desplazamiento)
{
   if(desplazamiento==0) //si desplazamiento es hacía arriba
    rectfill(screen,r[n]->x,r[n]->y,r[n]->x2,r[n]->y,pallete_color[0]);
   else if(desplazamiento==1) //a la derecha
    rectfill(screen,r[n]->x,r[n]->y,r[n]->x,r[n]->y2,pallete_color[0]);
   else if(desplazamiento==2) //a la izquierda
    rectfill(screen,r[n]->x2,r[n]->y,r[n]->x2,r[n]->y2,pallete_color[0]);
   else if(desplazamiento==3) //abajo
    rectfill(screen,r[n]->x,r[n]->y2,r[n]->x2,r[n]->y2,pallete_color[0]);
}

//Mover

void rectangulo::mover(int n, int lugar)
{
  int aux,aux2=0;

  // Movimiento hacia arriba

  while(r[n]->y2!=20)
  {
   r[n]->borrar(n,0);
   r[n]->y = r[n]->y - 1;
   r[n]->y2 = r[n]->y2 - 1;
   r[n]->pintar();
   rest(1); //velocidad
  }

  //Movimientos laterales

  if((r[n]->actual==0 && lugar==1) || (r[n]->actual==1 && lugar==2))  //lugar = destino
   aux = r[n]->x2 + 40 + n*20;
  else if(r[n]->actual==0 && lugar==2)
   aux = r[n]->x2 + 280 + n*20;
  else if((r[n]->actual==2 && lugar==1) || (r[n]->actual=1 && lugar==0))
   aux = r[n]->x - 40 - n*20;
  else if(r[n]->actual==2 && lugar==0)
   aux = r[n]->x - 280 - n*20;

   if(r[n]->actual==0 || (r[n]->actual==1 && lugar==2)){ //movimiento hacía la derecha
    while(r[n]->x!=aux){
     r[n]->borrar(n,1);
     r[n]->x = r[n]->x + 1;
     r[n]->x2 = r[n]->x2 + 1;
     r[n]->pintar();
     rest(1);
    }
    if(x>460)
     r[n]->actual = 2;
    else
     r[n]->actual = 1;
   }
   else{
    while(r[n]->x2!=aux){ //Movimiento hacía la izquierda
     r[n]->borrar(n,2);
     r[n]->x = r[n]->x - 1;
     r[n]->x2 = r[n]->x2 - 1;
     r[n]->pintar();
     rest(1);
    }
    if(x<240)
     r[n]->actual = 0;
    else
     r[n]->actual = 1;
   }

   //Movimiento hacia abajo

   while(r[n]->y!=340 && aux2==0)
  {
   r[n]->borrar(n,3);
   r[n]->y = r[n]->y + 1;
   r[n]->y2 = r[n]->y2 + 1;
   r[n]->pintar();
   for(int i=0;i<2;i++){if(((r[i]->y2-1)==r[n]->y) && (r[i]->x2 > r[n]->x2) && (r[i]->x < r[n]->x)) aux2=1;}
   rest(1); //velocidad
  }

  aux2=0;

}


 // Sirve para saber quien es el elemento superior de una pila

 int rectangulo::top(int origen)
 {
    int aux=0,top,n=2; //N numero de piezas
    while(aux==0){
     if((origen==0) && (r[n]->actual==0)){top=n; aux=1;}
     else if((origen==1) && (r[n]->actual==1)){top=n; aux=1;}
     else if((origen==2) && (r[n]->actual==2)){top=n; aux=1;}
     n--;
    }
    return top;
 }



// Inicializa todos los objetos

void inicializa_objetos()
{
 r[0] = new rectangulo (10,340,210,301,2,0); //grande
 r[1] = new rectangulo (20,300,200,261,3,0);
 r[2] = new rectangulo (30,260,190,221,4,0);

 /*r[0] = new rectangulo (10,340,210,301,2,0); //grande
 r[1] = new rectangulo (20,300,200,261,3,0);
 r[2] = new rectangulo (30,260,190,221,4,0);
 r[3] = new rectangulo (40,220,180,181,5,0);
 r[4] = new rectangulo (50,180,170,141,6,0);
 r[5] = new rectangulo (60,140,160,101,7,0); // x, y, x2, y2*/
}

//Aplicamos un algoritmo recursivo que resuelve el problema

void resolver(int n, int origen, int destino, int auxiliar)
{
    int top;
	if(n==1){
     top = r[0]->top(origen);
     r[top]->mover(top,destino);
	}
	else{
	 resolver(n-1,origen,auxiliar,destino);
	 top = r[0]->top(origen);
     r[top]->mover(top,destino);
	 resolver(n-1,auxiliar,destino,origen);
	}
}


int main()
{
    int n=2; //tres piezas
    inicia_allegro(700,350); //Dimensiones pantalla
    inicia_audio(70,70);
    install_mouse();
    install_timer();

    inicializa_objetos();
    for(int i=0;i<n;i++){r[i]->pintar();}
    resolver(3,0,2,1);
    system("cls");
    readkey();
    return 0;
}
END_OF_MAIN();

