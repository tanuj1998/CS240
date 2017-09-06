#include "DLList.h"
#include <stdio.h>

/**
 * @brief      Constructor for the DLList.
 */
DLList::DLList()
{
	head=new DLNode();
	head->next=head;
	head->prev=head;
}

/**
 * @brief      Destructor for the DLList.
 */
DLList::~DLList()
{
	DLNode *a;
	a =head->next;
	
	while(a != head){
	
	DLNode *b;
	b =a;
	a = a->next;

	delete b;}

	delete a;
}

/**
 * @brief      Print the DLList line by line.
 */
void DLList::print()
{
	DLNode *a;
	a =head->next;
	
	while(a != head){
	   
	   printf("%d\n",a->data);
	   a=a->next;}
}

/**
 * @brief      Sort and print the list.
 * 
 * This function should sort and print the list.
 * Note: the actual list is NOT to be modified.
 * In other words, it should only *print* in a
 * sorted order, not actually sort the list.
 */
void DLList::printSorted()
{
	int length;
	length = 0;

    DLNode *a;
    a = head->next;

    while(a!=head){
    
    ++length;
    a = a->next;
    }

    int *array;
    array =new int[length];

    int x;
    x = 0;

    a = head->next;
    while(a != head)
    {
        array[x] = a->data;
         ++x;
         a = a->next;
    }
    for(x = 0; x < length; x = (x+1))
    {
        for(int y = (x+1); y < length; y = (y+1))
        {
            if((array[y]) < (array[x]))
            {
                int temp;
		temp = array[x];
                array[x] = array[y];
                array[y] = temp;
            }
        }
    }
    for(int c = 0;c < length; c++)
    printf("%d\n", array[c]);
}

/**
 * @brief      Add to the front of the list.
 *
 * @param[in]  data  Item to add to front.
 */
void DLList::insertFront(int data)
{
	DLNode *b;
	b =new DLNode();
	b->data = data;
	b->next = head->next;
	b->prev = head;

	b->next->prev = b;
	b->prev->next = b;
}
void DLList::insert(int data)
{
	DLNode *a;
	a = new DLNode();

	a->data = data;
	a->next = head;

	a->prev = head->prev;
	head->prev->next = a;

	head->prev = a;
}

/**
 * @brief      Removes & stores the last element.
 *
 * The last element is removed and stored in the
 * referenced variable data.
 * 
 * @param      data  Thing in which we are storing the data.
 *
 * @return     True upon successful removal.
 */
bool DLList::removeLast(int & data)
{
	if(head->next == head){
	return false;
        }
        data = head->prev->data;

	DLNode *a;
	a =head->prev->prev;

	a->next=head;
	head->prev=a;

	return true;
}

/**
 * @brief      Difference of two lists.
 *
 * @param      list  Subtrahend.
 *
 * @return     Returns a pointer to the difference.
 */
DLList * DLList::difference(DLList & list)
{
	DLList * diff = new DLList();
	
	DLNode *a;
	a = head->next;
	
	while(a != head){

        DLNode *b;
	b = list.head->next;

       int c;
       c =0;
       while(b != list.head)
       {    
            if(b->data == a->data)
           c +=1;
            	b = b->next;
         }
        if(c==0)
    	diff->insertFront(a->data);
      	a = a->next;
	    }
	return diff;
}

/**
 * @brief      Returns a sublist of items in a range.
 *
 * @param[in]  start  First index.
 * @param[in]  end    Second index.
 *
 * @return     Elements between first and second index.
 */
DLList * DLList::getRange(int start, int end)
{
	DLList * range = new DLList();
	
	DLNode *a;
	a =head->next;
	
	while(a != head){
	if(0 < start){
	
	--start;
	--end;
	
	}

	if((start == 0) && (0 < end)){

	range->insertFront(a->data);
	--end;}

	a = a->next;
	}
	return range;
}

/**
 * @brief      Intersection of this list and another list.
 *
 * @param      list  The other list.
 *
 * @return     Elements list shares with this one.
 */
DLList * DLList::intersection(DLList & list)
{
	DLList * inter = new DLList();
	
	DLNode *x;
	x = head->next;

	while(x != head)
{
	    int a;
	    a = 0;

	    DLNode *y;
	    y =list.head->next;

	    while(y != list.head){

	    if(y->data == x->data)
	    
	    a += 1;
	    y = y->next;
	    }
	    if(a!=0)
	    inter->insert(x->data);
	    x = x->next;
	}
	return  inter;
}

/**
 * @brief      Removes nodes in the start-end range.
 *
 * @param[in]  start  First node.
 * @param[in]  end    Second node.
 */
void DLList::removeRange(int start, int end)
{
	DLNode *a;
	a = head->next;
	
	while(0 < start){
	
	--start;
	a = a->next;
	}

	DLNode *b;
	b = head->next;

	while(0 < end)
	{

	--end;
	b = b->next;
	}

	a->next=b;
	b->prev=a;
}

