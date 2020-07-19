/*
 * @Author: Runsheng WU 
 * @Date: 2020-07-17 09:56:01 
 * @Last Modified by: Runsheng WU
 * @Last Modified time: 2020-07-17 16:43:40
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int num;
    struct Node *next;
}JoseNode;

/**
 * CreateNode initialize one node with value i
 * @param i value of node 
  */
JoseNode *CreateNode(int i);

/**
 * JoseCircle_Init  Create circle LinkNode 
 * @param head head of JoseCircle
 * @param Jnew node to be inserted
 * @param i value of node inserted
  */
JoseNode *JoseCircle_Init(JoseNode *head, JoseNode *Jnew, int i);

/**
 * Josephus: Game
 * @param n number of node
 * @param m position of the first node of game
 * @param k intervalle
  */
void Josephus(const unsigned int n, const unsigned int m, const unsigned int k);

int main(int argc, char **argv)
{
    int n = 50, m = 4, k = 6;
    Josephus(n, m, k);
    return 0;
}

// Create one node
JoseNode *CreateNode(int i)
{
    JoseNode *j;
    j = (JoseNode*)malloc(sizeof(JoseNode));
    j->num = i;
    j->next = NULL;
    return j;
}

// Create LinkNode circle
JoseNode *JoseCircle_Init(JoseNode *head, JoseNode *Jnew, int i)
{
    JoseNode *Jpb = head;
    Jnew = CreateNode(i);
    if (head == NULL)
    {     
        head = Jnew;
        head->next = head;
    }
    else
    {
        while(Jpb->next != head)
            Jpb = Jpb->next;
        Jpb->next = Jnew;
        Jnew->next = head;
    }
    return head;      
}

void Josephus(const unsigned int n, const unsigned int m, const unsigned int k)
{
    JoseNode *Jose_head = NULL, *JoseN = NULL, *j = NULL, *p = NULL;
    int i = 0;
    if(n == 1)
        return;
    for (int i = 0; i < n; i++)
        Jose_head = JoseCircle_Init(Jose_head, JoseN, i+1);
    j = Jose_head;
    // find the mth node
    for (i = 0;i < (m - 1);i++)
        j = Jose_head->next;

    // Game start from the mth node
    printf("Push ordre in case n = %d, m = %d, k = %d is:\n", n, m, k);
    Jose_head = j;
    while(Jose_head->next != Jose_head)
    {
        while(i < (k - 2))              // find the k-1 node
        {
            j = Jose_head->next;
            i++;
        }
        p = j->next;                    // get the kth node which should be pushed out 
        printf("%d->", p->num);         // printf kth node
        j->next = p->next;              // (k-1)th node->next = (k+1)th node
        Jose_head = j->next;
        j = Jose_head;            // name (k+1)th node as new head;
        i = 0;                          // restart circle   
    }
    printf("%d\n", Jose_head->num);     // push the last node
    printf("==============================================================\n");
}