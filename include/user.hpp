/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef USER_HPP
#define USER_HPP

#include "bid.hpp"
#include "nlohmann/json.hpp"
#include "review.hpp"
#include <string>

/**
 * @class User
 * @brief Represents a user in the conference system.
 *
 * The User class provides the basic attributes and functionalities associated with
 * a user in the conference system. This includes personal information and methods
 * for determining interest in articles and reviewing articles. It serves as a base
 * class for more specific user roles.
 */
class User
{
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes a User object with default values. Its use is generally discouraged
     * unless specific default initialization is required.
     */
    User() = default;

    /**
     * @brief Constructor to initialize a user with JSON data.
     * @param userJson A JSON object containing the user's information.
     *
     * Constructs a User object by parsing the provided JSON data, extracting
     * relevant fields such as full name, affiliation, and email.
     */
    explicit User(const nlohmann::json& userJson);

    /**
     * @brief Virtual destructor.
     *
     * Ensures proper cleanup of derived classes.
     */
    virtual ~User();

    /**
     * @brief Get the full name of the user.
     * @return A constant reference to a string representing the user's full name.
     *
     * Returns the full name of the user.
     */
    const std::string& fullNames() const;

    /**
     * @brief Get the affiliation of the user.
     * @return A constant reference to a string representing the user's affiliation.
     *
     * Returns the affiliation of the user.
     */
    const std::string& affiliation() const;

    /**
     * @brief Get the email of the user.
     * @return A constant reference to a string representing the user's email.
     *
     * Returns the email of the user.
     */
    const std::string& email() const;

    /**
     * @brief Check if the user is a chair.
     * @return True if the user is a chair, false otherwise.
     *
     * Indicates whether the user holds a chair position.
     */
    bool isChair() const;

    /**
     * @brief Check if the user is an author.
     * @return True if the user is an author, false otherwise.
     *
     * Indicates whether the user is an author.
     */
    bool isAuthor() const;

    /**
     * @brief Checks if the user is a reviewer.
     * @return True if the user is a reviewer, false otherwise.
     *
     * Indicates that this user is a reviewer.
     */
    bool isReviewer() const;

    /**
     * @brief Determine the user's interest in an article.
     * @return A Bid object representing the user's interest in an article.
     *
     * This pure virtual method must be implemented by derived classes to specify
     * how the user determines interest in an article.
     */
    virtual Bid determineInterest()
    {
        throw std::runtime_error("Not implemented for Users");
    };

    /**
     * @brief Review an article.
     * @return A Review object containing the user's review of an article.
     *
     * This pure virtual method must be implemented by derived classes to specify
     * how the user reviews an article.
     */
    virtual Review reviewArticle()
    {
        throw std::runtime_error("Not implemented for Users");
    };

  protected:
    std::string m_fullNames;   /**< The full name of the user. */
    std::string m_affiliation; /**< The affiliation of the user. */
    std::string m_email;       /**< The email of the user. */
    std::string m_password;    /**< The password of the user. */
    bool m_isChair;            /**< Indicates if the user is a chair. */
    bool m_isAuthor;           /**< Indicates if the user is an author. */
};

#endif // USER_HPP
