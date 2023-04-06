#pragma once
#include <exception>

template<typename ElementType>

class DynamicArray
{
private:
	ElementType* elems;
	int dim;
	int capacity;

	void resize() {
		ElementType* elemsNou = new ElementType[2 * capacity];

		for (int i = 0; i < dim; i++)
			elemsNou[i] = elems[i];

		capacity *= 2;

		delete[] elems;

		elems = elemsNou;
	}
public:
	
	DynamicArray(int capacity) {
		this->dim = 0;
		this->capacity = capacity;
		this->elems = new ElementType[capacity];
	}
	
	DynamicArray(const DynamicArray& arrayToCopy)
	{
		this->dim = arrayToCopy.dim;
		this->capacity = arrayToCopy.capacity;

		this->elems = new ElementType[this->capacity];

		for (int i = 0; i < this->dim; i++)
			this->elems[i] = arrayToCopy.elems[i];
	}

	DynamicArray& operator=(const DynamicArray& arrayToCopy)
	{
		delete[] elems;
		this->dim = arrayToCopy.dim;
		this->capacity = arrayToCopy.capacity;

		this->elems = new ElementType[this->capacity];

		for (int i = 0; i < this->dim; i++)
			this->elems[i] = arrayToCopy.elems[i];

		return *this;
	}

	DynamicArray() {
		this->dim = 0;
		this->capacity = 2;
		this->elems = new ElementType[2];
	}

	void push_back(ElementType e) {
		if (this->capacity == this->dim) {
			resize();
		}
		this->elems[this->dim] = e;
		this->dim += 1;
	}
	
	void remove_element(int index) {
		//ElementType deleted = elems[index];
		for (int i = index; i < dim - 1; i++)
			elems[i] = elems[i + 1];
		dim -= 1;
		//return deleted;
	}

	ElementType& get(int index) {
		return elems[index];
	}

	int size() {
		return this->dim;
	}

	~DynamicArray() {
		delete[] elems;
	}

	ElementType& operator[](int poz) {
		//if (poz < 0 || poz >= dim) {
			//throw std::exception("Index out of bounds!");
		//}
		return elems[poz];
	}
};

