// po6
#include <po6/net/location.h>

// busybee
#include "busybee_mapper.h"
#include "busybee_mapper_c.h"

class mapper : public busybee_mapper {
    public:
        mapper(lookup_func_t lookup);
        ~mapper() throw ();

    public:
        virtual bool lookup(uint64_t server_id, po6::net::location* bound_to);

    private:
        lookup_func_t lookup_func;
};

mapper :: mapper(lookup_func_t _lookup)
{
    this->lookup_func = _lookup;
}

mapper :: ~mapper() throw ()
{
}

bool
mapper :: lookup(uint64_t server_id,
                 po6::net::location* bound_to)
{
    const char* address;
    uint16_t port;

    bool res;
    if (this->lookup_func(server_id, &address, &port) > 0)
        res = true;
    else
        res = false;

    *bound_to = po6::net::location(address, port);
    return res;
}

extern "C" {

busybee_mapper*
busybee_mapper_create(lookup_func_t lookup)
{
    return (busybee_mapper*) new mapper(lookup);
}

}