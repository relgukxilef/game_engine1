#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <boost/intrusive/list.hpp>

#include "pass.h"

namespace ge1 {

    struct [[deprecated]] composition {
        composition();

        void render();

        boost::intrusive::list<pass, constant_time_size<false>> passes;
    };

}

#endif // COMPOSITION_H
