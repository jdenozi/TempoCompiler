#ifndef TOTOCOMPILER_TOKEN_H
#define TOTOCOMPILER_TOKEN_H


namespace TotoCompiler::Lexer{
    enum class TokenType{
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
        Unexpected,
    };

    template<typename T>
    class Token{

    };
}

#endif //TOTOCOMPILER_TOKEN_H
