#include<gmp.h>
#include<stdio.h>
#include<stdlib.h>
// here a and b is variable who's Gcd we have to find
// d contains gcd(a,b)
// x and y will contain values such that they holds => x* a+y*b=gcd(a,b)

int main()
{
   mpz_t a,b,x,y,d,inv;

   mpz_inits(a,b,x,y,d,inv,NULL);
   gmp_printf("\n\nEnter the value of element X : ");
   gmp_scanf("%Zd",a);

   gmp_printf("\nEnter the value of modulas P : ");
   gmp_scanf("%Zd",b);

   mpz_gcdext(d,x,y,a,b);
   gmp_printf("We have to find value of X such that :\n");
   gmp_printf("X = ( %Zd ^ -1) mod ( %Zd) \n ",a,b);

   if(mpz_cmp_ui(d,1)==0)
   {
      gmp_printf("\nThe Value of X is equal to  => %Zd \n",x);
   }
   else
   {
      gmp_printf("\nInverse Modulas (%Zd) of element %Zd Doesn't Exist\n ",a);
   
   }
 
}
