#include <gtest/gtest.h>
#include "../../include/Lexer/Lexer.h"
#include "fstream"

TEST(TestLexe, testStreamBuffer){
    ASSERT_TRUE(true);
    std::ifstream file_to_open;
    file_to_open.open("assets/test.toto");
    auto lexer = TotoCompiler::Lexer::Lexer(std::move(file_to_open));
    lexer.printParse();
}
