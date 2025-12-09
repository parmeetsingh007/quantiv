import numpy as np
import math

def run_monte_carlo(S0, sigma, r=0.05, T=1.0, n_sims=1000):
    """
    Simple Monte Carlo simulation for final price after 1 year.
    """
    Z = np.random.normal(0, 1, n_sims)
    prices = S0 * np.exp((r - 0.5 * sigma**2) * T + sigma * math.sqrt(T) * Z)
    avg_price = float(prices.mean())
    return avg_price


def generate_paths(S0, sigma, r=0.05, T=1.0, n_paths=5, steps=252):
    """
    Generate multiple full price paths over time using Geometric Brownian Motion.
    Returns a 2D list: paths[path_index][time_step]
    """
    dt = T / steps
    paths = []

    for _ in range(n_paths):
        path = [S0]
        price = S0
        for _ in range(steps):
            Z = np.random.normal(0, 1)
            price = price * math.exp((r - 0.5 * sigma**2) * dt + sigma * math.sqrt(dt) * Z)
            path.append(price)
        paths.append(path)

    return paths
