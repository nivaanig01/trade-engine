import pandas as pd
import mplfinance as mpf
import random

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

addPlot = mpf.make_addplot(
    candleDF["MA"],
    color="cyan"
)

mpf.plot(
    candleDF,
    type="candle",
    style="charles",
    volume=True,
    addplot=addPlot,
    title="AAPL Professional Trading Chart",
    figsize=(12, 8)
)