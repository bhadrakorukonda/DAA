#include <bits/stdc++.h>
using namespace std;

// ====== NTT params (same trio of NTT-friendly primes) ======
using u32 = uint32_t; using u64 = uint64_t; using i128 = __int128_t;
struct NTTParams { u32 MOD, PR; int MAX_LOG; };
static constexpr NTTParams P1{167772161u, 3u, 25};
static constexpr NTTParams P2{469762049u, 3u, 26};
static constexpr NTTParams P3{1224736769u, 3u, 24};

static inline u32 addm(u32 a,u32 b,u32 M){ u32 s=a+b; return s>=M?s-M:s; }
static inline u32 subm(u32 a,u32 b,u32 M){ return a>=b?a-b:a+M-b; }
static inline u32 mulm(u64 a,u64 b,u32 M){ return (u32)((a*b)%M); }

static u32 modpow(u32 a, u64 e, u32 M){
    u64 r=1,x=a;
    while(e){ if(e&1) r=(r*x)%M; x=(x*x)%M; e>>=1; }
    return (u32)r;
}
static u32 invmod(u32 a, u32 M){ return modpow(a, M-2, M); }

// ====== Iterative breadth-first NTT ======
static void ntt(vector<u32>& a, bool invert, const NTTParams& P){
    int n = (int)a.size();
    for(int i=1,j=0;i<n;++i){ int b=n>>1; for(; j&b; b>>=1) j^=b; j^=b; if(i<j) swap(a[i],a[j]); }
    for(int len=2; len<=n; len<<=1){
        u32 wlen = modpow(P.PR, (P.MOD-1)/len, P.MOD);
        if(invert) wlen = invmod(wlen, P.MOD);
        for(int i=0;i<n;i+=len){
            u32 w=1; int half=len>>1;
            for(int j=0;j<half;++j){
                u32 u=a[i+j], v=mulm(a[i+j+half], w, P.MOD);
                a[i+j] = addm(u,v,P.MOD);
                a[i+j+half] = subm(u,v,P.MOD);
                w = mulm(w,wlen,P.MOD);
            }
        }
    }
    if(invert){
        u32 inv_n = invmod((u32)n, P.MOD);
        for(u32& x:a) x = mulm(x, inv_n, P.MOD);
    }
}

static vector<u32> conv_mod(const vector<u32>& A, const vector<u32>& B, const NTTParams& P){
    if(A.empty() || B.empty()) return {};
    int need = (int)A.size() + (int)B.size() - 1;
    int n=1; while(n<need) n<<=1;
    vector<u32> fa(n,0), fb(n,0);
    copy(A.begin(),A.end(),fa.begin());
    copy(B.begin(),B.end(),fb.begin());
    ntt(fa,false,P); ntt(fb,false,P);
    for(int i=0;i<n;++i) fa[i] = mulm(fa[i], fb[i], P.MOD);
    ntt(fa,true,P);
    fa.resize(need);
    return fa;
}

// ====== 3-modulus CRT with centered lifting (handles negatives) ======
static i128 crt3_centered(u32 r1, u32 r2, u32 r3){
    const i128 m1=P1.MOD, m2=P2.MOD, m3=P3.MOD;
    // combine r1,r2
    u32 m1_inv_m2 = invmod((u32)m1, (u32)m2);
    u32 t = mulm((r2 + P2.MOD - (r1 % P2.MOD)) % P2.MOD, m1_inv_m2, P2.MOD);
    i128 x12 = (i128)r1 + m1*(i128)t;          // mod m1*m2
    i128 m12 = m1*m2;

    u32 m12_mod_m3 = (u32)(m12 % m3);
    u32 inv_m12_m3 = invmod(m12_mod_m3, (u32)m3);
    u32 x12_mod_m3 = (u32)(x12 % m3);
    u32 u = mulm((r3 + P3.MOD - x12_mod_m3) % (u32)m3, inv_m12_m3, (u32)m3);

    i128 M = m12*m3;
    i128 x = x12 + m12*(i128)u;               // 0 <= x < M

    // Center to (-M/2, M/2]
    if (x > M/2) x -= M;
    return x;
}

// ====== Minimal BigInt (base 1e9) for printing huge coeffs ======
struct BigInt {
    static constexpr uint32_t BASE = 1000000000u;
    bool neg = false;
    vector<uint32_t> d; // little-endian chunks (least significant first)

    BigInt() = default;
    explicit BigInt(long long v){ *this = fromInt128((__int128)v); }
    static BigInt fromInt128(__int128 v){
        BigInt B; if(v<0){ B.neg=true; v = -v; }
        while(v){ B.d.push_back((uint32_t)(v % BASE)); v /= BASE; }
        if(B.d.empty()) B.d.push_back(0), B.neg=false;
        return B;
    }
    static BigInt fromI128Signed(i128 v){ // alias
        return fromInt128(v);
    }
    string toString() const {
        if(d.empty()) return "0";
        string s = neg ? "-" : "";
        int n = (int)d.size();
        s += to_string(d.back());
        char buf[16];
        for(int i=n-2;i>=0;--i){
            // pad each chunk to 9 digits
            snprintf(buf, sizeof(buf), "%09u", d[i]);
            s += buf;
        }
        return s;
    }
};

// ====== Public: exact integer convolution -> vector<BigInt> ======
static vector<BigInt> convolution_bigint_printable(const vector<long long>& A, const vector<long long>& B){
    if(A.empty() || B.empty()) return {};
    auto to_mod = [](const vector<long long>& V, u32 MOD){
        vector<u32> R(V.size());
        for(size_t i=0;i<V.size();++i){
            long long x = V[i] % (long long)MOD; if(x<0) x+=MOD; R[i]=(u32)x;
        }
        return R;
    };
    vector<u32> A1=to_mod(A,P1.MOD), B1=to_mod(B,P1.MOD);
    vector<u32> A2=to_mod(A,P2.MOD), B2=to_mod(B,P2.MOD);
    vector<u32> A3=to_mod(A,P3.MOD), B3=to_mod(B,P3.MOD);

    auto C1 = conv_mod(A1,B1,P1);
    auto C2 = conv_mod(A2,B2,P2);
    auto C3 = conv_mod(A3,B3,P3);

    int n = (int)C1.size();
    vector<BigInt> C(n);
    for(int i=0;i<n;++i){
        i128 x = crt3_centered(C1[i], C2[i], C3[i]); // signed exact value in (-M/2, M/2]
        C[i] = BigInt::fromI128Signed(x);
    }
    // trim trailing zeros (optional aesthetic)
    while(!C.empty()){
        bool allZero = (C.back().d.size()==1 && C.back().d[0]==0 && !C.back().neg);
        if(!allZero) break;
        C.pop_back();
    }
    return C;
}

// ====== Demo ======
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example 1: negatives + big magnitude
    vector<long long> A = {3, -2, 5, 1};
    vector<long long> B = {5, 1, 2, -3, 4};

    auto C = convolution_bigint_printable(A, B);
    cout << "Convolution (BigInt):\n";
    for(size_t i=0;i<C.size();++i){
        cout << "x^" << i << " -> " << C[i].toString() << "\n";
    }

    // Example 2: very large coefficients (beyond 64-bit sums)
    vector<long long> X(1<<12, 0), Y(1<<12, 0);
    X[0]   = 1'000'000'000;    // 1e9
    X[100] = 2'000'000'000;    // 2e9
    Y[0]   = 3'000'000'000;    // 3e9
    Y[50]  = 4'000'000'000;    // 4e9

    auto Z = convolution_bigint_printable(X, Y);
    cout << "\nBigInt sanity:\n";
    cout << "Z[0]   = "   << Z[0].toString()   << " (expect 3000000000000000000)\n";
    cout << "Z[50]  = "   << Z[50].toString()  << " (expect 4000000000000000000)\n";
    cout << "Z[100] = "   << Z[100].toString() << " (expect 6000000000000000000)\n";
    cout << "Z[150] = "   << Z[150].toString() << " (expect 8000000000000000000)\n";
}
