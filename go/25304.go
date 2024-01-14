package main 

import (
    "fmt"
    "bufio"
    "os"
)

func main() {
    var reader *bufio.Reader = bufio.NewReader(os.Stdin)
    var writer *bufio.Writer = bufio.NewWriter(os.Stdout)
    
    defer writer.Flush()
    
    var x, n, a, b int
    
    fmt.Fscanln(reader, &x)
    fmt.Fscanln(reader, &n)
    
    var sum int = 0
    
    for i := 0; i < n; i++ {
        fmt.Fscanln(reader, &a, &b)
        sum += (a*b)
    }
    
    if sum == x {
        fmt.Fprintln(writer, "Yes")
    } else {
        fmt.Fprintln(writer, "No")
    }
}