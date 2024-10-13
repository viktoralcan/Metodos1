#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <math.h>

void menu_funciones(int metodo);
void pedir_valores(int metodo, int opcion);
void metodo_biseccion(float (*func)(float), float a, float b, int max_iter, float tol, int metodo, int opcion);
void metodo_secante(float (*func)(float), float x0, float x1, int max_iter, float tol, int metodo, int opcion);
float validar_flotante(char* entrada);
int validar_entero(char* entrada);
float funcion1(float x);
float funcion2(float x);
float funcion3(float x);
float funcion4(float x);

void Lang(){
    
	struct lconv *lcPtr;
    setlocale(LC_ALL, "spanish");
    lcPtr = localeconv();
    lcPtr->decimal_point = ".";
    lcPtr->thousands_sep = ",";
    lcPtr->grouping = "3";
    
}

void Portada(){
    
	printf("\n\n\t\t\t\tUniversidad Nacional Aut�noma de M�xico\n");
    printf("\t\t\t\tFacultad de Estudios Superiores Acatl�n\n");
    printf("\t\t\t\t   Profesor: Teresa Carrillo Ram�rez\n");
    printf("\t\t\t\t  Integrantes:\n");
    printf("\t\t\t\t  Alcantara Mendez Victor Jesus\n");
    printf("\t\t\t\t  Gutierrez Baeza Luis Daniel\n");
    printf("\t\t\t\t  Soberanes Monroy Balam\n");
    printf("\t\t\t\t    Grupo: Extraordinario-Largo\n");
    printf("\t\t\t\t\t  M�todos Num�ricos I\n");
    printf("\t\t\t\t Programa 1\n\n\n");
    system("pause");
    
}

void menu_metodos(){
    
	int metodo;

    do{
    	system("cls");
        printf("MEN�\n");
        printf("1. Utilizar el m�todo de bisecci�n.\n");
        printf("2. Utilizar el m�todo de la secante.\n");
        printf("3. Salir.\n");
        printf("Escoja una opci�n: ");
        metodo=validar_entero("Ingrese una opci�n: ");

        switch(metodo){
            case 1:
                printf("M�todo de Bisecci�n seleccionado.\n");
                menu_funciones(metodo);
                break;
            case 2:
                printf("M�todo de la Secante seleccionado.\n");
                menu_funciones(metodo);
                break;
            case 3:
                printf("Finalizando el programa.\n");
                exit(0);
            default:
                printf("Por favor, escoja una opci�n v�lida.\n");
                system("pause");
        }
    } while (metodo!=3);
    
}

void menu_funciones(int metodo){
    
	int opcion;
    
	do{
		system("cls");
		printf("Seleccione la funci�n a desarrollar con el m�todo %d:\n",metodo);
        printf("1. f(x) = x^2 cos(x) - 2x\n");
        printf("2. f(x) = (6 - (2 / x^2))(e^(2+x)/4) + 1\n");
        printf("3. f(x) = x^3 - 3sin(x^2) + 1\n");
        printf("4. f(x) = x^3 + 6x^2 + 9.4x + 2.5\n");
        printf("5. Volver al men� anterior\n");
        opcion=validar_entero("Seleccione una opci�n: ");
        
        if(opcion>=1 && opcion<=4){
			pedir_valores(metodo, opcion);
		}else{ 
			printf("Funci�n no v�lida.\n"); 
		}
	}while(opcion!=5);
	    
}

void pedir_valores(int metodo, int opcion){
    
	int max_iter;
    float tol, a=0, b=0, x0=0, x1=0;
    float (*f)(float);  // Puntero a funci�n

    switch (opcion){
        case 1: 
			f = funcion1; 
			break;
        case 2: 
			f = funcion2; 
			break;
        case 3: 
			f = funcion3; 
			break;
        case 4: 
			f = funcion4; 
			break;
    }

    if(metodo==1){
    	max_iter=validar_entero("\n\nN�mero m�ximo de iteraciones: ");    
		tol=validar_flotante("Tolerancia (ej. 0.01): ");
        a=validar_flotante("Ingrese el valor de a: ");
        b=validar_flotante("Ingrese el valor de b: ");
        metodo_biseccion(f, a, b, max_iter, tol, metodo, opcion);
    }else if(metodo==2){
    	max_iter=validar_entero("\n\nN�mero m�ximo de iteraciones: ");    
		tol=validar_flotante("Tolerancia (ej. 0.01): ");
        x0=validar_flotante("Ingrese el valor de x_(n-1): ");
        x1=validar_flotante("Ingrese el valor de x_(n): ");
        metodo_secante(f, x0, x1, max_iter, tol, metodo, opcion);
    }
}

float funcion1(float x){ return (pow(x,2) * cos(x)) - (2 * x); }
float funcion2(float x){return (6 - (2 / pow(x, 2))) * (exp(2 + x) / 4) + 1;}
float funcion3(float x){ return pow(x, 3) - 3 * sin(pow(x, 2)) + 1; }
float funcion4(float x){ return pow(x, 3) + 6 * pow(x, 2) + (9.4 * x) + 2.5; }

void pregunta_nuevo(int metodo, int opcion){
    
	int opt3;

    do {
        printf("�Qu� desea hacer?\n");
        printf("1. Elegir otro intervalo\n");
        printf("2. Regresar al men� de funciones\n");
        printf("3. Salir\n\n");
        opt3 = validar_entero("Ingrese una opci�n: ");

        switch(opt3){
            case 1:
                pedir_valores(metodo, opcion);
                break;
            case 2:
                return;
            case 3:
                printf("Finalizando el programa.\n");
                exit(0);
            default:
                printf("Por favor, escoja una opci�n v�lida.\n");
                system("pause");
        }
    } while (opt3 != 3);
    
}

void metodo_biseccion(float(*func)(float), float a, float b, int max_iter, float tol, int metodo, int opcion){
    
	int i;
    float fa=func(a), fb=func(b);

    if(fa*fb>0){
    	printf("-----------------------------------------------------------------------\n");
        printf("El intervalo no contiene una ra�z.\n\n");
        pregunta_nuevo(metodo,opcion);
		system("pause");
        return;
	}
    
	printf("-----------------------------------------------------------------------\n");
    printf("Iteraci�n\ta\tb\tpm\tf(pm)\t|b-a|\n");
    
	for (i=0;i<max_iter;i++){
        float pm = (a + b) / 2;
        float fpm = func(pm);
		printf("-----------------------------------------------------------------------\n");
        printf("%d\t%f\t%f\t%f\t%f\t%f\n", i, a, b, pm, fpm, fabs(b - a));

        if (fabs(fpm) < tol || fabs(b - a) < tol) {
        	printf("\n\n-------------------------\n");
            printf("Ra�z encontrada: %f\n", pm);
            printf("Se encontr� la ra�z en la iteraci�n #%d con una tolerancia de %f.\n",i+1,tol); 
            printf("-------------------------\n\n");
            pregunta_nuevo(metodo,opcion);
            system("pause");
            return;
        }

        if(fa*fpm<0){
            b=pm;
        }else{
            a=pm;
        }
    }
    
    printf("-----------------------------------------------------------------------\n");
    printf("\n\nNo se encontr� ra�z en %d iteraciones.\n\n", max_iter);
    pregunta_nuevo(metodo,opcion);
    system("pause");
    
}

void metodo_secante(float (*func)(float), float x0, float x1, int max_iter, float tol, int metodo, int opcion){
	
    int i;
    
    printf("-----------------------------------------------------------------------\n");
    printf("Iteraci�n\tx_(n-1)\tx_(n)\tf(x_(n-1))\tf(x_(n))\tError Relativo porcentual\n");

    for(i=0;i<max_iter;i++){
        float f0 = func(x0);
        float f1 = func(x1);

        if(fabs(f1-f0)<1e-6){
        	printf("-----------------------------------------------------------------------\n");
            printf("\n\nDivisi�n por cero.\n\n");
            pregunta_nuevo(metodo,opcion);
            system("pause");
            return;
        }

        float x2=x1-(f1*(x1-x0)/(f1-f0));
        float error=fabs((x2-x1)/x2)*100;
	
		printf("-----------------------------------------------------------------------\n");
        printf("%d\t%f\t%f\t%f\t%f\t%f\n", i, x0, x1, f0, f1, error);

        if (error<tol){
        	printf("\n\n-------------------------\n");
            printf("Ra�z encontrada: %f\n", x2);
            printf("Se encontr� la ra�z en la iteraci�n #%d con una tolerancia de %f%.\n",i+1,tol); 
            printf("-------------------------\n\n");
            pregunta_nuevo(metodo,opcion);
            system("pause");
        }

        x0=x1;
        x1=x2;
    }
    printf("\n\nNo se encontr� ra�z en %d iteraciones.\n\n", max_iter);
    pregunta_nuevo(metodo,opcion);
    system("pause");
    
}

int validar_entero(char* mensaje){
    char buffer[100];
    int valor;

    while(1){
        printf("%s",mensaje);
        scanf("%s",buffer);
        if(sscanf(buffer,"%d",&valor)==1) return valor;
        printf("Entrada inv�lida. Intente de nuevo.\n");
    }
}

float validar_flotante(char* mensaje){
    char buffer[100];
    float valor;

    while(1){
        printf("%s",mensaje);
        scanf("%s",buffer);
        if(sscanf(buffer,"%f",&valor)==1) return valor;
        printf("Entrada inv�lida. Intente de nuevo.\n");
    }
}

int main(){
    Lang();
    Portada();
    menu_metodos();
    return 0;
}

