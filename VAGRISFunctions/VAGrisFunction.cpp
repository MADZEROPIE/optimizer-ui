#include <math.h>
#include <cassert>
#include "VAGrisFunction.h"
using namespace vagrisfunction;
// clang-format off
static const double rand_minimums[] = {
0.603052, 0.408337, /*f(min1)=-13.51436*/
  0.652988, 0.320592, /*f(min2)=-11.28447*/
  1.000000, 0.000000, /*f(min3)=-13.20907*/
  0.066182, 0.582587, /*f(min4)=-11.54117*/
  0.904308, 0.872639, /*f(min5)=-9.969261*/
  0.344375, 0.524932, /*f(min6)=-9.180137*/
  0.000000, 1.000000, /*f(min7)=-9.359486*/
  0.948275, 0.887031, /*f(min8)=-11.46999*/
  0.226047, 0.520153, /*f(min9)=-11.41470*/
  0.341732, 0.197620, /*f(min10)=-12.35783*/
  0.069264, 0.430955, /*f(min11)=-8.298100*/
  0.000000, 1.000000, /*f(min12)=-10.77891*/
  0.45221, 0.07292,  /*f(min13)=-9.639918*/
  0.579769, 0.046396, /*f(min14)=-10.84688*/
  0.000000, 1.000000, /*f(min15)=-9.998392*/
  0.310179, 1.000000, /*f(min16)=-13.27447*/
  0.909758, 0.926195, /*f(min17)=-11.20579*/
  0.434562, 0.825608, /*f(min18)=-8.555728*/
  0.06686, 0.77051,  /*f(min19)=-11.08050*/
  0.641337, 0.135186, /*f(min20)=-10.84137*/
  0.885029, 0.390289, /*f(min21)=-10.09915*/
  0.649650, 0.414282, /*f(min22)=-8.821688*/
  0.142623, 0.157327, /*f(min23)=-11.20434*/
  0.862953, 1.000000, /*f(min24)=-9.774841*/
  0.46036, 0.99314,  /*f(min25)=-9.446216*/
  0.379189, 0.688051, /*f(min26)=-9.922234*/
  0.845292, 0.424546, /*f(min27)=-9.353030*/
  0.441160, 0.016803, /*f(min28)=-8.927842*/
  1.000000, 1.000000, /*f(min29)=-11.97038*/
  0.303295, 0.134722, /*f(min30)=-11.05922*/
  0.109520, 0.265486, /*f(min31)=-8.961329*/ //CHECK
  1.000000, 0.000000, /*f(min32)=-10.25347*/
  0.593726, 0.503014, /*f(min33)=-13.75610*/
  0.694905, 1.000000, /*f(min34)=-10.07243*/
  0.051975, 0.409344, /*f(min35)=-10.66758*/
  0.125664, 0.518969, /*f(min36)=-9.606340*/
  0.000000, 0.000000, /*f(min37)=-11.10867*/
  0.155081, 0.238663, /*f(min38)=-8.586483*/
  0.53707, 0.46181,  /*f(min39)=-8.823492*/
  0.110985, 0.917791, /*f(min40)=-10.22533*/
  1.000000, 0.000000, /*f(min41)=-13.84155*/
  0.776095, 0.764724, /*f(min42)=-10.76901*/
  0.087367, 0.677632, /*f(min43)=-8.574448*/
  0.308037, 0.536113, /*f(min44)=-10.40137*/
  0.042100, 0.563607, /*f(min45)=-8.889051*/
  0.287025, 0.159219, /*f(min46)=-10.44960*/ //CHECK
  0.451926, 0.169839, /*f(min47)=-10.45448*/
  0.884761, 0.245341, /*f(min48)=-9.749494*/
  0.047782, 0.171633, /*f(min49)=-10.80496*/
  0.00000, 0.41596,  /*f(min50)=-12.16739*/
  0.192108, 0.303789, /*f(min51)=-11.14192*/
  0.554153, 0.809821, /*f(min52)=-10.06221*/
  0.91475, 0.54149,  /*f(min53)=-9.518639*/
  0.663042, 0.927703, /*f(min54)=-9,404623*/ //CHECK
  0.964492,  0.434984, /*f(min55)=-10.193476*/ //CHECK
  0.000000, 0.000000, /*f(min56)=-9.009641*/
  0.616058, 0.560244, /*f(min57)=-10.02504*/
  0.439890, 0.343722, /*f(min58)=-10.95753*/
  0.218146, 0.677192, /*f(min59)=-9.850361*/
  1.000000, 1.000000, /*f(min60)=-11.74782*/
  0.198145, 0.317876, /*f(min61)=-10.73907*/
  0.875874, 0.653336, /*f(min62)=-9.060382*/
  0.22999, 0.33624,  /*f(min63)=-10.74852*/
  0.169351, 0.015656, /*f(min64)=-8.455091*/
  0.760073, 0.906035, /*f(min65)=-11.29555*/
  0.702941, 0.308403, /*f(min66)=-10.47617*/
  0.365371, 0.282325, /*f(min67)=-9.285640*/
  0.314012, 0.651377, /*f(min68)=-9.592745*/
  0.237687, 0.374368, /*f(min69)=-10.82136*/
  0.583144, 0.5061395, /*f(min70)=-9.353751*/ //CHECK
  0.000000, 0.000000, /*f(min71)=-9.803835*/
  0.383319, 1.000000, /*f(min72)=-10.86034*/
  0.780103, 0.103783, /*f(min73)=-10.98085*/
  0.350265, 0.566946, /*f(min74)=-8.966131*/
  0.798535, 0.478706, /*f(min75)=-11.00382*/
  0.31759, 0.06967,  /*f(min76)=-9.959365*/
  0.715929, 0.704778, /*f(min77)=-11.38632*/
  0.563040, 0.442557, /*f(min78)=-11.44656*/
  0.565078, 0.322618, /*f(min79)=-14.17049*/
  0.146731, 0.510509, /*f(min80)=-10.61985*/
  0.000000, 0.543167, /*f(min81)=-11.31970*/
  0.208533, 0.454252, /*f(min82)=-10.95230*/
  0.155111, 0.972329, /*f(min83)=-11.41650*/
  0.000000, 1.000000, /*f(min84)=-12.05415*/
  0.336467, 0.909056, /*f(min85)=-10.45893*/
  0.57001, 0.90847,  /*f(min86)=-9.429290*/
  0.296290, 0.540579, /*f(min87)=-10.45261*/
  0.172262, 0.332732, /*f(min88)=-10.75306*/
  0.000000, 1.000000, /*f(min89)=-9.816527*/
  1.000000, 0.000000, /*f(min90)=-12.20688*/
  1.000000, 1.000000, /*f(min91)=-10.39147*/
  0.674061, 0.869954, /*f(min92)=-9.689030*/
  1.000000, 1.000000, /*f(min93)=-11.91809*/
  0.852506, 0.637278, /*f(min94)=-10.42941*/
  0.877491, 0.399780, /*f(min95)=-10.34945*/
  0.835605, 0.751888, /*f(min96)=-9.013732*/
  0.673378, 0.827427, /*f(min97)=-8.916823*/
  0.831754, 0.367117, /*f(min98)=-8.747803*/
  0.601971, 0.734465, /*f(min99)=-12.76981*/
  0.000000, 0.000000  /*f(min100)=-11.43793*/
};
static const unsigned char matcon[10][45] = {
	{ 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0 },
	{ 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0 },
	{ 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1 },
	{ 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0 },
	{ 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1 },
	{ 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0 },
};
// clang-format on

VAGrisFunction::VAGrisFunction() {
    mFunctionNumber = 1;
}

VAGrisFunction::~VAGrisFunction() {
}

void VAGrisFunction::SetFunctionNumber(int value) {
    assert(value > 0 && value <= 100);
    mFunctionNumber = value;

    int lst, i, j, i1, i2, i3;
    int nf = mFunctionNumber;

    if (nf < 1 || nf > 100)
        nf = 1;
    lst = 10;
    i1 = (nf - 1) / lst;
    i2 = i1 * lst;
    for (j = 0; j < 45; j++)
        icnf[j] = matcon[i1][j];
    if (i2 != (nf - 1)) {
        i3 = nf - 1 - i2;
        for (j = 1; j <= i3; j++)
            for (i = 0; i < 196; i++)
                rndm20(icnf);
    }
    for (j = 0; j < 7; j++)
        for (i = 0; i < 7; i++) {
            af[i][j] = 2. * rndm20(icnf) - 1.;
            cf[i][j] = 2. * rndm20(icnf) - 1.;
        }
    for (j = 0; j < 7; j++)
        for (i = 0; i < 7; i++) {
            bf[i][j] = 2. * rndm20(icnf) - 1.;
            df[i][j] = 2. * rndm20(icnf) - 1.;
        }
}

int VAGrisFunction::GetFunctionNumber() const {
    return mFunctionNumber;
}

double VAGrisFunction::GetMinimumXCoordinate(int fNumber) const {
    assert(fNumber > 0 && fNumber <= 100);
    return rand_minimums[2 * (fNumber - 1)];
}

double VAGrisFunction::GetMinimumYCoordinate(int fNumber) const {
    assert(fNumber > 0 && fNumber <= 100);
    return rand_minimums[2 * (fNumber - 1) + 1];
}

double VAGrisFunction::EvaluateFunction(double x, double y) const {
    int i, j;
    double d1, d2, sx1, cx1, sy1, cy1;
    double snx[7], csx[7], sny[7], csy[7];

    d1 = M_PI * x;
    d2 = M_PI * y;
    sx1 = sin(d1);
    cx1 = cos(d1);
    sy1 = sin(d2);
    cy1 = cos(d2);
    snx[0] = sx1;
    csx[0] = cx1;
    sny[0] = sy1;
    csy[0] = cy1;
    for (i = 0; i < 6; i++) {
        snx[i + 1] = snx[i] * cx1 + csx[i] * sx1;
        csx[i + 1] = csx[i] * cx1 - snx[i] * sx1;
        sny[i + 1] = sny[i] * cy1 + csy[i] * sy1;
        csy[i + 1] = csy[i] * cy1 - sny[i] * sy1;
    }
    d1 = 0;
    d2 = 0;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++) {
            d1 = d1 + af[i][j] * snx[i] * sny[j] + bf[i][j] * csx[i] * csy[j];
            d2 = d2 + cf[i][j] * snx[i] * sny[j] - df[i][j] * csx[i] * csy[j];
        }
    return (-sqrt(d1 * d1 + d2 * d2));
}

double VAGrisFunction::EvaluateXDerivative(double x, double y) const {
    int i, j;
    double dd, d1, d2, t1, t2, sx1, cx1, sy1, cy1;
    double snx[7], csx[7], sny[7], csy[7];

    d1 = M_PI * x;
    d2 = M_PI * y;
    sx1 = sin(d1);
    cx1 = cos(d1);
    sy1 = sin(d2);
    cy1 = cos(d2);
    snx[0] = sx1;
    csx[0] = cx1;
    sny[0] = sy1;
    csy[0] = cy1;
    for (i = 0; i < 6; i++) {
        snx[i + 1] = snx[i] * cx1 + csx[i] * sx1;
        csx[i + 1] = csx[i] * cx1 - snx[i] * sx1;
        sny[i + 1] = sny[i] * cy1 + csy[i] * sy1;
        csy[i + 1] = csy[i] * cy1 - sny[i] * sy1;
    }
    d1 = 0;
    d2 = 0;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++) {
            d1 = d1 + af[i][j] * snx[i] * sny[j] + bf[i][j] * csx[i] * csy[j];
            d2 = d2 + cf[i][j] * snx[i] * sny[j] - df[i][j] * csx[i] * csy[j];
        }
    dd = sqrt(d1 * d1 + d2 * d2);
    t1 = 0;
    t2 = 0;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++) {
            t1 += af[i][j] * M_PI * (i + 1) * csx[i] * sny[j];
            t1 -= bf[i][j] * M_PI * (i + 1) * snx[i] * csy[j];
            t2 += cf[i][j] * M_PI * (i + 1) * csx[i] * sny[j];
            t2 += df[i][j] * M_PI * (i + 1) * snx[i] * csy[j];
        }
    return (-(t1 * d1 + t2 * d2) / dd);
}

double VAGrisFunction::EvaluateYDerivative(double x, double y) const {
    int i, j;
    double dd, d1, d2, t1, t2, sx1, cx1, sy1, cy1;
    double snx[7], csx[7], sny[7], csy[7];

    d1 = M_PI * x;
    d2 = M_PI * y;
    sx1 = sin(d1);
    cx1 = cos(d1);
    sy1 = sin(d2);
    cy1 = cos(d2);
    snx[0] = sx1;
    csx[0] = cx1;
    sny[0] = sy1;
    csy[0] = cy1;
    for (i = 0; i < 6; i++) {
        snx[i + 1] = snx[i] * cx1 + csx[i] * sx1;
        csx[i + 1] = csx[i] * cx1 - snx[i] * sx1;
        sny[i + 1] = sny[i] * cy1 + csy[i] * sy1;
        csy[i + 1] = csy[i] * cy1 - sny[i] * sy1;
    }
    d1 = 0;
    d2 = 0;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++) {
            d1 = d1 + af[i][j] * snx[i] * sny[j] + bf[i][j] * csx[i] * csy[j];
            d2 = d2 + cf[i][j] * snx[i] * sny[j] - df[i][j] * csx[i] * csy[j];
        }
    dd = sqrt(d1 * d1 + d2 * d2);
    t1 = 0;
    t2 = 0;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++) {
            t1 += af[i][j] * M_PI * (j + 1) * snx[i] * csy[j];
            t1 -= bf[i][j] * M_PI * (j + 1) * csx[i] * sny[j];
            t2 += cf[i][j] * M_PI * (j + 1) * snx[i] * csy[j];
            t2 += df[i][j] * M_PI * (j + 1) * csx[i] * sny[j];
        }
    return (-(t1 * d1 + t2 * d2) / dd);
}

double VAGrisFunction::rndm20(unsigned char k[]) {
    int i;
    unsigned char k1[45];
    double de2, rndm;

    for (i = 0; i < 38; i++)
        k1[i] = k[i + 7];
    for (i = 38; i < 45; i++)
        k1[i] = 0;
    for (i = 0; i < 45; i++)
        k[i] = (unsigned char)abs(k[i] - k1[i]);
    for (i = 27; i < 45; i++)
        k1[i] = k[i - 27];
    for (i = 0; i < 27; i++)
        k1[i] = 0;

    gen(k, k1, 9, 44);
    gen(k, k1, 0, 8);

    rndm = 0.;
    de2 = 1.;
    for (i = 0; i < 36; i++) {
        de2 = de2 / 2;
        rndm = rndm + k[i + 9] * de2;
    }
    return (rndm);
}

void VAGrisFunction::gen(unsigned char k[], unsigned char k1[], int kap1, int kap2) {
    int jct, i, j;

    jct = 0;
    for (i = kap2; i >= kap1; i--) {
        j = (k[i] + k1[i] + jct) / 2;
        k[i] = k[i] + k1[i] + (unsigned char)jct - (unsigned char)j * 2;
        jct = j;
    }
    if (jct != 0)
        for (i = kap2; i >= kap1; i--) {
            j = (k[i] + jct) / 2;
            k[i] = k[i] + (unsigned char)jct - (unsigned char)j * 2;
            jct = j;
        }
}