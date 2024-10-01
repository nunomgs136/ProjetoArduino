// C++ code
//
// Créditos pelas músicas: https://github.com/robsoncouto/arduino-songs
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

int musica(int tipo)
{
    int melodia[40] = {0}; // Inicializa todos os elementos com 0

    if (tipo == 1)
    {
        // Copia os elementos para melodia, até o tamanho de desistiu
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
    for (int i = 0; i < tamanho; i++)
    {
        if (sequencia[i] != resposta[i])
        {
            return false;
        }
    }
    return true;
}

// Gerador aleatorio para a sequencia (Deve completar o vetor com 0 ou 1 distribuidos alatoriamente)
int gerador(int sequencia[])
{
    for (int i = 0; i < 10; i++)
    {
        int num = random(2);
        if (num == 0)
        {
            sequencia[i] = 0;
        }
        else
        {
            sequencia[i] = 1;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        Serial.println(sequencia[i]);
    }
    return 0;
}

int responder(int resposta[])
{
    lcd_1.clear();
    int contador = 0;
    int i = 0;

    while (i <= 10)
    {
        int btnSim = digitalRead(sim);
        int btnNao = digitalRead(nao);
        lcd_1.setCursor(0, 0);
        sprintf(buffer, "Sequencia: %d", contador);
        lcd_1.print(buffer);

        if (btnSim == 0)
        {
            resposta[i] = 0;
            digitalWrite(verde, HIGH);
            digitalWrite(vermelho, LOW);
            i++;
            bool comp = compara(seq, res, i);
            if (comp == false)
            {
                contador = 0;
                lcd_1.clear();
                lcd_1.setCursor(0, 1);
                musica(3);
                sprintf(buffer, "Errado!");
                lcd_1.print(buffer);
                lcd_1.setCursor(3, 1);
                sprintf(buffer, "Reiniciando.");
                i = 0;
                digitalWrite(verde, LOW);
                delay(1000);
                lcd_1.clear();
                intro1();
                return 1;
            }
            else
            {
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
                contador = 0;
                lcd_1.clear();
                lcd_1.setCursor(3, 0);
                musica(3);
                sprintf(buffer, "Errado!");
                lcd_1.print(buffer);
                lcd_1.setCursor(3, 1);
                sprintf(buffer, "Reiniciando.");
                lcd_1.print(buffer);
                i = 0;
                digitalWrite(vermelho, LOW);
                delay(1000);
                lcd_1.clear();
                intro1();
                return 1;
            }
            else
            {
                //lcd_1.clear();
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

        if (i == 10)
        {
            break;
        }
    }
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    musica(1);
    sprintf(buffer, "Proxima fase!");
    lcd_1.print(buffer);
    delay(1000);

    // // Passar para a próxima fase
    // lcd_1.clear();
    // fase2();
    // delay(1000);

    return 0;
}

int acender(int sequencia[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (sequencia[i] == 1)
        {
            delay(500);
            digitalWrite(vermelho, HIGH);
            digitalWrite(verde, LOW);
            delay(1000);
            digitalWrite(vermelho, LOW);
        }
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

int intro1()
{
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Observe a ordem");
    lcd_1.setCursor(0, 1);
    lcd_1.print("   das luzes!");
    // lcd_1.print(buffer);
    // lcd_1.print(buffer);
    // Aqui vamos movimentar todo o display X posições para a ESQUERDA.
    // for (int posi_LCD = 0; posi_LCD < 36; posi_LCD++)
    // {
    //     lcd_1.setCursor(16, 1);
    //     lcd_1.scrollDisplayLeft(); //Essa é a função que faz as letras se deslocarem
    // 	lcd_1.autoscroll();
    //     delay(250); // Quanto menor o tempo, mais rápido será o deslocamento
    // }
    return 0;
}

int fase1()
{
    // Faz o texto andar para a esquerda
    //while (lcd_1.cursor() > 0) {
    //}

    // lcd_1.clear();
    // lcd_1.setCursor(0, 0);
    // sprintf(buffer, "Observe a ordem das luzes");

    // //lcd_1.scrollDisplayLeft();
    // //lcd_1.autoscroll();
    // //delay(200); // Ajuste o delay para controlar a velocidade

    // lcd_1.print(buffer);

    // //lcd_1.setCursor(1,6);
    // //sprintf(buffer, "das luzes.");
    // lcd_1.print(buffer);
    intro1();
    delay(500);
    gerador(seq);
    acender(seq, 10);
    lcd_1.setCursor(0, 0);
    delay(1000);
    responder(res);
    // delay(1000);
    // // Passar para a próxima fase
    // lcd_1.clear();

    return 0;
}

// A partir daqui, a função contador() será chamada para contar o tempo do jogo
// Variavel para a contagem de tempo do jogo (Maior que 15 reinicia, em 10 toca a música de tempo esgotando)
int seg = 0;
int chance = 1;

// Vão ser 5 perguntas aleatorias de SIM ou NÃO, 2 faceis, 2 médias e 1 dificil, além da pergunta final (padrão: "Você é um robô?").

// // Perguntas faceis: 6
// const char *facil[]{
//     "O Sol é uma estrela?",
//     "A Lua é um satélite da Terra?",
//     "A Terra é redonda?",
//     "Tomate é um vegetal?",
//     "O Japão é um arquipélago?",
//     "Os morcegos são cegos?"};

// const char *res1[] = {
//     "s", "s", "s", "n", "s", "n"};

// // Perguntas médias: 6
// const char *medio[] = {
//     "As abelhas se comunicam dançando?",
//     "Os golfinhos são mamíferos?",
//     "O Youtube já quebrou?",
//     "A Guerra Fria ocorreu após a Segunda Guerra Mundial?",
//     "A gravidade foi descoberta por Albert Einstein?",
//     "A teoria do Big Bang foi proposta por Stephen Hawking?"};

// const char *res2[] = {
//     "s", "s", "s", "s", "n", "n"};

// // Perguntas dificeis: 6
// const char *dificil[] = {
//     "A teoria da relatividade foi proposta por Isaac Newton?",
//     "A primeira mulher a ganhar um prêmio Nobel foi Marie Curie?",
//     "A teoria da evolução foi proposta por Charles Darwin?",
//     "A primeira viagem ao espaço foi realizada por um astronauta americano?",
//     "A Teoria da Relatividade foi proposta no século XIX?",
//     "O deserto do Saara é o maior deserto do mundo?"};

// const char *res3[] = {
//     "n", "s", "n", "n", "n", "n"};

// Perguntas faceis: 6
const char *facil[]{
    "O Sol e uma estrela?",
    "A Lua e um satelite da Terra?",
    "A Terra e redonda?",
    "Tomate e um vegetal?",
    "O Japao e um arquipelago?",
    "Os morcegos sao cegos?"};

const char *res1[] = {
    "s", "s", "s", "n", "s", "n"};

// Perguntas medias: 6
const char *medio[] = {
    "As abelhas se comunicam dancando?",
    "Os golfinhos sao mamiferos?",
    "O Youtube ja quebrou?",
    "A Guerra Fria ocorreu apos a Segunda Guerra Mundial?",
    "A gravidade foi descoberta por Albert Einstein?",
    "A teoria do Big Bang foi proposta por Stephen Hawking?"};

const char *res2[] = {
    "s", "s", "s", "s", "n", "n"};

// Perguntas dificeis: 6
const char *dificil[]{
    "A teoria da relatividade foi proposta por Isaac Newton?",
    "A primeira mulher a ganhar um premio Nobel foi Marie Curie?",
    "A teoria da evolucao foi proposta por Charles Darwin?",
    "A primeira viagem ao espaco foi realizada por um astronauta americano?",
    "A Teoria da Relatividade foi proposta no seculo XIX?",
    "O deserto do Sahara e o maior deserto do mundo?"};

const char *res3[] = {
    "n", "s", "n", "n", "n", "n"};

char *resp = " ";

int intro2()
{
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("   Responda as");
    lcd_1.setCursor(0, 1);
    lcd_1.print("    perguntas!");
    // Aqui vamos movimentar todo o display X posições para a ESQUERDA.
    // for (int posi_LCD = 0; posi_LCD < 36; posi_LCD++)
    // {
    //     lcd_1.setCursor(16, 1);
    //     lcd_1.scrollDisplayLeft(); //Essa é a função que faz as letras se deslocarem
    // 	lcd_1.autoscroll();
    //     delay(250); // Quanto menor o tempo, mais rápido será o deslocamento
    // }
    return 0;
}

int embaralhar(const char *vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        int r = random(tamanho);
        const char *temp = vetor[i];
        vetor[i] = vetor[r];
        vetor[r] = temp;
    }
    return 0;
}

// Verificar se não respondeu a tempo
// Função contadora de tempo
int contador(int seg)
{
    for (int i = 0; i < seg; i++)
    {
        delay(1000);
        seg++;
        if (seg == 10)
        {
            musica(6);
        }
        if (seg == 15)
        {
            // Pula
            if (chance == 1)
            {
                // O limite de chances é 1
                chance = 0;
                musica(2);
            }
            // Perde
            else
            {
                musica(4);
                RESET;
            }
        }
    }
    return 0;
}

// Deve passar as perguntas, se a pessoa acertou ou não, e o tempo. Ela só pode errar/pular uma vez, se não perde.
int perguntas(const char *perg[], const char *res[], int tam)
{
    embaralhar(perg, tam);
    for (int i = 0; i < tam; i++)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print(perg[i]);
        // A pergunta deve passar pro lado direito ao esquerdo <---- (scroll), depois sumir e aparecer o tempo.
        // Aqui vamos movimentar todo o display X posições para a ESQUERDA.
        for (int posi_LCD = 0; posi_LCD < 36; posi_LCD++)
        {
            lcd_1.setCursor(16, 1);
            lcd_1.scrollDisplayLeft(); //Essa é a função que faz as letras se deslocarem
            lcd_1.autoscroll();
            delay(250); // Quanto menor o tempo, mais rápido será o deslocamento
        }
        lcd_1.clear();
        lcd_1.setCursor(0, 1);
        lcd_1.print("S ou N?");
        delay(1000);

        // // Resposta
        int btnSim = digitalRead(sim);
        int btnNao = digitalRead(nao);
        // if (btnSim == 0)
        // {
        //     resp = "s";
        // }
        // if (btnNao == 0)
        // {
        //     resp = "n";
        // }
        // if (resp == res[i])
        // {
        //     lcd_1.clear();
        //     lcd_1.setCursor(0, 0);
        //     lcd_1.print("Correto!");
        //     delay(1000);
        // }
        // else
        // {
        //     lcd_1.clear();
        //     lcd_1.setCursor(0, 0);
        //     lcd_1.print("Errado!");
        //     delay(1000);
        // }
    }
}

int fase2()
{
    intro2();
    delay(500);
    int round = 0;
    if round == 0
    {
        perguntas(facil, res1, 2);
    //     round++;
    // } else if round == 1
    // {
        perguntas(medio, res2, 2);
    //     round++;
    // } else if round == 2
    // {
        perguntas(dificil, res3, 1);
        round++;
    } else if (round == 1)
    {
        // Pergunta final
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Voce e um robo?");
        lcd_1.setCursor(0, 1);
        lcd_1.print("S ou N?");
        delay(1000);
        int btnSim = digitalRead(sim);
        int btnNao = digitalRead(nao);
        if (btnSim == 0)
        {
            resp = "s";
        }
        if (btnNao == 0)
        {
            resp = "n";
        }
        if (resp == "n")
        {
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("Correto!");
            delay(1000);
        }
        else
        {
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("Errado!");
            delay(1000);
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("    GAME OVER!");
            musica(4);
            delay(400);
            RESET;
        }
    }
    // perguntas(facil, res1, 2);
    // perguntas(medio, res2, 2);
    // perguntas(dificil, res3, 1);

    return 0;
}

// Inicia ou reinicia o jogo
void reinicia()
{
    lcd_1.clear();
    if (jogo == 0)
    {
        jogo = 1;
    }
    else
    {
        digitalWrite(vermelho, LOW);
        digitalWrite(verde, LOW);
        lcd_1.setCursor(0, 0);
        lcd_1.print("Reiniciando...");
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
    // int btnSim = digitalRead(sim);
    // int btnNao = digitalRead(nao);
    // Botão de início
    int btnInicio = digitalRead(inicio);
    //Serial.println(btnInicio);

    // lcd_1.clear();
    //jogo = 1;
    //passei = 1;
    if (jogo == 0)
    {
        lcd_1.setCursor(0, 0);
        lcd_1.print("   Bem-vindo.");
        lcd_1.setCursor(0, 1);
        lcd_1.print("  Pressione GO!");
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
        else if (passei = 2)
        {
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("    PARABENS!");
            lcd_1.setCursor(0, 1);
            lcd_1.print("  VOCE VENCEU!");
            musica(5);
            delay(400);
            RESET;
        }
    }
}
