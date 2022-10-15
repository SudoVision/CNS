#include<gmp.h>

int main()
{
	mpz_t a,b,temp;
	mpz_inits(a,b,temp,NULL);
	gmp_printf("\nEnter the value for a\n");
	gmp_scanf("%Zd",a);
	gmp_printf("\nEnter the value for b\n");
	gmp_scanf("%Zd",b);
	
	while(mpz_cmp_ui(b,0)!=0)
	{
//for legibility of output the additional verbose printing of the reminder is commented out
		//gmp_printf("\na = %Zd",a);
		//gmp_printf("\nb = %Zd",b);
		mpz_set(temp,b);
		mpz_mod(b,a,b);
		mpz_set(a,temp);
		//gmp_printf("\nreminder = %Zd",b);
	}
	
	gmp_printf("\nGCD : %Zd\n",temp);
	return 0;
}
