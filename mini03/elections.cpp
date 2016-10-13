#include <algorithm>
#include <numeric>
#include "elections.hpp"

using namespace std;

vector<Ballot> filter_valid_ballots(vector<Ballot> const &all_ballots) {
	vector<Ballot> ballots;
	copy_if(all_ballots.begin(), all_ballots.end(), back_inserter(ballots),
	        [](Ballot ballot) { return ballot.chosen_candidates.size() <= 3; });
	return ballots;
}

map<Candidate, unsigned int> count_votes(vector<Ballot> const &valid_ballots) {
	map<Candidate, unsigned int> votes;
	for (const Ballot &ballot : valid_ballots) {
		for (Candidate candidate : ballot.chosen_candidates) {
			auto position = votes.find(candidate);
			if (position == votes.end()) { //not found
				votes.insert(pair<Candidate, unsigned int>(candidate, 1));
			} else {
				position->second++;
			}
		}
	}
	return votes;
}

unsigned int votes_for_party(PoliticalParty const &party, map<Candidate, unsigned int> const &votes) {
	return accumulate(votes.begin(), votes.end(), 0U,
	                  [&party](unsigned int value, pair<Candidate, unsigned int> x) {
		                  if (find(party.candidates.begin(), party.candidates.end(), x.first) != party.candidates.end())
			                  return value + x.second;
		                  return value;
	                  });
}

vector<unsigned int> votes_for_parties(vector<PoliticalParty> const &parties, map<Candidate, unsigned int> votes) {
	vector<unsigned int> result;
	transform(parties.begin(), parties.end(), back_inserter(result),
	          [&votes](PoliticalParty party) { return votes_for_party(party, votes); });
	result.resize(parties.size());
	return result;
}

set<ElectedParty>
elected_parties(vector<PoliticalParty> const &parties, map<Candidate, unsigned int> votes, unsigned int minimum) {
	vector<unsigned int> results = votes_for_parties(parties, votes);
	set<ElectedParty> electedParties;
	for (unsigned int i = 0; i < results.size(); ++i) {
		if (results[i] >= minimum) {
			ElectedParty newElectedParty = ElectedParty();
			newElectedParty.name = parties[i].name;
			newElectedParty.number_of_votes = results[i];
			electedParties.insert(newElectedParty);
		}
	}
	return electedParties;
}

unsigned int valid_votes(vector<Ballot> const &valid_ballots) {
	return accumulate(valid_ballots.begin(), valid_ballots.end(), 0U,
	                  [](int value, Ballot x) { return x.chosen_candidates.size() + value; });
}

ElectionResults process_elections(Elections const &elections) {
	ElectionResults results;
	vector<Ballot> valid_ballots = filter_valid_ballots(elections.ballots);
	results.number_of_invalid_ballots = elections.ballots.size() - valid_ballots.size();
	results.number_of_votes = valid_votes(valid_ballots);
	map<Candidate, unsigned int> votes = count_votes(valid_ballots);
	unsigned int five_percent = (results.number_of_votes + 19) / 20;
	results.elected_parties = elected_parties(elections.parties, votes, five_percent);
	return results;
}
