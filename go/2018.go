package main 

import (
    "fmt"
    "bufio"
    "os"
)

func main() {
    reader := bufio.NewReader(os.Stdin)
    writer := bufio.NewWriter(os.Stdout)
    
    defer writer.Flush()
    
    var n int 
    fmt.Fscanln(reader, &n)
    
    arr := make([]int, n)
    for i := 1; i <= n; i++ {
        arr[i-1] = i 
    }
    
    now, end, result := 0, 0, 0
    for i := 0; i < n; i++ {
        for {
            if (end >= n) || (now >= n) {
                break 
            }
            
            now += arr[end]
            end += 1 
        }
        
        if now == n {
            result += 1 
        }
        
        now -= arr[i]
    }
    
    fmt.Fprintln(writer, result)
}