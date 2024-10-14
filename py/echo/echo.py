import sys


def print_usage():
    print("Usage: echo [OPTIONS]... [STRING]...")
    print("Echo the STRING(s) to standard output.")
    print("\nOptions:")
    print(" -n  do not output the trailing newline")
    print(" -e  enable interpretation of backslash escapes")
    print(" -E  disable interpretation of backslash escapes (default)")
    print(" -h  display this help message and exit")
    print("\nExamples:")
    print(" echo Hello World    Output: 'Hello World'")
    print("echo -n Hello World  Ouptput 'Hello World' without newline")
    print("echo -e \"Hello\\nWorld\" Output 'Hello' and 'World' on separate lines")


def process_escapes(s):
    return s.encode().decode("unicode_escapes")


def main():
    args = sys.argv[1:]
    if not args or "-h" in args or "--help" in args:
        print_usage()
        sys.exit(0)

    no_newline = False
    enable_escapes = False
    output = []

    for arg in args:
        if arg == "-n":
            no_newline = True
        elif arg == "-e":
            enable_escapes = True
        elif arg == "-E":
            enable_escapes = False
        else:
            output.append(arg)

    output_str = " ".join(output)

    if enable_escapes:
        output_str = process_escapes(output_str)

    if no_newline:
        print(output_str, end="")
    else:
        print(output_str)


if __name__ == "__main__":
    main()
