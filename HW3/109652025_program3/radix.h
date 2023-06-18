#include"quick.h"
#include <math.h>

struct List
{
    int num = 0;
    List* next = NULL;
};

class Radix
{
public:
    vector<int> v;
    Radix(vector<int> v_) : v(v_) {}

    void print_v()
    {
        for (auto vi : v)
            cout << vi << ",";
        cout << endl;
    }

    vector<int> sort()
    {
        radix_sort();
        return v;
    }

    vector<int> sort_print()
    {
        radix_sort_print();
        return v;
    }

    void radix_sort()
    {
        int i = 1, j, k, remainder;
        int n = v.size();

        while (i <= 100)
        {
            // initialize
            List* bucket = new List[10];
            List** last_node_location = new List * [10];

            for (int j = 0; j < 10; j++)
                last_node_location[j] = &bucket[j];

            for (int j = 0; j < n; j++)
            {
                remainder = (v[j] / i) % 10;
                last_node_location[remainder]->next = new List;
                last_node_location[remainder] = last_node_location[remainder]->next;
                last_node_location[remainder]->num = v[j];
            }

            k = 0; // reset
            for (int j = 0; j < 10; j++)
            {
                List* iterator = &bucket[j];
                while (iterator->next != NULL)
                {
                    iterator = iterator->next;
                    v[k++] = iterator->num;
                }
            }

            i *= 10;
        }
    }

    void radix_sort_print()
    {
        int i = 1, j, k, remainder;
        int n = v.size();

        while (i <= 100)
        {
            // initialize
            List* bucket = new List[10];
            List** last_node_location = new List * [10];

            for (int j = 0; j < 10; j++)
                last_node_location[j] = &bucket[j];

            for (int j = 0; j < n; j++)
            {
                remainder = (v[j] / i) % 10;
                last_node_location[remainder]->next = new List;
                last_node_location[remainder] = last_node_location[remainder]->next;
                last_node_location[remainder]->num = v[j];
            }

            if (i == 1)
                cout << "First-pass:" << endl;
            else if (i == 10)
                cout << "Second-pass:" << endl;
            else // i == 100
                cout << "Third-pass:" << endl;

            k = 0; // reset
            for (int j = 0; j < 10; j++)
            {
                cout << j << " |";
                List* iterator = &bucket[j];
                while (iterator->next != NULL)
                {
                    iterator = iterator->next;
                    v[k++] = iterator->num;
                    cout << " --> " << iterator->num;
                }
                cout << endl;
            }
            
            cout << "resulting chain : ";
            print_v();
            cout << endl;
            i *= 10;
        }
    }
};