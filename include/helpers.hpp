inline void myAssert(bool ok) {
    if (ok) {
        return;
    }
    else {
        throw "Assertion Error";
    }
}

inline bool compFloat(float a, float b, float E) {
    return (a-b) < E && (b-a) < E;
}
