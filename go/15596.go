package main

func sum(a []int) int {
	var result int = 0
	for i := 0; i < len(a); i++ {
		result += a[i]
	}
	return result
}
