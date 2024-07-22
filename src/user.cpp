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
    m_fullNames = userJson.value("m_fullNames", "");
    m_afiliation = userJson.value("m_afilation", "");
    m_email = userJson.value("m_email", "");
    m_password = userJson.value("m_password", "");
}