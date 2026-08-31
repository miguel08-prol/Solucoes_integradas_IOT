from flask import Flask, render_template

# Inicializa o aplicativo Flask
app = Flask(__name__)

# Rota principal que exibe a página de controle (index.html)
@app.route('/')
def index():
    """
    Esta função é chamada quando alguém acessa a página inicial.
    Ela informa no terminal que a página foi carregada e envia o arquivo
    'index.html' para o navegador.
    """
    print(">>> Página principal 'index.html' carregada pelo navegador.")
    return render_template('index.html')

# Rota que simula o recebimento dos comandos para os LEDs
@app.route('/control/<led_num>/<action>')
def control(led_num, action):
    """
    Esta é a função de teste principal. Ela é chamada pelo JavaScript
    da página HTML sempre que um botão é clicado.
    
    Em vez de enviar um comando para o Arduino, ela imprime uma mensagem
    clara no terminal, confirmando exatamente o que foi recebido.
    """
    
    print("=" * 40)
    print("COMANDO RECEBIDO DO NAVEGADOR!")
    print(f"   - Alvo: LED número {led_num}")
    print(f"   - Ação: '{action}'")
    print("=" * 40)
    
    # Retorna uma mensagem de confirmação para o navegador.
    # Você pode ver essa mensagem no console de desenvolvedor do navegador (F12).
    return f"Servidor de teste recebeu o comando: LED {led_num}, Ação '{action}'"

# Bloco principal para rodar o servidor
if __name__ == '__main__':
    """
    Inicia o servidor de desenvolvimento do Flask.
    - debug=True: O servidor reinicia automaticamente se você alterar o código.
    - host='0.0.0.0': Permite que o servidor seja acessado de outros dispositivos na mesma rede.
    - port=5000: Define a porta em que o servidor irá rodar.
    """
    print("Servidor de teste iniciado!")
    print("Abra seu navegador e acesse: http://localhost:5000")
    app.run(debug=True, host='0.0.0.0', port=5000)