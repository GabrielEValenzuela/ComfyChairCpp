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

void BiddingStateTrack::handleBidding(std::unordered_map<std::shared_ptr<Article>, BiddingInterest>& interestMap,
                                      const std::shared_ptr<Article>& article, BiddingInterest interest,
                                      OperationType operation)
{
    switch (operation)
    {
    case OperationType::Create:
        interestMap[article] = interest;
        break;
    case OperationType::Update:
        updateBidding(interestMap, article, interest);
        break;
    case OperationType::Delete:
        removeBidding(interestMap, article, interest);
        break;
    // LCOV_EXCL_START //Never reached.
    default:
        break;
        // LCOV_EXCL_STOP
    }
}

const std::string& BiddingStateTrack::stateName()
{
    return m_stateName;
}

void BiddingStateTrack::updateBidding(std::unordered_map<std::shared_ptr<Article>, BiddingInterest>& interestMap,
                                      const std::shared_ptr<Article>& article, BiddingInterest interest)
{
    const auto& targetTitle = article->articleName();
    auto it = interestMap.find(article);
    if (it != interestMap.end())
    {
        it->second = interest;
    }
    // LCOV_EXCL_START //ToDo Remove when article is fully implemented
    else
    {
        std::cout << "Article not found" << std::endl;
    }
    // LCOV_EXCL_STOP
}

void BiddingStateTrack::removeBidding(std::unordered_map<std::shared_ptr<Article>, BiddingInterest>& interestMap,
                                      const std::shared_ptr<Article>& article, BiddingInterest interest)
{
    const auto& targetTitle = article->articleName();
    auto it = interestMap.find(article);
    if (it != interestMap.end())
    {
        interestMap.erase(it);
    }
    // LCOV_EXCL_START //ToDo Remove when article is fully implemented
    else
    {
        std::cout << "Article not found" << std::endl;
    }
    // LCOV_EXCL_STOP
}
