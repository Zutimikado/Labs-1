from flask import Flask, jsonify, abort, make_response

app = Flask(__name__)


@app.route('/<string:city>', methods=['GET'])
def get_task(city):
    if city == '':
        abort(404)
    return jsonify(city)


@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Not found'}), 404)


if __name__ == '__main__':
    app.run(debug=True)
