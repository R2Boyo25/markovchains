#include "markov.h"
#include <iostream>
#include "nlohmann/json.hpp"
#include <cstdlib>

using namespace std;
using namespace Markov;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
    MarkovGenerator markov;
    if (argc > 1) {
       if (string(argv[2]) == "to") {
            markov.fromFile(argv[1]);

            ofstream o(argv[3]);
            o << setw(4) << markov.toJSON() << std::endl;
        }
        else if (string(argv[1]) == "from") {
            int len = atoi(argv[3]);
            ifstream i(argv[2]);
            stringstream s;
            s << i.rdbuf();

            markov.fromJSON(s.str());
            cout << markov.generate(len);
        } 
    } else {
        cout << "Usage:\n\tmark textfile to cachefile\n\tmark from cachefile lentogenerate" << endl;
    }
    return 0;

}