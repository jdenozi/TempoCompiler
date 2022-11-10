#ifndef TOTOCOMPILER_LEXER_H
#define TOTOCOMPILER_LEXER_H

#include <fstream>
#include "iostream"

namespace TotoCompiler::Lexer {
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
