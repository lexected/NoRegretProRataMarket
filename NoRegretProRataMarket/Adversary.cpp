#include "Adversary.h"

#include "Player.h"

#include <ctime>

Adversary::Adversary(unsigned int playerCount)
	: m_randomEngine((unsigned int)time(0)) {
	while (playerCount > 0) {
		m_players.push_back(std::make_unique<Player>(this, playerCount));
		--playerCount;
	}

	std::vector<double> weights;
	for (int i = 4; i < 104; ++i) {
		weights.push_back(1.0 / (i));
	}

	m_aggressingQuantityDistribution = std::make_unique<std::discrete_distribution<unsigned int>>(weights.begin(), weights.end());
}

void Adversary::playRound() {
	std::vector<unsigned int> actionsChosen(m_players.size(), 0);

	unsigned int cumulativeAction = 0;
	unsigned int playerIndex = 0;
	for (const auto& player : m_players) {
		unsigned int action = player->chooseAction();
		cumulativeAction += action;
		actionsChosen[playerIndex] = action;

		++playerIndex;
	}

	unsigned int aggressingQuantity = (m_aggressingQuantityDistribution->operator()(m_randomEngine) + 90)*10;

	playerIndex = 0;
	for (const auto& player : m_players) {
		unsigned int everyoneElsesCumulativeAction = cumulativeAction - actionsChosen[playerIndex];
		auto wholeActionSpectrum = player->getActions();
		std::vector<double> allocatedQuantities;
		allocatedQuantities.resize(wholeActionSpectrum.size(), 0);
		std::transform(wholeActionSpectrum.cbegin(), wholeActionSpectrum.cend(), allocatedQuantities.begin(), [&aggressingQuantity, &cumulativeAction](auto particularAction) {
			double fractionOfTheAggressingQuantity = ((double)particularAction)/(particularAction + cumulativeAction);
			return (unsigned int)std::floor(fractionOfTheAggressingQuantity * aggressingQuantity);
		});
		player->caulculateLosses(allocatedQuantities);

		++playerIndex;
	}
}
