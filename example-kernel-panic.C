void kernel_panic(char* motivo_do_erro) { // Abre a função

    unsigned short* tela = (unsigned short*)0xB8000;

    for (int i = 0; i < 2000; i++) {
        
        tela[i] = (0x4F << 8) | ' '; 
    }

} // Fecha a função
