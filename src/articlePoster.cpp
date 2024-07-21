/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "articlePoster.hpp"

ArticlePoster::ArticlePoster(const nlohmann::json& articleJson) : Article(articleJson)
{
    m_secondAttach = articleJson.value("additionalFileUrl", "");
}

void ArticlePoster::updateFields(const std::shared_ptr<Article>& article)
{
    Article::updateFields(article);
    m_secondAttach = std::static_pointer_cast<ArticlePoster>(article)->m_secondAttach;
}

void ArticlePoster::display() const
{
    Article::display();
    std::cout << "Second Attachment: " << m_secondAttach << std::endl;
}
