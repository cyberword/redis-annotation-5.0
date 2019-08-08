#include "../redismodule.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/** 获取时间 */
int redisModule_Milliseconds(RedisModuleCtx *ctx, RedisModuleString **argv, int argc){
    long long millSeconds = RedisModule_Milliseconds();
    printf("RedisModule_Milliseconds $hd", millSeconds);
    RedisModule_ReplyWithLongLong(ctx, millSeconds);
    return REDISMODULE_OK;
}
/** 获取截止字符串 */
int redisModule_StringPtrLen(RedisModuleCtx *ctx, RedisModuleString **argv, int argc){
    const char *str = RedisModule_StringPtrLen(*argv, 1);
    RedisModule_ReplyWithString(ctx, str);
    return REDISMODULE_OK;
}

/** 创建module string */
int redisModule_CreateString(RedisModuleCtx *ctx, RedisModuleString **argv, int argc){
    RedisModuleString *str = RedisModule_CreateString(ctx, *argv, sizeof(*argv));
    RedisModule_ReplyWithLongLong(ctx, sizeof(str));
    RedisModule_Free(str);
    return REDISMODULE_OK;
}


int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (RedisModule_Init(ctx, "module_test", 1, REDISMODULE_APIVER_1) == REDISMODULE_ERR){
        return REDISMODULE_ERR;
    }

    /* Log the list of parameters passing loading the module. */
    for (int j = 0; j < argc; j++) {
        const char *s = RedisModule_StringPtrLen(argv[j],NULL);
        printf("Module loaded with ARGV[%d] = %s\n", j, s);
    }

    if (RedisModule_CreateCommand(ctx,"api_RedisModule_Milliseconds",redisModule_Milliseconds, "readonly",0,0,0) == REDISMODULE_ERR){
        return REDISMODULE_ERR;
    }

    if (RedisModule_CreateCommand(ctx,"api_RedisModule_StringPtrLen",redisModule_Milliseconds, "readonly",0,0,0) == REDISMODULE_ERR){
        return REDISMODULE_ERR;
    }

    if (RedisModule_CreateCommand(ctx,"api_RedisModule_CreateString",redisModule_CreateString, "readonly",1,1,1) == REDISMODULE_ERR){
        return REDISMODULE_ERR;
    }


    return REDISMODULE_OK;


}