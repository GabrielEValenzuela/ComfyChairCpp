/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "articleRegular.hpp"

constexpr auto MINIMUM_ABSTRACT_SIZE = 300;

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
    std::cout << "=== Article ===" << std::endl;
    Article::display();
    std::cout << "Abstract: " << m_abstract << std::endl;
}

bool ArticleRegular::isValid() const
{
    return !m_abstract.empty() && !m_title.empty() && !m_attachedUrl.empty() &&
           m_abstract.size() >= MINIMUM_ABSTRACT_SIZE;
}

const std::string& ArticleRegular::articleName() const
{
    return m_title;
}
