#include<iostream>
#include<stdio.h>
#include<string.h>
#define N 100

using namespace std;

// doubly linked list CLASS
class DLL
{
    public:
        string key;
        string val;
        DLL *next;
        DLL *prev;
};

// Creating an array of DLL to store HASH table
DLL** ind = new DLL*[N];
int count = 0; // to maintain the no of values in a hash table

// the data type for a hash table
class HASH
{
    public:
    string KEY, VALUE; // key value pair
    int INKEY; // the index in which the values has to be sotred in 

    HASH(string KEY, string VALUE) // constructor
    {
        this->KEY = KEY;
        this->VALUE = VALUE;
        this->INKEY = hashcode(KEY); //creating the index value
        cout<<KEY<<" "<<VALUE<<"\n";
        collisions();
    }

    int gen_key(string keey) // simple hash function to generate the index value
    {
        int res = 0;
        for(int i = 0; keey[i] != '\0'; i++)
        {   
            res += int(keey[i]);
        }
        return res;
    }

    int hashcode( string msg) // converting a string to an integer for generation of index value
    {
        int k = gen_key(msg);
        int key = k%N;
        cout<<key<<"\n";
        return key;
    }

    void collisions() // inserting into the hash table and managing collisions, collisions are managed by creating linked lists on the same index
    {
        if(ind[INKEY] != NULL) // if there's already a value at the index then theres a collision
        {
            printf("Collision found \n");

            DLL *temp = ind[INKEY];

            while (temp->next != NULL)
            {
                if(temp->key == KEY)
                {
                    temp->val = VALUE;
                }
                temp = temp->next;
            }
            if(temp->key == KEY)
            {
                    temp->val = VALUE;
            }
            else
            {
            temp->next = new DLL();
            temp->next->key = KEY;
            temp->next->val = VALUE;
            temp->next->next = NULL;
            temp->next->prev = temp;
            temp->next = temp->next;
            count++;
            }
        }
        else
        {
            ind[INKEY] = new DLL();
            ind[INKEY]->key = KEY;
            ind[INKEY]->val = VALUE;
            ind[INKEY]->next = NULL;
            ind[INKEY]->prev = NULL;
            count++;
        }
    }

    friend ostream& operator<<(ostream &out, const HASH &var);

    void DELETE() // since we are using dynamic memeory allocation important to free up all the memory
    {
        DLL* cur , *temp;
        for(int i = 0 ; i < N; i++)
        {
            temp = ind[i];
            while(temp != NULL)
            {
                cur = temp;
                temp = temp->next;
                delete(cur);
            }
        }

        delete(ind);
    }
};

ostream& operator<<(ostream &out, const HASH &var)
{
    int t_count = count;
    out<<"{ ";
    int j = 0;
    for(int i = 0 ; i < N; i++)
    {
        DLL *temp = ind[i];
        while(temp != NULL)
        {
            j = i+1;
            out<<"'"<<temp->key<<"':'"<<temp->val<<"'";
            if(t_count > 1)
            {
                out<<" , ";
            }
            temp = temp->next;
            t_count--;
        }
    }
    out<<" }";
    return out;
}


int main()
{
    HASH n("hey","hello");
    HASH n1("am","why");
    HASH n2("hey","hi");
    HASH n3("huh","what");
    cout<<n3;

    n3.DELETE();
}