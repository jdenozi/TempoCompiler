#ifndef TOTOCOMPILER_LEXER_H
#define TOTOCOMPILER_LEXER_H

#include <fstream>
#include "iostream"

namespace TotoCompiler::Lexer {
    /**
     *  it will iterate character by character to do two things: decide where each token starts/stops and what type of token it is.
     *  If the lexer is unable to do this, then it will report an error for an invalid token.
     */
    class Lexer {
    public:
        explicit Lexer(std::ifstream &&stream): m_stream(std::move(stream)){
        };

        void printParse();

        void parse();


    private:
        std::ifstream m_stream;

    };
}
#endif //TOTOCOMPILER_LEXER_H
