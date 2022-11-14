#include <iostream>
#include <sstream>
#include "../../include/Lexer/Lexer.h"

namespace TotoCompiler::Lexer {

    void Lexer::Lexer::parse() {
        char c;
        std::stringstream buf;
        TokenType tmp_token_type;
        while (m_stream.get(c)) {

            if (c == 20) {
                fillTokenArray(buf, tmp_token_type);
            }
            if (c == EOF) {
                fillTokenArray(buf, tmp_token_type);
            }
            if (c > 47 && c < 58 || c > 64 && c < 91 || c > 96 && c < 123) buf << c;
        }

    }

    void Lexer::Lexer::fillTokenArray(std::stringstream &buf, TokenType &token_type) {
        if (buf.gcount() > 1) {
            m_token_array.emplace_back(new Token(buf.str()));
            token_type = m_token_array.back()->m_token_type;
        } else {
            m_token_array.emplace_back(new Token(static_cast<const char>(buf.get())));
            token_type = m_token_array.back()->m_token_type;
        }
        buf.clear();
    }

    void Lexer::Lexer::printParse() {
        char c;
        while (m_stream.get(c)) {
            std::cout << c << std::endl;
        }
    }

    void Lexer::printTokenArray() {
        for (auto token: m_token_array) {
            std::cout << token->m_token_type << token->m_token_string;
        }
    }
}

