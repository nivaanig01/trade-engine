import pandas as pd
import mplfinance as mpf
import random
import numpy as np

df = pd.read_csv("trades.csv")

aaplData = df[
    df["Symbol"] == "AAPL"
]

prices = list(
    aaplData["Price"]
)

candles = []

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

    volume = random.randint(
        100,
        1000
    )

    candles.append(
        [
            openPrice,
            highPrice,
            lowPrice,
            closePrice,
            volume
        ]
    )

candleDF = pd.DataFrame(
    candles,
    columns=[
        "Open",
        "High",
        "Low",
        "Close",
        "Volume"
    ]
)

candleDF.index = pd.date_range(
    start="2026-01-01",
    periods=len(candleDF),
    freq="D"
)

candleDF["MA"] = (
    candleDF["Close"]
    .rolling(2)
    .mean()
)

buySignals = []

sellSignals = []

profits = []

buyPrice = None

for i in range(
    len(candleDF)
):

    if i == 0:

        buySignals.append(
            np.nan
        )

        sellSignals.append(
            np.nan
        )

        continue

    currentClose = (
        candleDF["Close"]
        .iloc[i]
    )

    currentMA = (
        candleDF["MA"]
        .iloc[i]
    )

    if currentClose > currentMA:

        buySignals.append(
            currentClose
        )

        sellSignals.append(
            np.nan
        )

        if buyPrice is None:

            buyPrice = currentClose

    else:

        buySignals.append(
            np.nan
        )

        sellSignals.append(
            currentClose
        )

        if buyPrice is not None:

            profit = (
                currentClose
                - buyPrice
            )

            profits.append(
                profit
            )

            buyPrice = None

candleDF["BUY"] = buySignals

candleDF["SELL"] = sellSignals

maPlot = mpf.make_addplot(
    candleDF["MA"],
    color="blue"
)

buyPlot = mpf.make_addplot(
    candleDF["BUY"],
    type="scatter",
    marker="^",
    markersize=100,
    color="green"
)

sellPlot = mpf.make_addplot(
    candleDF["SELL"],
    type="scatter",
    marker="v",
    markersize=100,
    color="red"
)

mpf.plot(
    candleDF,
    type="candle",
    style="charles",
    volume=True,
    title="AAPL Strategy Backtest",
    addplot=[
        maPlot,
        buyPlot,
        sellPlot
    ],
    figsize=(12, 8)
)

print("\nBacktest Results:\n")

print(
    "Total Trades:",
    len(profits)
)

if len(profits) > 0:

    print(
        "Total Profit:",
        sum(profits)
    )

    print(
        "Average Profit:",
        sum(profits)
        / len(profits)
    )

else:

    print(
        "No completed trades."
    )