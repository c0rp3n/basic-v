# Style guide
This document lays out the general style that should be followed for Basic-V.

## Example
```cpp
#include <cstdint>

namespace bv
{
    enum struct MyEnum : uint64_t
    {
        One,
        Two,
        Three,
    }

    class MyClass
    {
    public:
        MyEnum variableEnum;
    private:
        uint32_t variableInt;

    public:
        MyClass()
        {
            this->variableEnum = MyEnum::One;
            this->variableInt = -1ul;
        }

        public void MyFunction()
        {
            return;
        }
    }
}
```

## Naming
#### Classes / Structs
Should use pascal case `ClassName` / `StructName`.
#### Functions
Should use pascal case `FunctionName`.
#### Variables
Should use camel case `variableName`.
#### Enums
Should use pascal case `EnumName`.
#### Defines
Should use upper snake case `DEFINE_NAME`.

## Layout
#### Tabs
Should be 4 spaces no tab charactors.
