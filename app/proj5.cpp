#include "proj5.hpp"
#include "MyPriorityQueue.hpp"
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <stack>

void loadWordsIntoTable(std::unordered_set<std::string> & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}


std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words)
{
    std::vector< std::string > ret, ret2;
    // "Base" cases
    if(s1.size() != s2.size())
        return ret;
    if(s1 == s2)
        return ret;
    
    // lambda expression that generates how many "letters away" a word is.
    auto generateDiff = [](std::string a1, std::string a2)
        {
            int temp = 0;
            for(int i = 0; i < a1.size(); i++)
                if (a1[i] != a2[i]) temp++;
            return temp;
        };
    
    // Algorithm:
    std::unordered_map<std::string, std::pair<int, std::string>> discovered;
    MyPriorityQueue<Node> pq;
    bool foundS2 = false;

    pq.insert({s1, "", 0, generateDiff(s1, s2)});
    
    while(!pq.isEmpty())
    {
        Node tmp = pq.min();
        pq.extractMin();
        int sumUp = tmp.lc_distance + tmp.lc_distance;
        discovered.insert({tmp.word, {sumUp+1, ""}});

        for(std::string x : words)
        {
            if(x.size() == s1.size())
            {
                if(generateDiff(x, tmp.word) == 1 && discovered.find(x) == discovered.end())
                {
                    pq.insert({x, tmp.word, tmp.lc_distance+1, generateDiff(x, s2)});
                    discovered.insert({x, {(tmp.lc_distance+1) + generateDiff(x, s2), tmp.word}});
                    if(x == s2){
                        foundS2 = true;
                    }
                }
                else if(generateDiff(x, tmp.word) == 1 && discovered.find(x) != discovered.end()){
                    if(discovered.find(x)->second.first > ((tmp.lc_distance + 1) + generateDiff(x, s2)))
                    {
                        pq.insert({x, tmp.word, tmp.lc_distance + 1, generateDiff(x, s2)});
                        discovered.find(x)->second = {(tmp.lc_distance + 1) + generateDiff(x, s2), tmp.word};
                        if(x == s2)
                            foundS2 = true;
                    }
                }

            }
        }
    }
    
    if(!foundS2)
        return ret;
    
    else{
        ret.push_back(s2);
        std::string next = discovered.find(s2)->second.second;
        
        while(next != "")
        {
            ret.push_back(next);
            next = discovered.find(next)->second.second;
        }
        
        // this is used to reverse vector.
        for(long a = ret.size()-1, b = 0; a >= 0; a--, b++)
            ret2.push_back(ret[a]);
        return ret2;
    }
}
