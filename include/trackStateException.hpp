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

/**
 * @brief TrackStateException is an exception class that defines the methods that a track must implement.
 */
class TrackStateException : public std::exception
{
  public:
    /**
     * @brief Overload what() method.
     *
     * @return const char*
     */
    // LCOV_EXCL_START
    const char* what() const noexcept override
    {
        return m_msg.what();
    }
    // LCOV_EXCL_STOP

    /**
     * @brief Construct a new socket DB Wrapper Exception object
     *
     * @param message
     */
    explicit TrackStateException(const std::string& message) : m_msg{message} // NOLINT
    {
    }

  private:
    std::runtime_error m_msg;
};

#endif // TRACK_STATE_EXCEPTION_HPP
