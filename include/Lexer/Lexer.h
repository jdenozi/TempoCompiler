#ifndef TOTOCOMPILER_LEXER_H
#define TOTOCOMPILER_LEXER_H

#include "iostream"

namespace TotoCompiler::Lexer::Lexer {
    class Lexer {
    public:

        explicit Lexer(std::streambuf *stream): m_stream(stream){
        };

        void printParse();

        void parse();


    private:
        std::streambuf *m_stream;

    };
}
#endif //TOTOCOMPILER_LEXER_H
