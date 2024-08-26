#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Player {
public:
    Player(int rating_, string nickname_) : rating(rating_), nickname(nickname_) {}

    int rating = 0;
    string nickname;
};

bool operator==(Player lhs, Player rhs) {
    return (lhs.rating == rhs.rating) && (lhs.nickname == rhs.nickname);
}

int SearchRightmostPlayerWithRating(vector<Player> players, int desired_rating) {
    int left = 0;
    int right = static_cast<int>(players.size() - 1);

    while (left < right) {
        int middle = (left + right) / 2;
        if (players[middle].rating > desired_rating) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }

    if (right == static_cast<int>(players.size()) - 1 && players[right].rating <= desired_rating) ++right;
    return right;
}

void InsertPlayerInList(vector<Player>& players, int index, Player new_player) {
    players.push_back(new_player);
    for (int i = static_cast<int>(players.size() - 1); i > index; --i) {
        players[i] = players[i - 1];
    }
    players[index] = new_player;
}

// Tests
void TestSearchRightmostPlayerWithRating() {
    vector<Player> players{{1100, "Crowbar Freeman"s},
                           {1200, "London Mollarik"s},
                           {1600, "Raziel of Kain"s},
                           {1600, "Gwinter of Rivia"s},
                           {1600, "Slayer of Fate"},
                           {3000, "Jon Know"},
                           {4000, "Caius Cosades"}
        };
    {
        int index = SearchRightmostPlayerWithRating(players, 1000);
        assert(index == 0);
    }
    {
        int index = SearchRightmostPlayerWithRating(players, 1100);
        assert(index == 1);
    }
    {
        int index = SearchRightmostPlayerWithRating(players, 1600);
        assert(index == 5);
    }
    {
        int index = SearchRightmostPlayerWithRating(players, 4000);
        assert(index == 7);
    }
    {
        int index = SearchRightmostPlayerWithRating(players, 4100);
        assert(index == 7);
    }

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestInsertPlayerInList() {
    {
        vector<Player> players{{1100, "Crowbar Freeman"s},
                               {1200, "London Mollarik"s},
                               {1600, "Raziel of Kain"s},
                               {1600, "Gwinter of Rivia"s},
                               {1600, "Slayer of Fate"},
                               {3000, "Jon Know"},
                               {4000, "Caius Cosades"}
        };
    
        Player new_player(1600, "Shmike"s);
        int index = SearchRightmostPlayerWithRating(players, new_player.rating);
        InsertPlayerInList(players, index, new_player);
        vector<Player> answer{{1100, "Crowbar Freeman"s},
                              {1200, "London Mollarik"s},
                              {1600, "Raziel of Kain"s},
                              {1600, "Gwinter of Rivia"s},
                              {1600, "Slayer of Fate"},
                              {1600, "Shmike"s},
                              {3000, "Jon Know"},
                              {4000, "Caius Cosades"}
        };
        assert (players == answer);
    }
    
    cout << __FUNCTION__ << " DONE"s << endl;
}

void Tests() {
    TestSearchRightmostPlayerWithRating();
    TestInsertPlayerInList();
}

int main() {
    Tests();
}