from flask import Flask, render_template, jsonify
import serial
import serial.tools.list_ports
import time

app = Flask(__name__)

# Configuração do Arduino
def encontrar_conectar_arduino():
    """Encontra e conecta com o Arduino automaticamente"""
    print("🔍 Procurando Arduino...")
    
    # Lista todas as portas COM disponíveis
    portas = serial.tools.list_ports.comports()
    portas_disponiveis = []
    
    for porta in portas:
        portas_disponiveis.append(porta.device)
        print(f"   📍 {porta.device} - {porta.description}")
    
    if not portas_disponiveis:
        print("❌ Nenhuma porta COM encontrada!")
        return None
    
    # Tentar portas comuns
    portas_tentativas = ['COM3', 'COM4', 'COM5', 'COM6', 'COM7']
    
    for porta in portas_tentativas:
        if porta in portas_disponiveis:
            try:
                print(f"🔄 Tentando conectar na {porta}...")
                arduino = serial.Serial(porta, 9600, timeout=1)
                time.sleep(2)  # Aguardar inicialização do Arduino
                
                # Testar comunicação
                arduino.write(b'S')
                time.sleep(0.5)
                
                # Ler resposta de teste
                if arduino.in_waiting:
                    resposta = arduino.readline().decode('utf-8').strip()
                    print(f"📡 Resposta do Arduino: {resposta}")
                
                print(f"✅ Conectado com sucesso na {porta}!")
                return arduino
                
            except Exception as e:
                print(f"❌ Falha na {porta}: {e}")
    
    print("🚨 Não foi possível conectar em nenhuma porta!")
    return None

# Conectar com Arduino
arduino = encontrar_conectar_arduino()

# Estado dos LEDs
estado_leds = {'led1': False, 'led2': False, 'led3': False}

def ler_resposta_arduino():
    """Lê dados do Arduino de forma não-bloqueante"""
    if arduino and arduino.in_waiting > 0:
        try:
            linha = arduino.readline().decode('utf-8').strip()
            if linha:
                print(f"📡 Arduino: {linha}")
                return linha
        except Exception as e:
            print(f"❌ Erro ao ler Arduino: {e}")
    return None

def processar_resposta_arduino(resposta):
    """Processa a resposta do Arduino"""
    if not resposta:
        return None
    
    if resposta == "LED_VERDE_ON":
        estado_leds.update({'led1': True, 'led2': False, 'led3': False})
        return {'tipo': 'led', 'led': 1, 'estado': 'on'}
    
    elif resposta == "LED_VERDE_OFF":
        estado_leds['led1'] = False
        return {'tipo': 'led', 'led': 1, 'estado': 'off'}
    
    elif resposta == "LED_AMARELO_ON":
        estado_leds.update({'led1': False, 'led2': True, 'led3': False})
        return {'tipo': 'led', 'led': 2, 'estado': 'on'}
    
    elif resposta == "LED_AMARELO_OFF":
        estado_leds['led2'] = False
        return {'tipo': 'led', 'led': 2, 'estado': 'off'}
    
    elif resposta == "LED_VERMELHO_ON":
        estado_leds.update({'led1': False, 'led2': False, 'led3': True})
        return {'tipo': 'led', 'led': 3, 'estado': 'on'}
    
    elif resposta == "LED_VERMELHO_OFF":
        estado_leds['led3'] = False
        return {'tipo': 'led', 'led': 3, 'estado': 'off'}
    
    elif resposta == "LEDS_RESETADOS":
        estado_leds.update({'led1': False, 'led2': False, 'led3': False})
        return {'tipo': 'leds_reset'}
    
    elif resposta.startswith("STATUS:"):
        # Formato: STATUS:VERDE_ON,AMARELO_OFF,VERMELHO_OFF
        status_str = resposta.replace("STATUS:", "")
        estados = status_str.split(',')
        
        estado_leds['led1'] = "VERDE_ON" in estados[0]
        estado_leds['led2'] = "AMARELO_ON" in estados[1]
        estado_leds['led3'] = "VERMELHO_ON" in estados[2]
        return {'tipo': 'status_leds'}
    
    elif resposta.startswith("DADOS:"):
        # Formato: DADOS:25.5;60.0
        dados_str = resposta.replace("DADOS:", "")
        temperatura, umidade = dados_str.split(';')
        return {
            'tipo': 'dados_sensor',
            'temperatura': float(temperatura),
            'umidade': float(umidade)
        }
    
    elif resposta == "ERRO_SENSOR":
        return {'tipo': 'erro_sensor'}
    
    elif resposta == "SISTEMA_INICIADO":
        return {'tipo': 'sistema_iniciado'}
    
    else:
        return {'tipo': 'desconhecido', 'resposta': resposta}

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/controlar/<int:led_num>/<string:action>')
def controlar_led(led_num, action):
    print(f"📥 Recebido: LED {led_num} -> {action}")
    
    if not arduino:
        return jsonify({'status': 'error', 'message': 'Arduino não conectado'})
    
    # Mapeamento de comandos
    comandos = {
        1: {'on': 'A', 'off': 'a'},
        2: {'on': 'B', 'off': 'b'},
        3: {'on': 'C', 'off': 'c'}
    }
    
    if led_num in comandos and action in comandos[led_num]:
        command = comandos[led_num][action]
        
        try:
            # Limpa buffer antes de enviar
            if arduino.in_waiting:
                arduino.read(arduino.in_waiting)
            
            # Envia comando
            arduino.write(command.encode())
            print(f"📤 Enviado comando: {command}")
            
            # Aguarda resposta
            time.sleep(0.5)
            resposta = ler_resposta_arduino()
            
            if resposta:
                resultado = processar_resposta_arduino(resposta)
                print(f"📨 Resposta processada: {resultado}")
            
            return jsonify({
                'status': 'success', 
                'message': f'LED {led_num} {action}',
                'comando': command
            })
            
        except Exception as e:
            print(f"❌ Erro: {e}")
            return jsonify({'status': 'error', 'message': f'Erro: {str(e)}'})
    
    return jsonify({'status': 'error', 'message': 'Comando inválido'})

@app.route('/get_data')
def get_data():
    print("🌡️  Solicitando dados do sensor...")
    
    if not arduino:
        return jsonify({'status': 'error', 'message': 'Arduino não conectado'})
    
    try:
        # Limpa buffer antes de enviar
        if arduino.in_waiting:
            arduino.read(arduino.in_waiting)
        
        # Envia comando para ler sensor
        arduino.write(b'T')
        print("📤 Enviado comando: T")
        
        # Aguarda resposta (DHT11 pode ser lento)
        time.sleep(2)
        resposta = ler_resposta_arduino()
        
        if resposta:
            resultado = processar_resposta_arduino(resposta)
            
            if resultado and resultado['tipo'] == 'dados_sensor':
                return jsonify({
                    'status': 'success',
                    'temperatura': resultado['temperatura'],
                    'umidade': resultado['umidade']
                })
            elif resultado and resultado['tipo'] == 'erro_sensor':
                return jsonify({'status': 'error', 'message': 'Erro na leitura do sensor DHT11'})
        
        return jsonify({'status': 'error', 'message': 'Sem resposta do sensor'})
        
    except Exception as e:
        print(f"❌ Erro: {e}")
        return jsonify({'status': 'error', 'message': f'Erro: {str(e)}'})

@app.route('/status_leds')
def status_leds():
    print("💡 Solicitando status dos LEDs...")
    
    if not arduino:
        return jsonify({'status': 'error', 'message': 'Arduino não conectado'})
    
    try:
        # Limpa buffer antes de enviar
        if arduino.in_waiting:
            arduino.read(arduino.in_waiting)
        
        # Envia comando de status
        arduino.write(b'S')
        print("📤 Enviado comando: S")
        
        # Aguarda resposta
        time.sleep(0.5)
        resposta = ler_resposta_arduino()
        
        if resposta:
            processar_resposta_arduino(resposta)
        
        return jsonify({
            'status': 'success',
            'leds': estado_leds
        })
        
    except Exception as e:
        print(f"❌ Erro: {e}")
        return jsonify({'status': 'error', 'message': f'Erro: {str(e)}'})

@app.route('/reset_leds')
def reset_leds():
    print("🔄 Resetando LEDs...")
    
    if not arduino:
        return jsonify({'status': 'error', 'message': 'Arduino não conectado'})
    
    try:
        # Limpa buffer antes de enviar
        if arduino.in_waiting:
            arduino.read(arduino.in_waiting)
        
        # Envia comando de reset
        arduino.write(b'R')
        print("📤 Enviado comando: R")
        
        # Aguarda resposta
        time.sleep(0.5)
        resposta = ler_resposta_arduino()
        
        if resposta:
            processar_resposta_arduino(resposta)
        
        return jsonify({
            'status': 'success',
            'message': 'LEDs resetados'
        })
        
    except Exception as e:
        print(f"❌ Erro: {e}")
        return jsonify({'status': 'error', 'message': f'Erro: {str(e)}'})

@app.route('/test')
def test():
    return jsonify({
        'status': 'success',
        'message': 'Servidor Flask funcionando!',
        'arduino_conectado': arduino is not None
    })

if __name__ == '__main__':
    print("\n" + "="*60)
    print("🚀 SISTEMA IoT - SEMÁFORO + ESTAÇÃO METEOROLÓGICA")
    print("="*60)
    
    if arduino:
        print("✅ Arduino: CONECTADO")
    else:
        print("❌ Arduino: DESCONECTADO")
    
    print("\n📡 Rotas disponíveis:")
    print("   GET  /                    - Página principal")
    print("   GET  /controlar/<1-3>/<on|off> - Controlar LEDs")
    print("   GET  /get_data            - Ler sensor DHT11")
    print("   GET  /status_leds         - Status dos LEDs")
    print("   GET  /reset_leds          - Resetar LEDs")
    print("   GET  /test                - Testar servidor")
    print("\n📱 Acesse: http://localhost:5000")
    print("="*60)
    
    app.run(debug=True, host='0.0.0.0', port=5000, use_reloader=False)