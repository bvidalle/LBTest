#include "Provider.hxx"

#include <sstream>

namespace test
{

Provider::Provider() : _id (++idGenerator) , _state(true)
{
}

std::string Provider::Get( ) const
{
    std::ostringstream s;
    s << _id;
    return s.str();
}

int Provider::GetId( ) const
{
    return _id;
}

bool Provider::Check( ) const
{
    return _state;
}

void Provider::SetState( bool newState)
{
    _state = newState;;
}

bool Provider::GetState( ) const
{
    return _state;
}


}
