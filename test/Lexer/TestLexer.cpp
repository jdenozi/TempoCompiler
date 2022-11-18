#include <gtest/gtest.h>
#include "../../src/Lexer/Lexer.h"
#include "fstream"

TEST(TestLexe, testStreamBuffer) {
    ASSERT_TRUE(true);
    std::ifstream file_to_open;
    file_to_open.open("resources/test.tempo");
    auto lexer = TempoCompiler::Lexer::Lexer(std::move(file_to_open));
    lexer.parse();
}
