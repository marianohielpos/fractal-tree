#include <string>
#include <stdint.h>

#ifndef _REGISTER_H_
#define _REGISTER_H_

class Register
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

    Register(uint32_t id, const char* cod, const char* description);

    Register(char* biteStream);

    Register(Register* _register);

    ~Register(void);

protected:

private:

    uint32_t* id;
    std::string* code;
    std::string* description;

};

#endif // _REGISTER_H_
