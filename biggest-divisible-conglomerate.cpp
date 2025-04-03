#include "bdc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Helper function to determine if a value can be added to the conglomerate only if it is divisible
bool CanBecomeAdded(int num, const vector<int>& conglomerate) {
    for (size_t i = 0; i < conglomerate.size(); i++) { //range-based loop
        int existing = conglomerate[i];  
        if (num % existing != 0 && existing % num != 0) {
            return false; // Violates divisibility requirement
        }
    }
    return true;
}

// Recursive function to find the largest conglomerate
vector<int> findLargestConglomerate(vector<int>& values, vector<int> current) {
    if (values.empty()) {
        return current; // Base case: return valid conglomerate
    }

    vector<int> largestConglomerate = current; // Set the current conglomerate as the largest for tracking purposes
    for (size_t i = 0; i < values.size(); i++) { // Iterate through the list and check if they can be added.
        // If so, make a new list adding the new current value
        if (CanBecomeAdded(values[i], current)) {
            vector<int> UpdatedLargestConglomerate = current;
            UpdatedLargestConglomerate.push_back(values[i]);

            // Recursion used here to continue finding the best conglomerate when iterating through the values in the loop
            vector<int> remainingValues(values.begin() + i + 1, values.end());
            vector<int> result = findLargestConglomerate(remainingValues, UpdatedLargestConglomerate); // Start the next value after the current and keep updating it

            if (result.size() > largestConglomerate.size()) { // Check if the result is bigger than our best conglomerate; if so, assign it as the final result
                largestConglomerate = result; // Final list with largest conglomerate
            }
        }
    }
    return largestConglomerate;
}

// This function finds the biggest divisible conglomerate in the given input vector.
vector<int> biggest_divisible_conglomerate(vector<int> input) {
    vector<int> current;
    return findLargestConglomerate(input, current);
}

// Function to convert a vector of integers to a string representation for easy printing
string vec_to_string(vector<int> v) {
    string result = "{";
    for (size_t i = 0; i < v.size(); i++) {
        result += to_string(v[i]);
        if (i != v.size() - 1) result += ", ";
    }
    result += "}";
    return result;
}
