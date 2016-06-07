#include <string>
#include <stdint.h>

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

class Registry
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

    Registry(uint32_t id, const char* cod, const char* description);

    Registry(char* biteStream);

    ~Registry(void);

protected:

private:

    uint32_t* id;
    std::string* code;
    std::string* description;

};

#endif // _REGISTRY_H_
