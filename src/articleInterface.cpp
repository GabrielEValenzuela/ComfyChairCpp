/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "articleInterface.hpp"
#include <iostream>

Article::Article(const nlohmann::json& articleJson)
{
    m_title = articleJson.value("articleTitle", "");
    m_attachedUrl = articleJson.value("attachedFileUrl", "");
    m_authors = articleJson.value("authors", std::vector<std::string>());
}

void Article::updateFields(const std::shared_ptr<Article>& article)
{
    m_title = article->m_title;
    m_attachedUrl = article->m_attachedUrl;
    m_authors = article->m_authors;
}

void Article::display() const
{
    std::cout << "Title: " << m_title << std::endl;
    std::cout << "Authors: ";
    for (auto it = m_authors.begin(); it != m_authors.end(); ++it)
    {
        std::cout << *it;
        if (it != std::prev(m_authors.end()))
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Attached URL: " << m_attachedUrl << std::endl;
}
