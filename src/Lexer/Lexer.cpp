
#include "../../include/Lexer/Lexer.h"

namespace TotoCompiler::Lexer {
    void Lexer::Lexer::parse() {

    }

    void Lexer::Lexer::printParse() {
        char c;
        while (m_stream.get(c)) {
            std::cout << c << std::endl;
        }
    }
}

