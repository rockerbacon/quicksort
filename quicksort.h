#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

#include "Lab309_ADT_StaticList.h"
#include <iostream>

//the value for the pivotBias is in the interval (0, 1). The closer the value is to 0 the closer the pivot will be to the leftmost element, the closer the value is to 1 the closer the pivot will be to the rightmost element
template <typename dataType>
void quicksort (Lab309::SList<dataType> &list, float pivotBias);

/*IMPLEMENTATION*/
template <typename dataType>
void quicksort_rec (Lab309::SList<dataType> &list, float pivotBias, size_t beginning, size_t end, int &step) {
	if (end-beginning == 0) {
		return;
	}

	size_t pivot;
	size_t i, j;
	dataType temp;

	//std::cout << "Partition from " << beginning << " to " << end << std::endl;	//debug

	pivot = (size_t)pivotBias*(end-beginning)+beginning;
	i = beginning;
	j = end;
	while (true) {
		while (list[i] <= list[pivot] && i != pivot) {
			i++;
		}
		while (list[j] >= list[pivot] && j != pivot) {
			j--;
		}
		
		if (i != j) {
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;

			if (i == pivot) {
				pivot = j;
			} else if (j == pivot) {
				pivot = i;
			}
		} else {
			break;
		}
	}

	std::cout << step << '.' << list << std::endl;
	step++;

	if (pivot - 1 < pivot && pivot - 1 >= beginning) {
		quicksort_rec(list, pivotBias, beginning, pivot-1, step);
	}
	if (pivot + 1 <= end) {
		quicksort_rec(list, pivotBias, pivot+1, end, step);
	}
}

template <typename dataType>
void quicksort (Lab309::SList<dataType> &list, float pivotBias) {
	if (pivotBias < 0 || pivotBias > 1 || list.getLength() < 2) {
		return;
	}
	int step = 1;
	quicksort_rec(list, pivotBias, 0, list.getLength()-1, step); 
}

#endif
