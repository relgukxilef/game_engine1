#ifndef PASS_H
#define PASS_H

#include <boost/intrusive/list.hpp>

#include "renderable.h"

namespace ge1 {

    using namespace boost::intrusive;

    struct pass : public list_base_hook<link_mode<auto_unlink>> {
        pass();

        list<renderable, constant_time_size<false>> renderables;
    };

}

#endif // PASS_H
