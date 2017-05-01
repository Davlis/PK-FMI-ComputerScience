package lab07;

import java.io.*;
import java.util.*;

class ReversPolishNotation {
    private String postfix;

    public ReversPolishNotation(String str) {
        postfix = isPostfix(str) ? str : toPostfix(str);
    }

    public String solve(){
        double out = this.compute();
        if(out%1 != 0)
            return String.valueOf(out);
        else
            return String.valueOf((int) out);
    }

    private double compute() {
        String[] input = postfix.split("\\s");
        Deque<Double> stack = new LinkedList<>();

        for (String token : input) {
            if (isOperand(token)) {
                stack.push(toDouble(token));
            } else if (isOperator(token) && stack.size() >= 2) {
                double operandB = stack.pop();
                double operandA = stack.pop();
                stack.push(eval(operandA, token, operandB));
            } else {
                return 0.0;
            }
        }

        return stack.pop();
    }

    public String toString() {
        return postfix;
    }

    private String toPostfix(String infix) {
        StreamTokenizer input = new StreamTokenizer(new StringReader(infix));
        StringBuilder output = new StringBuilder();
        Deque<Character> stack = new LinkedList<>();
        input.ordinaryChar('x');
        input.ordinaryChar('/');
        input.ordinaryChar('-');

        int type;
        try {
            while ((type = input.nextToken()) != StreamTokenizer.TT_EOF) {
                if (type >= 0) {
                    char token = (char) type;
                    if (token == '(') {
                        stack.push(token);
                    } else if (token == ')') {
                        while (!stack.isEmpty() && stack.peek() != '(')
                            output.append(stack.pop()).append(' ');

                        if (stack.peek() != '(') {
                            return null;
                        } else {
                            stack.pop();
                        }
                    } else {
                        if (!stack.isEmpty() && stack.peek() != '(') {
                            while (!stack.isEmpty() && precedence(token, stack.peek()) <= 0) {
                                output.append(stack.pop()).append(' ');
                            }
                        }

                        stack.push(token);
                    }
                } else if (type == StreamTokenizer.TT_NUMBER) {
                    output.append(input.nval).append(' ');
                }
            }
        } catch (IOException ex) {
            return null;
        }

        if (stack.contains('(') || stack.contains(')'))
            return null;

        while (!stack.isEmpty())
            output.append(stack.pop()).append(' ');

        return output.toString().trim();
    }

    private int precedence(char opA, char opB) {
        final String operatorOrder = "-+/x*";
        return operatorOrder.indexOf(opA) - operatorOrder.indexOf(opB);
    }

    private double eval(double a, String operator, double b) {
        switch (operator) {
            case "+":
                return a + b;
            case "-":
                return a - b;
            case "/":
                return a / b;
            case "*":
            case "x":
                return a * b;
        }

        return 0.0;
    }

    private double toDouble(String str) {
        try {
            return Double.parseDouble(str);
        } catch (NumberFormatException ex) {
            return 0.0;
        }
    }

    private boolean isOperand(String str) {
        return str.matches("\\d+(\\.\\d+)?");
    }

    private boolean isOperator(String str) {
        return str.matches("[-+/x*]");
    }

    private boolean isPostfix(String str) {
        String[] input = str.split("\\s");
        boolean lastTokenOperand = false;

        for (String token : input) {
            if (isOperator(token) && lastTokenOperand)
                lastTokenOperand = false;
            else if (isOperand(token) && lastTokenOperand)
                return true;
            else
                lastTokenOperand = true;
        }

        return false;
    }
}