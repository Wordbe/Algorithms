#include <cstdio>

int a[1001];

void printArray(int n){
    for (int i=0; i<n; ++i){
        printf("%d ", a[i]);
    }
    printf("\n");
}

void _swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

// ==============================================================
//  O(N^2) Sort
// ==============================================================

void bubbleSort(int n){
    for (int last = n; last > 0; --last){
        for (int i = 0; i < last - 1; ++i){
            // Like a bubble
            if (a[i] > a[i+1]) _swap(a[i], a[i+1]);
        }
    }
}

// 최댓값 뽑고, 맨뒤로
void selectionSort(int n){
    for (int last = n; last > 0; --last){
        // Get a maximum value.
        int maxidx = 0;
        for (int i = 1; i < last; ++i){
            if (a[maxidx] < a[i]) maxidx = i;
        }
        // Swap between 'max' and 'last' in the array.
        _swap(a[maxidx], a[last - 1]);
    }
}

// 하나 뽑고, 적당한 위치에 삽입
void insertionSort(int n){
    for (int i = 1; i < n; ++i){
        
        // Find a proper insertion loaction
        int insert_loc = 0;
        for (; insert_loc < i; ++insert_loc){
            if (a[i] < a[insert_loc]) break;
        }

        // Insert (뒤로 이동 후 insert)
        int temp = a[i];
        for (int j = i; j > insert_loc; --j){
            a[j] = a[j - 1];
        }
        a[insert_loc] = temp;
    }
}

// ==============================================================
//  O(NlogN) Sort
// ==============================================================



// ==============================================================
//  O(cN) Sort
// ==============================================================


int main() {
    int n;
    scanf("%d", &n);
    for (int i=0; i<n; ++i)
        scanf("%d", &a[i]);
    
    // bubbleSort(n);
    // selectionSort(n);
    // insertionSort(n);
    printArray(n);
    return 0;
}