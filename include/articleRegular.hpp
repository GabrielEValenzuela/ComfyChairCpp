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
 * The ArticleRegular class extends the Article class to handle articles
 * specifically formatted as regular articles. This class introduces an
 * additional attribute for an abstract, which is typically used for a short
 * description of the article. It inherits all public and protected properties
 * and methods from the Article class and overrides the display function to
 * include the abstract.
 */
class ArticleRegular : public Article
{
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes an ArticleRegular object with default values. Its use is generally
     * discouraged unless specific default initialization is required.
     */
    ArticleRegular() = default;

    /**
     * @brief Parameterized constructor to initialize a regular article with JSON data.
     * @param articleJson A JSON object containing the regular article's metadata.
     *
     * Constructs an ArticleRegular object by parsing the provided JSON data, extracting
     * relevant fields such as title, URL, abstract, and authors.
     */
    explicit ArticleRegular(const nlohmann::json& articleJson);

    /**
     * @brief Override method to update the regular article's fields.
     * @param article A shared pointer to another Article object containing updated fields.
     *
     * Updates the current regular article's metadata with values from another Article instance.
     * This includes handling the abstract specific to regular articles.
     */
    void updateFields(const std::shared_ptr<Article>& article) override;

    /**
     * @brief Override method to retrieve the regular article's title.
     * @return A constant reference to the regular article's title string.
     *
     * Returns the title of the regular article. This method is overridden from the base
     * Article class to provide specific implementation for ArticleRegular.
     */
    const std::string& articleName() const override;

    /**
     * @brief Override method to display the regular article's information.
     *
     * Outputs the regular article's details to the standard output, including the
     * abstract. This provides a comprehensive overview of the article's metadata,
     * enhancing user understanding.
     */
    void display() const override;

    /**
     * @brief Override method to check if the regular article is valid.
     * @return A boolean indicating the validity of the regular article.
     *
     * Determines the validity of the regular article by ensuring that all required fields
     * (title, attached file URL, and abstract with at least 300 characters) are populated.
     * This method is overridden to enforce regular article-specific validation criteria.
     */
    bool isValid() const override;

  private:
    std::string m_abstract; ///< Abstract providing a short description of the regular article.
};

#endif // ARTICLE_REGULAR_HPP
