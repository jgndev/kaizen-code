import sys

def count_words(filename):
    try:
        with open(filename, 'r') as file:
            return sum(len(line.split()) for line in file)
    except IOError as e:
        print(f"Error reading file '{filename}': {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: python3 {sys.argv[0]} <filename>", file=sys.stderr)
        sys.exit(1)

    filename = sys.argv[1]
    total_words = count_words(filename)
    print(f"Word count: {total_words}")
