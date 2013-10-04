#ifndef MERSENNE_H
#define MERSENNE_H

#include <Windows.h>
#include <ctime>

class MersenneTwister {
private:
	int N ;
	int M ;
	UINT MATRIX_A ;
	UINT UPPER_MASK ;
	UINT LOWER_MASK ;
	UINT TEMPERING_MASK_B ;
	UINT TEMPERING_MASK_C ;

	static UINT TEMPERING_SHIFT_U(UINT y) { return (y >> 11); }
	static UINT TEMPERING_SHIFT_S(UINT y) { return (y << 7); }
	static UINT TEMPERING_SHIFT_T(UINT y) { return (y << 15); }
	static UINT TEMPERING_SHIFT_L(UINT y) { return (y >> 18); }

    UINT* mt;
    short mti;

    UINT mag01[2];
	int genrand() {
        UINT y;

        if (mti >= N) {
            short kk;
            if (mti == N + 1) {
                sgenrand((UINT)time(NULL));
            }
            for (kk = 0; kk < N - M; kk++) {
                y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
                mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1];
            }
            for (; kk < N - 1; kk++) {
                y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
                mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1];
            }
            y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
            mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1];
            mti = 0;
        }

        y = mt[mti++];
        y ^= TEMPERING_SHIFT_U(y);
        y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
        y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
        y ^= TEMPERING_SHIFT_L(y);

        return (int)y;
    }
public:
	MersenneTwister() {
		N = 624;
		M = 397;
		MATRIX_A = 0x9908b0df;
		UPPER_MASK = 0x80000000;
		LOWER_MASK = 0x7fffffff;
		TEMPERING_MASK_B = 0x9d2c5680;
		TEMPERING_MASK_C = 0xefc60000;
		mt = new UINT[N];
		mti=N + 1;
		mag01[0]=0x0;
		mag01[1]=MATRIX_A;
        sgenrand((UINT)time(NULL));
	}
	virtual ~MersenneTwister(){
		delete[] mt;
	}
	void sgenrand(UINT seed) {
        mt[0] = seed & 0xffffffffU;
        for (mti = 1; mti < N; mti++) {
            mt[mti] = (69069 * mt[mti - 1]) & 0xffffffffU;
        }
    }
	int Next(int max) {
		return abs(genrand())%max;
    }
};

#endif MERSENNE_H