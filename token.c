#include "compiler.h"

bool token_is_keyword(struct token* the_token, const char* keyword){
    return the_token->type == TOKEN_TYPE_KEYWORD && S_EQ(the_token->sval, keyword);
}
