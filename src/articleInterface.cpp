/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "articleInterface.hpp"

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
    auto last = --m_authors.end();
    for (auto it = m_authors.begin(); it != last; ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << *last; // Print the last author without a trailing comma

    std::cout << std::endl;
    std::cout << "Attached URL: " << m_attachedUrl << std::endl;
}
