#pragma once
#include <string>

class XmlParser {
public:
    inline static XmlParser* getInstance() {return instance = (instance != nullptr) ? instance : new XmlParser();}
    void parse(std::string source);

private:
    XmlParser() {}
    static XmlParser* instance;
};
