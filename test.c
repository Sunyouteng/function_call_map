#include<stdio.h>
void say();
void say_();
void sayin();
int main()
{
int i =0;
say_();
sayin();
for (i =0;i<4;i++)
{

say();
}
return 0;
}
void say()
{
int i;
for (i=0;i<2;i++)
	sayin();

}
void sayin(){
printf ("hi");
}
void say_()
{
printf("say_");
}
