while True:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("That is not an integer")
    else:
        if height > 0 and height < 9:
            break

l = 1
for i in range(height):
    for j in range(height - l):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
    print("  ", end=""y)
    for t in range(i + 1):
        print("#", end="")
    print()
    l += 1