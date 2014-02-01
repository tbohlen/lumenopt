inline void myAssert(bool ok) {
    if (ok) {
        return;
    }
    else {
        throw "Assertion Error";
    }
}

inline bool compFloat(float a, float b, float E) {
    // returns one if they are equal and 0 otherwise
    return (a-b) < E && (b-a) < E;
}
