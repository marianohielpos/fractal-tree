

#include <std>
#define CODE_SIZE 3



#ifndef _NODE_H_
#define _NODE_H_



class Node
{
public:

    int getId();

    void setId(int foreignId);

    char* getCod();

    void setCod(std::string cod);

    char* setDescription(std::string foreignDescription);

    char* getDescription();

    Node(int* id, char* cod, char* description);

protected:

    int* id;
    char* cod;
    char* description;

private:


};

#endif // _NODE_H_
