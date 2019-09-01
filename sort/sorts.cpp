#include <cstdio>

int a[10000001];
int asize;
void printArray(int n=asize){
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
            if (a[i] > a[i+1]) _swap(a[i], a[i+1]); // Like a bubble
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

// 하나 뽑고, 적당한 위치에 삽입 / 잘 정렬되어 있을 경우 O(N)까지 성능이 좋아짐
void insertionSort(int n){
    for (int i = 1; i < n; ++i){
        
        // Find a proper insertion loaction
        int insert_loc = 0;
        for (; insert_loc < i; ++insert_loc){
            if (a[i] < a[insert_loc]) break;
        }

        // Insert (삽입할 위치 뒤의 원소들을 모두 한 칸 씩 뒤로 이동 후 삽입)
        int key = a[i]; // 삽입될 대상
        for (int j = i; j > insert_loc; --j){
            a[j] = a[j - 1];
        }
        a[insert_loc] = key;
    }
}

/*
    구간(Gap)을 나눈 후 구간별 insertion sort 한다.
    평균: O(N^1.3), 최악: O(N^2), 최선: O(N)
*/
void shellSort(int n, int k=2){
    for (int gap = n / k; gap > 0; gap /= k){ // for each gap
        if (gap % 2 == 0) ++gap;
        for (int first=0; first < gap; ++first){ // for each group
            
            // Insertion Sort
            for (int i = first + gap; i < n; i += gap){
                int key = a[i];
                // 끝에서 부터 삽입할 위치를 찾고, 못찾으면 한칸 뒤로 땡기고, 찾으면 삽입.
                int j = i;
                for (; j > first && a[j - gap] > key; j -= gap)
                    a[j] = a[j - gap];
                a[j] = key;
            }
        }
    }
}

// ==============================================================
//  O(NlogN) Sort
// ==============================================================

// Memory space for merge sort
int tmp[1000001];

// Merge a[start...mid] and a[mid+1...end] in nondecreasing order.
void merge(int start, int mid, int end){
    // Sort
    int i = start; // Index for a[start...mid]
    int j = mid + 1; // Index for a[mid+1...end]
    int k = 0; // Index for tmp[]
    while(i <= mid && j <= end){
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while(i <= mid) tmp[k++] = a[i++];
    while(j <= end) tmp[k++] = a[j++];

    // Copy tmp[] to a[]
    k = 0;
    while(start <= end) a[start++] = tmp[k++];
}

/*
    최악, 평균 둘 다 O(NlogN)
    하지만 temp 메모리를 일시적으로 많이 사용함.
    a[start...end]을 정렬
*/
void mergeSort(int s, int e){
    if (s >= e) return;
    int mid = (s + e) / 2;
    // O(logN)
    mergeSort(s, mid); 
    mergeSort(mid + 1, e);
    // O(N)
    merge(s, mid, e);
}

// -------------------------------------------------------------------------

int partition(int start, int end){
    int pivot = a[end]; // Set last value as a pivot.
    int i = start - 1; // 왼쪽구역과 오른쪽구역을 나누는 index
    for (int j = start; j < end; ++j){
        if (a[j] <= pivot) _swap(a[++i], a[j]);
    }
    _swap(a[i + 1], a[end]);
    return i + 1;
}

/*
    a[start...end]를 정렬
    quick sort는 불안정 정렬, 최악은 O(N^2), 평균은 O(NlogN)
*/
void quickSort(int s, int e){
    if (s >= e) return;
    int pivot_idx = partition(s, e); // O(N)
    // O(logN)
    quickSort(s, pivot_idx - 1);
    quickSort(pivot_idx + 1, e);
}

// -------------------------------------------------------------------------

void heapify(int k, int n){
    int left = 2 * k, right = 2 * k + 1, larger;
    if (right <= n){ // a[k] has two children
        if (a[left] > a[right]) larger = left;
        else larger = right;
    }
    else if (left <= n){ // a[k] has only one left child
        larger = left;
    }
    else return; // a[k] is a leaf

    if (a[larger] > a[k]){
        _swap(a[larger], a[k]);
        heapify(larger, n);
    }
}

void buildHeap(int n){
    for (int i = n / 2; i > 0; --i){
        heapify(i, n);
    }
}

void heapSort(int n){
    buildHeap(n);
    for (int i = n; i > 0; --i){
        _swap(a[0], a[i]);
        heapify(0, i - 1);
    }
}

// ==============================================================
//  O(N) Sort
// ==============================================================

void countingSort_fewMemory(int max_num, int arr_size){
    scanf("%d", &asize);
    int num;
    for (int i=0; i<asize; ++i){
        scanf("%d", &num);
        ++counts[num];
    }

    for (int i=1; i<MAX_NUM; ++i){
        for (int j=0; j<counts[i]; ++j)
            printf("%d ", i);
    }
    printf("\n");
}


#define MAX_COUNT 10001
int result[10000001];
int counts[MAX_COUNT];
void countingSort(int n){
    // 전역변수로 이미 0으로 초기화 되어 있음.
    for (int i = 0; i < MAX_COUNT; ++i){
        counts[i] = 0;
    }

    // 원소가 몇 개가 있는지 센다.
    for (int i = 0; i < n; ++i){
        ++counts[a[i]];
    }

    // counts 배열을 누적한다.
    for (int i = 1; i < MAX_COUNT; ++i){
        counts[i] += counts[i - 1];
    }

    // result 배열에 counting sort 결과를 저장한다.
    for (int i = n - 1; i >= 0; --i){
        result[counts[a[i]]--] = a[i];
    }

    for (int i = 0; i<n; ++i){
        a[i] = result[i];
    }
}

// -------------------------------------------------------------------------

void getMax(int n){
    int mx = a[0];
    for (int i=1; i<n; ++i){
        if (a[i] > mx) mx = a[i];
    }
    return mx;
}

/*
    최대 k 자릿수가 원소인 a[0...n-1]을 정렬
    가장 낮은 자릿수를 0번째라고 지정
*/

void radixSort(int n){
    int mx = getMax(n);

    for (int exp = 1; mx / exp > 0; exp *= 10){
        countingSort(n);
    }
}

int main() {
    scanf("%d", &asize);
    for (int i=0; i<asize; ++i)
        scanf("%d", &a[i]);
    
    // bubbleSort(asize);
    // selectionSort(asize);
    // insertionSort(asize);
    // mergeSort(0, asize - 1);
    // quickSort(0, asize - 1);
    // shellSort(asize);
    // heapSort(asize);
    // countingSort(asize);
    // radixSort(asize);
    printArray(asize);
    return 0;
}