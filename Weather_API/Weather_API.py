from flask import Flask, jsonify, abort, make_response
import requests

app = Flask(__name__)
d = {'dict': 1, 'dictionary': 2}


@app.route('/<string:city>', methods=['GET'])
def get_task(city):
    if city == '':
        abort(404)

    headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                             'Chrome/73.0.3683.103 Safari/537.36'}
    weather = requests.get('https://api.openweathermap.org/data/2.5/weather?q=' + city +
                           '&appid=d3035b1339c54a24bef66cb08652ac63', headers=headers, timeout=6)

    main_weather = weather.json().get('weather')[0].get('main')
    temp = weather.json().get('main')[0].get('temp') - 273.15
    pressure = weather.json().get('main')[0].get('pressure') * 0.750063755419211
    humidity = weather.json().get('main')[0].get('humidity')
    result = 'Main: ' + main_weather + '\n' + 'Temperature: ' + temp + '\n' + 'Pressure: ' + pressure + '\n' +\
             'Humidity: ' + humidity
    return result


@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Not found'}), 404)


if __name__ == '__main__':
    app.run(debug=True)
