#ifndef VECTORSTORE_H
#define VECTORSTORE_H

#include "main.h"

// ==============================
// Quick Sort
// ==============================
template <class T>
void swapInArray(T *arr, int i, int j);
template <class T>
void quickSort(T *arr, int size);
// ==============================
// Double number comparison

bool isDoubleEqual (double a, double b, double epsilon = 10e-4);


// Class ArrayList
// ==============================

template <class T>
class ArrayList
{
#ifdef TESTING
    friend class TestHelper;
#endif
private:
    T *data;
    int capacity;
    int count;

    void ensureCapacity(int cap);

public:
    class Iterator;
    friend class Iterator;

    ArrayList(int initCapacity = 10);
    ArrayList(const ArrayList<T> &other); // Deep Copy
    ~ArrayList();
    ArrayList<T> &operator=(const ArrayList<T> &other); // Deep Copy

    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool empty() const;
    int size() const;
    void clear();
    T &get(int index) const;
    void set(int index, T e);
    int indexOf(T item) const;
    bool contains(T item) const;
    // Each datatype needs a specific toString method in case item2str = 0
    string toString(string (*item2str)(T &) = 0) const;
    bool isValidIndex(int index) const;
    int getCount() const;
    T *getData() const;
    int getCapacity() const;
    Iterator begin();
    Iterator end();

    // Inner class Iterator
    class Iterator
    {
#ifdef TESTING
        friend class TestHelper;
#endif
    private:
        int cursor;
        ArrayList<T> *pList;

    public:
        Iterator(ArrayList<T> *pList = nullptr, int index = 0);
        Iterator &operator=(const Iterator &other); // Deep Copy
        T &operator*();
        bool operator!=(const Iterator &other) const;
        Iterator &operator++();
        Iterator operator++(int);
        Iterator &operator--();
        Iterator operator--(int);
        int getCursor() const;
        ArrayList<T> *getPList() const;
        bool isValidCursor(int cursor) const;
    };
};

// =====================================
// Class SinglyLinkedList
// =====================================
template <class T>
class SinglyLinkedList
{
#ifdef TESTING
    friend class TestHelper;
#endif
private:
    class Node
    {
    public:
        T data;
        Node *next;

        Node() : data(), next(nullptr) {}
        Node(const T &data, Node *next = nullptr) : data(data), next(next) {}
    };

    Node *head;
    Node *tail;
    int count;

public:
    class Iterator;
    friend class Iterator;

    SinglyLinkedList();
    ~SinglyLinkedList();

    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool removeItem(T item);
    bool empty() const;
    int size() const;
    void clear();
    T &get(int index) const;
    int indexOf(T item) const;
    bool contains(T item) const;
    string toString(string (*item2str)(T &) = 0) const;
    Node *getHead() const;
    Node *getTail() const;
    int getCount() const;
    T removeHead();
    T removeTail();
    double scalarProduct(const SinglyLinkedList &other) const;
    double vectorMagnitude() const;
    double manhattanDistance(const SinglyLinkedList &other) const;
    double euclideanDistance(const SinglyLinkedList &other) const;

    Iterator begin();
    Iterator end();

    // Inner class Iterator
    class Iterator
    {
#ifdef TESTING
        friend class TestHelper;
#endif
    private:
        Node *current;

    public:
        Iterator(Node *node = nullptr);
        Iterator &operator=(const Iterator &other); // Deep Copy
        T &operator*();
        bool operator!=(const Iterator &other) const;
        Iterator &operator++();
        Node *getCurrent() const;
        Iterator operator++(int);
        
    };
};

// =====================================
// Class VectorStore
// =====================================

class VectorStore
{
#ifdef TESTING
    friend class TestHelper;
#endif
public:
    struct VectorRecord
    {
        int id;
        string rawText;
        int rawLength;
        // A list with dimension size contains dimenstion numbers for a vector
        SinglyLinkedList<float> *vector;
        // CONSTRUCTOR
        VectorRecord(int id, const string &rawText, SinglyLinkedList<float> *vector);
    };

    using EmbedFn = SinglyLinkedList<float> *(*)(const string &);
    // static int nextId;

private:
    // A vector store contains many records, saved as an Array list
    ArrayList<VectorRecord *> records;
    // All the vector in the store has the dimension
    int dimension;
    // The size of the records
    int count;
    EmbedFn embeddingFunction;

public:
    // Construct a store with vectors in R^512
    VectorStore(int dimension = 512, EmbedFn embeddingFunction = nullptr);
    // Destructor
    ~VectorStore();
    int size() const;
    bool empty() const;
    void clear();

    SinglyLinkedList<float> *preprocessing(string rawText);

    void addText(string rawText);
    SinglyLinkedList<float> &getVector(int index) const;
    string getRawText(int index) const;
    int getId(int index) const;
    bool removeAt(int index);
    bool updateText(int index, string newRawText);
    void setEmbeddingFunction(EmbedFn newEmbeddingFunction);

    void forEach(void (*action)(SinglyLinkedList<float> &, int, string &));

    double cosineSimilarity(const SinglyLinkedList<float> &v1,
                            const SinglyLinkedList<float> &v2) const;
    double l1Distance(const SinglyLinkedList<float> &v1,
                      const SinglyLinkedList<float> &v2) const;
    double l2Distance(const SinglyLinkedList<float> &v1,
                      const SinglyLinkedList<float> &v2) const;

    int findNearest(const SinglyLinkedList<float> &query, const string &metric = "cosine") const;

    int *topKNearest(const SinglyLinkedList<float> &query, int k, const string &metric = "cosine") const;
    ArrayList<VectorRecord *> getRecords() const;
    int getDimension() const;
    int getCount() const ;

    // class Iterator{
    // private:
    //     VectorRecord* current;
    // public:
        
    // };
};

#endif // VECTORSTORE_H