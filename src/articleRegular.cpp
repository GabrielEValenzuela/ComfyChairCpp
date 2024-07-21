/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "articleRegular.hpp"

ArticleRegular::ArticleRegular(const nlohmann::json& articleJson) : Article(articleJson)
{
    m_abstract = articleJson.value("abstract", "");
}

void ArticleRegular::updateFields(const std::shared_ptr<Article>& article)
{
    Article::updateFields(article);
    m_abstract = std::static_pointer_cast<ArticleRegular>(article)->m_abstract;
}

void ArticleRegular::display() const
{
    Article::display();
    std::cout << "Abstract: " << m_abstract << std::endl;
}
