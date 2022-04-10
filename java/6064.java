import java.util.Scanner;

public class Main {
    static int m, n, x, y;
    
    public static void init(Scanner sc){
        m = sc.nextInt();
        n = sc.nextInt();
        x = sc.nextInt();
        y = sc.nextInt();
    }

    public static int gcd(int a, int b){
        if(b == 0)
            return a;
        return gcd(b, a % b);
    }

    public static int calc(){
        int lcm = (m*n)/gcd(m,n);
        int res = -1;
        while(true){
            if(x > lcm){
                break;
            }
            if((x - 1) % n + 1 == y){
                res = x;
                break;
            }
            x += m;
        }
        return res;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        for(int i = 0; i < t; i++){
            init(sc);
            System.out.println(calc());
        }
    }
}
