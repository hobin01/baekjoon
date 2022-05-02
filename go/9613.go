package main

import (
	"fmt"
)

func gcd(a, b int) int {
	for b != 0 {
		t := b
		b = a % b
		a = t
	}
	return a
}

func getSum(numbers []int) int {
	sum := 0
	len := len(numbers)
	if len == 1 {
		return numbers[0]
	}

	for i := 0; i < len-1; i++ {
		for j := i + 1; j < len; j++ {
			sum += gcd(numbers[i], numbers[j])
		}
	}

	return sum
}

func main() {
	var t int
	fmt.Scanln(&t)

	for i := 0; i < 2*t; i++ {
		var n int
		fmt.Scanf("%d", &n)
		numbers := make([]int, 0, n)
		for j := 0; j < n; j++ {
			var num int
			fmt.Scan(&num)
			numbers = append(numbers, num)
		}
		sum := getSum(numbers)
		if sum == 0 {
			continue
		}
		fmt.Println(sum)
	}

}
