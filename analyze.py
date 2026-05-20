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

prices = aaplData["Price"]
movingAverage = prices.rolling(3).mean()

plt.plot(
    prices,
    label="Price"
)

plt.plot(
    movingAverage,
    label="Moving Average"
)

plt.title(
    "AAPL Price + Moving Average"
)

plt.xlabel(
    "Trade Number"
)

plt.ylabel(
    "Price"
)

plt.legend()

plt.show()