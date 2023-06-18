#include"insertion.h"

class Quick
{
public:
    vector<int> v;
    Quick(vector<int> v_): v(v_){}

    void print_v()
    {
        for (auto vi : v)
            cout << vi << ",";
        cout << endl;
    }

    vector<int> sort()
    {
        quick_sort_partition(0, v.size() - 1);
        return v;
    }

    vector<int> sort_print()
    {
        cout << "Before:" << endl;
        print_v();
        quick_sort_partition_print(0, v.size() - 1);
        return v;
    }

    void quick_sort_partition_print(int front, int rear)
    {
        int leftBase, rightBase, temp;

        if (front >= rear)
            return; // done when there is only 1 element
        else
        {
            cout << front << '-' << rear << " :" << endl;
            leftBase = front + 1;
            rightBase = rear;

            while (true)
            {
                // end when v[leftBase] > v[front] or leftBase > rear
                while (leftBase <= rear && v[leftBase] <= v[front])
                    leftBase++;

                // end when v[rightBase] <= v[front] or rightBase == front
                while (rightBase > front && v[rightBase] > v[front])
                    rightBase--;

                if (leftBase <= rightBase)
                {
                    // swap v[leftBase] and v[rightBase]
                    temp = v[leftBase];
                    v[leftBase] = v[rightBase];
                    v[rightBase] = temp;
                }

                else if (leftBase > rear) // v[front] is the maximum
                {
                    // swap v[front] and v[rear]
                    temp = v[front];
                    v[front] = v[rear];
                    v[rear] = temp;
                    print_v();
                    quick_sort_partition_print(front, rear - 1);
                    return;
                }

                else if (rightBase == front) // v[front] is the minimum
                {
                    print_v();
                    quick_sort_partition_print(front + 1, rear);
                    return;
                }

                else
                    break; // end when leftBase >= rightBase
            }

            // swap v[front] and v[rightBase]
            temp = v[front];
            v[front] = v[rightBase];
            v[rightBase] = temp;
            print_v();
            quick_sort_partition_print(front, rightBase - 1);
            quick_sort_partition_print(rightBase + 1, rear);
        }
    }

    void quick_sort_partition(int front, int rear)
    {
        int leftBase, rightBase, temp;

        if (front >= rear)
            return; // done when there is only 1 element
        else
        {
            leftBase = front + 1;
            rightBase = rear;

            while (true) 
            {
                // end when v[leftBase] > v[front] or leftBase > rear
                while (leftBase <= rear && v[leftBase] <= v[front])
                    leftBase++;

                // end when v[rightBase] <= v[front] or rightBase == front
                while (rightBase > front && v[rightBase] > v[front])
                    rightBase--;

                if (leftBase <= rightBase) 
                {
                    // swap v[leftBase] and v[rightBase]
                    temp = v[leftBase];
                    v[leftBase] = v[rightBase];
                    v[rightBase] = temp;
                }

                else if (leftBase > rear) // v[front] is the maximum
                {
                    // swap v[front] and v[rear]
                    temp = v[front];
                    v[front] = v[rear];
                    v[rear] = temp;
                    quick_sort_partition(front, rear - 1);
                    return;
                }

                else if (rightBase == front) // v[front] is the minimum
                {
                    quick_sort_partition(front + 1, rear);
                    return;
                }

                else 
                    break; // end when leftBase >= rightBase
            }

            // swap v[front] and v[rightBase]
            temp = v[front];
            v[front] = v[rightBase];
            v[rightBase] = temp;
            quick_sort_partition(front, rightBase - 1);
            quick_sort_partition(rightBase + 1, rear);
        }
    }
};