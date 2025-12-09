import numpy as np
import math

def run_monte_carlo(S0, sigma, r=0.05, T=1.0, n_sims=1000):
    """
    Simple Monte Carlo simulation for final price after 1 year.
    S0: starting price
    sigma: volatility
    r: interest rate
    T: time (years)
    n_sims: number of random simulations
    """
    # Random normal values Z
    Z = np.random.normal(0, 1, n_sims)

    # Formula: S_T = S0 * exp((r - 0.5 * sigma^2) * T + sigma * sqrt(T) * Z)
    prices = S0 * np.exp((r - 0.5 * sigma**2) * T + sigma * math.sqrt(T) * Z)

    # Average of all final prices
    avg_price = float(prices.mean())
    return avg_price

if __name__ == "__main__":
    S0 = 100.0      # starting price
    sigma = 0.2     # volatility
    result = run_monte_carlo(S0, sigma)
    print("Average final price:", result)
