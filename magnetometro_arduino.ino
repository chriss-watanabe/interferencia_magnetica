#include <Wire.h>
#include <QMC5883LCompass.h>
#include <MPU6050.h>
#include <LiquidCrystal_I2C.h>

// Inicializa os sensores
QMC5883LCompass mag;
MPU6050 mpu;

// Inicializa o LCD I2C (endereço 0x27 ou 0x3F)
LiquidCrystal_I2C lcd(0x27, 20, 4); 

bool paused = false;  // Variável para pausar a exibição dos dados

void setup() {
    Serial.begin(9600);
    Wire.begin();

    // Inicializa o LCD
    lcd.begin(20, 4);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando...");
    delay(1000);
    lcd.clear();


    // Inicializa o QMC5883L (Magnetômetro)
    mag.init();
    Serial.println("Sensor QMC5883L inicializado!");

    // Inicializa o MPU6050 (Acelerômetro e Giroscópio)
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("Erro: MPU6050 não encontrado!");
        lcd.setCursor(0, 0);
        lcd.print("MPU6050 ERRO!");
        while (1);
    } else {
        Serial.println("Sensor MPU6050 detectado!");
    }
}

void loop() {
    // Verifica comandos do Serial Monitor
    if (Serial.available()) {
        char command = Serial.read();
        if (command == 'p') {
            paused = true;
            Serial.println("PAUSADO!");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("PAUSADO");
        } else if (command == 'r') {
            paused = false;
            Serial.println("RETOMADO!");
            lcd.clear();
        }
    }

    if (!paused) {
        // Lê os dados do Magnetômetro
        int mx, my, mz;
        mag.read();
        mx = mag.getX(); // µT
        my = mag.getY(); // µT
        mz = mag.getZ(); // µT

        // Exibe os dados no LCD com unidade (µT)
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mag (uT)");

        lcd.setCursor(0, 1);
        lcd.print("X:"); lcd.print(mx);

        lcd.setCursor(0, 2); // Posição para manter o alinhamento
        lcd.print("Y:"); lcd.print(my);

        lcd.setCursor(0, 3); // Abaixo de Y, centralizado
        lcd.print("Z:"); lcd.print(mz);

        // Lê os dados do Acelerômetro e Giroscópio
        int16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;
        mpu.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);

        // Converte aceleração para m/s²
        float ax = (ax_raw / 16384.0) * 9.81;
        float ay = (ay_raw / 16384.0) * 9.81;
        float az = (az_raw / 16384.0) * 9.81;

        // Converte velocidade angular para rad/s
        float gx = (gx_raw / 131.0) * (3.14159265359 / 180.0);
        float gy = (gy_raw / 131.0) * (3.14159265359 / 180.0);
        float gz = (gz_raw / 131.0) * (3.14159265359 / 180.0);

        //Divisor da tela
        lcd.setCursor(9,1);
        lcd.print("|");
        lcd.setCursor(9,2);
        lcd.print("|");
        lcd.setCursor(9,3);
        lcd.print("|");
        lcd.setCursor(10, 0);
        lcd.print("Acc (m/s2)");
        lcd.setCursor(10, 1);
        lcd.print("X:"); lcd.print(ax);
        lcd.setCursor(10, 2);
        lcd.print("Y:"); lcd.print(ay);
        lcd.setCursor(10, 3);
        lcd.print("Z:"); lcd.print(az);

        // Também exibe no Serial Monitor, formatado para o código em Python
        Serial.print(millis() / 1000);  // Timestamp (in seconds)
        Serial.print(",");
        Serial.print(mx); Serial.print(",");
        Serial.print(my); Serial.print(",");
        Serial.print(mz); Serial.print(",");
        Serial.print(ax); Serial.print(",");
        Serial.print(ay); Serial.print(",");
        Serial.print(az); Serial.print(",");
        Serial.print(gx); Serial.print(",");
        Serial.print(gy); Serial.print(",");
        Serial.println(gz);

        delay(1000);  // Aguarda antes da próxima leitura
    }
}
