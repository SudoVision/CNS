#include<gmp.h>


int main()
{
	mpz_t a,b,c;
	mpz_inits(a,b,c,NULL);
	gmp_printf("\nEnter the value for a\n");
	gmp_scanf("%Zd",a);
	gmp_printf("\nEnter the value for b\n");
	gmp_scanf("%Zd",b);
	
	if(mpz_cmp(a,b)>0) gmp_printf("\n\na is greater number\n");
	else gmp_printf("\n\nb is greater number\n");
return 0;
}


