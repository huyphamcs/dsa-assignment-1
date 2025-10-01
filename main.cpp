#include "VectorStore.h"

// Helper functions for testing
string intToString(int &value) {
    return to_string(value);
}

string floatToString(float &value) {
    return to_string(value);
}

string pointToString(Point &value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

// Mock embedding function for VectorStore testing
SinglyLinkedList<float>* mockEmbedding(const string &text) {
    SinglyLinkedList<float>* result = new SinglyLinkedList<float>();
    
    // Simple mock: convert each character to a float value
    for (char c : text) {
        result->add(static_cast<float>(c) / 100.0f);
    }
    
    return result;
}

// Test QuickSort Implementation
void test_quickSort() {
    cout << "=== Test QuickSort ===" << endl;
    
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int size1 = 7;
    
    cout << "Original array: ";
    for (int i = 0; i < size1; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    quickSort(arr1, size1);
    
    cout << "Sorted array: ";
    for (int i = 0; i < size1; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    // Test edge cases
    int arr2[] = {1};
    quickSort(arr2, 1);
    cout << "Single element array: " << arr2[0] << endl;
    
    int arr3[] = {};
    quickSort(arr3, 0);
    cout << "Empty array test passed" << endl;
    
    cout << "QuickSort tests completed" << endl << endl;
}

// Test ArrayList Implementation
void test_arrayList_basic() {
    cout << "=== Test ArrayList Basic Operations ===" << endl;
    
    ArrayList<int> list;
    
    // Test empty list
    cout << "Empty list size: " << list.size() << endl;
    cout << "Is empty: " << (list.empty() ? "true" : "false") << endl;
    
    // Test add operations
    list.add(10);
    list.add(20);
    list.add(30);
    
    cout << "After adding 10, 20, 30:" << endl;
    cout << "Size: " << list.size() << endl;
    cout << "List: " << list.toString(intToString) << endl;
    
    // Test add at index
    list.add(1, 15);
    cout << "After adding 15 at index 1: " << list.toString(intToString) << endl;
    
    // Test get and set
    cout << "Element at index 2: " << list.get(2) << endl;
    list.set(2, 25);
    cout << "After setting index 2 to 25: " << list.toString(intToString) << endl;
    
    // Test indexOf and contains
    cout << "Index of 25: " << list.indexOf(25) << endl;
    cout << "Contains 25: " << (list.contains(25) ? "true" : "false") << endl;
    cout << "Contains 100: " << (list.contains(100) ? "true" : "false") << endl;
    
    // Test remove
    int removed = list.removeAt(1);
    cout << "Removed element at index 1: " << removed << endl;
    cout << "List after removal: " << list.toString(intToString) << endl;
    
    cout << "ArrayList basic tests completed" << endl << endl;
}

void test_arrayList_copyAndAssignment() {
    cout << "=== Test ArrayList Copy and Assignment ===" << endl;
    
    ArrayList<int> original;
    original.add(1);
    original.add(2);
    original.add(3);
    
    // Test copy constructor
    ArrayList<int> copy(original);
    cout << "Original: " << original.toString(intToString) << endl;
    cout << "Copy: " << copy.toString(intToString) << endl;
    
    // Test assignment operator
    ArrayList<int> assigned;
    assigned = original;
    cout << "Assigned: " << assigned.toString(intToString) << endl;
    
    // Modify original and check if copies are independent
    original.add(4);
    cout << "After adding 4 to original:" << endl;
    cout << "Original: " << original.toString(intToString) << endl;
    cout << "Copy: " << copy.toString(intToString) << endl;
    cout << "Assigned: " << assigned.toString(intToString) << endl;
    
    cout << "ArrayList copy and assignment tests completed" << endl << endl;
}

void test_arrayList_iterator() {
    cout << "=== Test ArrayList Iterator ===" << endl;
    
    ArrayList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    
    cout << "Using iterator to traverse: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Test iterator operations
    auto it = list.begin();
    cout << "First element: " << *it << endl;
    ++it;
    cout << "Second element: " << *it << endl;
    --it;
    cout << "Back to first: " << *it << endl;
    
    cout << "ArrayList iterator tests completed" << endl << endl;
}

void test_arrayList_exceptions() {
    cout << "=== Test ArrayList Exception Handling ===" << endl;
    
    ArrayList<int> list;
    list.add(1);
    list.add(2);
    
    try {
        list.get(5); // Should throw exception
    } catch (const out_of_range& e) {
        cout << "Caught expected exception for get(5): " << e.what() << endl;
    }
    
    try {
        list.removeAt(10); // Should throw exception
    } catch (const out_of_range& e) {
        cout << "Caught expected exception for removeAt(10): " << e.what() << endl;
    }
    
    try {
        list.add(-1, 100); // Should throw exception
    } catch (const out_of_range& e) {
        cout << "Caught expected exception for add(-1, 100): " << e.what() << endl;
    }
    
    cout << "ArrayList exception tests completed" << endl << endl;
}

void test_singlyLinkedList_basic() {
    cout << "=== Test SinglyLinkedList Basic Operations ===" << endl;
    
    SinglyLinkedList<int> list;
    
    // Test empty list
    cout << "Empty list size: " << list.size() << endl;
    cout << "Is empty: " << (list.empty() ? "true" : "false") << endl;
    
    // Test add operations
    list.add(10);
    list.add(20);
    list.add(30);
    
    cout << "After adding 10, 20, 30:" << endl;
    cout << "Size: " << list.size() << endl;
    cout << "List: " << list.toString(intToString) << endl;
    
    // Test add at index
    list.add(1, 15);
    cout << "After adding 15 at index 1: " << list.toString(intToString) << endl;
    
    // Test get
    cout << "Element at index 2: " << list.get(2) << endl;
    
    // Test indexOf and contains
    cout << "Index of 20: " << list.indexOf(20) << endl;
    cout << "Contains 20: " << (list.contains(20) ? "true" : "false") << endl;
    cout << "Contains 100: " << (list.contains(100) ? "true" : "false") << endl;
    
    // Test remove operations
    int removed = list.removeAt(1);
    cout << "Removed element at index 1: " << removed << endl;
    cout << "List after removal: " << list.toString(intToString) << endl;
    
    bool itemRemoved = list.removeItem(30);
    cout << "Removed item 30: " << (itemRemoved ? "true" : "false") << endl;
    cout << "List after removing item 30: " << list.toString(intToString) << endl;
    
    cout << "SinglyLinkedList basic tests completed" << endl << endl;
}

void test_singlyLinkedList_headTail() {
    cout << "=== Test SinglyLinkedList Head/Tail Operations ===" << endl;
    
    SinglyLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    
    cout << "Original list: " << list.toString(intToString) << endl;
    
    int headRemoved = list.removeHead();
    cout << "Removed head: " << headRemoved << endl;
    cout << "List after removing head: " << list.toString(intToString) << endl;
    
    int tailRemoved = list.removeTail();
    cout << "Removed tail: " << tailRemoved << endl;
    cout << "List after removing tail: " << list.toString(intToString) << endl;
    
    cout << "SinglyLinkedList head/tail tests completed" << endl << endl;
}

void test_singlyLinkedList_vectorOperations() {
    cout << "=== Test SinglyLinkedList Vector Operations ===" << endl;
    
    SinglyLinkedList<float> vector1;
    vector1.add(1.0f);
    vector1.add(2.0f);
    vector1.add(3.0f);
    
    SinglyLinkedList<float> vector2;
    vector2.add(4.0f);
    vector2.add(5.0f);
    vector2.add(6.0f);
    
    cout << "Vector 1: " << vector1.toString(floatToString) << endl;
    cout << "Vector 2: " << vector2.toString(floatToString) << endl;
    
    // Test scalar product
    double scalarProd = vector1.scalarProduct(vector2);
    cout << "Scalar product: " << scalarProd << endl;
    
    // Test vector magnitude
    double magnitude1 = vector1.vectorMagnitude();
    double magnitude2 = vector2.vectorMagnitude();
    cout << "Vector 1 magnitude: " << magnitude1 << endl;
    cout << "Vector 2 magnitude: " << magnitude2 << endl;
    
    // Test distance measures
    double manhattanDist = vector1.manhattanDistance(vector2);
    double euclideanDist = vector1.euclideanDistance(vector2);
    cout << "Manhattan distance: " << manhattanDist << endl;
    cout << "Euclidean distance: " << euclideanDist << endl;
    
    cout << "SinglyLinkedList vector operations tests completed" << endl << endl;
}

void test_singlyLinkedList_iterator() {
    cout << "=== Test SinglyLinkedList Iterator ===" << endl;
    
    SinglyLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    
    cout << "Using iterator to traverse: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "SinglyLinkedList iterator tests completed" << endl << endl;
}

void test_singlyLinkedList_clear() {
    cout << "=== Test SinglyLinkedList Clear ===" << endl;
    
    SinglyLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    
    cout << "Before clear - Size: " << list.size() << endl;
    cout << "Before clear - Empty: " << (list.empty() ? "true" : "false") << endl;
    
    list.clear();
    
    cout << "After clear - Size: " << list.size() << endl;
    cout << "After clear - Empty: " << (list.empty() ? "true" : "false") << endl;
    
    cout << "SinglyLinkedList clear tests completed" << endl << endl;
}

void test_vectorStore_basic() {
    cout << "=== Test VectorStore Basic Operations ===" << endl;
    
    VectorStore store(3, mockEmbedding);
    
    // Test empty store
    cout << "Empty store size: " << store.size() << endl;
    cout << "Is empty: " << (store.empty() ? "true" : "false") << endl;
    cout << "Dimension: " << store.getDimension() << endl;
    
    // Test adding text
    store.addText("hello");
    store.addText("world");
    store.addText("test");
    
    cout << "After adding 3 texts:" << endl;
    cout << "Size: " << store.size() << endl;
    cout << "Count: " << store.getCount() << endl;
    
    // Test getting data
    for (int i = 0; i < store.size(); i++) {
        cout << "Record " << i << ":" << endl;
        cout << "  ID: " << store.getId(i) << endl;
        cout << "  Raw text: " << store.getRawText(i) << endl;
        cout << "  Vector size: " << store.getVector(i).size() << endl;
    }
    
    cout << "VectorStore basic tests completed" << endl << endl;
}

void test_vectorStore_update() {
    cout << "=== Test VectorStore Update Operations ===" << endl;
    
    VectorStore store(3, mockEmbedding);
    store.addText("original");
    
    cout << "Original text: " << store.getRawText(0) << endl;
    
    bool updated = store.updateText(0, "updated");
    cout << "Update successful: " << (updated ? "true" : "false") << endl;
    cout << "Updated text: " << store.getRawText(0) << endl;
    
    cout << "VectorStore update tests completed" << endl << endl;
}

void test_vectorStore_remove() {
    cout << "=== Test VectorStore Remove Operations ===" << endl;
    
    VectorStore store(3, mockEmbedding);
    store.addText("first");
    store.addText("second");
    store.addText("third");
    
    cout << "Before removal - Size: " << store.size() << endl;
    for (int i = 0; i < store.size(); i++) {
        cout << "  " << i << ": " << store.getRawText(i) << " (ID: " << store.getId(i) << ")" << endl;
    }
    
    bool removed = store.removeAt(1);
    cout << "Removal successful: " << (removed ? "true" : "false") << endl;
    cout << "After removal - Size: " << store.size() << endl;
    for (int i = 0; i < store.size(); i++) {
        cout << "  " << i << ": " << store.getRawText(i) << " (ID: " << store.getId(i) << ")" << endl;
    }
    
    cout << "VectorStore remove tests completed" << endl << endl;
}

void test_vectorStore_similarity() {
    cout << "=== Test VectorStore Similarity Operations ===" << endl;
    
    VectorStore store(3, mockEmbedding);
    store.addText("abc");  // Will create vector with normalized values
    store.addText("def");
    store.addText("xyz");
    
    SinglyLinkedList<float> query;
    query.add(0.5f);
    query.add(0.6f);
    query.add(0.7f);
    
    // Test different similarity metrics
    for (int i = 0; i < store.size(); i++) {
        double cosine = store.cosineSimilarity(query, store.getVector(i));
        double l1 = store.l1Distance(query, store.getVector(i));
        double l2 = store.l2Distance(query, store.getVector(i));
        
        cout << "Vector " << i << " similarities:" << endl;
        cout << "  Cosine: " << cosine << endl;
        cout << "  L1 Distance: " << l1 << endl;
        cout << "  L2 Distance: " << l2 << endl;
    }
    
    cout << "VectorStore similarity tests completed" << endl << endl;
}

void test_vectorStore_search() {
    cout << "=== Test VectorStore Search Operations ===" << endl;
    
    VectorStore store(3, mockEmbedding);
    store.addText("hello");
    store.addText("world");
    store.addText("test");
    store.addText("search");
    
    SinglyLinkedList<float> query;
    query.add(0.5f);
    query.add(0.6f);
    query.add(0.7f);
    
    // Test findNearest with different metrics
    try {
        int nearestCosine = store.findNearest(query, "cosine");
        cout << "Nearest (cosine): " << nearestCosine << " - " << store.getRawText(nearestCosine) << endl;
        
        int nearestEuclidean = store.findNearest(query, "euclidean");
        cout << "Nearest (euclidean): " << nearestEuclidean << " - " << store.getRawText(nearestEuclidean) << endl;
        
        int nearestManhattan = store.findNearest(query, "manhattan");
        cout << "Nearest (manhattan): " << nearestManhattan << " - " << store.getRawText(nearestManhattan) << endl;
    } catch (const exception& e) {
        cout << "Error in findNearest: " << e.what() << endl;
    }
    
    // Test topKNearest
    try {
        int k = 2;
        int* topK = store.topKNearest(query, k, "cosine");
        cout << "Top " << k << " nearest:" << endl;
        for (int i = 0; i < k; i++) {
            cout << "  " << topK[i] << endl;
        }
        delete[] topK;
    } catch (const exception& e) {
        cout << "Error in topKNearest: " << e.what() << endl;
    }
    
    cout << "VectorStore search tests completed" << endl << endl;
}

void test_vectorStore_exceptions() {
    cout << "=== Test VectorStore Exception Handling ===" << endl;
    
    VectorStore store(3, mockEmbedding);
    store.addText("test");
    
    SinglyLinkedList<float> query;
    query.add(1.0f);
    query.add(2.0f);
    query.add(3.0f);
    
    // Test invalid metric
    try {
        store.findNearest(query, "invalid_metric");
    } catch (const invalid_metric& e) {
        cout << "Caught expected exception for invalid metric: " << e.what() << endl;
    }
    
    // Test invalid k value
    try {
        store.topKNearest(query, -1, "cosine");
    } catch (const invalid_k_value& e) {
        cout << "Caught expected exception for invalid k: " << e.what() << endl;
    }
    
    // Test out of range access
    try {
        store.getRawText(10);
    } catch (const out_of_range& e) {
        cout << "Caught expected exception for out of range access: " << e.what() << endl;
    }
    
    cout << "VectorStore exception tests completed" << endl << endl;
}

void test_vectorStore_clear() {
    cout << "=== Test VectorStore Clear ===" << endl;
    
    VectorStore store(3, mockEmbedding);
    store.addText("test1");
    store.addText("test2");
    
    cout << "Before clear - Size: " << store.size() << endl;
    cout << "Before clear - Empty: " << (store.empty() ? "true" : "false") << endl;
    
    store.clear();
    
    cout << "After clear - Size: " << store.size() << endl;
    cout << "After clear - Empty: " << (store.empty() ? "true" : "false") << endl;
    
    cout << "VectorStore clear tests completed" << endl << endl;
}

// Callback function for forEach test
void printVectorInfo(SinglyLinkedList<float>& vector, int id, string& text) {
    cout << "Vector ID: " << id << ", Text: " << text << ", Size: " << vector.size() << endl;
}

void test_vectorStore_forEach() {
    cout << "=== Test VectorStore forEach ===" << endl;
    
    VectorStore store(3, mockEmbedding);
    store.addText("first");
    store.addText("second");
    store.addText("third");
    
    cout << "Using forEach to print all vectors:" << endl;
    store.forEach(printVectorInfo);
    
    cout << "VectorStore forEach tests completed" << endl << endl;
}

void test_arrayList_toString(){
    ArrayList<string>* newList = new ArrayList<string>();
    newList->add("Pham Quoc Huy");
    newList->add("Luu Nguyen Khanh Linh");
    newList->add("Nguyen Hong Thien An");
    cout << newList->toString() << endl;

    ArrayList<float>* newFloatList = new ArrayList<float>();
    for (float i = 0; i < 10; i+=1.5) newFloatList->add(i);
    cout << newFloatList->toString() << endl;

    ArrayList<char>* newCharList = new ArrayList<char>();
    newCharList->add('a');
    newCharList->add('b');
    newCharList->add('c');
    cout << newCharList->toString() << endl;

    ArrayList<double>* newDoubleList = new ArrayList<double>();
    for (double i = 0; i < 10; i+=0.9) newDoubleList->add(i);
    cout << newDoubleList->toString() << endl;
}

void test_singlyLinkedList_toString() {
    SinglyLinkedList<double>* newList = new SinglyLinkedList<double>();
    for (double i = 0; i < 10; i++) newList->add(i);
    cout << newList->toString() << endl;

    SinglyLinkedList<string>* newStringList = new SinglyLinkedList<string>();
    newStringList->add("Pham Quoc Huy");
    newStringList->add("Luu Nguyen Khanh Linh");
    newStringList->add("Nguyen Hong Thien An");
    cout << newStringList->toString() << endl;
}

// Run all tests
int main() {
    test_singlyLinkedList_toString();


    return 0;
}