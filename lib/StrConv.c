#include "StrConv.h"
#define NULL '\0'

void UIntToHexStr (unsigned int uiValue, char pcStr[]){

    unsigned int uiNibbleValue;
    unsigned char ucNibbleCounter;

    pcStr[0] = '0';
    pcStr[1] = 'x';
    for(ucNibbleCounter = 0; ucNibbleCounter < 4; ++ucNibbleCounter){
        uiNibbleValue = (uiValue >> (ucNibbleCounter*4)) & 0xF;
        if (uiNibbleValue <= 9){
            uiNibbleValue = uiNibbleValue + '0';
        }
        else {
            uiNibbleValue = uiNibbleValue + ('A' - 10);
        }
        pcStr[5-ucNibbleCounter] = uiNibbleValue;
    }
    pcStr[6] = NULL;
}

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){

    unsigned char ucNibbleCounter;
    *puiValue = 0;

    if((pcStr[0] != '0') || pcStr[1] != 'x' || NULL == pcStr[2]){
        return ERROR;
    }
    for (ucNibbleCounter = 2; NULL != pcStr[ucNibbleCounter]; ++ucNibbleCounter){
        *puiValue = *puiValue << 4;
        if( pcStr[ucNibbleCounter] > '9' ){
            *puiValue = *puiValue + (pcStr[ucNibbleCounter] - 'A' + 10 );
        }
        else{
            *puiValue = *puiValue + (pcStr[ucNibbleCounter] - '0' );
        }
    }
    if ((ucNibbleCounter >= 7)){
        return ERROR;
        }
    else {
        return OK;
    }
}


void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]){
    unsigned char ucDestinationStringIndex;
    for(ucDestinationStringIndex = 0; pcDestinationStr[ucDestinationStringIndex] != NULL; ++ucDestinationStringIndex){
    }
    UIntToHexStr(uiValue, &pcDestinationStr[ucDestinationStringIndex]);
}
