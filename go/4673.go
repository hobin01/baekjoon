package main

import "fmt"

func d(n int) int {
	var sum int = 0
	var array [4]int = [4]int{n % 10, (n % 100) / 10, (n % 1000) / 100, 0}

	if n == 10000 {
		sum = 10001
		return sum
	}

	array[3] = n / 1000

	for i := 0; i < 4; i++ {
		sum += array[i]
	}

	return n + sum
}

func contains(s []int, e int) bool {
	for _, a := range s {
		if a == e {
			return true
		}
	}
	return false
}

func main() {

	var result []int

	for i := 1; i <= 10000; i++ {
		sum := d(i)
		result = append(result, sum)
	}

	for i := 1; i <= 10000; i++ {
		c := contains(result, i)
		if c == false {
			fmt.Println(i)
		}
	}
}
