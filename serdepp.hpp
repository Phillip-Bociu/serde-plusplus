#pragma once
#include <type_traits>
#include <cstdint>
#include <string.h>

#if defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE __attribute__((always_inline)) inline
#endif

/*======================================
                Interface
 ======================================*/

 
namespace detail {
  // Needed for some older versions of GCC
  template<typename...>
    struct voider { using type = void; };

  // std::void_t will be part of C++17, but until then define it ourselves:
  template<typename... T>
    using void_t = typename voider<T...>::type;

  template<typename T, typename U = void>
    struct is_mappish_impl : std::false_type { };

  template<typename T>
    struct is_mappish_impl<T, void_t<typename T::key_type,
                                     typename T::mapped_type,
                                     decltype(std::declval<T&>()[std::declval<const typename T::key_type&>()])>>
    : std::true_type { };

  template<typename T, typename U = void>
    struct is_keyish_impl : std::false_type { };

  template<typename T>
    struct is_keyish_impl<T, void_t<typename T::key_type,
                                     decltype(std::declval<T&>()[std::declval<const typename T::key_type&>()])>>
    : std::true_type { };
}

template<typename T>
struct is_mappish : detail::is_mappish_impl<T>::type { };

template<typename T>
struct is_keyish : detail::is_keyish_impl<T>::type { };

namespace serdepp {
    // blob: indexable container of bytes
    template<typename Bytes, typename ... Args>
        std::uint64_t FORCE_INLINE serialize(Bytes& blob, const Args& ... args);

    // blob: indexable container of bytes
    template<typename Bytes, typename ... Args>
        std::uint64_t FORCE_INLINE deserialize(const Bytes& blob, Args& ... args);

    template<typename ... Args>
        std::uint64_t FORCE_INLINE getSerializedSize(const Args& ... args);

    template<typename Bytes, bool calculate = false>
        struct Serde {
            std::uint64_t position = 0;

            void FORCE_INLINE deserialize_one(const Bytes& bytes, auto& object);
            void FORCE_INLINE deserialize    (const Bytes& bytes);
            void FORCE_INLINE deserialize    (const Bytes& bytes, auto& first, auto&& ... objects);

            std::uint64_t FORCE_INLINE serialize_one(Bytes& output, const auto& object);
            std::uint64_t FORCE_INLINE serialize    (Bytes& output);
            std::uint64_t FORCE_INLINE serialize    (Bytes& output, auto& first, auto&& ... objects);
        };

    /*======================================
      Implementation
      ======================================*/

    struct any {
        template<class T>
            constexpr operator T(); // non explicit
    };

    template<class T>
        constexpr std::uint64_t FORCE_INLINE number_of_members() {
            using type = std::decay_t<T>;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 50;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 49;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 48;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 47;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 46;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 45;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 44;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 43;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 42;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 41;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 40;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 39;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 38;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 37;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 36;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 35;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 34;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 33;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 32;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 31;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 30;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 29;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 28;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 27;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 26;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 25;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 24;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 23;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 22;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 21;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 20;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 19;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 18;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 17;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 16;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 15;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 14;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 13;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 12;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 11;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 10;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 9;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 8;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{}, any{} }; }) return 7;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{}, any{} }; }) return 6;
            if constexpr (requires { type{ any{}, any{}, any{}, any{}, any{} }; }) return 5;
            if constexpr (requires { type{ any{}, any{}, any{}, any{} }; }) return 4;
            if constexpr (requires { type{ any{}, any{}, any{} }; }) return 3;
            if constexpr (requires { type{ any{}, any{} }; }) return 2;
            if constexpr (requires { type{ any{} }; }) return 1;
            return 0;
        }

    decltype(auto) FORCE_INLINE visit_object(auto&& object, auto && visitor) {
        constexpr std::uint64_t numMembers = number_of_members<decltype(object)>();
        if constexpr(numMembers == 0)  { return visitor(); };
        if constexpr(numMembers == 1)  { return visitor(object); };
        if constexpr(numMembers == 2)  { auto& [a2, a1] = object; return visitor(a2, a1); };
        if constexpr(numMembers == 3)  { auto& [a3, a2, a1] = object; return visitor(a3, a2, a1); };
        if constexpr(numMembers == 4)  { auto& [a4, a3, a2, a1] = object; return visitor(a4, a3, a2, a1); };
        if constexpr(numMembers == 5)  { auto& [a5, a4, a3, a2, a1] = object; return visitor(a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 6)  { auto& [a6, a5, a4, a3, a2, a1] = object; return visitor(a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 7)  { auto& [a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 8)  { auto& [a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 9)  { auto& [a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 10) { auto& [a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 11) { auto& [a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 12) { auto& [a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 13) { auto& [a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 14) { auto& [a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 15) { auto& [a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 16) { auto& [a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 17) { auto& [a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 18) { auto& [a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 19) { auto& [a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 20) { auto& [a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 21) { auto& [a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 22) { auto& [a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 23) { auto& [a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 24) { auto& [a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 25) { auto& [a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 26) { auto& [a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 27) { auto& [a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 28) { auto& [a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 29) { auto& [a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 30) { auto& [a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 31) { auto& [a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 32) { auto& [a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 33) { auto& [a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 34) { auto& [a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 35) { auto& [a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 36) { auto& [a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 37) { auto& [a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 38) { auto& [a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 39) { auto& [a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 40) { auto& [a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 41) { auto& [a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 42) { auto& [a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 43) { auto& [a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 44) { auto& [a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 45) { auto& [a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 46) { auto& [a46, a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a46, a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 47) { auto& [a47, a46, a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a47, a46, a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 48) { auto& [a48, a47, a46, a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a48, a47, a46, a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 49) { auto& [a49, a48, a47, a46, a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a49, a48, a47, a46, a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
        if constexpr(numMembers == 50) { auto& [a50, a49, a48, a47, a46, a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1] = object; return visitor(a50, a49, a48, a47, a46, a45, a44, a43, a42, a41, a40, a39, a38, a37, a36, a35, a34, a33, a32, a31, a30, a29, a28, a27, a26, a25, a24, a23, a22, a21, a20, a19, a18, a17, a16, a15, a14, a13, a12, a11, a10, a9, a8, a7, a6, a5, a4, a3, a2, a1); };
    }


    template<typename Bytes, bool calculate>
        void FORCE_INLINE Serde<Bytes, calculate>::deserialize_one(const Bytes& bytes, auto& object) {
            using T = std::remove_cvref_t<decltype(object)>;

            if constexpr(std::is_trivially_copyable_v<T>) {
                memcpy(&object, &bytes[position], sizeof(T));
                position += sizeof(T);
            } else if constexpr (is_keyish<T>{}) {
                using value_t = decltype(T{}[0]);
                std::uint64_t size;
                deserialize_one(bytes, size);

                object.clear();
                for(std::uint64_t i = 0; i < size; i++) {
                    typename T::key_type key;
                    deserialize_one(bytes, key);
                    if constexpr (is_mappish<T>{}) {
                        typename T::mapped_type value;
                        deserialize_one(bytes, value);
                        object[key] = value;
                    } else {
                        object.insert(key);
                    }
                }
            } else if constexpr (requires { T{}[0]; }){
                using value_t = decltype(T{}[0]);
                std::uint64_t size;
                deserialize_one(bytes, size);

                if constexpr(requires {T{}.resize(size);}) {
                    object.resize(size);
                }

                if constexpr(std::is_trivially_copyable_v<value_t>) {
                    memcpy(&object[0], &bytes[position], size * sizeof(value_t));
                    position += sizeof(value_t);
                } else {
                    for(std::uint64_t index = 0; index != size; index++) {
                        deserialize_one(bytes, object[index]);
                    }
                }
            } else {
                visit_object(object, [&](auto && ... args) {
                    this->deserialize(bytes, args ...);
                });
            }
        }

    template<typename Bytes, bool calculate>
        std::uint64_t FORCE_INLINE Serde<Bytes, calculate>::serialize_one(Bytes& output, const auto& object) {
            using T = std::remove_cvref_t<decltype(object)>;
            const std::uint64_t retval = position;

            if constexpr(std::is_trivially_copyable_v<T>) {
                if constexpr(!calculate) {
                    memcpy(&output[position], &object, sizeof(T));
                }
                position += sizeof(T);
            } else if constexpr (is_keyish<T>{}) {
                using value_t = decltype(T{}[0]);
                std::uint64_t size = object.size();
                serialize_one(output, size);

                if constexpr (is_mappish<T>{}) {
                    for(const auto& [key, val] : object) {
                        serialize_one(output, key);
                        serialize_one(output, val);
                    }
                } else {
                    for(const auto& key : object) {
                        serialize_one(output, key);
                    }
                }
            } else if constexpr (requires { T{}[0]; }){
                using value_t = decltype(T{}[0]);
                const std::uint64_t size = object.size();
                serialize_one(output, size);

                if constexpr(std::is_trivially_copyable_v<value_t>) {
                    if constexpr(!calculate) {
                        memcpy(&output[position], &object[0], sizeof(T) * size);
                    }
                    position += size * sizeof(T);
                } else {
                    for(const auto& element : object) {
                        serialize_one(output, element);
                    }
                }
            } else {
                visit_object(object, [&](auto&& ... args) {
                    return this->serialize(output, args ...);
                });
            }
            return retval;
        }

    template<typename Bytes, bool calculate>
        void FORCE_INLINE Serde<Bytes, calculate>::deserialize(const Bytes& bytes) {
        }

    template<typename Bytes, bool calculate>
        void FORCE_INLINE Serde<Bytes, calculate>::deserialize(const Bytes& bytes, auto& first, auto&& ... objects) {
            deserialize_one(bytes, first);
            deserialize(bytes, objects...);
        }

    template<typename Bytes, bool calculate>
        std::uint64_t FORCE_INLINE Serde<Bytes, calculate>::serialize(Bytes& output) {
            return 0;
        }

    template<typename Bytes, bool calculate>
        std::uint64_t FORCE_INLINE Serde<Bytes, calculate>::serialize(Bytes& output, auto& first, auto&& ... objects) {
            const std::uint64_t retval = serialize_one(output, first);
            serialize(output, objects...);
            return retval;
        }


    template<typename Bytes, typename ... Args>
        std::uint64_t FORCE_INLINE serialize(Bytes& output, const Args& ... args) {
            Serde<Bytes> s;
            s.serialize(output, args...);
            return s.position;
        }

    template<typename Bytes, typename ... Args>
        std::uint64_t FORCE_INLINE deserialize(const Bytes& output, Args& ... args) {
            Serde<Bytes> s;
            s.deserialize(output, args...);
            return s.position;
        }

    template<typename ... Args>
        std::uint64_t FORCE_INLINE getSerializedSize(const Args& ... args) {
            Serde<void*, true> s;
            void* _ = nullptr;
            s.serialize(_, args...);
            return s.position;
        }
}
#undef FORCE_INLINE
