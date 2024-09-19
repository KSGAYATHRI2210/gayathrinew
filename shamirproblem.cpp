#include <iostream>
#include <vector>
#include <map>
#include <cmath>

// Function to convert a string of a given base to a decimal integer
long long decodeValue(const std::string& value, int base) {
    long long result = 0;
    for (char digit : value) {
        result = result * base + (isdigit(digit) ? digit - '0' : toupper(digit) - 'A' + 10);
    }
    return result;
}

// Function to perform Lagrange interpolation and find the constant term c
long long lagrangeInterpolation(const std::vector<std::pair<int, long long>>& points, int k) {
    long long c = 0;
    for (int i = 0; i < k; ++i) {
        long long xi = points[i].first;
        long long yi = points[i].second;

        // Compute Lagrange basis polynomial L_i(x)
        long long Li = 1;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                long long xj = points[j].first;
                Li *= xj;
                Li /= (xj - xi);
            }
        }
        // Accumulate the term yi * Li
        c += yi * Li;
    }
    return c;
}

int main() {
    // Given input (you can replace this with dynamic input later)
    std::map<int, std::pair<int, std::string>> input = {
        {1, {10, "28735619723837"}},
        {2, {16, "1A228867F0CA"}},
        {3, {12, "32811A4AA0B7B"}},
        {4, {11, "917978721331A"}},
        {5, {16, "1A22886782E1"}},
        {6, {10, "28735619654702"}},
        {7, {14, "71AB5070CC4B"}},
        {8, {9, "122662581541670"}},
        {9, {8, "642121030037605"}}
    };

    int n = 9; // Number of points
    int k = 6; // Minimum number of points required to solve for the polynomial

    // Decode the input points
    std::vector<std::pair<int, long long>> points;
    for (const auto& item : input) {
        int x = item.first;
        int base = item.second.first;
        std::string encodedValue = item.second.second;
        long long y = decodeValue(encodedValue, base);
        points.push_back({x, y});
    }

    // Find the constant term c using Lagrange interpolation
    long long constantTerm = lagrangeInterpolation(points, k);

    std::cout << "The constant term c is: " << constantTerm << std::endl;

    return 0;
}
