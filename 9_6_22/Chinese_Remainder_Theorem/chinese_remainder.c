#include<gmp.h>
#include<stdio.h>
#include<stdlib.h>

void find_x(mpz_t M, mpz_t x, mpz_t m)
{
    mpz_t i,tmp;
    mpz_inits(i,tmp,NULL);
    mpz_set_ui(i,0);
    for(;mpz_cmp(i,m)<0; mpz_add_ui(i,i,1))
    {
        mpz_mul(tmp,M,i);
        mpz_mod(tmp,tmp,m);
        if(mpz_cmp_ui(tmp,1)==0)
        {
            mpz_set(x,i);
            break;
        }
    }
}

int main()
{
    int n;
    gmp_printf("\nEnter the number of conditions\n");
    scanf("%d",&n);

    mpz_t *a = (mpz_t *) malloc(sizeof(mpz_t)*n);
    mpz_t *m = (mpz_t *) malloc(sizeof(mpz_t)*n);
    mpz_t *x = (mpz_t *) malloc(sizeof(mpz_t)*n);
    mpz_t *M = (mpz_t *) malloc(sizeof(mpz_t)*n);

    for(int i=0; i<n; i++) {mpz_inits(a[i],m[i],x[i],M[i],NULL);}

    gmp_printf("\nEnter the a and m such that X congruent to a modulo m\n");
    mpz_t M_;
    mpz_inits(M_,NULL);
    mpz_set_ui(M_,1);

    for(int i=0; i<n; i++)
    {
        gmp_scanf("%Zd",a[i]);
        gmp_scanf("%Zd",m[i]);
        mpz_mul(M_,M_,m[i]);
    }
    gmp_printf("\na array :\n");
    for (int i = 0; i < n; i++)
    {
        gmp_printf("%Zd\t", a[i]);
    }
    gmp_printf("\n");
    gmp_printf("\nm array :\n");
    for (int i = 0; i < n; i++)
    {
        gmp_printf("%Zd\t", m[i]);
    }
    gmp_printf("\n");
    gmp_printf("\nM = %Zd\n",M_);
    gmp_printf("\nM array :\n");
    for(int i=0; i<n; i++)
    {
        mpz_fdiv_q(M[i],M_,m[i]);
        gmp_printf("%Zd\t",M[i]);
        find_x(M[i],x[i],m[i]);
    }

    gmp_printf("\nx array :\n");
    for(int i=0; i<n; i++)
    {
        gmp_printf("%Zd\t", x[i]);
    }
    gmp_printf("\n");
    mpz_t tmp,sum;
    mpz_inits(tmp,sum, NULL);
    
    mpz_set_ui(sum, 0);

    for(int i=0; i<n; i++)
    {
        // gmp_printf("\n%Zd",sum);
        mpz_set_ui(tmp, 1);
        mpz_mul(tmp,a[i],x[i]);
        mpz_mul(tmp,tmp,M[i]);
        mpz_add(sum,tmp,sum);
    }

    mpz_mod(sum,sum,M_);
    gmp_printf("\nThe number is : \n%Zd\n",sum);

    return 0;
}