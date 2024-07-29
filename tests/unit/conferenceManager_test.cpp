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
}

void ConferenceManagerTest::TearDown()
{
}

TEST_F(ConferenceManagerTest, ConferenceCreation)
{
    const auto& jsonConference = R"(
  {
    "biddingStart": "2024-07-18T00:00:00Z",
    "revisionStart": "2024-07-18T00:00:00Z",
    "selectionStart": "2024-07-18T00:00:00Z",
    "createdAt": "2024-07-18T00:00:00Z",
    "users": [
        {
            "name": "John Doe",
            "affiliation": "Example University",
            "password": "password",
            "email": "john.doe@example.com",
            "isChair": true,
            "isReviewer": true,
            "isAuthor": false
        },
        {
            "name": "John Doe 2nd",
            "email": "john.doe.2@example.com",
            "affiliation": "Example University",
            "password": "password",
            "isChair": false,
            "isReviewer": true,
            "isAuthor": false
        },
        {
            "name": "John Doe 3rd",
            "email": "john.doe.3@example.com",
            "affiliation": "Example University",
            "password": "password",
            "isChair": true,
            "isReviewer": false,
            "isAuthor": true
        },
        {
            "name": "John Doe 4th",
            "email": "john.doe.4@example.com",
            "affiliation": "Example University",
            "password": "password",
            "isChair": true,
            "isReviewer": true,
            "isAuthor": true
        }
    ],
    "tracks": [
        {
            "trackType": "regular",
            "trackTopic": "C++",
            "reviewers": [
                "John Doe"
            ],
            "articles": [
                {
                    "articleType": "regular",
                    "articleTitle": "Advanced C++ Techniques",
                    "attachedFileUrl": "https://bit.ly/example",
                    "abstract": "Detailed exploration of modern C++ features.",
                    "authors": [
                        "Jane Smith"
                    ]
                }
            ]
        },
        {
            "trackType": "workshop",
            "trackTopic": "Data Science",
            "reviewers": [
                "John Doe"
            ],
            "articles": [
                {
                    "articleType": "poster",
                    "articleTitle": "Visualizing Big Data",
                    "attachedFileUrl": "https://bit.ly/example",
                    "additionalFileUrl": "https://bit.ly/example2",
                    "authors": [
                        "Jane Smith"
                    ]
                }
            ]
        },
        {
            "trackType": "poster",
            "trackTopic": "Innovative Data Visualization Techniques",
            "reviewers": [
                "Alice Johnson"
            ],
            "articles": [
                {
                    "articleType": "poster",
                    "articleTitle": "Exploring Large Datasets with Interactive Posters",
                    "attachedFileUrl": "https://bit.ly/interactivePoster",
                    "additionalFileUrl": "https://bit.ly/posterSupplement",
                    "abstract": "This poster demonstrates novel techniques for interacting with large datasets in a poster format, emphasizing user engagement and data accessibility.",
                    "authors": [
                        "Bob Smith"
                    ]
                }
            ]
        }
    ]
}
    )"_json;

    auto conference = std::make_shared<Conference>(jsonConference);
    auto conferenceManager = std::make_shared<ConferenceManager>(conference);
    EXPECT_TRUE(conferenceManager != nullptr);
    EXPECT_TRUE(conferenceManager->conference() != nullptr);

    conferenceManager->startBidding(std::chrono::system_clock::now());
    conferenceManager->startRevision(std::chrono::system_clock::now());
    conferenceManager->startSelection(std::chrono::system_clock::now());
}
