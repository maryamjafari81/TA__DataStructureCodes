

#include <iostream>

using namespace std;

const int MAX_SIZE = 100;

class MinHeap {
private:
    int heap[MAX_SIZE];
    int size;

    void heapifyUp(int index) {
        if (index == 0) {
            return;
        }

        int parentIndex = (index - 1) / 2;
        if (heap[parentIndex] > heap[index]) {
            swap(heap[parentIndex], heap[index]);
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallest = index;

        if (leftChildIndex < size && heap[leftChildIndex] < heap[smallest]) {
            smallest = leftChildIndex;
        }
        if (rightChildIndex < size && heap[rightChildIndex] < heap[smallest]) {
            smallest = rightChildIndex;
        }

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap() : size(0) {}

    void enqueue(int value) {
        if (size == MAX_SIZE) {
            cout << "Queue is full." << endl;
            return;
        }

        heap[size] = value;
        heapifyUp(size);
        size++;
    }

    void dequeue() {
        if (size == 0) {
            cout << "Queue is empty." << endl;
            return;
        }

        swap(heap[0], heap[size - 1]);
        size--;
        heapifyDown(0);
    }

    void displayQueue() {
        if (size == 0) {
            cout << "Queue is empty." << endl;
            return;
        }

        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MinHeap queue;
    int choice, value;

    while (true) {
        cout << "Choose an operation:" << endl;
        cout << "1. Enqueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Display queue" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to enqueue: ";
                cin >> value;
                queue.enqueue(value);
                break;
            case 2:
                queue.dequeue();
                break;
            case 3:
                queue.displayQueue();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }

    return 0;
}

