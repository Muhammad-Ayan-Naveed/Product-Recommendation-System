# Product Recommendation System

A rule-based recommendation engine built entirely in C++ without any ML libraries.

## How It Works

Three decision trees each evaluate a user's purchase and search history using different weighting strategies:
- **Tree 0 (Purchase-biased):** Trusts purchase history more
- **Tree 1 (Search-biased):** Trusts search history more  
- **Tree 2 (Balanced):** Weights both equally

The trees vote via majority to predict the user's preferred product category. A custom Stack then serves the top recommendations from that category.

## Data Structures Used
- Custom Stack (for recommendations output)
- Arrays for product catalog and user history

## How to Run
1. Compile: `g++ project.cpp -o recommendation` or just paste it in a new file and run it.
2. Make sure `history.txt` is in the same directory
3. Run: `./recommendation`
4. Enter a User ID when prompted

## Files
- `project.cpp` — main source code
- `history.txt` — sample user history data
