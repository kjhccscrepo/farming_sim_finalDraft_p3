//
// Created by kistj on 12/3/2025.
//
#include "test_random.hpp"
int test_random::getNumFromFeed() {
    if (number_Feed_tape.empty() == true) {
        return -1;
    }
    if (numFeedIterator == number_Feed_tape.size()) {
        numFeedIterator = 0;
    }
    return number_Feed_tape[numFeedIterator];
}

int test_random::getMyNum() {
    if (!use_feed) {
        return myNum;
    } else {
        const int n = getNumFromFeed();
        numFeedIterator++;
        return n;
    }
}

void test_random::setN(const int &n) {
    myNum = n;
}

void test_random::toggleNumFeed() {
    if (use_feed == true) {
        use_feed = false;
    } else {
        use_feed = true;
    }
}

void test_random::pushNumFeed(const int &n) {
    if (use_feed == false) {
        toggleNumFeed();
    }
    number_Feed_tape.push_back(n);
}

void test_random::clearNumFeed() {
    numFeedIterator = 0;
    number_Feed_tape.clear();
}

void test_random::setNumFeed(const std::vector<int> &newNumFeed) {
    if (use_feed == false) {
        toggleNumFeed();
    }
    clearNumFeed();
    number_Feed_tape = newNumFeed;
}

int test_random::get_random_number() {
    return getMyNum();
}

int test_random::get_random_number_in_range(const int &minimum, const int &maximum) {
    return getMyNum();
}
