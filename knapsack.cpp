#include <iostream>
using namespace std;

int main() {
    int N, weight[100], cost[100], totalWeight = 0;
    cout << "Enter the number of items: ";
    cin >> N;

    cout << "Enter the weight & cost of item:" << endl;
    for (int i = 0; i < N; i++) {
        cin >> weight[i] >> cost[i];
        totalWeight += weight[i];
    }

    int dp[101][1001] = {0}; // dp[i][w] = max cost using first i items with weight limit w
    bool keep[101][1001] = {false}; // keep[i][w] = whether to keep item i at weight w

    for (int i = 1; i <= N; i++) {
        for (int w = 0; w <= totalWeight; w++) {
            if (weight[i - 1] <= w) {
                if (dp[i - 1][w] < dp[i - 1][w - weight[i - 1]] + cost[i - 1]) {
                    dp[i][w] = dp[i - 1][w - weight[i - 1]] + cost[i - 1];
                    keep[i][w] = true;
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int maxProfit = dp[N][totalWeight];
    int w = totalWeight;
    int trace[100], size = 0;

    for (int i = N; i > 0; i--) {
        if (keep[i][w]) {
            trace[size++] = i;
            w -= weight[i - 1];
        }
    }

    cout << "Max Profit: " << maxProfit << " (w = " << totalWeight - w << ")" << endl;
    cout << "Item Choice: ";
    for (int i = size - 1; i >= 0; i--) {
        cout << trace[i] << " ";
    }
    cout << "(W = " << totalWeight - w << ")" << endl;

    cout << "Most Expensive Cost (Per Capacity) = ";
    for (int i = 1; i <= totalWeight; i++) {
        cout << dp[N][i] << " ";
    }
    cout << endl;

    return 0;
}
