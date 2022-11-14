#ifndef TOTOCOMPILER_LEXER_H
#define TOTOCOMPILER_LEXER_H

#include <fstream>
#include "iostream"
#include "Token.h"
#include "vector"

namespace TotoCompiler::Lexer {
    /**
     *  it will iterate character by character to do two things: decide where each token starts/stops and what type of token it is.
     *  If the lexer is unable to do this, then it will report an error for an invalid token.
     */
    class Lexer {
    public:
        explicit Lexer(std::ifstream &&stream) : m_stream(std::move(stream)) {
        };

        void printParse();

        void printTokenArray();


        void parse();

        /**
         * This function takes a stringstream object and checks if it has more than one character in it. If it does, it creates
         * a new Token object with the stringstream's string. If it doesn't, it creates a new Token object with the
         * stringstream's character
         *
         * @param buf a stringstream object that is used to store the characters that make up a token.
         */
        void fillTokenArray(std::stringstream &buf, TokenType &token_type);

    private:
        std::ifstream m_stream;
        std::vector<Token *> m_token_array;

    };
}
#endif //TOTOCOMPILER_LEXER_H
