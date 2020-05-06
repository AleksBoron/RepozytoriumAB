#include "winbgi2.h"
#include "rk4.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


//szukamy rozwiazania rownania rozniczkowego {1} y' = f(y, t), gdzie y = y(t)
//warunek cauchiego jest dany y(t0) = y_0

double lambda = 10;//zmienna do pierwszego przykladu
double y_0 = 1; //warunek cauchiego
double t0 = 0; //warunek cauchiego

double fun(double t, double y); //funkcja opisujaca prawa strone rowniania {1}
double y_an(double t, double t0, double y_0); //policzone rozwiazanie na kartce

int main()
{
	double h = 0.01; //krok calkowania
	double t_max = 0; //prawa krawedz przedzialu
	double eps_eul, eps_rk4;//bledy w obu metodach

					printf("Podaj prawa krawedz przedzialu\n");
					scanf("%lf", &t_max);
	graphics(800, 600);


			scale(0, 0, t_max, 3.5);
			title("Blad Eul. (bialy) i rk4 (zielony)", "", "");
	
FILE *p;
p = fopen("Wyniki.txt","w");

		if(p == NULL)
	{
		printf("Blad otwarcia pliku\n");
		exit(-1);
	}

	//metoda Eulera
	double t = t0;
	double y = y_0;
	fprintf(p, "Metoda Eulera:\n");

	for(double j = 0; j < 7; j++)
	{
	for (int i = 1; i <= pow(2, j); i++)
	{
		double k = pow(2, j);//ten kawa³ek s³uzy do wpisywania do pliku
		fprintf(p, "\nPrzypadek gdy liczba krokow rowna sie %.1lf\n", k);
		fprintf(p, "Dlugosc kroku : %.2lf\n", h);
		fprintf(p, "\nKrok %d\n", i);
		t += h;  //tu sie dzieje metoda
			fprintf(p, "t = %lf", t);
		y += h*fun(t, y);
			fprintf(p, "\ny = %lf\n", y-1);
		
		

		
	}
		eps_eul = fabs(y - y_an(t, t0, y_0)) /fabs(y_an(t, t0, y_0)); // blad 
		fprintf(p, "Wzgledna wartosc bledu: %lf\n", eps_eul);
	t = 0;
	y = 1;
	}

	for (int i = 0; i < t_max/h; i++)//a ten kawalek do rysowania wykresu
	{
		t += h;  //tu sie dzieje metoda
		y += h*fun(t, y); 
		
		
		eps_eul = fabs(y - y_an(t, t0, y_0)) / fabs(y_an(t, t0, y_0)); // blad 
	
			circle(t, eps_eul, 1);
	}


	//metoda rk4
	t = t0;
	y = y_0;
	fprintf(p, "\n\nMetoda Rungego - Kutty 4-ego rzedu");

	for(double j = 0; j < 7; j++)
	{
	for (int i = 1; i <= pow(2, j); i++)
	{
		double k = pow(2, j);//ten kawa³ek s³uzy do wpisywania do pliku
		fprintf(p, "\nPrzypadek gdy liczba krokow rowna sie %.1lf\n", k);
		fprintf(p, "Dlugosc kroku : %.2lf\n", h);
		fprintf(p, "\nKrok %d\n", i);

		t += h; //tu metoda

		fprintf(p, "t = %lf\n", t);

		y = rk4(t, y, h, fun);

		fprintf(p, "y = %lf\n", y);
	
	}
			eps_rk4 = fabs(y - y_an(t, t0, y_0)) /fabs(y_an(t, t0, y_0));//blad
			fprintf(p, "Wzgledna wartosc bledu: %lf\n", eps_rk4);
	t = 0;
	y = 1;
	}
	
	for (int i = 0; i < t_max/h; i++)//a ten kawalek do rysowania wykresu
	{
		t += h; 
		y = rk4(t, y, h, fun);
		
		eps_rk4 = fabs(y - y_an(t, t0, y_0)) / fabs(y_an(t, t0, y_0));//blad
		
			setcolor(0.6);
			circle(t, eps_rk4, 1);
	}
	
	wait();
	fclose(p);
	return 0;
}


double fun(double t, double y)
{
	return lambda*y;
	//return 100*(sin(t)-y);
}
double y_an(double t, double t0, double y0) 
{
	return y0*exp(lambda*(t-t0));
	//return (sin(t)-0.01*cos(t)+0.01*exp(-100.*t))/1.0001;
}
