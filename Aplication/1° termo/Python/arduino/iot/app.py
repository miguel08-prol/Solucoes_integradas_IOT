from flask import Flask, render_template
import serial
import time

# ATENÇÃO: Verifique a porta COM correta no seu IDE do Arduino (em Ferramentas > Porta)
# No Windows, será algo como 'COM3', 'COM4', etc.

try:
    arduino = serial.Serial('COM3', 9600, timeout=1)
    time.sleep(2) # Um tempo para a porta serial se estabilizar
except serial.SerialException as e:
    print(f"Erro ao conectar com o Arduino: {e}")
    arduino = None

app = Flask(__name__)

# Rota principal que renderiza a página HTML
@app.route('/')
def index():
    return render_template('index.html')

# Rota que recebe os comandos do HTML e os envia para o Arduino
@app.route('/control/<led_num>/<action>')
def control(led_num, action):
    if arduino:
        command = ''
        if led_num == '1':
            command = 'A' if action == 'on' else 'a'
        elif led_num == '2':
            command = 'B' if action == 'on' else 'b'
        
        if command:
            arduino.write(command.encode())
            return f"Comando '{command}' enviado para o LED {led_num}."
        else:
            return "Comando inválido."
    else:
        return "Arduino não conectado."

if __name__ == '__main__':
     app.run(debug=True, host='0.0.0.0', port=5000, use_reloader=False)