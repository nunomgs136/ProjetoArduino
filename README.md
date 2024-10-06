# ProjetoArduino

## Introdução: 
O projeto foi feito para desenvolver um jogo de três fases utilizando um circuito que esteja dentro dos limites de um Arduino UNO e um Liquid Crystal Display(LCD), com programação feita com a linguagem C++. A primeira fase do jogo é um jogo da memória, no qual é mostrada para o usuário uma sequência de 10 luzes que são feitas aleatoriamente, então desse jeito, a cada vez que o usuário começar o jogo, será feita uma sequência de luzes, contando também para quando for usado o botão de reiniciar ou quando o jogador perder o jogo. Se o jogador acertar a sequência, será tocado um som através de um buzzer e o jogador progredirá para a segunda fase. Caso contrário, será reiniciado o jogo. 
A segunda fase é um jogo de perguntas e respostas. Todas as questões feitas tem respostas de sim ou não. Nesta fase, o jogador deve ter uma sequência de 5 respostas corretas para poder passar para a próxima fase. As perguntas são escolhidas aleatoriamente de um banco de 15 questões. Além disso, o jogador tem a oportunidade de pular uma questão sem perder o jogo, assim continuando da mesma marca na qual estava. Se o jogador responder incorretamente alguma questão, ele perderá o jogo, tendo que reiniciar desde a primeira fase. Se o jogador responder corretamente, será tocado um som após cada resposta correta, além de outro som no caso do jogador conseguir progredir de fase. 
 	Ademais se tem a terceira fase. Nesta fase, o jogador terá que responder uma pergunta fixa, ou seja, é a mesma para todas as vezes que o jogo for jogado. A pergunta também será de sim ou não, se o jogador acertar, ele ganhará o jogo, senão, terá que reiniciar da primeira fase.


## Metodologia:
Neste projeto, foram utilizados os seguintes materiais:
■Arduino UNO
■1 LED vermelho
■1 LED verde
■3 botões 
■ 2 resistores de 300 ohm
 ■1 resistor de 200 ohm
 ■1 Buzzer
■Display LCD 16x2

## Métodos: 
O código foi feito com uma separação de partes essenciais de cada fase em funções, sendo juntadas em uma função que representa cada fase, assim deixando a função de loop mais organizada. Seguem as funções necessárias para cada fase e as funções que representam a junção de tudo:

*Fase 1(Jogo da memória):*
 
**gerador(int sequencia[])** - Esta função gera a sequência que será usada na primeira fase, servindo não só para o explicitar a ordem quando os LEDs acendem na ordem, mas também para guardar como um vetor para comparar com as respostas do jogador. Dentro do vetor, são registrados como 0 as vezes que será acesa a luz verde e 1 os momentos que será acesa a luz vermelha. 

```C++
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

```
**acender(int sequencia[], int tamanho)** - Esta função é usada antes do jogador começar a replicar a ordem, servindo para explicitar a ordem de luzes. Ela lê o vetor aleatório que foi gerado e acende ou apaga os dois LEDs presentes no circuito adequadamente. 

```C++
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


```
**compara(int sequencia[], int resposta[], int tamanho)** - Esta função é usada para comparar a resposta que o jogador colocou em seu vetor (resposta) e as respostas que estão dentro do vetor de respostas que foi gerado na função gerador(sequência).  O parâmetro tamanho é usado para representar o tamanho do vetor resposta, para que não seja comparado indíces a mais do que é necessário no momento, já que esta função é usada depois de cada resposta do usuário, e não quando o vetor resposta for completamente preenchido.

```C++
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

```
**responder(int resposta[])** -  Esta função serve para registrar as respostas do usuário na primeira fase, através da leitura do botão do LED verde (btnSim) e do LED vermelho(btnNao). Após ser lido o pressionamento de um dos dois botões, a resposta é registrada dentro do vetor resposta com o LED correspondente sendo ligado e é chamada a função compara para analisar se a resposta do jogador está correta. Se estiver, é continuada a fase, sendo mostrado ambos o número de respostas corretas do jogador e uma mensagem de afirmação no LCD. Caso contrário, é encerrado o ciclo de resposta, o jogador sendo avisado de seu erro através do LCD e o Arduino é reiniciado. 

```C++
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


```
**fase1()** - Esta função começa imprimindo na LCD uma frase de aviso, informando o jogador que sua atenção deve se direcionar ao LEDs e a ordem no qual eles acendem. Após isso, é chamada a função gerador() e acender() para mostrar ao jogador a ordem de luzes na qual deve repetir e a função responder() para que ele possa imitar a sequência que lhe foi mostrada.
```C++

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

```
*Fase 2 (Perguntas e Respostas):* 

**embaralhar()** - Esta função serve para escolher as perguntas que serão utilizadas durante a segunda fase. É escolhido um índice aleatório da lista de perguntas que será adicionado a um vetor com as perguntas que foram selecionadas. 

```C++
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

```
__exibir(const char *pergunta)__ - Esta função serve para a impressão das perguntas no LCD. É feita uma condição caso a pergunta seja muito grande para que seja usada a função scrollDisplayLeft() e um delay para controlar a velocidade no qual a pergunta atravessa o LCD. 

```C++

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
```
__verificar(const char *respUsuario, const char *respCorreta)__ - Compara a resposta do jogador com a resposta correta, retornando se está certa ou não. 

```C++
// Verifica se a resposta do usuário é igual a resposta correta
bool verificar(const char *respUsuario, const char *respCorreta)
{
    // Compara as respostas
    // strcmp retorna 0 se as strings forem iguais
    return strcmp(respUsuario, respCorreta) == 0;
}

```

**verificarResposta()** - Verifica se algum botao feito para responder foi pressionado pelo usuário.
```C++
// Verifica se o botão foi pressionado
bool verificarResposta()
{
    return digitalRead(sim) == LOW || digitalRead(nao) == LOW;
}
```
**chamada()** - Define as próximas ações de acordo com a resposta do verificar(), continuando o jogo se a resposta estiver correta, ou reiniciando o Arduino caso esteja incorreta, além de imprimir uma mensagem no LCD dependendo do caso. 
```C++
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

```
**perguntas(**) - Informa o jogador sobre em qual questão ele está além do tempo para cada pergunta. Durante o seu ciclo de respostas, é mostrada a pergunta no LCD através do exibir(). Após isso, é feita uma leitura dos botões(btnSim e btnNao). Se for detectado o pressionamento de um dos botões, a sua resposta equivalente é marcada no LCD através de um * ao lado da resposta. Após isto, é feita a comparação da resposta do jogador e a resposta predeterminada com o chamada(). Além disto, se o usuário decidir pular uma questão, é explicitado no LCD que a habilidade de pular foi usada, prosseguindo com o jogo após tocar um som sinalizando esta perda da possibilidade de pular.

```C++
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

```
**fase2()** -  É impresso no LCD as instruções para esta fase do jogo, após isso, são chamadas as funções embaralhar() para serem escolhidas as questões e o perguntas() para o jogador responder e assim poder prosseguir com o jogo.


```C++
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

```
*Fase 3 (Pergunta Final):*

**fase3()** - Nesta função é feita a ultima fase por completo, sendo imprimido um aviso no LCD que a pergunta final será pergunta. Após isso, é impressa a pergunta final, no caso deste projeto,“Você é um robô?”, e as opções que, como na fase 2, são sim ou não. Depois, são lidos os botões (btnSim e btnNao) novamente e quando um for pressionado, será usada novamente a função chamada() para ver se a resposta correta foi escolhida. Além disso, é mostrado um timer no LCD, caso o tempo termine, é declarado GAME OVER e o Arduíno é reiniciado. Caso o jogador acerte a pergunta, é tocada uma música de vitória além de uma mensagem de parabéns no LCD. Caso ele erre, é tocado um som de derrota e o Arduíno é reiniciado. 
```C++
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
```
*Botão de iniciar/reiniciar:*
**reiniciar()** - É usada nesta função uma variável global chamada jogo para verificar se o jogo está sendo iniciado ou se o jogador quer reiniciar o jogo. Caso seja o primeiro caso, o jogo se inicia na primeira fase, se for o contrário, o Arduino reiniciará. 
```C++
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
```

*setup:* 
	Os pinos dos LEDs e do buzzer foram setados como OUTPUT para que eles acendam e faça som respectivamente com sucesso, já que eles não registram sinais, apenas recebem. Além disso, os 3 botões foram setados como INPUT_PULLUP para que as ações sejam realizadas com sucesso sem ter que continuar pressionando o botão. Também foi usada a função attachInterrupt() no botão de início para que ele possa reiniciar o Arduino quando necessário. Entre as outras funções usadas no setup, tem a inicialização do terminal com Serial.begin, o noTone para o funcionamento do buzzer e o randomSeed(analogRead(0)) para o funcionamento correto da randomização das luzes na primeira fase e das perguntas na segunda. 

 ```C++
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

```

 **loop()** - No loop, é lido o botão de início, que, quando pressionando, aciona também a leitura da váriavel jogo, que checa se o jogador quer iniciar ou reiniciar o jogo, após isso, ele é levado à primeira fase. Além disso, ao longo do jogo, é adicionado 1 à variável passei a cada fase que o jogador conquista, as fases são trocadas suavemente. Após o jogador vencer a terceira fase, é mostrada a mensagem de vitória e a música de vitória do jogo.  
 ```C++
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

```
*Projeto no TinkerCad:*


![Projeto de Arduino no Tinker Cad](https://github.com/user-attachments/assets/713e1cc2-02a9-4579-9bea-d3239286dc2e)

## Experimentos:


https://github.com/user-attachments/assets/7d6d45d2-77e6-4258-bb79-4799cc79803c
Neste vídeo é mostrado quando o jogador inicia o jogo e erra na primeira fase, resultando na volta ao início do jogo. 


https://github.com/user-attachments/assets/229a5040-8393-409b-99ff-ffb10c348d3d
Neste caso, o jogador aperta o botão de reiniciar o jogo, assim automaticamente o levando de volta para o início do jogo. 




https://github.com/user-attachments/assets/d44a117a-ffa4-46bb-aba9-97e3d11b597b
Neste exemplo, o jogador consegue vencer a primeira fase, assim sendo tocada a música de vitória e a transição para a segunda fase. 




https://github.com/user-attachments/assets/0c9b8d5d-5c73-440e-a589-c81061e13772
Neste caso, é mostrado o que acontece quando o jogador pula uma questão, assim começando do mesmo lugar, com uma pergunta diferente. 




https://github.com/user-attachments/assets/0e7d9fd7-1f54-404d-a1b4-b8c2a00e4bbb

Neste caso, é mostrado o que acontece quando o jogador pula mais de uma questão, perdendo o jogo e assim voltando para a primeira fase. 


https://github.com/user-attachments/assets/1baaab29-0fb3-4a68-8cf1-f3fcca77b43e

Neste vídeo, o jogador consegue com sucesso acertar todas as questões e é levado para a terceira e última fase. 


https://github.com/user-attachments/assets/085c4318-ae6f-43ed-a3db-09eb7e620ee8
Neste exemplo, o jogador erra a pergunta final, causando a sua derrota, acompanhada de uma música e o Arduino é reiniciado. 




https://github.com/user-attachments/assets/cb6e0c2d-f906-4f5e-a0a6-7b151cc18f29

Neste caso, o jogador acerta a pergunta final, assim sendo tocada uma música especial além de uma parabenização através da LCD. 













## Conclusão:

Em resumo, foi desenvolvido o projeto através de um circuito usando o Arduino UNO, uma LCD, 2 luzes de LED, 3 botões, um para resposta de sim/LED verde, um para resposta de não/LED vermelho e um para iniciar/reiniciar o jogo. Os eventos que tomam parte durante o jogo foram feitos a partir de um código em C++ no qual foram feitas várias funções que foram utilizadas em 3 outras funções que representam cada fase (fase1(), fase2() e fase3()). 

Entre os desafios durante o desenvolvimento do projeto, o maior relatado foi com erros do Arduino durante a execução do código. Para a solução, foram encontrados métodos alternativos para poder executar corretamente o que era necessário para o funcionamento integral do projeto, além de vários testes para ser encontrado com precisão as linhas de código que causavam os erros. Após a correção, as linhas eram comentadas e removidas. 
 

