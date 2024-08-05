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
 * @brief Abstract class representing an article in a conference or publication system.
 *
 * This class defines the interface for managing article metadata, including
 * the title, abstract, and file URL. It serves as a base class for various
 * types of articles, facilitating polymorphic behavior in derived classes.
 */
class Article
{
  public:
    /**
     * @brief Default constructor.
     *
     * This constructor initializes an Article object with default values.
     * Its use is discouraged unless specific default initialization is required.
     */
    Article() = default;

    /**
     * @brief Parameterized constructor to initialize an article with JSON data.
     * @param articleJson A JSON object containing the article's metadata.
     *
     * Constructs an Article object by parsing the provided JSON data, extracting
     * relevant fields such as title, URL, and authors.
     */
    explicit Article(const nlohmann::json& articleJson);

    /**
     * @brief Virtual method to update the article's fields.
     * @param article A shared pointer to another Article object containing updated fields.
     *
     * This method allows updating the current article's metadata with values
     * from another Article instance. Derived classes should implement this
     * to handle their specific fields.
     */
    virtual void updateFields(const std::shared_ptr<Article>& article);

    /**
     * @brief Pure virtual method to retrieve the article's title.
     * @return A constant reference to the article's title string.
     *
     * This method must be implemented by derived classes to return the specific
     * title of the article.
     */
    virtual const std::string& articleName() const = 0;

    /**
     * @brief Display the article's metadata.
     *
     * Outputs the article's details to the standard output, providing a user-friendly
     * overview of the article's metadata. Can be overridden by derived classes for
     * customized display.
     */
    virtual void display() const;

    /**
     * @brief Pure virtual method to check if the article is valid.
     * @return A boolean indicating the validity of the article.
     *
     * Derived classes must implement this method to define the criteria for
     * an article's validity, ensuring that all necessary fields and conditions
     * are met.
     */
    virtual bool isValid() const = 0;

  protected:
    std::string m_title;                ///< The article's title.
    std::string m_attachedUrl;          ///< The URL of the article's attached file.
    std::vector<std::string> m_authors; ///< List of authors associated with the article.
};

#endif // ARTICLE_INTERFACE_HPP
