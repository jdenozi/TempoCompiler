
#include "../../include/Lexer/Lexer.h"

namespace TotoCompiler::Lexer {
    void Lexer::Lexer::parse() {

    }

    void Lexer::Lexer::printParse() {
        for(size_t i = 0; i < m_stream->in_avail(); i++){
             auto c = m_stream->snextc();
             std::cout << static_cast<char>(c);
            m_stream->sputbackc(c);
        }
    }
}

