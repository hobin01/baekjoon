package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var s string
	writer := bufio.NewWriter(os.Stdout)
	reader := bufio.NewReader(os.Stdin)

	s, _ = reader.ReadString('\n') // \n 나올 때까지 입력
	// s = strings.TrimSpace(s)       // 앞 뒤 줄바꿈, 공백 등 불필요한 문자 제거 (순수 s)
	str := []rune(s)

	for i := 0; i < len(str); i++ {
		if str[i] >= 'a' && str[i] <= 'z' {
			tmp := str[i] - 'a'
			str[i] = 'a' + (tmp+13)%26
		} else if str[i] >= 'A' && str[i] <= 'Z' {
			tmp := str[i] - 'A'
			str[i] = 'A' + (tmp+13)%26
		}
	}

	s = string(str)
	fmt.Fprintf(writer, "%s", s)

	writer.Flush()
}
