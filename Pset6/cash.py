from cs50 import get_float

while True:
    cash = get_float("Change owed: ")
    if cash > 0:
        break

change = 0

while cash >= 0.25:
    change += 1
    cash -= 0.25
    cash = round(cash, 2)

while cash >= 0.1:
    change += 1
    cash -= 0.1
    cash = round(cash, 2)

while cash >= 0.05:
    change += 1
    cash -= 0.05
    cash = round(cash, 2)

while cash >= 0.01:
    change += 1
    cash -= 0.01
    cash = round(cash, 2)

print(f"{change}")