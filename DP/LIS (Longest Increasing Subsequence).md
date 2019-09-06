### LIS (Longest Increasing Subsequence)



> 수열 안에 있는 증가 하는 부분 수열 중 가장 긴 것을 찾는 문제

#### Idea1

a[] = {3, 2, 1, **7**, **5**, **4**, 2, **6**}

첫번째 원소 3을 기준으로, 그 다음 가능한 7 5 4 6 중 다시 재귀적으로 LIS를 뽑습니다.



```c++
#include <vector>
#include <algorithm>
using namespace std;
/*
	LIS의 길이를 반환
*/
int lis(const vector<int>& A) {
	if (A.empty()) return 0;
	int ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		vector<int> B;
		for (int j = i + 1; j < A.size(); ++j) {
			if (A[i] < A[j]) B.emplace_back(A[j]);
		}
		ret = max(ret, 1 + lis(B));
	}
	return ret;
}
```







#### Idea2 (입력 바꾸기) O(N<sup>2</sup>)

메모이제이션을 적용하여 중복되는 문제를 해결해봅시다.



**lis(start) : a[start]에서 시작하는 LIS(부분 증가수열) 중 최대 길이**

라고 문제를 재정의해보면, 

우리는 입력을 수열로 받지 않아도 되고, 따라서 메모이제이션이 수월해집니다.



```c++
int N;
int dp[100], a[100];
/*
	총 N개의 부분 문제를 갖고, 한 문제 마다 반복문 O(N)
	따라서 O(N^2)
*/
int lis2(int start) {
	int& ret = dp[start];
	if (ret) return ret;
	
	// a[start]는 포함하므로 길이는 적어도 1이상이다.
	ret = 1;
	for (int next = start + 1; next < N; ++next) {
		if (a[start] < a[next])
			ret = max(ret, lis2(next) + 1);
	}
	return ret;
}
```





#### Idea3 O(NlogN)



생각해내기 쉽지 않은 아이디어 입니다만, 이렇게 생각하면 구현은 쉽습니다.

**dp[i] : 길이가 i인 LIS을 만들 수 있는 마지막 원소 중 가장 작은 값**

따라서, dp의 크기가 곧 LIS의 길이 이고, 처음에는 빈 배열로 시작합니다.



a[] = {3, 2, 5, 2, 3, 1, 4}로 확인해 봅시다.



* (1) **(dp[]의 마지막 원소)**와 (2)** (a[]의 원소)**를 비교하여

  ​	(1) < (2) 이면 dp[]에 (2)를 추가합니다.

  ​	그렇지 않으면 dp[]에서 (2)가 들어갈 장소(lower_bound)를 찾아서 (2)를 대입합니다.



순서대로 dp[]를 확인해보면,

3 << 처음에는 그냥 넣어줍니다.

2 << "1자리"에 만들 수 있는 가장 마지막 원소는 3보다는 2가더 유리합니다.

2 5 << 2<5이므로 뒤에 넣어줍니다.

2 5 << lower_bound(2)가 인덱스 0을 찾았고, 2가 2를 대체했습니다.

2 3 << lower_bound(3)가 인덱스 1을 찾았고, 3이 5를 대체했습니다.  "2자리"에서는 (2, 5)보다 (2, 3)이 LIS를 만들기 유리합니다.

1 3 << lower_bound(1)가 인덱스 0을 찾았고, 1이 2를 대체했습니다.

1 3 4 <<  3<4 이므로 뒤에 넣어줍니다.



참고해야할 사항은 이렇게 만들어진 dp[]는 LIS 수열이 아니고,

단지 그 길이가 LIS와 같다는 점을 알 수 있습니다.



dp[] 역할을 vector v가 해주고 있습니다.

```c++
#11053 백준

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int a[1000000];
vector<int> v {-2076543210};
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	
	/*
		O(NlogN)
	*/
	for (int i = 0; i < n; ++i) {
		int num = a[i];
		if (v.back() < num) {
			v.emplace_back(num);
		}
		else {
			auto it = lower_bound(v.begin(), v.end(), num);
			*it = num;
		}
	}
	printf("%d\n", v.size() - 1);
	return 0;
}
```





#### + LIS 수열 출력 (Backtrace)

새로운 배열을 만듭니다.

 P[i] : 수열의 i번째 원소가 dp[]에서  위치하는 인덱스



위의 예제에서 p[] 는 다음과 같이 나옵니다.

1 1 2 **1** **2** 1 **3**

각각 배열 뒤에서 부터 봤을 때 3이 처음으로 나온 인덱스는 6(0부터시작)이기 때문에, a[6]을

2가 처음으로 나온 인덱스는 4이기 때문에, a[4]를

1이 처음으로 나온 인덱스는 3이기 때문에, a[3]을

역순으로 출력해 주시면 됩니다.

이 과정에서 메모리와 시간을 아끼기 위해 backtrace 알고리즘이 추가됩니다.



```c++
#백준 14003번

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int a[1000000];
int p[1000000];
int n;
vector<int> v {-2076543210};

/*
	배열의 크기가 커서 메모리가 늘어나고,
	다시 출력하는데 O(N)의 시간이 걸리므로,
	재귀함수를 이용한 백트래킹을 합니다.
*/
void backtrace(int idx, int last) {
	if (idx < 0) return;
	if (p[idx] == last) {
		backtrace(idx - 1, last - 1);
		printf("%d ", a[idx]);
	}
	else {
		backtrace(idx - 1, last);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	/*
		O(NlogN)
	*/
	for (int i = 0; i < n; ++i) {
		int num = a[i];
		if (v.back() < num) {
			p[i] = v.size();
			v.emplace_back(num);
		}
		else {
			auto it = lower_bound(v.begin(), v.end(), num);
			*it = num;
			p[i] = distance(v.begin(), it);
		}
	}
	printf("%d\n", v.size() - 1);
	backtrace(n - 1, v.size() - 1);
	return 0;
}
```

