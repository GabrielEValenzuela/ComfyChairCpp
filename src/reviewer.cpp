/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "reviewer.hpp"

Reviewer::Reviewer(const nlohmann::json& reviewerJson)
{
    m_fullNames = reviewerJson.value("m_fullNames", "");
    m_afiliation = reviewerJson.value("m_afiliation", "");
    m_email = reviewerJson.value("m_email", "");
    m_password = reviewerJson.value("m_password", "");
}
