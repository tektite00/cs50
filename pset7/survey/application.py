import csv

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
    if not name or len(name.strip()) == 0:
        return render_template("error.html", message="You must specify your Full Name.")
    elif not house:
        return render_template("error.html", message="You must specify your House.")
    elif not position:
        return render_template("error.html", message="You must specify your Quidditch Position.")
    with open('survey.csv', 'a') as fh:
        writer = csv.DictWriter(fh, fieldnames=["Name", "House", "Position"])
        writer.writerow({
            "Name":name,
            "House":house,
            "Position":position 
        })
    return redirect('/sheet')

@app.route("/sheet", methods=["GET"])
def get_sheet():
    with open('survey.csv', 'r') as fh:
        reader = csv.DictReader(fh)
        surveys = list(reader)
    return render_template("sheet.html", data=jsonify(surveys))