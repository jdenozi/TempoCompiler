#include <utility>
#include <ostream>

#ifndef TOTOCOMPILER_TOKEN_H
#define TOTOCOMPILER_TOKEN_H


namespace TotoCompiler::Lexer {
    enum class TokenType {
        Number,
        Identifier,
        LeftParenthesis,
        RightParenthesis,
        LeftBracket,
        RightBracket,
        LeftBrace,
        RightBrace,
        LessThan,
        GreaterThan,
        Equal,
        Plus,
        Minus,
        Asterisk,
        Slash,
        Hash,
        Dot,
        Comma,
        Colon,
        Semicolon,
        SingleQuote,
        DoubleQuote,
        Comment,
        Pipe,
        End,
        BackSlash,
        Unexpected,
    };

    class Token {

    public:
        Token(std::string token_string, TokenType token_type) : m_token_string(std::move(token_string)),
                                                                m_token_type(token_type) {}

        Token(Token const &token) = delete;

        Token &operator=(Token const &) = delete;

        explicit Token(std::string token_string) : m_token_string(std::move(token_string)) {
            if (m_token_string.at(0) == 23) {
                m_token_type = TokenType::Comment;
            } else {
                m_token_type = TokenType::Identifier;
            }
        };

        explicit Token(const char token_char) : m_token_string(static_cast<std::string>(&token_char)) {
            if (token_char == 22) m_token_type = TokenType::DoubleQuote;
            if (token_char == 40) m_token_type = TokenType::LeftParenthesis;
            if (token_char == 41) m_token_type = TokenType::RightParenthesis;
            if (token_char == 42) m_token_type = TokenType::Asterisk;
            if (token_char == 43) m_token_type = TokenType::Plus;
            if (token_char == 44) m_token_type = TokenType::Comma;
            if (token_char == 45) m_token_type = TokenType::Minus;
            if (token_char == 46) m_token_type = TokenType::Dot;
            if (token_char == 47) m_token_type = TokenType::Slash;
            if (token_char > 47 && token_char < 58) m_token_type = TokenType::Number;
            if (token_char == 58) m_token_type = TokenType::Colon;
            if (token_char == 59) m_token_type = TokenType::Semicolon;
            if (token_char == 60) m_token_type = TokenType::LessThan;
            if (token_char == 61) m_token_type = TokenType::Equal;
            if (token_char == 62) m_token_type = TokenType::GreaterThan;
            if (token_char > 64 && token_char < 91) m_token_type = TokenType::Number;
            if (token_char == 91) m_token_type = TokenType::LeftBracket;
            if (token_char == 92) m_token_type = TokenType::BackSlash;
            if (token_char == 93) m_token_type = TokenType::RightBracket;
            if (token_char == 96) m_token_type = TokenType::SingleQuote;
            if (token_char > 96 && token_char < 123) m_token_type = TokenType::Number;
            if (token_char == 123) m_token_type = TokenType::LeftBrace;
            if (token_char == 124) m_token_type = TokenType::Pipe;
            if (token_char == 125) m_token_type = TokenType::RightBrace;
            else {
                m_token_type = TokenType::Unexpected;
            }
        };

    public:
        const std::string m_token_string;
        TokenType m_token_type;
    };

    inline std::ostream &operator<<(std::ostream &str, TokenType &token_type) {
        switch (token_type) {
            case TokenType::Number:
                return str << "Number";
            case TokenType::Identifier:
                return str << "Identifier";
            case TokenType::LeftParenthesis:
                return str << "LeftParenthesis";
            case TokenType::RightParenthesis:
                return str << "RightParenthesis";
            case TokenType::LeftBracket:
                return str << "LeftBracket";
            case TokenType::RightBracket:
                return str << "RightBracket";
            case TokenType::LeftBrace:
                return str << "LeftBrace";
            case TokenType::RightBrace:
                return str << "RightBrace";
            case TokenType::LessThan:
                return str << "LessThan";
            case TokenType::GreaterThan:
                return str << "GreaterThan";
            case TokenType::Equal:
                return str << "Equal";
            case TokenType::Plus:
                return str << "Plus";
            case TokenType::Minus:
                return str << "Minus";
            case TokenType::Asterisk:
                return str << "Asterisk";
            case TokenType::Slash:
                return str << "Slash";
            case TokenType::Hash:
                return str << "Hash";
            case TokenType::Dot:
                return str << "Dot";
            case TokenType::Comma:
                return str << "Comma";
            case TokenType::Colon:
                return str << "Colon";
            case TokenType::Semicolon:
                return str << "Semicolon";
            case TokenType::SingleQuote:
                return str << "SingleQuote";
            case TokenType::DoubleQuote:
                return str << "DoubleQuote";
            case TokenType::Comment:
                return str << "Comment";
            case TokenType::Pipe:
                return str << "Pipe";
            case TokenType::End:
                return str << "End";
            case TokenType::BackSlash:
                return str << "BackSlash";
            case TokenType::Unexpected:
                return str << "Unexpected";
            default:
                return str << (int) token_type;
        }
    }
}

#endif //TOTOCOMPILER_TOKEN_H

