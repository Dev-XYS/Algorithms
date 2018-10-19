#include <bits/stdc++.h>
#define endl "\n"
#define loop(i, n) for (ll i = 0; i < n; i++)
#define printarr(arr, n) cout << #arr << ": "; for (ll i = 0; i < n; i++) cout << arr[i] << " "; cout << endl;
#define print(a) cout << #a << ": " << a << endl; 
typedef int64_t ll;
using namespace std;

ll n, *arr, *leftseq, *rightseq, *totalseq, *tail, length = 1, maximum;


/*
Output:
$ g++ -std=c++14 bitonic.cpp && ./a.out
6
1 3 4 2 6 1

leftseq: 0 1 2 1 3 0
rightseq: 0 2 2 1 1 0
totalseq: 0 3 4 2 4 0
Maximum length: 5

MaxElement: 4  Sequence: 1 3 4 2 1      LeftSeqLen: 2  RightSeqLen: 2
MaxElement: 6  Sequence: 1 3 4 6 1      LeftSeqLen: 3  RightSeqLen: 1
*/


ll binsearch(ll index) {
    ll x = arr[index];

    // printarr(tail, n)
    // cout << endl;
    // print(x)

    if (x <= tail[0]) {
        tail[0] = x;
        return 0;
    } else if (x > tail[length-1]) {
        tail[length] = x;
        return length++;
    } else {
        ll mid, beg = 0, end = length-1;
        while (beg < end) {
            mid = beg + (end - beg)/2;
            if (tail[mid] >= x) {
                if (end == mid)
                    break;
                end = mid;
            } else {
                if (beg == mid)
                    break;
                beg = mid;
            }
        }
        ll sm = mid;
        ll big = mid+1;
        tail[big] = x;
        return big;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    arr = new ll[n];
    leftseq = new ll[n];
    rightseq = new ll[n];
    totalseq = new ll[n];
    tail = new ll[n];

    loop(i, n)
        cin >> arr[i];

    cout << endl;
    // Maximum length of inc subsequence when node i is max
    length = 1;
    leftseq[0] = leftseq[n-1] = 0;
    tail[0] = arr[0];
    for (ll i = 1; i < n-1; i++) {
        leftseq[i] = binsearch(i);
    }
    printarr(leftseq, n)

    // Maximum length of dec subsequence when node i is max
    length = 1;
    rightseq[0] = rightseq[n-1] = 0;
    tail[0] = arr[n-1];
    for (ll i = n-2; i > 0; i--) {
        rightseq[i] = binsearch(i);
    }
    printarr(rightseq, n)

    // Total
    loop(i, n) {
        totalseq[i] = leftseq[i] + rightseq[i];
        if (totalseq[i] > maximum)
            maximum = totalseq[i];
    }
    printarr(totalseq, n)
    cout << "Maximum length: " << maximum+1 << endl;
    cout << endl;

    // Result Printing sequence
    ll len_left = 0, len_right = 0, j;
    stack <ll> s;
    loop(i, n) {
        if (totalseq[i] == maximum) {
            cout << "MaxElement: " << arr[i] << "  Sequence: ";

            len_left = leftseq[i]-1;
            j = i;
            while (len_left >= 0) {
                if (leftseq[--j] == len_left) {
                    s.push(arr[j]);
                    len_left--;
                }
            }
            while (!s.empty()) {
                cout << s.top() << " ";
                s.pop();
            }

            cout << arr[i] << " ";

            len_right = rightseq[i]-1;
            j = i;
            while (len_right >= 0) {
                if (rightseq[++j] == len_right) {
                    cout << arr[j] << " ";
                    len_right--;
                }
            }
            cout << "\t" << "LeftSeqLen: " << leftseq[i];
            cout << "  RightSeqLen: " << rightseq[i] << endl;
        }
    }

    return 0;
}
