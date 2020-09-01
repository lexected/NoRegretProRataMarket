#pragma once

#include <vector>
#include <memory>
#include <random>

#include "Player.h"

class Adversary {
public:
	Adversary(unsigned int playerCount);

	void playRound();
private:
	std::vector<std::unique_ptr<Player>> m_players;

	std::default_random_engine m_randomEngine;

	std::unique_ptr<std::discrete_distribution<unsigned int>> m_aggressingQuantityDistribution;
};

