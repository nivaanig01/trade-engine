import pandas as pd

df = pd.read_csv("trades.csv")

print("\nTrade Dataset:\n")

print(df)

print("\nAnalytics:\n")

print(
    "Total Trades:",
    len(df)
)

print(
    "Highest Price:",
    df["Price"].max()
)

print(
    "Lowest Price:",
    df["Price"].min()
)

print(
    "Average Price:",
    df["Price"].mean()
)

print(
    "Total Quantity:",
    df["Quantity"].sum()
)

print(
    "Symbols:",
    df["Symbol"].unique()
)