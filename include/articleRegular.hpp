/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef ARTICLE_REGULAR_HPP
#define ARTICLE_REGULAR_HPP

#include "articleInterface.hpp"

/**
 * @class ArticleRegular
 * @brief Represents a regular article in a conference or publication system.
 *
 * The ArticleRegular class extends the Article class to accommodate articles
 * specifically formatted as regular. This class adds an additional attribute to handle
 * an abstract, typically used for short description of the article.
 * It inherits all public and protected properties and methods from the Article class
 * but overloads the display function to include the abstract.
 */
class ArticleRegular : public Article
{
  public:
    /**
     * @brief Default constructor.
     * @note Deleted to avoid its use.
     */
    ArticleRegular() = delete;

    /**
     * @brief Constructor.
     * @param articleJson Represents the article's information, in a JSON format.
     *
     */
    explicit ArticleRegular(const nlohmann::json& articleJson);

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
    std::string m_abstract;
};

#endif // ARTICLE_REGULAR_HPP
