/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "user.hpp"
#include <iostream>

User::User(const nlohmann::json& userJson)
{
    m_fullNames = userJson.value("name", "");
    m_affiliation = userJson.value("affiliation", "");
    m_email = userJson.value("email", "");
    m_password = userJson.value("password", "");
    m_isChair = userJson.value("isChair", false);
    m_isAuthor = userJson.value("isAuthor", false);
}

const std::string& User::fullNames()
{
    return m_fullNames;
}

const std::string& User::affiliation()
{
    return m_affiliation;
}

const std::string& User::email()
{
    return m_email;
}

bool User::isChair()
{
    return m_isChair;
}

bool User::isAuthor()
{
    return m_isAuthor;
}

Bid User::determineInterest(const std::string& title)
{
    throw std::runtime_error("Regular user can't bid");
}
