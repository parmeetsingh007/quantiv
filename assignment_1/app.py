from flask import Flask, render_template, request, redirect, url_for
from monte_carlo import run_monte_carlo, generate_paths

import matplotlib
matplotlib.use("Agg")  # use non-GUI backend
import matplotlib.pyplot as plt

from io import BytesIO
import base64
from datetime import datetime

from flask_sqlalchemy import SQLAlchemy
from flask_bcrypt import Bcrypt
from flask_login import (
    LoginManager,
    UserMixin,
    login_user,
    logout_user,
    login_required,
    current_user,
)

app = Flask(__name__)

# --- Basic config ---
app.config["SECRET_KEY"] = "change_this_later_123"  # just needs to be non-empty
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///mc.db"
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

db = SQLAlchemy(app)
bcrypt = Bcrypt(app)
login_manager = LoginManager(app)
login_manager.login_view = "login"  # if not logged in, redirect here


# --- Models ---


class User(db.Model, UserMixin):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password_hash = db.Column(db.String(128), nullable=False)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)

    def set_password(self, password):
        self.password_hash = bcrypt.generate_password_hash(password).decode("utf-8")

    def check_password(self, password):
        return bcrypt.check_password_hash(self.password_hash, password)


class Simulation(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.Integer, db.ForeignKey("user.id"), nullable=False)
    S0 = db.Column(db.Float, nullable=False)
    sigma = db.Column(db.Float, nullable=False)
    r = db.Column(db.Float, default=0.05)
    T = db.Column(db.Float, default=1.0)
    num_simulations = db.Column(db.Integer, default=1000)
    average_price = db.Column(db.Float, nullable=False)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)

    user = db.relationship("User", backref="simulations")


@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))


# --- Routes ---


@app.route("/")
def index():
    # If already logged in, go straight to new simulation page
    if current_user.is_authenticated:
        return redirect(url_for("new_simulation"))
    return render_template("home.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if current_user.is_authenticated:
        return redirect(url_for("new_simulation"))

    if request.method == "POST":
        username = request.form.get("username", "").strip()
        password = request.form.get("password", "").strip()

        error = None

        if not username or not password:
            error = "Username and password are required."
        else:
            existing = User.query.filter_by(username=username).first()
            if existing:
                error = "Username already taken. Choose another."

        if error:
            return render_template("register.html", error=error)

        # Create new user
        user = User(username=username)
        user.set_password(password)
        db.session.add(user)
        db.session.commit()

        # Log the user in directly after registration (optional)
        login_user(user)
        return redirect(url_for("new_simulation"))

    return render_template("register.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    if current_user.is_authenticated:
        return redirect(url_for("new_simulation"))

    if request.method == "POST":
        username = request.form.get("username", "").strip()
        password = request.form.get("password", "").strip()

        user = User.query.filter_by(username=username).first()
        if user and user.check_password(password):
            login_user(user)
            return redirect(url_for("new_simulation"))
        else:
            error = "Invalid username or password."
            return render_template("login.html", error=error)

    return render_template("login.html")


@app.route("/logout")
@login_required
def logout():
    logout_user()
    return redirect(url_for("index"))


@app.route("/new_simulation", methods=["GET", "POST"])
@login_required
def new_simulation():
    if request.method == "POST":
        try:
            S0 = float(request.form.get("S0", 0))
            sigma = float(request.form.get("sigma", 0))

            error = None
            if S0 <= 0:
                error = "Starting price (S0) must be positive."
            elif sigma < 0:
                error = "Volatility (sigma) cannot be negative."

            if error:
                return render_template("new_simulation.html", error=error)

            # 1) Run Monte Carlo to get average final price
            r = 0.05
            T = 1.0
            n_sims = 1000

            avg_price = run_monte_carlo(S0, sigma, r=r, T=T, n_sims=n_sims)

            # 2) Generate 5 price paths
            paths = generate_paths(S0, sigma, r=r, T=T, n_paths=5, steps=252)

            # 3) Plot the paths with matplotlib
            fig, ax = plt.subplots()
            for path in paths:
                ax.plot(path)

            ax.set_title("Sample Monte Carlo Price Paths")
            ax.set_xlabel("Time step")
            ax.set_ylabel("Price")

            buf = BytesIO()
            fig.savefig(buf, format="png", bbox_inches="tight")
            buf.seek(0)
            plot_data = base64.b64encode(buf.read()).decode("ascii")
            plt.close(fig)

            # 4) Save this simulation to the database (History)
            sim = Simulation(
                user_id=current_user.id,
                S0=S0,
                sigma=sigma,
                r=r,
                T=T,
                num_simulations=n_sims,
                average_price=avg_price,
            )
            db.session.add(sim)
            db.session.commit()

            # 5) Render result page
            return render_template(
                "result.html",
                S0=S0,
                sigma=sigma,
                avg_price=avg_price,
                plot_data=plot_data,
            )

        except ValueError:
            return render_template("new_simulation.html",
                                   error="Please enter valid numbers.")

    return render_template("new_simulation.html")


@app.route("/history")
@login_required
def history():
    sims = (
        Simulation.query
        .filter_by(user_id=current_user.id)
        .order_by(Simulation.created_at.desc())
        .all()
    )
    return render_template("history.html", simulations=sims)


# Create tables if they don't exist
with app.app_context():
    db.create_all()


if __name__ == "__main__":
    app.run(debug=True)
