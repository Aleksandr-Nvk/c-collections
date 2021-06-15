# C collections

This is an implementation of basic C# collections on C.
These are: List, Linked List, Stack, Queue and Dictionary. All of them are based on default C arrays.
You can check usage examples [here](https://github.com/Aleksandr-Nvk/c-collections/tree/main/usages). Source files can be seen [here](https://github.com/Aleksandr-Nvk/c-collections/tree/main/source).

# "Generic" version
[collections_generic.h](https://github.com/Aleksandr-Nvk/c-collections/blob/main/source/collections_generic.h) contains macros which let achieve type-independent usage of C collections. Since C doesn't provide us with generics, calling these macros will (in compile time) paste API for particular type and let us use the collections with any possible data types, except pointers and composite data types like "unsigned int", "long double" etc., since macros require single type names to be passed. You can still use aliases like "uint32_t" instead of "unsigned int".

# Pointer version
Everything in [source](https://github.com/Aleksandr-Nvk/c-collections/tree/main/source) omitting collections_generic.h is source code for collections that only work with pointers. It is particularly useful for strings. Pointer version of the C collections doesn't need to be initialized like "Generic" version.
