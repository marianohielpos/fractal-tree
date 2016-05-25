#include <string>

#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:

    int* getId();

    std::string getDescription();

    std::string getCode();

    void setId(int* id);

    void setCode(std::string cod);

    void setDescription(std::string description);

    Node(int* id, std::string cod, std::string description);

protected:

private:

    int* id;
    std::string cod;
    std::string description;

};

#endif // _NODE_H_
