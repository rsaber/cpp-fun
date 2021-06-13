#include <type_traits>
#include <iostream>
#include <string_view>

template <auto Name, int Length>
struct Unit {
    constexpr static auto name = Name;
    constexpr static auto length = Length;
};

namespace Units {
    extern const char KM[] = "KM";
    extern const char M[] = "M";
}

namespace detail {
    template <typename DummyT>
    auto _static_assert() {
        static_assert(sizeof(DummyT) != sizeof(DummyT), "UNDEFINED UNIT REFERENCED!");
    }

    template <auto ToFind, typename First, typename... Rest>
    auto find() {
        if constexpr(ToFind == First::name) {
            return First{};
        }
        else if constexpr(sizeof...(Rest) == 0) {
            return _static_assert<ToFind>();
        }
        else 
        {
            return find<ToFind, Rest...>();
        }
    }
}

template <typename... Units>
class UnitConverter {
    private:
    public:
    constexpr UnitConverter() = default;
    
    template <auto FromUnit, auto ToUnit>
    constexpr auto ratio() {
        return detail::find<FromUnit, Units...>().length / detail::find<ToUnit, Units...>().length;
    }
};



int main() {
    UnitConverter<
	Unit<Units::KM, 1000>, 
	Unit<Units::M, 1>
    > graph;

    std::cout << graph.ratio<Units::KM, Units::M>() << std::endl;
}


