#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "serdepp.hpp"

using namespace serdepp;

struct SerializeMe {
    int a, b, c, d;
    
    SerializeMe() = default;
    SerializeMe(int a, int b) {
        this->a = a;
        this->b = b;
        c = 0;
        d = 0;
    }
};

struct SerializeMe2 {
    int a;
    int b;
    std::vector<std::vector<std::vector<int>>> vec;
    int c;
    float f;
    double d;
    char ch;
    std::string name;
    SerializeMe sm;
    
    bool operator==(const SerializeMe2& other) const {
        if(a != other.a) return false;
        if(b != other.b) return false;
        if(c != other.c) return false;
        if(f != other.f) return false;
        if(d != other.d) return false;
        if(ch != other.ch) return false;
        if(name != other.name) return false;
        if(memcmp(&sm, &other.sm, sizeof(sm)) != 0) return false;
        
        if(vec.size() != other.vec.size()) return false;
        
        for(int i = 0; i != vec.size(); i++) {
            if(vec[i].size() != other.vec[i].size()) return false;

            for(int j = 0; j != vec[i].size(); j++) {
                if(vec[i][j].size() != other.vec[i][j].size()) return false;

                for(int k = 0; k != vec[i][j].size(); k++) {
                    if(vec[i][j][k] != other.vec[i][j][k]) return false;
                }
            }
        }
            return true;
    }
};


int main(int argc, char** argv) {
    
    SerializeMe sm;
    sm.a = 1;
    sm.b = 2;
    sm.c = 3;
    sm.d = 4;

    SerializeMe2 testVal = {
        1, 
        2, 
        {{{1, 2, 3}, {4, 5}, {43}}, {{3, 3, 23}, {123}, {123, 45}}, {{123, 123, 123, 123}, {123, 123}}}, 
        3,
        6.1f,
        4.0,
        '@',
        std::string("yes yes yes yes"),
        sm
    };

    {

        std::cout << "struct initialized" << std::endl;

        std::uint64_t size = getSerializedSize(testVal);
        std::uint8_t* b = new std::uint8_t[size];
        serialize(b, testVal);

        std::cout << "serialized" << std::endl;
        {
            std::ofstream f("test.bin");
            f.write((char*)b, size);
            f.flush();
        }
    } 

    {
        std::uint8_t* blob;
        {
            std::ifstream f("test.bin");

            f.seekg(0, std::ios_base::end);
            std::size_t size = f.tellg();
            blob = new std::uint8_t[size];
            f.seekg(0, std::ios_base::beg);
            f.read((char*)blob, size);
        }
        std::cout << "read from file" << std::endl;

        SerializeMe2 b;
        deserialize(blob, b);
        std::cout << "deserialized" << std::endl;

        std::cout << b.a << " " << b.b << " " << b.c << std::endl << std::endl;
        for(std::vector<std::vector<int>>& v : b.vec) {
            for(std::vector<int>& e : v) {
                for(int& value : e) {
                    std::cout << value << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << b.f << " " << b.d << " " << b.ch << " " << b.name << std::endl;
        std::cout << b.sm.a << "\n";
        std::cout << b.sm.b << "\n";
        std::cout << b.sm.c << "\n";
        std::cout << b.sm.d << std::endl;

        if(b == testVal) {
            std::cout << "TEST PASSED!!!\n";
            return 0;
        } else {
            std::cout << "TEST FAILED :(\n";
            return 1;
        }
    }
}

