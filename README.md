# CS4532 Concurrent Programming - Take-Home Assignments

This repository contains lab assignments for the CS4532 Concurrent Programming course, focusing on parallel programming with Pthreads, mutexes, and semaphores.

## Lab 1: Linked List Implementation with Pthreads

In this lab, you will implement a linked list as:

1. **Serial Program**  
   - A standard linked list implementation without concurrency.

2. **Parallel Program with Mutex Lock**  
   - A parallel linked list implementation using the Pthreads library, with a single mutex protecting the entire linked list.

3. **Parallel Program with Read-Write Locks**  
   - A parallel linked list implementation using the Pthreads library, utilizing read-write locks for enhanced concurrency.

### Objectives
- Gain hands-on experience with Pthreads and parallel program design.
- Understand synchronization mechanisms like mutexes and read-write locks.

## Lab 2: Bus Rider Problem

In this lab, you will implement the Bus Rider Problem using mutexes and semaphores. This exercise demonstrates the use of synchronization primitives to manage concurrent access in a real-world scenario.

### Objectives
- Understand the application of mutexes and semaphores in practical concurrent programming problems.
- Learn how to handle thread synchronization in a shared resource environment.

## Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/RaviniKuruppu/Concurrent-Programming.git
