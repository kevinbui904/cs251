/* complex.c
Written by Thien K. M. Bui
Last modified 01/26/22
*/

#include <stdio.h>

struct Complex
{
    double real;
    double imaginary;
};

/* complex_product
multiple two complex numbers together
*/
struct Complex complex_product(struct Complex c1, struct Complex c2)
{
    double prod_real = c1.real * c2.real - c1.imaginary * c2.imaginary;
    double prod_imaginary = c1.real * c2.imaginary + c2.real * c1.imaginary;

    struct Complex product;
    product.real = prod_real;
    product.imaginary = prod_imaginary;

    return product;
}

/*describe_complex_number
pretty print real and imaginary part of a complex number
*/
void describe_complex_number(struct Complex complex)
{
    printf("Complex number: %2.2f + %2.2f i\n", complex.real, complex.imaginary);
}

int main()
{
    struct Complex c1, c2;

    printf("Enter real part of c1: ");
    scanf("%lf", &c1.real);
    printf("Enter imaginary part of c1: ");
    scanf("%lf", &c1.imaginary);

    printf("Enter real part of c2: ");
    scanf("%lf", &c2.real);
    printf("Enter imaginary part of c2: ");
    scanf("%lf", &c2.imaginary);

    struct Complex product = complex_product(c1, c2);
    describe_complex_number(product);
}