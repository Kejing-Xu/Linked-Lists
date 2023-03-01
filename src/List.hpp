/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode *temp = head_, *nextPoint = NULL;
  while(temp!=NULL){
    nextPoint=temp->next;
    delete temp;
    length_--;
    temp=nextPoint;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (head_ != NULL) {
    head_ -> prev = newNode;
    newNode -> next = head_;
    head_ =newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
    head_ = newNode;
  }
  

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (head_ != NULL) {
    tail_ -> next = newNode;
    newNode -> prev = tail_;
    tail_ =newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
    head_ = newNode;
  }
  length_++;
}


/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */


template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  for (int i = 0; i < splitPoint; i++) {
    curr = curr->next;
  }
  if(curr==NULL)return NULL;
  if (curr->prev != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode *temp=head_;
  while(temp!=NULL&&temp->next!=NULL&&temp->next->next!=NULL){
    ListNode *newNode=temp->next->next->next;
    if(temp==head_){
      head_=temp->next;
      head_->prev=NULL;
      head_->next->next=temp;
      temp->prev=head_->next;
      temp->next=newNode;
      if(newNode!=NULL)
      newNode->prev=temp;
      else
      tail_=temp;
    }
    else{
      ListNode *head1=temp->next;
      head1->prev=temp->prev;
      temp->prev->next=head1;
      head1->next->next=temp;
      temp->prev=head1->next;
      temp->next=newNode;
      if(newNode!=NULL)
      newNode->prev=temp;
      else
      tail_=temp;
    }
    temp=temp->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  ListNode* startP=startPoint;
  ListNode* endP=endPoint;
  if(startP==endP)
  return;
  if(startP->prev!=NULL)
  startP->prev->next=endP;
  else
  head_=endP;
  ListNode *temp=endP;
  ListNode *newBegin=endP->next;
  ListNode *prevNode=NULL;
  while(temp!=startP){
    if(temp==endP){
      temp->next=temp->prev;
      temp->prev=startP->prev;
    }
    else{
      temp->next=temp->prev;
      temp->prev=prevNode;
    }
    prevNode=temp;
    temp=temp->next;
  }
  temp->prev=prevNode;
  temp->next=newBegin;
  if(newBegin!=NULL)
  newBegin->prev=temp;
  else
  tail_=temp;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode *start=head_;
  ListNode *end=start;
  while(start!=NULL){
    for(int i=0;i<n-1;i++){
    if(end->next==NULL)
    break;
    end=end->next;
    }
    reverse(start,end);
    start=start->next;
    end=start;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first==NULL)return second;
  if(second==NULL)return first;
  ListNode *newHead=first;
  ListNode *temp1=first, *temp2=second, *newtemp2=second;
    if(temp2->data<newHead->data){
      while(temp2->next!=NULL&&temp2->next->data<newHead->data)
        temp2=temp2->next;
      newtemp2=temp2->next;
      newHead=second;
      temp2->next=first;
      first->prev=temp2;
      if(newtemp2==NULL)return newHead;
      else
      temp2=newtemp2;
      }
    while(newtemp2!=NULL){
      temp2=newtemp2;
    while(temp1->next!=NULL&&temp1->next->data<temp2->data){
      temp1=temp1->next;
    }
    if(temp1->next==NULL){
      temp1->next=temp2;
      temp2->prev=temp1;
      return newHead;
    }
    newtemp2=temp2->next;
    temp2->prev=temp1;
    temp2->next=temp1->next;
    temp1->next=temp2;
    temp2->next->prev=temp2;
    }
    if(newtemp2==NULL){
      temp1->next=temp2;
      temp2->next=temp1;
    }
  return newHead;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength<2) return start;
  ListNode *head1=start;
  ListNode *head2=split(start,chainLength/2);
  head1=mergesort(head1,chainLength/2);
  head2=mergesort(head2,chainLength-chainLength/2);
  return merge(head1,head2);
}
