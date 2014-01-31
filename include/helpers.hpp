inline void myAssert(bool ok) {
    if (ok) {
        return;
    }
    else {
        throw "Assertion Error";
    }
}
