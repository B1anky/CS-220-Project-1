#include "base64.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

char * b64decode(char b64[],int len);
static char stringResult[MAX_MSG_LENGTH];

int main(int argc, char **argv) {
	char inputMsg[MAX_MSG_LENGTH] = "";
	int b64i=0;
	char in;
	while(1) {
		in=getchar();
		if (feof(stdin)) break;
		inputMsg[b64i++]=in;
	}
	assert(b64i<MAX_MSG_LENGTH);

	char * result=b64decode(inputMsg,b64i);
	int stri=0;
	for(stri=0; result[stri]; stri++) {
		putchar(result[stri]);
	}
	return 0;
}

char * b64decode(char b64[],int len) {
	bool* binaryArr = (bool*) malloc(len*8);
	int curlet = 0, outChar = 0, letCount = 0, i = 0, j = 0;
	for (i = 0; i < len; ++i)
		if(b64[i] != '=')	
			for(j =5; j>=0; j--)
				binaryArr[curlet++] = (b64Index(b64[i]) & ( 1 << j )) >> j;
	for (i = 0; i < curlet; ++i){
		if(i % 8 == 0 && i != 0){
			stringResult[letCount++] = outChar;
			outChar = 0;
			if(letCount == (curlet/8))break;
		}
		outChar = outChar*2 + binaryArr[i];
	}
	free(binaryArr);
	stringResult[++letCount]='\0';
	return stringResult;
}