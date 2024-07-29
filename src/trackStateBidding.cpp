#include "trackStateBidding.hpp"
#include "bid.hpp"

void BiddingStateTrack::handleArticle(std::vector<std::shared_ptr<Article>>& articles,
                                      const std::shared_ptr<Article>& article, OperationType operation)
{
    throw TrackStateException("Cannot handle articles in Bidding state");
}

void BiddingStateTrack::handleSelection(
    std::vector<std::shared_ptr<Article>> selectedArticles, std::shared_ptr<SelectionStrategy> selectionStrategy,
    std::unordered_map<std::shared_ptr<Article>, std::shared_ptr<Rating>> articuleRatingMap, int number)
{
    throw TrackStateException("Cannot handle selection in Bidding state");
}

void BiddingStateTrack::handleBidding(const std::vector<std::shared_ptr<Article>>& articles,
                                      std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                                      const std::vector<std::shared_ptr<User>> reviewers)
{
    for (const auto& reviewer : reviewers)
    {
        for (const auto& article : articles)
        {
            auto interest = reviewer->determineInterest();
            biddingMap[article] = interest;
        }
    }
}

void BiddingStateTrack::handleReview(const std::vector<std::shared_ptr<Article>>& articles,
                                     const std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                                     std::unordered_map<std::shared_ptr<Article>, Review>& reviewMap,
                                     const std::vector<std::shared_ptr<User>> reviewers)
{
    throw TrackStateException("Review is not allowed in bidding state");
}

const std::string& BiddingStateTrack::stateName()
{
    return m_stateName;
}
