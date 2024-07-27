/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "conference.hpp"
#include "reviewer.hpp"
#include "trackFactory.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

Conference::Conference(const nlohmann::json& conferenceJson)
{
    // Parse the conference's information

    // Start with the users, as they are needed for the reviewers we map
    // by full name
    if (conferenceJson.contains("users"))
    {
        for (const auto& userJson : conferenceJson["users"])
        {
            if (!userJson.at("isReviewer").get<bool>())
            {
                m_users.emplace_back(std::make_shared<User>(userJson));
            }
            else
            {
                auto reviewer = std::make_shared<Reviewer>(userJson);
                m_reviewers.insert({reviewer->fullNames(), reviewer});
                m_users.push_back(reviewer);
            }
        }
    }

    // Parse the conference's tracks
    // And add the reviewers to the tracks
    if (conferenceJson.contains("tracks"))
    {
        for (const auto& trackJson : conferenceJson.at("tracks"))
        {
            try
            {
                auto track = TrackFactory::createTrack(trackJson);
                validateAndAddReviewers(track, trackJson);
                m_tracks.push_back(track);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error creating track: " << e.what() << std::endl;
            }
        }
    }
    if (conferenceJson.contains("createdAt"))
    {
        m_createdAt = parseDate(conferenceJson.value("createdAt", ""));
    }
    else
    {
        m_createdAt = std::chrono::system_clock::now();
    }
}

std::chrono::system_clock::time_point Conference::parseDate(const std::string& dateStr)
{
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail())
    {
        throw std::runtime_error("Parse failed");
    }
    std::time_t time = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(time);
}

std::chrono::system_clock::time_point Conference::biddingStart()
{
    return m_biddingStart;
}

void Conference::biddingStart(const std::chrono::system_clock::time_point& timePoint)
{
    m_biddingStart = timePoint;
}

std::chrono::system_clock::time_point Conference::revisionStart()
{
    return m_revisionStart;
}

void Conference::revisionStart(const std::chrono::system_clock::time_point& timePoint)
{
    printBiddingSummary();
    m_revisionStart = timePoint;
}

std::chrono::system_clock::time_point Conference::selectionStart()
{
    return m_selectionStart;
}

void Conference::selectionStart(const std::chrono::system_clock::time_point& timePoint)
{
    m_selectionStart = timePoint;
}

std::vector<std::shared_ptr<Track>> Conference::tracks()
{
    return m_tracks;
}

std::chrono::system_clock::time_point Conference::createdAt()
{
    return m_createdAt;
}

void Conference::validateAndAddReviewers(std::shared_ptr<Track> track, const nlohmann::json& trackJson)
{
    if (trackJson.contains("reviewers"))
    {
        for (const auto& reviewerName : trackJson["reviewers"])
        {

            for (const auto& user : m_reviewers)
            {
            }
            if (m_reviewers.find(reviewerName) == m_reviewers.end())
            {
                throw std::invalid_argument("Reviewer not found: " + reviewerName.get<std::string>());
            }
            track->addReviewer(m_reviewers[reviewerName]);
        }
    }
}

size_t Conference::sizeParticipants()
{
    return m_users.size();
}

void Conference::printBiddingSummary()
{
    std::cout << "Bidding Summary" << std::endl;
    std::cout << "================" << std::endl;
    for (const auto& track : m_tracks)
    {
        track->currentBids();
    }
}
