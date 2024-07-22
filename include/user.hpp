/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef USER_HPP
#define USER_HPP

#include "nlohmann/json.hpp"
#include <string>

/**
 * @class User
 * @brief
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
     * @brief Constructor.
     * @param fullNames The full name of the user.
     * @param affiliation The affiliation of the user.
     * @param email The email of the user.
     * @param password The password of the user.
     */
    User(const std::string& fullNames, const std::string& affiliation, const std::string& email,
         const std::string& password)
        : m_fullNames(fullNames), m_affiliation(affiliation), m_email(email), m_password(password)
    {
    }

    /**
     * @brief Destructor.
     */
    virtual ~User() = default;

    /**
     * @brief Getter for the full name.
     * @return The full name of the user.
     */
    std::string getFullNames() const
    {
        return m_fullNames;
    }

  protected:
    std::string m_fullNames;
    std::string m_affiliation;
    std::string m_email;
    std::string m_password;
};

#endif // USER_HPP
