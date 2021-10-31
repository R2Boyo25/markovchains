#include <string>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "nlohmann/json.hpp"

namespace Markov {
    class MarkovGenerator {
        public:
            std::string generate(int w);
            void fromJSON(std::string JSON);
            void fromFile(std::string file);
            nlohmann::json toJSON();
        private:
            void createDictionary( unsigned int kl );
            std::string fileBuffer;
            std::map<std::string, std::vector<std::string> > dictionary;
            unsigned int keyLen = 1;
    };
};