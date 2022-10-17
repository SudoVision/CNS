#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void generate_prime(mpz_t p)
{
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed = time(NULL);
    gmp_randseed_ui(state, seed);

    int bits = 1024;
    mpz_rrandomb(p, state, bits);
    mpz_nextprime(p,p);
    return;
}

void generate_e(mpz_t e, mpz_t phi)
{
    mpz_set_d(e,2);
    mpz_t gcd;
    mpz_init(gcd);
    for(;mpz_cmp(e,phi)<0;mpz_add_ui(e,e,1))
    {
        mpz_gcd(gcd,e,phi);
        if(mpz_cmp_ui(gcd,1)==0) break; 
    }
    return;
}

int main()
{
    mpz_t p,q,phi,e,public_key, private_key;
    mpz_inits(p,q,e,phi,public_key,private_key,NULL);

    //generate the prime numbers
    generate_prime(p);
    generate_prime(q);

    mpz_mul(public_key,p,q);
    gmp_printf("\nPublic Key : \n%Zd\n",public_key);
    mpz_sub(phi,public_key,p);
    mpz_sub(phi,phi,q);
    mpz_add_ui(phi,phi,1);

    generate_e(e,phi);

    mpz_invert(private_key,e,phi);
    gmp_printf("\nPrivate Key : \n%Zd\n", private_key);

    mpz_t pt, et;
    mpz_inits(pt,et,NULL);

    gmp_printf("\nEnter the number to be encrypted : ");
    gmp_scanf("%Zd",pt);
    mpz_powm(et,pt,e,public_key);
    gmp_printf("Encrypted : \n%Zd\n",et);
    mpz_powm(pt,et,private_key,public_key);
    gmp_printf("\nPlain Text Decrypted: \n%Zd\n",pt);

    return 0;
}