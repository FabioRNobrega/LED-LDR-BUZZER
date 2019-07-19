//Autor: Fábio R. Nóbrega
//Artista: Lays Santos

//Carrega a biblioteca LiquidCrystalpara Display LCD 1602
#include <LiquidCrystal.h>

int tempo = 60; // Estabelece o valor inicial que aparece no display
const int buzzer = 10;
const int sensorPin = A0; // Porta do Sensor LDR Analógico
int ledPin13 = 13; // Led para Debug
int sensorValue = 0; // Varavel criada para alcance da sencibilidade do LDR
int tempoDuracao = tempo; // Valor de duração da contagem regreciva

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(sensorPin, INPUT); // Estabelece conecção física com o LDR
  pinMode(ledPin13, OUTPUT);// // Estabelece conecção física com o LED
  pinMode(buzzer, OUTPUT); // Conecção Buzzer
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2); // Inicia o Display
  Serial.begin(9600);// inicia Conecção com porta Serial Monitor e Plotter
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  if (sensorValue <= 110) {
    noTone(buzzer); // Deliga Buzzer
    digitalWrite(ledPin13, LOW); // Deliga Led
    lcd.noDisplay();// Deliga o Display
    tempoDuracao = tempo;  // Reinicia o valor da variavel
  }

  if  (sensorValue > 120 ) {

    digitalWrite(ledPin13, HIGH);

    lcd.display();//Liga a tela

    if ((tempoDuracao < tempo + 1) && (tempoDuracao > -1)) {
      lcd.setCursor(7, 0);//Posiciona o cursor na coluna 7, linha 1;
      tone(buzzer, 900); //Ligando o buzzer com uma frequencia de 900 hz.
      lcd.print(tempoDuracao--);

      delay(500);
      noTone(buzzer);//Desligando o buzzer. Gerando BIP
      delay(1000);
      lcd.clear();

    } else {
      lcd.clear();//Posiciona o cursor na coluna 0, linha 0;
      lcd.setCursor(0, 0);//Envia o texto entre aspas para o LCD
      lcd.print("Desculpe eu estava ocupada...");//Posiciona o cursor na coluna 0, linha 1;

      //Rolagem para a esquerda
      for (int posicao = 0; posicao < 30; posicao++)
      {
        lcd.scrollDisplayLeft();
        delay(300);
        tone(buzzer, 900); // Buzzer tocando constante
      }
    }
  }
}






