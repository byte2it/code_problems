#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

class JSONNode;
using JSONObject = std::map<std::string, std::shared_ptr<JSONNode>>;
using JSONList = std::vector<std::shared_ptr<JSONNode>>;

class JSONNode {
    enum class Type { OBJECT, LIST, STRING, NUMBER, BOOLEAN, NULL_TYPE };
    union Values {
        JSONObject* object;
        JSONList* list;
        std::string* s;
        float fValue;
        bool bValue;
    } values;
    Type type;

public:
    JSONNode() {}
    JSONNode(Type t) { type = t; }
    auto returnObject() {
        if (type == Type::OBJECT)
            return *values.object;
        throw std::logic_error("Improper return");
    }
    auto returnList() {
        if (type == Type::LIST)
            return *values.list;
        throw std::logic_error("Improper return");
    }
    auto returnString() {
        if (type == Type::STRING)
            return *values.s;
        throw std::logic_error("Improper return");
    }
    auto returnFloat() {
        if (type == Type::NUMBER)
            return values.fValue;
        throw std::logic_error("Improper return");
    }
    void setObject(JSONObject* object) {
        this->values.object = object;
        type = Type::OBJECT;
    }
    void setString(std::string* s) {
        this->values.s = s;
        type = Type::STRING;
    }
    void setNumber(float f) {
        this->values.fValue = f;
        type = Type::NUMBER;
    }
    void setList(JSONList* list) {
        this->values.list = list;
        type = Type::LIST;
    }
    void setBoolean(bool v) {
        this->values.bValue = v;
        type = Type::BOOLEAN;
    }
    void setNull() {
        type = Type::NULL_TYPE;
    }

    std::string toString(int indentationLevel) {
        std::string spaceString = std::string(indentationLevel, ' ');

        std::string outputString = "";
        switch (type) {
        case Type::STRING: {
            outputString += spaceString + *values.s;
            break;
        }
        case Type::NUMBER: {
            outputString += spaceString + std::to_string(values.fValue);
            break;
        }
        case Type::BOOLEAN: {
            outputString += spaceString + (values.bValue ? "true" : "false");
            break;
        }
        case Type::NULL_TYPE: {
            outputString += spaceString + "null";
            break;
        }
        case Type::LIST: {
            std::cout << "[";
            int index = 0;
            for (auto node : (*values.list)) {
                outputString += node->toString(indentationLevel + 1);
                if (index < (*values.list).size() - 1) {
                    outputString += spaceString + ", ";
                }
                index++;
            }
            outputString += spaceString + "]\n";
            break;
        }
        case Type::OBJECT: {
            outputString += "{\n";
            for (JSONObject::iterator i = (*values.object).begin();
                i != (*values.object).end(); i++) {
                outputString += spaceString + i->first + ": ";
                outputString += i->second->toString(indentationLevel + 1);
                JSONObject::iterator next = i;
                next++;
                if ((next) != (*values.object).end()) {
                    outputString += spaceString + ",";
                }
                outputString += spaceString + "\n";
            }
            outputString += "}\n";
            return outputString;
        }
        }
    }

    void printNode(int indentationLevel) {
        std::cout << toString(indentationLevel);
    }
};

enum class TOKEN {
    CURLY_OPEN,
    CURLY_CLOSE,
    COLON,
    STRING,
    NUMBER,
    ARRAY_OPEN,
    ARRAY_CLOSE,
    COMMA,
    BOOLEAN,
    NULL_TYPE
};

struct Token {
    std::string value;
    TOKEN type;
};

class Tokenizer {
    std::fstream file;
    size_t prevPos;

public:
    Tokenizer(std::string fileName) {
        file.open(fileName, std::ios::in);
        if (!file.good())
            std::cout << "File open error" << std::endl;
    }
    auto getWithoutWhiteSpace() {
        char c = ' ';
        while ((c == ' ' || c == '\n')) {
            file.get(c);

            if ((c == ' ' || c == '\n') && !file.good())
                throw std::logic_error("Ran out of tokens");
            else if (!file.good())
                return c;
        }
        return c;
    }
    auto getToken() {
        char c;
        if (file.eof())
            std::cout << "Exhaused tokens" << std::endl;

        prevPos = file.tellg();
        c = getWithoutWhiteSpace();

        std::cout << c << std::endl;
        struct Token token;
        if (c == '"') {
            token.type = TOKEN::STRING;
            token.value = "";
            file.get(c);
            while (c != '"') {
                token.value += c;
                file.get(c);
            }
        }
        else if (c == '{')
            token.type = TOKEN::CURLY_OPEN;
        else if (c == '}')
            token.type = TOKEN::CURLY_CLOSE;
        else if (c == '-' || (c >= '0' && c <= '9')) {
            token.type = TOKEN::NUMBER;
            token.value = "";
            token.value += c;
            std::streampos prevCharPos = file.tellg();
            while ((c == '-') || (c >= '0' && c <= '9') || c == '.') {
                prevCharPos = file.tellg();
                file.get(c);

                if (file.eof())
                    break;
                else {
                    if ((c == '-') || (c >= '0' && c <= '9') || (c == '.'))
                        token.value += c;
                    else
                        file.seekg(prevCharPos);
                }
            }
        }
        else if (c == 'f') {
            token.type = TOKEN::BOOLEAN;
            token.value = "False";
            file.seekg(4, std::ios_base::cur);
        }
        else if (c == 't') {
            token.type = TOKEN::BOOLEAN;
            token.value = "True";
            file.seekg(3, std::ios_base::cur);
        }
        else if (c == 'n') {
            token.type = TOKEN::NULL_TYPE;
            file.seekg(3, std::ios_base::cur);
        }
        else if (c == '[')
            token.type = TOKEN::ARRAY_OPEN;
        else if (c == ']')
            token.type = TOKEN::ARRAY_CLOSE;
        else if (c == ':')
            token.type = TOKEN::COLON;
        else if (c == ',')
            token.type = TOKEN::COMMA;
        return token;
    }

    auto hasMoreTokens() {
        return !file.eof();
    }

    void rollBackToken() {
        if (file.eof())
            file.clear();

        file.seekg(prevPos);
    }
};

class JSONParser {
    std::fstream file;
    std::shared_ptr<JSONNode> root;
    std::unique_ptr<JSONNode> current;
    Tokenizer tokenizer;

public:
    JSONParser(const std::string filename) : tokenizer(filename) {}

    void parse() {
        std::string key = "";
        while (tokenizer.hasMoreTokens()) {
            Token token;
            try {
                token = tokenizer.getToken();
                switch (token.type) {
                case TOKEN::CURLY_OPEN: {
                    std::shared_ptr<JSONNode> parsedObject = parseObject();
                    parsedObject->printNode(0);
                    if (!root) {
                        root = parsedObject;
                    }
                    break;
                }
                case TOKEN::ARRAY_OPEN: {
                    std::shared_ptr<JSONNode> parsedList = parseList();
                    if (!root) {
                        root = parsedList;
                    }
                    break;
                }

                case TOKEN::STRING: {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSONNode> parsedString = parseString();
                    if (!root) {
                        root = parsedString;
                    }
                    break;
                }
                case TOKEN::NUMBER: {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSONNode> parsedNumber = parseNumber();
                    if (!root) {
                        root = parsedNumber;
                    }
                    break;
                }

                case TOKEN::BOOLEAN: {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSONNode> parsedBoolean = parseBoolean();
                    break;
                }
                }
            }

            catch (std::logic_error e) {
                break;
            }
        }
    }

    std::shared_ptr<JSONNode> parseObject() {
        std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
        JSONObject* keyObjectMap = new JSONObject();
        bool hasCompleted = false;
        while (!hasCompleted) {
            if (tokenizer.hasMoreTokens()) {
                Token nextToken = tokenizer.getToken();
                std::string key = nextToken.value;
                std::cout << key << std::endl;
                tokenizer.getToken();
                nextToken = tokenizer.getToken();
                std::shared_ptr<JSONNode> node;
                switch (nextToken.type) {
                case TOKEN::STRING: {
                    tokenizer.rollBackToken();
                    (*keyObjectMap)[key] = parseString();
                    break;
                }
                case TOKEN::ARRAY_OPEN: {
                    (*keyObjectMap)[key] = parseList();
                    break;
                }
                case TOKEN::NUMBER: {
                    tokenizer.rollBackToken();
                    (*keyObjectMap)[key] = parseNumber();
                    break;
                }
                case TOKEN::CURLY_OPEN: {
                    (*keyObjectMap)[key] = parseObject();
                    break;
                }
                case TOKEN::BOOLEAN: {
                    tokenizer.rollBackToken();
                    (*keyObjectMap)[key] = parseBoolean();
                    break;

                }
                case TOKEN::NULL_TYPE: {
                    (*keyObjectMap)[key] = parseNull();
                    break;
                }
                }
                nextToken = tokenizer.getToken();
                if (nextToken.type == TOKEN::CURLY_CLOSE) {
                    hasCompleted = true;
                    break;
                }
            }
            else
                throw std::logic_error("No more tokens");
        }
        node->setObject(keyObjectMap);
        return node;
    }
    std::shared_ptr<JSONNode> parseString() {
        std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
        Token token = tokenizer.getToken();
        std::string* sValue = new std::string(token.value);
        node->setString(sValue);
        return node;
    }
    std::shared_ptr<JSONNode> parseNumber() {
        std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
        Token nextToken = tokenizer.getToken();
        std::string value = nextToken.value;
        std::cout << value << std::endl;
        float fValue = std::stof(value);
        node->setNumber(fValue);
        return node;
    }

    std::shared_ptr<JSONNode> parseList() {
        std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
        JSONList* list = new JSONList();
        bool hasCompleted = false;
        while (!hasCompleted) {
            if (!tokenizer.hasMoreTokens())
                throw std::logic_error("No more tokens");
            else {
                Token nextToken = tokenizer.getToken();
                std::shared_ptr<JSONNode> node;
                switch (nextToken.type) {
                case TOKEN::ARRAY_OPEN: {
                    node = parseList();
                    break;
                }
                case TOKEN::CURLY_OPEN: {
                    node = parseObject();
                    break;
                }
                case TOKEN::STRING: {
                    tokenizer.rollBackToken();
                    node = parseString();
                    break;
                }
                case TOKEN::NUMBER: {
                    tokenizer.rollBackToken();
                    node = parseNumber();
                    break;
                }
                case TOKEN::BOOLEAN: {
                    tokenizer.rollBackToken();
                    node = parseBoolean();
                    break;

                }
                case TOKEN::NULL_TYPE: {
                    node = parseNull();
                    break;
                }
                }
                list->push_back(node);
                nextToken = tokenizer.getToken();
                if (nextToken.type == TOKEN::ARRAY_CLOSE) {
                    hasCompleted = true;
                }
            }
        }
        node->setList(list);
        return node;
    }
    std::shared_ptr<JSONNode> parseBoolean() {
        std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
        Token nextToken = tokenizer.getToken();
        node->setBoolean(nextToken.value == "True" ? true : false);
        return node;
    }

    std::shared_ptr<JSONNode> parseNull() {
        std::shared_ptr<JSONNode> node = std::make_shared<JSONNode>();
        node->setNull();
        return node;
    }
};

int main(int argc, char* argv[]) {
    std::string filename = argv[1];
    JSONParser parser(filename);
    parser.parse();
}
