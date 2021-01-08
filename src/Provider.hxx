#pragma once

#include <string>

namespace test
{

static int idGenerator = 0;

class Provider
{
public:

    Provider();

    Provider(Provider const&);

    std::string Get() const;

    int GetId() const;

    bool Check() const;

    // for test purposes
    void SetState( bool newState);
    bool GetState() const;

private:
    int         _id;
    bool        _state;
};

} //namespace test

