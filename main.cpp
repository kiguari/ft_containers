#include "vector.hpp"
#include "stack.hpp"
#include "set.hpp"
#include "map.hpp"

int main()
{
    unsigned int start_time =  clock();

    ft::vector<int> vector1(10, 7);
    vector1.push_back(3);
    ft::vector<int>::iterator vector1_it = vector1.begin();
    std::cout << *vector1_it << std::endl;

    ft::stack<int> stack1;
    stack1.push(10);

    ft::map<int, std::string> map1;
    map1.insert(ft::make_pair(1, "tryu"));
    ft::map<int, std::string>::iterator map1_it = map1.begin();
    std::cout << map1_it->first << std::endl;
    ft::make_pair(1, "tryu");//

    ft::set<int> set1;
    set1.insert(1);
    ft::set<int>::iterator set1_it = set1.begin();
    std::cout << *set1_it << std::endl;

    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    std::cout << search_time << std::endl;
    // system("leaks a.out");
    return(0);
}