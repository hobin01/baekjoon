package main

import (
	"fmt"
)

func min(num1 int, num2 int) int {
	if num1 > num2 {
		return num2
	} else {
		return num1
	}
}

func main() {
	var n int
	fmt.Scanln(&n)

	// dp[n] = min(dp[n], dp[n-제곱수] + 1)
	// 처음에 dp[n] = n 으로 초기화
	var dp [100001]int
	for i := 0; i <= 100000; i++ {
		dp[i] = i
	}

	for i := 1; i <= n; i++ {
		for j := 1; j*j <= i; j++ {
			dp[i] = min(dp[i], dp[i-j*j]+1)
		}
	}

	fmt.Println(dp[n])
}
