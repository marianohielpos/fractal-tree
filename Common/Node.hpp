#include <string>

#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:

    size_t* getId();

    std::string* getDescription();

    std::string* getCode();

    const char* getStream();

    size_t getSize();

    void setId(int id);

    void setCode(const char* cod);

    void setDescription(const char* description);

    Node(size_t id, const char* cod, const char* description);

    Node(char* biteStream);

    ~Node(void);

protected:

private:

    size_t* id;
    std::string* code;
    std::string* description;

};

#endif // _NODE_H_
