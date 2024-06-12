from flask import Flask, request, jsonify

app = Flask(__name__)

data = []

@app.route('/sensorldr', methods=['POST'])
def post():
    content = request.get_json()
    ldrvalue = content.get("ldrvalue")
    if ldrvalue is not None:
        data.append({"ldrvalue": ldrvalue})
        return jsonify({"message": "new data saved"}), 201
    else:
        return jsonify({"message": "ldrvalue is missing"}), 400

@app.route('/sensorldr', methods=['GET'])
def get():
    return jsonify(data), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
