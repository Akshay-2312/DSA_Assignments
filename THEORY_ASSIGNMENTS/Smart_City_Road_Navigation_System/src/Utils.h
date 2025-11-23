#pragma once
#include <bits/stdc++.h>

namespace Utils {
    inline void clearInput() { 
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }

    inline int readInt(const std::string &prompt) { 
        std::cout << prompt; int x; 
        std::cin >> x; return x; 
    
    }

    inline double readDouble(const std::string &prompt) {
        std::cout << prompt; 
        double x; 
        std::cin >> x; 
        return x; 
    }

    inline std::string readLine(const std::string &prompt) { 
        std::cout << prompt; 
        std::string s; 
        std::getline(std::cin, s); 
        
        if(s.empty()){ 
            std::getline(std::cin, s);
        } 
        return s;
    }
}