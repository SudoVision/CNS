#include<gmp.h>
#include<time.h>
#include<math.h>
#include<stdio.h>


int main()
{
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	unsigned long seed = time(NULL);
	gmp_randseed_ui(state,seed);
	
	int bits = 1024;
	gmp_printf("\nNumber of bits of the number : %d\n",bits);
	mpz_t a;
	mpz_inits(a,NULL);
	mpz_rrandomb(a,state,bits);
	gmp_printf("\nChecking For primality\n");
	
	int reps = 50;
	int ret = mpz_probab_prime_p(a,reps);
	
	gmp_printf("\nNumber of Reps : %d\n",reps);
	
	int cnt = 0;
	
	while(ret!=2)
	{
		mpz_nextprime(a,a);
		ret = mpz_probab_prime_p(a,reps);
		//gmp_printf("%d\n",ret);
		cnt++;
		if(cnt>10)break;
	}
	
	double prob = pow(4,-reps)*10e30;
	
	if(ret == 2) gmp_printf("\nDefinitely Prime :\n%Zd\n",a);
	else if (ret ==1) gmp_printf("\nProbably Prime with asymptomatic probability of failure lesser than %f*10e-30:\n\n%Zd\n",prob,a);
	return 0;
}
