#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <boost/intrusive/list.hpp>

namespace ge1 {

    using namespace boost::intrusive;

    struct renderable : public list_base_hook<link_mode<auto_unlink>> {
        virtual ~renderable() = default;

        virtual void render() = 0;
    };

}

#endif // RENDERABLE_H
