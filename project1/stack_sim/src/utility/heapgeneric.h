#pragma once

#include <vector>

//may need several heaps for what we probably should accomplish in "memory"
//instruction heap
//data heap
//stack

template<typename T> //generic typing
class Heap_Generic {
public:
	//constructors
	Heap_Generic() {}
	~Heap_Generic();

	//modifiers
	void insert(const T element) { heap.push_back(element);	heapifyUp(static_cast<int>(heap.size() - 1)); }
	void deleteRoot() {
		heap[0] = heap.at(size() - 1);
		heap.pop_back();
		heapifyDown(0);
	}
	void deleteSegment(const unsigned int& begin, const unsigned int& end) {
		if (size() >= end && end > begin) {
			heap.erase(heap.begin() + begin, heap.begin() + end);
		}
		heapifyDown();
	}

	//capacity
	const int& size() const { return heap.size(); }

	//accessors
	T& operator[](const int& address) { return heap[address]; }
private:
	//node access
	const int& left(int parent) const {
 		int i = ( parent << 1 ) + 1; // 2 * parent + 1
    	return ( i < heap.size() ) ? i : -1;
	}
	const int& right(int parent) const {
		int i = ( parent << 1 ) + 2; // 2 * parent + 2
    	return ( i < heap.size() ) ? i : -1;
	}
	const int& parent(int child) const {
		if (child != 0) {
	        int i = (child - 1) >> 1;
	        return i;
	    }
	    return -1;
	}

	//modifiers cont.
	void heapifyUp(int index) {
		while (index > 0 && parent(index) >= 0 && heap[parent(index)] > heap[index]) {
			int temp = heap[parent(index)];
			heap[parent(index)] = heap[index];
			heap[index] = temp;
			index = parent(index);
		}
	}

	void heapifyDown(const int index) {
		int child = left(index);

		if (child > 0 && right(index) > 0 && heap[child] > heap[right(index)]) {
			child = right(index);
		}

		if (child > 0) {
			int tmp = heap[index];
	        heap[index] = heap[child];
	        heap[child] = tmp;
	        heapifyDown(child);
		}
	}

	//data template
	std::vector<T> heap;
};

