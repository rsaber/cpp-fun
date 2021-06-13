
template <auto ShortFlag, auto LongFlag>
struct Flag {
    constexpr auto getS() const { return ShortFlag; }
    constexpr auto getL() const { return LongFlag; }
    constexpr auto operator()() const { return ShortFlag; }
};

#define CreateFlag(FlagName, Short, Long) \
    extern const char FlagName ## shortHand [] = Short; \
    extern const char FlagName ## longHand [] = Long; \
    constexpr Flag<FlagName ## shortHand, FlagName ## longHand> FlagName; 

CreateFlag(DirectoryFlag, "-d", "--directory");

int main()
{
    std::cout << DirectoryFlag.getS() << std::endl;
}
