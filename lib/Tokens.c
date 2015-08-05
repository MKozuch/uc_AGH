#include "StrOp.h"
#include "StrConv.h"
#include "Tokens.h"
#define NULL '\0'

#define MAX_KEYWORD_STRING_LTH 10
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_NR 3
#define DELIMETER_CHAR ' '

typedef struct Keyword
{
    enum KeywordCode eCode;
    char cString[MAX_KEYWORD_STRING_LTH + 1];
};

struct Keyword asKeywordList[MAX_KEYWORD_NR] =
{
    {RST, "reset"},
    {LD, "load"},
    {ST, "store"}
};

unsigned char ucTokenNr;

struct Token asToken[MAX_TOKEN_NR];

enum eFindTokensInStringMachineStates{TOKEN, DELIMETER};

unsigned char ucFindTokensInString(char *pcString){

    unsigned char ucCharacterCounter, ucCurrentCharacter, ucTokenCounter = 0;
    enum eFindTokensInStringMachineStates eFindTokensState = DELIMETER;

    for(ucCharacterCounter = 0;; ucCharacterCounter++){
        ucCurrentCharacter = pcString[ucCharacterCounter];
        switch (eFindTokensState){
            case TOKEN:{
                if (NULL == ucCurrentCharacter) {
                    return ucTokenCounter;
                }
                else if(DELIMETER_CHAR == ucCurrentCharacter){
                    eFindTokensState = DELIMETER;
                }
                else{
                    eFindTokensState = TOKEN;
                }
            break;
            }
            case DELIMETER:{
                if (NULL == ucCurrentCharacter) {
                    return ucTokenCounter;
                }
                else if(DELIMETER_CHAR == ucCurrentCharacter){
                    eFindTokensState = DELIMETER;
                }
                else if(ucTokenCounter < MAX_TOKEN_NR){
                    asToken[ucTokenCounter].uValue.pcString = pcString + ucCharacterCounter;
                    ucTokenCounter++;
                    eFindTokensState = TOKEN;
                }
                else{
                    eFindTokensState = TOKEN;
                }
            break;
            }
            default:{
            break;
            }
        }
    }
}


enum Result eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode){

    unsigned char ucKeywordCounter;

    for(ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++){
        if(eCompareString(pcStr, asKeywordList[ucKeywordCounter].cString) == EQUAL){
            *peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
            return OK;
        }
    }
    return ERROR;
}


void DecodeTokens(void){

    unsigned char ucTokenCounter;
    union TokenValue uNewValue;
    struct Token *spCurrentTokenPtr;

    for(ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++){
        spCurrentTokenPtr = &asToken[ucTokenCounter];
        if(OK == eStringToKeyword(spCurrentTokenPtr->uValue.pcString, &uNewValue.eKeyword)){
            spCurrentTokenPtr->eType = KEYWORD;
            spCurrentTokenPtr->uValue = uNewValue;
        }
        else if(OK == eHexStringToUInt(spCurrentTokenPtr->uValue.pcString, &uNewValue.uiNumber)){
            spCurrentTokenPtr->eType = NUMBER;
            spCurrentTokenPtr->uValue = uNewValue;
        }
        else {
            spCurrentTokenPtr->eType = STRING;
        }
    }
}


void DecodeMsg(char *pcString){
    ucTokenNr = ucFindTokensInString(pcString);
    ReplaceCharactersInString(pcString, DELIMETER_CHAR, NULL);
    DecodeTokens();
}
