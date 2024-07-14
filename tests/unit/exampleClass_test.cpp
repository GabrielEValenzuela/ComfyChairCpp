/*
 * ComfyChair 
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#include "exampleClass_test.hpp"

void ExampleClassTest::SetUp()
{
    
}

void ExampleClassTest::TearDown()
{
    
}

TEST_F(ExampleClassTest, TestSuccessfulMessage)
{
    auto example = ExampleClass();
    EXPECT_NO_THROW(example.printHelloWorld());
    ASSERT_EQ(1, 1);
}
