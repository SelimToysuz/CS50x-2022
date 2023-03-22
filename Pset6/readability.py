from cs50 import get_string


text = get_string("Text: ")

letter = 0
word = 1
sentence = 0

for i in text:
    if i.isalpha():
        letter += 1
        continue
    if i == ' ':
        word += 1
        continue
    if i == '.' or i == '!' or i == '?':
        sentence += 1
        continue

index = round(5.88 * (letter / word) - 29.6 * (sentence / word) - 15.8)

if index < 1:
    print("Before Grade 1")
if index > 16:
    print("Grade 16+")
elif index > 1:
    print(f"Grade {index}")
