package main
import "fmt"

func main() {
    var n int
    fmt.Scan(&n)
    
    for i := n; i >= 1; i-- {
        for j := 0; j < i; j++ {
            fmt.Print("*")
        }
        fmt.Print("\n")
    }
}