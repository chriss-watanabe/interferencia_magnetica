# EMI Impact Logger – Arduino + Python

Este repositório apresenta os códigos utilizados no experimento "**Análise e Mitigação da Interferência Eletromagnética em Sistemas Eletrônicos**", conduzido como projeto da disciplina **Soluções para Desafios de Engenharia** na **Universidade Federal do ABC (UFABC)**.

O projeto tem como objetivo observar, analisar e discutir as consequências da interferência eletromagnética (IEM) em aeronaves, foguetes, satélites e outros veículos e equipamentos diversos; Simular os efeitos de IEM e modelar um experimento prático para comprovar os resultados; Propor e testar soluções para mitigar os efeitos da IEM e melhorar a compatibilidade eletromagnética em sistemas eletrônicos.

O projeto é de autoria de Allan Kuwabara, Christian Watanabe, Cauet Scariot e Julia Marion, com a orientação da Prof. Dra. Claudia Celeste Celestino de Paula Santos.

---

## Estrutura do repositório

/arduino/ magnetometro_arduino

Código para Arduino IDE (C++) de leitura dos sensores QMC5883L e MPU6050 e compilação dos dados através da porta serial.

/python/ read_serial.py

Código em Python para leitura dos dados da porta serial e posterior gravação em um arquivo CSV.

---

## Componentes utilizados

- Magnetômetro QMC5883L
- Acelerômetro e giroscópio MPU6050;
- Arduino UNO;
- Display LCD 20x4 (Interface I2C);
- Placa de prototipagem (protoboard);
- Cabos jumper macho-macho;

---

## Software e bibliotecas utilizadas

- **Arduino IDE**
- Bibliotecas do Arduino:
  - [Wire.h](https://www.arduino.cc/en/Reference/Wire) (standard)
  - [QMC5883LCompass.h](https://github.com/mprograms/QMC5883LCompass)
  - [MPU6050.h](https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050)
  - [LiquidCrystal_I2C.h](https://github.com/johnrickman/LiquidCrystal_I2C)

- **Python 3**
  - [pyserial](https://pypi.org/project/pyserial/)
 
  Instalação:
  pip install pyserial
  
## Funcionamento do código
Setup Arduino
Conecte os sensores e LCD de acordo com a configuração apresentada;

Abra o arquivo magnetometro_arduino no Arduino IDE;

Verifique e upload o sketch para o Arduino;

Confira a impressão dos dados através do monitor LCD e da porta serial (Baud 9600).

Log de dados Python
Conecte o Arduino ao computador;

Edite as variáveis PORT e BAUD do arquivo read_serial.py de acordo com as especificações do seu computador;

Rode o arquivo python no Terminal (ou em outra IDE preferida):
python serial_logger.py

Os dados serão salvos após o fim da execução do código.

Cada coluna de dados segue a seguinte formatação:

Hora (s),Mag_X (uT),Mag_Y (uT),Mag_Z (uT),Accel_X (m/s²),Accel_Y (m/s²),Accel_Z (m/s²),Gyro_X (rad/s),Gyro_Y (rad/s),Gyro_Z (rad/s)

## Notas
Pressione ENTER no Terminal para pausar e retomar a leitura de dados pelos sensores.

Pressione CTRL+C no Terminal para interromper a execução do código Python e salvar os dados no arquivo CSV.

Certifique-se que a porta serial e o Baud rate estão definidos conforme a configuração atual do Arduino. É possível verificar a porta utilizada pela placa através do próprio Arduino IDE.

No início do programa, duas mensagens de erro serão impressas: "Formato inválido: Sensor QMC5883L inicializado!" e "Formato inválido: Sensor MPU6050 detectado!", que inevitavelmente fogem da formatação dos dados esperados para a porta serial, mas não comprometem o funcionamento normal da aplicação.

Referências

[QMC5883L Datasheet](https://qstcorp.com/upload/pdf/202202/13-52-04%20QMC5883L%20Datasheet%20Rev.%20A(1).pdf)

[MPU6050 Datasheet](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)
