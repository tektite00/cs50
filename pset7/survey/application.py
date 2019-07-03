import csv
import re

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    name = request.form.get("name")
    house = request.form.get("house")
    position = request.form.get("position")
    # Validate inputs
    if not name:
        return render_template("error.html", message=":( You must specify your Full Name!")
    elif len(name.strip()) == 0 or re.search(r'\d', name):
        return render_template("error.html", message=":( Your Full Name must not contain blank or numerical values!")
    elif not house:
        return render_template("error.html", message=":( You must specify your House!")
    elif not position:
        return render_template("error.html", message=":( You must specify your Quidditch Position!")
    # Once input is validated write it to csv file
    with open('survey.csv', 'a') as fh:
        writer = csv.writer(fh)
        writer.writerow((name, house, position))
    return redirect('/sheet')  # Redirect user to sheet.html


@app.route("/sheet", methods=["GET"])
def get_sheet():
    # Open survey.csv file and load it
    with open('survey.csv', 'r') as fh:
        reader = csv.reader(fh)
        surveys = list(reader)
    return render_template("sheet.html", surveys=surveys)