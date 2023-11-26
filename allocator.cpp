#include <iostream>
#include <map>

template <typename T>
struct MyAllocator {
	using value_type = T;

	MyAllocator();

	template <typename U>
	MyAllocator(const MyAllocator<U>&);

	T* allocate (std::size_t n);
	
	void deallocate (T* p, std::size_t n);
};

template <typename T>
MyAllocator<T>::MyAllocator() {
}

template <typename T>
template <typename U>
MyAllocator<T>::MyAllocator(const MyAllocator<U>& ) {
	// should we make a copy of the rhs.m_buffer ?
	// No, we should not!
}

template <typename T>
T* MyAllocator<T>::allocate (std::size_t n) {
	auto p = std::malloc(n * sizeof(T));
	if (!p) {
		throw std::bad_alloc();
    }

	return reinterpret_cast<T *>(p);
}

template <typename T>
void MyAllocator<T>::deallocate (T* p, std::size_t ) {
	std::free(p);
}

template <class T, class U>
constexpr bool operator== (const MyAllocator<T>&, const MyAllocator<U>&) noexcept {
	return false;
}

template <class T, class U>
constexpr bool operator!= (const MyAllocator<T>&, const MyAllocator<U>&) noexcept {
	return false;
}

const std::array<int, 10> factorials = {0, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int main() {

    std::map<int, int> map_1;
    for (size_t i = 0; i < 10; ++i) {
        map_1[i] = factorials[i];
    }

    std::map<int, int, MyAllocator<std::pair<const int, int>>> map_2;
    for (size_t i = 0; i < 10; ++i) {
        map_2[i] = factorials[i];
    }



    return 0;
}