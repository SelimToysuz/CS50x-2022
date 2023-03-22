from cs50 import get_int


def main():
    # Numara sıfırdan büyük olana kadar soruyor
    while True:
        number = get_int("Number: ")
        if number > 0:
            break

    # Basamak sayısını hesaplıyor
    digit_no = len(str(number))

    # Rakamları bir listeye topluyor
    digits = []
    for i in str(number):
        digits.append(i)

    # Luhn's algoristmasına uygunluğu kontrol ediyor
    if (luhns_algorithm(digit_no, digits)) == False:
        print("INVALID")
        return 1

    # Hangi kart olduğunu yazdırıyor
    if digit_no == 15:
        if int(digits[0]) == 3:
            if int(digits[1]) == 4 or 7:
                print("AMEX")
                return 0

    if digit_no == 13 or 16:
        if int(digits[0]) == 4:
            print("VISA")
            return 0

    if digit_no == 16:
        if int(digits[0]) == 5:
            if int(digits[1]) == 1 or 2 or 3 or 4 or 5:
                print("MASTERCARD")
                return 0

    else:
        print("INVALID")
        return 0

# Luhn's algoritmasına uygunluğunu test ediyor


def luhns_algorithm(digit_no, digits):
    counter = 0

    for i in range(2, digit_no + 1, 2):
        if (2 * int(digits[digit_no - i])) > 9:
            counter += (2 * int(digits[digit_no - i])) % 10
            counter += 1
        else:
            counter += (2 * int(digits[digit_no - i]))
        counter += int(digits[digit_no - (i - 1)])

    if (digit_no % 2) != 0:
        counter += int(digits[0])

    if (counter % 10) == 0:
        return True
    return False


main()