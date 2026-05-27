import pandas as pd
import mplfinance as mpf
import random
import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

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



fig = plt.figure()

fig, ax = plt.subplots()

def animate(frame):

    newPrice = random.randint(
        80,
        250
    )

    newTrade = pd.DataFrame(
        [
            {
                "BuyID": 9999,
                "SellID": 9999,
                "Price": newPrice,
                "Quantity": 1,
                "Timestamp": time.ctime(),
                "Symbol": random.choice(["AAPL", "TSLA"])
            }
        ]
    )

    newTrade.to_csv(
        "trades.csv",
        mode="a",
        header=False,
        index=False
    )

    ax.clear()

    mpf.plot(
        candleDF,
        type="candle",
        style="charles",
        volume=False,
        mav=(2),
        ax=ax
    )

ani = animation.FuncAnimation(
    fig,
    animate,
    interval=3000,
    cache_frame_data=False
)

plt.show()

print("\nBacktest Results:\n")

print(
    "Total Trades:",
    len(profits)
)

if len(profits) > 0:

    totalProfit = sum(
        profits
    )

    averageProfit = (
        totalProfit
        / len(profits)
    )

    winningTrades = 0

    for p in profits:

        if p > 0:

            winningTrades += 1

    winRate = (
        winningTrades
        / len(profits)
    ) * 100

    print(
        "Total Profit:",
        totalProfit
    )

    print(
        "Average Profit:",
        averageProfit
    )

    print(
        "Best Trade:",
        max(profits)
    )

    print(
        "Worst Trade:",
        min(profits)
    )

    print(
        "Win Rate:",
        round(winRate, 2),
        "%"
    )

else:

    print(
        "No completed trades."
    )

equityCurve = []

balance = 1000

for p in profits:

    balance += p

    equityCurve.append(
        balance
    )

if len(equityCurve) > 0:

    import matplotlib.pyplot as plt

    plt.plot(
        equityCurve
    )

    plt.title(
        "Strategy Equity Curve"
    )

    plt.xlabel(
        "Trade Number"
    )

    plt.ylabel(
        "Account Balance"
    )

    plt.show()

peak = equityCurve[0]

maxDrawdown = 0

for value in equityCurve:

    if value > peak:

        peak = value

    drawdown = peak - value

    if drawdown > maxDrawdown:

        maxDrawdown = drawdown

print("\nRisk Analytics:\n")

print(
    "Maximum Drawdown:",
    maxDrawdown
)  

print("\nStrategy Comparison:\n")

maStrategyProfit = sum(
    profits
)

momentumProfit = 0

for i in range(
    1,
    len(prices)
):

    if prices[i] > prices[i - 1]:

        momentumProfit += (
            prices[i]
            - prices[i - 1]
        )

print(
    "Moving Average Strategy Profit:",
    maStrategyProfit
)

print(
    "Momentum Strategy Profit:",
    momentumProfit
)

if maStrategyProfit > momentumProfit:

    print(
        "Best Strategy: Moving Average"
    )

elif momentumProfit > maStrategyProfit:

    print(
        "Best Strategy: Momentum"
    )

else:

    print(
        "Strategies Performed Equally"
    )

print("\nParameter Optimization:\n")

bestWindow = None

bestProfit = -999999

for window in [2, 3, 5]:

    testProfit = 0

    rollingMA = (
        candleDF["Close"]
        .rolling(window)
        .mean()
    )

    for i in range(
        window,
        len(candleDF)
    ):

        currentClose = (
            candleDF["Close"]
            .iloc[i]
        )

        currentMA = (
            rollingMA
            .iloc[i]
        )

        previousClose = (
            candleDF["Close"]
            .iloc[i - 1]
        )

        if currentClose > currentMA:

            testProfit += (
                currentClose
                - previousClose
            )

    print(
        "Window",
        window,
        "Profit:",
        round(testProfit, 2)
    )

    if testProfit > bestProfit:

        bestProfit = testProfit

        bestWindow = window

print(
    "\nBest MA Window:",
    bestWindow
)

print(
    "Best Window Profit:",
    round(bestProfit, 2)
)
print("\nPortfolio Analytics:\n")

cashBalance = 10000

sharesOwned = 0

for price in prices:

    if price < 100:

        sharesOwned += 1

        cashBalance -= price

    elif sharesOwned > 0:

        sharesOwned -= 1

        cashBalance += price

latestPrice = prices[-1]

portfolioValue = (
    cashBalance
    + sharesOwned * latestPrice
)

print(
    "Cash Balance:",
    round(cashBalance, 2)
)

print(
    "Shares Owned:",
    sharesOwned
)

print(
    "Latest Price:",
    latestPrice
)

print(
    "Total Portfolio Value:",
    round(portfolioValue, 2)
)

print("\nMulti-Asset Portfolio:\n")

symbols = df["Symbol"].unique()

for symbol in symbols:

    symbolData = df[
        df["Symbol"] == symbol
    ]

    symbolPrices = list(
        symbolData["Price"]
    )

    averagePrice = (
        sum(symbolPrices)
        / len(symbolPrices)
    )

    highestPrice = max(
        symbolPrices
    )

    lowestPrice = min(
        symbolPrices
    )

    print(
        symbol
    )

    print(
        "Trades:",
        len(symbolPrices)
    )

    print(
        "Average Price:",
        round(averagePrice, 2)
    )

    print(
        "Highest Price:",
        highestPrice
    )

    print(
        "Lowest Price:",
        lowestPrice
    )

    print()

print("\nAdvanced Risk Metrics:\n")

if len(profits) > 1:

    averageReturn = (
        sum(profits)
        / len(profits)
    )

    variance = 0

    for p in profits:

        variance += (
            p - averageReturn
        ) ** 2

    variance /= len(profits)

    standardDeviation = (
        variance ** 0.5
    )

    if standardDeviation != 0:

        sharpeRatio = (
            averageReturn
            / standardDeviation
        )

    else:

        sharpeRatio = 0

    print(
        "Average Return:",
        round(averageReturn, 2)
    )

    print(
        "Risk (Std Dev):",
        round(standardDeviation, 2)
    )

    print(
        "Sharpe Ratio:",
        round(sharpeRatio, 2)
    )

else:

    print(
        "Not enough trades for Sharpe Ratio."
    )

print("\nCorrelation Analytics:\n")

aaplPrices = list(
    df[
        df["Symbol"] == "AAPL"
    ]["Price"]
)

tslaPrices = list(
    df[
        df["Symbol"] == "TSLA"
    ]["Price"]
)

minimumLength = min(
    len(aaplPrices),
    len(tslaPrices)
)

if minimumLength > 1:

    aaplPrices = (
        aaplPrices[:minimumLength]
    )

    tslaPrices = (
        tslaPrices[:minimumLength]
    )

    correlationMatrix = np.corrcoef(
        aaplPrices,
        tslaPrices
    )

    correlation = (
        correlationMatrix[0][1]
    )

    print(
        "AAPL-TSLA Correlation:",
        round(correlation, 2)
    )

    if correlation > 0.7:

        print(
            "Strong Positive Correlation"
        )

    elif correlation < -0.7:

        print(
            "Strong Negative Correlation"
        )

    else:

        print(
            "Weak/Moderate Correlation"
        )

else:

    print(
        "Not enough data for correlation."
    )

print("\nMarket Volatility Index:\n")

priceChanges = []

for i in range(
    1,
    len(prices)
):

    change = abs(
        prices[i]
        - prices[i - 1]
    )

    priceChanges.append(
        change
    )

if len(priceChanges) > 0:

    averageVolatility = (
        sum(priceChanges)
        / len(priceChanges)
    )

    maxVolatility = max(
        priceChanges
    )

    print(
        "Average Volatility:",
        round(averageVolatility, 2)
    )

    print(
        "Maximum Single Move:",
        round(maxVolatility, 2)
    )

    if averageVolatility > 50:

        print(
            "Market State: HIGH VOLATILITY"
        )

    elif averageVolatility > 20:

        print(
            "Market State: MODERATE VOLATILITY"
        )

    else:

        print(
            "Market State: LOW VOLATILITY"
        )

else:

    print(
        "Not enough data for volatility analysis."
    )

print("\nMarket Regime Classification:\n")

overallTrend = (
    prices[-1]
    - prices[0]
)

if averageVolatility > 50:

    regime = "VOLATILE"

elif overallTrend > 100:

    regime = "BULL MARKET"

elif overallTrend < -100:

    regime = "BEAR MARKET"

else:

    regime = "SIDEWAYS MARKET"

print(
    "Overall Trend:",
    overallTrend
)

print(
    "Detected Regime:",
    regime
)

if regime == "BULL MARKET":

    print(
        "Momentum strategies favored."
    )

elif regime == "BEAR MARKET":

    print(
        "Defensive strategies favored."
    )

elif regime == "VOLATILE":

    print(
        "Risk management critical."
    )

else:

    print(
        "Mean reversion strategies favored."
    )

print("\nAdaptive Strategy Engine:\n")

if regime == "BULL MARKET":

    selectedStrategy = (
        "Momentum Strategy"
    )

elif regime == "BEAR MARKET":

    selectedStrategy = (
        "Defensive Strategy"
    )

elif regime == "VOLATILE":

    selectedStrategy = (
        "Risk-Control Strategy"
    )

else:

    selectedStrategy = (
        "Mean Reversion Strategy"
    )

print(
    "Selected Strategy:",
    selectedStrategy
)

if selectedStrategy == "Momentum Strategy":

    print(
        "Focus on trend-following trades."
    )

elif selectedStrategy == "Defensive Strategy":

    print(
        "Reduce exposure and preserve capital."
    )

elif selectedStrategy == "Risk-Control Strategy":

    print(
        "Use smaller positions and tighter controls."
    )

else:

    print(
        "Trade price reversals cautiously."
    )

print("\nPosition Sizing Engine:\n")

baseCapital = portfolioValue

if regime == "VOLATILE":

    riskPercent = 0.02

elif regime == "BULL MARKET":

    riskPercent = 0.10

elif regime == "BEAR MARKET":

    riskPercent = 0.03

else:

    riskPercent = 0.05

positionSize = (
    baseCapital
    * riskPercent
)

print(
    "Portfolio Capital:",
    round(baseCapital, 2)
)

print(
    "Risk Allocation:",
    int(riskPercent * 100),
    "%"
)

print(
    "Recommended Position Size:",
    round(positionSize, 2)
)

if riskPercent <= 0.03:

    print(
        "Defensive capital allocation active."
    )

elif riskPercent >= 0.10:

    print(
        "Aggressive capital deployment active."
    )

else:

    print(
        "Balanced capital allocation active."
    ) 

print("\nAutomated Risk Shutdown System:\n")

shutdownTriggered = False

if averageVolatility > 80:

    shutdownTriggered = True

if sharpeRatio < -1:

    shutdownTriggered = True

if maxDrawdown > 150:

    shutdownTriggered = True

if shutdownTriggered:

    print(
        "RISK SHUTDOWN ACTIVATED"
    )

    print(
        "Trading activity halted."
    )

    print(
        "System entering protection mode."
    )

else:

    print(
        "System operating normally."
    )

    print(
        "Risk conditions acceptable."
    )