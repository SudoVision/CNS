#include <gmp.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

void power(mpz_t x, mpz_t y, mpz_t p, mpz_t result)
{
    mpz_t res,tmp;
    mpz_inits(res,tmp,NULL);
    mpz_set_ui(res,1);

    mpz_mod(x,x,p);
    while(mpz_cmp_ui(y,0)>0)
    {
        mpz_mod_ui(tmp, y, 2);
        if (mpz_cmp_ui(tmp, 1)==0)
        {
            mpz_mul(res,res,x);
            mpz_mod(res,res,p);
        }
        mpz_fdiv_q_ui(y,y,2);
        mpz_mul(x,x,x);
        mpz_mod(x,x,p);
    }
    mpz_set(result,res);
}

int millertest(mpz_t d, mpz_t n)
{
    mpz_t a,res,n_4,n_1;
    mpz_inits(a,res,n_4,n_1,NULL);

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed = time(NULL);
    gmp_randseed_ui(state, seed);

    mpz_urandomm(a,state,n);
    mpz_sub_ui(n_4,n,4);
    mpz_mod(a,a,n_4);
    mpz_add_ui(a,a,2);

    mpz_sub_ui(n_1,n,1);

    power(a,d,n,res);
    if(mpz_cmp_ui(res,1)==0 || mpz_cmp(res,n_1)==0) return 1;

    while(mpz_cmp(d,n_1)!=0)
    {
        mpz_mul(res,res,res);
        mpz_mod(res,res,n);
        mpz_mul_ui(d,d,2);

        if(mpz_cmp_ui(res,1)==0) return 0;
        if (mpz_cmp(res, n_1) == 0) return 1;
    }
    return 0;
}


int isprime(mpz_t n, mpz_t k)
{
    if(mpz_cmp_ui(n,1)<=0 || mpz_cmp_ui(n,4)==0) return 0;
    if(mpz_cmp_ui(n,3)<=0) return 1;

    mpz_t d,n_1,tmp;
    mpz_inits(d,n_1,tmp,NULL);
    mpz_sub_ui(n_1,n,1);
    mpz_set(d,n_1);

    mpz_mod_ui(tmp,d,2);
    while(mpz_cmp_ui(tmp,0)!=0)
    {
        mpz_fdiv_q_ui(d,d,2);
        mpz_mod_ui(tmp, d, 2);
    }

    mpz_t i;
    mpz_init_set_ui(i,0);
    for(;mpz_cmp(i,k)<0; mpz_add_ui(i,i,1))
    {
        if(!millertest(d,n)) return 0;
    }
    return 1;
    
}


int main()
{
    mpz_t n,k;
    mpz_inits(n,k,NULL);
    gmp_printf("\nEnter the Value of N : \n");
    gmp_scanf("%Zd",n);
    gmp_printf("Enter the value of k : \n");
    gmp_scanf("%Zd", k);

    if(isprime(n,k))
    gmp_printf("The number : \n%Zd\nis a prime number\n",n);
    else gmp_printf("The number is a composite number\n");
    return  0;
}