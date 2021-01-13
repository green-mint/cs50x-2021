import csv
import sys

def calculate_sequence_reps(seq: str, dna_sample: str) -> int:

    index = dna_sample.find(seq)

    if index == -1:
        return 0
    else:
        count = 0
        while (dna_sample[index:index+len(seq)] == seq):
            count += 1
            index += len(seq)
        count_next = calculate_sequence_reps(seq,dna_sample[index:])
        if (count > count_next):
            return count
        else:
            return count_next

def main():
    #if (len(sys.argv) != 3):
        #sys.exit("Usage: python dna.py database.csv sequence.txt")

    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        database = list(reader)

    with open(sys.argv[2], "r") as file:
        dna_sample = file.readline()

    
    for entry in database:
        similar = True
        #print(entry["name"].upper() + "\n")
        for key in entry.keys():
            if key == "name":
                continue
            
            #print(f"{entry[key]} in database is {int(entry[key])} and calculated is {calculate_sequence_reps(key,dna_sample)}\n")
            if int(entry[key]) != calculate_sequence_reps(key,dna_sample):
                similar = False
                break
        if similar:
            print(entry["name"])
            return 1;

    print("No match")
    return 0


if __name__ == "__main__":
    main()