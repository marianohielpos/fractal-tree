#include <string>

#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:

    int* getId();

    std::string* getDescription();

    std::string* getCode();

    std::string* getFields();

    void setId(int* id);

    void setCode(const char* cod);

    void setDescription(const char* description);

    Node(int* id, const char* cod, const char* description);

    ~Node(void);

protected:

private:

    int* id;
    std::string* code;
    std::string* description;

};

#endif // _NODE_H_
