#include <cstdio>
#include <vector>
#include <string>
using namespace std;

/*
    String search
    [strstr() in C], [string::find() in C++], [indexOf() in java] operated like below.
    O(|H||N|)
*/
vector<int> naive_search(const string &H, const string &N){
    vector<int> ret;

    for (int i = 0; i <= H.size() - N.size(); ++i){
        bool matched = true;
        for (int j=0; j<N.size(); ++j){
            if (H[i + j] != N[j]) {
                matched = false;
                break;
            }
        }
        if (matched) ret.emplace_back(i);
    }
    return ret;
}


vector<int> getPartialMatch(const string &N){
    int m = N.size();
    vector<int> pi(m, 0);

    int begin = 1, matched = 0;
    while(begin + matched < m){
        if (N[begin + matched] == N[matched]){
            ++matched;
            pi[begin + matched - 1] = matched;
        }
        else {
            if (matched == 0) ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}

// O(|N| + |H|)
vector<int> kmpSearch(const string &H, const string &N){
    int n = H.size(), m = N.size();
    vector<int> ret;

    /*
        pi[i] = N[...i]의 접두사와 접미사가 일치하는 최대 문자열의 길이
        O(N^3) --> O(N^2) --> O(|N|)

    */
    vector<int> pi = getPartialMatch(N);

    /* 
        begin은 N에서 시작 문자열 위치
        matched는 M에서 N과 현재까지 매치된 위치
    */
    int begin = 0, matched = 0;
    while(begin <= n - m){
        if (matched < m && H[begin + matched] == N[matched]){
            ++matched;
            if (matched == m) ret.emplace_back(begin); 
        }
        else {
            // 예외: matched가 0이면 다음 칸 부터 계속.
            if (matched == 0) ++begin;
            // KMP 핵심 logic
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
}

int main() {
    return 0;
}