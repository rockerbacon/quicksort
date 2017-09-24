/*
General purpose static list
	Vitor Andrade dos Santos, 2016
*/

#ifndef _LAB309_ADT_STATIC_LIST_H_
#define _LAB309_ADT_STATIC_LIST_H_

#include <iostream>
#include <stdexcept>
#include "Lab309_ADT_StaticContainer.h"

namespace Lab309 {

	template<typename dataType>
	class SList : public SContainer<dataType> {

		template<typename any> friend class SList;
		template<typename any> friend class LList;

		public:
			//constructors and destructor
			SList (void) = default;
			explicit SList (size_t size) throw (std::invalid_argument, std::bad_alloc) : SContainer<dataType>(size) {}
			SList (const SList<dataType> &list) throw (std::bad_alloc) : SContainer<dataType>(list) {}
			SList (SList<dataType> &&list) : SContainer<dataType>(list) {}
			SList (const std::initializer_list<dataType> &list) throw (std::invalid_argument, std::bad_alloc) : SContainer<dataType>(list) {}

			//getters
			size_t getIndex (dataType data) const throw (std::invalid_argument);

			//methods
			bool contains (const SList<dataType> &list) const;
			bool contains (dataType data) const;

			void add (size_t index, const SList<dataType> &list) throw (std::out_of_range, std::length_error);
			void add (size_t index, dataType data) throw (std::out_of_range, std::length_error);

			SList<dataType> removeIndex (SList<size_t> &&indexList) throw (std::bad_alloc, std::out_of_range);
			dataType removeIndex (size_t index) throw (std::out_of_range);
			size_t remove (const SList<dataType> &list) throw (std::invalid_argument);
			void remove (dataType data) throw (std::invalid_argument);

			void sort (void);	//heapsort

			inline std::ostream& toStream (std::ostream &stream) const;

			//operators
			//assignment
			SList<dataType>& operator= (const SList<dataType> &list) throw (std::bad_alloc);
			SList<dataType>& operator= (SList<dataType> &&list);

			//array subscripting operator
			dataType& operator[] (size_t index) const throw (std::out_of_range);

	};

}

/*IMPLEMENTATION*/
/*GETTERS*/
template<typename dataType>
size_t Lab309::SList<dataType>::getIndex (dataType data) const throw (std::invalid_argument) {

	size_t index;

	try {
		index = 0;
		while (this->data[index] != data) {
			index++;
			if (index == this->length) {
				throw std::invalid_argument ("Error on SList<dataType>::getIndex(dataType data): list does not contain data");
			}
		}
		return index;
	} catch (std::invalid_argument &error) {
		throw error;
	}

}

/*METHODS*/
template<typename dataType>
bool Lab309::SList<dataType>::contains (const SList<dataType> &list) const {
	size_t i, j;

	if (list.length > this->length) {
		return false;
	}

	for (i = 0; i <= this->length-list.length; i++) {
		j = 0;
		while (this->data[i+j] == list.data[j]) {
			j++;
			if (j == list.length) {
				return true;
			}
		}
	}

	return false;
}

template<typename dataType>
bool Lab309::SList<dataType>::contains (dataType data) const {
	size_t i;

	for (i = 0; i < this->length; i++) {
		if (this->data[i] == data) {
			return true;
		}
	}

	return false;
}

template<typename dataType>
void Lab309::SList<dataType>::add (size_t index, dataType data) throw (std::out_of_range, std::length_error) {
	size_t i;

	try {
		if (this->length == this->size) {
			throw std::length_error("Error on SList<dataType>::add(size_t index, dataType data): this list doesn't have the required space to receive data");
		} else if (index > this->length) {
			throw std::out_of_range ("Error on SList<dataType>::add(size_t index, dataType data): index exceeds this list's boundaries");
		}

		//open space to add data
		if (this->length > 0) {
			for (i = this->length-1; i >= index; i--) {
				this->data[i+1] = this->data[i];
				if (i == 0) {
					break;
				}
			}
		}

		this->data[index] = data;

		this->length++;

	} catch (std::out_of_range &error) {
		throw error;
	} catch (std::length_error &error) {
		throw error;
	}
}

template<typename dataType>
void Lab309::SList<dataType>::add (size_t index, const SList<dataType> &list) throw (std::out_of_range, std::length_error) {
	size_t i;

	try {
		if (this->length+list.length > this->size) {
			throw std::length_error("Error on SList<dataType>::add(size_t index, SList<dataType> &list): this list doesn't have the required space to receive list");
		} else if (index > this->length) {
			throw std::out_of_range ("Error on SList<dataType>::add(size_t index, SList<dataType> &list): index exceeds this list's boundaries");
		}

		//open space to add data
		if (this->length > 0) {
			for (i = this->length-1; i >= index; i--) {
				this->data[i+list.length] = this->data[i];
				if (i == 0) {
					break;
				}
			}
		}

		for (i = 0; i < list.length; i++, index++) {
			this->data[index] = list.data[i];
		}

		this->length += list.length;

	} catch (std::out_of_range &error) {
		throw error;
	} catch (std::length_error &error) {
		throw error;
	}
}

template<typename dataType>
Lab309::SList<dataType> Lab309::SList<dataType>::removeIndex (SList<size_t> &&indexList) throw (std::bad_alloc, std::out_of_range) {
	dataType removed;
	size_t i, j, k;

	try {
		SList<dataType> removed(indexList.size);	//possible std::bad_alloc throw

		indexList.sort();
		k = indexList.data[0];
		for (i = 0; i < indexList.length-1; i++) {
			removed.add(removed.length, this->data[indexList.data[i]]);
			for (j = indexList.data[i]+1; j < indexList.data[i+1]; j++, k++) {
				this->data[k] = this->data[j];
			}
		}
		removed.add(removed.length, this->data[indexList.data[i]]);
		for (j = indexList.data[i]+1; j < this->length-1; j++, k++) {
			this->data[k] = this->data[j];
		}

		this->length -= indexList.length;
		return removed;
	} catch (std::out_of_range &error) {
		throw error;
	}
}

template<typename dataType>
dataType Lab309::SList<dataType>::removeIndex (size_t index) throw (std::out_of_range) {
	dataType removed;
	size_t i;

	try {
		if (index >= this->length) {
			throw std::out_of_range("Error on SList<dataType>::removeIndex(size_t index): index exceeds list's boundaries");
		}
		removed = this->data[index];
		for (i = index; i < this->length-1; i++) {
			this->data[i] = this->data[i+1];
		}
		this->length--;

		return removed;
	} catch (std::out_of_range &error) {
		throw error;
	}
}

template<typename dataType>
size_t Lab309::SList<dataType>::remove (const SList<dataType> &list) throw (std::invalid_argument) {
	size_t i, j;

	try {
		if (this->length < list.length) {
			throw std::invalid_argument("Error on SList<dataType>::remove(const SList<dataType> &list): list is larger than this list");
		}

		//find location where data to be removed is
		for (i = 0; i <= this->length-list.length; i++) {
			j = 0;
			while (this->data[i+j] == list.data[j]) {
				j++;
				if (j == list.length) {
					goto REMOVE;
				}
			}
		}

		throw std::invalid_argument("Error on SList<dataType>::remove(const SList<dataType> &list): this list does not contain list");

		REMOVE:
		for (j += i; j < this->length; j++) {
			this->data[j-list.length] = this->data[j];
		}
		this->length -= list.length;

		return i;
	} catch (std::invalid_argument &error) {
		throw error;
	}
}

template<typename dataType>
void Lab309::SList<dataType>::remove (dataType data) throw (std::invalid_argument) {
	try {
		this->removeIndex(this->getIndex(data));	//possible std::invalid_argument throw
	} catch (std::invalid_argument &error) {
		throw error;
	}
}

template<typename dataType>
void Lab309::SList<dataType>::sort (void) {
	size_t child, father, auxIndex;
	dataType aux;

	if (this->length < 2) {
		return;
	}

	//heapify data
	auxIndex = 1;
	for (child = 1; child < this->length; child = auxIndex) {
		father = (child-1)/2;
		auxIndex++;
		while (this->data[child] > this->data[father] && child > 0) {
			aux = this->data[child];
			this->data[child] = this->data[father];
			this->data[father] = aux;

			child = father;
			father = (child-1)/2;
		}
	}

	//heapsort
	for (auxIndex = this->length-1; auxIndex > 0; auxIndex--) {
		aux = this->data[0];
		this->data[0] = this->data[auxIndex];
		this->data[auxIndex] = aux;

		//shift-up
		father = 0;
		child = 1;
		while (child < auxIndex) {
			aux = this->data[child];
			if (child+1 < auxIndex) {
				if (this->data[child+1] > aux) {
					child++;
					aux = this->data[child];
				}
			}
			if (this->data[father] >= aux) {
				break;
			}

			this->data[child] = this->data[father];
			this->data[father] = aux;

			father = child;
			child = 2*father+1;
		}
	}
}

template<typename dataType>
std::ostream& Lab309::SList<dataType>::toStream (std::ostream &stream) const {
	size_t i;
	stream << '[';
	for (i = 0; i < this->length-1; i++) {
		stream << this->data[i] << ", ";
	}
	stream << this->data[i] << ']';

	return stream;
}

/*OPERATORS*/
//ASSIGNMENT
template<typename dataType>
Lab309::SList<dataType>& Lab309::SList<dataType>::operator= (const SList<dataType> &list) throw (std::bad_alloc) {
	dataType *dataAux;

	try {
		SList<dataType> copy(list);	//possible std::bad_alloc throw

		dataAux = this->data;
		this->data = copy.data;
		copy.data = dataAux;

		this->length = copy.length;
		this->size = copy.size;

		return *this;
	} catch (std::bad_alloc &error) {
		throw error;
	}
}

template<typename dataType>
Lab309::SList<dataType>& Lab309::SList<dataType>::operator= (SList<dataType> &&list) {
	dataType *dataAux;

	dataAux = this->data;
	this->data = list.data;
	list.data = dataAux;

	this->length = list.length;
	this->size = list.size;

	return *this;
}

//ARRAY SUBSCRIPTING
template<typename dataType>
dataType& Lab309::SList<dataType>::operator[] (size_t index) const throw (std::out_of_range) {
	try {
		if (index >= this->length) {
			throw std::out_of_range("Error on SList<dataType>::operator[] (size_t index): index exceeds list's boundaries");
		}
		return this->data[index];
	} catch (std::out_of_range &error) {
		throw error;
	}
}

#endif
