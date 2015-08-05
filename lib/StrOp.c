#include "StrOp.h"
#define NULL '\0'


void CopyString(char pcSource[], char pcDestination[]){

	unsigned char ucCharCounter;

	for(ucCharCounter = 0; NULL != pcSource[ucCharCounter]; ++ucCharCounter){
		pcDestination[ucCharCounter] = pcSource[ucCharCounter];
	}
	pcDestination[ucCharCounter] = NULL;
}


enum CompResult eCompareString(char pcStr1[], char pcStr2[]){

	unsigned char ucCharCounter;

	for(ucCharCounter = 0; pcStr1[ucCharCounter] == pcStr2[ucCharCounter]; ++ucCharCounter){
		if ((pcStr1[ucCharCounter] == NULL) && (pcStr2[ucCharCounter] == NULL)){
			return EQUAL;
		}
	}
	return NONEQUAL;
}


void AppendString (char pcSourceStr[],char pcDestinationStr[]){

	unsigned char ucCharCounter;

	for (ucCharCounter = 0; pcDestinationStr[ucCharCounter] != NULL; ++ucCharCounter){
	}
    CopyString(pcSourceStr, pcDestinationStr + ucCharCounter);
}


void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar){

    unsigned char ucCharCounter;

    for(ucCharCounter = 0; pcString[ucCharCounter] != NULL; ++ucCharCounter)
    {
        if(pcString[ucCharCounter] == cOldChar){
            pcString[ucCharCounter] = cNewChar;
        }
    }
}
