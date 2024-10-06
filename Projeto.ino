// C++ code
//
// Segundo semestre de 2024
//
// Por:
// Marjorie Luize Martins Costa
// Nuno Martins Guilhermino da Silva
//
// Disciplina:
// Computação Móvel
//
// Github do projeto:
// https://github.com/nunomgs136/ProjetoArduino/
//
// Créditos pelas músicas:
// https://github.com/robsoncouto/arduino-songs
//
// Notas a serem utilizadas
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

// Função para resetar o Arduino
#define RESET asm("jmp (0x0000)")
// "Volta no loop"

#include <LiquidCrystal.h>

// Entradas
int verde = 7;
int vermelho = 6;
int inicio = 2;
int sim = 9;
int nao = 8;
int buzzer = 13;
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 10);
// Onde serão colocadas as palavras a serem exibidas no visor
char buffer[50];
// Variavel para o jogo ativar ou reiniciar: Começa em 0, clica 1 vez, começa o jogo, clica 2 vezes ou mais, reinicia.
int jogo = 0;
int passei = 0;

// Sons do Buzzer

// Acertou
// Pulou questão
// Errou
// Desistiu (Game over)
// Venceu
// Tempo esgotando

// Define se a música é lenta ou rápida (Velocidade)
int tempo = 0;
int tipo = 0;

// Tipo 1, tempo 200
int acertou[] = {
    // Inicio do Mario
    NOTE_E5,
    8,
    NOTE_E5,
    8,
    REST,
    8,
    NOTE_E5,
    8,
    REST,
    8,
    NOTE_C5,
    8,
    NOTE_E5,
    8, //1
    NOTE_G5,
    4,
    REST,
    4,
};

// Tipo 2, tempo 100
int pulou[] = { // Pulo da gaita
    NOTE_C5, 4, NOTE_G4, 8, NOTE_AS4, 4};

// Tipo 3, tempo 225
int errou[] = {
    // DOOM
    NOTE_E2,
    8,
    NOTE_E2,
    8,
    NOTE_E3,
    8,
    NOTE_E2,
    8,
    NOTE_E2,
    8,
    NOTE_D3,
    8,
    NOTE_E2,
    8,
    NOTE_E2,
    8, //1
    NOTE_C3,
    8,
    NOTE_E2,
    8,
    NOTE_E2,
    8,
    NOTE_AS2,
    8,
};

// Tipo 4, tempo 200
int desistiu[] = {
    // Mario game over
    NOTE_C5,
    -4,
    NOTE_G4,
    -4,
    NOTE_E4,
    4, //45
    NOTE_A4,
    -8,
    NOTE_B4,
    -8,
    NOTE_A4,
    -8,
    NOTE_GS4,
    -8,
    NOTE_AS4,
    -8,
    NOTE_GS4,
    -8,
    NOTE_G4,
    8,
    NOTE_D4,
    8,
    NOTE_E4,
    -2,
};

// Tipo 5, tempo 140
int venceu[] = {
    // Take on me
    NOTE_FS5,
    8,
    NOTE_FS5,
    8,
    NOTE_D5,
    8,
    NOTE_B4,
    8,
    REST,
    8,
    NOTE_B4,
    8,
    REST,
    8,
    NOTE_E5,
    8,
    REST,
    8,
    NOTE_E5,
    8,
    REST,
    8,
    NOTE_E5,
    8,
    NOTE_GS5,
    8,
    NOTE_GS5,
    8,
    NOTE_A5,
    8,
    NOTE_B5,
    8,
};

// Tipo 6, tempo 85
int acabou[] = {
    // Game of thrones
    NOTE_G4,
    8,
    NOTE_C4,
    8,
    NOTE_DS4,
    16,
    NOTE_F4,
    16,
    NOTE_G4,
    8,
    NOTE_C4,
    8,
};

// Função para tocar a música
int musica(int tipo)
{
    // Testando com 30
    int melodia[40] = {0}; // Inicializa todos os elementos com 0
    // Copia os elementos correspondente ao tipo de música para melodia
    if (tipo == 1)
    {
        for (int i = 0; i < sizeof(acertou) / sizeof(acertou[0]); i++)
        {
            melodia[i] = acertou[i];
        }
        tempo = 200;
    }
    else if (tipo == 2)
    {
        for (int i = 0; i < sizeof(pulou) / sizeof(pulou[0]); i++)
        {
            melodia[i] = pulou[i];
        }
        tempo = 100;
    }
    else if (tipo == 3)
    {
        for (int i = 0; i < sizeof(errou) / sizeof(errou[0]); i++)
        {
            melodia[i] = errou[i];
        }
        tempo = 225;
    }
    else if (tipo == 4)
    {
        for (int i = 0; i < sizeof(desistiu) / sizeof(desistiu[0]); i++)
        {
            melodia[i] = desistiu[i];
        }
        tempo = 200;
    }
    else if (tipo == 5)
    {
        for (int i = 0; i < sizeof(venceu) / sizeof(venceu[0]); i++)
        {
            melodia[i] = venceu[i];
        }
        tempo = 140;
    }
    else if (tipo == 6)
    {
        for (int i = 0; i < sizeof(acabou) / sizeof(acabou[0]); i++)
        {
            melodia[i] = acabou[i];
        }
        tempo = 85;
    }
    else
    {
        return 1;
    }

    // Calcula o número de notas na melodia, considerando que cada nota ocupa 2 posições no array: uma para a altura e outra para a duração.
    int notes = sizeof(melodia) / sizeof(melodia[0]) / 2;
    // Calcula a duração de uma semínima em milissegundos, com base no tempo (bpm).
    int notas = (60000 * 4) / tempo;
    // Variáveis para controlar a duração de cada nota e a divisão do compasso.
    int divide = 0, duracao = 0;
    // Itera sobre as notas da melodia, pulando de duas em duas posições para pegar altura e duração.
    for (int atual = 0; atual < notes * 2; atual = atual + 2)
    {
        // Calcula a duração da nota atual, considerando notas normais e com colcheia de ponto.
        divide = melodia[atual + 1];
        if (divide > 0)
        {
            // Nota normal: a duração é calculada diretamente.
            duracao = (notas) / divide;
        }
        else if (divide < 0)
        {
            // Nota com colcheia de ponto: a duração é aumentada em 50%.
            duracao = (notas) / abs(divide);
            duracao *= 1.5;
        }
        // Toca a nota por 90% da duração calculada.
        tone(buzzer, melodia[atual], duracao * 0.9);
        // Pausa entre as notas.
        delay(duracao);
        // Para a geração da onda sonora antes da próxima nota.
        noTone(buzzer);
    }
    return 0;
}

// Primeira fase (Luzes e memoria)
int tam = 0;
int seq[10];
int res[10];

// Comparador das sequencias
bool compara(int sequencia[], int resposta[], int tamanho)
{
    // Compara as sequencias
    for (int i = 0; i < tamanho; i++)
    {
        if (sequencia[i] != resposta[i])
        {
            // Se forem diferentes, retorna falso
            return false;
        }
    }
    return true;
}

// Gerador aleatorio para a sequencia (Deve completar o vetor com 0 ou 1 distribuidos alatoriamente)
void gerador(int sequencia[])
{
    Serial.println("______________");
    // Gera a sequencia de 0 e 1 aleatoriamente, atribuindo a sequencia 10 vezes
    for (int i = 0; i < 10; i++)
    {
        // Gera um número aleatório entre 0 e 1
        int num = random(2);
        if (num == 0)
        {
            sequencia[i] = 0;
        }
        else
        {
            sequencia[i] = 1;
        }
        // Imprime a sequencia
        Serial.println(sequencia[i]);
    }
    Serial.println("______________");
}

// Responder a sequencia
int responder(int resposta[])
{
    lcd_1.clear();
    int contador = 0;
    int i = 0;
    lcd_1.setCursor(0, 0);
    lcd_1.print("Repita a serie");
    delay(1000);
    lcd_1.clear();
    // Enquanto o i for menor que 10 (contagem de respostas)
    while (i < 10)
    {
        int btnSim = digitalRead(sim);
        int btnNao = digitalRead(nao);
        lcd_1.setCursor(0, 0);
        sprintf(buffer, "Sequencia: %d", contador);
        lcd_1.print(buffer);

        // Verifica se o botão foi pressionado
        if (btnSim == 0)
        {
            // Atribui a resposta
            resposta[i] = 0;
            digitalWrite(verde, HIGH);
            digitalWrite(vermelho, LOW);
            i++;
            // Compara as sequencias
            bool comp = compara(seq, res, i);
            // Se forem diferentes, reinicia
            if (comp == false)
            {
                contador = 0;
                lcd_1.clear();
                lcd_1.setCursor(0, 1);
                sprintf(buffer, "Errado!");
                lcd_1.print(buffer);
                lcd_1.setCursor(3, 1);
                sprintf(buffer, "Reiniciando.");
                i = 0;
                digitalWrite(verde, LOW);
                musica(3);
                lcd_1.clear();
                RESET;
                return 1;
            }
            else
            {
                // Se forem iguais, continua
                lcd_1.setCursor(0, 1);
                sprintf(buffer, "Correto!");
                lcd_1.print(buffer);
                contador++;
                delay(400);
                digitalWrite(verde, LOW);
                delay(400);
                lcd_1.clear();
            }
        }
        if (btnNao == 0)
        {
            resposta[i] = 1;
            digitalWrite(vermelho, HIGH);
            digitalWrite(verde, LOW);
            i++;
            bool comp = compara(seq, res, i);
            if (comp == false)
            {
                // Resetando
                contador = 0;
                lcd_1.clear();
                lcd_1.setCursor(3, 0);
                sprintf(buffer, "Errado!");
                lcd_1.print(buffer);
                lcd_1.setCursor(3, 1);
                sprintf(buffer, "Reiniciando.");
                lcd_1.print(buffer);
                i = 0;
                digitalWrite(vermelho, LOW);
                musica(3);
                lcd_1.clear();
                RESET;
                return 1;
            }
            else
            {
                lcd_1.setCursor(0, 1);
                sprintf(buffer, "Correto!");
                lcd_1.print(buffer);
                contador++;
                delay(400);
                digitalWrite(vermelho, LOW);
                delay(400);
                lcd_1.clear();
            }
        }
    }
    // Passou
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    sprintf(buffer, "Proxima fase!");
    lcd_1.print(buffer);
    musica(1);
    return 0;
}

// Acender as luzes de acordo com a sequencia
int acender(int sequencia[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        // Se a sequencia for 1, acende o vermelho
        if (sequencia[i] == 1)
        {
            delay(500);
            digitalWrite(vermelho, HIGH);
            digitalWrite(verde, LOW);
            delay(1000);
            digitalWrite(vermelho, LOW);
        }
        // Se a sequencia for 0, acende o verde
        else
        {
            delay(500);
            digitalWrite(verde, HIGH);
            digitalWrite(vermelho, LOW);
            delay(1000);
            digitalWrite(verde, LOW);
        }
    }
    delay(1000);
}

// Fase 1
int fase1()
{
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Observe a ordem");
    lcd_1.setCursor(3, 1);
    lcd_1.print("das luzes!");
    delay(500);
    gerador(seq);
    acender(seq, 10);
    delay(1000);
    responder(res);
    return 0;
}

// Vida do jogador
int chance = 1;

// Vão ser 5 perguntas aleatorias de SIM ou NÃO, além da pergunta final (padrão: "Você é um robô?").

// Banco de perguntas
const char *banco[15] = {
    "O Sol e uma estrela?",
    "A Lua e um satelite da Terra?",
    "A Terra e plana?",
    "Tomate e um vegetal?",
    "O Japao e um arquipelago?",
    "Os morcegos sao cegos?",
    "As abelhas se comunicam dancando?",
    "Os golfinhos sao mamiferos?",
    "O Youtube ja quebrou?",
    "O Brasil e o maior pais do mundo?",
    "O sistema solar possui 8 planetas?",
    "Gatos tem 7 vidas?",
    "Cachalote e o maior animal do mundo?",
    "O tigre e o maior felino do mundo?",
    "Amazonia e a maior floresta do mundo?"};

// Respostas
const char *respostas[15] = {
    "s",
    "s",
    "n",
    "n",
    "s",
    "n",
    "s",
    "s",
    "s",
    "n",
    "s",
    "n",
    "n",
    "s",
    "s"};

// Perguntas sorteadas
int sorteados[5] = {};

// Resposta do usuário
char *resp;

// Marcador para as perguntas já selecionadas
bool marcadas[15] = {
    false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

// Embaralhar as perguntas
void embaralhar()
{
    // Sorteia 6 perguntas
    for (int j = 0; j < 6; j++)
    {
        // Sorteia um índice
        int indice = random(15);
        // Se a pergunta não foi marcada
        if (!marcadas[indice])
        {
            // Atribui o índice sorteado ao vetor de perguntas sorteadas
            sorteados[j] = indice;
            // Marca a pergunta
            marcadas[indice] = true;
        }
        else
        {
            // Se a pergunta já foi marcada, sorteia novamente
            j--;
        }
    }
}

// Exibir a pergunta
void exibir(const char *pergunta)
{
    lcd_1.setCursor(2, 0);
    lcd_1.print(pergunta);
    // Se a pergunta for maior que 16 caracteres, desloca a pergunta

    for (int i = 0; i < strlen(pergunta); i++)
    {
        // Desloca para a esquerda
        lcd_1.scrollDisplayLeft();
        delay(300); // Quanto menor o tempo, mais rápido será o deslocamento
    }
}

// Verifica se a resposta do usuário é igual a resposta correta
bool verificar(const char *respUsuario, const char *respCorreta)
{
    // Compara as respostas
    // strcmp retorna 0 se as strings forem iguais
    return strcmp(respUsuario, respCorreta) == 0;
}

// Chamada da função de verificação
void chamada(const char *resp, const char *resposta)
{
    lcd_1.clear();
    // Verifica se a resposta do usuário é igual a resposta correta
    if (verificar(resp, resposta))
    {
        lcd_1.setCursor(4, 0);
        lcd_1.print("Correto!");
        musica(1);
    }
    // Se a resposta estiver errada
    else
    {
        lcd_1.setCursor(4, 0);
        lcd_1.print("Errado!");
        delay(400);
        lcd_1.clear();
        lcd_1.setCursor(4, 0);
        lcd_1.print("GAME OVER!");
        musica(4);
        RESET;
    }
}

// Verifica se o botão foi pressionado
bool verificarResposta()
{
    return digitalRead(sim) == LOW || digitalRead(nao) == LOW;
}

// Perguntas da fase 2
void perguntas()
{
    // Número max de perguntas
    int a = 5;
    // Pergunta atual
    int per = 0;
    for (int i = 0; i < a; i++)
    {
        // Indice da pergunta e resposta
        int s = sorteados[i];
        const char *quest = banco[s];
        const char *resposta = respostas[s];
        lcd_1.clear();
        lcd_1.setCursor(2, 0);
        // Exibe o número da pergunta
        per++;
        sprintf(buffer, "Pergunta: %d ", per);
        lcd_1.print(buffer);
        lcd_1.setCursor(5, 1);
        lcd_1.print(" de 5 ");
        delay(2000);
        lcd_1.clear();
        // Exibe a pergunta
        exibir(quest);
        delay(500);
        lcd_1.clear();
        lcd_1.setCursor(3, 1);
        lcd_1.print("SIM ou NAO");
        delay(300);
        // Verificador
        bool respostaRecebida = false;
        int seg = millis();
        int total = 10000;
        // Enquanto a resposta não for recebida
        while (!respostaRecebida)
        {
            int resto = total - (millis() - seg);
            sprintf(buffer, "Tempo: %d ", resto / 1000);
            lcd_1.setCursor(4, 0);
            lcd_1.print(buffer);
            int btnSim = digitalRead(sim);
            int btnNao = digitalRead(nao);
            if (verificarResposta())
            {
                respostaRecebida = true;
                if (btnSim == 0)
                {
                    *resp = 's';
                    lcd_1.setCursor(2, 1);
                    lcd_1.print("*SIM ou NAO");
                    delay(300);
                }
                if (btnNao == 0)
                {
                    *resp = 'n';
                    lcd_1.setCursor(2, 1);
                    lcd_1.print("SIM ou *NAO");
                    delay(300);
                }
                chamada(resp, resposta);
                break;
            }
            // Tempo esgotou
            if (resto <= 0)
            {
                lcd_1.clear();
                lcd_1.setCursor(0, 0);
                lcd_1.print("Tempo esgotado!");
                // Se o tempo acabar, o jogador perde uma vida
                if (chance == 1)
                {
                    chance = 0;
                    lcd_1.setCursor(4, 1);
                    lcd_1.print("Vidas: 1");
                    delay(700);
                    lcd_1.setCursor(4, 1);
                    lcd_1.print("Vidas: 0");
                    musica(2);
                    lcd_1.clear();
                    per--;
                    a++;
                    break;
                }
                // Se ele já gastou a unica vida, perde o jogo
                else
                {
                    lcd_1.clear();
                    lcd_1.setCursor(3, 0);
                    lcd_1.print("GAME OVER!");
                    musica(4);
                    RESET;
                }
            }
        }
    }
}

// Fase 2
void fase2()
{
    lcd_1.clear();
    lcd_1.setCursor(3, 0);
    lcd_1.print("Responda as");
    lcd_1.setCursor(4, 1);
    lcd_1.print("perguntas!");
    delay(1000);
    embaralhar();
    perguntas();
}

void fase3()
{
    // LCD não suporta caracteres especiais
    lcd_1.clear();
    lcd_1.setCursor(1, 0);
    lcd_1.print("PERGUNTA FINAL!");
    delay(2000);
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("VOCE E UM ROBO?");
    lcd_1.setCursor(3, 1);
    lcd_1.print("SIM ou NAO");
    delay(2000);
    lcd_1.clear();
    lcd_1.setCursor(3, 1);
    lcd_1.print("SIM ou NAO");
    delay(300);
    // Verificador
    bool respostaRecebida = false;
    int seg = millis();
    int total = 10000;
    while (!respostaRecebida)
    {
        int resto = total - (millis() - seg);

        sprintf(buffer, "Tempo: %d ", resto / 1000);
        lcd_1.setCursor(3, 0);
        lcd_1.print(buffer);
        int btnSim = digitalRead(sim);
        int btnNao = digitalRead(nao);
        if (verificarResposta())
        {
            respostaRecebida = true;
            if (btnSim == 0)
            {
                *resp = 's';
                lcd_1.setCursor(2, 1);
                lcd_1.print("*SIM ou NAO");
                delay(300);
            }
            if (btnNao == 0)
            {
                *resp = 'n';
                lcd_1.setCursor(2, 1);
                lcd_1.print("SIM ou *NAO");
                delay(300);
            }
            const char *resposta = "n";
            chamada(resp, resposta);
            break;
        }
        // Tempo esgotou
        if (resto <= 0)
        {
            // Resetando
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("Tempo esgotado!");
            delay(700);

            lcd_1.clear();
            lcd_1.setCursor(4, 0);
            lcd_1.print("GAME OVER!");
            musica(4);
            RESET;
        }
    }
}

// Inicia ou reinicia o jogo
void reinicia()
{
    lcd_1.clear();
    if (jogo == 0)
    {
        // Inicia o jogo
        jogo = 1;
    }
    else
    {
        // Reinicia o jogo
        digitalWrite(vermelho, LOW);
        digitalWrite(verde, LOW);
        lcd_1.setCursor(0, 0);
        lcd_1.print("Reiniciando...");
        musica(6);
        delay(30000);
        RESET;
    }
}

// Aplicando uma vez
void setup()
{
    lcd_1.begin(16, 2); // Configure o número de colunas e linhas no LCD.
    // Leds
    pinMode(vermelho, OUTPUT);
    pinMode(verde, OUTPUT);
    // Botões
    pinMode(inicio, INPUT_PULLUP);
    pinMode(sim, INPUT_PULLUP);
    pinMode(nao, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
    noTone(buzzer);
    // Botão de reiniciar
    attachInterrupt(digitalPinToInterrupt(inicio), reinicia, RISING);
    // Inicializar o randomizador
    randomSeed(analogRead(0));
}
// Looping
void loop()
{
    // Botão de início
    int btnInicio = digitalRead(inicio);
    // Testando as fases
    //passei = 1;
    if (jogo == 0)
    {
        lcd_1.setCursor(3, 0);
        lcd_1.print("Bem-vindo.");
        lcd_1.setCursor(2, 1);
        lcd_1.print("Pressione GO!");
        // Se o botão for pressionado, inicia o jogo
    }
    if (jogo == 1)
    {
        lcd_1.clear();
        if (passei == 0)
        {
            fase1();
            passei = 1;
        }
        else if (passei == 1)
        {
            fase2();
            passei = 2;
        }
        else if (passei == 2)
        {
            fase3();
            passei = 3;
        }
        else if (passei = 3)
        {
            lcd_1.clear();
            lcd_1.setCursor(4, 0);
            lcd_1.print("PARABENS!");
            lcd_1.setCursor(2, 1);
            lcd_1.print("VOCE VENCEU!");
            musica(5);
            RESET;
        }
    }
}
