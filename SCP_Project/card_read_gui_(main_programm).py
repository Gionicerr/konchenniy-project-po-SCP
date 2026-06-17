import tkinter as tk
from tkinter import font
import threading
import serial
import subprocess
import time
import sys
import os

BG_COLOR = "#000000"
FG_COLOR = "#ffd000"   # жёлтый терминальный

PORT = "COM6"
BAUDRATE = 9600

ALLOWED_UID = "29 1B 44 02"

EXE_TO_RUN = os.path.join(r"C:\SCP_Project", "SCPClass_clear_cmd.exe")

# ---------- GUI ----------

root = tk.Tk()
root.title("SCP Terminal")
root.configure(bg=BG_COLOR)

# Размер окна
root.geometry("1600x900")

# Моноширинный шрифт
mono = font.Font(family="Consolas", size=14)

# Общий frame
frame = tk.Frame(root, bg=BG_COLOR)
frame.pack(fill="both", expand=True, padx=20, pady=20)

# Верхняя строка
label_top = tk.Label(
    frame,
    text="SYSTEM ONLINE",
    fg=FG_COLOR,
    bg=BG_COLOR,
    font=mono,
    anchor="w",
)
label_top.pack(anchor="nw")

label_line = tk.Label(
    frame,
    text="==================== [SCIENTIST INTERFACE] ====================",
    fg=FG_COLOR,
    bg=BG_COLOR,
    font=mono,
    anchor="w",
)
label_line.pack(anchor="nw", pady=(0, 20))

# Блок SCP справа
scp_box = (
    "            _ _ _ _ _ _ _ _ _         \n"
    "           |                 |        \n"
    "           |                 |        \n"
    "           |                 |        \n"
    "         _/                   \\_      \n"
    "       _/                       \\_    \n"
    "      /                           \\   \n"
    "     /             | |             \\       \n"
    "    |             _| |_             |       \n"
    "   |            _— | | —_            |      \n"
    "   |           /   | |   \           |      \n"
    "  |           /    \\ /    \           |      \n"
    "  |          |             |          |      \n"
    "  |           \  / | | \\  /           |      \n"
    "  |            —/ /   \\ \\—            |      \n"
    "   |           / /—_ _—\\ \\           |      \n"
    "   |          / /       \\ \\          |      \n"
    "  /                                   \\        \n"
    " /                                     \\        \n"
    "/                _______                \\        \n"
    " — —_ _         /       \\         _ _— —       \n"
    "      _ _   —  /         \\  —   _ _       \n"
    "         — —                  — —       \n"
    "            THE SCP FOUNDATION     "
)

scp_label = tk.Label(
    frame,
    text=scp_box,
    fg=FG_COLOR,
    bg=BG_COLOR,
    font=mono,
    justify="left",
)
scp_label.pack(anchor="ne")

# Текст логина
login_label = tk.Label(
    frame,
    text="ATTACH YOUR ACCESS CARD PLEASE",
    fg=FG_COLOR,
    bg=BG_COLOR,
    font=mono,
    anchor="w",
)
login_label.pack(anchor="nw", pady=(40, 10))

# Строка CARD > _
name_frame = tk.Frame(frame, bg=BG_COLOR)
name_frame.pack(anchor="nw", pady=(10, 0))

prompt_label = tk.Label(
    name_frame,
    text="CARD > ",
    fg=FG_COLOR,
    bg=BG_COLOR,
    font=mono,
)
prompt_label.pack(side="left")

name_var = tk.StringVar()

entry = tk.Entry(
    name_frame,
    textvariable=name_var,
    fg=FG_COLOR,
    bg=BG_COLOR,
    insertbackground=FG_COLOR,
    relief="flat",
    font=mono,
    width=30,
)
entry.pack(side="left")
entry.focus_set()

# ---------- Логика RFID / запуск программы ----------

# пробуем открыть порт
try:
    ser = serial.Serial(PORT, BAUDRATE, timeout=1)
except Exception as e:
    ser = None
    login_label.config(text=f"ERROR: CAN'T OPEN {PORT}: {e}")

def update_status(uid):
    login_label.config(text="CARD DETECTED: *****")

def set_access_granted():
    login_label.config(text="CARD DETECTED: *****")
    name_var.set("Access ACCEPTED")
    try:
        subprocess.Popen(
            ["cmd", "/c", "start", "", EXE_TO_RUN],
            shell=True
        )
        root.destroy()
    except Exception as e:
        name_var.set(f"START ERROR: {e}")


def set_access_denied():
    login_label.config(text="CARD DETECTED: *****")
    name_var.set("Access DENIED")

def reader_loop():
    if ser is None:
        return
    while True:
        try:
            line = ser.readline().decode("utf-8").strip()
        except Exception:
            continue
        if not line:
            continue

        parts_split = line.split(":", 1)
        uid_part = parts_split[1] if len(parts_split) > 1 else line

        # убираем лишние пробелы и приводим к верхнему регистру
        parts = uid_part.split()
        uid = " ".join(parts).upper()

        print(repr(uid))

        root.after(0, update_status, uid)

        if uid == ALLOWED_UID:
            root.after(0, set_access_granted)
        else:
            root.after(0, set_access_denied)

        time.sleep(0.1)


# Обработка Enter (ручной ввод, если нужен)
def on_enter(event=None):
    uid = name_var.get().strip()
    if not uid:
        return
    if uid == ALLOWED_UID:
        set_access_granted()
    else:
        set_access_denied()

entry.bind("<Return>", on_enter)

# Старт фонового потока чтения
if ser is not None:
    t = threading.Thread(target=reader_loop, daemon=True)
    t.start()

root.mainloop()