#include <stdio.h>
int gcd(int a, int b);
void change(int* a, int* b);
int main() {
    int a,b,z;
    printf("Inserire i due numeri di cui si vuole trovare il MCD:\n");
    scanf("%d %d",&a,&b);
    z=gcd(a,b);
    printf("MCD = %d\n",z);
    return 0;
}
int gcd(int a, int b){
    if(a==b)
        return a;
    if(a<b)
        change(&a,&b);
    if(((a%2)==0) && ((b%2)==0))
        return 2*gcd(a/2,b/2);
    else if(((a%2)!=0) && ((b%2)!=0))
        return gcd((a-b)/2,b);
    else if(((a%2)!=0) && ((b%2)==0))
        return gcd(a,b/2);
    else if(((a%2)==0) && ((b%2)!=0))
        return gcd(a/2,b);
}
void change(int* a, int* b){
    int temp;
    temp=*b;
    *b=*a;
    *a=temp;
}