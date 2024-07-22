/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "conference.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

Conference::Conference(const nlohmann::json& conferenceJson)
{
    for (const auto& chairListJson : conferenceJson["chairs"])
    {
        for (const auto& chairJson : chairListJson)
        {
            m_chairs.push_back(std::make_shared<User>(chairJson));
        }
    }
    for (const auto& authorListJson : conferenceJson["authors"])
    {
        for (const auto& authorJson : authorListJson)
        {
            m_authors.push_back(std::make_shared<User>(authorJson));
        }
    }
    m_createdAt = parseDate(conferenceJson.value("createdAt", ""));
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
