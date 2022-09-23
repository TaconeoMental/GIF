#define REC_0(a)
#define REC_1(a, X) a(X)
#define REC_2(a, X, ...) a(X)REC_1(a, __VA_ARGS__)
#define REC_3(a, X, ...) a(X)REC_2(a, __VA_ARGS__)
#define REC_4(a, X, ...) a(X)REC_3(a, __VA_ARGS__)
#define REC_5(a, X, ...) a(X)REC_4(a, __VA_ARGS__)
#define REC_6(a, X, ...) a(X)REC_5(a, __VA_ARGS__)
#define REC_7(a, X, ...) a(X)REC_6(a, __VA_ARGS__)
#define REC_8(a, X, ...) a(X)REC_7(a, __VA_ARGS__)
#define REC_9(a, X, ...) a(X)REC_8(a, __VA_ARGS__)
#define REC_10(a, X, ...) a(X)REC_9(a, __VA_ARGS__)
#define REC_11(a, X, ...) a(X)REC_10(a, __VA_ARGS__)
#define REC_12(a, X, ...) a(X)REC_11(a, __VA_ARGS__)
#define REC_13(a, X, ...) a(X)REC_12(a, __VA_ARGS__)
#define REC_14(a, X, ...) a(X)REC_13(a, __VA_ARGS__)
#define REC_15(a, X, ...) a(X)REC_14(a, __VA_ARGS__)
#define UTIL_GET_MACRO(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,N,...) N
#define UTIL_FOR_EACH_MACRO(action, ...) \
    UTIL_GET_MACRO(_0,__VA_ARGS__,REC_15,REC_14,REC_13,REC_12,REC_11,REC_10,REC_9,REC_8,REC_7,REC_6,REC_5,REC_4,REC_3,REC_2,REC_1,REC_0)(action,__VA_ARGS__)

#define REC2_1(a, b)
#define REC2_2(a, b, X) a(b,X)
#define REC2_3(a, b, X, ...) a(b,X)
#define REC2_4(a, b, X, Y, Z,...) a(b,X)REC2_3(a,Y,Z, __VA_ARGS__)
#define REC2_5(a, b, X, Y, Z,...) a(b,X)REC2_4(a,Y,Z, __VA_ARGS__)
#define REC2_6(a, b, X, Y, Z,...) a(b,X)REC2_5(a,Y,Z, __VA_ARGS__)
#define REC2_7(a, b, X, Y, Z,...) a(b,X)REC2_6(a,Y,Z, __VA_ARGS__)
#define REC2_8(a, b, X, Y, Z,...) a(b,X)REC2_7(a,Y,Z,  __VA_ARGS__)
#define REC2_9(a, b, X, Y, Z,...) a(b,X)REC2_8(a,Y,Z, __VA_ARGS__)
#define REC2_10(a, b, X, Y,Z, ...) a(b,X)REC2_9(a,Y,Z, __VA_ARGS__)
#define REC2_11(a, b, X, Y, Z,...) a(b,X)REC2_10(a,Y,Z, __VA_ARGS__)
#define REC2_12(a, b, X, Y, Z,...) a(b,X)REC2_11(a,Y,Z,__VA_ARGS__)
#define REC2_14(a, b, X, Y, Z,...) a(b,X)REC2_13(a,Y,Z, __VA_ARGS__)
#define REC2_13(a, b, X, Y, Z,...) a(b,X)REC2_12(a, Y,Z, __VA_ARGS__)
#define REC2_15(a, b, X, Y, Z,...) a(b,X)REC2_14(a, Y, Z __VA_ARGS__)
#define UTIL_FOR_EACH_MACRO_2_ARGS(action, ...) \
    UTIL_GET_MACRO(_0,__VA_ARGS__,REC2_15,REC2_14,REC2_13,REC2_12,REC2_11,REC2_10,REC2_9,REC2_8,REC2_7,REC2_6,REC2_5,REC2_4,REC2_3,REC2_2,REC2_1)(action,__VA_ARGS__)

// Recursiva para 2 argumentos
#define REC3_1(a, b)
#define REC3_2(a, b, X) a(b,X)
#define REC3_3(a, b, X,...) REC3_2(a,a(b,X),__VA_ARGS__)
#define REC3_4(a, b, X, Y,...) REC3_3(a,a(b,X),Y, __VA_ARGS__)
#define REC3_5(a, b, X, Y,...) REC3_4(a,a(b,X),Y, __VA_ARGS__)
#define REC3_6(a, b, X, Y,...) REC3_5(a,a(b,X),Y,  __VA_ARGS__)
#define REC3_7(a, b, X, Y,...) REC3_6(a,a(b,X),Y, __VA_ARGS__)
#define REC3_8(a, b, X, Y,...) REC3_7(a,a(b,X),Y,  __VA_ARGS__)
#define REC3_9(a, b, X, Y,...) REC3_8(a,a(b,X),Y, __VA_ARGS__)
#define REC3_10(a, b, X, Y,...) REC3_9(a,a(b,X),Y, __VA_ARGS__)
#define REC3_11(a, b, X, Y,...) REC3_10(a,a(b,X),Y, __VA_ARGS__)
#define REC3_12(a, b, X, Y,...) REC3_11(a,a(b,X),Y,__VA_ARGS__)
#define REC3_14(a, b, X, Y,...) REC3_13(a,a(b,X),Y, __VA_ARGS__)
#define REC3_13(a, b, X, Y,...) REC3_12(a, a(b,X),Y, __VA_ARGS__)
#define REC3_15(a, b, X, Y,...) REC3_14(a, a(b,X), Y __VA_ARGS__)
#define UTIL_FOR_EACH_MACRO_RECURSIVE_2_ARGS(action, ...) \
    UTIL_GET_MACRO(_0,__VA_ARGS__,REC3_15,REC3_14,REC3_13,REC3_12,REC3_11,REC3_10,REC3_9,REC3_8,REC3_7,REC3_6,REC3_5,REC3_4,REC3_3,REC3_2,REC3_1)(action,__VA_ARGS__)

#define UTIL_STRNX(A) #A
#define UTIL_STR(A) UTIL_STRNX(A)

#define UTIL_EXPAND(A) A

#define CONCAT_(A,B) A ## B
#define CONCAT__(A,B) CONCAT_(A,B)
#define UTIL_CONCAT(...) \
    UTIL_FOR_EACH_MACRO_RECURSIVE_2_ARGS(CONCAT__,__VA_ARGS__)
