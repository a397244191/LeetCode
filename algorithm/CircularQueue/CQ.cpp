class MyCircularQueue {
public:
    int f,r,size;
    bool full;
    int* arr;
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        arr = new int[k];
        f = 0;
        r = 0;
        size = k;
        full = false;
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if(isFull()) return false;
        arr[r] = value;
        r = r == size-1 ? 0 : r+1;
        full = (r == f);
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if(isEmpty()) return false;
        f = f == size-1 ? 0 : f+1;
        full = false;
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        if(isEmpty()) return -1;
        else return arr[f];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        if(isEmpty()) return -1;
        else {
            int a = r == 0 ? size-1 : r-1;
            return arr[a];
        }
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return ((full) ? false : f == r);
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return full;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue obj = new MyCircularQueue(k);
 * bool param_1 = obj.enQueue(value);
 * bool param_2 = obj.deQueue();
 * int param_3 = obj.Front();
 * int param_4 = obj.Rear();
 * bool param_5 = obj.isEmpty();
 * bool param_6 = obj.isFull();
 */