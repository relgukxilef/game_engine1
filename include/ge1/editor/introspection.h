#pragma once

#include <tuple>
#include <array>
#include <memory>
#include <vector>
#include <string>
#include <sstream>

namespace ge1 {

    struct abstract_value {
        abstract_value() = default;
        virtual ~abstract_value() = default;

        virtual unsigned size() const = 0;
        virtual std::unique_ptr<abstract_value> child(unsigned index) const = 0;
        virtual const char* child_name(unsigned index) const = 0; // can be null
        virtual std::string value_string() const = 0;
    };

    template<typename T>
    struct value : public abstract_value {
        value(T& v) : v(v) {}
        ~value() override = default;

        unsigned size() const override;
        const char* child_name(unsigned index) const override;
        std::unique_ptr<abstract_value> child(unsigned index) const override;
        std::string value_string() const override;

        T& v;
    };

    template<typename T>
    value<T> make_value(T& t) {
        return value<T>(t);
    }

    template<typename Type>
    struct fundamental_accessor_t {
        unsigned size(Type& v) const { return 0; }
        std::unique_ptr<abstract_value> child(Type& v, unsigned index) const {
            return nullptr;
        }
        const char* child_name(Type& v, unsigned index) const {
            return nullptr;
        }
        std::string value_string(Type& v) const {
            std::stringstream s;
            s << v;
            return s.str();
        }
    };

    template<typename Type>
    struct range_accessor_t {
        unsigned size(Type& v) const { return std::end(v) - std::begin(v); }
        std::unique_ptr<abstract_value> child(Type& v, unsigned index) const {
            return std::make_unique<value<decltype(*std::begin(v))>>(
                *(std::begin(v) + index)
            );
        }
        const char* child_name(Type& v, unsigned index) const { return nullptr; }
        std::string value_string(Type& v) const {
            std::stringstream s;
            s << &v;
            return s.str();
        }
    };

    namespace detail {
        template<typename T, typename C>
        void create_member(
            abstract_value*& av, unsigned index, unsigned& i, C& object,
            T member
        ) {
            auto& v = object.*member;
            if (i == index)
                av = new value<decltype(v)>(v);
            i++;
        }
    }

    template<typename Type, auto... Members>
    struct struct_accessor_t {
        std::array<const char*, sizeof...(Members)> identifiers;
        unsigned size(Type& v) const { return sizeof...(Members); }
        std::unique_ptr<abstract_value> child(Type& v, unsigned index) const {
            unsigned i = 0;
            abstract_value* value = nullptr;
            (detail::create_member(value, index, i, v, Members), ...);
            return std::unique_ptr<abstract_value>(value);
        }
        const char* child_name(Type& v, unsigned index) const {
            return identifiers[index];
        }
        std::string value_string(Type& v) const {
            std::stringstream s;
            s << &v;
            return s.str();
        }
    };

    template<typename C, typename T>
    C get_class(T C::*);

    template<auto M>
    struct member_t {
        const char* i;
        inline static constexpr auto m = M;
        typedef decltype(get_class(M)) t;
    };

    inline constexpr const char* identifier(const char* i) {
        return i;
    }

    template<auto M>
    constexpr auto member(const char* i) {
        return member_t<M>{identifier(i)};
    }

    template<typename T1, typename... T>
    constexpr auto make_struct_accessor(T1 t1, T... t) {
        return struct_accessor_t<typename T1::t, T1::m, T::m...>{
            std::array<const char*, sizeof...(t) + 1>{ t1.i, t.i... }
        };
    }

    template<typename T>
    constexpr const fundamental_accessor_t<T> accessor = {};

    template<typename T>
    constexpr const range_accessor_t<std::vector<T>> accessor<std::vector<T>> =
        {};

    template<typename T>
    constexpr const auto accessor<T&> = accessor<T>;

    template<typename T>
    unsigned value<T>::size() const { return accessor<T>.size(v); }

    template<typename T>
    const char* value<T>::child_name(unsigned index) const {
        return accessor<T>.child_name(v, index);
    }

    template<typename T>
    std::unique_ptr<abstract_value> value<T>::child(unsigned index) const {
        return accessor<T>.child(v, index);
    }

    template<typename T>
    std::string value<T>::value_string() const {
        return accessor<T>.value_string(v);
    }
}
