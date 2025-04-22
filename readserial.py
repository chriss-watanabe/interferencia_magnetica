import serial
import csv
import threading
from datetime import datetime

#define a porta (MEGA: COM4, UNO: COM6) e o baud rate (Monitor Serial)
PORT = 'COM6'
BAUD = 9600
FILENAME = f"sensor_log_{datetime.now().strftime('%H%M%S')}.csv"

#pausa da leitura
paused = False
running = True

def toggle_pause():
    global paused, running
    print("Pressione Enter para pausar/continuar.")
    print("Pressione CTRL + C para fechar o código.")
    while running:
        input()
        paused = not paused
        print("⏸ Pausado." if paused else "▶ Continuando.")

listener = threading.Thread(target=toggle_pause)
listener.daemon = True
listener.start()

ser = serial.Serial(PORT, BAUD)
print(f"Logging data to {FILENAME}...")

with open(FILENAME, mode='w', newline='') as file:
    writer = csv.writer(file)
    #programa le os dados do monitor serial, separados por vírgula, e imprime em um arquivo .csv salvo na mesma pasta
    #hora em milissegundos, com uma leitura por segundo
    writer.writerow(['Hora', 'Mag_X (uT)', 'Mag_Y (uT)', 'Mag_Z (uT)', 'Accel_X (m/s²)', 'Accel_Y (m/s²)', 'Accel_Z (m/s²)', 'Gyro_X (rad/s)', 'Gyro_Y (rad/s)', 'Gyro_Z (rad/s)'])

    try:
        while True:
            if paused:
                continue

            line = ser.readline().decode('utf-8').strip()

            try:
                data = line.split(',')
                if len(data) == 10:
                    writer.writerow(data)
                else:
                    print("Formato inválido:", line)
            except Exception as e:
                print(f"Erro compilando linha: {e}")

    #programa deve ser encerrado para que os dados da pasta sejam compilados
    except KeyboardInterrupt:
        print("Logging interrompido.")
    finally:
        ser.close()
