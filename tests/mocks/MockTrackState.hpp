/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */
#ifndef _MOCK_TRACKSTATE_HPP
#define _MOCK_TRACKSTATE_HPP

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "articleInterface.hpp"
#include "bid.hpp"
#include "nlohmann/json.hpp"
#include "trackStateInterface.hpp"
#include <memory>

/**
 * @class MockTrackState
 *
 * @brief Mock class for simulating a track state object.
 *
 * The `MockTrackState` class is designed to simulate the behavior of a track state
 * for testing purposes. It provides mock implementations of methods and
 * allows you to set expectations on method calls and their return values for testing.
 *
 * This class is used in unit tests only to verify interactions with a content
 * register without actually performing real operations on it.
 */
class MockTrackState : public ITrackState
{
  public:
    /**
     * @brief MockTrackState constructor.
     */
    MockTrackState() = default;
    ~MockTrackState() = default;
    /**
     * @brief Mock method for appendArticle.
     *
     * @note This method is intended for testing purposes and does not perform any real action.
     */
    MOCK_METHOD(void, handleArticle,
                (std::vector<std::shared_ptr<Article>>&, const std::shared_ptr<Article>&, OperationType), (override));
    MOCK_METHOD(void, handleBidding,
                ((std::unordered_map<std::shared_ptr<Article>, BiddingInterest>&), const std::shared_ptr<Article>&,
                 BiddingInterest, OperationType),
                (override));

    MOCK_METHOD(const std::string&, stateName, (), (override));
};

#endif // _MOCK_TRACKSTATE_HPP
