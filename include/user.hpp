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
#include <string>

/**
 * @class User
 * @brief Represents a user.
 */
class User
{
  public:
    /**
     * @brief Default constructor.
     * @note Avoid its use.
     */
    User() = default;

    /**
     * @brief Constructor.
     * @param userJson Represents the user's information, in a JSON format.
     */
    explicit User(const nlohmann::json& userJson);

    /**
     * @brief Destructor.
     */
    virtual ~User() = default;

    /**
     * @brief Getter for the full name.
     * @return The full name of the user.
     */
    const std::string& fullNames();

    /**
     * @brief Getter for the affiliation.
     * @return The affiliation of the user.
     */
    const std::string& affiliation();

    /**
     * @brief Getter for the email.
     * @return The email of the user.
     */
    const std::string& email();

    /**
     * @brief Getter for the chair status.
     * @return True if the user is a chair, false otherwise.
     */
    bool isChair();

    /**
     * @brief Getter for the author status.
     * @return True if the user is an author, false otherwise.
     */

    bool isAuthor();

    /**
     * @brief Places a bid
     *
     * @note This method is pure virtual and must be implemented by the derived classes.
     */
    virtual Bid determineInterest(const std::string& title);

  protected:
    std::string m_fullNames;   /**< The full name of the user. */
    std::string m_affiliation; /**< The affiliation of the user. */
    std::string m_email;       /**< The email of the user. */
    std::string m_password;    /**< The password of the user. */
    bool m_isChair;            /**< Indicates if the user is a chair. */
    bool m_isAuthor;           /**< Indicates if the user is an author. */
};

#endif // USER_HPP
