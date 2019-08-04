#include "../redismodule.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int redisModule_Milliseconds(RedisModuleCtx *ctx, RedisModuleString **argv, int argc){
    long long millSeconds = RedisModule_Milliseconds();
    printf("RedisModule_Milliseconds $hd", millSeconds);
    RedisModule_ReplyWithLongLong(ctx, millSeconds);
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

    if (RedisModule_CreateCommand(ctx,"RedisModule_Milliseconds",redisModule_Milliseconds, "readonly",0,0,0) == REDISMODULE_ERR){
        return REDISMODULE_ERR;
    }


    return REDISMODULE_OK;


}