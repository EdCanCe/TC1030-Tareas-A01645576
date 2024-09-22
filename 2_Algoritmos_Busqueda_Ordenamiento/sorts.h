#ifndef SORTS_H_
#define SORTS_H_
#include<iostream>
#include<vector>

template <class T>
class Sorts{
    private:
        void swap(std::vector<T>&, int, int);
        void copy(std::vector<T>&, std::vector<T>&, int, int);
	    void arr(std::vector<T>&, std::vector<T>&, int, int, int);
	    void divide(std::vector<T>&, std::vector<T>&, int, int);
    public:
        void ordenaSeleccion(std::vector<T>&);
        void ordenaBurbuja(std::vector<T>&);
        void ordenaMerge(std::vector<T>&);
        int busqSecuencial(std::vector<T> &, T);
        int busqBinaria(std::vector<T>&, T);
};

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &v){
    for(int i=0; i<v.size(); i++){
		int l=i;
		for(int j=i+1; j<v.size(); j++){
			if(v[j]<v[l]) l=j;
		}
		swap(v, i, l);
	}
}

template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &v){
    for(int i=0; i<v.size(); i++){
		for(int j=0; j<v.size()-i-1; j++){
			if(v[j]>v[j+1]) swap(v, j, j+1);
		}
	}
}

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &v){
	std::vector<T> copia(v.size());
	divide(v, copia, 0, v.size()-1);
}

template <class T>
int Sorts<T>::busqSecuencial(std::vector<T> &v, T dato){
    for(int i=0; i<v.size(); i++){
        if(v[i]==dato) return i;
    }
    return -1;
}

template <class T>
int Sorts<T>::busqBinaria(std::vector<T> &v, T dato){
    int low=0, high=v.size()-1, mid;
	while(low<=high){
		mid=(low+high)/2;
		if(v[mid]==dato) return mid;
		if(v[mid]<dato) low=mid+1;
		else high=mid-1;
	}
    return -1;
}

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T l = v[i];
	v[i] = v[j];
	v[j] = l;
}

template <class T>
void Sorts<T>::copy(std::vector<T> &A, std::vector<T> &B, int low, int high){
    for(int i=low; i<=high; i++){
		A[i]=B[i];
	}
}

template <class T>
void Sorts<T>::arr(std::vector<T> &A, std::vector<T>&B, int low, int mid, int high){
    int i=low, j=mid+1, l=low;
	while(i<=mid && j<=high) {
		if(A[i]<A[j]){
			B[l]=A[i];
			i++;
		}else{
			B[l]=A[j];
			j++;
		}
		l++;
	}
	if(i>mid){
		for(;j<=high;j++) {
			B[l++] = A[j];
		}
	}else{
		for(;i<=mid;i++) {
			B[l++]=A[i];
		}
	}
}

template <class T>
void Sorts<T>::divide(std::vector<T> &A, std::vector<T> &B, int low, int high){
    if(high-low<1){
		return;
	}
	int mid=(low+high)/2;
	divide(A, B, low, mid);
	divide(A, B, mid+1, high);
	arr(A, B, low, mid, high);
	copy(A, B, low, high);
}

#endif