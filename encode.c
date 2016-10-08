#include "base64.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

char * b64encode(char string[],int len);
char convertTo64(char sixBitNum);
static char b64Result[MAX_MSG_LENGTH];
int getIthBit(int num, int i);

int main(int argc, char **argv) {
	char inputMsg[MAX_MSG_LENGTH] = "";
	int stri=0;
	char in;
	while(1) {
		in=getchar();
		if (feof(stdin)) break;
		inputMsg[stri++]=in;
	}
	inputMsg[stri]=0;
	assert(stri<MAX_MSG_LENGTH);

	char * result = b64encode(inputMsg,stri);
	int b64i=0;
	for(b64i=0; result[b64i]; b64i++) {
		putchar(result[b64i]);
	}
	printf("\n");	
	return 0;
}

char convertTo64(char sixBitNum){
	if(sixBitNum < 26){
		sixBitNum = sixBitNum + 'A';
	}else if(sixBitNum < 52){
		sixBitNum = sixBitNum - 26 + 'a';
	}else if(sixBitNum  < 62){
		sixBitNum = sixBitNum - 52 + '0';
	}else if(sixBitNum > 62){
		sixBitNum = sixBitNum - 62 + '+';
	}else{
		sixBitNum = '=';
	}

	return sixBitNum;
}

int getIthBit(int n, int i){
	return (n & ( 1 << i )) >> i;
}

char * b64encode(char string[ ], int len) {
	bool* myconvert  = 0;
	int curlet = 0, numbuf = 0, c = 0, i = 0, j =0;

	if( (len%3) == 0){}		
	else if( (len%3) == 2){
		len++;numbuf = 1;
	}
	else{
		len+=2;numbuf = 2;
	}
	myconvert = (bool*) malloc(len * 8);

	for(i=0; i<len; i++)
		for(j =7; j>=0; j--){
			bool ou = getIthBit(string[i], j);
			myconvert[c] =(ou);
			c++;
		}
	if( (len%3) == 0){/*do nothing*/}
	else if( (len%3) == 2){
		for (i = 0; i < 2; ++i)
			myconvert[c++] = 0;
		for (i = 0; i < 8; ++i)
			myconvert[c++] = -1;
	}
	else{
		for (i = 0; i < 4; ++i)
			myconvert[c++] = 0;
		for (i = 0; i < 14; ++i)
			myconvert[c++] = -1;
	}

	char outChar = 0;
	int negcount = 0;
	for(i=0; i<len*8; i++){
		if(i%6==0 && i != 0){
			b64Result[curlet++] = convertTo64(outChar);
			outChar = 0;
		}
		if( i >= (len*8) - (numbuf*6) )	{
			negcount += 1;
			continue;
		}
		outChar *= 2;
		outChar += myconvert[i];
	}
	if(negcount >= 6){	
		if(numbuf == 2){
			curlet--;
			b64Result[++curlet] = '=';
		}
		b64Result[curlet] = '=';
	}
	else
		b64Result[curlet] = convertTo64(outChar);
	b64Result[++curlet] = '\0';
	free(myconvert);
	return b64Result;
}