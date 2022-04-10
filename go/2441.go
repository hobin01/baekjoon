package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	n := 0
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	fmt.Fscanln(reader, &n)

	for i := 0; i < n; i++ {
		for j := 0; j < i; j++ {
			fmt.Fprintf(writer, " ")
		}
		for j := i; j < n; j++ {
			fmt.Fprintf(writer, "*")
		}
		fmt.Fprintln(writer)
	}

	writer.Flush()
}
