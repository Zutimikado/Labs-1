from flask import Flask, jsonify, abort, make_response
import requests

app = Flask(__name__)
API_KEY = 'd3035b1339c54a24bef66cb08652ac63'


@app.route('/<string:city>', methods=['GET'])
def get_weather(city):
    weather = requests.get(f"https://api.openweathermap.org/data/2.5/weather?q={city}&appid={API_KEY}", timeout=6)

    if city == '' or weather.status_code == 404:
        abort(404)

    main_weather = weather.json().get('weather')[0].get('main')
    temp = weather.json().get('main').get('temp') - 273.15
    pressure = int(weather.json().get('main').get('pressure') * 0.750063755419211)
    humidity = weather.json().get('main').get('humidity')
    result = {
        'Main': main_weather,
        'Temp': temp,
        'Pressure': pressure,
        'Humidity': humidity,
        'City': city
    }

    return make_response(jsonify(result))


@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Not found'}), 404)


if __name__ == '__main__':
    app.run(debug=True)
