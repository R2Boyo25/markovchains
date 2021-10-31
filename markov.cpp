#include "markov.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace Markov {
    void MarkovGenerator::fromJSON(std::string JSON) {
        keyLen = 1;
        json j;

        j = json::parse(JSON);
        dictionary = j;
    }

    json MarkovGenerator::toJSON() {
        json j;

        j = dictionary;

        return j;
    }

    void MarkovGenerator::fromFile(std::string file) {
        srand( unsigned( time( 0 ) ) );
        std::ifstream f( file.c_str(), std::ios_base::in );
        fileBuffer = std::string( ( std::istreambuf_iterator<char>( f ) ), std::istreambuf_iterator<char>() ) + " ";
        f.close();
        if( fileBuffer.length() < 1 ) return;

        if (fileBuffer.length() < 15000) {
            keyLen = 1;
        } else {
            keyLen = 1;
        }

        createDictionary( keyLen );
    }

    std::string MarkovGenerator::generate( int w ) {
        srand( unsigned( time( 0 ) ) );
        std::string out;
        std::string key, first, second;
        size_t next;
        std::map<std::string, std::vector<std::string> >::iterator it = dictionary.begin();
        std::advance( it, rand() % dictionary.size() );
        key = ( *it ).first;
        out.append(key);

        while( true ) {
            std::vector<std::string> d = dictionary[key];
            if( d.size() < 1 ) break;
            second = d[rand() % d.size()];
            if( second.length() < 1 ) break;

            out.append(" ");
            out.append(second);
            if( --w < 0 ) break;
            next = key.find_first_of( 32, 0 );
            first = key.substr( next + 1 );
            key = first + " " + second;
        }
        return out;
    }

    void MarkovGenerator::createDictionary( unsigned int kl ) {
        std::string w1, key;
        size_t wc = 0, pos, next;
        next = fileBuffer.find_first_not_of( 32, 0 );
        if( next == std::string::npos ) return;
        while( wc < kl ) {
            pos = fileBuffer.find_first_of( ' ', next );
            w1 = fileBuffer.substr( next, pos - next );
            key += w1 + " ";
            next = fileBuffer.find_first_not_of( 32, pos + 1 );
            if( next == std::string::npos ) return;
            wc++;
        }
        key = key.substr( 0, key.size() - 1 );
        while( true ) {
            next = fileBuffer.find_first_not_of( 32, pos + 1 );
            //std::cout << next << " " << std::string::npos << std::endl;
            if( next == std::string::npos ) return;
            pos = fileBuffer.find_first_of( 32, next );
            w1 = fileBuffer.substr( next, pos - next );
            //std::cout << w1.size() << std::endl;
            if( w1.size() < 1 ) break;
            if( std::find( dictionary[key].begin(), dictionary[key].end(), w1 ) == dictionary[key].end() ) 
                dictionary[key].push_back( w1 );
            key = key.substr( key.find_first_of( 32 ) + 1 ) + " " + w1;
            //std::cout << key << std::endl;
        }
    }
}