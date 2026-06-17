import tkinter as tk
from tkinter import font, scrolledtext
import threading

BG_COLOR = "#000000"
FG_COLOR = "#ffd000"   # Р¶С‘Р»С‚С‹Р№ С‚РµСЂРјРёРЅР°Р»СЊРЅС‹Р№

# ---------- GUI ----------

root = tk.Tk()
root.title("SCP Terminal")
root.configure(bg=BG_COLOR)
root.geometry("1600x900")

mono = font.Font(family="Consolas", size=14)

frame = tk.Frame(root, bg=BG_COLOR)
frame.pack(fill="both", expand=True, padx=20, pady=20)

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

# ---------- Р›РµРІР°СЏ РєРѕР»РѕРЅРєР° СЃРѕ СЃРїРёСЃРєРѕРј РєРѕРјР°РЅРґ ----------

scp_list_text = (
    "AVAILABLE COMMANDS:\n"
    " 1. to add an employee\n"
    " 2. to delete an employee\n"
    " 3. to trigger every person\n"
    " 4. to print staff information\n"
    " 5. to add the SCP\n"
    " 6. to delete the SCP\n"
    " 7. to simulate massive breach\n"
    " 8. to interact the SCP with other SCP/staff\n"
    " 9. to print SCPs threat report\n"
    " 0. to print menu\n"
)

commands_row = tk.Frame(frame, bg=BG_COLOR)
commands_row.pack(anchor="nw", fill="x", pady=(0, 20))

scp_list_label = tk.Label(
    commands_row,
    text=scp_list_text,
    fg=FG_COLOR,
    bg=BG_COLOR,
    font=mono,
    justify="left",
    anchor="nw",
)
scp_list_label.pack(side="left", anchor="nw")

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
    "   |           /   | |   \\           |      \n"
    "  |           /    \\ /    \\           |      \n"
    "  |          |             |          |      \n"
    "  |           \\  / | | \\  /           |      \n"
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
    commands_row,
    text=scp_box,
    fg=FG_COLOR,
    bg=BG_COLOR,
    font=mono,
    justify="left",
)
scp_label.pack(side="left", padx=(40, 0), anchor="ne")

# ---------- РћР±Р»Р°СЃС‚СЊ РІС‹РІРѕРґР° СЂРµР·СѓР»СЊС‚Р°С‚РѕРІ ----------

output_frame = tk.Frame(frame, bg=BG_COLOR)
output_frame.pack(anchor="nw", fill="both", expand=True, pady=(20, 0))

output_label = tk.Label(
    output_frame,
    text="OUTPUT:",
    fg=FG_COLOR,
    bg=BG_COLOR,
    font=mono,
    anchor="w",
)
output_label.pack(anchor="nw")

output_text = scrolledtext.ScrolledText(
    output_frame,
    fg=FG_COLOR,
    bg=BG_COLOR,
    insertbackground=FG_COLOR,
    font=mono,
    wrap=tk.WORD,
    width=80,
    height=15,
    relief="flat",
    borderwidth=0,
)
output_text.pack(anchor="nw", fill="both", expand=True)

# ---------- Р’РІРѕРґ РєРѕРјР°РЅРґС‹ ----------

input_frame = tk.Frame(frame, bg=BG_COLOR)
input_frame.pack(anchor="nw", pady=(10, 0))

prompt_label = tk.Label(
    input_frame,
    text="ENTER COMMAND > ",
    fg=FG_COLOR,
    bg=BG_COLOR,
    font=mono,
)
prompt_label.pack(side="left")

command_var = tk.StringVar()

entry = tk.Entry(
    input_frame,
    textvariable=command_var,
    fg=FG_COLOR,
    bg=BG_COLOR,
    insertbackground=FG_COLOR,
    relief="flat",
    font=mono,
    width=30,
)
entry.pack(side="left")
entry.focus_set()

root.mainloop()