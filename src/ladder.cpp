#include "ladder.h"
using namespace std;

void error(string word1, string word2, string msg) {
    cout << "Error with words \"" << word1 << "\" and \"" << word2 << "\": " << msg << endl;
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d)
        return false;       // If the length difference is ever greater than d, it isn't valid.


    int i = 0, j = 0;  // indexes for both strings
    int diff = 0;      // used for tracking differences

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            diff++;
            if (diff > d) return false;  // More than allowed edits, exit early

            if (len1 > len2)          // catch up smaller str to bigger one
                i++;
            else if (len1 < len2)     // catch up smaller str to bigger one
                j++;
            else   
                i++, j++; // Substitution, meaning standard increment
        } 
        
        else
            i++, j++;   // increment if no difference
    }

    // if any extra characters remaining in either string, will never be negative, only 0 or pos.
    diff += (len1 - i);
    diff += (len2 - j);

    return diff <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "You can't transform a word into itself.");
        vector<string> empty;
        return empty;
    }
    
    // Need to make sure begin_word can be outside the word_list
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;

    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        

        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for (string word : word_list) {
            if (is_adjacent(last_word, word))

                if (visited.find(word) == visited.end()) {   // meaning if word not in visited.
                    visited.insert(word);

                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    
                    if (word == end_word)
                        return new_ladder;

                    ladder_queue.push(new_ladder);
                } 
        } 
    }

    error(begin_word, end_word, "No valid transformation was found.");
    vector<string> empty;
    return empty;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    
    while (file >> word) {
        for (char &c : word) {          // must make everything lowercase
            c = std::tolower(c);        // is there more efficient way?
        }
        word_list.insert(word);
    }

    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    int size = ladder.size();

    for (int i = 0; i < size; i++) {
        cout << ladder[i];
        if (i != size - 1)
            cout << " -> ";
    }
    cout << endl;
}

// These assert statements were given to us as test cases in the instructions.

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    assert(generate_word_ladder("code", "data", word_list).size() == 6);
    assert(generate_word_ladder("work", "play", word_list).size() == 6);
    assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
