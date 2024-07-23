/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#include "conferenceManager_test.hpp"
#include "conferenceManager.hpp"

void ConferenceManagerTest::SetUp()
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

    conferenceManager = std::make_shared<ConferenceManager>(conference);
}

void ConferenceManagerTest::TearDown()
{
}

TEST_F(ConferenceManagerTest, ConferenceManagerCreation)
{
    EXPECT_TRUE(conferenceManager != nullptr);
}

TEST_F(ConferenceManagerTest, ConferenceManagerTrackState)
{
    testing::internal::CaptureStdout();
    conferenceManager->getConference()->getTracks()[0]->currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track 'Track SW Engineering' currently is in 'Reception' state\n");

    conferenceManager->startBidding();

    testing::internal::CaptureStdout();
    conferenceManager->getConference()->getTracks()[0]->currentState();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track 'Track SW Engineering' currently is in 'Bidding' state\n");
}