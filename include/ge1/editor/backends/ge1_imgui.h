#pragma once

#include <sstream>

#include "imgui.h"
#include "../introspection.h"

namespace ge1 {

    void tree_node(const abstract_value& v) {
        auto size = v.size();
        for (unsigned i = 0; i < size; i++) {
            auto identifier = v.child_name(i);
            std::stringstream label;
            if (identifier) {
                label << identifier;
            } else {
                label << '[' << i << ']';
            }
            auto child = v.child(i);
            label << ' ' << child->value_string();
            if (ImGui::TreeNode(label.str().c_str())) {
                tree_node(*child);
                ImGui::TreePop();
            }
        }
    }
}
