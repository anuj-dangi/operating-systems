#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_FRAME 3

typedef struct Frame
{
    int page_no;
    bool valid = false;
} F;

typedef struct Page
{
    int frame_no;
    bool valid = false;
} P;

class Node
{   
public: 
    int data;
    Node* prev;
    Node* next;

    Node(int data)
    {
        this->data = data;
        prev = next = NULL;
    }
};

class Stack
{
public: 
    Node* front;
    Node* top;
    int size;
    int capacity;

    Stack(int capacity)
    {
        front = top = NULL;
        this->capacity = capacity;
        this->size = 0;
    }

    int insert(int data)
    {
        // If the page is already in stack, move it to top (no page fault)
        if (contains(data)) {
            used(data);
            return -1;
        }

        Node* node = new Node(data);

        // If there's space
        if(size < capacity)
        {
            if (size == 0)
            {
                front = top = node;
            }
            else
            {
                top->next = node;
                node->prev = top;
                top = node;
            }
            size++;
            // print();
            return -1;
        }

        // Stack is full: evict front (LRU)
        int evicted_page = front->data;
        Node* old_front = front;
        front = front->next;
        if (front) front->prev = NULL;
        delete old_front;
        size--; // decrease temporarily

        // Add new node to top
        top->next = node;
        node->prev = top;
        top = node;
        size++;

        // print();
        return evicted_page;
    }

    void used(int data)
    {
        Node* temp = front;

        while (temp != NULL && temp->data != data)
        {
            temp = temp->next;
        }

        if (temp == NULL || temp == top)
            return; // Not found or already most recently used

        // Remove from current position
        if (temp->prev)
            temp->prev->next = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;

        if (temp == front)
            front = temp->next;

        // Move to top
        temp->prev = top;
        temp->next = NULL;
        top->next = temp;
        top = temp;

        // print();
    }

    bool contains(int data)
    {
        Node* temp = front;
        while (temp)
        {
            if (temp->data == data)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void print()
    {
        Node* temp = front;
        cout << "LRU Stack: ";
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};


void fifo(vector<int> page_no, vector<F> frames, vector<P> page_table)
{
    cout << "-----FIRST IN FIRST OUT-----\n\n";
    queue<int> q;

    int total_pagefault = 0;

    for (int i = 0; i < page_no.size(); i++)
    {
        if (page_table[page_no[i]].valid)
        {
            cout << "Page found in Frame\t";
            cout << "Page no: " << page_no[i] << " -> " << "Frame no: " << page_table[page_no[i]].frame_no << endl;
        }
        else
        {
            bool found = false;
            for (int j = 0; j < MAX_FRAME; j++)
            {
                if (!frames[j].valid)
                {
                    frames[j].page_no = page_no[i];
                    frames[j].valid = true;

                    page_table[page_no[i]].frame_no = j;
                    page_table[page_no[i]].valid = true;
                    cout << "Page inserted in Frame\tPage no: " << page_no[i] << " -> " << "Frame no: " << page_table[page_no[i]].frame_no << endl;
                    found = true;
                    q.push(j);
                    break;
                }
            }

            if (!found)
            {
                cout << "Page fault\t";
                total_pagefault++;

                int frame_no = q.front();
                q.pop();

                page_table[frames[frame_no].page_no].valid = false;
                page_table[page_no[i]].frame_no = frame_no;
                page_table[page_no[i]].valid = true;

                frames[frame_no].page_no = page_no[i];

                q.push(frame_no);

                cout << "Page no: " << page_no[i] << " -> " << "Frame no: " << page_table[page_no[i]].frame_no << endl;
            }
        }
    }

    cout << "\nTotal Page fault : " << total_pagefault << endl;
}

void lru(vector<int> page_no, vector<F> frames, vector<P> page_table)
{
    cout << "\n\n-----LEAST RECENTLY USED-----\n\n";
    Stack s(MAX_FRAME);

    int total_pagefault = 0;

    for (int i = 0; i < page_no.size(); i++)
    {
        if (page_table[page_no[i]].valid)
        {
            cout << "Page found in Frame\t";
            cout << "Page no: " << page_no[i] << " -> " << "Frame no: " << page_table[page_no[i]].frame_no << endl;
            s.used(page_no[i]);
        }
        else
        {
            bool found = false;
            for (int j = 0; j < MAX_FRAME; j++)
            {
                if (!frames[j].valid)
                {
                    frames[j].page_no = page_no[i];
                    frames[j].valid = true;

                    page_table[page_no[i]].frame_no = j;
                    page_table[page_no[i]].valid = true;
                    cout << "Page inserted in Frame\tPage no: " << page_no[i] << " -> " << "Frame no: " << page_table[page_no[i]].frame_no << endl;
                    found = true;
                    s.insert(page_no[i]);
                    break;
                }
            }

            if (!found)
            {
                cout << "Page fault\t";
                total_pagefault++;

                int page_data = s.insert(page_no[i]);
                int frame_no;
                
                for(int k=0;k<MAX_FRAME;k++)
                {
                    if(frames[k].page_no == page_data)
                    {
                        frame_no = k;
                    }
                }

                page_table[frames[frame_no].page_no].valid = false;
                page_table[page_no[i]].frame_no = frame_no;
                page_table[page_no[i]].valid = true;

                frames[frame_no].page_no = page_no[i];

                cout << "Page no: " << page_no[i] << " -> " << "Frame no: " << page_table[page_no[i]].frame_no << endl;
            }
        }
    }

    cout << "\nTotal Page fault : " << total_pagefault << endl;
}

void optimal(vector<int> page_no, vector<F> frames, vector<P> page_table)
{
    cout << "\n\n-----OPTIMAL-----\n\n";
    int total_pagefault = 0;

    for(int i=0;i<page_no.size();i++)   
    {
        if(page_table[page_no[i]].valid)
        {
            cout << "Page found in Frame\t";
            cout << "Page no: " << page_no[i] << " -> " << "Frame no: "  << page_table[page_no[i]].frame_no << endl;
        }
        else
        {
            bool found=false;
            for(int j=0;j<MAX_FRAME;j++)
            {
                if(!frames[j].valid)
                {
                    frames[j].page_no = page_no[i];
                    frames[j].valid = true;

                    page_table[page_no[i]].frame_no = j;
                    page_table[page_no[i]].valid = true;
                    cout << "Page inserted in Frame\tPage no: " << page_no[i] << " -> " << "Frame no: "  << page_table[page_no[i]].frame_no << endl;
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                cout << "Page fault\t";
                total_pagefault++;

                int victim_index = i;
                int frame_no = 0;
                //using optimal policie
                for(int j=0;j<MAX_FRAME;j++)
                {
                    for(int k=i+1;k<page_no.size();k++)
                    {
                        if(frames[j].page_no == page_no[k] && victim_index < k)
                        {
                            victim_index = k;
                            frame_no = j;
                        }
                    }
                }

                page_table[page_no[victim_index]].valid = false;
                page_table[page_no[i]].frame_no = frame_no;
                page_table[page_no[i]].valid = true;

                frames[frame_no].page_no = page_no[i];

                cout << page_no[i] << " -> " << "Frame no: "  << page_table[page_no[i]].frame_no << endl;
            }
        }
    }

    cout << "\nTotal Page fault : " << total_pagefault << endl;
}

int main()
{
    vector<int> reference_string = {0, 1, 2, 0, 3, 4, 1, 0, 3, 2, 4, 5, 1, 2, 3};
    vector<F> frames(MAX_FRAME);
    vector<P> page_table(6);

    fifo(reference_string, frames, page_table);
    lru(reference_string, frames, page_table);
    optimal(reference_string, frames, page_table);
}