package main

import (
	"bufio"
	"fmt"
	"os"
)

func gcd(a int64, b int64) int64 {
	var result int64 = 0

	if a < b {
		a, b = b, a
	}

	var q int64 = a
	var r int64 = b

	for {
		if r == 0 {
			result = a
			break
		}
		q = a / b
		r = a - (q * b)
		a, b = b, r
	}

	return result
}

func main() {
	var a int64 = 0
	var b int64 = 0

	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)

	fmt.Fscanf(reader, "%d %d", &a, &b)

	var result = gcd(a, b)

	for i := 0; i < int(result); i++ {
		fmt.Fprintf(writer, "1")
	}
	writer.Flush()
}
