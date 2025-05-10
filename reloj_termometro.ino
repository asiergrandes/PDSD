#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int horas = 0;
int minutos = 0;
int segundos = 0;
unsigned long tiempoAnterior = 0;
int estado = 0;
int inputPins[] = {A0, A1, A2, A3, A4};

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    if (analogRead(inputPins[i]) > 1000) {
      delay(200);
      if (i == 0) estado = 1;
      else if (i == 1) estado = 2;
      else if (i == 2) estado = 3;
      else if (i == 3) estado = 4;
      else if (i == 4) estado = 0;
    }
  }

  if (estado == 0) menu();
  else if (estado == 1) reloj();
  else if (estado == 2) termometro();
  else if (estado == 3) cambiarHora();
  else if (estado == 4) cambiarMinuto();
}

void menu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1.Reloj 2.Temp");
  lcd.setCursor(0, 1);
  lcd.print("3.Hora 4.Min 5.Sal");
  delay(200);
}

void reloj() {
  if (millis() - tiempoAnterior >= 1000) {
    tiempoAnterior = millis();
    segundos++;
    if (segundos == 60) {
      segundos = 0;
      minutos++;
      if (minutos == 60) {
        minutos = 0;
        horas++;
        if (horas == 24) horas = 0;
      }
    }
  }
  lcd.clear();
  lcd.setCursor(4, 0);
  if (horas < 10) lcd.print("0");
  lcd.print(horas);
  lcd.print(":");
  if (minutos < 10) lcd.print("0");
  lcd.print(minutos);
  lcd.print(":");
  if (segundos < 10) lcd.print("0");
  lcd.print(segundos);
  delay(200);
}

void termometro() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: 23C");
  delay(200);
}

void cambiarHora() {
  horas++;
  if (horas == 24) horas = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nueva hora: ");
  lcd.print(horas);
  delay(200);
}

void cambiarMinuto() {
  minutos++;
  if (minutos == 60) minutos = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nuevo minuto: ");
  lcd.print(minutos);
  delay(200);
}
