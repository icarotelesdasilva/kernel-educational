
unsigned char mapa_teclado[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0, // mapeia as teclas do teclado qwerty
 '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,  '*',   0,
  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0, '-',   0,   0,   0, '+',   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0
};

// shell basico abaixo:
void esperar_comando(char* buffer_destino) {
    int posicao = 0;
    unsigned char ultima_tecla = 0;

    while(1) {
        // Pega o sinal elétrico bruto do fio do teclado
        unsigned char codigo = ler_porta_teclado();

        // Se uma tecla foi pressionada (e não solta)
        if (codigo != ultima_tecla && !(codigo & 0x80)) {
            char letra = mapa_teclado[codigo];
            
            if (letra != 0) {
                // SE APERTAR ENTER: Finaliza a string e devolve pro Boot do _start
                if (letra == '\n') {
                    buffer_destino[posicao] = '\0'; // Fecha o comando
                    print_colorido("\n", 0x0F);     // Pula a linha na tela
                    return;                         // Libera o terminal!
                } 
                // SE FOR BACKSPACE: Apaga a última letra (se houver)
                else if (letra == '\b') {
                    if (posicao > 0) {
                        posicao--;
                        // Aqui daria para recuar o cursor na tela (ajuste VGA)
                    }
                }
                // SE FOR LETRA/NÚMERO NORMAL: Guarda na gaveta e joga no monitor
                else if (posicao < 99) {
                    buffer_comando_bruto[posicao] = letra; // Guarda no buffer
                    posicao++;
                    
                    // Cria a string temporária para printar na tela em Branco
                    char texto[2] = {letra, '\0'};
                    print_colorido(texto, 0x0F);
                }
            }
            ultima_tecla = codigo; // Evita repetição infinita se segurar a tecla
        } 
        // Se o usuário soltou a tecla, reseta o estado
        else if (codigo & 0x80) {
            ultima_tecla = 0;
        }
    }
}
