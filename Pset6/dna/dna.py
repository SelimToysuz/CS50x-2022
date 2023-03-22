import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("usage: python dna.py databases/small.csv sequence.txt")
        return 1

    # Read database file into a variable
    data = []
    str = []
    names = []

    with open(f"{sys.argv[1]}", "r") as database:
        reader = csv.reader(database)
        i = 0
        for row in reader:
            if i == 0:
                str_no = len(row) - 1
                str.append(row)
                i += 1
                continue
            names.append(row[0])
            data.append([])
            for j in range(str_no):
                data[i - 1].insert(j + 1, int(row[j + 1]))
            i += 1
    database.close()

    # Read DNA sequence file into a variable
    with open(f"{sys.argv[2]}", "r") as sequence:
        text = sequence.readline()
    sequence.close()

    # Find longest match of each STR in DNA sequence
    person = []
    for k in range(str_no):
        person.append((longest_match(text, str[0][k + 1])))

    # Check database for matching profiles
    for j in range(i - 1):
        counter = 0
        for k in range(str_no):
            if person[k] == data[j][k]:
                counter += 1
        if counter == str_no:
            print(f"{names[j]}")
            return 0

    print("No match")
    return 0


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()