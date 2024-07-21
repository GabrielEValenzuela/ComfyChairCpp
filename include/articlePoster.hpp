/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef ARTICLE_POSTER_HPP
#define ARTICLE_POSTER_HPP

#include "articleInterface.hpp"

/**
 * @class ArticlePoster
 * @brief Represents a poster article in a conference or publication system.
 *
 * The ArticlePoster class extends the Article class to accommodate articles
 * specifically formatted as posters. This class adds an additional attribute to handle
 * a secondary attachment URL, typically used for additional poster-related resources.
 * It inherits all public and protected properties and methods from the Article class
 * but specializes the << operator to include the secondary attachment URL.
 */
class ArticlePoster : public Article
{
  public:
    /**
     * @brief Default constructor.
     * @note Avoid its use.
     */
    ArticlePoster() = default;

    /**
     * @brief Constructor.
     * @param articleJson Represents the article's information, in a JSON format.
     *
     */
    explicit ArticlePoster(const nlohmann::json& articleJson);

    /**
     * @brief updateFields updates the article's fields.
     * @param article The article with the updated fields.
     */
    void updateFields(const std::shared_ptr<Article>& article) override;

    /**
     * @brief Display poster article information.
     */
    void display() const override;

  private:
    std::string m_secondAttach;
};

#endif // ARTICLE_POSTER_HPP
