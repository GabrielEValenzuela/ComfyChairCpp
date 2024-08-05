/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 21, 2024.
 *
 * MIT License
 */

#ifndef TRACK_STATE_EXCEPTION_HPP
#define TRACK_STATE_EXCEPTION_HPP

#include <stdexcept>
#include <string>

/**
 * @class TrackStateException
 * @brief Exception class for handling errors related to track states.
 *
 * The TrackStateException class extends the standard exception to provide
 * specific error handling for track state-related issues within the conference
 * management system.
 */
class TrackStateException : public std::exception
{
  public:
    /**
     * @brief Constructor to create a TrackStateException with a specific message.
     * @param message A string containing the error message.
     *
     * Initializes a TrackStateException object with the provided error message.
     */
    explicit TrackStateException(const std::string& message) : m_msg{message} // NOLINT
    {
    }

    /**
     * @brief Overloaded what() method to retrieve the error message.
     * @return A constant character pointer to the error message.
     *
     * Provides the error message associated with the exception.
     */
    const char* what() const noexcept override
    {
        return m_msg.what();
    }

  private:
    std::runtime_error m_msg; /**< Runtime error containing the exception message. */
};

#endif // TRACK_STATE_EXCEPTION_HPP
