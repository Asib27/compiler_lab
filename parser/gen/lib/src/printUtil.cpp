#include"../printUtil.h"

void PrintUtil::printLog(std::string token, std::string symbol, int lineNo){
    logos << "Line# " << lineNo << ": Token <" << token 
        << "> Lexeme " << symbol << " found" << std::endl;
    // fprintf(logout,"Line# %d: TOKEN <%s> Lexeme %s found\n",yylineno,token.c_str(), symbol.c_str());
}

void PrintUtil::printToken(std::string token, std::string symbol){
    tokenos << "<" << token << ", " << symbol << ">" << std::endl;
    // fprintf(tokenout,"<%s, %s>\n",token.c_str(), symbol.c_str());
}

void PrintUtil::printHelper(std::string token, std::string symbol, int lineNo){
    printLog(token, symbol, lineNo);
    printToken(token, symbol);
}


char PrintUtil::escapeToChar(char c){
    const int map_size = 11;
    const char keys[] = {'\'', '\"', 'n', 't', '\\', 'a', 'f', 'r', 'b', 'v', '0'};
    const char values[] = {'\'', '\"', '\n', '\t', '\\', '\a', '\f', '\r', '\b', '\v', '\0'};

    for(int i = 0; i < map_size; i++){
        if(keys[i] == c){
            return values[i];
        } 
    }

    //TODO: EMPTY CHAR HANDLE CODE
    return c;
}

bool PrintUtil::isEscapeChar(char c){
    const int map_size = 11;
    const char keys[] = {'\'', '\"', 'n', 't', '\\', 'a', 'f', 'r', 'b', 'v', '0'};

    for(int i = 0; i < map_size; i++){
        if(keys[i] == c) return true;
    }

    return false;
}

std::string PrintUtil::removerSlashNewline(std::string text){
    std::string ans = "";
    for(int i = 1; i < text.length()-1; i++){
        if(text[i] == '\\' && text[i+1] == '\n'){
            i++;
        }
        else{
            ans.push_back(text[i]);
        }
    }

    return ans;
}

std::string PrintUtil::insertEscapeInString(std::string text){
    std::string ans = "";

    for(int i = 0; i < text.length() -1; i++){
        if(text[i] == '\\'){
            char c = escapeToChar(text[i+1]);
            ans.append(1,c);
            i++;
        }
        else{
            ans.append(1,text[i]);
        }
    }

    // insert last char as it will not be processed
    if(text.length() > 2 && text[text.length()-2] != '\\')
        ans.append(1,text.back());
    return ans;
}

PrintUtil::PrintUtil(std::ostream &token, std::ostream &log)
    : tokenos(token), logos(log), errorCount(0)
{

}

void PrintUtil::printKeyword(std::string text, int lineNo){
    std::string upper = "";
    for(auto i: text){
        if(i >= 'a' && i <= 'z')
            upper.push_back(i - 'a' + 'A');
        else upper.push_back(i);
    }

    printHelper(upper, text, lineNo);
}

void PrintUtil::print(std::string token, std::string text, int lineNo){
    printHelper(token, text, lineNo);
}

void PrintUtil::printPunctuation(std::string text, int lineNo){
    char c = text[0];

    std::string keys = "=!(){}[],;";
    std::string values[] = {"ASSIGNOP", "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL",
        "LSQUARE", "RSQUARE", "COMMA", "SEMICOLON"
    };

    for(int i = 0; i < keys.length(); i++){
        if(c == keys[i]){
            printHelper(values[i], std::string(1, c), lineNo);
        }
    }
}

void PrintUtil::printChar(std::string text, int lineNo){
    if(text.length() == 2){
        printError("EMPTY_CONST_CHAR", text, lineNo);
    }
    else if(text.length() == 3){
        printHelper("CONST_CHAR", std::string(1, text[1]), lineNo);
    }
    else if(text.length() == 4 && text[1] == '\\' && isEscapeChar(text[2])){			
        printHelper("CONST_CHAR", std::string(1, escapeToChar(text[2])), lineNo);
    }
    else{
        printError("MULTICHAR_CONST_CHAR", text, lineNo);
    }
}

int PrintUtil::printString(std::string text, int lineNo){
    std::string singleLine = removerSlashNewline(text);
    std::string ans = insertEscapeInString(singleLine);

    if(singleLine.length() < text.length() - 2){
        int lineSpanByComment = (text.length() - 2 - singleLine.length()) / 2;
        printToken("MULTI LINE STRING", ans);
        printLog("MULTI LINE STRING", text, lineNo - lineSpanByComment);
        // printHelper("MULTI LINE STRING", ans, lineNo);
    }
    else{
        printToken("SINGLE LINE STRING", ans);
        printLog("SINGLE LINE STRING", text, lineNo);
        // printHelper("SINGLE LINE STRING", ans, lineNo);
    }

    return 0;
}


int PrintUtil::newLineCount(std::string text){
    int lineCount = 0;

    for(auto i: text){
        if(i == '\n') lineCount++;
    }

    return lineCount;
}

void PrintUtil::printComment(std::string text, int lineNo){
    // string ans = removerSlashNewline(text);
    // ans = ans.substr(1, ans.length()-1);
    int lineCount = newLineCount(text);
    text = text.substr(0, text.length()-1);
    printLog("SINGLE LINE COMMENT", text, lineNo - lineCount);
}

void PrintUtil::printMultilineComment(std::string text, int lineNo){
    int lineCount = newLineCount(text);
    printLog("MULTI LINE COMMENT", "/*" + text + "*/", lineNo - lineCount);
}

void PrintUtil::printError(std::string error, std::string text, int lineNo){
    errorCount++;
    logos << "Error at line# " << lineNo << ": " << error << " " << text << std::endl;
}

int PrintUtil::getErrorCount(){
    return errorCount;
}