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

    conference = std::make_shared<Conference>(jsonConference);
}

void ConferenceTest::TearDown()
{
}

TEST_F(ConferenceTest, ConferenceCreation)
{
    EXPECT_TRUE(conference != nullptr);
    EXPECT_EQ(conference->chairs().size(), 1);
    EXPECT_EQ(conference->tracks().size(), 2);
}

TEST_F(ConferenceTest, ConferenceRevisionTime)
{
    auto today = std::chrono::system_clock::now();

    conference->revisionStart(std::chrono::system_clock::now());

    EXPECT_EQ(conference->revisionStart(), today);
}

TEST_F(ConferenceTest, ConferenceSelectiiobTime)
{
    auto today = std::chrono::system_clock::now();

    conference->selectionStart(std::chrono::system_clock::now());

    EXPECT_EQ(conference->selectionStart(), today);
}
