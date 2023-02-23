#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <stdexcept>

template <typename T, typename PComparator = std::less<T> >
class Heap {
public:
    /**
     * @brief Construct a new Heap object
     * 
     * @param m ary-ness of heap tree (default to 2)
     * @param c binary predicate function/functor that takes two items
     *          as an argument and returns a bool if the first argument has
     *          priority over the second.
     */
    Heap(int m = 2, PComparator c = PComparator()) : m_arity(m), comp(c) {}

    /**
    * @brief Destroy the Heap object
    * 
    */
    ~Heap() {}

    /**
     * @brief Push an item to the heap
     * 
     * @param item item to heap
     */
    void push(const T& item) {
        heap.push_back(item);
        heapify_up(heap.size() - 1);
    }

    /**
     * @brief Returns the top (priority) item
     * 
     * @return T const& top priority item
     * @throw std::underflow_error if the heap is empty
     */
    T const& top() const {
        if (empty()) {
            throw std::underflow_error("Heap is empty.");
        }
        return heap.front();
    }

    /**
     * @brief Remove the top priority item
     * 
     * @throw std::underflow_error if the heap is empty
     */
    void pop() {
        if (empty()) {
            throw std::underflow_error("Heap is empty.");
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
    }

    /**
     * @brief Returns true if the heap is empty
     * 
     */
    bool empty() const {
        return heap.empty();
    }

    /**
     * @brief Returns size of the heap
     * 
     */
    size_t size() const {
        return heap.size();
    }

private:
    std::vector<T> heap;
    int m_arity;
    PComparator comp;

    void heapify_up(int i) {
        while (i > 0) {
            int parent = (i - 1) / m_arity;
            if (comp(heap[i], heap[parent])) {
                std::swap(heap[i], heap[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }

    void heapify_down(int i) {
        while (true) {
            int child_min = i * m_arity + 1;
            if ((unsigned)child_min >= heap.size()) {
                break;
            }
            int child_max = std::min(child_min + m_arity - 1, int(heap.size()) - 1);
            int min_index = i;
            for (int j = child_min; j <= child_max; j++) {
                if (comp(heap[j], heap[min_index])) {
                    min_index = j;
                }
            }
            if (min_index != i) {
                std::swap(heap[i], heap[min_index]);
                i = min_index;
            } else {
                break;
            }
        }
    }
};
#endif
