using namespace std;
int main( int argc, char* argv[]) {
    // create a building model
    // building will be 3 by 3 by 3
    vector buildingVec(27)
    for (i = 0; i < 27; i++) {
        if (i < 11 || i == 12 || i == 13 || i == 26) {
            buildingVec[i] = 1;
        }
        else {
            buildingVec[i] = 0;
        }
    } // parse it
    // save it
}
