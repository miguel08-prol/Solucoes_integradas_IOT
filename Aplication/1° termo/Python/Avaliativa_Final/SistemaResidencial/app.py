from flask import Flask, render_template, jsonify
import serial
import serial.tools.list_ports
import time
import threading

app = Flask(__name__)

# Configuração do Arduino
def encontrar_conectar_arduino():
    print("🔍 Procurando Arduino...")
    portas = serial.tools.list_ports.comports()
    portas_disponiveis = []
    
    for porta in portas:
        portas_disponiveis.append(porta.device)
        print(f"   📍 {porta.device} - {porta.description}")
    
    if not portas_disponiveis:
        print("❌ Nenhuma porta COM encontrada!")
        return None
    
    portas_tentativas = ['COM3', 'COM4', 'COM5', 'COM6', 'COM7']
    
    for porta in portas_tentativas:
        if porta in portas_disponiveis:
            try:
                print(f"🔄 Tentando conectar na {porta}...")
                arduino = serial.Serial(porta, 9600, timeout=1)
                time.sleep(2)
                
                arduino.write(b'S')
                time.sleep(0.5)
                
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

# Estado do sistema
estado_sistema = {
    'temperatura': 0,
    'umidade': 0,
    'alerta_temperatura': False,
    'alerta_geladeira': False,
    'ventilador_ligado': False,
    'aquecedor_ligado': False,
    'led_normal': False,
    'led_alerta': False,
    'led_geladeira': False
}

def ler_resposta_arduino():
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
    if not resposta:
        return None
    
    # Dados do sensor
    if resposta.startswith("DADOS:"):
        dados_str = resposta.replace("DADOS:", "")
        partes = dados_str.split(';')
        
        if len(partes) >= 5:
            temperatura = float(partes[0])
            umidade = float(partes[1])
            alerta_temp = "ALERTA_TEMP" in partes[2]
            alerta_gel = "ALERTA_GELADEIRA" in partes[3]
            ventilador = "VENTILADOR_ON" in partes[4]
            aquecedor = "AQUECEDOR_ON" in partes[5] if len(partes) > 5 else False
            
            estado_sistema.update({
                'temperatura': temperatura,
                'umidade': umidade,
                'alerta_temperatura': alerta_temp,
                'alerta_geladeira': alerta_gel,
                'ventilador_ligado': ventilador,
                'aquecedor_ligado': aquecedor
            })
            
            return {'tipo': 'dados_sensor', 'dados': estado_sistema}
    
    # Status dos LEDs
    elif resposta.startswith("STATUS:"):
        status_str = resposta.replace("STATUS:", "")
        estados = status_str.split(',')
        
        estado_sistema.update({
            'led_normal': "NORMAL_ON" in estados[0],
            'led_alerta': "ALERTA_ON" in estados[1],
            'led_geladeira': "GELADEIRA_ON" in estados[2],
            'ventilador_ligado': "VENTILADOR_ON" in estados[3],
            'aquecedor_ligado': "AQUECEDOR_ON" in estados[4]
        })
        return {'tipo': 'status_sistema'}
    
    # Mensagens de alerta
    elif "ALERTA:" in resposta:
        return {'tipo': 'alerta', 'mensagem': resposta}
    
    elif "ALERTA_CRITICO:" in resposta:
        return {'tipo': 'alerta_critico', 'mensagem': resposta}
    
    elif "SUGESTÃO:" in resposta:
        return {'tipo': 'sugestao', 'mensagem': resposta}
    
    # Confirmações de comando
    elif "LIGADO" in resposta or "DESLIGADO" in resposta:
        return {'tipo': 'comando', 'mensagem': resposta}
    
    elif resposta == "SISTEMA_RESETADO":
        estado_sistema.update({
            'alerta_temperatura': False,
            'alerta_geladeira': False,
            'ventilador_ligado': False,
            'aquecedor_ligado': False
        })
        return {'tipo': 'sistema_resetado'}
    
    elif resposta == "ERRO_SENSOR":
        return {'tipo': 'erro_sensor'}
    
    elif resposta == "SISTEMA_RESIDENCIAL_INICIADO":
        return {'tipo': 'sistema_iniciado'}
    
    else:
        return {'tipo': 'desconhecido', 'resposta': resposta}

# Thread para monitorar mensagens do Arduino
def monitorar_arduino():
    while True:
        if arduino:
            resposta = ler_resposta_arduino()
            if resposta:
                processar_resposta_arduino(resposta)
        time.sleep(0.1)

# Iniciar thread de monitoramento
threading.Thread(target=monitorar_arduino, daemon=True).start()

# Rotas Flask
@app.route('/')
def index():
    return render_template('index.html')

@app.route('/get_data')
def get_data():
    print("🌡️  Solicitando dados do sensor...")
    
    if not arduino:
        return jsonify({'status': 'error', 'message': 'Arduino não conectado'})
    
    try:
        if arduino.in_waiting:
            arduino.read(arduino.in_waiting)
        
        arduino.write(b'T')
        print("📤 Enviado comando: T")
        
        time.sleep(2)
        resposta = ler_resposta_arduino()
        
        if resposta:
            resultado = processar_resposta_arduino(resposta)
            
            if resultado and resultado['tipo'] == 'dados_sensor':
                return jsonify({
                    'status': 'success',
                    'temperatura': estado_sistema['temperatura'],
                    'umidade': estado_sistema['umidade'],
                    'alerta_temperatura': estado_sistema['alerta_temperatura'],
                    'alerta_geladeira': estado_sistema['alerta_geladeira'],
                    'ventilador_ligado': estado_sistema['ventilador_ligado'],
                    'aquecedor_ligado': estado_sistema['aquecedor_ligado']
                })
            elif resultado and resultado['tipo'] == 'erro_sensor':
                return jsonify({'status': 'error', 'message': 'Erro na leitura do sensor DHT11'})
        
        return jsonify({'status': 'error', 'message': 'Sem resposta do sensor'})
        
    except Exception as e:
        print(f"❌ Erro: {e}")
        return jsonify({'status': 'error', 'message': f'Erro: {str(e)}'})

@app.route('/controlar/<string:dispositivo>/<string:acao>')
def controlar_dispositivo(dispositivo, acao):
    print(f"📥 Recebido: {dispositivo} -> {acao}")
    
    if not arduino:
        return jsonify({'status': 'error', 'message': 'Arduino não conectado'})
    
    try:
        # Mapeamento de comandos
        comandos = {
            'ventilador': {'on': 'V', 'off': 'v'},
            'aquecedor': {'on': 'A', 'off': 'a'}
        }
        
        if dispositivo in comandos and acao in comandos[dispositivo]:
            command = comandos[dispositivo][acao]
            
            if arduino.in_waiting:
                arduino.read(arduino.in_waiting)
            
            arduino.write(command.encode())
            print(f"📤 Enviado comando: {command}")
            
            time.sleep(0.5)
            resposta = ler_resposta_arduino()
            
            if resposta:
                resultado = processar_resposta_arduino(resposta)
                print(f"📨 Resposta processada: {resultado}")
            
            return jsonify({
                'status': 'success', 
                'message': f'{dispositivo} {acao}',
                'comando': command
            })
        
        return jsonify({'status': 'error', 'message': 'Comando inválido'})
        
    except Exception as e:
        print(f"❌ Erro: {e}")
        return jsonify({'status': 'error', 'message': f'Erro: {str(e)}'})

@app.route('/status_sistema')
def status_sistema():
    print("💡 Solicitando status do sistema...")
    
    if not arduino:
        return jsonify({'status': 'error', 'message': 'Arduino não conectado'})
    
    try:
        if arduino.in_waiting:
            arduino.read(arduino.in_waiting)
        
        arduino.write(b'S')
        print("📤 Enviado comando: S")
        
        time.sleep(0.5)
        resposta = ler_resposta_arduino()
        
        if resposta:
            processar_resposta_arduino(resposta)
        
        return jsonify({
            'status': 'success',
            'sistema': estado_sistema
        })
        
    except Exception as e:
        print(f"❌ Erro: {e}")
        return jsonify({'status': 'error', 'message': f'Erro: {str(e)}'})

@app.route('/reset_sistema')
def reset_sistema():
    print("🔄 Resetando sistema...")
    
    if not arduino:
        return jsonify({'status': 'error', 'message': 'Arduino não conectado'})
    
    try:
        if arduino.in_waiting:
            arduino.read(arduino.in_waiting)
        
        arduino.write(b'R')
        print("📤 Enviado comando: R")
        
        time.sleep(0.5)
        resposta = ler_resposta_arduino()
        
        if resposta:
            processar_resposta_arduino(resposta)
        
        return jsonify({
            'status': 'success',
            'message': 'Sistema resetado'
        })
        
    except Exception as e:
        print(f"❌ Erro: {e}")
        return jsonify({'status': 'error', 'message': f'Erro: {str(e)}'})

@app.route('/test')
def test():
    return jsonify({
        'status': 'success',
        'message': 'Servidor Flask funcionando!',
        'arduino_conectado': arduino is not None,
        'sistema': 'Monitoramento Residencial Inteligente'
    })

if __name__ == '__main__':
    print("\n" + "="*60)
    print("🏠 SISTEMA RESIDENCIAL INTELIGENTE")
    print("="*60)
    
    if arduino:
        print("✅ Arduino: CONECTADO")
    else:
        print("❌ Arduino: DESCONECTADO")
    
    print("\n📡 Rotas disponíveis:")
    print("   GET  /                            - Página principal")
    print("   GET  /get_data                    - Ler sensor DHT11")
    print("   GET  /controlar/<dispositivo>/<acao> - Controlar dispositivos")
    print("   GET  /status_sistema              - Status do sistema")
    print("   GET  /reset_sistema               - Resetar sistema")
    print("   GET  /test                        - Testar servidor")
    print("\n🎯 Dispositivos: ventilador, aquecedor")
    print("🎯 Ações: on, off")
    print("\n📱 Acesse: http://localhost:5000")
    print("="*60)
    
    app.run(debug=True, host='0.0.0.0', port=5000, use_reloader=False)