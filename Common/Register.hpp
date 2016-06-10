#include <string>
#include <stdint.h>

#ifndef _REGISTER_H_
#define _REGISTER_H_

class Register
{
public:

    uint32_t getId();

    const char* getDescription();

    const char* getCode();

    bool getStream(char*, uint32_t size);

    uint32_t getSize();

    void setId(uint32_t id);

    void setCode(const char* cod);

    void setDescription(const char* description);

    Register(uint32_t id, const char* cod, const char* description);

    Register(const char* byteStream);

    Register(const Register& _register);

    Register();

    ~Register(void);

protected:

private:

    uint32_t id;
    std::string code;
    std::string description;

};

#endif // _REGISTER_H_
