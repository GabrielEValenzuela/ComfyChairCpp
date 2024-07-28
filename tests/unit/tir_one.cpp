/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 25, 2024.
 *
 * MIT License
 */

#include "tir_one.hpp"

void TIROne::SetUp()
{
}

void TIROne::TearDown()
{
}

TEST_F(TIROne, HandleBidAndReview)
{
    const auto jsonInput = R"(
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
                    "articleTitle": "Advanced C++ Techniques 1",
                    "attachedFileUrl": "https://bit.ly/example",
                    "abstract": "Detailed exploration of modern C++ features.",
                    "authors": [
                        "Jane Smith"
                    ]
                },
                {
                    "articleType": "regular",
                    "articleTitle": "Advanced C++ Techniques 2",
                    "attachedFileUrl": "https://bit.ly/example",
                    "abstract": "Detailed exploration of modern C++ features.",
                    "authors": [
                        "Jane Smith"
                    ]
                },
                {
                    "articleType": "regular",
                    "articleTitle": "Advanced C++ Techniques 3",
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
                    "articleTitle": "Visualizing Big Data 1",
                    "attachedFileUrl": "https://bit.ly/example",
                    "additionalFileUrl": "https://bit.ly/example2",
                    "authors": [
                        "Jane Smith"
                    ]
                },
                {
                    "articleType": "regular",
                    "articleTitle": "Advanced C++ Techniques",
                    "attachedFileUrl": "https://bit.ly/example",
                    "abstract": "Detailed exploration of modern C++ features.",
                    "authors": [
                        "Jane Smith"
                    ]
                },
                {
                    "articleType": "poster",
                    "articleTitle": "Visualizing Big Data 2",
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
                "John Doe"
            ],
            "articles": [
                {
                    "articleType": "poster",
                    "articleTitle": "Exploring Large Datasets with Interactive Posters 1",
                    "attachedFileUrl": "https://bit.ly/interactivePoster",
                    "additionalFileUrl": "https://bit.ly/posterSupplement",
                    "abstract": "This poster demonstrates novel techniques for interacting with large datasets in a poster format, emphasizing user engagement and data accessibility.",
                    "authors": [
                        "Bob Smith"
                    ]
                },
                {
                    "articleType": "poster",
                    "articleTitle": "Exploring Large Datasets with Interactive Posters 2",
                    "attachedFileUrl": "https://bit.ly/interactivePoster",
                    "additionalFileUrl": "https://bit.ly/posterSupplement",
                    "abstract": "This poster demonstrates novel techniques for interacting with large datasets in a poster format, emphasizing user engagement and data accessibility.",
                    "authors": [
                        "Bob Smith"
                    ]
                },
                {
                    "articleType": "poster",
                    "articleTitle": "Exploring Large Datasets with Interactive Posters 3",
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
})"_json;

    // Create a conference
    auto conference = std::make_shared<Conference>(jsonInput);
    auto conferenceManager = std::make_shared<ConferenceManager>(conference);

    // Check if is valid, the JSON input should have
    // - 4 users
    // - 3 tracks
    // - 3 papers per track

    EXPECT_TRUE(conference != nullptr);

    // Check the users
    EXPECT_EQ(conference->sizeParticipants(), 4);

    // Check the tracks
    EXPECT_EQ(conference->tracks().size(), 3);

    // Check articles per track
    size_t index{0};
    for (const auto& track : jsonInput.at("tracks"))
    {
        for (const auto& article : track.at("articles"))
        {
            if (article.at("articleType") == "regular")
            {
                conference->tracks().at(index)->handleTrackArticle(std::make_shared<ArticleRegular>(article),
                                                                   OperationType::Create);
            }
            else if (article.at("articleType") == "poster")
            {
                conference->tracks().at(index)->handleTrackArticle(std::make_shared<ArticlePoster>(article),
                                                                   OperationType::Create);
            }
        }
        EXPECT_EQ(conference->tracks().at(index)->amountArticles(), 3);
        ++index;
    }

    // Check the bidding process
    conferenceManager->startBidding(std::chrono::system_clock::now());

    // Check the state of the tracks
    for (const auto& track : conference->tracks())
    {
        testing::internal::CaptureStdout();
        track->currentState();
        auto outputCurrentState = testing::internal::GetCapturedStdout();
        EXPECT_THAT(outputCurrentState, testing::HasSubstr("Bidding"));
    }

    // Handle the bid for the articles
    for (const auto& track : conference->tracks())
    {
        track->handleTrackBidding();
        EXPECT_EQ(track->amountBids(), 3);
    }

    // Check the revision state
    conferenceManager->startRevision(std::chrono::system_clock::now());

    // Check the state of the tracks
    for (const auto& track : conference->tracks())
    {
        testing::internal::CaptureStdout();
        track->currentState();
        auto outputCurrentState = testing::internal::GetCapturedStdout();
        EXPECT_THAT(outputCurrentState, testing::HasSubstr("Review"));
    }

    // Handle the review for the articles
    for (const auto& track : conference->tracks())
    {
        track->handleTrackReview();
        EXPECT_EQ(track->amountReviews(), 3);
    }

    conferenceManager->startSelection(std::chrono::system_clock::now());
}
