import threading
import time
import tkinter as Tkinter

import serial

SCALE = 50
FREQUENCY = 100  # ms
PORT = "/dev/ttyACM0"
BAUDRATE = 115200
INVERT = True

WIDTH = 19
HEIGTH = 19


def rgb(red, green, blue):
    return f"#{red:02x}{green:02x}{blue:02x}"


def grayscale(gray):
    return f"#{gray * 0x00010101:06x}"


arduino = serial.Serial(PORT, BAUDRATE, parity=serial.PARITY_EVEN, bytesize=8, stopbits=1)

window = Tkinter.Tk()
window.title("ADNS5050 CAMERA")
window.geometry(f"{str(WIDTH*SCALE)}x{HEIGTH*SCALE}")
window.configure(bg=rgb(255, 255, 255))

canvas = Tkinter.Canvas(width=WIDTH * SCALE, height=HEIGTH * SCALE, bg=rgb(255, 255, 255))
canvas.pack()


def pixel(x, y, color):
    x *= SCALE
    y *= SCALE
    canvas.create_rectangle(x, y, x + SCALE, y + SCALE, fill=grayscale(color - 128 if INVERT else color), width=0)


def thread():
    while True:
        frame = arduino.readline().rstrip(b"\n")
        if len(frame) == (WIDTH * HEIGTH):  # Protect against dropped frames
            for x in range(WIDTH):
                for y in range(HEIGTH):
                    pixel(x, y, frame[y + (x * HEIGTH)])
        time.sleep(FREQUENCY / 1000)


threading.Thread(daemon=True, target=thread).start()
window.mainloop()
