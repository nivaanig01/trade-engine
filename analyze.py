import pandas as pd
import mplfinance as mpf

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

    candles.append(
        [
            openPrice,
            highPrice,
            lowPrice,
            closePrice
        ]
    )

candleDF = pd.DataFrame(
    candles,
    columns=[
        "Open",
        "High",
        "Low",
        "Close"
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
    candleDF["MA"]
)

mpf.plot(
    candleDF,
    type="candle",
    style="yahoo",
    title="AAPL Professional Chart",
    addplot=addPlot
)