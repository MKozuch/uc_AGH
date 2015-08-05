typedef enum TokenType {KEYWORD, NUMBER, STRING};

typedef enum KeywordCode {LD, ST, RST};

typedef union TokenValue
{
    enum KeywordCode eKeyword;
    unsigned int uiNumber;
    char *pcString;
};

typedef struct Token
{
    enum TokenType eType;
    union TokenValue uValue;
};

void DecodeMsg(char*);
