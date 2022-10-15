#include<gmp.h>
#include<time.h>
#include<math.h>
#include<stdio.h>

int main()
{
    mpz_t p;
    mpz_inits(p,NULL);
    gmp_printf("\nEnter the number \n");
    gmp_scanf("%Zd",p);

    gmp_randstate_t state;
	gmp_randinit_mt(state);
	unsigned long seed;
	
	int bits = 10;
    mpz_t a;
	mpz_inits(a,NULL);
	
    mpz_t ret;
    mpz_inits(ret,NULL);

    int flag = 1;

    long int zero = 0;

    for(int i=0; i<50; i++)
    {
        seed = time(NULL);
        gmp_randseed_ui(state,seed);
        mpz_rrandomb(a,state,bits);

        mpz_powm (ret,a,p,p);
        mpz_mod(a,a,p);
        mpz_sub(ret,ret,a);

        mpz_mod(ret,ret,p);
        if(mpz_cmp_ui(ret,zero)!=0) 
        {
            flag = 0;
            break;
        }
        bits += 2;
    }
    if(flag) gmp_printf("\nGiven number is prime\n");
    else gmp_printf("\nGiven number is composite\n");

    return 0;
}