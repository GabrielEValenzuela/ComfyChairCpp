/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#include "conference_test.hpp"
#include "conference.hpp"
#include "trackFactory.hpp"

void ConferenceTest::SetUp()
{
}

void ConferenceTest::TearDown()
{
}

TEST_F(ConferenceTest, ConferenceCreation)
{
    const auto& jsonConference = R"(
    {
        "chairs": [
            {
                "fullNames": "Martin Venturino",
                "affiliation": "Tecnicas y herramientas",
                "email": "marven@tyh.com",
                "password": "https://bit.ly/example2"
            }
        ],
        "authors": [
            {
                "fullNames": "Matias",
                "affiliation": "Tecnicas y herramientas 2",
                "email": "matimati@tyh.com",
                "password": "https://bit.ly/example21155"
            }
        ],
        "tracks": [
            { "trackTopic": "Track SW Engineering" },
            { "trackTopic": "AI Engineering" }
        ],
        "createdAt": "2024-07-13"
    }
    )"_json;

    auto conference = std::make_shared<Conference>(jsonConference);

    EXPECT_TRUE(conference != nullptr);
    EXPECT_EQ(conference->getChairs().size(), 1);
    EXPECT_EQ(conference->getTracks().size(), 2);
}
