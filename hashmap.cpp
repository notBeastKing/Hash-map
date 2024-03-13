#include<iostream>
#include<stdio.h>
#include<string.h>
#define N 100

using namespace std;

class DLL
{
    public:
        string key;
        string val;
        DLL *next;
        DLL *prev;
};

DLL** ind = new DLL*[N];
int count = 0;

class HASH
{
    public:
    string KEY, VALUE;
    int INKEY;

    HASH(string KEY, string VALUE)
    {
        this->KEY = KEY;
        this->VALUE = VALUE; //VALUE
        this->INKEY = hashcode(KEY); //ind KEY
        cout<<KEY<<" "<<VALUE<<"\n";
        collisions();
    }

    int gen_key(string keey)
    {
        int res = 0;
        for(int i = 0; keey[i] != '\0'; i++)
        {   
            res += int(keey[i]);
        }
        return res;
    }

    int hashcode( string msg)
    {
        int k = gen_key(msg);
        int key = k%N;
        cout<<key<<"\n";
        return key;
    }

    void collisions()
    {
        if(ind[INKEY] != NULL)
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

    void DELETE()
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