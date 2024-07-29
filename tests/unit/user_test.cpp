/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#include "user_test.hpp"
#include "user.hpp"

void UserTest::SetUp()
{
}

void UserTest::TearDown()
{
}

TEST_F(UserTest, UserCreation)
{
    const auto& jsonUser = R"(
    {
            "name": "Martin Venturino",
            "affiliation": "Tecnicas y herramientas",
            "email": "marven@tyh.com",
            "password": "https://bit.ly/example2"
    }
    )"_json;

    auto user = std::make_shared<User>(jsonUser);

    EXPECT_TRUE(user != nullptr);
    EXPECT_EQ(user->fullNames(), "Martin Venturino");
    EXPECT_EQ(user->affiliation(), "Tecnicas y herramientas");
    EXPECT_EQ(user->email(), "marven@tyh.com");
    EXPECT_EQ(user->isChair(), false);
    EXPECT_EQ(user->isAuthor(), false);
    EXPECT_THROW(user->determineInterest(), std::runtime_error);
}
