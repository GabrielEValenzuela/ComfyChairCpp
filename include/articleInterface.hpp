/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef ARTICLE_INTERFACE_HPP
#define ARTICLE_INTERFACE_HPP

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @class Article
 * @brief Represents an article in a conference or publication system.
 *
 * The Article class provides functionalities to manage the details
 * of an article, such as title, abstract, and file URL. It serves as a
 * base class for different types of articles, enabling polymorphic behavior.
 */
class Article
{
  public:
    /**
     * @brief Default constructor.
     * @note Avoid its use.
     */
    Article() = default;

    /**
     * @brief Constructor.
     * @param articleJson Represents the article's information, in a JSON format.
     */
    explicit Article(const nlohmann::json& articleJson);

    /**
     * @brief updateFields updates the article's fields.
     * @param article The article with the updated fields.
     */
    virtual void updateFields(const std::shared_ptr<Article>& article);

    /**
     * @brief Get the article's title
     * @return The article's title.
     */
    const std::string& articleName() const;

    /**
     * @brief Display the article's information.
     */
    virtual void display() const;

  protected:
    std::string m_title;                ///< The article's name.
    std::string m_attachedUrl;          ///< The article's URL.
    std::vector<std::string> m_authors; ///< The users that have access to the article.
};

#endif // ARTICLE_INTERFACE_HPP
