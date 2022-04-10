import java.util.Scanner;

public class Main {
    public static void main(String[] args){
        int num = 0;
        int res = 0;
        Scanner sc = new Scanner(System.in);
        for(int i = 0; i < 4; i++){
            int num1 = sc.nextInt();
            int num2 = sc.nextInt();
            num -= num1;
            num += num2;
            res = res > num ? res : num;
        }
        System.out.println(res);
    }
}