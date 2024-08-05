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
 * The ArticlePoster class extends the Article class to handle articles
 * specifically formatted as posters. It introduces an additional attribute
 * for a secondary attachment URL, which is typically used for supplementary
 * poster-related resources. This class inherits all public and protected
 * properties and methods from the Article class and overrides necessary methods
 * to include poster-specific functionality.
 */
class ArticlePoster : public Article
{
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes an ArticlePoster object with default values. Its use is generally
     * discouraged unless specific default initialization is required.
     */
    ArticlePoster() = default;

    /**
     * @brief Parameterized constructor to initialize a poster article with JSON data.
     * @param articleJson A JSON object containing the poster article's metadata.
     *
     * Constructs an ArticlePoster object by parsing the provided JSON data, extracting
     * relevant fields such as title, URL, secondary attachment URL, and authors.
     */
    explicit ArticlePoster(const nlohmann::json& articleJson);

    /**
     * @brief Override method to update the poster article's fields.
     * @param article A shared pointer to another Article object containing updated fields.
     *
     * Updates the current poster article's metadata with values from another Article instance.
     * This includes handling the secondary attachment URL specific to poster articles.
     */
    void updateFields(const std::shared_ptr<Article>& article) override;

    /**
     * @brief Override method to retrieve the poster article's title.
     * @return A constant reference to the poster article's title string.
     *
     * Returns the title of the poster article. This method is overridden from the base
     * Article class to provide specific implementation for ArticlePoster.
     */
    const std::string& articleName() const override;

    /**
     * @brief Override method to display the poster article's information.
     *
     * Outputs the poster article's details to the standard output, including the
     * secondary attachment URL. This provides a comprehensive overview of the poster's
     * metadata, enhancing user understanding.
     */
    void display() const override;

    /**
     * @brief Override method to check if the poster article is valid.
     * @return A boolean indicating the validity of the poster article.
     *
     * Determines the validity of the poster article by ensuring that all required fields
     * (title, attached file URL, and secondary attachment URL) are populated. This method
     * is overridden to enforce poster-specific validation criteria.
     */
    bool isValid() const override;

  private:
    std::string m_secondAttach; ///< URL for the secondary attachment specific to poster articles.
};

#endif // ARTICLE_POSTER_HPP
