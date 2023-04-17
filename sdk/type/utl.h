#pragma once

template <typename T>
struct CUtlMemory {
	T* memory;
	int allocCount;
	int growSize;
};

template <typename T>
struct CUtlVector {
	CUtlMemory<T> memory;
	int size;
	T* elements;
};