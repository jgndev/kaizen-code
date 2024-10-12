package main

import (
	"fmt"
	"os"
	"strings"
)

func printUsage() {
	fmt.Println("Usage: echo [OPTION]... [STRING]...")
	fmt.Println("Echo the STRING(s) to standard output.")
	fmt.Println("\nOptions:")
	fmt.Println("	-n	do not output the trailing newline")
	fmt.Println("	-e	enable interpretation of backslash escapes")
	fmt.Println("	-E	disable interpretatoin of backslash escapes")
	fmt.Println("	-h	display this help message and exit")
	fmt.Println("\nExamples:")
	fmt.Println("	echo Hello World	Output 'Hello World'")
	fmt.Println("	echo -n Hello World	Output 'Hello World' without a newline")
	fmt.Println("	echo -e \"Hello\\nWorld\" Output 'Hello' and 'World' on separate lines")
}

func main() {
	// Get all arguments except the program name
	args := os.Args[1:]
	noNewLine := false
	enableEscapes := false
	output := []string{}

	if len(args) == 0 {
		printUsage()
		os.Exit(0)
	}

	// Process flags and collect the text to echo
	for _, arg := range args {
		switch arg {
		case "-n":
			noNewLine = true
		case "-e":
			enableEscapes = true
		case "-E":
			enableEscapes = false
		case "-h", "--help":
			printUsage()
			os.Exit(0)
		default:
			output = append(output, arg)
		}
	}

	// Join the putput arguments into a single string
	outputStr := strings.Join(output, " ")

	// Process escape sequences if enabled
	if enableEscapes {
		outputStr = processEscapes(outputStr)
	}

	// Print the output
	if noNewLine {
		fmt.Print(outputStr)
	} else {
		fmt.Println(outputStr)
	}
}

func processEscapes(s string) string {
	s = strings.Replace(s, "\\n", "\n", -1)
	s = strings.Replace(s, "\\t", "\t", -1)
	s = strings.Replace(s, "\\\\", "\\", -1)

	return s
}
