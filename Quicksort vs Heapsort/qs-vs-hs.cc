

#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <stdio.h>
#include <memory.h>
#include <iomanip>


using namespace std;
using namespace chrono;

double pasos = 0.00;
double pasosRandomQuickSort = 0.00;
double pasosRandomHeapSort = 0.00;
double pasosSortedQuickSort = 0.00;
double pasosSortedHeapSort = 0.00;
double pasosReverseQuickSort = 0.00;
double pasosReverseHeapSort = 0.00;

//--------------------------------------------------------------
// Middle Quick Sort
void middle_QuickSort(int * v, long left, long right){
long i,j;
int pivot; 
    if (left<right){
        pasos++;
        i=left; j=right;
        pivot=v[(i+j)/2];
        do{
            pasos++;
            while (v[i]<pivot){
                i++;
                pasos++;
            } 
            while (v[j]>pivot) {
                j--;
                pasos++;
            };
            if (i<=j){ 
                swap(v[i], v[j]);
                i++;
                j--;
            }
        }while (i<=j);
        if (left < j)  middle_QuickSort(v,left,j);
        if (i < right) middle_QuickSort(v,i,right);
    }
}

//--------------------------------------------------------------                
//HEAPSORT
// Procedure sink used by Heapsort algorith
// Sink an element (indexed by i) in a tree to keep the heap property. n is the size of the heap. 

void sink(int *v, size_t n, size_t i)
{

size_t largest;
size_t l, r; //left and right child

do{
    pasos++;
    largest = i;  // Initialize largest as root
    l = 2*i + 1;  // In a heap, left child (if exists) of node i is at (2*i + 1) position
    r = 2*i + 2;  // right child (if exists) of node i is at (2*i + 2) position
 
    // If left child exists and left child is larger than root
    if (l < n && v[l] > v[largest]) {
    //Note that l>=n means that  root (or largest) node has not left child 
        largest = l;
    }
 
    // If right child exists and right child is larger than largest so far 
    if (r < n && v[r] > v[largest]){
        largest = r;
    }
 
    // If largest is still root the process is done
    if (largest == i) {
        break;
    }
    
    // If not (largest has changed), swap new largest with current node i and repeat the process with childs. 
    swap(v[i], v[largest]);
    i=largest;  
   } while (true);
}
 
//--------------------------------------------------------------                
// Heapsort algorithm 
void heapSort(int *v, size_t n)
{
    // Build heap with the input array
    for (size_t i = n / 2 - 1; i >= 0; i--){
        pasos++;
        sink(v, n, i);
        if (i==0) break; //as size_t is unsigned type

    }   
    // Now we have a HEAP on the input array, let's take this to sort the array. 
    // One by one extract the first element, which is the largest, swap it with the last element of the vector and rebuild heap by sinking the new placed element on the begin of vector.  
    for (size_t i=n-1; i>0; i--)
    {
        pasos++;
        // Move current root to the end.
        swap(v[0], v[i]);
        //Now largest element is at the end but do not know if the first element is well placed, so sink process is required
        sink(v, i, 0);
    }
}

int main(void){

    int * vectorQuickSort;
    int * vectorHeapSort;
    int * vectorQuickSortInverso;
    int * vectorHeapSortInverso;
    size_t size;

    srand(getpid());

    cout << "QUICKSORT VERSUS HEAPSORT"
        << endl
        << "Average processing Msteps (millions of program steps)"
        << endl
        << "Number of samples (arrays of integer): 30"
        << endl
        << endl
        << "\t       RANDOM ARRAYS \t         SORTED ARRAYS \t     REVERSE SORTED ARRAYS"
        << endl
        << " \t    --------------------    --------------------    -------------------------" 
        << endl
        << "Size \t    Quicksort   Heapsort   Quicksort    Heapsort    Quicksort    Heapsort"
        << endl
        << "============================================================================================="
        << endl;
    for (int exp = 15; exp <= 22; exp++){

        size = (size_t) powl(2,exp);
        
        if (vectorQuickSort){
            cout << size << "\t     " << std::flush;
           // double media = 0;
           

             for(size_t i = 0; i < 30; i++ ){
                vectorQuickSort = new int [size];
                vectorHeapSort = new int [size];
                vectorQuickSortInverso = new int [size];
                vectorHeapSortInverso = new int [size];
                for (size_t j = 0; j < size; j++) {
                    vectorQuickSort[j] = rand();
            
                 }
                for (size_t j = 0; j < size; j++) {
                    vectorHeapSort[j] = vectorQuickSort[j];
                    //cout << vOrdenado[i];
                }
                //memcopy(&vectorQuickSort,&vectorHeapSort,sizeof(vectorQuickSort));

// AQUI RANDOM ---------------------------------------------------
                middle_QuickSort(vectorQuickSort,0,size-1);
                pasosRandomQuickSort = pasosRandomQuickSort + pasos;
                pasos = 0;
                heapSort(vectorHeapSort,size);
                pasosRandomHeapSort = pasosRandomHeapSort + pasos;
                pasos = 0;


// AQUI ORDENADOS ------------------------------------------------
                middle_QuickSort(vectorQuickSort,0,size-1);
                pasosSortedQuickSort = pasosSortedQuickSort + pasos;
                pasos = 0;
                heapSort(vectorHeapSort,size);
                pasosSortedHeapSort = pasosSortedHeapSort + pasos;
                pasos = 0;



                for (size_t j = 0; j < size; j++){
                    vectorHeapSortInverso[size-j] = vectorHeapSort[j];
                    vectorQuickSortInverso[size-j] = vectorQuickSort[j];
                }
 

// AQUI ORDENADO INVESO ------------------------------------------------
                middle_QuickSort(vectorQuickSortInverso,0,size-1);
                pasosReverseQuickSort = pasosReverseQuickSort + pasos;
                pasos = 0;
                heapSort(vectorHeapSortInverso,size);
                pasosReverseHeapSort = pasosReverseHeapSort + pasos;
                pasos = 0;

                delete []vectorQuickSort; 
                delete []vectorHeapSort; 
                delete []vectorQuickSortInverso; 
                delete []vectorHeapSortInverso;  
    
            }
            pasosRandomQuickSort = pasosRandomQuickSort/30;
            pasosRandomQuickSort = pasosRandomQuickSort/1000000;
            pasosRandomHeapSort = pasosRandomHeapSort/30;
            pasosRandomHeapSort = pasosRandomHeapSort/1000000;

            pasosSortedQuickSort = pasosSortedQuickSort/30;
            pasosSortedQuickSort = pasosSortedQuickSort/1000000;
            pasosSortedHeapSort = pasosSortedHeapSort/30;
            pasosSortedHeapSort = pasosSortedHeapSort/1000000;

            pasosReverseQuickSort = pasosReverseQuickSort/30;
            pasosReverseQuickSort = pasosReverseQuickSort/1000000;
            pasosReverseHeapSort = pasosReverseHeapSort/30;
            pasosReverseHeapSort = pasosReverseHeapSort/1000000;
            cout << fixed << setprecision(3) << pasosRandomQuickSort 
            << "\t" 
            << fixed << setprecision(3) 
            << pasosRandomHeapSort 
            << "\t   "
            << fixed << setprecision(3)
            << pasosSortedQuickSort 
            << "\t" 
            << fixed << setprecision(3)
            << pasosSortedHeapSort 
            << "\t    " 
            << fixed << setprecision(3)
            << pasosReverseQuickSort 
            << "\t " 
            << fixed << setprecision(3)
            << pasosReverseHeapSort
            << endl;


        }
        else {
            cerr << "Error, not enough memory!" << endl;
            exit (1);  
        }
    }
}   
