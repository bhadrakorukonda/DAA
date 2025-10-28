#include <bits/stdc++.h>
using namespace std;

// ====================== Utilities ======================
using u32 = uint32_t;
using u64 = uint64_t;
using i64 = long long;
using i128 = __int128_t;

static inline u32 addm(u32 a, u32 b, u32 MOD){ u32 s=a+b; return s>=MOD?s-MOD:s; }
static inline u32 subm(u32 a, u32 b, u32 MOD){ return a>=b ? a-b : a+MOD-b; }
static inline u32 mulm(u64 a, u64 b, u32 MOD){ return (u32)((a*b)%MOD); }

static u32 modpow(u32 a, u64 e, u32 MOD){
    u64 r=1, x=a;
    while(e){
        if(e&1) r=(r*x)%MOD;
        x=(x*x)%MOD;
        e>>=1;
    }
    return (u32)r;
}

static u32 invmod(u32 a, u32 MOD){
    // MOD is prime in our use; inverse via Fermat
    return modpow(a, MOD-2, MOD);
}

// ====================== NTT (iterative) ======================
struct NTTParams {
    u32 MOD;      // prime modulus = k*2^m + 1
    u32 PR;       // primitive root modulo MOD
    int MAX_LOG;  // maximum power-of-two supported (<= 23..26 depending on MOD)
};

static void ntt(vector<u32>& a, bool invert, const NTTParams& P){
    int n = (int)a.size();
    // bit-reversal permutation
    for(int i=1, j=0; i<n; ++i){
        int bit = n>>1;
        for(; j&bit; bit>>=1) j ^= bit;
        j ^= bit;
        if(i<j) swap(a[i], a[j]);
    }
    for(int len=2; len<=n; len<<=1){
        u32 root = modpow(P.PR, (P.MOD-1)/len, P.MOD);
        if(invert) root = invmod(root, P.MOD);
        for(int i=0; i<n; i+=len){
            u32 w = 1;
            int half = len>>1;
            for(int j=0; j<half; ++j){
                u32 u = a[i+j];
                u32 v = mulm(a[i+j+half], w, P.MOD);
                a[i+j]      = addm(u, v, P.MOD);
                a[i+j+half] = subm(u, v, P.MOD);
                w = mulm(w, root, P.MOD);
            }
        }
    }
    if(invert){
        u32 inv_n = invmod((u32)n, P.MOD);
        for(u32 &x : a) x = mulm(x, inv_n, P.MOD);
    }
}

static vector<u32> convolution_mod(const vector<u32>& A, const vector<u32>& B, const NTTParams& P){
    if(A.empty() || B.empty()) return {};
    int need = (int)A.size() + (int)B.size() - 1;
    int n = 1; while(n < need) n <<= 1;

    vector<u32> fa(n,0), fb(n,0);
    copy(A.begin(), A.end(), fa.begin());
    copy(B.begin(), B.end(), fb.begin());

    ntt(fa, false, P);
    ntt(fb, false, P);
    for(int i=0;i<n;++i) fa[i] = mulm(fa[i], fb[i], P.MOD);
    ntt(fa, true, P);

    fa.resize(need);
    return fa;
}

// ====================== Multi-mod CRT combine ======================
// We’ll use three classic NTT primes with primitive root 3:
static constexpr NTTParams P1{167772161u, 3u, 25};   // 5 * 2^25 + 1
static constexpr NTTParams P2{469762049u, 3u, 26};   // 7 * 2^26 + 1
static constexpr NTTParams P3{1224736769u, 3u, 24};  // 73 * 2^24 + 1

// Combine residues r1 (mod m1), r2 (mod m2), r3 (mod m3) -> exact integer via CRT.
// Returns value in 128-bit; caller can cast to signed 64-bit if safe.
static i128 crt3(u32 r1, u32 r2, u32 r3){
    const i128 m1 = P1.MOD, m2 = P2.MOD, m3 = P3.MOD;
    // x ≡ r1 (mod m1)
    // x = r1 + m1 * t, where t ≡ (r2 - r1) * inv(m1, m2) (mod m2)
    u32 m1_inv_m2 = invmod((u32)m1, (u32)m2);
    u32 t = mulm((r2 + P2.MOD - (r1 % P2.MOD)) % P2.MOD, m1_inv_m2, (u32)m2);

    i128 x12 = (i128)r1 + (i128)m1 * (i128)t; // now x12 ≡ r1 mod m1, ≡ r2 mod m2

    // x = x12 + m1*m2 * u,  where  u ≡ (r3 - x12) * inv(m1*m2, m3) (mod m3)
    i128 m12 = m1 * m2;
    u32 m12_mod_m3 = (u32)(m12 % m3);
    u32 inv_m12_m3 = invmod(m12_mod_m3, (u32)m3);
    u32 x12_mod_m3 = (u32)(x12 % m3);
    u32 u = mulm((r3 + P3.MOD - x12_mod_m3) % (u32)m3, inv_m12_m3, (u32)m3);

    i128 x = x12 + m12 * (i128)u; // unique modulo m1*m2*m3
    return x; // not reduced; this is the smallest non-negative solution
}

// Public: exact integer convolution using 3-modulus NTT + CRT
static vector<long long> convolution_bigint(const vector<long long>& A, const vector<long long>& B){
    if(A.empty() || B.empty()) return {};

    // Convert to unsigned residues mod each prime (handle negatives too)
    auto to_mod = [&](const vector<long long>& V, u32 MOD){
        vector<u32> R(V.size());
        for(size_t i=0;i<V.size();++i){
            long long x = V[i] % (long long)MOD;
            if(x < 0) x += MOD;
            R[i] = (u32)x;
        }
        return R;
    };

    vector<u32> A1 = to_mod(A, P1.MOD), B1 = to_mod(B, P1.MOD);
    vector<u32> A2 = to_mod(A, P2.MOD), B2 = to_mod(B, P2.MOD);
    vector<u32> A3 = to_mod(A, P3.MOD), B3 = to_mod(B, P3.MOD);

    auto C1 = convolution_mod(A1, B1, P1);
    auto C2 = convolution_mod(A2, B2, P2);
    auto C3 = convolution_mod(A3, B3, P3);

    int n = (int)C1.size();
    vector<long long> C(n);
    for(int i=0;i<n;++i){
        i128 x = crt3(C1[i], C2[i], C3[i]); // exact (mod m1*m2*m3)
        // If you KNOW true coefficients fit in 64 bits, cast safely:
        long long val = (long long)x;
        C[i] = val;
    }
    // Trim trailing zeros for cleanliness
    while(!C.empty() && C.back()==0) C.pop_back();
    return C;
}

// ====================== Demo / Test ======================
static vector<long long> naive_mul(const vector<long long>& A, const vector<long long>& B){
    vector<long long> C(A.size()+B.size()-1, 0);
    for(size_t i=0;i<A.size();++i)
        for(size_t j=0;j<B.size();++j)
            C[i+j] += A[i]*B[j];
    return C;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example 1: small integers (compares with naive)
    vector<long long> A = {3, -2, 5, 1};           // allow negatives
    vector<long long> B = {5, 1, 2, -3, 4};

    auto C_ntt = convolution_bigint(A, B);
    auto C_ref = naive_mul(A, B);

    cout << "Equal to naive? " << (C_ntt == C_ref ? "YES" : "NO") << "\n";
    cout << "Result coefficients:\n";
    for(size_t i=0;i<C_ntt.size();++i){
        cout << "x^" << i << " -> " << C_ntt[i] << "\n";
    }

    // Example 2: larger coefficients to show no modular wrap
    vector<long long> X(1<<12, 0), Y(1<<12, 0); // length 4096 each
    X[0] = 1'000'000'000; X[100] = 2'000'000'000;
    Y[0] = 3'000'000'000; Y[50]  = 4'000'000'000;

    auto Z = convolution_bigint(X, Y);
    cout << "\nBig-coeff sanity checks:\n";
    cout << "Z[0]      = " << Z[0] << " (expected 3e18)\n";
    cout << "Z[50]     = " << Z[50] << " (expected 4e18)\n";
    cout << "Z[100]    = " << Z[100] << " (expected 6e18)\n";
    cout << "Z[150]    = " << Z[150] << " (expected 8e18)\n";
}
