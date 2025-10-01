#include "VectorStore.h"

// ----------------- Quick sort implementation -----------------

// Utility functions
template <class T>
void swapInArray(T *arr, int i, int j)
{
    if (i != j)
    { // Avoid self-assignment
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

template <class T>
void quickSort(T *arr, int size)
{
    if (size <= 1)
        return;

    T pivot = arr[0];
    int left = 1;
    int right = size - 1;

    // Partitioning phase
    while (left <= right)
    {
        // Find element from left that should be on right side of pivot
        while (left <= right && arr[left] < pivot)
            left++;

        // Find element from right that should be on left side of pivot
        while (left <= right && arr[right] >= pivot)
            right--;

        // If we found elements to swap
        if (left < right)
        {
            swapInArray(arr, left, right);
            left++;
            right--;
        }
    }

    // Place pivot in correct position
    swapInArray(arr, 0, right);

    // Recursively sort left and right subarrays
    quickSort(arr, right);
    quickSort(arr + right + 1, size - right - 1);
}

// ----------------- ArrayList Implementation -----------------

template <class T>
ArrayList<T>::ArrayList(int initCapacity)
{
    // TODO
    data = new T[initCapacity];
    count = 0;
    capacity = initCapacity;
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T> &other)
{
    // TODO
    data = new T[other.capacity];
    count = other.getCount();
    capacity = other.getCapacity();
    for (int i = 0; i < count; i++)
        *(data + i) = *(other.getData() + i);
}

template <class T>
ArrayList<T>::~ArrayList()
{
    // TODO
    delete[] data;
}

template <class T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &other)
{
    if (this != &other)
    {
        delete[] data;
        capacity = other.capacity;
        count = other.count;
        data = new T[capacity];
        for (int i = 0; i < count; i++)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// TODO: implement other methods of ArrayList
template <class T>
void ArrayList<T>::ensureCapacity(int cap)
{
    if (cap > capacity)
    {
        capacity = cap * 2;
        T *newData = new T[capacity];
        for (int i = 0; i < count; i++)
            *(newData + i) = *(data + i);
        data = newData;
    }
}

template <class T>
void ArrayList<T>::add(T e)
{
    ensureCapacity(count + 1);
    *(data + count++) = e;
}
template <class T>
void ArrayList<T>::add(int index, T e)
{
    ensureCapacity(count + 1);
    if (!count)
    {
        add(e);
        return;
    }
    if (index < 0 || index > count)
    {
        throw out_of_range("Index is invalid!");
        return;
    }
    else if (index == count)
    {
        add(e);
        return;
    }
    else
    {
        for (int i = count; i > index; i--)
            *(data + i) = *(data + i - 1);
        *(data + index) = e;
    }
    count++;
}
template <class T>
bool ArrayList<T>::isValidIndex(int index) const { return (index >= 0 && index < count); }

template <class T>
T ArrayList<T>::removeAt(int index)
{
    if (isValidIndex(index))
    {
        T output = *(data + index);
        for (int i = index; i < count; i++)
            *(data + i) = *(data + i + 1);
        count--;
        return output;
    }
    else
        throw out_of_range("Index is invalid!");
    // return (T)-1;
}
template <class T>
bool ArrayList<T>::empty() const { return !count; }
template <class T>
int ArrayList<T>::size() const { return count; }
template <class T>
void ArrayList<T>::clear()
{
    delete[] data;
    capacity = 10;
    data = new T[capacity];
    capacity = 10;
    count = 0;
}
template <class T>
T &ArrayList<T>::get(int index) const
{
    if (isValidIndex(index))
    {
        return *(data + index);
    }
    throw out_of_range("Index is invalid!");
}
template <class T>
void ArrayList<T>::set(int index, T e)
{
    if (isValidIndex(index))
        *(data + index) = e;
    else
        throw out_of_range("Index is invalid!");
}
template <class T>
int ArrayList<T>::indexOf(T item) const
{
    for (int i = 0; i < count; i++)
    {
        if (*(data + i) == item)
            return i;
    }
    return -1;
}
template <class T>
bool ArrayList<T>::contains(T item) const
{
    for (int i = 0; i < count; i++)
    {
        if (*(data + i) == item)
            return true;
    }
    return false;
}
template <class T>
int ArrayList<T>::getCount() const { return count; }
template <class T>
T *ArrayList<T>::getData() const { return data; }
template <class T>
int ArrayList<T>::getCapacity() const { return capacity; }

template <class T>
string ArrayList<T>::toString(string (*item2str)(T &)) const
{
    string output;
    if (item2str)
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            T &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }

    return output;
}

template <>
string ArrayList<int>::toString(string (*item2str)(int &)) const
{
    if (count == 0)
        return "[]";
    string output;
    if (item2str)
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            int &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }
    else
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            int &number = get(i);
            string str = std::to_string(number);
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }

    return output;
}

template <>
string ArrayList<float>::toString(string (*item2str)(float &)) const
{
    if (count == 0)
        return "[]";
    string output;
    if (item2str)
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            float &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }
    else
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            float &number = get(i);
            string str = std::to_string(number);
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }

    return output;
}

template <>
string ArrayList<string>::toString(string (*item2str)(string &)) const
{
    if (count == 0)
        return "[]";
    string output;
    if (item2str)
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            string &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }
    else
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            string &number = get(i);
            string str = number;
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }

    return output;
}

template <>
string ArrayList<char>::toString(string (*item2str)(char &)) const
{
    if (count == 0)
        return "[]";
    string output;
    if (item2str)
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            char &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }
    else
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            char &number = get(i);
            string str = std::to_string(number);
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }

    return output;
}

template <>
string ArrayList<double>::toString(string (*item2str)(double &)) const
{
    if (count == 0)
        return "[]";
    string output;
    if (item2str)
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            double &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }
    else
    {
        output = "[";

        for (int i = 0; i < count; i++)
        {
            double &number = get(i);
            string str = std::to_string(number);
            if (i != count - 1)
                output = output + str + ", ";
            else
                output = output + str + "]";
        }
    }

    return output;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::begin()
{
    return ArrayList<T>::Iterator(this, 0);
}
template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::end()
{
    return ArrayList<T>::Iterator(this, count);
}
// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T> *pList, int index)
{
    // TODO
    if (index < 0 || index > pList->getCount())
        throw out_of_range("Index is invalid!");
    this->pList = pList;
    cursor = index;
}

// TODO: implement other methods of ArrayList::Iterator
template <class T>
int ArrayList<T>::Iterator::getCursor() const
{
    return cursor;
}
template <class T>
bool ArrayList<T>::Iterator::isValidCursor(int cursor) const
{
    return !(cursor < 0 || cursor > pList->getCount());
}
template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator=(const ArrayList<T>::Iterator &other)
{
    cursor = other.cursor;
    pList = other.pList;
    return *this;
}
template <class T>
T &ArrayList<T>::Iterator::operator*()
{
    if (cursor == pList->getCount())
        throw;
    if (!ArrayList<T>::Iterator::isValidCursor(cursor))
        throw out_of_range("Iterator is out of range!");
    T &output = *(pList->getData() + cursor);
    // output = *(pList + cursor);
    return output;
}

template <class T>
bool ArrayList<T>::Iterator::operator!=(const ArrayList<T>::Iterator &other) const
{
    return (this->pList->getData() != other.pList->getData() || this->cursor != other.getCursor());
}

template <class T>
ArrayList<T> *ArrayList<T>::Iterator::getPList() const
{
    return pList;
}
template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator++()
{
    if (cursor == pList->getCount())
        throw out_of_range("Iterator cannot advance past end!");
    cursor++;
    return *this;
}
template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++(int)
{
    if (cursor == pList->getCount())
        throw out_of_range("Iterator cannot advance past end!");
    Iterator temp = *this;

    cursor++;
    // ++(*this);
    return temp;
}
template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator--()
{
    if (cursor == 0)
        throw out_of_range("Iterator cannot move before begin!");
    cursor--;
    return *this;
}
template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--(int)
{
    if (cursor == 0)
        throw out_of_range("Iterator cannot move before begin!");
    Iterator temp = *this;
    cursor--;
    return temp;
}

// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList()
{
    // TODO
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    // TODO
    clear();
}

// TODO: implement other methods of SinglyLinkedList
template <class T>
void SinglyLinkedList<T>::add(T e)
{
    Node *newNode = new Node(e);
    if (!count)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}
template <class T>
void SinglyLinkedList<T>::add(int index, T e)
{
    if (!(index >= 0 && index <= count))
        throw out_of_range("Index is invalid!");
    if (index == count)
    {
        add(e);
        return;
    }
    if (index == 0)
    {
        Node *insertData = new Node(e);
        insertData->next = head;
        head = insertData;
        count++;
        return;
    }
    Node *temp = head;
    for (int i = 0; i < index - 1; i++)
    {
        temp = temp->next;
    }
    Node *insertData = new Node(e);
    insertData->next = temp->next;
    temp->next = insertData;
    count++;
}
template <class T>
typename SinglyLinkedList<T>::Node *SinglyLinkedList<T>::getHead() const
{
    return head;
}
template <class T>
typename SinglyLinkedList<T>::Node *SinglyLinkedList<T>::getTail() const
{
    return tail;
}
template <class T>
int SinglyLinkedList<T>::getCount() const
{
    return count;
}
template <class T>
T SinglyLinkedList<T>::removeHead()
{
    if (count == 0)
    {
        throw out_of_range("Cannot remove from empty list!");
    }

    T output = head->data;
    Node *temp = head;

    if (count == 1)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        head = head->next;
    }

    delete temp;
    count--;
    return output;
}
template <class T>
T SinglyLinkedList<T>::removeTail()
{
    if (count == 0)
    {
        throw out_of_range("Cannot remove from empty list!");
    }

    if (count == 1)
    {
        T output = tail->data;
        delete tail;
        head = nullptr;
        tail = nullptr;
        count--;
        return output;
    }

    T output = tail->data;

    // Find the second-to-last node
    Node *temp = head;
    for (int i = 0; i < count - 2; i++)
    {
        temp = temp->next;
    }

    // Delete the tail and update pointers
    delete tail;
    tail = temp;
    tail->next = nullptr;
    count--;

    return output;
}
template <class T>
T SinglyLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index >= count)
        throw out_of_range("Index is invalid!");
    if (count == 1)
    {
        Node *temp = head;
        T output = temp->data;
        head = nullptr;
        tail = nullptr;
        delete temp;
        count--;
        return output;
    }
    T output;
    if (index == 0)
    {
        return removeHead();
    }
    else if (index == count - 1)
    {
        return removeTail();
    }
    else
    {
        Node *temp = head;
        for (int i = 0; i < index - 1; i++)
            temp = temp->next;
        Node *temp2 = temp->next;
        output = temp2->data;
        temp->next = temp->next->next;
        delete temp2;
    }
    count--;
    return output;
}
template <class T>
bool SinglyLinkedList<T>::removeItem(T item)
{
    Node *temp = head;
    int removeIndex = -1;
    for (int i = 0; i < count; i++)
    {
        if (temp->data == item)
        {
            removeIndex = i;
            break;
        }
        temp = temp->next;
    }
    if (removeIndex == -1)
        return false;
    removeAt(removeIndex);
    return true;
}
template <class T>
bool SinglyLinkedList<T>::empty() const
{
    return !count;
}
template <class T>
int SinglyLinkedList<T>::size() const
{
    return count;
}
template <class T>
void SinglyLinkedList<T>::clear()
{
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}
template <class T>
T &SinglyLinkedList<T>::get(int index) const
{
    if (index < 0 || index > count - 1)
        throw out_of_range("Index is invalid!");
    Node *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;
    return temp->data;
}
template <class T>
int SinglyLinkedList<T>::indexOf(T item) const
{
    int itemIndex = -1;
    Node *temp = head;
    for (int i = 0; i < count; i++)
    {
        if (temp->data == item)
        {
            itemIndex = i;
            break;
        }
        temp = temp->next;
    }
    return itemIndex;
}
template <class T>
bool SinglyLinkedList<T>::contains(T item) const
{
    if (indexOf(item) == -1)
        return false;
    return true;
}
template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T &)) const
{
    if (count == 0)
        return "";
    string output;
    if (item2str)
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            T &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }

    return output;
}

template <>
string SinglyLinkedList<int>::toString(string (*item2str)(int &)) const
{
    string output;
    if (item2str)
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            int &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }
    else
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            int &number = get(i);
            string str = std::to_string(number);
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }

    return output;
}

template <>
string SinglyLinkedList<float>::toString(string (*item2str)(float &)) const
{
    string output;
    if (item2str)
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            float &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }
    else
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            float &number = get(i);
            string str = std::to_string(number);
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }

    return output;
}

template <>
string SinglyLinkedList<string>::toString(string (*item2str)(string &)) const
{
    string output;
    if (item2str)
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            string &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }
    else
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            string &number = get(i);
            string str = number;
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }

    return output;
}

template <>
string SinglyLinkedList<char>::toString(string (*item2str)(char &)) const
{
    string output;
    if (item2str)
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            char &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }
    else
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            char &number = get(i);
            string str = std::to_string(number);
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }

    return output;
}


template <>
string SinglyLinkedList<double>::toString(string (*item2str)(double &)) const
{
    string output;
    if (item2str)
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            double &number = get(i);
            string str = item2str(number);
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }
    else
    {
        output = "";

        for (int i = 0; i < count; i++)
        {
            double &number = get(i);
            string str = std::to_string(number);
            if (i != count - 1)
                output = output + "[" + str + "]->";
            else
                output = output + "[" + str + "]";
        }
    }

    return output;
}




template <class T>
double SinglyLinkedList<T>::scalarProduct(const SinglyLinkedList &other) const
{
    double output = 0;
    Node *ptr1 = head;
    Node *ptr2 = other.head;
    for (int i = 0; i < count; i++)
    {
        double temp1 = ptr1->data;
        double temp2 = ptr2->data;
        output += (temp1 * temp2);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        cout << output << " ";
    }
    cout << endl;
    return output;
}





template <>
double SinglyLinkedList<float>::scalarProduct(const SinglyLinkedList &other) const
{
    double output = 0;
    Node *ptr1 = head;
    Node *ptr2 = other.head;
    for (int i = 0; i < count; i++)
    {
        double temp1 = (double)(ptr1->data);
        double temp2 = (double)(ptr2->data);
        output += (temp1 * temp2);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        // cout << output << " ";
    }
    // cout << endl;
    return output;
}
template <>
double SinglyLinkedList<string>::scalarProduct(const SinglyLinkedList &other) const
{
    double output = 0;
    Node *ptr1 = head;
    Node *ptr2 = other.head;
    for (int i = 0; i < count; i++)
    {
        double temp1 = stod(ptr1->data);
        double temp2 = stod(ptr2->data);
        output += (temp1 * temp2);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        // cout << output << " ";
    }
    // cout << endl;
    return output;
}
template <>
double SinglyLinkedList<Point>::scalarProduct(const SinglyLinkedList &other) const
{
    return 0;
}

template <class T>
double SinglyLinkedList<T>::vectorMagnitude() const
{
    double output = 0;
    Node *temp = head;
    for (int i = 0; i < count; i++)
    {
        output = output + (temp->data * temp->data);
        temp = temp->next;
    }
    return sqrt(output);
}
template <>
double SinglyLinkedList<string>::vectorMagnitude() const
{
    double output = 0;
    Node *temp = head;
    for (int i = 0; i < count; i++)
    {
        double val = stod(temp->data);
        output = output + (val * val);
        temp = temp->next;
    }
    return sqrt(output);
}
template <>
double SinglyLinkedList<Point>::vectorMagnitude() const
{
    return 0;
}
template <class T>
double SinglyLinkedList<T>::manhattanDistance(const SinglyLinkedList &other) const
{
    double output = 0;
    Node *ptr1 = head;
    Node *ptr2 = other.head;
    for (int i = 0; i < count; i++)
    {
        output = output + abs(ptr1->data - ptr2->data);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return output;
}
template <>
double SinglyLinkedList<string>::manhattanDistance(const SinglyLinkedList &other) const
{
    double output = 0;
    Node *ptr1 = head;
    Node *ptr2 = other.head;
    for (int i = 0; i < count; i++)
    {
        double val1 = stod(ptr1->data);
        double val2 = stod(ptr2->data);
        output = output + abs(val1 - val2);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return output;
}

template <>
double SinglyLinkedList<Point>::manhattanDistance(const SinglyLinkedList &other) const
{
    return 0;
}

template <class T>
double SinglyLinkedList<T>::euclideanDistance(const SinglyLinkedList &other) const
{
    double output = 0;
    Node *ptr1 = head;
    Node *ptr2 = other.head;
    for (int i = 0; i < count; i++)
    {
        output = output + (ptr1->data - ptr2->data) * (ptr1->data - ptr2->data);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return sqrt(output);
}
template <>
double SinglyLinkedList<string>::euclideanDistance(const SinglyLinkedList &other) const
{
    double output = 0;
    Node *ptr1 = head;
    Node *ptr2 = other.head;
    for (int i = 0; i < count; i++)
    {
        double val1 = stod(ptr1->data);
        double val2 = stod(ptr2->data);
        output = output + (val1 - val2) * (val1 - val2);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return sqrt(output);
}

template <>
double SinglyLinkedList<Point>::euclideanDistance(const SinglyLinkedList &other) const
{
    return 0;
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin()
{
    return Iterator(head);
}
template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end()
{
    return Iterator(tail);
}
// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node *node)
{
    // TODO
    current = node;
}

// TODO: implement other methods of SinglyLinkedList::Iterator
template <class T>
typename SinglyLinkedList<T>::Iterator &SinglyLinkedList<T>::Iterator::operator=(const Iterator &other)
{
    current = other.getCurrent();
    return *this;
}
template <class T>
T &SinglyLinkedList<T>::Iterator::operator*()
{
    if (current == nullptr)
        throw out_of_range("Iterator is out of range!");
    return current->data;
}

template <class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator &other) const
{
    return (current != other.getCurrent());
}

template <class T>
typename SinglyLinkedList<T>::Node *SinglyLinkedList<T>::Iterator::getCurrent() const
{
    return current;
}
template <class T>
typename SinglyLinkedList<T>::Iterator &SinglyLinkedList<T>::Iterator::operator++()
{
    if (current->next == nullptr)
        throw out_of_range("Iterator cannot advance past end!");
    this->current = current->next;
    return *this;
}
template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::operator++(int)
{
    if (current->next == nullptr)
        throw out_of_range("Iterator cannot advance past end!");
    Iterator temp = *this;
    this->current = current->next;
    return temp;
}

// ----------------- VectorStore Implementation -----------------

// VectorRecord constructor
VectorStore::VectorRecord::VectorRecord(int id, const string &rawText, SinglyLinkedList<float> *vector)
{
    this->id = id;
    this->rawText = rawText;
    this->vector = vector;
    this->rawLength = rawText.length();
}

VectorStore::VectorStore(int dimension, EmbedFn embeddingFunction)
{
    // TODO
    this->dimension = dimension;
    count = 0;
    this->embeddingFunction = embeddingFunction;
}

VectorStore::~VectorStore()
{
    // TODO
}

int VectorStore::size() const
{
    return count;
}
bool VectorStore::empty() const
{
    return count == 0;
}
void VectorStore::clear()
{
    while (count > 0)
    {
        removeAt(0);
    }
}
SinglyLinkedList<float> *VectorStore::preprocessing(string rawText)
{
    SinglyLinkedList<float> *newVector = embeddingFunction(rawText);
    int newDimension = newVector->getCount();
    if (newDimension > dimension)
    {
        for (int i = 0; i < newDimension - dimension; i++)
            newVector->removeTail();
    }
    else if (newDimension < dimension)
    {
        for (int i = 0; i < dimension - newDimension; i++)
            newVector->add(0.0);
    }
    return newVector;
}

void VectorStore::addText(string rawText)
{
    SinglyLinkedList<float> *processedData = preprocessing(rawText);
    int newId = (count==0) ? 1 : (getId(count-1)+1);
    int textLength = rawText.length();
    VectorRecord *newRecord = new VectorRecord(newId, rawText, processedData);
    newRecord->rawLength = textLength;
    records.add(newRecord);
    count++;
}
SinglyLinkedList<float> &VectorStore::getVector(int index) const
{
    if (index < 0 || index > count - 1)
        throw out_of_range("Index is invalid!");
    return *records.get(index)->vector;
}

string VectorStore::getRawText(int index) const
{
    if (index < 0 || index > count - 1)
        throw out_of_range("Index is invalid!");
    return records.get(index)->rawText;
}
int VectorStore::getId(int index) const
{
    if (index < 0 || index > count - 1)
        throw out_of_range("Index is invalid!");
    return records.get(index)->id;
}
bool VectorStore::removeAt(int index)
{
    if (index < 0 || index > count - 1)
        throw out_of_range("Index is invalid!");
    VectorRecord *temp = records.get(index);
    records.removeAt(index);
    delete temp->vector;
    delete temp;
    count--;
    for (int i = index; i < count; i++)
        records.get(i)->id = i + 1;
    return true;
}

bool VectorStore::updateText(int index, string newRawText)
{
    if (index < 0 || index > count - 1)
        throw out_of_range("Index is invalid!");
    int newLength = newRawText.length();
    SinglyLinkedList<float> *newVector = preprocessing(newRawText);
    VectorRecord *currentRecord = records.get(index);
    currentRecord->rawText = newRawText;
    currentRecord->vector = newVector;
    currentRecord->rawLength = newLength;
    return true;
}
void VectorStore::setEmbeddingFunction(EmbedFn newEmbeddingFunction)
{
    embeddingFunction = newEmbeddingFunction;
}

void VectorStore::forEach(void (*action)(SinglyLinkedList<float> &, int, string &))
{
    for (int i = 0; i < count; i++)
        action(getVector(i), records.get(i)->id, records.get(i)->rawText);
}
double VectorStore::cosineSimilarity(const SinglyLinkedList<float> &v1,
                                     const SinglyLinkedList<float> &v2) const
{
    double scalarProduct = v1.scalarProduct(v2);
    double firstMagnitude = v1.vectorMagnitude();
    double secondMagnitude = v2.vectorMagnitude();

    return scalarProduct / (firstMagnitude * secondMagnitude);
}

double VectorStore::l1Distance(const SinglyLinkedList<float> &v1,
                               const SinglyLinkedList<float> &v2) const
{
    return v1.manhattanDistance(v2);
}
double VectorStore::l2Distance(const SinglyLinkedList<float> &v1,
                               const SinglyLinkedList<float> &v2) const
{
    return v1.euclideanDistance(v2);
}
int VectorStore::findNearest(const SinglyLinkedList<float> &query, const string &metric) const
{
    if (!(metric == "cosine" || metric == "euclidean" || metric == "manhattan"))
        throw invalid_metric();

    if (metric == "cosine")
    {
        int nearestIndex = 0;
        int minDistance = cosineSimilarity(query, getVector(0));
        for (int i = 1; i < count; i++)
        {
            double distance = cosineSimilarity(query, getVector(i));
            if (minDistance > distance)
            {
                minDistance = distance;
                nearestIndex = i;
            }
        }
        return nearestIndex;
    }
    else if (metric == "manhattan")
    {
        int nearestIndex = 0;
        int minDistance = l1Distance(query, getVector(0));
        for (int i = 1; i < count; i++)
        {
            double distance = l1Distance(query, getVector(i));
            if (minDistance > distance)
            {
                minDistance = distance;
                nearestIndex = i;
            }
        }
        return nearestIndex;
    }
    else
    {
        int nearestIndex = 0;
        int minDistance = l2Distance(query, getVector(0));
        for (int i = 1; i < count; i++)
        {
            double distance = l2Distance(query, getVector(i));
            if (minDistance > distance)
            {
                minDistance = distance;
                nearestIndex = i;
            }
        }
        return nearestIndex;
    }
}
int *VectorStore::topKNearest(const SinglyLinkedList<float> &query, int k, const string &metric) const
{
    if (!(metric == "cosine" || metric == "euclidean" || metric == "manhattan"))
        throw invalid_metric();
    if (k <= 0 || k > count - 1)
        throw invalid_k_value();
    int *output = new int[k];
    double *storage = new double[count];
    if (metric == "cosine")
    {
        for (int i = 0; i < count; i++)
            storage[i] = cosineSimilarity(query, getVector(i));
    }
    else if (metric == "euclidean")
    {
        for (int i = 0; i < count; i++)
            storage[i] = l1Distance(query, getVector(i));
    }
    else
    {
        for (int i = 0; i < count; i++)
            storage[i] = l2Distance(query, getVector(i));
    }
    quickSort(storage, count);
    for (int i = count - 1; i > count - 1 - k; i--)
    {
        *(output + count - i) = storage[i];
    }
    delete[] storage;
    return output;
}
ArrayList<VectorStore::VectorRecord *> VectorStore::getRecords() const
{
    return records;
}
int VectorStore::getDimension() const
{
    return dimension;
}
int VectorStore::getCount() const
{
    return count;
}
// Explicit template instantiation for char, string, int, double, float, and Point

// QuickSort instantiations
template void quickSort<int>(int *, int);
template void quickSort<double>(double *, int);
template void quickSort<float>(float *, int);

template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
