#include "MyPriorityQueue.hpp"
#include "proj5.hpp"
#include <iostream>
#include <unordered_set>
#include <fstream>

void testCases(int x);
int main()
{
//    for(int x = 1; x <= 7 ; x++)
        testCases(5);
	return 0;
    
}

void testCases(int x)
{
    switch (x) {
        case 1: {
            // tests isEmpty, size, insert & extract min.
            MyPriorityQueue<char> tmp;
            assert(tmp.isEmpty() && tmp.size()==0);
            tmp.insert('a');
            tmp.insert('b');
            tmp.insert('c');
            tmp.insert('d');
            assert(!tmp.isEmpty() && tmp.size()==4);
            assert(tmp.min()=='a');
            tmp.extractMin();
            assert(!tmp.isEmpty() && tmp.size()==3);
            assert(tmp.min()=='b');
            std::cout << "TestCase [1] : passed!" << std::endl;
        }
            break;
        case 2: {
            // tests exception in extractMin.
            MyPriorityQueue<char> tmp;
            try {
                tmp.extractMin();
            } catch (...) {
                std::cout << "TestCase [2] : passed!" << std::endl;
            }
        } break;
        case 3: {
            // tests exception in min.
            MyPriorityQueue<char> tmp;
            try {
                tmp.min();
            } catch (...) {
                std::cout << "TestCase [3] : passed!" << std::endl;
            }
        } break;
        case 4: {
            MyPriorityQueue<int> p;
            p.insert(1);
            p.insert(20);
            p.insert(13);
            p.insert(17);
            p.insert(9);
            p.insert(40);
            p.insert(80);
            p.insert(70);
            p.insert(65);
            p.insert(100);
            p.insert(0);
            p.insert(-5);
            for(int i = 1; i < 13; i++)
                p.extractMin();
            try{
                p.extractMin();
            } catch(...){
                std::cout << "TestCase [4] : passed!" << std::endl;
            }
        } break;
        case 5: {
            std::string WORD_ONE = "ant";
            std::string WORD_TWO = "eat";
            auto CORRECT_LENGTH = 5;


            std::unordered_set<std::string> words;
            std::ifstream in("/Users/cesarbelvedere/project5/project5/project5-xcode/project5-xcode/words.txt");
            loadWordsIntoTable(words, in);


            std::vector< std::string > r = convert(WORD_ONE, WORD_TWO, words);
            for(auto x : r)
                std::cout << x << std::endl;
            assert(r.size() == CORRECT_LENGTH);
            
            std::cout << "TestCase [5] : passed!" << std::endl;
        } break;
        case 6: {
            std::string WORD_ONE = "element";
            std::string WORD_TWO = "changes";
            auto CORRECT_LENGTH = 10;
            
            std::unordered_set<std::string> words;
            std::ifstream in("/Users/cesarbelvedere/project5/project5/project5-xcode/project5-xcode/words.txt");
            loadWordsIntoTable(words, in);

            std::vector< std::string > r = convert(WORD_ONE, WORD_TWO, words);
            std::cout << r.size() << std::endl;
            for(auto x : r)
                std::cout << x << std::endl;
            assert(r.size() == CORRECT_LENGTH);
            std::cout << "TestCase [6] : passed!" << std::endl;
        } break;
        case 7: {
            std::string WORD_ONE = "math";
            std::string WORD_TWO = "hard";
            auto CORRECT_LENGTH = 0;
            
            std::unordered_set<std::string> words;
            std::ifstream in("/Users/cesarbelvedere/project5/project5/project5-xcode/project5-xcode/word.txt");
            loadWordsIntoTable(words, in);

            std::vector< std::string > r = convert(WORD_ONE, WORD_TWO, words);
//            std::cout << r.size() << std::endl;
            assert(r.size() == CORRECT_LENGTH);
            std::cout << "TestCase [7] : passed!" << std::endl;
        } break;
        default:
            break;
    }
}

