import java.util.Random;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class BusRiderProblem {
    private static Semaphore mutex = new Semaphore(1); // Protect shared variables
    private static Semaphore bus = new Semaphore(0);   // Signal for the bus arrival
    private static Semaphore boarded = new Semaphore(0);  // Signal for riders to board
    private static int waiting = 0;     // keeps track of how many riders are waiting for the bus
    private static final int BUS_CAPACITY = 50; // Maximum capacity of the bus

    private static Random random = new Random();
    private static int bus_Delay = 1200; // Each bus arrives after 20 minutes
    private static int rider_Delay = 30; // Each rider arrives after 30 seconds

    public static void main(String[] args) {
        Thread riderArrivesThread = new Thread(new RiderArrives());
        riderArrivesThread.start();

        Thread busArrivesThread = new Thread(new BusArrives());
        busArrivesThread.start();
    }

    static long calculateRandomDelay(int mean) {
        // Generate a random delay between 0 and 2 * mean
        return (long) (random.nextDouble() * 2 * mean);
    }

    static class RiderArrives implements Runnable {
        @Override
        public void run() {
            while (true) {
                Thread riderThread = new Thread(new Rider());
                riderThread.start();
                try {
                    // Thread sleep until a new rider arrives
                    Thread.sleep(calculateRandomDelay(rider_Delay));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static class BusArrives implements Runnable {
        @Override
        public void run() {
            while (true) {
                Thread busThread = new Thread(new Bus());
                busThread.start();
                try {
                    // Thread sleep until the next bus arrives
                    Thread.sleep(calculateRandomDelay(bus_Delay));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static class Bus implements Runnable {
        @Override
        public void run() {
            try {
                mutex.acquire();   // The Bus acquires the mutex to start boarding
                int n = Math.min(waiting, BUS_CAPACITY);  // get the minimum to prevent more than 50 riders from boarding into the bus
                arrive(n);
                for (int i = 0; i < n; i++) {
                    bus.release();
                    boarded.acquire();
                }
                waiting = Math.max(waiting - BUS_CAPACITY, 0);
                mutex.release();  // The Bus releases the mutex after boarding is done
                depart();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        private void arrive(int n) {
            System.out.println("Bus arrived when " + waiting + " riders waiting and it gets " + n + " riders on board.");
        }

        private void depart() {
            System.out.println("Bus departed with " + waiting + " riders remaining.\n");
        }
    }

    static class Rider implements Runnable {
        // Static counter to generate unique incremental IDs
        private static final AtomicInteger idCounter = new AtomicInteger(1);
        private final int riderId; // Unique ID for each rider

        Rider() {
            this.riderId = idCounter.getAndIncrement();
        }

        @Override
        public void run() {
            try {
                mutex.acquire();
                waiting++;
                waitForTheBus();
                mutex.release();
                bus.acquire();
                board();
                boarded.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        private void waitForTheBus() {
        //    System.out.println("Rider (ID:"+ this.riderId + ") waiting." + " Total riders waiting: " + waiting);
        }

        private void board() {
        //    System.out.println("Rider (ID:"+ this.riderId + ") boarded");
        }
    }
}
