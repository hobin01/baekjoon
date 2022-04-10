package main

import "fmt"

func main() {

	var n int
	fmt.Scanln(&n)

	if n < 100 {
		fmt.Println(n)
	} else {
		var cnt int = 0
		for i := 100; i <= n; i++ {
			if (i/100 + i%10) == (2 * ((i % 100) / 10)) {
				cnt++
			}
		}
		fmt.Println(cnt + 99)
	}
}
