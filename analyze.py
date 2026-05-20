import pandas as pd
import matplotlib.pyplot as plt

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

aaplData = df[
    df["Symbol"] == "AAPL"
]

plt.plot(
    aaplData["Price"]
)

plt.title(
    "AAPL Price History"
)

plt.xlabel(
    "Trade Number"
)

plt.ylabel(
    "Price"
)

plt.show()