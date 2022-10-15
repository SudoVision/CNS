#include<gmp.h>
#include<stdio.h>
#include<stdlib.h>
#define LENGTH 3

// here a and b is variable who's Gcd we have to find
// d contains gcd(a,b)
// x and y will contain values such that they holds => x* a+y*b=gcd(a,b)

int main()
{
  mpz_t a,b,x,y,d;

  mpz_inits(a,b,x,y,d,NULL);
  gmp_printf("\nEnter the value of a-");
  gmp_scanf("%Zd",a);

  gmp_printf("\nEnter the value of b-");
  gmp_scanf("%Zd",b);

  mpz_gcdext(d,x,y,a,b);

  gmp_printf("a*%Zd + b*%Zd = %Zd \n",x,y,d);
  gmp_printf("gcd(a,b) = %Zd \n",d);
  
  gmp_printf("\nBezout Coefficient are => %Zd , %Zd\n",x,y);
  return 0;
}
