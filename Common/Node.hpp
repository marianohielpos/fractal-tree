#include <string>
#include <stdint.h>

#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:

    uint32_t* getId();

    std::string* getDescription();

    std::string* getCode();

    const char* getStream();

    uint32_t getSize();

    void setId(int id);

    void setCode(const char* cod);

    void setDescription(const char* description);

    Node(uint32_t id, const char* cod, const char* description);

    Node(char* biteStream);

    ~Node(void);

protected:

private:

    uint32_t* id;
    std::string* code;
    std::string* description;

};

#endif // _NODE_H_
