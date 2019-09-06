#include <iostream>
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

#define _CRT_SECURE_NO_WARNINGS



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
