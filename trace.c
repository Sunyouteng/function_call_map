/********************************************************************
 * File: trace.c
 *
 * main function for the pvtrace utility.
 *
 * Author: M. Tim Jones <mtj@mtjones.com>
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "symbols.h"
#include "stack.h"


int main( int argc, char *argv[] )
{
  FILE *tracef;
  char type;
  unsigned int address;

  if (argc != 2) {

    printf("Usage: pvtrace <image>\n\n");
    exit(-1);

  }

  initSymbol( argv[1] );

  stackInit();

  tracef = fopen("trace.txt", "r");//open trace.txt to read.

  if (tracef == NULL) {
    printf("Can't open trace.txt\n");
    exit(-1);
  }

  while (!feof(tracef)) {
	
    fscanf( tracef, "%c0x%x\n", &type, &address );//scan every line, to get E or X and the address. this will loop many times.....

    if        (type == 'E') {

      /* Function Entry */

      addSymbol( address );// for every adress in every line, add its symbol  

      addCallTrace( address );

      stackPush( address );

    } else if (type == 'X') {

      /* Function Exit */

      (void) stackPop();

    }//elseif

  }//while

  emitSymbols();

  fclose( tracef );
  
  return 0;
}

