#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string bwt_encode(string text) {
    int n = text.size();
    string bwt = "";
    vector<string> rotations(n);

    // Generate all rotations of the text
    for (int i = 0; i < n; i++) {
        rotations[i] = text.substr(i) + text.substr(0, i);
    }

    // Sort the rotations lexicographically
    sort(rotations.begin(), rotations.end());

    // Get the last character of each rotation
    for (int i = 0; i < n; i++) {
        bwt += rotations[i][n - 1];
    }

    return bwt;
}

string bwt_decode(string bwt) {
    int n = bwt.size();
    string text = "";
    vector<string> table(n);

    // Fill the table with empty strings
    for (int i = 0; i < n; i++) {
        table[i] = "";
    }

    // Fill the table with the sorted rotations
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            table[j] = bwt[j] + table[j];
        }
        sort(table.begin(), table.end());
    }

    // Find the original text in the table
    for (int i = 0; i < n; i++) {
        if (table[i][n - 1] == '$') {
            text = table[i];
            break;
        }
    }

    return text.substr(0, n - 1);
}

int main() {
    string text = "banana";
    string bwt = bwt_encode(text);
    string decoded_text = bwt_decode(bwt);

    cout << "Original text: " << text << endl;
    cout << "BWT encoded text: " << bwt << endl;
    cout << "Decoded text: " << decoded_text << endl;

    return 0;
}