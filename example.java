import java.util.*;

public class Example {
    private static final int MAX_COUNT = 100;
    public String message = "Hello, World!";

    public static void main(String[] args) {
        Example example = new Example();
        example.run();
    }

    public void run() {
        int x = 42;
        double y = 3.14159;
        float z = 2.718f;
        long bigNumber = 123456789L;
        boolean flag = true;
        char letter = 'A';
        int hexValue = 0x1A3F;

        // Single line comment
        String text = "This is a \"test\" string";

        if (x > 0 && flag) {
            for (int i = 0; i < 10; i++) {
                System.out.println("Count: " + i);
            }
        } else {
            System.out.println(message);
        }

        /* Multi-line
           comment block */
        try {
            int[] numbers = {1, 2, 3, 4, 5};
            for (int num : numbers) {
                processNumber(num);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        int result = calculate(5, 3);
        System.out.printf("Result: %d\n", result);
    }

    private void processNumber(int num) {
        switch (num) {
            case 1:
                System.out.println("One");
                break;
            case 2:
                System.out.println("Two");
                break;
            default:
                System.out.println("Other: " + num);
        }
    }

    private int calculate(int a, int b) {
        return a * b + (a - b) / 2;
    }

    @Override
    public String toString() {
        return "Example{" +
               "message='" + message + '\'' +
               '}';
    }
}