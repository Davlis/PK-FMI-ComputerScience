package lab08;

import java.util.ArrayList;
import java.util.Scanner;

/**
 * Created by kamil on 16/05/2017.
 */
public class Threads
{
    private static final int amountOfThreads;

    private final Matrix m;
    private final Vector v;
    private ArrayList<Thread> threadArray;

    static
    {
        System.out.println("How many threads do you want? (int)");
        Scanner input = new Scanner(System.in);
        amountOfThreads = input.nextInt();
    }

    public Threads(){
        v = this.makeVector();
        System.out.println("Vector:\n" + v);
        m = this.makeMatrix();
        System.out.println("Matrix:\n" + m);

        threadArray = new ArrayList<Thread>();
        for(int i = 0; i < Threads.amountOfThreads; i++)
            threadArray.add(new Thread(new ColumnThread(v, m, i+1)));

        System.out.println("Threads have been started\n");
        for(int i = 0; i < threadArray.size(); i++){
            try {
                threadArray.get(i).start();
                threadArray.get(i).join();
            }
            catch (InterruptedException ex) {
                ex.printStackTrace();
                System.out.println("FFS CHARLES Y U NO COUNT THREAD " + i);
            }
        }
    }

    private Vector makeVector() {
        Vector v = new Vector(Threads.amountOfThreads);
        for(int i = 0; i < Threads.amountOfThreads; i++){
            v.setValue(i, 4);
        }
        return v;
    }

    private Matrix makeMatrix() {
        Matrix m = new Matrix(Threads.amountOfThreads);
        for(int i = 0; i < Threads.amountOfThreads; i++){
            for(int j = 0; j < Threads.amountOfThreads; j++){
               m.setValue(i, j, (i+1)+(i*j));
            }
        }
        return m;
    }

    private class ColumnThread implements Runnable {
        private Vector v;
        private Matrix m;
        private int threadNumber;

        public ColumnThread(Vector v, Matrix m, int threadNumber){
            System.out.println("Creating thread: " + threadNumber);
            this.v = v;
            this.m = m;
            this.threadNumber = threadNumber;
        }

        public void run() {
            Vector out = m.getColumnVector(threadNumber-1).simple_multiplication(v);
            System.out.println("Thread number: " + threadNumber + "\nVector after multiply: \n" + out + "\n");
        }
    }


    public static void main(String[] args){
        Threads threads = new Threads();
        System.out.println("The end");
    }
}
