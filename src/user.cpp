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
    m_fullNames = userJson.value("fullNames", "");
    m_affiliation = userJson.value("affiliation", "");
    m_email = userJson.value("email", "");
    m_password = userJson.value("password", "");
}

std::string User::fullNames()
{
    return m_fullNames;
}
