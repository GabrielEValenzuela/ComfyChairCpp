/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "conference.hpp"
#include "trackFactory.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

Conference::Conference(const nlohmann::json& conferenceJson)
{
    if (conferenceJson.contains("chairs"))
    {
        for (const auto& chairJson : conferenceJson["chairs"])
        {
            m_chairs.push_back(std::make_shared<User>(chairJson));
        }
    }
    if (conferenceJson.contains("authors"))
    {
        for (const auto& authorJson : conferenceJson["authors"])
        {
            m_authors.push_back(std::make_shared<User>(authorJson));
        }
    }
    if (conferenceJson.contains("tracks"))
    {
        for (const auto& trackJson : conferenceJson["tracks"])
        {
            m_tracks.push_back(TrackFactory::createTrack(trackJson, TrackType::Regular));
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

std::vector<std::shared_ptr<User>> Conference::chairs()
{
    return m_chairs;
}

std::vector<std::shared_ptr<Track>> Conference::tracks()
{
    return m_tracks;
}

std::chrono::system_clock::time_point Conference::createdAt()
{
    return m_createdAt;
}
