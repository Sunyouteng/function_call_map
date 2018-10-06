/********************************************************************
 * File: instrument.c
 *
 * Instrumentation source -- link this with your application, and
 *  then execute to build trace data file (trace.txt).
 *
 * Author: M. Tim Jones <mtj@mtjones.com>
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* Function prototypes with attributes */
void main_constructor( void )
	__attribute__ ((no_instrument_function, constructor));

void main_destructor( void )
	__attribute__ ((no_instrument_function, destructor));

void __cyg_profile_func_enter( void *, void * ) 
	__attribute__ ((no_instrument_function));

void __cyg_profile_func_exit( void *, void * )
	__attribute__ ((no_instrument_function));


static FILE *fp;

/*
fopen函数原型  FILE *fopen(const char *filename, const char *mode);
w  - open for writing (file need not exist)  如果文件不存在，就创建一个新的。
w+ - open for reading and writing (overwrite file)
a  - open for appending (file need not exist)
a+ - open for reading and writing (append if file exists)
r  - open for reading
r+ - open for reading and writing, start at beginning
对于 “w”和“a”权限来说，如果存在这个名称为 “filename”的文件，那么就直接操作那个文件，如果没有就创建新的文件。其它的操作filename必须存在
*/
void main_constructor( void )
{
  fp = fopen( "trace.txt", "w" );
  if (fp == NULL) exit(-1);
}


void main_deconstructor( void )
{//文件用完之后需要关闭，
  fclose( fp );
}
/*
fprintf()
函数原型： int fprintf(FILE *stream, const char *format, ...);
功能： 将 format格式对应的内容输出到 stream指向的文件中。
举例：fprintf( stream, "%s%c", s, c ); 
*/
	
void __cyg_profile_func_enter( void *this, void *callsite )
{
  fprintf(fp, "E%p\n", (int *)this);//%p一般以十六进制整数方式输出指针的值..Hexadecimal
}//only print the present function's address. not print the caller.


void __cyg_profile_func_exit( void *this, void *callsite )
{
  fprintf(fp, "X%p\n", (int *)this);
}

