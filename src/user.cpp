/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "user.hpp"

User::User(const nlohmann::json& userJson)
{
    m_fullNames = userJson.at("name").get<std::string>();
    m_affiliation = userJson.at("affiliation").get<std::string>();
    m_email = userJson.at("email").get<std::string>();
    m_password = userJson.at("password").get<std::string>();
    m_isChair = userJson.at("isChair").get<bool>();
    m_isAuthor = userJson.at("isAuthor").get<bool>();
}

User::~User()
{
}

const std::string& User::fullNames() const
{
    return m_fullNames;
}

const std::string& User::affiliation() const
{
    return m_affiliation;
}

const std::string& User::email() const
{
    return m_email;
}

bool User::isChair() const
{
    return m_isChair;
}

bool User::isAuthor() const
{
    return m_isAuthor;
}

bool User::isReviewer() const
{
    return false;
}
