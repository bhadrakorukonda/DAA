#include <bits/stdc++.h>
using namespace std;

// ---------- NTT over mod = 998244353 ----------
using int64 = long long;
const uint32_t MOD = 998244353;   // = 119 * 2^23 + 1
const uint32_t PR  = 3;           // primitive root

static inline uint32_t addm(uint32_t a, uint32_t b){ uint32_t s=a+b; return s>=MOD?s-MOD:s; }
static inline uint32_t subm(uint32_t a, uint32_t b){ return a>=b ? a-b : a+MOD-b; }
static inline uint32_t mulm(uint64_t a, uint64_t b){ return (uint32_t)((a*b)%MOD); }

uint32_t modpow(uint32_t a, uint64_t e){
    uint64_t r=1, x=a;
    while(e){
        if(e&1) r = (r*x)%MOD;
        x = (x*x)%MOD;
        e >>= 1;
    }
    return (uint32_t)r;
}

// In-place iterative NTT (Cooley–Tukey, breadth-first)
void ntt(vector<uint32_t>& a, bool invert){
    int n = (int)a.size();

    // bit-reverse permutation
    for(int i=1, j=0; i<n; ++i){
        int bit = n>>1;
        for(; j&bit; bit>>=1) j ^= bit;
        j ^= bit;
        if(i<j) swap(a[i], a[j]);
    }

    for(int len=2; len<=n; len<<=1){
        uint32_t root = modpow(PR, (MOD-1)/len);
        if(invert) root = modpow(root, MOD-2); // inverse root

        for(int i=0; i<n; i+=len){
            uint32_t w = 1;
            int half = len>>1;
            for(int j=0; j<half; ++j){
                uint32_t u = a[i+j];
                uint32_t v = mulm(a[i+j+half], w);
                a[i+j]       = addm(u, v);
                a[i+j+half]  = subm(u, v);
                w = mulm(w, root);
            }
        }
    }

    if(invert){
        uint32_t inv_n = modpow(n, MOD-2);
        for(uint32_t &x : a) x = mulm(x, inv_n);
    }
}

// Convolution C = A * B (mod MOD)
vector<uint32_t> convolution_ntt(const vector<uint32_t>& A, const vector<uint32_t>& B){
    if(A.empty() || B.empty()) return {};
    int n1 = (int)A.size(), n2 = (int)B.size();
    int n = 1; while(n < n1 + n2 - 1) n <<= 1;

    vector<uint32_t> fa(n,0), fb(n,0);
    copy(A.begin(), A.end(), fa.begin());
    copy(B.begin(), B.end(), fb.begin());

    ntt(fa, false);
    ntt(fb, false);
    for(int i=0;i<n;++i) fa[i] = mulm(fa[i], fb[i]);
    ntt(fa, true);

    fa.resize(n1 + n2 - 1);
    return fa;
}

// ------------- Demo -------------
int main(){
    // Example: (3 + 2x + 5x^2) * (5 + x + 2x^2)
    vector<uint32_t> A = {3, 2, 5};
    vector<uint32_t> B = {5, 1, 2};

    auto C = convolution_ntt(A, B);

    cout << "NTT convolution (mod " << MOD << "):\n";
    for(size_t i=0;i<C.size();++i){
        cout << "x^" << i << " -> " << C[i] << "\n";
    }
    // Expected (over integers): 15, 13, 33, 9, 10 (all < MOD, so identical mod MOD)
}
