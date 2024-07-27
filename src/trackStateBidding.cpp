#include "trackStateBidding.hpp"
#include "bid.hpp"

void BiddingStateTrack::handleArticle(std::vector<std::shared_ptr<Article>>& articles,
                                      const std::shared_ptr<Article>& article, OperationType operation)
{
    throw TrackStateException("Cannot handle articles in Bidding state");
}

void BiddingStateTrack::handleBidding(const std::vector<std::shared_ptr<Article>>& articles,
                                      std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                                      const std::vector<std::shared_ptr<User>> reviewers)
{
    for (const auto& reviewer : reviewers)
    {
        for (const auto& article : articles)
        {
            auto interest = reviewer->determineInterest(article->articleName());
            biddingMap[article] = interest;
        }
    }
}

const std::string& BiddingStateTrack::stateName()
{
    return m_stateName;
}
