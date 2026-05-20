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

aaplData = df[
    df["Symbol"] == "AAPL"
]

prices = list(
    aaplData["Price"]
)

print("\nCandlestick Data:\n")

windowSize = 4

for i in range(
    0,
    len(prices),
    windowSize
):

    candle = prices[i:i+windowSize]

    if len(candle) < 4:

        break

    openPrice = candle[0]

    highPrice = max(candle)

    lowPrice = min(candle)

    closePrice = candle[-1]

    print(
        "OPEN:",
        openPrice,
        "HIGH:",
        highPrice,
        "LOW:",
        lowPrice,
        "CLOSE:",
        closePrice
    )